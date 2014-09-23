function transpileLayoutEngineToJava(code) {
  return __transpileToJavaCommon(code)
    .replace('node.style.measure', 'node.measure')
    .replace(/\.children\.length/g, '.getChildCount()')
    .replace(/node.children\[i\]/g, 'node.getChildAt(i)')
    .replace(/fmaxf/g, 'Math.max')
    .replace(/\/\*\([^\/]+\*\/\n/g, '') // remove comments for other languages
    .replace(/var\/\*([^\/]+)\*\//g, '$1')
    .replace(/ === /g, ' == ')
    .replace(/\n  /g, '\n')
    .replace(/\/[*]!([^*]+)[*]\//g, '$1')
    .replace(/css_node_t\*/g, 'CSSNode');
}

function transpileCTestsArrayToJava(allTestsInC) {
  var allTestsInJava = [];
  for (var i = 0; i < allTestsInC.length; i++) {
    allTestsInJava[i] =
        "@Test\n" +
        "public void testCase" + i + "()\n" +
        __transpileSingleTestToJava(allTestsInC[i]);
  }
  return allTestsInJava.join('\n\n');
}

function __transpileToJavaCommon(code) {
  return code
    .replace(/CSS_UNDEFINED/g, 'CSSConstants.UNDEFINED')
    .replace(/css_flex_direction_t/g, 'CSSFlexDirection')
    .replace(/CSS_FLEX_DIRECTION_/g, 'CSSFlexDirection.')
    .replace(/css_align_t/g, 'CSSAlign')
    .replace(/CSS_ALIGN_/g, 'CSSAlign.')
    .replace(/CSS_POSITION_/g, 'CSSPositionType.')
    .replace(/css_justify_t/g, 'CSSJustify')
    .replace(/CSS_JUSTIFY_/g, 'CSSJustify.')
    .replace(/css_dim_t/g, 'MeasureOutput')
    .replace(/bool/g, 'boolean')
    .replace(/^(\s+)([^\s]+)\s+\+=/gm, '$1$2 = $2 +') // Expand +=
    .replace(/leading\[([^\]]+)\]/g, 'getLeading($1)')
    .replace(/trailing\[([^\]]+)\]/g, 'getTrailing($1)')
    .replace(/pos\[([^\]]+)\]/g, 'getPos($1)')
    .replace(/dim\[([^\]]+)\]/g, 'getDim($1)')
    .replace(/(\w+)\.layout\[((?:getLeading|getPos)\([^\)]+\))\]\s+=\s+([^;]+);/gm, 'setLayoutPosition($1, $2, $3);')
    .replace(/(\w+)\.layout\[((?:getLeading|getPos)\([^\]]+\))\]/g, 'getLayoutPosition($1, $2)')
    .replace(/(\w+)\.layout\[(getDim\([^\)]+\))\]\s+=\s+([^;]+);/gm, 'setLayoutDimension($1, $2, $3);')
    .replace(/(\w+)\.layout\[(getDim\([^\]]+\))\]/g, 'getLayoutDimension($1, $2)')
    .replace(/(\w+)\.style\[((?:getLeading|getPos)\([^\]]+\))\]/g, 'getStylePosition($1, $2)')
    .replace(/(\w+)\.style\[(getDim\([^\]]+\))\]/g, 'getStyleDimension($1, $2)');
}

function __transpileSingleTestToJava(code) {
  return __transpileToJavaCommon(code)
    .replace(/new_test_css_node/g, 'new TestCSSNode')
    .replace(/(style|layout)\.dimensions\[CSS_(WIDTH|HEIGHT)\]/g, function (str, match1, match2) { return match1 + '.' + match2.toLowerCase(); })
    .replace(/layout\.position\[CSS_(TOP|LEFT)\]/g, function (str, match1) { return 'layout.' + (match1 == 'TOP' ? 'y' : 'x'); })
    .replace(/style\.(position|margin|border|padding)\[CSS_(TOP|BOTTOM|LEFT|RIGHT)\]/g, function (str, match1, match2) { return 'style.' + match1 + match2[0] + match2.substring(1).toLowerCase(); })
    .replace(/get_child\(.*context\,\s([^\)]+)\)/g, 'getChildAt($1)')
    .replace(/init_css_node_children/g, 'addChildren')
    .replace(/measure\s*=\s*measure/g, 'setMeasureFunction(sTestMeasureFunction)')
    .replace(/css_node_t(\s)\*/g, 'TestCSSNode$1')
    .replace(/\->/g, '.')
    .replace(/(\d+\.\d+)/g, '$1f')
    .replace(/style\.([^_\s]+)_(\w)(\w+)/g, function (str, m1, m2, m3) { return 'style.' + m1 + m2.toUpperCase() + m3; });
}