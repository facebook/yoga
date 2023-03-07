/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

const PythonEmitter = function () {
  Emitter.call(this, 'python', '  ');
};

function toValuePython(value) {
  if (value === 'yoga.AUTO') return 'auto';
  var n = value.toString().replace('px','').replace('%','');
  return n + (Number(n) == n && n % 1 !== 0 ? '' : '');
}

function toPythonMethodName(value) {
  if (value.indexOf('%') >= 0){
    return '_percent';
  } else if(value.indexOf('AUTO') >= 0) {
    return '_auto';
  }
  return '';
}

function toPythonUpper(symbol) {
  let out = '';
  for (let i = 0; i < symbol.length; i++) {
    const c = symbol.charAt(i);
    if (c == c.toUpperCase() && i != 0 && symbol[i - 1] != symbol[i - 1].toUpperCase()) {
      out += '_';
    }
    out += c.toUpperCase();
  }
  return out;
}

PythonEmitter.prototype = Object.create(Emitter.prototype, {
  constructor: { value: PythonEmitter },

  emitPrologue: {
    value: function () {
      this.push('import pytest');
      this.push('import yoga');
      this.push('');
    }
  },

  emitTestPrologue: {
    value: function (name, experiments) {
      this.push('');
      this.push('def test_' + name + '():');
      this.pushIndent();
      this.pushIndent();
      this.push('config = yoga.Config()');
      this.push('');

      if (experiments.length > 0) {
        for (const experiment of experiments) {
          this.push('config.set_experimental_feature_enabled(yoga.EXPERIMENTAL_FEATURE_' + toPythonUpper(experiment) + ', True)');
        }
        this.push('');
      }
    }
  },

  emitTestTreePrologue: {
    value: function (nodeName) {
      if (nodeName === 'root') {
        this.push(`root = yoga.Node(config)`);
      } else {
        this.push(`${nodeName} = yoga.Node(config)`);
      }
    }
  },

  emitTestEpilogue: {
    value: function (experiments) {
      this.popIndent();
      this.popIndent();
      this.push('');
    }
  },

  emitEpilogue: {
    value: function () {
      this.push('');
    }
  },

  AssertEQ: {
    value: function (v0, v1) {
      this.push(`assert ${v1} == ${v0}`);
    }
  },

  YGAlignAuto: { value: 'yoga.ALIGN_AUTO' },
  YGAlignCenter: { value: 'yoga.ALIGN_CENTER' },
  YGAlignFlexEnd: { value: 'yoga.ALIGN_FLEX_END' },
  YGAlignFlexStart: { value: 'yoga.ALIGN_FLEX_START' },
  YGAlignStretch: { value: 'yoga.ALIGN_STRETCH' },
  YGAlignSpaceBetween: { value: 'yoga.ALIGN_SPACE_BETWEEN' },
  YGAlignSpaceAround: { value: 'yoga.ALIGN_SPACE_AROUND' },
  YGAlignBaseline: { value: 'yoga.ALIGN_BASELINE' },

  YGDirectionInherit: { value: 'yoga.DIRECTION_INHERIT' },
  YGDirectionLTR: { value: 'yoga.DIRECTION_LTR' },
  YGDirectionRTL: { value: 'yoga.DIRECTION_RTL' },

  YGEdgeBottom: { value: 'yoga.EDGE_BOTTOM' },
  YGEdgeEnd: { value: 'yoga.EDGE_END' },
  YGEdgeLeft: { value: 'yoga.EDGE_LEFT' },
  YGEdgeRight: { value: 'yoga.EDGE_RIGHT' },
  YGEdgeStart: { value: 'yoga.EDGE_START' },
  YGEdgeTop: { value: 'yoga.EDGE_TOP' },

  YGGutterAll: { value: 'yoga.GUTTER_ALL' },
  YGGutterColumn: { value: 'yoga.GUTTER_COLUMN' },
  YGGutterRow: { value: 'yoga.GUTTER_ROW' },

  YGFlexDirectionColumn: { value: 'yoga.FLEX_DIRECTION_COLUMN' },
  YGFlexDirectionColumnReverse: { value: 'yoga.FLEX_DIRECTION_COLUMN_REVERSE' },
  YGFlexDirectionRow: { value: 'yoga.FLEX_DIRECTION_ROW' },
  YGFlexDirectionRowReverse: { value: 'yoga.FLEX_DIRECTION_ROW_REVERSE' },

  YGJustifyCenter: { value: 'yoga.JUSTIFY_CENTER' },
  YGJustifyFlexEnd: { value: 'yoga.JUSTIFY_FLEX_END' },
  YGJustifyFlexStart: { value: 'yoga.JUSTIFY_FLEX_START' },
  YGJustifySpaceAround: { value: 'yoga.JUSTIFY_SPACE_AROUND' },
  YGJustifySpaceBetween: { value: 'yoga.JUSTIFY_SPACE_BETWEEN' },
  YGJustifySpaceEvenly: { value: 'yoga.JUSTIFY_SPACE_EVENLY' },

  YGOverflowHidden: { value: 'yoga.OVERFLOW_HIDDEN' },
  YGOverflowVisible: { value: 'yoga.OVERFLOW_VISIBLE' },

  YGPositionTypeAbsolute: { value: 'yoga.POSITION_TYPE_ABSOLUTE' },
  YGPositionTypeRelative: { value: 'yoga.POSITION_TYPE_RELATIVE' },

  YGAuto: { value: 'yoga.AUTO' },

  YGWrapNoWrap: { value: 'yoga.WRAP_NO_WRAP' },
  YGWrapWrap: { value: 'yoga.WRAP_WRAP' },
  YGWrapWrapReverse: { value: 'yoga.WRAP_WRAP_REVERSE' },

  YGUndefined: { value: 'float("nan")' },

  YGDisplayFlex: { value: 'yoga.DISPLAY_FLEX' },
  YGDisplayNone: { value: 'yoga.DISPLAY_NONE' },

  YGNodeCalculateLayout: {
    value: function (node, dir, experiments) {
      this.push(node + '.calculate_layout(float("nan"), float("nan"), ' + dir + ');');
    }
  },

  YGNodeInsertChild: {
    value: function (parentName, nodeName, index) {
      this.push(parentName + '.insert_child(' + nodeName + ', ' + index + ')');
    }
  },

  YGNodeLayoutGetLeft: {
    value: function (nodeName) {
      return nodeName + '.get_computed_left()';
    }
  },

  YGNodeLayoutGetTop: {
    value: function (nodeName) {
      return nodeName + '.get_computed_top()';
    }
  },

  YGNodeLayoutGetWidth: {
    value: function (nodeName) {
      return nodeName + '.get_computed_width()';
    }
  },

  YGNodeLayoutGetHeight: {
    value: function (nodeName) {
      return nodeName + '.get_computed_height()';
    }
  },

  YGNodeStyleSetAlignContent: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_align_content(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetAlignItems: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_align_items(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetAlignSelf: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_align_self(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetBorder: {
    value: function (nodeName, edge, value) {
      this.push(nodeName + '.set_border(' + toValuePython(edge) + ', ' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetDirection: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_direction(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetDisplay: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_display(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetFlexBasis: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_flex_basis' + toPythonMethodName(value) + '(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetFlexDirection: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_flex_direction(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetFlexGrow: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_flex_grow(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetFlexShrink: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_flex_shrink(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetFlexWrap: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_flex_wrap(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetHeight: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_height' + toPythonMethodName(value) + '(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetJustifyContent: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_justify_content(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetMargin: {
    value: function (nodeName, edge, value) {
      var params = [edge];
      var valueStr = toValuePython(value);
      if (valueStr !== 'auto') {
        params.push(valueStr);
      }
      this.push(nodeName + '.set_margin' + toPythonMethodName(value) + '(' + params.join(', ') + ')');
    }
  },

  YGNodeStyleSetMaxHeight: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_max_height' + toPythonMethodName(value) + '(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetMaxWidth: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_max_width' + toPythonMethodName(value) + '(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetMinHeight: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_min_height' + toPythonMethodName(value) + '(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetMinWidth: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_min_width' + toPythonMethodName(value) + '(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetOverflow: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_overflow(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetPadding: {
    value: function (nodeName, edge, value) {
      this.push(nodeName + '.set_padding' + toPythonMethodName(value) + '(' + toValuePython(edge) + ', ' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetPosition: {
    value: function (nodeName, edge, value) {
      this.push(nodeName + '.set_position' + toPythonMethodName(value) + '(' + toValuePython(edge) + ', ' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetPositionType: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_position_type(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetWidth: {
    value: function (nodeName, value) {
      this.push(nodeName + '.set_width' + toPythonMethodName(value) + '(' + toValuePython(value) + ')');
    }
  },

  YGNodeStyleSetGap: {
    value: function (nodeName, gap, value) {
      this.push(nodeName + '.set_gap' + toPythonMethodName(value) + '(' + toValuePython(gap) + ', ' + toValuePython(value) + ')');
    }
  },
});
