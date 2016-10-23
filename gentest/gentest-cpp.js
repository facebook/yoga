/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var CPPEmitter = function() {
  Emitter.call(this, 'cpp', '  ');
};

CPPEmitter.prototype = Object.create(Emitter.prototype, {
  constructor:{value:CPPEmitter},

  emitPrologue:{value:function() {
    this.push([
      '#include <CSSLayout/CSSLayout.h>',
      '#include <gtest/gtest.h>',
      '',
    ]);
  }},

  emitTestPrologue:{value:function(name) {
    this.push('TEST(CSSLayoutTest, ' + name + ') {');
    this.pushIndent();
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('const CSSNodeRef ' + nodeName + ' = CSSNodeNew();');
  }},

  emitTestEpilogue:{value:function() {
    this.push([
      '',
      'CSSNodeFreeRecursive(root);',
    ]);
    this.popIndent();
    this.push([
      '}',
      '',
    ]);
  }},

  emitEpilogue:{value:function() {
  }},

  AssertEQ:{value:function(v0, v1) {
    this.push('ASSERT_EQ(' + v0 + ', ' + v1 + ');');
  }},

  CSSAlignAuto:{value:'CSSAlignAuto'},
  CSSAlignCenter:{value:'CSSAlignCenter'},
  CSSAlignFlexEnd:{value:'CSSAlignFlexEnd'},
  CSSAlignFlexStart:{value:'CSSAlignFlexStart'},
  CSSAlignStretch:{value:'CSSAlignStretch'},

  CSSDirectionInherit:{value:'CSSDirectionInherit'},
  CSSDirectionLTR:{value:'CSSDirectionLTR'},
  CSSDirectionRTL:{value:'CSSDirectionRTL'},

  CSSEdgeBottom:{value:'CSSEdgeBottom'},
  CSSEdgeEnd:{value:'CSSEdgeEnd'},
  CSSEdgeLeft:{value:'CSSEdgeLeft'},
  CSSEdgeRight:{value:'CSSEdgeRight'},
  CSSEdgeStart:{value:'CSSEdgeStart'},
  CSSEdgeTop:{value:'CSSEdgeTop'},

  CSSFlexDirectionColumn:{value:'CSSFlexDirectionColumn'},
  CSSFlexDirectionColumnReverse:{value:'CSSFlexDirectionColumnReverse'},
  CSSFlexDirectionRow:{value:'CSSFlexDirectionRow'},
  CSSFlexDirectionRowReverse:{value:'CSSFlexDirectionRowReverse'},

  CSSJustifyCenter:{value:'CSSJustifyCenter'},
  CSSJustifyFlexEnd:{value:'CSSJustifyFlexEnd'},
  CSSJustifyFlexStart:{value:'CSSJustifyFlexStart'},
  CSSJustifySpaceAround:{value:'CSSJustifySpaceAround'},
  CSSJustifySpaceBetween:{value:'CSSJustifySpaceBetween'},

  CSSOverflowHidden:{value:'CSSOverflowHidden'},
  CSSOverflowVisible:{value:'CSSOverflowVisible'},

  CSSPositionTypeAbsolute:{value:'CSSPositionTypeAbsolute'},
  CSSPositionTypeRelative:{value:'CSSPositionTypeRelative'},

  CSSWrapTypeNoWrap:{value:'CSSWrapTypeNoWrap'},
  CSSWrapTypeWrap:{value:'CSSWrapTypeWrap'},

  CSSUndefined:{value:'CSSUndefined'},

  CSSNodeCalculateLayout:{value:function(node, dir) {
    this.push('CSSNodeCalculateLayout(' + node + ', CSSUndefined, CSSUndefined, ' + dir + ');');
  }},

  CSSNodeInsertChild:{value:function(parentName, nodeName, index) {
    this.push('CSSNodeInsertChild(' + parentName + ', ' + nodeName + ', ' + index + ');');
  }},

  CSSNodeLayoutGetLeft:{value:function(nodeName) {
    return 'CSSNodeLayoutGetLeft(' + nodeName + ')';
  }},

  CSSNodeLayoutGetTop:{value:function(nodeName) {
    return 'CSSNodeLayoutGetTop(' + nodeName + ')';
  }},

  CSSNodeLayoutGetWidth:{value:function(nodeName) {
    return 'CSSNodeLayoutGetWidth(' + nodeName + ')';
  }},

  CSSNodeLayoutGetHeight:{value:function(nodeName) {
    return 'CSSNodeLayoutGetHeight(' + nodeName + ')';
  }},

  CSSNodeStyleSetAlignContent:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetAlignContent(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetAlignItems:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetAlignItems(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetAlignSelf:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetAlignSelf(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetBorder:{value:function(nodeName, edge, value) {
    this.push('CSSNodeStyleSetBorder(' + nodeName + ', ' + edge + ', ' + value + ');');
  }},

  CSSNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetDirection(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetFlexBasis(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetFlexDirection(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetFlexGrow(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetFlexShrink(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetFlexWrap(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetHeight(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetJustifyContent(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push('CSSNodeStyleSetMargin(' + nodeName + ', ' + edge + ', ' + value + ');');
  }},

  CSSNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetMaxHeight(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetMaxWidth(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetMinHeight(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetMinWidth(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetOverflow(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push('CSSNodeStyleSetPadding(' + nodeName + ', ' + edge + ', ' + value + ');');
  }},

  CSSNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push('CSSNodeStyleSetPosition(' + nodeName + ', ' + edge + ', ' + value + ');');
  }},

  CSSNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetPositionType(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push('CSSNodeStyleSetWidth(' + nodeName + ', ' + value + ');');
  }},
});
