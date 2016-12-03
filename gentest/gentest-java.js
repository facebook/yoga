/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var JavaEmitter = function() {
  Emitter.call(this, 'java', '  ');
};

function toJavaUpper(symbol) {
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

JavaEmitter.prototype = Object.create(Emitter.prototype, {
  constructor:{value:JavaEmitter},

  emitPrologue:{value:function() {
    this.push([
      'package com.facebook.csslayout;',
      '',
      'import org.junit.Test;',
      '',
      'import static org.junit.Assert.assertEquals;',
      '',
      'public class YogaTest {',
    ]);
    this.pushIndent();
  }},

  emitTestPrologue:{value:function(name, experiments) {
    this.push('@Test');
    this.push('public void test_' + name + '() {');
    this.pushIndent();

    if (experiments.length > 0) {
      for (var i in experiments) {
        this.push('YogaNode.setExperimentalFeatureEnabled(YogaExperimentalFeature.' + toJavaUpper(experiments[i]) +', true);');
      }
      this.push('');
    }
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('final YogaNode ' + nodeName + ' = new YogaNode();');
  }},

  emitTestEpilogue:{value:function(experiments) {
    if (experiments.length > 0) {
      this.push('');
      for (var i in experiments) {
        this.push('YogaNode.setExperimentalFeatureEnabled(YogaExperimentalFeature.' + toJavaUpper(experiments[i]) +', false);');
      }
    }

    this.popIndent();
    this.push([
      '}',
      '',
    ]);
  }},

  emitEpilogue:{value:function(lines) {
    this.popIndent();
    this.push([
      '}',
      '',
    ]);
  }},

  AssertEQ:{value:function(v0, v1) {
    this.push('assertEquals(' + v0 + 'f, ' + v1 + ', 0.0f);');
  }},

  YGAlignAuto:{value:'YogaAlign.AUTO'},
  YGAlignCenter:{value:'YogaAlign.CENTER'},
  YGAlignFlexEnd:{value:'YogaAlign.FLEX_END'},
  YGAlignFlexStart:{value:'YogaAlign.FLEX_START'},
  YGAlignStretch:{value:'YogaAlign.STRETCH'},

  YGDirectionInherit:{value:'YogaDirection.INHERIT'},
  YGDirectionLTR:{value:'YogaDirection.LTR'},
  YGDirectionRTL:{value:'YogaDirection.RTL'},

  YGEdgeBottom:{value:'YogaEdge.BOTTOM'},
  YGEdgeEnd:{value:'YogaEdge.END'},
  YGEdgeLeft:{value:'YogaEdge.LEFT'},
  YGEdgeRight:{value:'YogaEdge.RIGHT'},
  YGEdgeStart:{value:'YogaEdge.START'},
  YGEdgeTop:{value:'YogaEdge.TOP'},

  YGFlexDirectionColumn:{value:'YogaFlexDirection.COLUMN'},
  YGFlexDirectionColumnReverse:{value:'YogaFlexDirection.COLUMN_REVERSE'},
  YGFlexDirectionRow:{value:'YogaFlexDirection.ROW'},
  YGFlexDirectionRowReverse:{value:'YogaFlexDirection.ROW_REVERSE'},

  YGJustifyCenter:{value:'YogaJustify.CENTER'},
  YGJustifyFlexEnd:{value:'YogaJustify.FLEX_END'},
  YGJustifyFlexStart:{value:'YogaJustify.FLEX_START'},
  YGJustifySpaceAround:{value:'YogaJustify.SPACE_AROUND'},
  YGJustifySpaceBetween:{value:'YogaJustify.SPACE_BETWEEN'},

  YGOverflowHidden:{value:'YogaOverflow.HIDDEN'},
  YGOverflowVisible:{value:'YogaOverflow.VISIBLE'},

  YGPositionTypeAbsolute:{value:'YogaPositionType.ABSOLUTE'},
  YGPositionTypeRelative:{value:'YogaPositionType.RELATIVE'},

  YGUndefined:{value:'YogaConstants.UNDEFINED'},

  YGWrapNoWrap:{value:'YogaWrap.NO_WRAP'},
  YGWrapWrap:{value:'YogaWrap.WRAP'},

  YGNodeCalculateLayout:{value:function(node, dir) {
    this.push(node + '.setDirection(' + dir + ');');
    this.push(node + '.calculateLayout();');
  }},

  YGNodeInsertChild:{value:function(parentName, nodeName, index) {
    this.push(parentName + '.addChildAt(' + nodeName + ', ' + index + ');');
  }},

  YGNodeLayoutGetLeft:{value:function(nodeName) {
    return nodeName + '.getLayoutX()';
  }},

  YGNodeLayoutGetTop:{value:function(nodeName) {
    return nodeName + '.getLayoutY()';
  }},

  YGNodeLayoutGetWidth:{value:function(nodeName) {
    return nodeName + '.getLayoutWidth()';
  }},

  YGNodeLayoutGetHeight:{value:function(nodeName) {
    return nodeName + '.getLayoutHeight()';
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
    this.push(nodeName + '.setBorder(' + edge + ', ' + value + 'f);');
  }},

  YGNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.setDirection(' + value + ');');
  }},

  YGNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexBasis(' + value + 'f);');
  }},

  YGNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexDirection(' + value + ');');
  }},

  YGNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexGrow(' + value + 'f);');
  }},

  YGNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexShrink(' + value + 'f);');
  }},

  YGNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push(nodeName + '.setWrap(' + value + ');');
  }},

  YGNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setHeight(' + value + 'f);');
  }},

  YGNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push(nodeName + '.setJustifyContent(' + value + ');');
  }},

  YGNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setMargin(' + edge + ', ' + value + 'f);');
  }},

  YGNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setMaxHeight(' + value + 'f);');
  }},

  YGNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setMaxWidth(' + value + 'f);');
  }},

  YGNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setMinHeight(' + value + 'f);');
  }},

  YGNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setMinWidth(' + value + 'f);');
  }},

  YGNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push(nodeName + '.setOverflow(' + value + ');');
  }},

  YGNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setPadding(' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setPosition(' + edge + ', ' + value + 'f);');
  }},

  YGNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push(nodeName + '.setPositionType(' + value + ');');
  }},

  YGNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setWidth(' + value + 'f);');
  }},
});
