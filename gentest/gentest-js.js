/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var JSEmitter = function() {
  Emitter.call(this, 'js', '  ');
};

JSEmitter.prototype = Object.create(Emitter.prototype, {
  constructor:{value:JSEmitter},

  emitPrologue:{value:function() {
    this.push([
      'var include = require(\'./include.js\');',
      'include.include(\'../src/YGEnums.js\');',
      'include.include(\'../src/Yoga.js\');',
      '',
      'describe(\'YogaTest\', () => {',
      '',
    ]);
    this.pushIndent();
  }},

  emitTestPrologue:{value:function(name, experiments) {
    this.push('it(\'' + name + '\', () => {');
    this.pushIndent();

    if (experiments.length > 0) {
      for (var i in experiments) {
        this.push('_YGSetExperimentalFeatureEnabled(_YGExperimentalFeature' + experiments[i] +', true);');
      }
      this.push('');
    }
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('var ' + nodeName + ' = _YGNodeNew();');
  }},

  emitTestEpilogue:{value:function(experiments) {
    this.push([
      '',
      '_YGNodeFreeRecursive(root);',
    ]);

    if (experiments.length > 0) {
      this.push('');
      for (var i in experiments) {
        this.push('_YGSetExperimentalFeatureEnabled(_YGExperimentalFeature' + experiments[i] +', false);');
      }
    }

    this.popIndent();
    this.push([
      '});',
      '',
    ]);
  }},

  emitEpilogue:{value:function() {
    this.popIndent();
    this.push([
      '});',
      '',
    ]);
  }},

  AssertEQ:{value:function(v0, v1) {
    this.push('expect(' + v1 + ').toBe(' + v0 + ');');
  }},

  YGAlignAuto:{value:'_YGAlignAuto'},
  YGAlignCenter:{value:'_YGAlignCenter'},
  YGAlignFlexEnd:{value:'_YGAlignFlexEnd'},
  YGAlignFlexStart:{value:'_YGAlignFlexStart'},
  YGAlignStretch:{value:'_YGAlignStretch'},

  YGDirectionInherit:{value:'_YGDirectionInherit'},
  YGDirectionLTR:{value:'_YGDirectionLTR'},
  YGDirectionRTL:{value:'_YGDirectionRTL'},

  YGEdgeBottom:{value:'_YGEdgeBottom'},
  YGEdgeEnd:{value:'_YGEdgeEnd'},
  YGEdgeLeft:{value:'_YGEdgeLeft'},
  YGEdgeRight:{value:'_YGEdgeRight'},
  YGEdgeStart:{value:'_YGEdgeStart'},
  YGEdgeTop:{value:'_YGEdgeTop'},

  YGFlexDirectionColumn:{value:'_YGFlexDirectionColumn'},
  YGFlexDirectionColumnReverse:{value:'_YGFlexDirectionColumnReverse'},
  YGFlexDirectionRow:{value:'_YGFlexDirectionRow'},
  YGFlexDirectionRowReverse:{value:'_YGFlexDirectionRowReverse'},

  YGJustifyCenter:{value:'_YGJustifyCenter'},
  YGJustifyFlexEnd:{value:'_YGJustifyFlexEnd'},
  YGJustifyFlexStart:{value:'_YGJustifyFlexStart'},
  YGJustifySpaceAround:{value:'_YGJustifySpaceAround'},
  YGJustifySpaceBetween:{value:'_YGJustifySpaceBetween'},

  YGOverflowHidden:{value:'_YGOverflowHidden'},
  YGOverflowVisible:{value:'_YGOverflowVisible'},

  YGPositionTypeAbsolute:{value:'_YGPositionTypeAbsolute'},
  YGPositionTypeRelative:{value:'_YGPositionTypeRelative'},

  YGWrapNoWrap:{value:'_YGWrapNoWrap'},
  YGWrapWrap:{value:'_YGWrapWrap'},

  YGUndefined:{value:'_YGUndefined'},

  YGNodeCalculateLayout:{value:function(node, dir) {
    this.push('_YGNodeCalculateLayout(' +
      node + ', ' + this.YGUndefined + ', ' + this.YGUndefined + ', ' + dir + ');');
  }},

  YGNodeInsertChild:{value:function(parentName, nodeName, index) {
    this.push('_YGNodeInsertChild(' + parentName + ', ' + nodeName + ', ' + index + ');');
  }},

  YGNodeLayoutGetLeft:{value:function(nodeName) {
    return '_YGNodeLayoutGetLeft(' + nodeName + ')';
  }},

  YGNodeLayoutGetTop:{value:function(nodeName) {
    return '_YGNodeLayoutGetTop(' + nodeName + ')';
  }},

  YGNodeLayoutGetWidth:{value:function(nodeName) {
    return '_YGNodeLayoutGetWidth(' + nodeName + ')';
  }},

  YGNodeLayoutGetHeight:{value:function(nodeName) {
    return '_YGNodeLayoutGetHeight(' + nodeName + ')';
  }},

  YGNodeStyleSetAlignContent:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetAlignContent(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetAlignItems:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetAlignItems(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetAlignSelf:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetAlignSelf(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetBorder:{value:function(nodeName, edge, value) {
    this.push('_YGNodeStyleSetBorder(' + nodeName + ', ' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetDirection(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetFlexBasis(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetFlexDirection(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetFlexGrow(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetFlexShrink(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetFlexWrap(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetHeight(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetJustifyContent(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push('_YGNodeStyleSetMargin(' + nodeName + ', ' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetMaxHeight(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetMaxWidth(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetMinHeight(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetMinWidth(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetOverflow(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push('_YGNodeStyleSetPadding(' + nodeName + ', ' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push('_YGNodeStyleSetPosition(' + nodeName + ', ' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetPositionType(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push('_YGNodeStyleSetWidth(' + nodeName + ', ' + value + ');');
  }},
});
