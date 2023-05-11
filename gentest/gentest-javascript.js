/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

const JavascriptEmitter = function() {
  Emitter.call(this, 'js', '  ');
};

function toValueJavascript(value) {
  if (value.match(/^[0-9.e+-]+px$/i)) return parseFloat(value);
  if (value.match(/^[0-9.e+-]+%/i)) return JSON.stringify(value);
  if (value == 'Yoga.AUTO') return '"auto"';
  return value;
}

JavascriptEmitter.prototype = Object.create(Emitter.prototype, {
  constructor:{value:JavascriptEmitter},

  emitPrologue:{value:function() {
    this.push('import {Yoga} from "../tools/globals";')
    this.push('import {')
    this.pushIndent();
    this.push('Align,');
    this.push('Direction,');
    this.push('Display,');
    this.push('Edge,');
    this.push('Errata,');
    this.push('ExperimentalFeature,');
    this.push('FlexDirection,');
    this.push('Gutter,');
    this.push('Justify,');
    this.push('MeasureMode,');
    this.push('Overflow,');
    this.push('PositionType,');
    this.push('Unit,');
    this.push('Wrap,');
    this.popIndent();
    this.push('} from \'yoga-layout\';');
    this.push('');
  }},

  emitTestPrologue:{value:function(name, experiments, ignore) {
    const testFn = ignore ? `test.skip` : 'test';
    this.push(`${testFn}('${name}', () => {`);
    this.pushIndent();
    this.push('const config = Yoga.Config.create();');
    this.push('let root;');
    this.push('');

    if (experiments.length > 0) {
      for (const experiment of experiments) {
        this.push(`config.setExperimentalFeatureEnabled(ExperimentalFeature.${experiment}, true);`);
      }
      this.push('');
    }

    this.push('try {');
    this.pushIndent();
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    if (nodeName === 'root') {
      this.push(`root = Yoga.Node.create(config);`);
    } else {
      this.push(`const ${nodeName} = Yoga.Node.create(config);`);
    }
  }},

  emitTestEpilogue:{value:function(experiments) {
    this.popIndent();
    this.push('} finally {');
    this.pushIndent();

    this.push('if (typeof root !== \'undefined\') {');
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
  }},

  emitEpilogue:{value:function () {
    this.push('');
  }},

  AssertEQ:{value:function(v0, v1) {
    this.push(`expect(${v1}).toBe(${v0});`);
  }},

  YGAlignAuto:{value: 'Align.Auto'},
  YGAlignCenter:{value: 'Align.Center'},
  YGAlignFlexEnd:{value: 'Align.FlexEnd'},
  YGAlignFlexStart:{value: 'Align.FlexStart'},
  YGAlignStretch:{value: 'Align.Stretch'},
  YGAlignSpaceBetween:{value: 'Align.SpaceBetween'},
  YGAlignSpaceAround:{value: 'Align.SpaceAround'},
  YGAlignBaseline:{value: 'Align.Baseline'},

  YGDirectionInherit:{value: 'Direction.Inherit'},
  YGDirectionLTR:{value: 'Direction.LTR'},
  YGDirectionRTL:{value: 'Direction.RTL'},

  YGEdgeBottom:{value: 'Edge.Bottom'},
  YGEdgeEnd:{value: 'Edge.End'},
  YGEdgeLeft:{value: 'Edge.Left'},
  YGEdgeRight:{value: 'Edge.Right'},
  YGEdgeStart:{value: 'Edge.Start'},
  YGEdgeTop:{value: 'Edge.Top'},

  YGGutterAll:{value: 'Gutter.All'},
  YGGutterColumn:{value: 'Gutter.Column'},
  YGGutterRow:{value: 'Gutter.Row'},

  YGFlexDirectionColumn:{value: 'FlexDirection.Column'},
  YGFlexDirectionColumnReverse:{value: 'FlexDirection.ColumnReverse'},
  YGFlexDirectionRow:{value: 'FlexDirection.Row'},
  YGFlexDirectionRowReverse:{value: 'FlexDirection.RowReverse'},

  YGJustifyCenter:{value: 'Justify.Center'},
  YGJustifyFlexEnd:{value: 'Justify.FlexEnd'},
  YGJustifyFlexStart:{value: 'Justify.FlexStart'},
  YGJustifySpaceAround:{value: 'Justify.SpaceAround'},
  YGJustifySpaceBetween:{value: 'Justify.SpaceBetween'},
  YGJustifySpaceEvenly:{value: 'Justify.SpaceEvenly'},

  YGOverflowHidden:{value: 'Overflow.Hidden'},
  YGOverflowVisible:{value: 'Overflow.Visible'},

  YGPositionTypeAbsolute:{value: 'PositionType.Absolute'},
  YGPositionTypeRelative:{value: 'PositionType.Relative'},

  YGAuto:{value:'\'auto\''},
  YGUndefined:{value:'undefined'},

  YGWrapNoWrap:{value: 'Wrap.NoWrap'},
  YGWrapWrap:{value: 'Wrap.Wrap'},
  YGWrapWrapReverse:{value: 'Wrap.WrapReverse'},

  YGDisplayFlex:{value: 'Display.Flex'},
  YGDisplayNone:{value: 'Display.None'},

  YGNodeCalculateLayout:{value:function(node, dir, experiments) {
    this.push(node + '.calculateLayout(undefined, undefined, ' + dir + ');');
  }},

  YGNodeInsertChild:{value:function(parentName, nodeName, index) {
    this.push(parentName + '.insertChild(' + nodeName + ', ' + index + ');');
  }},

  YGNodeLayoutGetLeft:{value:function(nodeName) {
    return nodeName + '.getComputedLeft()';
  }},

  YGNodeLayoutGetTop:{value:function(nodeName) {
    return nodeName + '.getComputedTop()';
  }},

  YGNodeLayoutGetWidth:{value:function(nodeName) {
    return nodeName + '.getComputedWidth()';
  }},

  YGNodeLayoutGetHeight:{value:function(nodeName) {
    return nodeName + '.getComputedHeight()';
  }},

  YGNodeStyleSetAlignContent:{value:function(nodeName, value) {
    this.push(nodeName + '.setAlignContent(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetAlignItems:{value:function(nodeName, value) {
    this.push(nodeName + '.setAlignItems(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetAlignSelf:{value:function(nodeName, value) {
    this.push(nodeName + '.setAlignSelf(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetBorder:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setBorder(' + toValueJavascript(edge) + ', ' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.setDirection(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetDisplay:{value:function(nodeName, value) {
    this.push(nodeName + '.setDisplay(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexBasis(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexDirection(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexGrow(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexShrink(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexWrap(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setHeight(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push(nodeName + '.setJustifyContent(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setMargin(' + toValueJavascript(edge) + ', ' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setMaxHeight(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setMaxWidth(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setMinHeight(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setMinWidth(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push(nodeName + '.setOverflow(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setPadding(' + toValueJavascript(edge) + ', ' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setPosition(' + toValueJavascript(edge) + ', ' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push(nodeName + '.setPositionType(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setWidth(' + toValueJavascript(value) + ');');
  }},

  YGNodeStyleSetGap:{value:function(nodeName, gap, value) {
    this.push(nodeName + '.setGap('+ toValueJavascript(gap) + ', ' + toValueJavascript(value) + ');');
  }},
});
