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
      'var Yoga = Yoga || require(\'../src/Yoga.js\');',
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
        this.push('Yoga.setExperimentalFeatureEnabled(Yoga.ExperimentalFeature' + experiments[i] +', true);');
      }
      this.push('');
    }
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('var ' + nodeName + ' = Yoga.nodeNew();');
  }},

  emitTestEpilogue:{value:function(experiments) {
    this.push([
      '',
      'Yoga.nodeFreeRecursive(root);',
    ]);

    if (experiments.length > 0) {
      this.push('');
      for (var i in experiments) {
        this.push('Yoga.setExperimentalFeatureEnabled(Yoga.ExperimentalFeature' + experiments[i] +', false);');
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

  YGAlignAuto:{value:'Yoga.AlignAuto'},
  YGAlignCenter:{value:'Yoga.AlignCenter'},
  YGAlignFlexEnd:{value:'Yoga.AlignFlexEnd'},
  YGAlignFlexStart:{value:'Yoga.AlignFlexStart'},
  YGAlignStretch:{value:'Yoga.AlignStretch'},

  YGDirectionInherit:{value:'Yoga.DirectionInherit'},
  YGDirectionLTR:{value:'Yoga.DirectionLTR'},
  YGDirectionRTL:{value:'Yoga.DirectionRTL'},

  YGEdgeBottom:{value:'Yoga.EdgeBottom'},
  YGEdgeEnd:{value:'Yoga.EdgeEnd'},
  YGEdgeLeft:{value:'Yoga.EdgeLeft'},
  YGEdgeRight:{value:'Yoga.EdgeRight'},
  YGEdgeStart:{value:'Yoga.EdgeStart'},
  YGEdgeTop:{value:'Yoga.EdgeTop'},

  YGFlexDirectionColumn:{value:'Yoga.FlexDirectionColumn'},
  YGFlexDirectionColumnReverse:{value:'Yoga.FlexDirectionColumnReverse'},
  YGFlexDirectionRow:{value:'Yoga.FlexDirectionRow'},
  YGFlexDirectionRowReverse:{value:'Yoga.FlexDirectionRowReverse'},

  YGJustifyCenter:{value:'Yoga.JustifyCenter'},
  YGJustifyFlexEnd:{value:'Yoga.JustifyFlexEnd'},
  YGJustifyFlexStart:{value:'Yoga.JustifyFlexStart'},
  YGJustifySpaceAround:{value:'Yoga.JustifySpaceAround'},
  YGJustifySpaceBetween:{value:'Yoga.JustifySpaceBetween'},

  YGOverflowHidden:{value:'Yoga.OverflowHidden'},
  YGOverflowVisible:{value:'Yoga.OverflowVisible'},

  YGPositionTypeAbsolute:{value:'Yoga.PositionTypeAbsolute'},
  YGPositionTypeRelative:{value:'Yoga.PositionTypeRelative'},

  YGWrapNoWrap:{value:'Yoga.WrapNoWrap'},
  YGWrapWrap:{value:'Yoga.WrapWrap'},

  YGUndefined:{value:'Yoga.Undefined'},

  YGNodeCalculateLayout:{value:function(node, dir) {
    this.push('Yoga.nodeCalculateLayout(' +
      node + ', ' + this.YGUndefined + ', ' + this.YGUndefined + ', ' + dir + ');');
  }},

  YGNodeInsertChild:{value:function(parentName, nodeName, index) {
    this.push('Yoga.nodeInsertChild(' + parentName + ', ' + nodeName + ', ' + index + ');');
  }},

  YGNodeLayoutGetLeft:{value:function(nodeName) {
    return 'Yoga.nodeLayoutGetLeft(' + nodeName + ')';
  }},

  YGNodeLayoutGetTop:{value:function(nodeName) {
    return 'Yoga.nodeLayoutGetTop(' + nodeName + ')';
  }},

  YGNodeLayoutGetWidth:{value:function(nodeName) {
    return 'Yoga.nodeLayoutGetWidth(' + nodeName + ')';
  }},

  YGNodeLayoutGetHeight:{value:function(nodeName) {
    return 'Yoga.nodeLayoutGetHeight(' + nodeName + ')';
  }},

  YGNodeStyleSetAlignContent:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetAlignContent(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetAlignItems:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetAlignItems(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetAlignSelf:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetAlignSelf(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetBorder:{value:function(nodeName, edge, value) {
    this.push('Yoga.nodeStyleSetBorder(' + nodeName + ', ' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetDirection(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetFlexBasis(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetFlexDirection(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetFlexGrow(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetFlexShrink(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetFlexWrap(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetHeight(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetJustifyContent(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push('Yoga.nodeStyleSetMargin(' + nodeName + ', ' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetMaxHeight(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetMaxWidth(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetMinHeight(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetMinWidth(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetOverflow(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push('Yoga.nodeStyleSetPadding(' + nodeName + ', ' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push('Yoga.nodeStyleSetPosition(' + nodeName + ', ' + edge + ', ' + value + ');');
  }},

  YGNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetPositionType(' + nodeName + ', ' + value + ');');
  }},

  YGNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push('Yoga.nodeStyleSetWidth(' + nodeName + ', ' + value + ');');
  }},
});
