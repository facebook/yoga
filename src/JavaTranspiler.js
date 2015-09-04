/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

function __transpileToJavaCommon(code) {
  return code
    .replace(/CSS_UNDEFINED/g, 'CSSConstants.UNDEFINED')
    .replace(/CSS_JUSTIFY_/g, 'CSSJustify.')
    .replace(/CSS_ALIGN_/g, 'CSSAlign.')
    .replace(/css_flex_direction_t/g, 'CSSFlexDirection')
    .replace(/css_direction_t/g, 'CSSDirection')
    .replace(/css_align_t/g, 'CSSAlign')
    .replace(/css_justify_t/g, 'CSSJustify')
    .replace(/css_dim_t/g, 'MeasureOutput')
    .replace(/bool/g, 'boolean')
    .replace(/style\[dim/g, 'style.dimensions[dim')
    .replace(/(style|layout)\.width/g, '$1.dimensions[DIMENSION_WIDTH]')
    .replace(/(style|layout)\.height/g, '$1.dimensions[DIMENSION_HEIGHT]')
    .replace(/layout\[dim/g, 'layout.dimensions[dim')
    .replace(/layout\[pos/g, 'layout.position[pos')
    .replace(/layout\[leading/g, 'layout.position[leading')
    .replace(/layout\[trailing/g, 'layout.position[trailing')
    .replace(/\/\*\(c\)!([^*]+)\*\//g, '')
    .replace(/var\/\*\(java\)!([^*]+)\*\//g, '$1')
    .replace(/\/\*\(java\)!([^*]+)\*\//g, '$1')
}

function __transpileSingleTestToJava(code) {
  return __transpileToJavaCommon(code)
    .replace(/CSS_DIRECTION_/g, 'CSSDirection.')
    .replace(/CSS_FLEX_DIRECTION_/g, 'CSSFlexDirection.')
    .replace(/CSS_WRAP/g, 'CSSWrap.WRAP')
    .replace(/CSS_POSITION_/g, 'CSSPositionType.')
    .replace(/new_test_css_node/g, 'new TestCSSNode')
    .replace( // style.position[CSS_TOP] => style.position[CSSLayout.POSITION_TOP]
        /(style|layout)\.position\[CSS_(LEFT|TOP|RIGHT|BOTTOM)\]/g,
        function (str, match1, match2) {
            return match1 + '.position[POSITION_' + match2 + ']';
        })
    .replace( // style.dimensions[CSS_WIDTH] => style.dimensions[CSSLayout.DIMENSION_WIDTH]
        /(style|layout)\.dimensions\[CSS_(WIDTH|HEIGHT)\]/g,
        function (str, match1, match2) {
            return match1 + '.dimensions[DIMENSION_' + match2 + ']';
        })
    .replace( // style.maxDimensions[CSS_WIDTH] => style.maxWidth
        /(style|layout)\.maxDimensions\[CSS_(WIDTH|HEIGHT)\]/g,
        function (str, match1, match2) {
            return match1 + '.max' + match2.substr(0, 1).toUpperCase() + match2.substr(1).toLowerCase();
        })
    .replace( // style.minDimensions[CSS_WIDTH] => style.minWidth
        /(style|layout)\.minDimensions\[CSS_(WIDTH|HEIGHT)\]/g,
        function (str, match1, match2) {
            return match1 + '.min' + match2.substr(0, 1).toUpperCase() + match2.substr(1).toLowerCase();
        })
    .replace( // style.margin[CSS_TOP] = 12.3 => style.margin[Spacing.TOP].set(12.3)
        /style\.(margin|border|padding)\[CSS_(TOP|BOTTOM|LEFT|RIGHT|START|END)\]\s+=\s+(-?[\.\d]+)/g,
        function (str, match1, match2, match3) {
          var propertyCap = match1.charAt(0).toUpperCase() + match1.slice(1);
          return 'set' + propertyCap + '(Spacing.' + match2 + ', ' + match3 + ')';
        })
    .replace( // style.margin[CSS_TOP] => style.margin[Spacing.TOP]
        /style\.(margin|border|padding)\[CSS_(TOP|BOTTOM|LEFT|RIGHT|START|END)\]/g,
        function (str, match1, match2) {
          return 'style.' + match1 + '.get(Spacing.' + match2 + ')';
        })
    .replace(/get_child\(.*context\,\s([^\)]+)\)/g, 'getChildAt($1)')
    .replace(/init_css_node_children/g, 'addChildren')
    .replace(/css_node_t(\s)\*/g, 'TestCSSNode$1')
    .replace(/\->/g, '.')
    .replace(/(\d+\.\d+)/g, '$1f')
    .replace( // style.flex_direction => style.flexDirection
        /style\.([^_\[\]\s]+)_(\w)(\w+)/g,
        function (str, match1, match2, match3) {
            return 'style.' + match1 + match2.toUpperCase() + match3;
        })
    .replace(/(\w+)\.measure\s+=\s+.+/, '$1.setMeasureFunction(sTestMeasureFunction);');
}

function indent(code) {
  return code
    .split('\n')
    .map(function(line) { return '  ' + line; })
    .join('\n');
}

var JavaTranspiler = {
  transpileLayoutEngine: function(code) {
    return indent(
      __transpileToJavaCommon(code)
        .replace(/function\s+layoutNode.*/, '')
        .replace('node.style.measure', 'node.measure')
        .replace(/\.children\.length/g, '.getChildCount()')
        .replace(/node.children\[i\]/g, 'node.getChildAt(i)')
        .replace(/node.children\[ii\]/g, 'node.getChildAt(ii)')
        .replace(/fmaxf/g, 'Math.max')
        .replace(/\/\*\([^\/]+\*\/\n/g, '') // remove comments for other languages
        .replace(/var\/\*([^\/]+)\*\//g, '$1')
        .replace(/ === /g, ' == ')
        .replace(/ !== /g, ' != ')
        .replace(/\n {2}/g, '\n')
        .replace(/\/[*]!([^*]+)[*]\//g, '$1')
        .replace(/css_node_t\*/g, 'CSSNode'));
  },

  transpileCConstDefs: function(cConstDefs) {
    return indent(
      cConstDefs
        .replace(/#define\s+(\w+)\s+(\"[^\"]+\")/g, 'public static final String $1 = $2;')
        .replace(/#define\s+(\w+)\s+(.+)/g, 'public static final float $1 = $2f;'));
  },

  transpileCTestsArray: function(allTestsInC) {
    var allTestsInJava = [];
    for (var i = 0; i < allTestsInC.length; i++) {
      allTestsInJava[i] =
          '  @Test\n' +
          '  public void testCase' + i + '()\n' +
          __transpileSingleTestToJava(allTestsInC[i]);
    }
    return allTestsInJava.join('\n\n');
  }
};

if (typeof module !== 'undefined') {
  module.exports = JavaTranspiler;
}
