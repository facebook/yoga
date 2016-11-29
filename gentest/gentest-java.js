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
      'public class CSSNodeLayoutTest {',
    ]);
    this.pushIndent();
  }},

  emitTestPrologue:{value:function(name, experiments) {
    this.push('@Test');
    this.push('public void test_' + name + '() {');
    this.pushIndent();

    if (experiments.length > 0) {
      for (var i in experiments) {
        this.push('CSSNode.setExperimentalFeatureEnabled(CSSExperimentalFeature.' + toJavaUpper(experiments[i]) +', true);');
      }
      this.push('');
    }
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('final CSSNode ' + nodeName + ' = new CSSNode();');
  }},

  emitTestEpilogue:{value:function(experiments) {
    if (experiments.length > 0) {
      this.push('');
      for (var i in experiments) {
        this.push('CSSNode.setExperimentalFeatureEnabled(CSSExperimentalFeature.' + toJavaUpper(experiments[i]) +', false);');
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

  CSSAlignAuto:{value:'CSSAlign.AUTO'},
  CSSAlignCenter:{value:'CSSAlign.CENTER'},
  CSSAlignFlexEnd:{value:'CSSAlign.FLEX_END'},
  CSSAlignFlexStart:{value:'CSSAlign.FLEX_START'},
  CSSAlignStretch:{value:'CSSAlign.STRETCH'},

  CSSDirectionInherit:{value:'CSSDirection.INHERIT'},
  CSSDirectionLTR:{value:'CSSDirection.LTR'},
  CSSDirectionRTL:{value:'CSSDirection.RTL'},

  CSSEdgeBottom:{value:'CSSEdge.BOTTOM'},
  CSSEdgeEnd:{value:'CSSEdge.END'},
  CSSEdgeLeft:{value:'CSSEdge.LEFT'},
  CSSEdgeRight:{value:'CSSEdge.RIGHT'},
  CSSEdgeStart:{value:'CSSEdge.START'},
  CSSEdgeTop:{value:'CSSEdge.TOP'},

  CSSFlexDirectionColumn:{value:'CSSFlexDirection.COLUMN'},
  CSSFlexDirectionColumnReverse:{value:'CSSFlexDirection.COLUMN_REVERSE'},
  CSSFlexDirectionRow:{value:'CSSFlexDirection.ROW'},
  CSSFlexDirectionRowReverse:{value:'CSSFlexDirection.ROW_REVERSE'},

  CSSJustifyCenter:{value:'CSSJustify.CENTER'},
  CSSJustifyFlexEnd:{value:'CSSJustify.FLEX_END'},
  CSSJustifyFlexStart:{value:'CSSJustify.FLEX_START'},
  CSSJustifySpaceAround:{value:'CSSJustify.SPACE_AROUND'},
  CSSJustifySpaceBetween:{value:'CSSJustify.SPACE_BETWEEN'},

  CSSOverflowHidden:{value:'CSSOverflow.HIDDEN'},
  CSSOverflowVisible:{value:'CSSOverflow.VISIBLE'},

  CSSPositionTypeAbsolute:{value:'CSSPositionType.ABSOLUTE'},
  CSSPositionTypeRelative:{value:'CSSPositionType.RELATIVE'},

  CSSUndefined:{value:'CSSConstants.UNDEFINED'},

  CSSWrapNoWrap:{value:'CSSWrap.NO_WRAP'},
  CSSWrapWrap:{value:'CSSWrap.WRAP'},

  CSSNodeCalculateLayout:{value:function(node, dir) {
    this.push(node + '.setDirection(' + dir + ');');
    this.push(node + '.calculateLayout();');
  }},

  CSSNodeInsertChild:{value:function(parentName, nodeName, index) {
    this.push(parentName + '.addChildAt(' + nodeName + ', ' + index + ');');
  }},

  CSSNodeLayoutGetLeft:{value:function(nodeName) {
    return nodeName + '.getLayoutX()';
  }},

  CSSNodeLayoutGetTop:{value:function(nodeName) {
    return nodeName + '.getLayoutY()';
  }},

  CSSNodeLayoutGetWidth:{value:function(nodeName) {
    return nodeName + '.getLayoutWidth()';
  }},

  CSSNodeLayoutGetHeight:{value:function(nodeName) {
    return nodeName + '.getLayoutHeight()';
  }},

  CSSNodeStyleSetAlignContent:{value:function(nodeName, value) {
    this.push(nodeName + '.setAlignContent(' + value + ');');
  }},

  CSSNodeStyleSetAlignItems:{value:function(nodeName, value) {
    this.push(nodeName + '.setAlignItems(' + value + ');');
  }},

  CSSNodeStyleSetAlignSelf:{value:function(nodeName, value) {
    this.push(nodeName + '.setAlignSelf(' + value + ');');
  }},

  CSSNodeStyleSetBorder:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setBorder(' + edge + ', ' + value + 'f);');
  }},

  CSSNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.setDirection(' + value + ');');
  }},

  CSSNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexBasis(' + value + 'f);');
  }},

  CSSNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexDirection(' + value + ');');
  }},

  CSSNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexGrow(' + value + 'f);');
  }},

  CSSNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexShrink(' + value + 'f);');
  }},

  CSSNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push(nodeName + '.setWrap(' + value + ');');
  }},

  CSSNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setHeight(' + value + 'f);');
  }},

  CSSNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push(nodeName + '.setJustifyContent(' + value + ');');
  }},

  CSSNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setMargin(' + edge + ', ' + value + 'f);');
  }},

  CSSNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setMaxHeight(' + value + 'f);');
  }},

  CSSNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setMaxWidth(' + value + 'f);');
  }},

  CSSNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setMinHeight(' + value + 'f);');
  }},

  CSSNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setMinWidth(' + value + 'f);');
  }},

  CSSNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push(nodeName + '.setOverflow(' + value + ');');
  }},

  CSSNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setPadding(' + edge + ', ' + value + ');');
  }},

  CSSNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setPosition(' + edge + ', ' + value + 'f);');
  }},

  CSSNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push(nodeName + '.setPositionType(' + value + ');');
  }},

  CSSNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setWidth(' + value + 'f);');
  }},
});
