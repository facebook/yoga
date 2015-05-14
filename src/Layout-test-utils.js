/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
/* globals document, computeLayout */

var layoutTestUtils = (function() {

  if (typeof jasmine !== 'undefined') {
    jasmine.matchersUtil.buildFailureMessage = function () {
      var args = Array.prototype.slice.call(arguments, 0),
        matcherName = args[0],
        isNot = args[1],
        actual = args[2],
        expected = args.slice(3),
        englishyPredicate = matcherName.replace(/[A-Z]/g, function(s) { return ' ' + s.toLowerCase(); });

      var pp = function(node) {
        return jasmine.pp(node)
          .replace(/([\{\[]) /g, '$1')
          .replace(/ ([\}\]:])/g, '$1');
      };

      var message = 'Expected ' +
        pp(actual) +
        (isNot ? ' not ' : ' ') +
        '\n' +
        englishyPredicate;

      if (expected.length > 0) {
        for (var i = 0; i < expected.length; i++) {
          if (i > 0) {
            message += ',';
          }
          message += ' ' + pp(expected[i]);
        }
      }

      return message + '.';
    };
  }

  var _cachedIframe;

  function renderIframe() {
    var iframe = document.createElement('iframe');
    document.body.appendChild(iframe);
    return iframe;
  }

  function getIframe(iframe) {
    if (_cachedIframe) {
      return _cachedIframe;
    }

    var doc = iframe.contentDocument;

    if (doc.readyState === 'complete') {
      var style = document.createElement('style');
      style.textContent = (function() {/*
        body, div {
          box-sizing: border-box;
          border: 0 solid black;
          position: relative;

          display: flex;
          display: -webkit-flex;
          flex-direction: column;
          -webkit-flex-direction: column;
          align-items: stretch;
          -webkit-align-items: stretch;
          justify-content: flex-start;
          -webkit-justify-content: flex-start;
          flex-shrink: 0;
          -webkit-flex-shrink: 0;

          margin: 0;
          padding: 0;
        }

        hack to ignore three hundred px width of the body {}
        body > div {
          align-self: flex-start;
        }
      */} + '').slice(15, -4);
      doc.head.appendChild(style);
      _cachedIframe = iframe;
      return iframe;
    } else {
      setTimeout(getIframe.bind(null, iframe), 0);
    }
  }

  if (typeof window !== 'undefined') {
    var iframe = renderIframe();
    getIframe(iframe);
  }

  if (typeof computeLayout === 'object') {
    var fillNodes = computeLayout.fillNodes;
    var extractNodes = computeLayout.extractNodes;
    var realComputeLayout = computeLayout.computeLayout;
  }

  function roundLayout(layout) {
    // Chrome rounds all the numbers with a precision of 1/64
    // Reproduce the same behavior
    function round(number) {
      var floored = Math.floor(number);
      var decimal = number - floored;
      if (decimal === 0) {
        return number;
      }
      var minDifference = Infinity;
      var minDecimal = Infinity;
      for (var i = 1; i < 64; ++i) {
        var roundedDecimal = i / 64;
        var difference = Math.abs(roundedDecimal - decimal);
        if (difference < minDifference) {
          minDifference = difference;
          minDecimal = roundedDecimal;
        }
      }
      return floored + minDecimal;
    }

    function rec(layout) {
      layout.top = round(layout.top);
      layout.left = round(layout.left);
      layout.width = round(layout.width);
      layout.height = round(layout.height);
      if (layout.children) {
        for (var i = 0; i < layout.children.length; ++i) {
          rec(layout.children[i]);
        }
      }
    }

    rec(layout);
    return layout;
  }

  function capitalizeFirst(str) {
    return str.charAt(0).toUpperCase() + str.slice(1);
  }

  function computeCSSLayout(rootNode) {
    fillNodes(rootNode);
    realComputeLayout(rootNode);
    return roundLayout(extractNodes(rootNode));
  }

  function computeDOMLayout(node) {
    var body = getIframe().contentDocument.body;

    function transfer(div, node, name, ext) {
      if (name in node.style) {
        var value = node.style[name] + (ext || '');
        div.style['-webkit-' + name] = value;
        div.style['webkit' + capitalizeFirst(name)] = value;
        div.style[name] = value;
      }
    }

    function transferSpacing(div, node, type, suffix) {
      transfer(div, node, type + suffix, 'px');
      transfer(div, node, type + 'Left' + suffix, 'px');
      transfer(div, node, type + 'Top' + suffix, 'px');
      transfer(div, node, type + 'Bottom' + suffix, 'px');
      transfer(div, node, type + 'Right' + suffix, 'px');
      transfer(div, node, type + 'Start' + suffix, 'px');
      transfer(div, node, type + 'End' + suffix, 'px');
    }

    function renderNode(parent, node) {
      var div = document.createElement('div');
      transfer(div, node, 'width', 'px');
      transfer(div, node, 'height', 'px');
      transfer(div, node, 'minWidth', 'px');
      transfer(div, node, 'minHeight', 'px');
      transfer(div, node, 'maxWidth', 'px');
      transfer(div, node, 'maxHeight', 'px');
      transfer(div, node, 'top', 'px');
      transfer(div, node, 'left', 'px');
      transfer(div, node, 'right', 'px');
      transfer(div, node, 'bottom', 'px');
      transferSpacing(div, node, 'margin', '');
      transferSpacing(div, node, 'padding', '');
      transferSpacing(div, node, 'border', 'Width');
      transfer(div, node, 'flexDirection');
      transfer(div, node, 'direction');
      transfer(div, node, 'flex');
      transfer(div, node, 'flexWrap');
      transfer(div, node, 'justifyContent');
      transfer(div, node, 'alignSelf');
      transfer(div, node, 'alignItems');
      transfer(div, node, 'position');
      parent.appendChild(div);
      (node.children || []).forEach(function(child) {
        renderNode(div, child);
      });
      if (node.style.measure) {
        div.innerText = node.style.measure.toString();
      }
      return div;
    }

    var div = renderNode(body, node);

    function buildLayout(absoluteRect, div) {
      var rect = div.getBoundingClientRect();
      var result = {
        width: rect.width,
        height: rect.height,
        top: rect.top - absoluteRect.top,
        left: rect.left - absoluteRect.left
      };

      var children = [];
      for (var child = div.firstChild; child; child = child.nextSibling) {
        if (child.nodeType !== 3 /* textNode */) {
          children.push(buildLayout(rect, child));
        }
      }
      if (children.length) {
        result.children = children;
      }
      return result;
    }
    var layout = buildLayout({left: 0, top: 0}, div);
    body.removeChild(div);
    return layout;
  }

  function nameLayout(name, layout) {
    var namedLayout = {name: name};
    for (var key in layout) {
      namedLayout[key] = layout[key];
    }
    return namedLayout;
  }

  function testFillNodes(node, filledNode) {
    expect(fillNodes(node)).toEqual(filledNode);
  }

  function testExtractNodes(node, extractedNode) {
    expect(extractNodes(node)).toEqual(extractedNode);
  }

  function testNamedLayout(name, layoutA, layoutB) {
    expect(nameLayout(name, layoutA))
      .toEqual(nameLayout(name, layoutB));
  }

  function isEqual(a, b) {
    // computeCSSLayout and computeDOMLayout output a tree with same ordered elements
    return JSON.stringify(a) === JSON.stringify(b);
  }

  function reduceTest(node) {
    function isWorking() {
      return isEqual(
        computeDOMLayout(node),
        computeCSSLayout(node)
      );
    }
    if (isWorking()) {
      return node;
    }

    var isModified = true;

    function rec(node) {
      var key;
      var value;

      // Style
      for (key in node.style) {
        value = node.style[key];
        delete node.style[key];
        if (isWorking()) {
          node.style[key] = value;
        } else {
          isModified = true;
        }
      }
      // Round values
      for (key in node.style) {
        value = node.style[key];
        if (value > 100) {
          node.style[key] = Math.round(value / 100) * 100;
        } else if (value > 10) {
          node.style[key] = Math.round(value / 10) * 10;
        } else if (value > 1) {
          node.style[key] = 5;
        }
        if (node.style[key] !== value) {
          if (isWorking()) {
            node.style[key] = value;
          } else {
            isModified = true;
          }
        }
      }
      // Children
      for (var i = 0; node.children && i < node.children.length; ++i) {
        value = node.children[i];
        node.children.splice(i, 1);
        if (isWorking()) {
          if (!node.children) {
            node.children = [];
          }
          node.children.splice(i, 0, value);
          rec(node.children[i]);
        } else {
          i--;
          isModified = true;
        }
      }
    }
    while (isModified) {
      isModified = false;
      rec(node);
    }

    return node;
  }

  var iframeText;
  function measureTextSizes(text, width) {
    iframeText = iframeText || document.createElement('iframe');
    document.body.appendChild(iframeText);

    var body = iframeText.contentDocument.body;
    if (width === undefined || width !== width) {
      width = Infinity;
    }

    var div = document.createElement('div');
    div.style.width = (width === Infinity ? 10000000 : width) + 'px';
    div.style.display = 'flex';
    div.style.flexDirection = 'column';
    div.style.alignItems = 'flex-start';

    var span = document.createElement('span');
    span.style.display = 'flex';
    span.style.flexDirection = 'column';
    span.style.alignItems = 'flex-start';
    span.innerText = text;

    div.appendChild(span);
    body.appendChild(div);
    var rect = span.getBoundingClientRect();
    body.removeChild(div);
    return {
      width: rect.width,
      height: rect.height
    };
  }

  var texts = {
    small: 'small',
    big: 'loooooooooong with space'
  };

  var preDefinedTextSizes = {
    smallWidth: 34.671875,
    smallHeight: 18,
    bigWidth: 172.421875,
    bigHeight: 36,
    bigMinWidth: 100.4375
  };

  var textSizes;
  if (typeof require === 'function') {
    textSizes = preDefinedTextSizes;
  } else {
    textSizes = {
      smallWidth: measureTextSizes(texts.small, 0).width,
      smallHeight: measureTextSizes(texts.small, 0).height,
      bigWidth: measureTextSizes(texts.big).width,
      bigHeight: measureTextSizes(texts.big, 0).height,
      bigMinWidth: measureTextSizes(texts.big, 0).width
    };
  }

  return {
    texts: texts,
    textSizes: textSizes,
    preDefinedTextSizes: preDefinedTextSizes,
    testLayout: function(node, expectedLayout) {
      var layout = computeCSSLayout(node);
      var domLayout = computeDOMLayout(node);
      testNamedLayout('expected-dom', expectedLayout, domLayout);
      testNamedLayout('layout-dom', layout, domLayout);
    },
    testFillNodes: testFillNodes,
    testExtractNodes: testExtractNodes,
    testRandomLayout: function(node) {
      expect({node: node, layout: computeCSSLayout(node)})
        .toEqual({node: node, layout: computeDOMLayout(node)});
    },
    testsFinished: function() {
      console.log('tests finished!');
    },
    computeLayout: computeCSSLayout,
    computeDOMLayout: computeDOMLayout,
    reduceTest: reduceTest,
    text: function(text) {
      var fn = function(width) {
        if (width === undefined || width !== width) {
          width = Infinity;
        }

        // Constants for testing purposes between C/JS and other platforms
        // Comment this block of code if you want to use the browser to
        // generate proper sizes
        if (text === texts.small) {
          return {
            width: Math.min(textSizes.smallWidth, width),
            height: textSizes.smallHeight
          };
        }
        if (text === texts.big) {
          var res = {
            width: width >= textSizes.bigWidth ? textSizes.bigWidth : Math.max(textSizes.bigMinWidth, width),
            height: width >= textSizes.bigWidth ? textSizes.smallHeight : textSizes.bigHeight
          };
          return res;
        }
      };
      fn.toString = function() { return text; };
      return fn;
    }
  };
})();

if (typeof module !== 'undefined') {
  module.exports = layoutTestUtils;
}
