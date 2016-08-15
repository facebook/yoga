/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

window.onload = function() {
 printTest("INSERT_NAME_HERE", calculateTree(document.body.children[0]));
}

function printTest(testName, layoutTree) {
  var lines = [
    '/**',
    ' * Copyright (c) 2014-present, Facebook, Inc.',
    ' * All rights reserved.',
    ' *',
    ' * This source code is licensed under the BSD-style license found in the',
    ' * LICENSE file in the root directory of this source tree. An additional grant',
    ' * of patent rights can be found in the PATENTS file in the same directory.',
    ' */',
    '',
    '#include <CSSLayout/CSSLayout-internal.h>',
    '#include <CSSLayoutTestUtils/CSSLayoutTestUtils.h>',
    '#include <gtest/gtest.h>',
    '',
    'TEST(CSSLayoutTest, ' + testName + ') {',
  ];

  lines.push('  ' + setupTestTree(layoutTree[0], 'root', null).reduce(function(curr, prev) {
    return curr + '\n  ' + prev;
  }));

  lines.push('  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);');
  lines.push('');

  lines.push('  ' + assertTestTree(layoutTree[0], 'root', null).reduce(function(curr, prev) {
    return curr + '\n  ' + prev;
  }));

  lines.push('}');
  lines.push('');

  printLines(lines);
}

function assertTestTree(node, nodeName, parentName) {
  var lines = [
    'ASSERT_EQ(' + node.left + ', CSSNodeLayoutGetLeft(' + nodeName + '));',
    'ASSERT_EQ(' + node.top + ', CSSNodeLayoutGetTop(' + nodeName + '));',
    'ASSERT_EQ(' + node.width + ', CSSNodeLayoutGetWidth(' + nodeName + '));',
    'ASSERT_EQ(' + node.height + ', CSSNodeLayoutGetHeight(' + nodeName + '));',
  ];

  for (var i = 0; i < node.children.length; i++) {
    lines.push('');
    var childName = nodeName + '_child' + i;
    lines = lines.concat(assertTestTree(node.children[i], childName, nodeName));
  }

  return lines;
}

