/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

function __transpileToCSharpCommon(code) {
  return code
    .replace(/CSS_UNDEFINED/g, 'CSSConstants.UNDEFINED')
    .replace(/CSS_JUSTIFY_/g, 'CSSJustify.')
    .replace(/CSS_ALIGN_/g, 'CSSAlign.')
    .replace(/CSS_POSITION_/g, 'CSSPositionType.')
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
    .replace(/getPositionType\((.+?)\)/g, '$1.style.positionType')
    .replace(/getJustifyContent\((.+?)\)/g, '$1.style.justifyContent')
    .replace(/getAlignContent\((.+?)\)/g, '$1.style.alignContent')
    .replace(/isPosDefined\((.+?),\s*(.+?)\)/g, '!isUndefined\($1.style.position[$2]\)')
    .replace(/isDimDefined\((.+?),\s*(.+?)\)/g, '\(!isUndefined\($1.style.dimensions[dim[$2]]\) && $1.style.dimensions[dim[$2]] >= 0.0\)')
    .replace(/getPosition\((.+?),\s*(.+?)\)/g, '\(isUndefined\($1.style.position[$2]\) ?  0 : $1.style.position[$2]\)')
    .replace(/setTrailingPosition\((.+?),\s*(.+?),\s*(.+?)\)/g, '$2.layout.position[trailing[$3]] = $1.layout.dimensions[dim[$3]] - $2.layout.dimensions[dim[$3]] - $2.layout.position[pos[$3]]')
    .replace(/isFlex\((.+?)\)/g, '\($1.style.positionType == CSSPositionType.RELATIVE && $1.style.flex > 0\)')
    .replace(/isFlexWrap\((.+?)\)/g, '\($1.style.flexWrap == CSSWrap.WRAP\)')
    .replace(/getPaddingAndBorderAxis\((.+?),\s*(.+?)\)/g, '\(getLeadingPaddingAndBorder($1, $2) + getTrailingPaddingAndBorder($1, $2)\)')
    .replace(/getBorderAxis\((.+?),\s*(.+?)\)/g, '\(getLeadingBorder($1, $2) + getTrailingBorder($1, $2)\)')
    .replace(/getMarginAxis\((.+?),\s*(.+?)\)/g, '\(getLeadingMargin($1, $2) + getTrailingMargin($1, $2)\)')
    .replace(/getLeadingPaddingAndBorder\((.+?),\s*(.+?)\)/g, '\(getLeadingPadding($1, $2) + getLeadingBorder($1, $2)\)')
    .replace(/getTrailingPaddingAndBorder\((.+?),\s*(.+?)\)/g, '\(getTrailingPadding($1, $2) + getTrailingBorder($1, $2)\)')
    .replace(/getDimWithMargin\((.+?),\s*(.+?)\)/g, '\($1.layout.dimensions[dim[$2]] + getLeadingMargin($1, $2) + getTrailingMargin($1, $2)\)')
    .replace(/getLeadingMargin\((.+?),\s*(.+?)\)/g, '$1.style.margin.getWithFallback(leadingSpacing[$2], leading[$2])')
    .replace(/getTrailingMargin\((.+?),\s*(.+?)\)/g, '$1.style.margin.getWithFallback(trailingSpacing[$2], trailing[$2])')
    .replace(/getLeadingPadding\((.+?),\s*(.+?)\)/g, '$1.style.padding.getWithFallback(leadingSpacing[$2], leading[$2])')
    .replace(/getTrailingPadding\((.+?),\s*(.+?)\)/g, '$1.style.padding.getWithFallback(trailingSpacing[$2], trailing[$2])')
    .replace(/getLeadingBorder\((.+?),\s*(.+?)\)/g, '$1.style.border.getWithFallback(leadingSpacing[$2], leading[$2])')
    .replace(/getTrailingBorder\((.+?),\s*(.+?)\)/g, '$1.style.border.getWithFallback(trailingSpacing[$2], trailing[$2])')
    .replace(/isRowDirection\((.+?)\)/g, '\($1 == CSS_FLEX_DIRECTION_ROW || $1 == CSS_FLEX_DIRECTION_ROW_REVERSE\)')
    .replace(/isUndefined\((.+?)\)/g, 'float.IsNaN\($1\)')
    .replace(/\/\*\(c\)!([^*]+)\*\//g, '')
    .replace(/var\/\*\(java\)!([^*]+)\*\//g, '$1')
    .replace(/\/\*\(java\)!([^*]+)\*\//g, '$1')

    // additional case conversions

    .replace(/(CSSConstants|CSSWrap|CSSJustify|CSSAlign|CSSPositionType)\.([_A-Z]+)/g,
        function(str, match1, match2) {
          return match1 + '.' + constantToPascalCase(match2);
        });
}

function __transpileSingleTestToCSharp(code) {
  return __transpileToCSharpCommon(code)
 .replace(/CSS_DIRECTION_/g, 'CSSDirection.')
    .replace(/CSS_FLEX_DIRECTION_/g, 'CSSFlexDirection.')
    .replace(/CSS_WRAP/g, 'CSSWrap.WRAP')
    .replace(/new_test_css_node/g, 'new TestCSSNode')
    .replace(// style.position[CSS_TOP] => style.position[CSSLayout.POSITION_TOP]
        /(style|layout)\.position\[CSS_(LEFT|TOP|RIGHT|BOTTOM)\]/g,
        function(str, match1, match2) {
          return match1 + '.position[POSITION_' + match2 + ']';
        })
    .replace(// style.dimensions[CSS_WIDTH] => style.dimensions[CSSLayout.DIMENSION_WIDTH]
        /(style|layout)\.dimensions\[CSS_(WIDTH|HEIGHT)\]/g,
        function(str, match1, match2) {
          return match1 + '.dimensions[DIMENSION_' + match2 + ']';
        })
    .replace(// style.maxDimensions[CSS_WIDTH] => style.maxWidth
        /(style|layout)\.maxDimensions\[CSS_(WIDTH|HEIGHT)\]/g,
        function(str, match1, match2) {
          return match1 + '.max' + match2.substr(0, 1).toUpperCase() + match2.substr(1).toLowerCase();
        })
    .replace(// style.minDimensions[CSS_WIDTH] => style.minWidth
        /(style|layout)\.minDimensions\[CSS_(WIDTH|HEIGHT)\]/g,
        function(str, match1, match2) {
          return match1 + '.min' + match2.substr(0, 1).toUpperCase() + match2.substr(1).toLowerCase();
        })
    .replace(// style.margin[CSS_TOP] = 12.3 => style.margin[Spacing.TOP].set(12.3)
        /style\.(margin|border|padding)\[CSS_(TOP|BOTTOM|LEFT|RIGHT|START|END)\]\s+=\s+(-?[\.\d]+)/g,
        function(str, match1, match2, match3) {
          var propertyCap = match1.charAt(0).toUpperCase() + match1.slice(1);
          return 'set' + propertyCap + '(Spacing.' + match2 + ', ' + match3 + ')';
        })
    .replace(// style.margin[CSS_TOP] => style.margin[Spacing.TOP]
        /style\.(margin|border|padding)\[CSS_(TOP|BOTTOM|LEFT|RIGHT|START|END)\]/g,
        function(str, match1, match2) {
          return 'style.' + match1 + '.get(Spacing.' + match2 + ')';
        })
    .replace(/get_child\(.*context\,\s([^\)]+)\)/g, 'getChildAt($1)')
    .replace(/init_css_node_children/g, 'addChildren')
    .replace(/css_node_t(\s)\*/g, 'TestCSSNode$1')
    .replace(/\->/g, '.')
    .replace(/(\d+\.\d+)/g, '$1f')
    .replace(// style.flex_direction => style.flexDirection
        /style\.([^_\[\]\s]+)_(\w)(\w+)/g,
        function(str, match1, match2, match3) {
          return 'style.' + match1 + match2.toUpperCase() + match3;
        })
    .replace(/(\w+)\.measure\s+=\s+.+/, '$1.setMeasureFunction(sTestMeasureFunction);')

    // additional case conversions

    .replace(/(CSSWrap|CSSFlexDirection)\.([_A-Z]+)/g,
        function(str, match1, match2) {
          return match1 + '.' + constantToPascalCase(match2);
        });
}

function indent(code) {
  return code
    .split('\n')
    .map(function(line) { return '    ' + line; })
    .join('\n');
}

function constantToPascalCase(str) {
  return str[0] + str.substr(1)
    .toLowerCase()
    .replace(/_(.)/g,
      function(_, m) { return m.toUpperCase(); });
}

var CSharpTranspiler = {
  transpileLayoutEngine: function(code) {
    return indent(
      __transpileToCSharpCommon(code)
        .replace(/function\s+layoutNode.*/, '')
        .replace('node.style.measure', 'node.measure')
        .replace(/\.children\.length/g, '.getChildCount()')
        .replace(/node.children\[i\]/g, 'node.getChildAt(i)')
        .replace(/node.children\[ii\]/g, 'node.getChildAt(ii)')
        .replace(/fmaxf/g, 'Math.Max')
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
        .replace(/#define\s+(\w+)\s+(\"[^\"]+\")/g, 'public static readonly string $1 = $2;')
        .replace(/#define\s+(\w+)\s+(.+)/g, 'public static readonly float $1 = $2f;'));
  },

  transpileCTestsArray: function(allTestsInC) {
    var allTestsInCSharp = [];
    for (var i = 0; i < allTestsInC.length; i++) {
      allTestsInCSharp[i] =
          '    [Test]\n' +
          '    public void TestCase' + i + '()\n' +
          __transpileSingleTestToCSharp(allTestsInC[i]);
    }
    return allTestsInCSharp.join('\n\n');
  }
};

if (typeof module !== 'undefined') {
  module.exports = CSharpTranspiler;
}
