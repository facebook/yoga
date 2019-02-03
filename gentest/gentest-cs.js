/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

function toValueCs(value) {
  var n = value.toString().replace('px','').replace('%','');
  return n + (Number(n) == n && n % 1 !== 0 ? 'f' : '');
}

function toCsUnitValue(value) {
  var methodName = '';
  if (value.indexOf('%') >= 0){
    methodName = '.Percent()';
  }
  if(value.indexOf('Auto') >= 0){
    return 'YogaValue.Auto()';
  }
  return toValueCs(value) + methodName;
}

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

    this.push('YogaConfig config = new YogaConfig();')
    for (var i in experiments) {
      this.push('config.SetExperimentalFeatureEnabled(YogaExperimentalFeature.' + experiments[i] +', true);');
    }
    this.push('');
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('YogaNode ' + nodeName + ' = new YogaNode(config);');
  }},

  emitTestEpilogue:{value:function(experiments) {

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
  YGAlignSpaceBetween:{value:'YogaAlign.SpaceBetween'},
  YGAlignSpaceAround:{value:'YogaAlign.SpaceAround'},
  YGAlignBaseline:{value:'YogaAlign.Baseline'},

  YGDirectionInherit:{value:'YogaDirection.Inherit'},
  YGDirectionLTR:{value:'YogaDirection.LTR'},
  YGDirectionRTL:{value:'YogaDirection.RTL'},

  YGEdgeBottom:{value:'Bottom'},
  YGEdgeEnd:{value:'End'},
  YGEdgeLeft:{value:'Left'},
  YGEdgeRight:{value:'Right'},
  YGEdgeStart:{value:'Start'},
  YGEdgeTop:{value:'Top'},

  YGFlexDirectionColumn:{value:'YogaFlexDirection.Column'},
  YGFlexDirectionColumnReverse:{value:'YogaFlexDirection.ColumnReverse'},
  YGFlexDirectionRow:{value:'YogaFlexDirection.Row'},
  YGFlexDirectionRowReverse:{value:'YogaFlexDirection.RowReverse'},

  YGJustifyCenter:{value:'YogaJustify.Center'},
  YGJustifyFlexEnd:{value:'YogaJustify.FlexEnd'},
  YGJustifyFlexStart:{value:'YogaJustify.FlexStart'},
  YGJustifySpaceAround:{value:'YogaJustify.SpaceAround'},
  YGJustifySpaceBetween:{value:'YogaJustify.SpaceBetween'},
  YGJustifySpaceEvenly:{value:'YogaJustify.SpaceEvenly'},

  YGOverflowHidden:{value:'YogaOverflow.Hidden'},
  YGOverflowVisible:{value:'YogaOverflow.Visible'},

  YGPositionTypeAbsolute:{value:'YogaPositionType.Absolute'},
  YGPositionTypeRelative:{value:'YogaPositionType.Relative'},

  YGUndefined:{value:'YogaConstants.Undefined'},

  YGAuto:{value:'YogaConstants.Auto'},

  YGDisplayFlex:{value:'YogaDisplay.Flex'},
  YGDisplayNone:{value:'YogaDisplay.None'},

  YGWrapNoWrap:{value:'YogaWrap.NoWrap'},
  YGWrapWrap:{value:'YogaWrap.Wrap'},
  YGWrapWrapReverse:{value: 'YogaWrap.WrapReverse'},

  YGNodeCalculateLayout:{value:function(node, dir, experiments) {
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
    this.push(nodeName + '.AlignContent = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetAlignItems:{value:function(nodeName, value) {
    this.push(nodeName + '.AlignItems = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetAlignSelf:{value:function(nodeName, value) {
    this.push(nodeName + '.AlignSelf = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetBorder:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.Border' + edge + 'Width = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.StyleDirection = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetDisplay:{value:function(nodeName, value) {
    this.push(nodeName + '.Display = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push(nodeName + '.FlexBasis = ' + toCsUnitValue(value) + ';');
  }},

  YGNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.FlexDirection = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push(nodeName + '.FlexGrow = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push(nodeName + '.FlexShrink = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push(nodeName + '.Wrap = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.Height = ' + toCsUnitValue(value) + ';');
  }},

  YGNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push(nodeName + '.JustifyContent = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.Margin' + edge + ' = ' + toCsUnitValue(value) + ';');
  }},

  YGNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.MaxHeight = ' + toCsUnitValue(value) + ';');
  }},

  YGNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.MaxWidth = ' + toCsUnitValue(value) + ';');
  }},

  YGNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.MinHeight = ' + toCsUnitValue(value) + ';');
  }},

  YGNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.MinWidth = ' + toCsUnitValue(value) + ';');
  }},

  YGNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push(nodeName + '.Overflow = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.Padding' + edge + ' = ' + toCsUnitValue(value) + ';');
  }},

  YGNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.' + edge + ' = ' + toCsUnitValue(value) + ';');
  }},

  YGNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push(nodeName + '.PositionType = ' + toValueCs(value) + ';');
  }},

  YGNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.Width = ' + toCsUnitValue(value) + ';');
  }},
});
