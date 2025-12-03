/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

/* global Emitter:readable */

function toValueCpp(value) {
  const n = value.toString().replace('px', '').replace('%', '');
  return n + (Number(n) == n && n % 1 !== 0 ? 'f' : '');
}

function toFunctionNameCpp(value) {
  if (value.indexOf('%') >= 0) {
    return 'Percent';
  } else if (value.indexOf('Auto') >= 0) {
    return 'Auto';
  } else if (value.indexOf('MaxContent') >= 0) {
    return 'MaxContent';
  } else if (value.indexOf('FitContent') >= 0) {
    return 'FitContent';
  } else if (value.indexOf('Stretch') >= 0) {
    return 'Stretch';
  }

  return '';
}

function keywordFunctionCpp(functionPrefix, nodeName, value) {
  const functionSuffix = toFunctionNameCpp(value);
  if (
    functionSuffix == 'Auto' ||
    functionSuffix == 'MaxContent' ||
    functionSuffix == 'FitContent' ||
    functionSuffix == 'Stretch'
  ) {
    return functionPrefix + functionSuffix + '(' + nodeName + ');';
  } else {
    return (
      functionPrefix +
      functionSuffix +
      '(' +
      nodeName +
      ', ' +
      toValueCpp(value) +
      ');'
    );
  }
}

const CPPEmitter = function () {
  Emitter.call(this, 'cpp', '  ');
};

