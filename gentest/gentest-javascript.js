/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var JavascriptEmitter = function() {
  Emitter.call(this, 'js', '  ');
};

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

    if (experiments.length > 0) {
      for (var i in experiments) {
        this.push('Yoga.setExperimentalFeatureEnabled(Yoga.FEATURE_' + toJavascriptUpper(experiments[i]) + ', true);');
      }
      this.push('');
    }
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('var ' + nodeName + ' = Yoga.Node.create();');
  }},

  emitTestEpilogue:{value:function(experiments) {
    this.push('');
    this.push('if (typeof root !== "undefined")');
    this.pushIndent();
    this.push('root.freeRecursive();');
    this.popIndent();

    this.push('');
    this.push('(typeof gc !== "undefined") && gc();');
    this.AssertEQ('0', 'Yoga.getInstanceCount()');

    if (experiments.length > 0) {
      this.push('');
      for (var i in experiments) {
        this.push('Yoga.setExperimentalFeatureEnabled(Yoga.FEATURE_' + toJavascriptUpper(experiments[i]) + ', false);');
      }
    }

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

  YGOverflowHidden:{value:'Yoga.OVERFLOW_HIDDEN'},
  YGOverflowVisible:{value:'Yoga.OVERFLOW_VISIBLE'},

  YGPositionTypeAbsolute:{value:'Yoga.POSITION_TYPE_ABSOLUTE'},
  YGPositionTypeRelative:{value:'Yoga.POSITION_TYPE_RELATIVE'},

  YGWrapNoWrap:{value:'Yoga.WRAP_NO_WRAP'},
  YGWrapWrap:{value:'Yoga.WRAP_WRAP'},

  YGUndefined:{value:'Yoga.UNDEFINED'},

  YGNodeCalculateLayout:{value:function(node, dir) {
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
    this.push(nodeName + '.setAlignContent(' + value + ');');
  }},

  YGNodeStyleSetAlignItems:{value:function(nodeName, value) {
    this.push(nodeName + '.setAlignItems(' + value + ');');
  }},

  YGNodeStyleSetAlignSelf:{value:function(nodeName, value) {
    this.push(nodeName + '.setAlignSelf(' + value + ');');
  }},

  YGNodeStyleSetBorder:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setBorder(' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.setDirection(' + value + ');');
  }},

  YGNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexBasis(' + value + ');');
  }},

  YGNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexDirection(' + value + ');');
  }},

  YGNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexGrow(' + value + ');');
  }},

  YGNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexShrink(' + value + ');');
  }},

  YGNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexWrap(' + value + ');');
  }},

  YGNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setHeight(' + value + ');');
  }},

  YGNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push(nodeName + '.setJustifyContent(' + value + ');');
  }},

  YGNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setMargin(' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setMaxHeight(' + value + ');');
  }},

  YGNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setMaxWidth(' + value + ');');
  }},

  YGNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setMinHeight(' + value + ');');
  }},

  YGNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setMinWidth(' + value + ');');
  }},

  YGNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push(nodeName + '.setOverflow(' + value + ');');
  }},

  YGNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setPadding(' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setPosition(' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push(nodeName + '.setPositionType(' + value + ');');
  }},

  YGNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setWidth(' + value + ');');
  }},
});
