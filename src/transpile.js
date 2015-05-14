/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var layoutTestUtils = require('./Layout-test-utils.js');
var computeLayout = require('./Layout.js').computeLayout;
var fs = require('fs');
var JavaTranspiler = require('./JavaTranspiler.js');

var currentTest = '';
var allTests = [];
var computeDOMLayout = layoutTestUtils.computeDOMLayout;
var reduceTest = layoutTestUtils.reduceTest;
global.layoutTestUtils = {
  testLayout: function(node, expectedLayout) {
    allTests.push({name: currentTest, node: node, expectedLayout: expectedLayout});
  },
  testRandomLayout: function(node, i) {
    allTests.push({name: 'Random #' + i, node: node, expectedLayout: computeDOMLayout(node)});
  },
  computeLayout: layoutTestUtils.computeLayout,
  reduceTest: reduceTest,
  text: layoutTestUtils.text,
  texts: layoutTestUtils.texts,
  textSizes: layoutTestUtils.textSizes
};

global.describe = function(name, cb) {
  if (name === 'Layout') {
    cb();
  }
};
global.it = function(name, cb) { currentTest = name; cb(); };
global.xit = function() { /* ignore skipped tests */ };

require('./__tests__/Layout-test.js');


function printLayout(test) {
  var level = 1;
  var res = [];

  function indent(level) {
    var result = '';
    for (var i = 0; i < level; ++i) {
      result += '  ';
    }
    return result;
  }

  function add(str) {
    if (str.length > 0) {
      str = indent(level) + str;
    }
    res.push(str);
  }

  function isEmpty(obj) {
    return !Object.keys(obj).length;
  }

  add('{');
  level++;

  // Output the style node
  add('css_node_t *root_node = new_test_css_node();');
  add('{');
  level++;
  if (!isEmpty(test.node.style) || test.node.children && test.node.children.length) {
    add('css_node_t *node_0 = root_node;');
  }
  function recStyle(node) {

    function addStyle(str) {
      add('node_' + (level - 3) + '->style.' + str);
    }

    function addEnum(node, jsKey, cKey, dict) {
      if (jsKey in node.style) {
        addStyle(cKey + ' = ' + dict[node.style[jsKey]] + ';');
      }
    }

    function addFloat(node, jsKey, cKey) {
      if (jsKey in node.style) {
        addStyle(cKey + ' = ' + node.style[jsKey] + ';');
      }
    }

    function addSpacing(node, spacing, suffix) {
      addFloat(node, spacing + suffix, spacing + '[CSS_LEFT]');
      addFloat(node, spacing + suffix, spacing + '[CSS_TOP]');
      addFloat(node, spacing + suffix, spacing + '[CSS_RIGHT]');
      addFloat(node, spacing + suffix, spacing + '[CSS_BOTTOM]');
      addFloat(node, spacing + suffix, spacing + '[CSS_START]');
      addFloat(node, spacing + suffix, spacing + '[CSS_END]');

      addFloat(node, spacing + 'Left' + suffix, spacing + '[CSS_LEFT]');
      addFloat(node, spacing + 'Top' + suffix, spacing + '[CSS_TOP]');
      addFloat(node, spacing + 'Right' + suffix, spacing + '[CSS_RIGHT]');
      addFloat(node, spacing + 'Bottom' + suffix, spacing + '[CSS_BOTTOM]');
      addFloat(node, spacing + 'Start' + suffix, spacing + '[CSS_START]');
      addFloat(node, spacing + 'End' + suffix, spacing + '[CSS_END]');
    }

    function addMeasure(node) {
      if ('measure' in node.style) {
        add('node_' + (level - 3) + '->measure = measure;');
        add('node_' + (level - 3) + '->context = "' + node.style.measure.toString() + '";');
      }
    }

    addEnum(node, 'direction', 'direction', {
      'ltr': 'CSS_DIRECTION_LTR',
      'rtl': 'CSS_DIRECTION_RTL'
    });
    addEnum(node, 'flexDirection', 'flex_direction', {
      'row': 'CSS_FLEX_DIRECTION_ROW',
      'row-reverse': 'CSS_FLEX_DIRECTION_ROW_REVERSE',
      'column': 'CSS_FLEX_DIRECTION_COLUMN',
      'column-reverse': 'CSS_FLEX_DIRECTION_COLUMN_REVERSE'
    });
    addEnum(node, 'justifyContent', 'justify_content', {
      'flex-start': 'CSS_JUSTIFY_FLEX_START',
      'center': 'CSS_JUSTIFY_CENTER',
      'flex-end': 'CSS_JUSTIFY_FLEX_END',
      'space-between': 'CSS_JUSTIFY_SPACE_BETWEEN',
      'space-around': 'CSS_JUSTIFY_SPACE_AROUND'
    });
    addEnum(node, 'alignItems', 'align_items', {
      'flex-start': 'CSS_ALIGN_FLEX_START',
      'center': 'CSS_ALIGN_CENTER',
      'flex-end': 'CSS_ALIGN_FLEX_END',
      'stretch': 'CSS_ALIGN_STRETCH'
    });
    addEnum(node, 'alignSelf', 'align_self', {
      'flex-start': 'CSS_ALIGN_FLEX_START',
      'center': 'CSS_ALIGN_CENTER',
      'flex-end': 'CSS_ALIGN_FLEX_END',
      'stretch': 'CSS_ALIGN_STRETCH'
    });
    addEnum(node, 'position', 'position_type', {
      'relative': 'CSS_POSITION_RELATIVE',
      'absolute': 'CSS_POSITION_ABSOLUTE'
    });
    addEnum(node, 'flexWrap', 'flex_wrap', {
      'nowrap': 'CSS_NOWRAP',
      'wrap': 'CSS_WRAP'
    });
    addFloat(node, 'flex', 'flex');
    addFloat(node, 'width', 'dimensions[CSS_WIDTH]');
    addFloat(node, 'height', 'dimensions[CSS_HEIGHT]');
    addFloat(node, 'maxWidth', 'maxDimensions[CSS_WIDTH]');
    addFloat(node, 'maxHeight', 'maxDimensions[CSS_HEIGHT]');
    addFloat(node, 'minWidth', 'minDimensions[CSS_WIDTH]');
    addFloat(node, 'minHeight', 'minDimensions[CSS_HEIGHT]');
    addSpacing(node, 'margin', '');
    addSpacing(node, 'padding', '');
    addSpacing(node, 'border', 'Width');
    addFloat(node, 'left', 'position[CSS_LEFT]');
    addFloat(node, 'top', 'position[CSS_TOP]');
    addFloat(node, 'right', 'position[CSS_RIGHT]');
    addFloat(node, 'bottom', 'position[CSS_BOTTOM]');
    addMeasure(node);

    if (node.children) {
      add('init_css_node_children(node_' + (level - 3) + ', ' + node.children.length + ');');
      add('{');
      level++;
      add('css_node_t *node_' + (level - 3) + ';');

      for (var i = 0; i < node.children.length; ++i) {
        add('node_' + (level - 3) + ' = node_' + (level - 4) + '->get_child(node_' + (level - 4) + '->context, ' + i + ');');
        recStyle(node.children[i]);
      }

      level--;
      add('}');
    }
  }
  recStyle(test.node);
  level--;
  add('}');
  add('');

  // Output the expected layout node
  add('css_node_t *root_layout = new_test_css_node();');
  add('{');
  level++;
  add('css_node_t *node_0 = root_layout;');

  function recLayout(node) {
    function addLayout(str) {
      add('node_' + (level - 3) + '->layout.' + str);
    }

    addLayout('position[CSS_TOP] = ' + node.top + ';');
    addLayout('position[CSS_LEFT] = ' + node.left + ';');
    addLayout('dimensions[CSS_WIDTH] = ' + node.width + ';');
    addLayout('dimensions[CSS_HEIGHT] = ' + node.height + ';');

    if (node.children) {
      add('init_css_node_children(node_' + (level - 3) + ', ' + node.children.length + ');');
      add('{');
      level++;
      add('css_node_t *node_' + (level - 3) + ';');

      for (var i = 0; i < node.children.length; ++i) {
        add('node_' + (level - 3) + ' = node_' + (level - 4) + '->get_child(node_' + (level - 4) + '->context, ' + i + ');');
        recLayout(node.children[i]);
      }

      level--;
      add('}');
    }
  }
  recLayout(test.expectedLayout);
  level--;
  add('}');
  add('');

  // Do the test
  add('test("' + test.name.replace(/"/g, '\\"') + '", root_node, root_layout);');
  level--;
  add('}');
  return res.join('\n');
}

function transpileAnnotatedJStoC(jsCode) {
  return jsCode
    .replace('node.style.measure', 'node.measure')
    .replace(/\.children\.length/g, '.children_count')
    .replace(/\.width/g, '.dimensions[CSS_WIDTH]')
    .replace(/\.height/g, '.dimensions[CSS_HEIGHT]')
    .replace(/\.maxWidth/g, '.maxDimensions[CSS_WIDTH]')
    .replace(/\.maxHeight/g, '.maxDimensions[CSS_HEIGHT]')
    .replace(/\.minWidth/g, '.minDimensions[CSS_WIDTH]')
    .replace(/\.minHeight/g, '.minDimensions[CSS_HEIGHT]')
    .replace(/layout\[dim/g, 'layout.dimensions[dim')
    .replace(/layout\[pos/g, 'layout.position[pos')
    .replace(/layout\[leading/g, 'layout.position[leading')
    .replace(/layout\[trailing/g, 'layout.position[trailing')
    .replace(/style\[dim/g, 'style.dimensions[dim')
    .replace(/node.children\[i\]/g, 'node->get_child(node->context, i)')
    .replace(/node\./g, 'node->')
    .replace(/child\./g, 'child->')
    .replace(/parent\./g, 'parent->')
    .replace(/var\/\*([^\/]+)\*\//g, '$1')
    .replace(/ === /g, ' == ')
    .replace(/ !== /g, ' != ')
    .replace(/\n {2}/g, '\n')
    .replace(/\/\*\(c\)!([^*]+)\*\//g, '$1')
    .replace(/\/[*]!([^*]+)[*]\//g, '$1')
    .replace(/\/\*\(java\)!([^*]+)\*\//g, '')
    .split('\n').slice(1, -1).join('\n');
}

function makeConstDefs() {
  /* eslint no-multi-spaces: 3 */
  var lines = [
    '#define SMALL_WIDTH '   + layoutTestUtils.textSizes.smallWidth,
    '#define SMALL_HEIGHT '  + layoutTestUtils.textSizes.smallHeight,
    '#define BIG_WIDTH '     + layoutTestUtils.textSizes.bigWidth,
    '#define BIG_HEIGHT '    + layoutTestUtils.textSizes.bigHeight,
    '#define BIG_MIN_WIDTH ' + layoutTestUtils.textSizes.bigMinWidth,
    '#define SMALL_TEXT "'   + layoutTestUtils.texts.small + '"',
    '#define LONG_TEXT "'    + layoutTestUtils.texts.big + '"'
  ];
  return lines.join('\n');
}

function generateFile(fileName, generatedContent) {
  var content = fs.readFileSync(fileName, 'utf8').toString();
  content = content.replace(new RegExp(
    /\/\*\* START_GENERATED \*\*\/[\s\S]*\/\*\* END_GENERATED \*\*\//
  ), '/** START_GENERATED **/\n' + generatedContent + '\n  /** END_GENERATED **/');

  fs.writeFileSync(fileName, content);
}


var allTestsInC = allTests.map(printLayout);
generateFile(__dirname + '/__tests__/Layout-test.c', allTestsInC.join('\n\n'));
generateFile(__dirname + '/Layout-test-utils.c', makeConstDefs());
generateFile(__dirname + '/Layout.c', transpileAnnotatedJStoC(computeLayout.toString()));
generateFile(__dirname + '/java/src/com/facebook/csslayout/LayoutEngine.java', JavaTranspiler.transpileLayoutEngine(computeLayout.toString()));
generateFile(__dirname + '/java/tests/com/facebook/csslayout/TestConstants.java', JavaTranspiler.transpileCConstDefs(makeConstDefs()));
generateFile(__dirname + '/java/tests/com/facebook/csslayout/LayoutEngineTest.java', JavaTranspiler.transpileCTestsArray(allTestsInC));
