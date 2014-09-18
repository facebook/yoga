function transpileLayoutEngineToJava(code) {
  return __transpileToJavaCommon(code)
    .replace('node.style.measure', 'node.measure')
    .replace(/\.children\.length/g, '.getChildCount()')
    .replace(/node.children\[i\]/g, 'node.getChildAt(i)')
    .replace(/\.(layout|style)\.width/g, '.$1.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH]')
    .replace(/\.(layout|style)\.height/g, '.$1.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT]')
    .replace(/fmaxf/g, 'Math.max')
    .replace(/layout\[dim/g, 'layout.dimensions[dim')
    .replace(/layout\[pos/g, 'layout.position[pos')
    .replace(/layout\[leading/g, 'layout.position[leading')
    .replace(/style\[dim/g, 'style.dimensions[dim')
    .replace(/\/\*\([^\/]+\*\/\n/g, '') // remove comments for other languages
    .replace(/var\/\*([^\/]+)\*\//g, '$1')
    .replace(/leading\[([^\]]+)\]/g, 'getLeading($1)')
    .replace(/trailing\[([^\]]+)\]/g, 'getTrailing($1)')
    .replace(/pos\[([^\]]+)\]/g, 'getPos($1)')
    .replace(/dim\[([^\]]+)\]/g, 'getDim($1)')
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
    .replace(/bool/g, 'boolean');
}

function __transpileSingleTestToJava(code) {
  return __transpileToJavaCommon(code)
    .replace(/new_test_css_node/g, 'new TestCSSNode')
    .replace(/CSS_(WIDTH|HEIGHT)/g, 'CSSConstants.DIMENSION_INDEX_$1')
    .replace(/CSS_(TOP|BOTTOM|LEFT|RIGHT)/g, 'CSSConstants.POSITION_INDEX_$1')
    .replace(/get_child\(.*context\,\s([^\)]+)\)/g, 'getChildAt($1)')
    .replace(/init_css_node_children/g, 'addChildren')
    .replace(/measure\s*=\s*measure/g, 'setMeasureFunction(sTestMeasureFunction)')
    .replace(/css_node_t(\s)\*/g, 'TestCSSNode$1')
    .replace(/\->/g, '.')
    .replace(/(\d+\.\d+)/g, '$1f');
}