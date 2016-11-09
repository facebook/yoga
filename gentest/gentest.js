/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

window.onload = function() {
  checkDefaultValues();

  printTest(
      new CPPEmitter(),
      document.body.children[0],
      document.body.children[1],
      document.body.children[2]);

  printTest(
      new JavaEmitter(),
      document.body.children[0],
      document.body.children[1],
      document.body.children[2]);

  printTest(
      new CSEmitter(),
      document.body.children[0],
      document.body.children[1],
      document.body.children[2]);
}

function assert(condition, message) {
  if (!condition) {
    throw new Error(message);
  }
}

function printTest(e, LTRContainer, RTLContainer, genericContainer) {
  e.push([
    '/**',
    ' * Copyright (c) 2014-present, Facebook, Inc.',
    ' * All rights reserved.',
    ' *',
    ' * This source code is licensed under the BSD-style license found in the',
    ' * LICENSE file in the root directory of this source tree. An additional grant',
    ' * of patent rights can be found in the PATENTS file in the same directory.',
    ' */',
    '',
    '/**',
    ' * @Generated by gentest/gentest.sh with the following input',
    ' *',
  ]);

  var indentation = 0;
  e.push(genericContainer.innerHTML.split('\n').map(function(line) {
    return line.trim();
  }).filter(function(line) {
    return line.length > 0 && line !== '<div id="default"></div>';
  }).map(function(line) {
    var result;
    if (line.indexOf('</div') == 0) {
      result = '  '.repeat(indentation - 1) + line;
    } else {
      result = '  '.repeat(indentation) + line;
    }

    indentation += (line.match(/<div/g) || []).length;
    indentation -= (line.match(/<\/div/g) || []).length;
    return result;
  }).reduce(function(curr, prev) {
    if (prev.indexOf('<div') == 0) {
      prev = '\n' + prev;
    }
    return curr + '\n' + prev;
  }));
  e.push([
    ' *',
    ' */',
    '',
  ]);
  e.emitPrologue();

  var LTRLayoutTree = calculateTree(LTRContainer);
  var RTLLayoutTree = calculateTree(RTLContainer);
  var genericLayoutTree = calculateTree(genericContainer);


  for (var i = 0; i < genericLayoutTree.length; i++) {
    e.emitTestPrologue(genericLayoutTree[i].name);

    if (genericLayoutTree[i].name == 'wrap_column') {
      // Modify width and left values due to both safari and chrome not abiding by the
      // specification. The undefined dimension of a parent should be defined by the total size
      // of their children in that dimension.
      // See diagram under flex-wrap header https://www.w3.org/TR/css-flexbox-1/
      assert(LTRLayoutTree[0].width == 30, 'wrap_column LTR root.width should be 30');
      LTRLayoutTree[0].width = 60;
      assert(RTLLayoutTree[0].width == 30, 'wrap_column RTL root.width should be 30');
      RTLLayoutTree[0].width = 60;
      var children = RTLLayoutTree[0].children;
      assert(children[0].left == 0, 'wrap_column RTL root_child0.left should be 0');
      children[0].left = 30;
      assert(children[1].left == 0, 'wrap_column RTL root_child0.left should be 0');
      children[1].left = 30;
      assert(children[2].left == 0, 'wrap_column RTL root_child2.left should be 0');
      children[2].left = 30;
      assert(children[3].left == -30, 'wrap_column RTL root_child3.left should be -30');
      children[3].left = 0;
    }

    setupTestTree(
        e,
        undefined,
        LTRLayoutTree[i],
        genericLayoutTree[i],
        'root',
        null);

    e.CSSNodeCalculateLayout('root', e.CSSDirectionLTR);
    e.push('');

    assertTestTree(e, LTRLayoutTree[i], 'root', null);
    e.push('');

    e.CSSNodeCalculateLayout('root', e.CSSDirectionRTL);
    e.push('');

    assertTestTree(e, RTLLayoutTree[i], 'root', null);

    e.emitTestEpilogue();
  }
  e.emitEpilogue();

  e.print();
}

