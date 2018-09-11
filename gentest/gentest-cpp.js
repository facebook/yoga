/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

function toValueCpp(value) {
  var n = value.toString().replace('px','').replace('%','');
  return n + (Number(n) == n && n % 1 !== 0 ? 'f' : '');
}

function toFunctionName(value) {
  if (value.indexOf('%') >= 0) {
    return 'Percent';
  } else if(value.indexOf('Auto') >= 0) {
    return 'Auto';
  }
  return '';
}

var CPPEmitter = function() {
  Emitter.call(this, 'cpp', '  ');
};

CPPEmitter.prototype = Object.create(Emitter.prototype, {
  constructor:{value:CPPEmitter},

  emitPrologue:{value:function() {
    this.push([
      '#include <gtest/gtest.h>',
      '#include <yoga/Yoga.h>',
      '',
    ]);
  }},

  emitTestPrologue:{value:function(name, experiments) {
    this.push('TEST(YogaTest, ' + name + ') {');
    this.pushIndent();

    this.push('const YGConfigRef config = YGConfigNew();')
    for (var i in experiments) {
      this.push('YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeature' + experiments[i] +', true);');
    }
    this.push('');
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('const YGNodeRef ' + nodeName + ' = YGNodeNewWithConfig(config);');
  }},

  emitTestEpilogue:{value:function(experiments) {
    this.push([
      '',
      'YGNodeFreeRecursive(root);',
    ]);

    this.push('');
    this.push('YGConfigFree(config);')

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
  YGAlignSpaceBetween:{value:'YGAlignSpaceBetween'},
  YGAlignSpaceAround:{value:'YGAlignSpaceAround'},
  YGAlignBaseline:{value:'YGAlignBaseline'},

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
  YGJustifySpaceEvenly:{value:'YGJustifySpaceEvenly'},

  YGOverflowHidden:{value:'YGOverflowHidden'},
  YGOverflowVisible:{value:'YGOverflowVisible'},

  YGPositionTypeAbsolute:{value:'YGPositionTypeAbsolute'},
  YGPositionTypeRelative:{value:'YGPositionTypeRelative'},

  YGWrapNoWrap:{value:'YGWrapNoWrap'},
  YGWrapWrap:{value:'YGWrapWrap'},
  YGWrapWrapReverse:{value: 'YGWrapWrapReverse'},

  YGUndefined:{value:'YGUndefined'},

  YGDisplayFlex:{value:'YGDisplayFlex'},
  YGDisplayNone:{value:'YGDisplayNone'},
  YGAuto:{value:'YGAuto'},


  YGNodeCalculateLayout:{value:function(node, dir, experiments) {
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

  YGNodeStyleSetDisplay:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetDisplay(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetFlexBasis' + toFunctionName(value) + '(' + nodeName + ', ' + toValueCpp(value) + ');');
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
    this.push('YGNodeStyleSetHeight' + toFunctionName(value) + '(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetJustifyContent(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    var valueStr = toValueCpp(value);
    if (valueStr != 'YGAuto') {
      valueStr = ', ' + valueStr;
    } else {
      valueStr = '';
    }
    this.push('YGNodeStyleSetMargin' + toFunctionName(value) + '(' + nodeName + ', ' + edge +  valueStr + ');');
  }},

  YGNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetMaxHeight' + toFunctionName(value) + '(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetMaxWidth' + toFunctionName(value) + '(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetMinHeight' + toFunctionName(value) + '(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetMinWidth' + toFunctionName(value) + '(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetOverflow(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push('YGNodeStyleSetPadding' + toFunctionName(value) + '(' + nodeName + ', ' + edge + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push('YGNodeStyleSetPosition' + toFunctionName(value) + '(' + nodeName + ', ' + edge + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetPositionType(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},

  YGNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push('YGNodeStyleSetWidth' + toFunctionName(value) + '(' + nodeName + ', ' + toValueCpp(value) + ');');
  }},
});
