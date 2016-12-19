/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

function toValueCpp(value) {
  var n = value.toString().replace('px','').replace('%','');
  return n + (Number(n) == n && n % 1 !== 0 ? 'f' : '');
}
 
function toValueCppCpp(value) {
  var methodName = '';
  if(value.indexOf('px') >= 0){
    methodName = 'YGPx';
  }else if (value.indexOf('%') >= 0){
    methodName = 'YGPercent';
  }
  return methodName + '(' + toValueCpp(value) + ')';
}

var CPPEmitter = function() {
  Emitter.call(this, 'cpp', '  ');
};

CPPEmitter.prototype = Object.create(Emitter.prototype, {
  constructor:{value:CPPEmitter},

  emitPrologue:{value:function() {
    this.push([
      '#include <yoga/Yoga.h>',
      '#include <gtest/gtest.h>',
      '',
    ]);
  }},

  emitTestPrologue:{value:function(name, experiments) {
    this.push('TEST(YogaTest, ' + name + ') {');
    this.pushIndent();

    if (experiments.length > 0) {
      for (var i in experiments) {
        this.push('YGSetExperimentalFeatureEnabled(YGExperimentalFeature' + experiments[i] +', true);');
      }
      this.push('');
    }
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('const YGNodeRef ' + nodeName + ' = YGNodeNew();');
  }},

  emitTestEpilogue:{value:function(experiments) {
    this.push([
      '',
      'YGNodeFreeRecursive(root);',
    ]);

    if (experiments.length > 0) {
      this.push('');
      for (var i in experiments) {
        this.push('YGSetExperimentalFeatureEnabled(YGExperimentalFeature' + experiments[i] +', false);');
      }
    }

    this.popIndent();
    this.push([
      '}',
      '',
    ]);
  }},

  emitEpilogue:{value:function() {
  }},

  AssertEQ:{value:function(v0, v1) {
    this.push('ASSERT_FLOAT_EQ(' + toValueCpp(v0) + ', ' + v1 + ');');
  }},

  YGAlignAuto:{value:'YGAlignAuto'},
  YGAlignCenter:{value:'YGAlignCenter'},
  YGAlignFlexEnd:{value:'YGAlignFlexEnd'},
  YGAlignFlexStart:{value:'YGAlignFlexStart'},
  YGAlignStretch:{value:'YGAlignStretch'},

  YGDirectionInherit:{value:'YGDirectionInherit'},
  YGDirectionLTR:{value:'YGDirectionLTR'},
  YGDirectionRTL:{value:'YGDirectionRTL'},

  YGEdgeBottom:{value:'YGEdgeBottom'},
  YGEdgeEnd:{value:'YGEdgeEnd'},
  YGEdgeLeft:{value:'YGEdgeLeft'},
  YGEdgeRight:{value:'YGEdgeRight'},
  YGEdgeStart:{value:'YGEdgeStart'},
  YGEdgeTop:{value:'YGEdgeTop'},

  YGFlexDirectionColumn:{value:'YGFlexDirectionColumn'},
  YGFlexDirectionColumnReverse:{value:'YGFlexDirectionColumnReverse'},
  YGFlexDirectionRow:{value:'YGFlexDirectionRow'},
  YGFlexDirectionRowReverse:{value:'YGFlexDirectionRowReverse'},

  YGJustifyCenter:{value:'YGJustifyCenter'},
  YGJustifyFlexEnd:{value:'YGJustifyFlexEnd'},
  YGJustifyFlexStart:{value:'YGJustifyFlexStart'},
  YGJustifySpaceAround:{value:'YGJustifySpaceAround'},
  YGJustifySpaceBetween:{value:'YGJustifySpaceBetween'},

  YGOverflowHidden:{value:'YGOverflowHidden'},
  YGOverflowVisible:{value:'YGOverflowVisible'},

  YGPositionTypeAbsolute:{value:'YGPositionTypeAbsolute'},
  YGPositionTypeRelative:{value:'YGPositionTypeRelative'},

  YGWrapNoWrap:{value:'YGWrapNoWrap'},
  YGWrapWrap:{value:'YGWrapWrap'},

  YGUndefined:{value:'YGUndefined'},

  YGNodeCalculateLayout:{value:function(node, dir) {
    this.push('YGNodeCalculateLayout(' + node + ', YGUndefined, YGUndefined, ' + dir + ');');
  }},

  YGNodeInsertChild:{value:function(parentName, nodeName, index) {
    this.push('YGNodeInsertChild(' + parentName + ', ' + nodeName + ', ' + index + ');');
  }},

  YGNodeLayoutGetLeft:{value:function(nodeName) {
    return 'YGNodeLayoutGetLeft(' + nodeName + ')';
  }},

  YGNodeLayoutGetTop:{value:function(nodeName) {
    return 'YGNodeLayoutGetTop(' + nodeName + ')';
  }},

  YGNodeLayoutGetWidth:{value:function(nodeName) {
    return 'YGNodeLayoutGetWidth(' + nodeName + ')';
  }},

  YGNodeLayoutGetHeight:{value:function(nodeName) {
    return 'YGNodeLayoutGetHeight(' + nodeName + ')';
  }},

  YGNodeStyleSetAlignContent:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetAlignContent(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetAlignItems:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetAlignItems(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetAlignSelf:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetAlignSelf(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetBorder:{value:function(nodeName, edge, value) {
    this.push('YGNodeStyleSetBorder(' + nodeName + ', ' + edge + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetDirection(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetFlexBasis(' + nodeName + ', ' + toValueCppCpp(value) + ');');
  }},

  YGNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetFlexDirection(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetFlexGrow(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetFlexShrink(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetFlexWrap(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetHeight(' + nodeName + ', ' + toValueCppCpp(value) + ');');
  }},

  YGNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetJustifyContent(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push('YGNodeStyleSetMargin(' + nodeName + ', ' + edge + ', ' + toValueCppCpp(value) + ');');
  }},

  YGNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetMaxHeight(' + nodeName + ', ' + toValueCppCpp(value) + ');');
  }},

  YGNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetMaxWidth(' + nodeName + ', ' + toValueCppCpp(value) + ');');
  }},

  YGNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetMinHeight(' + nodeName + ', ' + toValueCppCpp(value) + ');');
  }},

  YGNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetMinWidth(' + nodeName + ', ' + toValueCppCpp(value) + ');');
  }},

  YGNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetOverflow(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push('YGNodeStyleSetPadding(' + nodeName + ', ' + edge + ', ' + toValueCppCpp(value) + ');');
  }},

  YGNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push('YGNodeStyleSetPosition(' + nodeName + ', ' + edge + ', ' + toValueCppCpp(value) + ');');
  }},

  YGNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetPositionType(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetWidth(' + nodeName + ', ' + toValueCppCpp(value) + ');');
  }},
});
