/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 * @flow
 * @format
 */

import yoga from 'yoga-layout';
import LayoutRecord from './LayoutRecord';
import PositionRecord from './PositionRecord';
import {JSEnumLookup} from './CodeJavaScript';
import type {LayoutRecordT} from './LayoutRecord';
import type {Yoga$Direction} from 'yoga-layout';

function getEnum(yogaEnum: string, value: string | number): string {
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
    : String(value);
}

function getLayoutCode(node: LayoutRecordT, indent: string = ''): string {
  const lines = [];
  const untouchedLayout = LayoutRecord({width: '', height: ''});
  const untouchedPosition = PositionRecord({});
  lines.push(indent + '<View style={{');
  lines.push(indent + '  flex: 1,');
  Object.keys(node.toJSON()).forEach(key => {
    if (key === 'border' && !node.border.equals(untouchedPosition)) {
      ['Top', 'Left', 'Right', 'Bottom'].forEach(pKey => {
        if (
          untouchedPosition[pKey.toLowerCase()] !==
          node.border[pKey.toLowerCase()]
        ) {
          lines.push(
            indent +
              `  border${pKey}Width: ${node.border[pKey.toLowerCase()]},`,
          );
        }
      });
    } else if (
      node[key] instanceof PositionRecord &&
      !node[key].equals(untouchedPosition)
    ) {
      const {top, left, right, bottom} = node[key].toJS();
      if (
        top !== untouchedPosition.top &&
        top === left &&
        top === right &&
        top === bottom
      ) {
        // all edges
        lines.push(indent + `  ${key}: ${node[key].top},`);
        return;
      }
      const alreadySet = [];
      if (top !== untouchedPosition.top && top === bottom) {
        lines.push(indent + `  ${key}Vertical: ${node[key].top},`);
        alreadySet.push('top', 'bottom');
      }
      if (left !== untouchedPosition.left && left === right) {
        lines.push(indent + `  ${key}Horizontal: ${node[key].left},`);
        alreadySet.push('left', 'right');
      }
      ['left', 'top', 'right', 'bottom'].forEach((pKey, i) => {
        if (
          node[key][pKey] !== untouchedPosition[pKey] &&
          alreadySet.indexOf(pKey) === -1
        ) {
          lines.push(
            indent +
              `  ${key}${pKey[0].toUpperCase()}${pKey.substr(1)}: ${
                node[key][pKey]
              },`,
          );
        }
      });
    } else if (key !== 'children' && node[key] !== untouchedLayout[key]) {
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
