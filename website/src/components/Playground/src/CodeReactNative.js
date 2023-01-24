/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

import yoga from 'yoga-layout/dist/entry-browser';
import LayoutRecord from './LayoutRecord';
import PositionRecord from './PositionRecord';
import {JSEnumLookup} from './CodeJavaScript';
import type {LayoutRecordT} from './LayoutRecord';
import type {Yoga$Direction} from 'yoga-layout';

function getValue(value) {
  return typeof value === 'number' || /^\d+$/.test(value)
    ? String(value)
    : `'${value}'`;
}

function getEnum(yogaEnum: string, value: string | number): string {
  console.log(yogaEnum);
  const enumValue = Object.keys(yoga)
    .filter(
      key =>
        JSEnumLookup[yogaEnum] &&
        key.toLowerCase().startsWith(JSEnumLookup[yogaEnum].toLowerCase()),
    )
    .find(key => yoga[key] === value);

  return enumValue
    ? "'" +
        enumValue
          .replace(/^([A-Z]+)_/, '')
          .replace('_', '-')
          .toLowerCase() +
        "'"
    : getValue(value);
}

function getLayoutCode(node: LayoutRecordT, indent: string = ''): string {
  const lines = [];
  const untouchedLayout = LayoutRecord();
  lines.push(indent + '<View style={{');
  lines.push(indent + '  flex: 1,');
  Object.keys(node.toJSON()).forEach(key => {
    if (key === 'border' && !node.border.equals(untouchedLayout[key])) {
      ['Top', 'Left', 'Right', 'Bottom'].forEach(pKey => {
        if (
          untouchedLayout[key][pKey.toLowerCase()] !==
          node.border[pKey.toLowerCase()]
        ) {
          lines.push(
            indent +
              `  border${pKey}Width: ${getValue(
                node.border[pKey.toLowerCase()],
              )},`,
          );
        }
      });
    } else if (
      node[key] instanceof PositionRecord &&
      !node[key].equals(untouchedLayout[key])
    ) {
      const {top, left, right, bottom} = node[key].toJS();
      if (
        top &&
        top !== untouchedLayout[key].top &&
        top === left &&
        top === right &&
        top === bottom
      ) {
        // all edges
        lines.push(indent + `  ${key}: ${node[key].top},`);
        return;
      }
      const alreadySet = [];
      if (top && top !== untouchedLayout[key].top && top === bottom) {
        lines.push(indent + `  ${key}Vertical: ${getValue(node[key].top)},`);
        alreadySet.push('top', 'bottom');
      }
      if (left && left !== untouchedLayout[key].left && left === right) {
        lines.push(indent + `  ${key}Horizontal: ${getValue(node[key].left)},`);
        alreadySet.push('left', 'right');
      }
      ['left', 'top', 'right', 'bottom'].forEach((pKey, i) => {
        if (
          node[key][pKey] !== untouchedLayout[key][pKey] &&
          alreadySet.indexOf(pKey) === -1 &&
          node[key][pKey] &&
          !Number.isNaN(node[key][pKey])
        ) {
          lines.push(
            indent +
              `  ${key}${pKey[0].toUpperCase()}${pKey.substr(1)}: ${getValue(
                node[key][pKey],
              )},`,
          );
        }
      });
    } else if (
      key === 'positionType' &&
      node[key] === yoga.POSITION_TYPE_ABSOLUTE
    ) {
      lines.push(indent + `  position: 'absolute',`);
    } else if (
      key !== 'children' &&
      node[key] !== untouchedLayout[key] &&
      node[key]
    ) {
      lines.push(indent + `  ${key}: ${getEnum(key, node[key])},`);
    }
  });
  if (node.children.size > 0) {
    lines.push(indent + '}}>');
  } else {
    lines.push(indent + '}} />');
  }
  if (node.children.size > 0) {
    lines.push(
      ...node.children
        .toJSON()
        .map(child => getLayoutCode(child, indent + '  ')),
    );
  }
  if (node.children.size > 0) {
    lines.push(indent + '</View>');
  }
  return lines.join('\n');
}

export default function generateCode(
  root: LayoutRecordT,
  direction: Yoga$Direction,
): string {
  return [
    `import React, {Component} from 'react';`,
    `import {View} from 'react-native';`,
    '',
    'export default class MyLayout extends Component {',
    '  render() {',
    '    return (',
    getLayoutCode(root, '      '),
    '    );',
    '  }',
    '};',
  ].join('\n');
}