function assertTestTree(e, node, nodeName, parentName) {
  e.AssertEQ(node.left, e.CSSNodeLayoutGetLeft(nodeName));
  e.AssertEQ(node.top, e.CSSNodeLayoutGetTop(nodeName));
  e.AssertEQ(node.width, e.CSSNodeLayoutGetWidth(nodeName));
  e.AssertEQ(node.height, e.CSSNodeLayoutGetHeight(nodeName));

  for (var i = 0; i < node.children.length; i++) {
    e.push('');
    var childName = nodeName + '_child' + i;
    assertTestTree(e, node.children[i], childName, nodeName);
  }
}

function checkDefaultValues() {
  // Sanity check of the CSSLayout default values by test-template.html
  [
    {style:'flex-direction', value:'column'},
    {style:'justify-content', value:'flex-start'},
    {style:'align-content', value:'flex-start'},
    {style:'align-items', value:'stretch'},
    {style:'position', value:'relative'},
    {style:'flex-wrap', value:'nowrap'},
    {style:'overflow', value:'visible'},
    {style:'flex-grow', value:'0'},
    {style:'flex-shrink', value:'0'},
    {style:'left', value:'0px'},
    {style:'top', value:'0px'},
    {style:'right', value:'0px'},
    {style:'bottom', value:'0px'},
  ].forEach(function(item) {
    assert(item.value === getDefaultStyleValue(item.style),
        item.style + ' should be ' + item.value);
  });
}

