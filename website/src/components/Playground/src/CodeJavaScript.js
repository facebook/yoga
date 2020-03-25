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
import type {LayoutRecordT} from './LayoutRecord';
import type {Yoga$Direction} from 'yoga-layout';

export const JSEnumLookup = {
  justifyContent: 'JUSTIFY_',
  alignItems: 'ALIGN_',
  alignContent: 'ALIGN_',
  alignSelf: 'ALIGN_',
  position: 'POSITION_',
  flexDirection: 'DIRECTION_',
  flexWrap: 'WRAP_',
  positionType: 'POSITION_TYPE_',
  direction: 'DIRECTION_',
};

function getEnum(yogaEnum: string, value: string | number): string {
  return `yoga.${Object.keys(yoga)
    .filter(key => key.toLowerCase().startsWith(yogaEnum.toLowerCase()))
    .find(key => yoga[key] === value) || value}`;
}

function setProperty(
  name: string,
  key: string,
  value: string,
  enumValue?: string,
): string {
  return [
    name,
    '.set',
    key[0].toUpperCase() + key.substr(1),
    '(',
    enumValue ? `${enumValue}, ` : '',
    JSEnumLookup[key] ? getEnum(JSEnumLookup[key], value) : value,
    ');',
  ].join('');
}

function getLayoutCode(
  node: LayoutRecordT,
  name: string,
  index: number,
): string {
  const lines = [];
  const childName = (i: number) => `${name === 'root' ? 'node' : name}_${i}`;

  lines.push(
    ...node.children.map((node, i) => getLayoutCode(node, childName(i), i)),
  );

  lines.push('', `// create node ${name}`, `const ${name} = Node.create();`);
  const untouchedNode = LayoutRecord({width: '', height: ''});
  Object.keys(untouchedNode.toJS()).forEach(key => {
    if (key !== 'children' && untouchedNode[key] !== node[key]) {
      if (node[key] instanceof PositionRecord) {
        // iterate through position record
        const {top, left, right, bottom} = node[key].toJS();
        if (
          top !== untouchedNode[key].top &&
          top === left &&
          top === right &&
          top === bottom
        ) {
          // all edges
          lines.push(setProperty(name, key, node[key].top, getEnum('edge', 8)));
          return;
        }
        const alreadySet = [];
        if (top !== untouchedNode[key].top && top === bottom) {
          lines.push(setProperty(name, key, node[key].top, getEnum('edge', 7)));
          alreadySet.push('top', 'bottom');
        }
        if (left !== untouchedNode[key].left && left === right) {
          lines.push(
            setProperty(name, key, node[key].left, getEnum('edge', 6)),
          );
          alreadySet.push('left', 'right');
        }
        ['left', 'top', 'right', 'bottom'].forEach((pKey, i) => {
          if (
            node[key][pKey] !== untouchedNode[key][pKey] &&
            alreadySet.indexOf(pKey) === -1
          ) {
            lines.push(
              setProperty(name, key, node[key][pKey], getEnum('edge', i)),
            );
          }
        });
      } else {
        lines.push(setProperty(name, key, node[key]));
      }
    }
  });

  if (node.children && node.children.size > 0) {
    lines.push(
      '',
      '// insert children',
      ...node.children.map(
        (_, i) => `${name}.insertChild(${childName(i)}, ${i});`,
      ),
    );
  }

  return lines.join('\n');
}

export default function generateCode(
  root: LayoutRecordT,
  direction: Yoga$Direction,
): string {
  const rootNodeName = 'root';
  return [
    `import yoga, {Node} from 'yoga-layout';`,
    getLayoutCode(root, rootNodeName, 0),
    '',
    `${rootNodeName}.calculateLayout(${root.width}, ${root.height}, ${getEnum(
      'direction',
      direction,
    )});`,
    `${rootNodeName}.getComputedLayout();`,
  ].join('\n');
}