CPPEmitter.prototype = Object.create(Emitter.prototype, {
  constructor: {value: CPPEmitter},

  emitPrologue: {
    value: function () {
      this.push([
        '#include <gtest/gtest.h>',
        '#include <yoga/Yoga.h>',
        '#include "../util/TestUtil.h"',
        '',
      ]);
    },
  },

  emitTestPrologue: {
    value: function (name, experiments, disabled) {
      this.push('TEST(YogaTest, ' + name + ') {');
      this.pushIndent();

      if (disabled) {
        this.push('GTEST_SKIP();');
        this.push('');
      }

      this.push('YGConfigRef config = YGConfigNew();');
      for (const i in experiments) {
        this.push(
          'YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeature' +
            experiments[i] +
            ', true);',
        );
      }
      this.push('');
    },
  },

  emitTestTreePrologue: {
    value: function (nodeName) {
      this.push('YGNodeRef ' + nodeName + ' = YGNodeNewWithConfig(config);');
    },
  },

  emitTestEpilogue: {
    value: function (_experiments) {
      this.push(['', 'YGNodeFreeRecursive(root);']);

      this.push('');
      this.push('YGConfigFree(config);');

      this.popIndent();
      this.push(['}', '']);
    },
  },

  emitEpilogue: {value: function () {}},

  AssertEQ: {
    value: function (v0, v1) {
      this.push('ASSERT_FLOAT_EQ(' + toValueCpp(v0) + ', ' + v1 + ');');
    },
  },

  YGAlignAuto: {value: 'YGAlignAuto'},
  YGAlignCenter: {value: 'YGAlignCenter'},
  YGAlignFlexEnd: {value: 'YGAlignFlexEnd'},
  YGAlignFlexStart: {value: 'YGAlignFlexStart'},
  YGAlignStretch: {value: 'YGAlignStretch'},
  YGAlignSpaceBetween: {value: 'YGAlignSpaceBetween'},
  YGAlignSpaceAround: {value: 'YGAlignSpaceAround'},
  YGAlignSpaceEvenly: {value: 'YGAlignSpaceEvenly'},
  YGAlignBaseline: {value: 'YGAlignBaseline'},
  YGAlignStart: {value: 'YGAlignStart'},
  YGAlignEnd: {value: 'YGAlignEnd'},

  YGDirectionInherit: {value: 'YGDirectionInherit'},
  YGDirectionLTR: {value: 'YGDirectionLTR'},
  YGDirectionRTL: {value: 'YGDirectionRTL'},

  YGEdgeBottom: {value: 'YGEdgeBottom'},
  YGEdgeEnd: {value: 'YGEdgeEnd'},
  YGEdgeLeft: {value: 'YGEdgeLeft'},
  YGEdgeRight: {value: 'YGEdgeRight'},
  YGEdgeStart: {value: 'YGEdgeStart'},
  YGEdgeTop: {value: 'YGEdgeTop'},

  YGGutterAll: {value: 'YGGutterAll'},
  YGGutterColumn: {value: 'YGGutterColumn'},
  YGGutterRow: {value: 'YGGutterRow'},

  YGFlexDirectionColumn: {value: 'YGFlexDirectionColumn'},
  YGFlexDirectionColumnReverse: {value: 'YGFlexDirectionColumnReverse'},
  YGFlexDirectionRow: {value: 'YGFlexDirectionRow'},
  YGFlexDirectionRowReverse: {value: 'YGFlexDirectionRowReverse'},

  YGJustifyCenter: {value: 'YGJustifyCenter'},
  YGJustifyFlexEnd: {value: 'YGJustifyFlexEnd'},
  YGJustifyFlexStart: {value: 'YGJustifyFlexStart'},
  YGJustifySpaceAround: {value: 'YGJustifySpaceAround'},
  YGJustifySpaceBetween: {value: 'YGJustifySpaceBetween'},
  YGJustifySpaceEvenly: {value: 'YGJustifySpaceEvenly'},
  YGJustifyStretch: {value: 'YGJustifyStretch'},
  YGJustifyStart: {value: 'YGJustifyStart'},
  YGJustifyEnd: {value: 'YGJustifyEnd'},
  YGJustifyAuto: {value: 'YGJustifyAuto'},

  YGOverflowHidden: {value: 'YGOverflowHidden'},
  YGOverflowVisible: {value: 'YGOverflowVisible'},
  YGOverflowScroll: {value: 'YGOverflowScroll'},

  YGPositionTypeAbsolute: {value: 'YGPositionTypeAbsolute'},
  YGPositionTypeRelative: {value: 'YGPositionTypeRelative'},
  YGPositionTypeStatic: {value: 'YGPositionTypeStatic'},

  YGWrapNoWrap: {value: 'YGWrapNoWrap'},
  YGWrapWrap: {value: 'YGWrapWrap'},
  YGWrapWrapReverse: {value: 'YGWrapWrapReverse'},

  YGBoxSizingBorderBox: {value: 'YGBoxSizingBorderBox'},
  YGBoxSizingContentBox: {value: 'YGBoxSizingContentBox'},

  YGUndefined: {value: 'YGUndefined'},

  YGDisplayFlex: {value: 'YGDisplayFlex'},
  YGDisplayNone: {value: 'YGDisplayNone'},
  YGDisplayContents: {value: 'YGDisplayContents'},
  YGAuto: {value: 'YGAuto'},

  YGMaxContent: {value: 'MaxContent'},
  YGFitContent: {value: 'FitContent'},
  YGStretch: {value: 'Stretch'},

  YGDisplayGrid: {value: 'YGDisplayGrid'},

  YGNodeCalculateLayout: {
    value: function (node, dir, _experiments) {
      this.push(
        'YGNodeCalculateLayout(' +
          node +
          ', YGUndefined, YGUndefined, ' +
          dir +
          ');',
      );
    },
  },

  YGNodeInsertChild: {
    value: function (parentName, nodeName, index) {
      this.push(
        'YGNodeInsertChild(' +
          parentName +
          ', ' +
          nodeName +
          ', ' +
          index +
          ');',
      );
    },
  },

  YGNodeLayoutGetLeft: {
    value: function (nodeName) {
      return 'YGNodeLayoutGetLeft(' + nodeName + ')';
    },
  },

  YGNodeLayoutGetTop: {
    value: function (nodeName) {
      return 'YGNodeLayoutGetTop(' + nodeName + ')';
    },
  },

  YGNodeLayoutGetWidth: {
    value: function (nodeName) {
      return 'YGNodeLayoutGetWidth(' + nodeName + ')';
    },
  },

  YGNodeLayoutGetHeight: {
    value: function (nodeName) {
      return 'YGNodeLayoutGetHeight(' + nodeName + ')';
    },
  },

  YGNodeStyleSetAlignContent: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetAlignContent(' +
          nodeName +
          ', ' +
          toValueCpp(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetAlignItems: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetAlignItems(' +
          nodeName +
          ', ' +
          toValueCpp(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetAlignSelf: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetAlignSelf(' + nodeName + ', ' + toValueCpp(value) + ');',
      );
    },
  },

  YGNodeStyleSetAspectRatio: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetAspectRatio' +
          toFunctionNameCpp(value) +
          '(' +
          nodeName +
          ', ' +
          toValueCpp(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetBorder: {
    value: function (nodeName, edge, value) {
      this.push(
        'YGNodeStyleSetBorder(' +
          nodeName +
          ', ' +
          edge +
          ', ' +
          toValueCpp(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetDirection: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetDirection(' + nodeName + ', ' + toValueCpp(value) + ');',
      );
    },
  },

  YGNodeStyleSetDisplay: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetDisplay(' + nodeName + ', ' + toValueCpp(value) + ');',
      );
    },
  },

  YGNodeStyleSetFlexBasis: {
    value: function (nodeName, value) {
      this.push(keywordFunctionCpp('YGNodeStyleSetFlexBasis', nodeName, value));
    },
  },

  YGNodeStyleSetFlexDirection: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetFlexDirection(' +
          nodeName +
          ', ' +
          toValueCpp(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetFlexGrow: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetFlexGrow(' + nodeName + ', ' + toValueCpp(value) + ');',
      );
    },
  },

  YGNodeStyleSetFlexShrink: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetFlexShrink(' +
          nodeName +
          ', ' +
          toValueCpp(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetFlexWrap: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetFlexWrap(' + nodeName + ', ' + toValueCpp(value) + ');',
      );
    },
  },

  YGNodeStyleSetJustifyContent: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetJustifyContent(' +
          nodeName +
          ', ' +
          toValueCpp(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetJustifyItems: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetJustifyItems(' +
          nodeName +
          ', ' +
          toValueCpp(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetJustifySelf: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetJustifySelf(' +
          nodeName +
          ', ' +
          toValueCpp(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetMargin: {
    value: function (nodeName, edge, value) {
      let valueStr = toValueCpp(value);
      if (valueStr != 'YGAuto') {
        valueStr = ', ' + valueStr;
      } else {
        valueStr = '';
      }
      this.push(
        'YGNodeStyleSetMargin' +
          toFunctionNameCpp(value) +
          '(' +
          nodeName +
          ', ' +
          edge +
          valueStr +
          ');',
      );
    },
  },

  YGNodeStyleSetHeight: {
    value: function (nodeName, value) {
      this.push(keywordFunctionCpp('YGNodeStyleSetHeight', nodeName, value));
    },
  },

  YGNodeStyleSetWidth: {
    value: function (nodeName, value) {
      this.push(keywordFunctionCpp('YGNodeStyleSetWidth', nodeName, value));
    },
  },

  YGNodeStyleSetMaxHeight: {
    value: function (nodeName, value) {
      this.push(keywordFunctionCpp('YGNodeStyleSetMaxHeight', nodeName, value));
    },
  },

  YGNodeStyleSetMaxWidth: {
    value: function (nodeName, value) {
      this.push(keywordFunctionCpp('YGNodeStyleSetMaxWidth', nodeName, value));
    },
  },

  YGNodeStyleSetMinHeight: {
    value: function (nodeName, value) {
      this.push(keywordFunctionCpp('YGNodeStyleSetMinHeight', nodeName, value));
    },
  },

  YGNodeStyleSetMinWidth: {
    value: function (nodeName, value) {
      this.push(keywordFunctionCpp('YGNodeStyleSetMinWidth', nodeName, value));
    },
  },

  YGNodeStyleSetOverflow: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetOverflow(' + nodeName + ', ' + toValueCpp(value) + ');',
      );
    },
  },

  YGNodeStyleSetPadding: {
    value: function (nodeName, edge, value) {
      this.push(
        'YGNodeStyleSetPadding' +
          toFunctionNameCpp(value) +
          '(' +
          nodeName +
          ', ' +
          edge +
          ', ' +
          toValueCpp(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetPosition: {
    value: function (nodeName, edge, value) {
      let valueStr = toValueCpp(value);
      if (valueStr != 'YGAuto') {
        valueStr = ', ' + valueStr;
      } else {
        valueStr = '';
      }
      this.push(
        'YGNodeStyleSetPosition' +
          toFunctionNameCpp(value) +
          '(' +
          nodeName +
          ', ' +
          edge +
          valueStr +
          ');',
      );
    },
  },

  YGNodeStyleSetPositionType: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetPositionType(' +
          nodeName +
          ', ' +
          toValueCpp(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetGap: {
    value: function (nodeName, gap, value) {
      this.push(
        'YGNodeStyleSetGap' +
          toFunctionNameCpp(value) +
          '(' +
          nodeName +
          ', ' +
          gap +
          ', ' +
          toValueCpp(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetBoxSizing: {
    value: function (nodeName, value) {
      this.push(
        'YGNodeStyleSetBoxSizing(' + nodeName + ', ' + toValueCpp(value) + ');',
      );
    },
  },

  YGNodeSetMeasureFunc: {
    value: function (nodeName, innerText, _) {
      this.push(`YGNodeSetContext(${nodeName}, (void*)"${innerText}");`);
      this.push(
        `YGNodeSetMeasureFunc(${nodeName}, &facebook::yoga::test::IntrinsicSizeMeasure);`,
      );
    },
  },

  YGNodeStyleSetGridTemplateRows: {
    value: function (nodeName, value) {
      if (!value) {
        return;
      }

      const tracks = parseGridTrackList(this, value);
      if (!tracks || tracks.length === 0) {
        return;
      }

      this.push(`auto ${nodeName}_gridTemplateRows = YGGridTrackListCreate();`);

      for (const track of tracks) {
        if (track.type === 'minmax') {
          const minVal = this.formatGridTrackValue(track.min);
          const maxVal = this.formatGridTrackValue(track.max);
          this.push(
            `YGGridTrackListAddTrack(${nodeName}_gridTemplateRows, YGMinMax(${minVal}, ${maxVal}));`,
          );
        } else {
          const val = this.formatGridTrackValue(track);
          this.push(
            `YGGridTrackListAddTrack(${nodeName}_gridTemplateRows, ${val});`,
          );
        }
      }

      this.push(
        `YGNodeStyleSetGridTemplateRows(${nodeName}, ${nodeName}_gridTemplateRows);`,
      );
      this.push(`YGGridTrackListFree(${nodeName}_gridTemplateRows);`);
    },
  },

  YGNodeStyleSetGridTemplateColumns: {
    value: function (nodeName, value) {
      if (!value) {
        return;
      }

      const tracks = parseGridTrackList(this, value);
      if (!tracks || tracks.length === 0) {
        return;
      }

      this.push(
        `auto ${nodeName}_gridTemplateColumns = YGGridTrackListCreate();`,
      );

      for (const track of tracks) {
        if (track.type === 'minmax') {
          const minVal = this.formatGridTrackValue(track.min);
          const maxVal = this.formatGridTrackValue(track.max);
          this.push(
            `YGGridTrackListAddTrack(${nodeName}_gridTemplateColumns, YGMinMax(${minVal}, ${maxVal}));`,
          );
        } else {
          const val = this.formatGridTrackValue(track);
          this.push(
            `YGGridTrackListAddTrack(${nodeName}_gridTemplateColumns, ${val});`,
          );
        }
      }

      this.push(
        `YGNodeStyleSetGridTemplateColumns(${nodeName}, ${nodeName}_gridTemplateColumns);`,
      );
      this.push(`YGGridTrackListFree(${nodeName}_gridTemplateColumns);`);
    },
  },

  YGNodeStyleSetGridColumnStart: {
    value: function (nodeName, value) {
      this.push(`YGNodeStyleSetGridColumnStart(${nodeName}, ${value});`);
    },
  },

  YGNodeStyleSetGridColumnStartSpan: {
    value: function (nodeName, value) {
      this.push(`YGNodeStyleSetGridColumnStartSpan(${nodeName}, ${value});`);
    },
  },

  YGNodeStyleSetGridColumnEnd: {
    value: function (nodeName, value) {
      this.push(`YGNodeStyleSetGridColumnEnd(${nodeName}, ${value});`);
    },
  },

  YGNodeStyleSetGridColumnEndSpan: {
    value: function (nodeName, value) {
      this.push(`YGNodeStyleSetGridColumnEndSpan(${nodeName}, ${value});`);
    },
  },

  YGNodeStyleSetGridRowStart: {
    value: function (nodeName, value) {
      this.push(`YGNodeStyleSetGridRowStart(${nodeName}, ${value});`);
    },
  },

  YGNodeStyleSetGridRowStartSpan: {
    value: function (nodeName, value) {
      this.push(`YGNodeStyleSetGridRowStartSpan(${nodeName}, ${value});`);
    },
  },

  YGNodeStyleSetGridRowEnd: {
    value: function (nodeName, value) {
      this.push(`YGNodeStyleSetGridRowEnd(${nodeName}, ${value});`);
    },
  },

  YGNodeStyleSetGridRowEndSpan: {
    value: function (nodeName, value) {
      this.push(`YGNodeStyleSetGridRowEndSpan(${nodeName}, ${value});`);
    },
  },

  YGNodeStyleSetGridAutoColumns: {
    value: function (nodeName, value) {
      if (!value) {
        return;
      }

      const tracks = parseGridTrackList(this, value);
      if (!tracks || tracks.length === 0) {
        return;
      }

      this.push(`auto ${nodeName}_gridAutoColumns = YGGridTrackListCreate();`);

      for (const track of tracks) {
        if (track.type === 'minmax') {
          const minVal = this.formatGridTrackValue(track.min);
          const maxVal = this.formatGridTrackValue(track.max);
          this.push(
            `YGGridTrackListAddTrack(${nodeName}_gridAutoColumns, YGMinMax(${minVal}, ${maxVal}));`,
          );
        } else {
          const val = this.formatGridTrackValue(track);
          this.push(
            `YGGridTrackListAddTrack(${nodeName}_gridAutoColumns, ${val});`,
          );
        }
      }

      this.push(
        `YGNodeStyleSetGridAutoColumns(${nodeName}, ${nodeName}_gridAutoColumns);`,
      );
      this.push(`YGGridTrackListFree(${nodeName}_gridAutoColumns);`);
    },
  },

  YGNodeStyleSetGridAutoRows: {
    value: function (nodeName, value) {
      if (!value) {
        return;
      }

      const tracks = parseGridTrackList(this, value);
      if (!tracks || tracks.length === 0) {
        return;
      }

      this.push(`auto ${nodeName}_gridAutoRows = YGGridTrackListCreate();`);

      for (const track of tracks) {
        if (track.type === 'minmax') {
          const minVal = this.formatGridTrackValue(track.min);
          const maxVal = this.formatGridTrackValue(track.max);
          this.push(
            `YGGridTrackListAddTrack(${nodeName}_gridAutoRows, YGMinMax(${minVal}, ${maxVal}));`,
          );
        } else {
          const val = this.formatGridTrackValue(track);
          this.push(
            `YGGridTrackListAddTrack(${nodeName}_gridAutoRows, ${val});`,
          );
        }
      }

      this.push(
        `YGNodeStyleSetGridAutoRows(${nodeName}, ${nodeName}_gridAutoRows);`,
      );
      this.push(`YGGridTrackListFree(${nodeName}_gridAutoRows);`);
    },
  },

  formatGridTrackValue: {
    value: function (track) {
      switch (track.type) {
        case 'auto':
          return 'YGAuto()';
        case 'points':
          return `YGPoints(${toValueCpp(track.value)})`;
        case 'percent':
          return `YGPercent(${toValueCpp(track.value)})`;
        case 'fr':
          return `YGFr(${toValueCpp(track.value)})`;
        default:
          return 'YGAuto()';
      }
    },
  },
});

function parseGridTrackList(e, value) {
  if (!value || value === 'none') {
    return null;
  }

  // Parse space-separated track values
  // Examples: "100px 100px 100px", "100px 100% minmax(100px, 200px) auto"
  const tracks = [];
  const parts = value.trim().split(/\s+/);

  let i = 0;
  while (i < parts.length) {
    const part = parts[i];

    if (part.startsWith('minmax(')) {
      // Handle minmax function - may span multiple parts if there are spaces
      let minmaxStr = part;
      while (!minmaxStr.includes(')') && i < parts.length - 1) {
        i++;
        minmaxStr += ' ' + parts[i];
      }

      // Extract min and max values from minmax(min, max)
      const match = minmaxStr.match(/minmax\(([^,]+),\s*([^)]+)\)/);
      if (match) {
        const min = match[1].trim();
        const max = match[2].trim();
        tracks.push({
          type: 'minmax',
          min: parseGridTrackValue(e, min),
          max: parseGridTrackValue(e, max),
        });
      }
    } else {
      // Simple track value
      tracks.push(parseGridTrackValue(e, part));
    }
    i++;
  }

  return tracks;
}

function parseGridTrackValue(e, value) {
  if (value === 'auto') {
    return {type: 'auto'};
  } else if (value.endsWith('px')) {
    return {type: 'points', value: parseFloat(value)};
  } else if (value.endsWith('%')) {
    return {type: 'percent', value: parseFloat(value)};
  } else if (value.endsWith('fr')) {
    return {type: 'fr', value: parseFloat(value)};
  }
  return {type: 'auto'};
}