function setupTestTree(e, parent, node, genericNode, nodeName, parentName, index) {
  e.emitTestTreePrologue(nodeName);

  for (var style in node.style) {
    // Skip position info for root as it messes up tests
    if (node.declaredStyle[style] === "" &&
        (style == 'position' ||
         style == 'left' ||
         style == 'top' ||
         style == 'right' ||
         style == 'bottom' ||
         style == 'width' ||
         style == 'height')) {
      continue;
    }

    if (node.style[style] !== getDefaultStyleValue(style)) {
      switch (style) {
        case 'direction':
          e.CSSNodeStyleSetDirection(nodeName, directionValue(e, node.style[style]));
          break;
        case 'flex-direction':
          e.CSSNodeStyleSetFlexDirection(nodeName, flexDirectionValue(e, node.style[style]));
          break;
        case 'justify-content':
          e.CSSNodeStyleSetJustifyContent(nodeName, justifyValue(e, node.style[style]));
          break;
        case 'align-content':
          e.CSSNodeStyleSetAlignContent(nodeName, alignValue(e, node.style[style]));
          break;
        case 'align-items':
          e.CSSNodeStyleSetAlignItems(nodeName, alignValue(e, node.style[style]));
          break;
        case 'align-self':
          if (!parent || node.style[style] !== parent.style['align-items']) {
            e.CSSNodeStyleSetAlignSelf(nodeName, alignValue(e, node.style[style]));
          }
          break;
        case 'position':
          e.CSSNodeStyleSetPositionType(nodeName, positionValue(e, node.style[style]));
          break;
        case 'flex-wrap':
          e.CSSNodeStyleSetFlexWrap(nodeName, wrapValue(e, node.style[style]));
          break;
        case 'overflow':
          e.CSSNodeStyleSetOverflow(nodeName, overflowValue(e, node.style[style]));
          break;
        case 'flex-grow':
          e.CSSNodeStyleSetFlexGrow(nodeName, node.style[style]);
          break;
        case 'flex-shrink':
          e.CSSNodeStyleSetFlexShrink(nodeName, node.style[style]);
          break;
        case 'flex-basis':
          e.CSSNodeStyleSetFlexBasis(nodeName, pixelValue(e, node.style[style]));
          break;
        case 'left':
          if (genericNode.rawStyle.indexOf('start:') >= 0) {
            e.CSSNodeStyleSetPosition(nodeName, e.CSSEdgeStart, pixelValue(e, node.style[style]));
          } else {
            e.CSSNodeStyleSetPosition(nodeName, e.CSSEdgeLeft, pixelValue(e, node.style[style]));
          }
          break;
        case 'top':
          e.CSSNodeStyleSetPosition(nodeName, e.CSSEdgeTop, pixelValue(e, node.style[style]));
          break;
        case 'right':
          if (genericNode.rawStyle.indexOf('end:') >= 0) {
            e.CSSNodeStyleSetPosition(nodeName, e.CSSEdgeEnd, pixelValue(e, node.style[style]));
          } else {
            e.CSSNodeStyleSetPosition(nodeName, e.CSSEdgeRight, pixelValue(e, node.style[style]));
          }
          break;
        case 'bottom':
          e.CSSNodeStyleSetPosition(nodeName, e.CSSEdgeBottom, pixelValue(e, node.style[style]));
          break;
        case 'margin-left':
          if (genericNode.rawStyle.indexOf('margin-start:') >= 0) {
            e.CSSNodeStyleSetMargin(nodeName, e.CSSEdgeStart, pixelValue(e, node.style[style]));
          } else {
            e.CSSNodeStyleSetMargin(nodeName, e.CSSEdgeLeft, pixelValue(e, node.style[style]));
          }
          break;
        case 'margin-top':
          e.CSSNodeStyleSetMargin(nodeName, e.CSSEdgeTop, pixelValue(e, node.style[style]));
          break;
        case 'margin-right':
          if (genericNode.rawStyle.indexOf('margin-end:') >= 0) {
            e.CSSNodeStyleSetMargin(nodeName, e.CSSEdgeEnd, pixelValue(e, node.style[style]));
          } else {
            e.CSSNodeStyleSetMargin(nodeName, e.CSSEdgeRight, pixelValue(e, node.style[style]));
          }
          break;
        case 'margin-bottom':
          e.CSSNodeStyleSetMargin(nodeName, e.CSSEdgeBottom, pixelValue(e, node.style[style]));
          break;
        case 'padding-left':
          if (genericNode.rawStyle.indexOf('padding-start:') >= 0) {
            e.CSSNodeStyleSetPadding(nodeName, e.CSSEdgeStart, pixelValue(e, node.style[style]));
          } else {
            e.CSSNodeStyleSetPadding(nodeName, e.CSSEdgeLeft, pixelValue(e, node.style[style]));
          }
          break;
        case 'padding-top':
          e.CSSNodeStyleSetPadding(nodeName, e.CSSEdgeTop, pixelValue(e, node.style[style]));
          break;
        case 'padding-right':
          if (genericNode.rawStyle.indexOf('padding-end:') >= 0) {
            e.CSSNodeStyleSetPadding(nodeName, e.CSSEdgeEnd, pixelValue(e, node.style[style]));
          } else {
            e.CSSNodeStyleSetPadding(nodeName, e.CSSEdgeRight, pixelValue(e, node.style[style]));
          }
          break;
        case 'padding-bottom':
          e.CSSNodeStyleSetPadding(nodeName, e.CSSEdgeBottom, pixelValue(e, node.style[style]));
          break;
        case 'border-left-width':
          if (genericNode.rawStyle.indexOf('border-start-width:') >= 0) {
            e.CSSNodeStyleSetBorder(nodeName, e.CSSEdgeStart, pixelValue(e, node.style[style]));
          } else {
            e.CSSNodeStyleSetBorder(nodeName, e.CSSEdgeLeft, pixelValue(e, node.style[style]));
          }
          break;
        case 'border-top-width':
          e.CSSNodeStyleSetBorder(nodeName, e.CSSEdgeTop, pixelValue(e, node.style[style]));
          break;
        case 'border-right-width':
          if (genericNode.rawStyle.indexOf('border-end-width:') >= 0) {
            e.CSSNodeStyleSetBorder(nodeName, e.CSSEdgeEnd, pixelValue(e, node.style[style]));
          } else {
            e.CSSNodeStyleSetBorder(nodeName, e.CSSEdgeRight, pixelValue(e, node.style[style]));
          }
          break;
        case 'border-bottom-width':
          e.CSSNodeStyleSetBorder(nodeName, e.CSSEdgeBottom, pixelValue(e, node.style[style]));
          break;
        case 'width':
          e.CSSNodeStyleSetWidth(nodeName, pixelValue(e, node.style[style]));
          break;
        case 'min-width':
          e.CSSNodeStyleSetMinWidth(nodeName, pixelValue(e, node.style[style]));
          break;
        case 'max-width':
          e.CSSNodeStyleSetMaxWidth(nodeName, pixelValue(e, node.style[style]));
          break;
        case 'height':
          e.CSSNodeStyleSetHeight(nodeName, pixelValue(e, node.style[style]));
          break;
        case 'min-height':
          e.CSSNodeStyleSetMinHeight(nodeName, pixelValue(e, node.style[style]));
          break;
        case 'max-height':
          e.CSSNodeStyleSetMaxHeight(nodeName, pixelValue(e, node.style[style]));
          break;
      }
    }
  }

  if (parentName) {
    e.CSSNodeInsertChild(parentName, nodeName, index);
  }

  for (var i = 0; i < node.children.length; i++) {
    e.push('');
    var childName = nodeName + '_child' + i;
    setupTestTree(
        e,
        node,
        node.children[i],
        genericNode.children[i],
        childName,
        nodeName,
        i);
  }
}

