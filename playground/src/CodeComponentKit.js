// @flow
import yoga from 'yoga-layout';
import LayoutRecord from './LayoutRecord';
import PositionRecord from './PositionRecord';
import type {LayoutRecordT} from './LayoutRecord';
import type {Yoga$Direction} from 'yoga-layout';

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

function keyLookup(key: string): string {
  const keyLookup = {
    flexWrap: 'wrap',
    flexDirection: 'direction',
  };
  return keyLookup[key] || key;
}

function getLayoutCode(
  node: LayoutRecordT,
  indent: string = '',
  isRoot?: boolean,
): string {
  const lines = [];

  lines.push(indent + `[CKFlexboxComponent`);
  lines.push(indent + ` newWithView:kWhiteBackgroundView`);
  lines.push(indent + ` size:{${node.width},${node.height}}`);
  lines.push(indent + ` style:{`);
  const untouchedLayout = LayoutRecord({});
  const untouchedPosition = PositionRecord({});

  Object.keys(node.toJSON()).forEach(key => {
    if (
      node[key] instanceof PositionRecord &&
      !node[key].equals(untouchedPosition)
    ) {
      lines.push(indent + `\t.${key} = {`);

      if (key === 'positionType') {
        lines.push(
          indent +
            `\t.position = ${enumLookup.positionType[node.positionType]},`,
        );
      }

      ['top', 'left', 'right', 'bottom'].forEach(pKey => {
        if (node[key][pKey]) {
          lines.push(indent + `\t\t.${pKey} = ${node[key][pKey]},`);
        }
      });

      lines.push(indent + `\t},`);
    } else if (
      key !== 'children' &&
      key !== 'width' &&
      key !== 'height' &&
      node[key] !== untouchedLayout[key]
    ) {
      if (enumLookup[key]) {
        lines.push(
          indent +
            `\t.${keyLookup(key)} = ${enumLookup[key][node.flexDirection]},`,
        );
      } else {
        console.error(`Unknown property ${key}`);
      }
    }
  });
  lines.push(indent + ` }`);

  if (node.children.size > 0) {
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
    lines.push(indent + '}');
  }
  lines[lines.length - 1] += `]${isRoot ? ';' : ''}`;

  return lines.join('\n');
}

export default function generateCode(
  root: LayoutRecordT,
  direction: Yoga$Direction,
): string {
  return ['CKFlexboxComponent *c =', getLayoutCode(root, '\t', true)].join(
    '\n',
  );
}
