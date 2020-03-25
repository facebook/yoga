/**
 * Copyright (c) Facebook, Inc. and its affiliates.
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

function getEnum(yogaEnum: string, value: string | number): string {
  const enumLookup = {
    justifyContent: 'Justify',
    alignItems: 'Align',
    alignContent: 'Align',
    alignSelf: 'Align',
    position: 'Position',
    flexWrap: 'Wrap',
    positionType: 'PositionType',
    direction: 'Driection',
  };

  if (!enumLookup[yogaEnum]) {
    return String(value);
  } else {
    const enumValue = Object.keys(yoga)
      .filter(key =>
        key.toLowerCase().startsWith(JSEnumLookup[yogaEnum].toLowerCase()),
      )
      .find(key => yoga[key] === value);

    return `Yoga${enumLookup[yogaEnum]}.${
      enumValue ? enumValue.replace(/^([A-Z]+)_/, '') : value
    }`;
  }
}

function dipOrPercent(value) {
  console.log(value);
  return value === 'auto'
    ? 'Auto'
    : typeof value === 'string' && /%$/.test(value)
      ? 'Percent'
      : 'Dip';
}

function getValue(value) {
  return value === 'auto' ? '' : `, ${parseFloat(value)}`;
}

function getLayoutCode(
  node: LayoutRecordT,
  indent: string = '',
  isReturning?: boolean,
): string {
  const lines = [];
  const flexDirection = {
    [yoga.FLEX_DIRECTION_ROW]: 'Row',
    [yoga.FLEX_DIRECTION_ROW_REVERSE]: 'RowReverse',
    [yoga.FLEX_DIRECTION_COLUMN]: 'Column',
    [yoga.FLEX_DIRECTION_COLUMN_REVERSE]: 'ColumnReverse',
  };

  lines.push(
    indent +
      `${isReturning ? 'return ' : ''}${
        flexDirection[node.flexDirection]
      }.create(c)`,
  );
  if (node.children.size > 0) {
    lines.push(
      ...node.children
        .toJSON()
        .map(
          child =>
            `${indent}\t.child(\n${getLayoutCode(child, indent + '\t\t')})`,
        ),
    );
  }
  const untouchedLayout = LayoutRecord();
  const untouchedPosition = PositionRecord({});
  Object.keys(node.toJSON()).forEach(key => {
    if (
      node[key] instanceof PositionRecord &&
      !node[key].equals(untouchedPosition)
    ) {
      if (key === 'border') {
        lines.push(indent + '\t.border(', indent + '\t\tBorder.create(c)');
      }

      const {top, left, right, bottom} = node[key].toJS();
      if (
        top !== untouchedPosition.top &&
        top === left &&
        top === right &&
        top === bottom
      ) {
        // all edges
        lines.push(
          indent +
            (key === 'border'
              ? `\t\t\t.width${dipOrPercent(
                  node[key].top,
                )}(YogaEdge.ALL${getValue(node[key].top)})`
              : `\t.${key}${dipOrPercent(node[key].top)}(YogaEdge.ALL${getValue(
                  node[key].top,
                )})`),
        );
        return;
      }
      const alreadySet = [];
      if (top !== untouchedPosition.top && top === bottom) {
        lines.push(
          indent +
            (key === 'border'
              ? `\t\t\t.width${dipOrPercent(
                  node[key].top,
                )}(YogaEdge.VERTICAL${getValue(node[key].top)})`
              : `\t.${key}${dipOrPercent(
                  node[key].top,
                )}(YogaEdge.VERTICAL${getValue(node[key].top)})`),
        );
        alreadySet.push('top', 'bottom');
      }
      if (left !== untouchedPosition.left && left === right) {
        lines.push(
          indent +
            (key === 'border'
              ? `\t\t\t.width${dipOrPercent(
                  node[key].left,
                )}(YogaEdge.HORIZONTAL${getValue(node[key].left)})`
              : `\t.${key}${dipOrPercent(
                  node[key].left,
                )}(YogaEdge.HORIZONTAL${getValue(node[key].left)})`),
        );
        alreadySet.push('left', 'right');
      }
      ['left', 'top', 'right', 'bottom'].forEach((pKey, i) => {
        if (
          node[key][pKey] !== untouchedPosition[pKey] &&
          alreadySet.indexOf(pKey) === -1 &&
          node[key][pKey]
        ) {
          lines.push(
            indent +
              (key === 'border'
                ? `\t\t\t.width${dipOrPercent(
                    node.border[pKey],
                  )}(YogaEdge.${pKey.toUpperCase()}${getValue(
                    node.border[pKey],
                  )})`
                : `\t.${key}${dipOrPercent(
                    node[key][pKey],
                  )}(YogaEdge.${pKey.toUpperCase()}${getValue(
                    node[key][pKey],
                  )})`),
          );
        }
      });

      if (key === 'border') {
        lines.push(
          indent + '\t\t\t.color(YogaEdge.ALL, 0xfff36b7f)',
          indent + '\t\t\t.build())',
        );
      }
    } else if (
      key !== 'children' &&
      key !== 'flexDirection' &&
      node[key] !== untouchedLayout[key] &&
      node[key]
    ) {
      if (node[key] === 'auto') {
        lines.push(indent + `\t.${key}Auto(${getEnum(key, node[key])})`);
      } else if (typeof node[key] === 'string' && /%$/.test(node[key])) {
        lines.push(indent + `\t.${key}Percent(${parseFloat(node[key])})`);
      } else if (
        [
          'width',
          'height',
          'minHeight',
          'maxHeight',
          'minWidth',
          'maxWidth',
          'flexBasis',
        ].indexOf(key) > -1
      ) {
        lines.push(indent + `\t.${key}Dip(${getEnum(key, node[key])})`);
      } else {
        lines.push(indent + `\t.${key}(${getEnum(key, node[key])})`);
      }
    }
  });

  return lines.join('\n');
}

export default function generateCode(
  root: LayoutRecordT,
  direction: Yoga$Direction,
): string {
  return [
    '@LayoutSpec',
    'public class PlaygroundComponentSpec {',
    '\t@OnCreateLayout',
    '\tstatic Component onCreateLayout(ComponentContext c) {',
    getLayoutCode(root, '\t\t', true),
    '\t\t\t.build();',
    '\t}',
    '}',
  ].join('\n');
}
