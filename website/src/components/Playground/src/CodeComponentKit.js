/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// @flow
import yoga from 'yoga-layout/dist/entry-browser';
import LayoutRecord from './LayoutRecord';
import PositionRecord from './PositionRecord';
import type {LayoutRecordT} from './LayoutRecord';
import type {Yoga$Direction, Yoga$Node} from 'yoga-layout';

const enumLookup = {
  flexDirection: {
    [yoga.FLEX_DIRECTION_COLUMN]: 'CKFlexboxDirectionVertical',
    [yoga.FLEX_DIRECTION_ROW]: 'CKFlexboxDirectionHorizontal',
    [yoga.FLEX_DIRECTION_COLUMN_REVERSE]: 'CKFlexboxDirectionVerticalReverse',
    [yoga.FLEX_DIRECTION_ROW_REVERSE]: 'CKFlexboxDirectionHorizontalReverse',
  },
  alignItems: {
    [yoga.ALIGN_FLEX_START]: 'CKFlexboxAlignItemsStart',
    [yoga.ALIGN_FLEX_END]: 'CKFlexboxAlignItemsEnd',
    [yoga.ALIGN_CENTER]: 'CKFlexboxAlignItemsCenter',
    [yoga.ALIGN_BASELINE]: 'CKFlexboxAlignItemsBaseline',
    [yoga.ALIGN_STRETCH]: 'CKFlexboxAlignItemsStretch',
  },
  alignSelf: {
    [yoga.ALIGN_AUTO]: 'CKFlexboxAlignSelfAuto',
    [yoga.ALIGN_FLEX_START]: 'CKFlexboxAlignSelfStart',
    [yoga.ALIGN_FLEX_END]: 'CKFlexboxAlignSelfEnd',
    [yoga.ALIGN_CENTER]: 'CKFlexboxAlignSelfCenter',
    [yoga.ALIGN_BASELINE]: 'CKFlexboxAlignSelfBaseline',
    [yoga.ALIGN_STRETCH]: 'CKFlexboxAlignSelfStretch',
  },
  alignContent: {
    [yoga.ALIGN_FLEX_START]: 'CKFlexboxAlignContentStart',
    [yoga.ALIGN_FLEX_END]: 'CKFlexboxAlignContentEnd',
    [yoga.ALIGN_CENTER]: 'CKFlexboxAlignContentCenter',
    [yoga.ALIGN_SPACE_BETWEEN]: 'CKFlexboxAlignContentSpaceBetween',
    [yoga.ALIGN_SPACE_AROUND]: 'CKFlexboxAlignContentSpaceAround',
    [yoga.ALIGN_STRETCH]: 'CKFlexboxAlignContentStretch',
  },
  justifyContent: {
    [yoga.JUSTIFY_FLEX_START]: 'CKFlexboxJustifyContentStart',
    [yoga.JUSTIFY_CENTER]: 'CKFlexboxJustifyContentCenter',
    [yoga.JUSTIFY_FLEX_END]: 'CKFlexboxJustifyContentEnd',
    [yoga.JUSTIFY_SPACE_BETWEEN]: 'CKFlexboxJustifyContentSpaceBetween',
    [yoga.JUSTIFY_SPACE_AROUND]: 'CKFlexboxJustifyContentSpaceAround',
  },
  flexWrap: {
    [yoga.WRAP_NO_WRAP]: 'CKFlexboxWrapNoWrap',
    [yoga.WRAP_WRAP]: 'CKFlexboxWrapWrap',
    [yoga.WRAP_WRAP_REVERSE]: 'CKFlexboxWrapWrapReverse',
  },
  positionType: {
    [yoga.POSITION_TYPE_RELATIVE]: 'CKFlexboxPositionTypeRelative',
    [yoga.POSITION_TYPE_ABSOLUTE]: 'CKFlexboxPositionTypeAbsolute',
  },
};

const untouchedLayout = LayoutRecord({});
const untouchedPosition = PositionRecord({});

function keyLookup(key: string): string {
  const keyLookup = {
    flexWrap: 'wrap',
    flexDirection: 'direction',
  };
  return keyLookup[key] || key;
}

function getValue(value) {
  if (typeof value === 'string' && /%$/.test(value)) {
    return `RCRelativeDimension::Percent(${parseFloat(value)})`;
  } else if (value === 'auto') {
    return 'RCRelativeDimension::Auto()';
  } else {
    return String(parseFloat(value));
  }
}

function getLayoutCode(
  node: LayoutRecordT,
  indent: string = '',
  isRoot?: boolean,
): string {
  const lines = [];
  const isFlexbox = node.children.size > 0;

  lines.push(
    indent +
      `${isRoot ? '' : `.component = \n${indent}`}[${
        isFlexbox ? 'CKFlexboxComponent' : 'CKComponent'
      }`,
  );
  lines.push(indent + ` newWithView:{}`);
  lines.push(
    indent + ` size:{${getValue(node.width)},${getValue(node.height)}}`,
  );

  const CKFlexboxComponentStyle = [
    'direction',
    'margin',
    'justifyContent',
    'alignItems',
    'alignContent',
    'wrap',
    'padding',
    'border',
  ];
  const CKFlexboxComponentChild = [
    'margin',
    'padding',
    'flexGrow',
    'flexShrink',
    'flexBasis',
    'alignSelf',
    'position',
  ];

  if (isFlexbox) {
    // render styles
    lines.push(indent + ` style:{`);
    indent += '\t';
    CKFlexboxComponentStyle.forEach(key => {
      let line = renderKey(node, key, indent);
      if (line) {
        lines.push(line);
      }
    });
    indent = indent.substr(-1);
    lines.push(indent + ` }`);

    // render children
    lines.push(indent + ' children:{');
    lines.push(
      ...node.children
        .toJSON()
        .map(
          child =>
            `${indent}\t{\n${getLayoutCode(
              child,
              indent + '\t\t',
            )}\n${indent}\t},`,
        ),
    );
    lines.push(indent + `}]${isRoot ? ';' : ','}`);
  } else {
    lines[lines.length - 1] += '],';
    CKFlexboxComponentChild.forEach(key => {
      let line = renderKey(node, key, indent);
      if (line) {
        lines.push(line);
      }
    });
  }

  return lines.join('\n');
}

function renderKey(node: Yoga$Node, key: string, indent: string): ?string {
  if (
    node[key] instanceof PositionRecord &&
    !node[key].equals(untouchedPosition)
  ) {
    const lines = [];
    lines.push(indent + `.${key} = {`);

    if (key === 'position') {
      lines.push(
        indent + `\t.type = ${enumLookup.positionType[node.positionType]},`,
      );
    }

    ['top', 'start', 'end', 'bottom'].forEach(pKey => {
      if (node[key][pKey]) {
        lines.push(indent + `\t.${pKey} = ${getValue(node[key][pKey])},`);
      }
    });

    lines.push(indent + `},`);
    return lines.join('\n');
  } else if (node[key] !== untouchedLayout[key]) {
    if (enumLookup[key]) {
      return indent + `.${keyLookup(key)} = ${enumLookup[key][node[key]]},`;
    } else {
      console.error(`Unknown property ${key}`);
    }
  }
}

export default function generateCode(
  root: LayoutRecordT,
  direction: Yoga$Direction,
): string {
  return ['CKFlexboxComponent *c =', getLayoutCode(root, '\t', true)].join(
    '\n',
  );
}
