/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

var JavascriptEmitter = function() {
  Emitter.call(this, 'js', '  ');
};

function toValueJavascript(value) {
  if (value.match(/^[0-9.e+-]+px$/i)) return parseFloat(value);
  if (value.match(/^[0-9.e+-]+%/i)) return JSON.stringify(value);
  if (value == 'Yoga.AUTO') return '"auto"';
  return value;
}

function toJavascriptUpper(symbol) {
  var out = '';
  for (var i = 0; i < symbol.length; i++) {
    var c = symbol[i];
    if (c == c.toUpperCase() && i != 0 && symbol[i - 1] != symbol[i - 1].toUpperCase()) {
      out += '_';
    }
    out += c.toUpperCase();
  }
  return out;
}

JavascriptEmitter.prototype = Object.create(Emitter.prototype, {
  constructor:{value:JavascriptEmitter},

  emitPrologue:{value:function() {
    this.push([
      'var Yoga = Yoga || require("../../sources/entry-" + process.env.TEST_ENTRY);',
      ''
    ]);
  }},

  emitTestPrologue:{value:function(name, experiments) {
    this.push('it(' + JSON.stringify(name) + ', function () {');
    this.pushIndent();
    this.push('var config = Yoga.Config.create();');
    this.push('');

    if (experiments.length > 0) {
      for (var i in experiments) {
        this.push('config.setExperimentalFeatureEnabled(Yoga.EXPERIMENTAL_FEATURE_' + toJavascriptUpper(experiments[i]) + ', true);');
      }
      this.push('');
    }

    this.push('try {');
    this.pushIndent();
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('var ' + nodeName + ' = Yoga.Node.create(config);');
  }},

  emitTestEpilogue:{value:function(experiments) {
    this.popIndent();
    this.push('} finally {');
    this.pushIndent();

    this.push('if (typeof root !== "undefined") {');
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
    this.push('console.assert(' + v0 + ' === ' + v1 + ', "' + v0 + ' === ' + v1 + ' (" + ' + v1 + ' + ")");');
  }},

  YGAlignAuto:{value:'Yoga.ALIGN_AUTO'},
  YGAlignCenter:{value:'Yoga.ALIGN_CENTER'},
  YGAlignFlexEnd:{value:'Yoga.ALIGN_FLEX_END'},
  YGAlignFlexStart:{value:'Yoga.ALIGN_FLEX_START'},
  YGAlignStretch:{value:'Yoga.ALIGN_STRETCH'},
  YGAlignSpaceBetween:{value:'Yoga.ALIGN_SPACE_BETWEEN'},
  YGAlignSpaceAround:{value:'Yoga.ALIGN_SPACE_AROUND'},
  YGAlignBaseline:{value:'Yoga.ALIGN_BASELINE'},

  YGDirectionInherit:{value:'Yoga.DIRECTION_INHERIT'},
  YGDirectionLTR:{value:'Yoga.DIRECTION_LTR'},
  YGDirectionRTL:{value:'Yoga.DIRECTION_RTL'},

  YGEdgeBottom:{value:'Yoga.EDGE_BOTTOM'},
  YGEdgeEnd:{value:'Yoga.EDGE_END'},
  YGEdgeLeft:{value:'Yoga.EDGE_LEFT'},
  YGEdgeRight:{value:'Yoga.EDGE_RIGHT'},
  YGEdgeStart:{value:'Yoga.EDGE_START'},
  YGEdgeTop:{value:'Yoga.EDGE_TOP'},

  YGFlexDirectionColumn:{value:'Yoga.FLEX_DIRECTION_COLUMN'},
  YGFlexDirectionColumnReverse:{value:'Yoga.FLEX_DIRECTION_COLUMN_REVERSE'},
  YGFlexDirectionRow:{value:'Yoga.FLEX_DIRECTION_ROW'},
  YGFlexDirectionRowReverse:{value:'Yoga.FLEX_DIRECTION_ROW_REVERSE'},

  YGJustifyCenter:{value:'Yoga.JUSTIFY_CENTER'},
  YGJustifyFlexEnd:{value:'Yoga.JUSTIFY_FLEX_END'},
  YGJustifyFlexStart:{value:'Yoga.JUSTIFY_FLEX_START'},
  YGJustifySpaceAround:{value:'Yoga.JUSTIFY_SPACE_AROUND'},
  YGJustifySpaceBetween:{value:'Yoga.JUSTIFY_SPACE_BETWEEN'},
  YGJustifySpaceEvenly:{value:'Yoga.JUSTIFY_SPACE_EVENLY'},

  YGOverflowHidden:{value:'Yoga.OVERFLOW_HIDDEN'},
  YGOverflowVisible:{value:'Yoga.OVERFLOW_VISIBLE'},

  YGPositionTypeAbsolute:{value:'Yoga.POSITION_TYPE_ABSOLUTE'},
  YGPositionTypeRelative:{value:'Yoga.POSITION_TYPE_RELATIVE'},

  YGAuto:{value:'Yoga.AUTO'},

  YGWrapNoWrap:{value:'Yoga.WRAP_NO_WRAP'},
  YGWrapWrap:{value:'Yoga.WRAP_WRAP'},
  YGWrapWrapReverse:{value: 'Yoga.WRAP_WRAP_REVERSE'},

  YGUndefined:{value:'Yoga.UNDEFINED'},

  YGDisplayFlex:{value:'Yoga.DISPLAY_FLEX'},
  YGDisplayNone:{value:'Yoga.DISPLAY_NONE'},

  YGNodeCalculateLayout:{value:function(node, dir, experiments) {
    this.push(node + '.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, ' + dir + ');');
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
});
