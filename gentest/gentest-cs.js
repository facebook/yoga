/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var CSEmitter = function() {
  Emitter.call(this, 'cs', '    ');
};

CSEmitter.prototype = Object.create(Emitter.prototype, {
  constructor:{value:CSEmitter},

  emitPrologue:{value:function() {
    this.push([
      'using System;',
      'using NUnit.Framework;',
      '',
      'namespace Facebook.Yoga',
      '{',
    ]);
    this.pushIndent();
    this.push([
      '[TestFixture]',
      'public class YogaTest',
      '{',
    ]);
    this.pushIndent();
  }},

  emitTestPrologue:{value:function(name, experiments) {
    this.push('[Test]');
    this.push('public void Test_' + name + '()');
    this.push('{');
    this.pushIndent();

    if (experiments.length > 0) {
      for (var i in experiments) {
        this.push('YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.' + experiments[i] +', true);');
      }
      this.push('');
    }
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('YogaNode ' + nodeName + ' = new YogaNode();');
  }},

  emitTestEpilogue:{value:function(experiments) {
    if (experiments.length > 0) {
      this.push('');
      for (var i in experiments) {
        this.push('YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.' + experiments[i] +', false);');
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
    this.push('}');
    this.popIndent();
    this.push([
      '}',
      '',
    ]);
  }},

  AssertEQ:{value:function(v0, v1) {
    this.push('Assert.AreEqual(' + v0 + 'f, ' + v1 + ');');
  }},

  YGAlignAuto:{value:'YogaAlign.Auto'},
  YGAlignCenter:{value:'YogaAlign.Center'},
  YGAlignFlexEnd:{value:'YogaAlign.FlexEnd'},
  YGAlignFlexStart:{value:'YogaAlign.FlexStart'},
  YGAlignStretch:{value:'YogaAlign.Stretch'},

  YGDirectionInherit:{value:'YogaDirection.Inherit'},
  YGDirectionLTR:{value:'YogaDirection.LTR'},
  YGDirectionRTL:{value:'YogaDirection.RTL'},

  YGEdgeBottom:{value:'YogaEdge.Bottom'},
  YGEdgeEnd:{value:'YogaEdge.End'},
  YGEdgeLeft:{value:'YogaEdge.Left'},
  YGEdgeRight:{value:'YogaEdge.Right'},
  YGEdgeStart:{value:'YogaEdge.Start'},
  YGEdgeTop:{value:'YogaEdge.Top'},

  YGFlexDirectionColumn:{value:'YogaFlexDirection.Column'},
  YGFlexDirectionColumnReverse:{value:'YogaFlexDirection.ColumnReverse'},
  YGFlexDirectionRow:{value:'YogaFlexDirection.Row'},
  YGFlexDirectionRowReverse:{value:'YogaFlexDirection.RowReverse'},

  YGJustifyCenter:{value:'YogaJustify.Center'},
  YGJustifyFlexEnd:{value:'YogaJustify.FlexEnd'},
  YGJustifyFlexStart:{value:'YogaJustify.FlexStart'},
  YGJustifySpaceAround:{value:'YogaJustify.SpaceAround'},
  YGJustifySpaceBetween:{value:'YogaJustify.SpaceBetween'},

  YGOverflowHidden:{value:'YogaOverflow.Hidden'},
  YGOverflowVisible:{value:'YogaOverflow.Visible'},

  YGPositionTypeAbsolute:{value:'YogaPositionType.Absolute'},
  YGPositionTypeRelative:{value:'YogaPositionType.Relative'},

  YGUndefined:{value:'YogaConstants.Undefined'},

  YGWrapNoWrap:{value:'YogaWrap.NoWrap'},
  YGWrapWrap:{value:'YogaWrap.Wrap'},

  YGNodeCalculateLayout:{value:function(node, dir) {
    this.push(node + '.StyleDirection = ' + dir + ';');
    this.push(node + '.CalculateLayout();');
  }},

  YGNodeInsertChild:{value:function(parentName, nodeName, index) {
    this.push(parentName + '.Insert(' + index + ', ' + nodeName + ');');
  }},

  YGNodeLayoutGetLeft:{value:function(nodeName) {
    return nodeName + '.LayoutX';
  }},

  YGNodeLayoutGetTop:{value:function(nodeName) {
    return nodeName + '.LayoutY';
  }},

  YGNodeLayoutGetWidth:{value:function(nodeName) {
    return nodeName + '.LayoutWidth';
  }},

  YGNodeLayoutGetHeight:{value:function(nodeName) {
    return nodeName + '.LayoutHeight';
  }},

  YGNodeStyleSetAlignContent:{value:function(nodeName, value) {
    this.push(nodeName + '.AlignContent = ' + value + ';');
  }},

  YGNodeStyleSetAlignItems:{value:function(nodeName, value) {
    this.push(nodeName + '.AlignItems = ' + value + ';');
  }},

  YGNodeStyleSetAlignSelf:{value:function(nodeName, value) {
    this.push(nodeName + '.AlignSelf = ' + value + ';');
  }},

  YGNodeStyleSetBorder:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.SetBorder(' + edge + ', ' + value + 'f);');
  }},

  YGNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.StyleDirection = ' + value + ';');
  }},

  YGNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push(nodeName + '.FlexBasis = ' + value + 'f;');
  }},

  YGNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.FlexDirection = ' + value + ';');
  }},

  YGNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push(nodeName + '.FlexGrow = ' + value + 'f;');
  }},

  YGNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push(nodeName + '.FlexShrink = ' + value + 'f;');
  }},

  YGNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push(nodeName + '.Wrap = ' + value + ';');
  }},

  YGNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.Height = ' + value + 'f;');
  }},

  YGNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push(nodeName + '.JustifyContent = ' + value + ';');
  }},

  YGNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.SetMargin(' + edge + ', ' + value + 'f);');
  }},

  YGNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.MaxHeight = ' + value + 'f;');
  }},

  YGNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.MaxWidth = ' + value + 'f;');
  }},

  YGNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.MinHeight = ' + value + 'f;');
  }},

  YGNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.MinWidth = ' + value + 'f;');
  }},

  YGNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push(nodeName + '.Overflow = ' + value + ';');
  }},

  YGNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.SetPadding(' + edge + ', ' + value + 'f);');
  }},

  YGNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.SetPosition(' + edge + ', ' + value + 'f);');
  }},

  YGNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push(nodeName + '.PositionType = ' + value + ';');
  }},

  YGNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.Width = ' + value + 'f;');
  }},
});