function setupTestTree(node, nodeName, parentName, index) {
  var lines = [
    'CSSNodeRef ' + nodeName + ' = CSSNodeNew();',
  ];

  for (var style in node.style) {
    if (node.style[style] !== getDefaultStyleValue(style)) {
      var TODO = '';
      switch (style) {
        case 'direction':
          lines.push('CSSNodeSetDirection(' + nodeName + ', ' +
              directionValue(node.style[style]) + ');');
          break;
        case 'flex-direction':
          lines.push('CSSNodeStyleSetFlexDirection(' + nodeName + ', ' +
              flexDirectionValue(node.style[style]) + ');');
          break;
        case 'justify-content':
          lines.push('CSSNodeStyleSetJustifyContent(' + nodeName + ', ' +
              justifyValue(node.style[style]) + ');');
          break;
        case 'align-content':
          lines.push('CSSNodeStyleSetAlignContent(' + nodeName + ', ' +
              alignValue(node.style[style]) + ');');
          break;
        case 'align-items':
          lines.push('CSSNodeStyleSetAlignItems(' + nodeName + ', ' +
              alignValue(node.style[style]) + ');');
          break;
        case 'align-self':
          lines.push('CSSNodeStyleSetAlignSelf(' + nodeName + ', ' +
              alignValue(node.style[style]) + ');');
          break;
        case 'position':
          lines.push('CSSNodeSetPositionType(' + nodeName + ', ' +
              positionValue(node.style[style]) + ');');
          break;
        case 'flex-wrap':
          lines.push('CSSNodeSetFlexWrap(' + nodeName + ', ' + wrapValue(node.style[style]) + ');');
          break;
        case 'overflow':
          lines.push('CSSNodeSetOverflow(' + nodeName + ', ' +
              overflowValue(node.style[style]) + ');');
          break;
        case 'flex-grow':
          lines.push('CSSNodeStyleSetFlexGrow(' + nodeName + ', ' + node.style[style] + ');');
          break;
        case 'flex-shrink':
          lines.push('CSSNodeStyleSetFlexShrink(' + nodeName + ', ' + node.style[style] + ');');
          break;
        case 'flex-basis':
          lines.push('CSSNodeStyleSetFlexBasis(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'left':
          lines.push('CSSNodeStyleSetPositionLeft(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'top':
          lines.push('CSSNodeStyleSetPositionTop(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'right':
          lines.push('CSSNodeStyleSetPositionRight(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'bottom':
          lines.push('CSSNodeStyleSetPositionBottom(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'margin-left':
          lines.push('CSSNodeStyleSetMarginLeft(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'margin-top':
          lines.push('CSSNodeStyleSetMarginTop(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'margin-right':
          lines.push('CSSNodeStyleSetMarginRight(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'margin-bottom':
          lines.push('CSSNodeStyleSetMarginBottom(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'padding-left':
          lines.push('CSSNodeStyleSetPaddingLeft(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'padding-top':
          lines.push('CSSNodeStyleSetPaddingTop(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'padding-right':
          lines.push('CSSNodeStyleSetPaddingRight(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'padding-bottom':
          lines.push('CSSNodeStyleSetPaddingBottom(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'border-left-width':
          lines.push('CSSNodeStyleSetBorderLeft(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'border-top-width':
          lines.push('CSSNodeStyleSetBorderTop(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'border-right-width':
          lines.push('CSSNodeStyleSetBorderRight(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'border-bottom-width':
          lines.push('CSSNodeStyleSetBorderBottom(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'width':
          lines.push('CSSNodeStyleSetWidth(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'min-width':
          lines.push('CSSNodeStyleSetMinWidth(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'max-width':
          lines.push('CSSNodeStyleSetMaxWidth(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'height':
          lines.push('CSSNodeStyleSetHeight(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'min-height':
          lines.push('CSSNodeStyleSetMinHeight(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
        case 'max-height':
          lines.push('CSSNodeStyleSetMaxHeight(' + nodeName + ', ' +
              pixelValue(node.style[style]) + ');');
          break;
      }
    }
  }

  if (parentName) {
    lines.push('CSSNodeInsertChild(' + parentName + ', ' + nodeName + ', ' + index + ');');
  }

  for (var i = 0; i < node.children.length; i++) {
    lines.push('');
    var childName = nodeName + '_child' + i;
    lines = lines.concat(setupTestTree(node.children[i], childName, nodeName, i));
  }

  return lines;
}

function overflowValue(value) {
  switch (value) {
    case 'visible': return 'CSSOverflowVisible';
    case 'hidden': return 'CSSOverflowHidden';
  }
}

function wrapValue(value) {
  switch (value) {
    case 'wrap': return 'CSSWrapTypeWrap';
    case 'nowrap': return 'CSSWrapTypeNoWrap';
  }
}

function flexDirectionValue(value) {
  switch (value) {
    case 'row': return 'CSSFlexDirectionRow';
    case 'row-reverse': return 'CSSFlexDirectionRowReverse';
    case 'column': return 'CSSFlexDirectionColumn';
    case 'column-reverse': return 'CSSFlexDirectionColumnReverse';
  }
}

function justifyValue(value) {
  switch (value) {
    case 'center': return 'CSSJustifyCenter';
    case 'space-around': return 'CSSJustifySpaceAround';
    case 'space-between': return 'CSSJustifySpaceBetween';
    case 'flex-start': return 'CSSJustifyFlexStart';
    case 'flex-end': return 'CSSJustifyFlexEnd';
  }
}

function positionValue(value) {
  switch (value) {
    case 'absolute': return 'CSSPositionTypeAbsolute';
    default: return 'CSSPositionTypeRelative'
  }
}

function directionValue(value) {
  switch (value) {
    case 'ltr': return 'CSSDirectionLTR';
    case 'rtl': return 'CSSDirectionRTL';
    case 'inherit': return 'CSSDirectionInherit';
  }
}

function alignValue(value) {
  switch (value) {
    case 'auto': return 'CSSAlignAuto';
    case 'center': return 'CSSAlignCenter';
    case 'stretch': return 'CSSAlignStretch';
    case 'flex-start': return 'CSSAlignFlexStart';
    case 'flex-end': return 'CSSAlignFlexEnd';
  }
}

function pixelValue(value) {
  switch (value) {
    case 'auto': return 'CSSUndefined';
    case 'undefined': return 'CSSUndefined';
    default: return value.replace('px', '');
  }
}

function getDefaultStyleValue(style) {
  var node = document.getElementById('default');
  return getComputedStyle(node, null).getPropertyValue(style);
}

function printLines(lines) {
  console.log(lines.map(function(value) {
    return value + '\n';
  }).reduce(function(prev, curr) {
    return prev + curr;
  }, ''));
}

function calculateTree(root) {
  var rootLayout = [];

  for (var i = 0; i < root.children.length; i++) {
    var child = root.children[i];
    rootLayout.push({
      left: child.offsetLeft,
      top: child.offsetTop,
      width: child.offsetWidth,
      height: child.offsetHeight,
      children: calculateTree(child),
      style: getCSSLayoutStyle(child),
    });
  }

  return rootLayout;
}

function getCSSLayoutStyle(node) {
  return [
    'direction',
    'flex-direction',
    'justify-content',
    'align-content',
    'align-items',
    'align-self',
    'position',
    'flex-wrap',
    'overflow',
    'flex-grow',
    'flex-shrink',
    'flex-basis',
    'left',
    'top',
    'right',
    'bottom',
    'margin-left',
    'margin-top',
    'margin-right',
    'margin-bottom',
    'padding-left',
    'padding-top',
    'padding-right',
    'padding-bottom',
    'border-left-width',
    'border-top-width',
    'border-right-width',
    'border-bottom-width',
    'width',
    'min-width',
    'max-width',
    'height',
    'min-height',
    'max-height',
  ].reduce(function(prev, curr) {
    prev[curr] = getComputedStyle(node, null).getPropertyValue(curr);
    return prev;
  }, {});
}
