/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

/* global Emitter:readable */

function parseGridTrackListJS(value) {
  if (!value || value === 'none') {
    return null;
  }

  if (typeof value !== 'string') {
    return null;
  }

  const tracks = [];
  const parts = value.trim().split(/\s+/);

  let i = 0;
  while (i < parts.length) {
    const part = parts[i];

    if (part.startsWith('minmax(')) {
      let minmaxStr = part;
      while (!minmaxStr.includes(')') && i < parts.length - 1) {
        i++;
        minmaxStr += ' ' + parts[i];
      }

      const match = minmaxStr.match(/minmax\(([^,]+),\s*([^)]+)\)/);
      if (match) {
        const min = match[1].trim();
        const max = match[2].trim();
        tracks.push({
          type: 'minmax',
          min: parseGridTrackValueJS(min),
          max: parseGridTrackValueJS(max),
        });
      }
    } else {
      tracks.push(parseGridTrackValueJS(part));
    }
    i++;
  }

  return tracks;
}

function parseGridTrackValueJS(value) {
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

const JavascriptEmitter = function () {
  Emitter.call(this, 'js', '  ');
};

function toValueJavascript(value) {
  if (value.match(/^[0-9.e+-]+px$/i)) return parseFloat(value);
  if (value.match(/^[0-9.e+-]+%/i)) return JSON.stringify(value);
  if (value == 'Yoga.AUTO') return '"auto"';
  if (value == 'max-content') return '"max-content"';
  if (value == 'fit-content') return '"fit-content"';
  if (value == 'stretch') return '"stretch"';
  return value;
}

JavascriptEmitter.prototype = Object.create(Emitter.prototype, {
  constructor: {value: JavascriptEmitter},

  emitPrologue: {
    value: function () {
      this.push(
        "import { instrinsicSizeMeasureFunc } from '../tools/utils.ts'",
      );
      this.push("import Yoga from 'yoga-layout';");
      this.push('import {');
      this.pushIndent();
      this.push('Align,');
      this.push('BoxSizing,');
      this.push('Direction,');
      this.push('Display,');
      this.push('Edge,');
      this.push('Errata,');
      this.push('ExperimentalFeature,');
      this.push('FlexDirection,');
      this.push('GridTrackType,');
      this.push('Gutter,');
      this.push('Justify,');
      this.push('MeasureMode,');
      this.push('Overflow,');
      this.push('PositionType,');
      this.push('Unit,');
      this.push('Wrap,');
      this.popIndent();
      this.push("} from 'yoga-layout';");
      this.push('');
    },
  },

  emitTestPrologue: {
    value: function (name, experiments, ignore) {
      const testFn = ignore ? `test.skip` : 'test';
      this.push(`${testFn}('${name}', () => {`);
      this.pushIndent();
      this.push('const config = Yoga.Config.create();');
      this.push('let root;');
      this.push('');

      if (experiments.length > 0) {
        for (const experiment of experiments) {
          this.push(
            `config.setExperimentalFeatureEnabled(ExperimentalFeature.${experiment}, true);`,
          );
        }
        this.push('');
      }

      this.push('try {');
      this.pushIndent();
    },
  },

  emitTestTreePrologue: {
    value: function (nodeName) {
      if (nodeName === 'root') {
        this.push(`root = Yoga.Node.create(config);`);
      } else {
        this.push(`const ${nodeName} = Yoga.Node.create(config);`);
      }
    },
  },

  emitTestEpilogue: {
    value: function (_experiments) {
      this.popIndent();
      this.push('} finally {');
      this.pushIndent();

      this.push("if (typeof root !== 'undefined') {");
      this.pushIndent();
      this.push('root.freeRecursive();');
      this.popIndent();
      this.push('}');
      this.push('');
      this.push('config.free();');

      this.popIndent();
      this.push('}');

      this.popIndent();
      this.push('});');
    },
  },

  emitEpilogue: {
    value: function () {
      this.push('');
    },
  },

  AssertEQ: {
    value: function (v0, v1) {
      this.push(`expect(${v1}).toBe(${v0});`);
    },
  },

  YGAlignAuto: {value: 'Align.Auto'},
  YGAlignCenter: {value: 'Align.Center'},
  YGAlignFlexEnd: {value: 'Align.FlexEnd'},
  YGAlignFlexStart: {value: 'Align.FlexStart'},
  YGAlignStretch: {value: 'Align.Stretch'},
  YGAlignSpaceBetween: {value: 'Align.SpaceBetween'},
  YGAlignSpaceAround: {value: 'Align.SpaceAround'},
  YGAlignSpaceEvenly: {value: 'Align.SpaceEvenly'},
  YGAlignBaseline: {value: 'Align.Baseline'},
  YGAlignStart: {value: 'Align.Start'},
  YGAlignEnd: {value: 'Align.End'},

  YGDirectionInherit: {value: 'Direction.Inherit'},
  YGDirectionLTR: {value: 'Direction.LTR'},
  YGDirectionRTL: {value: 'Direction.RTL'},

  YGEdgeBottom: {value: 'Edge.Bottom'},
  YGEdgeEnd: {value: 'Edge.End'},
  YGEdgeLeft: {value: 'Edge.Left'},
  YGEdgeRight: {value: 'Edge.Right'},
  YGEdgeStart: {value: 'Edge.Start'},
  YGEdgeTop: {value: 'Edge.Top'},

  YGGutterAll: {value: 'Gutter.All'},
  YGGutterColumn: {value: 'Gutter.Column'},
  YGGutterRow: {value: 'Gutter.Row'},

  YGFlexDirectionColumn: {value: 'FlexDirection.Column'},
  YGFlexDirectionColumnReverse: {value: 'FlexDirection.ColumnReverse'},
  YGFlexDirectionRow: {value: 'FlexDirection.Row'},
  YGFlexDirectionRowReverse: {value: 'FlexDirection.RowReverse'},

  YGJustifyCenter: {value: 'Justify.Center'},
  YGJustifyFlexEnd: {value: 'Justify.FlexEnd'},
  YGJustifyFlexStart: {value: 'Justify.FlexStart'},
  YGJustifySpaceAround: {value: 'Justify.SpaceAround'},
  YGJustifySpaceBetween: {value: 'Justify.SpaceBetween'},
  YGJustifySpaceEvenly: {value: 'Justify.SpaceEvenly'},
  YGJustifyStretch: {value: 'Justify.Stretch'},
  YGJustifyStart: {value: 'Justify.Start'},
  YGJustifyEnd: {value: 'Justify.End'},
  YGJustifyAuto: {value: 'Justify.Auto'},

  YGOverflowHidden: {value: 'Overflow.Hidden'},
  YGOverflowVisible: {value: 'Overflow.Visible'},
  YGOverflowScroll: {value: 'Overflow.Scroll'},

  YGPositionTypeAbsolute: {value: 'PositionType.Absolute'},
  YGPositionTypeRelative: {value: 'PositionType.Relative'},
  YGPositionTypeStatic: {value: 'PositionType.Static'},

  YGAuto: {value: "'auto'"},
  YGUndefined: {value: 'undefined'},

  YGWrapNoWrap: {value: 'Wrap.NoWrap'},
  YGWrapWrap: {value: 'Wrap.Wrap'},
  YGWrapWrapReverse: {value: 'Wrap.WrapReverse'},

  YGDisplayFlex: {value: 'Display.Flex'},
  YGDisplayNone: {value: 'Display.None'},
  YGDisplayContents: {value: 'Display.Contents'},

  YGBoxSizingBorderBox: {value: 'BoxSizing.BorderBox'},
  YGBoxSizingContentBox: {value: 'BoxSizing.ContentBox'},

  YGMaxContent: {value: 'max-content'},
  YGFitContent: {value: 'fit-content'},
  YGStretch: {value: 'stretch'},

  YGDisplayGrid: {value: 'Display.Grid'},

  YGNodeCalculateLayout: {
    value: function (node, dir, _experiments) {
      this.push(node + '.calculateLayout(undefined, undefined, ' + dir + ');');
    },
  },

  YGNodeInsertChild: {
    value: function (parentName, nodeName, index) {
      this.push(parentName + '.insertChild(' + nodeName + ', ' + index + ');');
    },
  },

  YGNodeLayoutGetLeft: {
    value: function (nodeName) {
      return nodeName + '.getComputedLeft()';
    },
  },

  YGNodeLayoutGetTop: {
    value: function (nodeName) {
      return nodeName + '.getComputedTop()';
    },
  },

  YGNodeLayoutGetWidth: {
    value: function (nodeName) {
      return nodeName + '.getComputedWidth()';
    },
  },

  YGNodeLayoutGetHeight: {
    value: function (nodeName) {
      return nodeName + '.getComputedHeight()';
    },
  },

  YGNodeStyleSetAlignContent: {
    value: function (nodeName, value) {
      this.push(
        nodeName + '.setAlignContent(' + toValueJavascript(value) + ');',
      );
    },
  },

  YGNodeStyleSetAlignItems: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setAlignItems(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetAlignSelf: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setAlignSelf(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetAspectRatio: {
    value: function (nodeName, value) {
      this.push(
        nodeName + '.setAspectRatio(' + toValueJavascript(value) + ');',
      );
    },
  },

  YGNodeStyleSetBorder: {
    value: function (nodeName, edge, value) {
      this.push(
        nodeName +
          '.setBorder(' +
          toValueJavascript(edge) +
          ', ' +
          toValueJavascript(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetDirection: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setDirection(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetDisplay: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setDisplay(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetFlexBasis: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setFlexBasis(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetFlexDirection: {
    value: function (nodeName, value) {
      this.push(
        nodeName + '.setFlexDirection(' + toValueJavascript(value) + ');',
      );
    },
  },

  YGNodeStyleSetFlexGrow: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setFlexGrow(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetFlexShrink: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setFlexShrink(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetFlexWrap: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setFlexWrap(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetHeight: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setHeight(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetJustifyContent: {
    value: function (nodeName, value) {
      this.push(
        nodeName + '.setJustifyContent(' + toValueJavascript(value) + ');',
      );
    },
  },

  YGNodeStyleSetJustifyItems: {
    value: function (nodeName, value) {
      this.push(
        nodeName + '.setJustifyItems(' + toValueJavascript(value) + ');',
      );
    },
  },

  YGNodeStyleSetJustifySelf: {
    value: function (nodeName, value) {
      this.push(
        nodeName + '.setJustifySelf(' + toValueJavascript(value) + ');',
      );
    },
  },

  YGNodeStyleSetMargin: {
    value: function (nodeName, edge, value) {
      this.push(
        nodeName +
          '.setMargin(' +
          toValueJavascript(edge) +
          ', ' +
          toValueJavascript(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetMaxHeight: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setMaxHeight(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetMaxWidth: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setMaxWidth(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetMinHeight: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setMinHeight(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetMinWidth: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setMinWidth(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetOverflow: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setOverflow(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetPadding: {
    value: function (nodeName, edge, value) {
      this.push(
        nodeName +
          '.setPadding(' +
          toValueJavascript(edge) +
          ', ' +
          toValueJavascript(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetPosition: {
    value: function (nodeName, edge, value) {
      const valueStr = toValueJavascript(value);

      if (valueStr == "'auto'") {
        this.push(
          nodeName + '.setPositionAuto(' + toValueJavascript(edge) + ');',
        );
      } else {
        this.push(
          nodeName +
            '.setPosition(' +
            toValueJavascript(edge) +
            ', ' +
            valueStr +
            ');',
        );
      }
    },
  },

  YGNodeStyleSetPositionType: {
    value: function (nodeName, value) {
      this.push(
        nodeName + '.setPositionType(' + toValueJavascript(value) + ');',
      );
    },
  },

  YGNodeStyleSetWidth: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setWidth(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeStyleSetGap: {
    value: function (nodeName, gap, value) {
      this.push(
        nodeName +
          '.setGap(' +
          toValueJavascript(gap) +
          ', ' +
          toValueJavascript(value) +
          ');',
      );
    },
  },

  YGNodeStyleSetBoxSizing: {
    value: function (nodeName, value) {
      this.push(nodeName + '.setBoxSizing(' + toValueJavascript(value) + ');');
    },
  },

  YGNodeSetMeasureFunc: {
    value: function (nodeName, innerText, flexDirection) {
      this.push(
        `${nodeName}.setMeasureFunc(instrinsicSizeMeasureFunc.bind({text: "${innerText}", flexDirection: ${toValueJavascript(
          flexDirection,
        )}}));`,
      );
    },
  },

  YGNodeStyleSetGridTemplateRows: {
    value: function (nodeName, value) {
      const tracks = parseGridTrackListJS(value);
      if (!tracks || tracks.length === 0) {
        return;
      }

      this.push(`const ${nodeName}GridTemplateRows = [];`);

      for (const track of tracks) {
        if (track.type === 'minmax') {
          const minVal = this.formatGridTrackValueJS(track.min);
          const maxVal = this.formatGridTrackValueJS(track.max);
          this.push(
            `${nodeName}GridTemplateRows.push({type: GridTrackType.Minmax, min: ${minVal}, max: ${maxVal}});`,
          );
        } else {
          const val = this.formatGridTrackValueJS(track);
          this.push(`${nodeName}GridTemplateRows.push(${val});`);
        }
      }

      this.push(
        `${nodeName}.setGridTemplateRows(${nodeName}GridTemplateRows);`,
      );
    },
  },

  YGNodeStyleSetGridTemplateColumns: {
    value: function (nodeName, value) {
      const tracks = parseGridTrackListJS(value);
      if (!tracks || tracks.length === 0) {
        return;
      }

      this.push(`const ${nodeName}GridTemplateColumns = [];`);

      for (const track of tracks) {
        if (track.type === 'minmax') {
          const minVal = this.formatGridTrackValueJS(track.min);
          const maxVal = this.formatGridTrackValueJS(track.max);
          this.push(
            `${nodeName}GridTemplateColumns.push({type: GridTrackType.Minmax, min: ${minVal}, max: ${maxVal}});`,
          );
        } else {
          const val = this.formatGridTrackValueJS(track);
          this.push(`${nodeName}GridTemplateColumns.push(${val});`);
        }
      }

      this.push(
        `${nodeName}.setGridTemplateColumns(${nodeName}GridTemplateColumns);`,
      );
    },
  },

  YGNodeStyleSetGridColumnStart: {
    value: function (nodeName, value) {
      this.push(`${nodeName}.setGridColumnStart(${value});`);
    },
  },

  YGNodeStyleSetGridColumnStartSpan: {
    value: function (nodeName, value) {
      this.push(`${nodeName}.setGridColumnStartSpan(${value});`);
    },
  },

  YGNodeStyleSetGridColumnEnd: {
    value: function (nodeName, value) {
      this.push(`${nodeName}.setGridColumnEnd(${value});`);
    },
  },

  YGNodeStyleSetGridColumnEndSpan: {
    value: function (nodeName, value) {
      this.push(`${nodeName}.setGridColumnEndSpan(${value});`);
    },
  },

  YGNodeStyleSetGridRowStart: {
    value: function (nodeName, value) {
      this.push(`${nodeName}.setGridRowStart(${value});`);
    },
  },

  YGNodeStyleSetGridRowStartSpan: {
    value: function (nodeName, value) {
      this.push(`${nodeName}.setGridRowStartSpan(${value});`);
    },
  },

  YGNodeStyleSetGridRowEnd: {
    value: function (nodeName, value) {
      this.push(`${nodeName}.setGridRowEnd(${value});`);
    },
  },

  YGNodeStyleSetGridRowEndSpan: {
    value: function (nodeName, value) {
      this.push(`${nodeName}.setGridRowEndSpan(${value});`);
    },
  },

  YGNodeStyleSetGridAutoColumns: {
    value: function (nodeName, value) {
      const tracks = parseGridTrackListJS(value);
      if (!tracks || tracks.length === 0) {
        return;
      }

      this.push(`const ${nodeName}GridAutoColumns = [];`);

      for (const track of tracks) {
        if (track.type === 'minmax') {
          const minVal = this.formatGridTrackValueJS(track.min);
          const maxVal = this.formatGridTrackValueJS(track.max);
          this.push(
            `${nodeName}GridAutoColumns.push({type: GridTrackType.Minmax, min: ${minVal}, max: ${maxVal}});`,
          );
        } else {
          const val = this.formatGridTrackValueJS(track);
          this.push(`${nodeName}GridAutoColumns.push(${val});`);
        }
      }

      this.push(`${nodeName}.setGridAutoColumns(${nodeName}GridAutoColumns);`);
    },
  },

  YGNodeStyleSetGridAutoRows: {
    value: function (nodeName, value) {
      const tracks = parseGridTrackListJS(value);
      if (!tracks || tracks.length === 0) {
        return;
      }

      this.push(`const ${nodeName}GridAutoRows = [];`);

      for (const track of tracks) {
        if (track.type === 'minmax') {
          const minVal = this.formatGridTrackValueJS(track.min);
          const maxVal = this.formatGridTrackValueJS(track.max);
          this.push(
            `${nodeName}GridAutoRows.push({type: GridTrackType.Minmax, min: ${minVal}, max: ${maxVal}});`,
          );
        } else {
          const val = this.formatGridTrackValueJS(track);
          this.push(`${nodeName}GridAutoRows.push(${val});`);
        }
      }

      this.push(`${nodeName}.setGridAutoRows(${nodeName}GridAutoRows);`);
    },
  },

  formatGridTrackValueJS: {
    value: function (track) {
      switch (track.type) {
        case 'auto':
          return `{type: GridTrackType.Auto}`;
        case 'points':
          return `{type: GridTrackType.Points, value: ${toValueJavascript(
            track.value + 'px',
          )}}`;
        case 'percent':
          return `{type: GridTrackType.Percent, value: ${track.value}}`;
        case 'fr':
          return `{type: GridTrackType.Fr, value: ${track.value}}`;
        default:
          return `{type: GridTrackType.Auto}`;
      }
    },
  },
});
