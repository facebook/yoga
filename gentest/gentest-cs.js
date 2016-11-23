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
      'namespace Facebook.CSSLayout',
      '{',
    ]);
    this.pushIndent();
    this.push([
      '[TestFixture]',
      'public class CSSNodeLayoutTest',
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
        this.push('CSSNode.SetExperimentalFeatureEnabled(CSSExperimentalFeature.' + experiments[i] +', true);');
      }
      this.push('');
    }
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('CSSNode ' + nodeName + ' = new CSSNode();');
  }},

  emitTestEpilogue:{value:function(experiments) {
    if (experiments.length > 0) {
      this.push('');
      for (var i in experiments) {
        this.push('CSSNode.SetExperimentalFeatureEnabled(CSSExperimentalFeature.' + experiments[i] +', false);');
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

  CSSAlignAuto:{value:'CSSAlign.Auto'},
  CSSAlignCenter:{value:'CSSAlign.Center'},
  CSSAlignFlexEnd:{value:'CSSAlign.FlexEnd'},
  CSSAlignFlexStart:{value:'CSSAlign.FlexStart'},
  CSSAlignStretch:{value:'CSSAlign.Stretch'},

  CSSDirectionInherit:{value:'CSSDirection.Inherit'},
  CSSDirectionLTR:{value:'CSSDirection.LTR'},
  CSSDirectionRTL:{value:'CSSDirection.RTL'},

  CSSEdgeBottom:{value:'CSSEdge.Bottom'},
  CSSEdgeEnd:{value:'CSSEdge.End'},
  CSSEdgeLeft:{value:'CSSEdge.Left'},
  CSSEdgeRight:{value:'CSSEdge.Right'},
  CSSEdgeStart:{value:'CSSEdge.Start'},
  CSSEdgeTop:{value:'CSSEdge.Top'},

  CSSFlexDirectionColumn:{value:'CSSFlexDirection.Column'},
  CSSFlexDirectionColumnReverse:{value:'CSSFlexDirection.ColumnReverse'},
  CSSFlexDirectionRow:{value:'CSSFlexDirection.Row'},
  CSSFlexDirectionRowReverse:{value:'CSSFlexDirection.RowReverse'},

  CSSJustifyCenter:{value:'CSSJustify.Center'},
  CSSJustifyFlexEnd:{value:'CSSJustify.FlexEnd'},
  CSSJustifyFlexStart:{value:'CSSJustify.FlexStart'},
  CSSJustifySpaceAround:{value:'CSSJustify.SpaceAround'},
  CSSJustifySpaceBetween:{value:'CSSJustify.SpaceBetween'},

  CSSOverflowHidden:{value:'CSSOverflow.Hidden'},
  CSSOverflowVisible:{value:'CSSOverflow.Visible'},

  CSSPositionTypeAbsolute:{value:'CSSPositionType.Absolute'},
  CSSPositionTypeRelative:{value:'CSSPositionType.Relative'},

  CSSUndefined:{value:'CSSConstants.Undefined'},

  CSSWrapNoWrap:{value:'CSSWrap.NoWrap'},
  CSSWrapWrap:{value:'CSSWrap.Wrap'},

  CSSNodeCalculateLayout:{value:function(node, dir) {
    this.push(node + '.StyleDirection = ' + dir + ';');
    this.push(node + '.CalculateLayout();');
  }},

  CSSNodeInsertChild:{value:function(parentName, nodeName, index) {
    this.push(parentName + '.Insert(' + index + ', ' + nodeName + ');');
  }},

  CSSNodeLayoutGetLeft:{value:function(nodeName) {
    return nodeName + '.LayoutX';
  }},

  CSSNodeLayoutGetTop:{value:function(nodeName) {
    return nodeName + '.LayoutY';
  }},

  CSSNodeLayoutGetWidth:{value:function(nodeName) {
    return nodeName + '.LayoutWidth';
  }},

  CSSNodeLayoutGetHeight:{value:function(nodeName) {
    return nodeName + '.LayoutHeight';
  }},

  CSSNodeStyleSetAlignContent:{value:function(nodeName, value) {
    this.push(nodeName + '.AlignContent = ' + value + ';');
  }},

  CSSNodeStyleSetAlignItems:{value:function(nodeName, value) {
    this.push(nodeName + '.AlignItems = ' + value + ';');
  }},

  CSSNodeStyleSetAlignSelf:{value:function(nodeName, value) {
    this.push(nodeName + '.AlignSelf = ' + value + ';');
  }},

  CSSNodeStyleSetBorder:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.SetBorder(' + edge + ', ' + value + 'f);');
  }},

  CSSNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.StyleDirection = ' + value + ';');
  }},

  CSSNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push(nodeName + '.FlexBasis = ' + value + 'f;');
  }},

  CSSNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.FlexDirection = ' + value + ';');
  }},

  CSSNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push(nodeName + '.FlexGrow = ' + value + 'f;');
  }},

  CSSNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push(nodeName + '.FlexShrink = ' + value + 'f;');
  }},

  CSSNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push(nodeName + '.Wrap = ' + value + ';');
  }},

  CSSNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.StyleHeight = ' + value + 'f;');
  }},

  CSSNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push(nodeName + '.JustifyContent = ' + value + ';');
  }},

  CSSNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.SetMargin(' + edge + ', ' + value + 'f);');
  }},

  CSSNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.StyleMaxHeight = ' + value + 'f;');
  }},

  CSSNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.StyleMaxWidth = ' + value + 'f;');
  }},

  CSSNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.StyleMinHeight = ' + value + 'f;');
  }},

  CSSNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.StyleMinWidth = ' + value + 'f;');
  }},

  CSSNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push(nodeName + '.Overflow = ' + value + ';');
  }},

  CSSNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.SetPadding(' + edge + ', ' + value + 'f);');
  }},

  CSSNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.SetPosition(' + edge + ', ' + value + 'f);');
  }},

  CSSNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push(nodeName + '.PositionType = ' + value + ';');
  }},

  CSSNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.StyleWidth = ' + value + 'f;');
  }},
});
