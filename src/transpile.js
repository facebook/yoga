var layoutTestUtils = require('./Layout-test-utils.js');
var computeLayout = require('./Layout.js');
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

global.describe = function(name, cb) { cb(); };
global.it = function(name, cb) { currentTest = name; cb(); };
global.xit = function() { /* ignore skipped tests */ };

require('./__tests__/Layout-test.js');


function printLayout(test) {
  var level = 1;
  var res = [];

  function add(str) {
    if (str.length > 0) {
      str = indent(level) + str;
    }
    res.push(str);
  }

  function isEmpty(obj) {
    for (var key in obj) {
      return false;
    }
    return true;
  }

  function indent(level) {
    var result = '';
    for (var i = 0; i < level; ++i) {
      result += '  ';
    }
    return result;
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
  function rec_style(node) {

    function addStyle(str) {
      add('node_' + (level - 3) + '->style.' + str);
    }

    function addEnum(node, js_key, c_key, dict) {
      if (js_key in node.style) {
        addStyle(c_key + ' = ' + dict[node.style[js_key]] + ';');
      }
    }

    function addFloat(positive, node, js_key, c_key) {
      if (js_key in node.style) {
        if (positive === 'positive' && node.style[js_key] < 0) {
          // do nothing
        } else {
          addStyle(c_key + ' = ' + node.style[js_key] + ';');
        }
      }
    }

    function addSpacing(positive, node, spacing, suffix) {
      addFloat(positive, node, spacing + suffix, spacing + '[CSS_LEFT]');
      addFloat(positive, node, spacing + suffix, spacing + '[CSS_TOP]');
      addFloat(positive, node, spacing + suffix, spacing + '[CSS_RIGHT]');
      addFloat(positive, node, spacing + suffix, spacing + '[CSS_BOTTOM]');

      addFloat(positive, node, spacing + 'Left' + suffix, spacing + '[CSS_LEFT]');
      addFloat(positive, node, spacing + 'Top' + suffix, spacing + '[CSS_TOP]');
      addFloat(positive, node, spacing + 'Right' + suffix, spacing + '[CSS_RIGHT]');
      addFloat(positive, node, spacing + 'Bottom' + suffix, spacing + '[CSS_BOTTOM]');
    }

    function addMeasure(node) {
      if ('measure' in node.style) {
        add('node_' + (level - 3) + '->measure = measure;');
        add('node_' + (level - 3) + '->context = "' + node.style.measure.toString() + '";');
      }
    }

    addEnum(node, 'flexDirection', 'flex_direction', {
      'row': 'CSS_FLEX_DIRECTION_ROW',
      'column': 'CSS_FLEX_DIRECTION_COLUMN'
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
    addFloat('positive', node, 'flex', 'flex');
    addFloat('positive', node, 'width', 'dimensions[CSS_WIDTH]');
    addFloat('positive', node, 'height', 'dimensions[CSS_HEIGHT]');
    addSpacing('all', node, 'margin', '');
    addSpacing('positive', node, 'padding', '');
    addSpacing('positive', node, 'border', 'Width');
    addFloat('all', node, 'left', 'position[CSS_LEFT]');
    addFloat('all', node, 'top', 'position[CSS_TOP]');
    addFloat('all', node, 'right', 'position[CSS_RIGHT]');
    addFloat('all', node, 'bottom', 'position[CSS_BOTTOM]');
    addMeasure(node);

    if (node.children) {
      add('init_css_node_children(node_' + (level - 3) +', ' + node.children.length + ');');
      add('{');
      level++;
      add('css_node_t *node_' + (level - 3) + ';');

      for (var i = 0; i < node.children.length; ++i) {
        add('node_' + (level - 3) + ' = node_' + (level - 4) + '->get_child(node_' + (level - 4) + '->context, ' + i + ');');
        rec_style(node.children[i]);
      }

      level--;
      add('}');
    }
  }
  rec_style(test.node);
  level--;
  add('}');
  add('');

  // Output the expected layout node
  add('css_node_t *root_layout = new_test_css_node();');
  add('{');
  level++;
  add('css_node_t *node_0 = root_layout;');

  function rec_layout(node) {
    function addLayout(str) {
      add('node_' + (level - 3) + '->layout.' + str);
    }

    addLayout('position[CSS_TOP] = ' + node.top + ';');
    addLayout('position[CSS_LEFT] = ' + node.left + ';');
    addLayout('dimensions[CSS_WIDTH] = ' + node.width + ';');
    addLayout('dimensions[CSS_HEIGHT] = ' + node.height + ';');

    if (node.children) {
      add('init_css_node_children(node_' + (level - 3) +', ' + node.children.length + ');');
      add('{');
      level++;
      add('css_node_t *node_' + (level - 3) + ';');

      for (var i = 0; i < node.children.length; ++i) {
        add('node_' + (level - 3) + ' = node_' + (level - 4) + '->get_child(node_' + (level - 4) + '->context, ' + i + ');');
        rec_layout(node.children[i]);
      }

      level--;
      add('}');
    }
  }
  rec_layout(test.expectedLayout);
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
    .replace(/layout\[dim/g, 'layout.dimensions[dim')
    .replace(/layout\[pos/g, 'layout.position[pos')
    .replace(/layout\[leading/g, 'layout.position[leading')
    .replace(/style\[dim/g, 'style.dimensions[dim')
    .replace(/node.children\[i\]/g, 'node->get_child(node->context, i)')
    .replace(/node\./g, 'node->')
    .replace(/child\./g, 'child->')
    .replace(/parent\./g, 'parent->')
    .replace(/var\/\*([^\/]+)\*\//g, '$1')
    .replace(/ === /g, ' == ')
    .replace(/\n  /g, '\n')
    .replace(/\/\*\(c\)!([^*]+)\*\//g, '$1')
    .replace(/\/[*]!([^*]+)[*]\//g, '$1')
    .split('\n').slice(1, -1).join('\n');
}

function makeConstDefs() {
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
