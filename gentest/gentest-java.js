/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

function toValueJava(value) {
  var n = value.toString().replace('px','').replace('%','');
  return n + (Number(n) == n && n % 1 !== 0 ? '' : '');
}

function toMethodName(value) {
  if (value.indexOf('%') >= 0){
    return 'Percent';
  } else if(value.indexOf('AUTO') >= 0) {
    return 'Auto';
  }
  return '';
}

var JavaEmitter = function() {
  Emitter.call(this, 'java', '  ');
};

function toJavaUpper(symbol) {
  var out = '';
  for (var i = 0; i < symbol.length; i++) {
    var c = symbol[i];
    if (c == c.toUpperCase() && i != 0 && symbol[i - 1] != symbol[i - 1].toUpperCase()) {
      out += '_';
    }
    out += c.toUpperCase();
  }
  return out;
}

JavaEmitter.prototype = Object.create(Emitter.prototype, {
  constructor:{value:JavaEmitter},

  emitPrologue:{value:function() {
    this.push([
      'package com.facebook.yoga;',
      '',
      'import static org.junit.Assert.assertEquals;',
      '',
      'import org.junit.Ignore;',
      'import org.junit.Test;',
      'import org.junit.runner.RunWith;',
      'import org.junit.runners.Parameterized;',
      '',
      '@RunWith(Parameterized.class)',
      'public class YogaTest {',
    ]);
    this.pushIndent();
    this.push([
      '@Parameterized.Parameters(name = "{0}")',
      'public static Iterable<TestParametrization.NodeFactory> nodeFactories() {',
    ]);
    this.pushIndent();
    this.push('return TestParametrization.nodeFactories();');
    this.popIndent();
    this.push('}');
    this.push([
      '',
      '@Parameterized.Parameter public TestParametrization.NodeFactory mNodeFactory;',
      '',
    ]);
  }},

  emitTestPrologue:{value:function(name, experiments, disabled) {
    this.push('@Test');
    if (disabled) {
      this.push('@Ignore');
    }
    this.push('public void test_' + name + '() {');
    this.pushIndent();

    this.push("YogaConfig config = YogaConfigFactory.create();")
    for (var i in experiments) {
      this.push('config.setExperimentalFeatureEnabled(YogaExperimentalFeature.' + toJavaUpper(experiments[i]) +', true);');
    }
    this.push('');
  }},

  emitTestTreePrologue:{value:function(nodeName) {
    this.push('final YogaNode ' + nodeName + ' = createNode(config);');
  }},

  emitTestEpilogue:{value:function(experiments) {
    this.popIndent();
    this.push([
      '}',
      '',
    ]);
  }},

  emitEpilogue:{value:function(lines) {
    this.push('private YogaNode createNode(YogaConfig config) {');
    this.pushIndent();
    this.push('return mNodeFactory.create(config);');
    this.popIndent();
    this.push('}');
    this.popIndent();
    this.push([
      '}',
      '',
    ]);
  }},

  AssertEQ:{value:function(v0, v1) {
    this.push('assertEquals(' + v0 + 'f, ' + v1 + ', 0.0f);');
  }},

  YGAlignAuto:{value:'YogaAlign.AUTO'},
  YGAlignCenter:{value:'YogaAlign.CENTER'},
  YGAlignFlexEnd:{value:'YogaAlign.FLEX_END'},
  YGAlignFlexStart:{value:'YogaAlign.FLEX_START'},
  YGAlignStretch:{value:'YogaAlign.STRETCH'},
  YGAlignSpaceBetween:{value:'YogaAlign.SPACE_BETWEEN'},
  YGAlignSpaceAround:{value:'YogaAlign.SPACE_AROUND'},
  YGAlignBaseline:{value:'YogaAlign.BASELINE'},

  YGDirectionInherit:{value:'YogaDirection.INHERIT'},
  YGDirectionLTR:{value:'YogaDirection.LTR'},
  YGDirectionRTL:{value:'YogaDirection.RTL'},

  YGEdgeBottom:{value:'YogaEdge.BOTTOM'},
  YGEdgeEnd:{value:'YogaEdge.END'},
  YGEdgeLeft:{value:'YogaEdge.LEFT'},
  YGEdgeRight:{value:'YogaEdge.RIGHT'},
  YGEdgeStart:{value:'YogaEdge.START'},
  YGEdgeTop:{value:'YogaEdge.TOP'},

  YGGutterAll:{value:'YogaGutter.ALL'},
  YGGutterColumn:{value:'YogaGutter.COLUMN'},
  YGGutterRow:{value:'YogaGutter.ROW'},

  YGFlexDirectionColumn:{value:'YogaFlexDirection.COLUMN'},
  YGFlexDirectionColumnReverse:{value:'YogaFlexDirection.COLUMN_REVERSE'},
  YGFlexDirectionRow:{value:'YogaFlexDirection.ROW'},
  YGFlexDirectionRowReverse:{value:'YogaFlexDirection.ROW_REVERSE'},

  YGJustifyCenter:{value:'YogaJustify.CENTER'},
  YGJustifyFlexEnd:{value:'YogaJustify.FLEX_END'},
  YGJustifyFlexStart:{value:'YogaJustify.FLEX_START'},
  YGJustifySpaceAround:{value:'YogaJustify.SPACE_AROUND'},
  YGJustifySpaceBetween:{value:'YogaJustify.SPACE_BETWEEN'},
  YGJustifySpaceEvenly:{value:'YogaJustify.SPACE_EVENLY'},

  YGOverflowHidden:{value:'YogaOverflow.HIDDEN'},
  YGOverflowVisible:{value:'YogaOverflow.VISIBLE'},

  YGPositionTypeAbsolute:{value:'YogaPositionType.ABSOLUTE'},
  YGPositionTypeRelative:{value:'YogaPositionType.RELATIVE'},

  YGUndefined:{value:'YogaConstants.UNDEFINED'},

  YGDisplayFlex:{value:'YogaDisplay.FLEX'},
  YGDisplayNone:{value:'YogaDisplay.NONE'},
  YGAuto:{value:'YogaConstants.AUTO'},


  YGWrapNoWrap:{value:'YogaWrap.NO_WRAP'},
  YGWrapWrap:{value:'YogaWrap.WRAP'},
  YGWrapWrapReverse:{value: 'YogaWrap.WRAP_REVERSE'},

  YGNodeCalculateLayout:{value:function(node, dir, experiments) {
    this.push(node + '.setDirection(' + dir + ');');
    this.push(node + '.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);');
  }},

  YGNodeInsertChild:{value:function(parentName, nodeName, index) {
    this.push(parentName + '.addChildAt(' + nodeName + ', ' + index + ');');
  }},

  YGNodeLayoutGetLeft:{value:function(nodeName) {
    return nodeName + '.getLayoutX()';
  }},

  YGNodeLayoutGetTop:{value:function(nodeName) {
    return nodeName + '.getLayoutY()';
  }},

  YGNodeLayoutGetWidth:{value:function(nodeName) {
    return nodeName + '.getLayoutWidth()';
  }},

  YGNodeLayoutGetHeight:{value:function(nodeName) {
    return nodeName + '.getLayoutHeight()';
  }},

  YGNodeStyleSetAlignContent:{value:function(nodeName, value) {
    this.push(nodeName + '.setAlignContent(' + toValueJava(value) + ');');
  }},

  YGNodeStyleSetAlignItems:{value:function(nodeName, value) {
    this.push(nodeName + '.setAlignItems(' + toValueJava(value) + ');');
  }},

  YGNodeStyleSetAlignSelf:{value:function(nodeName, value) {
    this.push(nodeName + '.setAlignSelf(' + toValueJava(value) + ');');
  }},

  YGNodeStyleSetBorder:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setBorder(' + edge + ', ' + toValueJava(value) + 'f);');
  }},

  YGNodeStyleSetDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.setDirection(' + toValueJava(value) + ');');
  }},

  YGNodeStyleSetDisplay:{value:function(nodeName, value) {
    this.push(nodeName + '.setDisplay(' + toValueJava(value) + ');');
  }},

  YGNodeStyleSetFlexBasis:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexBasis' + toMethodName(value) + '(' + toValueJava(value) + 'f);');
  }},

  YGNodeStyleSetFlexDirection:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexDirection(' + toValueJava(value) + ');');
  }},

  YGNodeStyleSetFlexGrow:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexGrow(' + toValueJava(value) + 'f);');
  }},

  YGNodeStyleSetFlexShrink:{value:function(nodeName, value) {
    this.push(nodeName + '.setFlexShrink(' + toValueJava(value) + 'f);');
  }},

  YGNodeStyleSetFlexWrap:{value:function(nodeName, value) {
    this.push(nodeName + '.setWrap(' + toValueJava(value) + ');');
  }},

  YGNodeStyleSetHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setHeight' + toMethodName(value) + '(' + toValueJava(value) + 'f);');
  }},

  YGNodeStyleSetJustifyContent:{value:function(nodeName, value) {
    this.push(nodeName + '.setJustifyContent(' + toValueJava(value) + ');');
  }},

  YGNodeStyleSetMargin:{value:function(nodeName, edge, value) {
    var valueStr = toValueJava(value);
    if (valueStr != 'YogaConstants.AUTO') {
      valueStr = ', ' + valueStr + 'f';
    } else {
      valueStr = '';
    }

    this.push(nodeName + '.setMargin' + toMethodName(value) + '(' + edge + valueStr + ');');
  }},

  YGNodeStyleSetMaxHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setMaxHeight' + toMethodName(value) + '(' + toValueJava(value) + 'f);');
  }},

  YGNodeStyleSetMaxWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setMaxWidth' + toMethodName(value) + '(' + toValueJava(value) + 'f);');
  }},

  YGNodeStyleSetMinHeight:{value:function(nodeName, value) {
    this.push(nodeName + '.setMinHeight' + toMethodName(value) + '(' + toValueJava(value) + 'f);');
  }},

  YGNodeStyleSetMinWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setMinWidth' + toMethodName(value) + '(' + toValueJava(value) + 'f);');
  }},

  YGNodeStyleSetOverflow:{value:function(nodeName, value) {
    this.push(nodeName + '.setOverflow(' + toValueJava(value) + ');');
  }},

  YGNodeStyleSetPadding:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setPadding' + toMethodName(value) + '(' + edge + ', ' + toValueJava(value) + ');');
  }},

  YGNodeStyleSetPosition:{value:function(nodeName, edge, value) {
    this.push(nodeName + '.setPosition' + toMethodName(value) + '(' + edge + ', ' + toValueJava(value) + 'f);');
  }},

  YGNodeStyleSetPositionType:{value:function(nodeName, value) {
    this.push(nodeName + '.setPositionType(' + toValueJava(value) + ');');
  }},

  YGNodeStyleSetWidth:{value:function(nodeName, value) {
    this.push(nodeName + '.setWidth' + toMethodName(value) + '(' + toValueJava(value) + 'f);');
  }},

  YGNodeStyleSetGap:{value:function(nodeName, gap, value) {
    this.push(nodeName + '.setGap' + toMethodName(value) + '(' + gap + ', ' + toValueJava(value) + 'f);');
  }},
});
