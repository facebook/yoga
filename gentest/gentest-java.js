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

  emitTestPrologue:{value:function(name) {
    this.push('@Test');
    this.push('public void test_' + name + '() {');
    this.pushIndent();
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('final CSSNode ' + nodeName + ' = new CSSNode();');
  }},

  emitTestEpilogue:{value:function() {
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
    this.push('assertEquals(' + v0 + ', ' + v1 + ', 0.0f);');
  }},

  CSSAlignAuto:{value:'CSSAlign.AUTO'},
  CSSAlignCenter:{value:'CSSAlign.CENTER'},
  CSSAlignFlexEnd:{value:'CSSAlign.FLEX_END'},
  CSSAlignFlexStart:{value:'CSSAlign.FLEX_START'},
  CSSAlignStretch:{value:'CSSAlign.STRETCH'},

  CSSDirectionInherit:{value:'CSSDirection.INHERIT'},
  CSSDirectionLTR:{value:'CSSDirection.LTR'},
  CSSDirectionRTL:{value:'CSSDirection.RTL'},

  CSSEdgeBottom:{value:'Spacing.BOTTOM'},
  CSSEdgeEnd:{value:'Spacing.END'},
  CSSEdgeLeft:{value:'Spacing.LEFT'},
  CSSEdgeRight:{value:'Spacing.RIGHT'},
  CSSEdgeStart:{value:'Spacing.START'},
  CSSEdgeTop:{value:'Spacing.TOP'},

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

  CSSWrapTypeNoWrap:{value:'CSSWrap.NO_WRAP'},
  CSSWrapTypeWrap:{value:'CSSWrap.WRAP'},

  CSSNodeCalculateLayout:{value:function(node, dir) {
    this.push(node + '.setDirection(' + dir + ');');
    this.push(node + '.calculateLayout(null);');
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
    this.push(nodeName + '.setBorder(' + edge + ', ' + value + ');');
  }},

  CSSNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.setDirection(' + value + ');');
  }},

  CSSNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexBasis(' + value + ');');
  }},

  CSSNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexDirection(' + value + ');');
  }},

  CSSNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexGrow(' + value + ');');
  }},

  CSSNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexShrink(' + value + ');');
  }},

  CSSNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push(nodeName + '.setWrap(' + value + ');');
  }},

  CSSNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setStyleHeight(' + value + ');');
  }},

  CSSNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push(nodeName + '.setJustifyContent(' + value + ');');
  }},

  CSSNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setMargin(' + edge + ', ' + value + ');');
  }},

  CSSNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setStyleMaxHeight(' + value + ');');
  }},

  CSSNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setStyleMaxWidth(' + value + ');');
  }},

  CSSNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setStyleMinHeight(' + value + ');');
  }},

  CSSNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setStyleMinWidth(' + value + ');');
  }},

  CSSNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push(nodeName + '.setOverflow(' + value + ');');
  }},

  CSSNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setPadding(' + edge + ', ' + value + ');');
  }},

  CSSNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setPosition(' + edge + ', ' + value + ');');
  }},

  CSSNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push(nodeName + '.setPositionType(' + value + ');');
  }},

  CSSNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setStyleWidth(' + value + ');');
  }},
});