function overflowValue(e, value) {
  switch (value) {
    case 'visible': return e.CSSOverflowVisible;
    case 'hidden': return e.CSSOverflowHidden;
  }
}

function wrapValue(e, value) {
  switch (value) {
    case 'wrap': return e.CSSWrapTypeWrap;
    case 'nowrap': return e.CSSWrapTypeNoWrap;
  }
}

function flexDirectionValue(e, value) {
  switch (value) {
    case 'row': return e.CSSFlexDirectionRow;
    case 'row-reverse': return e.CSSFlexDirectionRowReverse;
    case 'column': return e.CSSFlexDirectionColumn;
    case 'column-reverse': return e.CSSFlexDirectionColumnReverse;
  }
}

function justifyValue(e, value) {
  switch (value) {
    case 'center': return e.CSSJustifyCenter;
    case 'space-around': return e.CSSJustifySpaceAround;
    case 'space-between': return e.CSSJustifySpaceBetween;
    case 'flex-start': return e.CSSJustifyFlexStart;
    case 'flex-end': return e.CSSJustifyFlexEnd;
  }
}

function positionValue(e, value) {
  switch (value) {
    case 'absolute': return e.CSSPositionTypeAbsolute;
    default: return e.CSSPositionTypeRelative
  }
}

function directionValue(e, value) {
  switch (value) {
    case 'ltr': return e.CSSDirectionLTR;
    case 'rtl': return e.CSSDirectionRTL;
    case 'inherit': return e.CSSDirectionInherit;
  }
}

function alignValue(e, value) {
  switch (value) {
    case 'auto': return e.CSSAlignAuto;
    case 'center': return e.CSSAlignCenter;
    case 'stretch': return e.CSSAlignStretch;
    case 'flex-start': return e.CSSAlignFlexStart;
    case 'flex-end': return e.CSSAlignFlexEnd;
  }
}

function pixelValue(e, value) {
  switch (value) {
    case 'auto': return e.CSSUndefined;
    case 'undefined': return e.CSSUndefined;
    default: return value.replace('px', '');
  }
}

function getDefaultStyleValue(style) {
  if (style == 'position') {
    return 'relative';
  }
  var node = document.getElementById('default');
  return getComputedStyle(node, null).getPropertyValue(style);
}

function calculateTree(root) {
  var rootLayout = [];

  for (var i = 0; i < root.children.length; i++) {
    var child = root.children[i];
    rootLayout.push({
      name: child.id !== '' ? child.id : 'INSERT_NAME_HERE',
      left: child.offsetLeft + child.parentNode.clientLeft,
      top: child.offsetTop + child.parentNode.clientTop,
      width: child.offsetWidth,
      height: child.offsetHeight,
      children: calculateTree(child),
      style: getCSSLayoutStyle(child),
      declaredStyle: child.style,
      rawStyle: child.getAttribute('style'),
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
  ].reduce(function(map, key) {
    map[key] = node.style[key] || getComputedStyle(node, null).getPropertyValue(key);
    return map;
  }, {});
}

var Emitter = function(lang, indent) {
  this.lang = lang;
  this.indent = indent;
  this.indents = [];
  this.lines = [];
};

Emitter.prototype = Object.create(Object.prototype, {
  constructor:{value:Emitter},

  pushIndent:{value:function() {
    this.indents.push(this.indent);
  }},

  popIndent:{value:function() {
    this.indents.pop();
  }},

  push:{value:function(line) {
    if (line instanceof Array) {
      line.forEach(function(element) {
        this.push(element);
      }, this);
      return;
    } else if (line.length > 0) {
      line = this.indents.join('') + line;
    }
    this.lines.push(line);
  }},

  print:{value:function() {
    console.log(this.lines.join('\n'));
  }},
});
