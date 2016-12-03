/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

function toFloatString(n) {
  return n + (Number(n) == n && n % 1 !== 0 ? 'f' : '');
}

var CPPEmitter = function() {
  Emitter.call(this, 'cpp', '  ');
};

CPPEmitter.prototype = Object.create(Emitter.prototype, {
  constructor:{value:CPPEmitter},

  emitPrologue:{value:function() {
    this.push([
      '#include <CSSLayout/Yoga.h>',
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
    this.push('ASSERT_FLOAT_EQ(' + toFloatString(v0) + ', ' + v1 + ');');
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

  CSSNodeCalculateLayout:{value:function(node, dir) {
    this.push('YGNodeCalculateLayout(' + node + ', YGUndefined, YGUndefined, ' + dir + ');');
  }},

  CSSNodeInsertChild:{value:function(parentName, nodeName, index) {
    this.push('YGNodeInsertChild(' + parentName + ', ' + nodeName + ', ' + index + ');');
  }},

  CSSNodeLayoutGetLeft:{value:function(nodeName) {
    return 'YGNodeLayoutGetLeft(' + nodeName + ')';
  }},

  CSSNodeLayoutGetTop:{value:function(nodeName) {
    return 'YGNodeLayoutGetTop(' + nodeName + ')';
  }},

  CSSNodeLayoutGetWidth:{value:function(nodeName) {
    return 'YGNodeLayoutGetWidth(' + nodeName + ')';
  }},

  CSSNodeLayoutGetHeight:{value:function(nodeName) {
    return 'YGNodeLayoutGetHeight(' + nodeName + ')';
  }},

  CSSNodeStyleSetAlignContent:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetAlignContent(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetAlignItems:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetAlignItems(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetAlignSelf:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetAlignSelf(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetBorder:{value:function(nodeName, edge, value) {
    this.push('YGNodeStyleSetBorder(' + nodeName + ', ' + edge + ', ' + toFloatString(value) + ');');
  }},

  CSSNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetDirection(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetFlexBasis(' + nodeName + ', ' + toFloatString(value) + ');');
  }},

  CSSNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetFlexDirection(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetFlexGrow(' + nodeName + ', ' + toFloatString(value) + ');');
  }},

  CSSNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetFlexShrink(' + nodeName + ', ' + toFloatString(value) + ');');
  }},

  CSSNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetFlexWrap(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetHeight(' + nodeName + ', ' + toFloatString(value) + ');');
  }},

  CSSNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetJustifyContent(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push('YGNodeStyleSetMargin(' + nodeName + ', ' + edge + ', ' + toFloatString(value) + ');');
  }},

  CSSNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetMaxHeight(' + nodeName + ', ' + toFloatString(value) + ');');
  }},

  CSSNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetMaxWidth(' + nodeName + ', ' + toFloatString(value) + ');');
  }},

  CSSNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetMinHeight(' + nodeName + ', ' + toFloatString(value) + ');');
  }},

  CSSNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetMinWidth(' + nodeName + ', ' + toFloatString(value) + ');');
  }},

  CSSNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetOverflow(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push('YGNodeStyleSetPadding(' + nodeName + ', ' + edge + ', ' + toFloatString(value) + ');');
  }},

  CSSNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push('YGNodeStyleSetPosition(' + nodeName + ', ' + edge + ', ' + toFloatString(value) + ');');
  }},

  CSSNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetPositionType(' + nodeName + ', ' + value + ');');
  }},

  CSSNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetWidth(' + nodeName + ', ' + toFloatString(value) + ');');
  }},
});
