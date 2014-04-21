
var layoutTestUtils = (function() {
  var iframe = (function() {
    var iframe = document.createElement('iframe');
    document.body.appendChild(iframe);
    var doc = iframe.contentDocument;

    var style = document.createElement('style');
    style.innerText = (function() {/*
      body, div {
        box-sizing: border-box;
        position: relative;

        display: flex;
        flex-direction: column;
        align-items: flex-start;
        justify-content: flex-start;
        flex-shrink: 0;

        margin: 0;
        padding: 0;
      }
    */} + '').slice(15, -4);
    doc.head.appendChild(style);

    return iframe;
  })();

  function computeDOMLayout(node) {
    var body = iframe.contentDocument.body;

    function transfer(div, node, name, ext) {
      if (name in node.style) {
        div.style[name] = node.style[name] + (ext || '');
      }
    }

    function transferSpacing(div, node, type) {
      transfer(div, node, type, 'px');
      transfer(div, node, type + 'Left', 'px');
      transfer(div, node, type + 'Top', 'px');
      transfer(div, node, type + 'Bottom', 'px');
      transfer(div, node, type + 'Right', 'px');
    }

    function renderNode(parent, node) {
      var div = document.createElement('div');
      transfer(div, node, 'width', 'px');
      transfer(div, node, 'height', 'px');
      transfer(div, node, 'top', 'px');
      transfer(div, node, 'left', 'px');
      transfer(div, node, 'right', 'px');
      transfer(div, node, 'bottom', 'px');
      transferSpacing(div, node, 'margin');
      transferSpacing(div, node, 'padding');
      transfer(div, node, 'flexDirection');
      transfer(div, node, 'flex');
      transfer(div, node, 'justifyContent');
      transfer(div, node, 'alignSelf');
      transfer(div, node, 'alignItems');
      transfer(div, node, 'position');
      parent.appendChild(div);
      (node.children || []).forEach(function(child) {
        renderNode(div, child);
      });
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
        children.push(buildLayout(rect, child));
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

  function testNamedLayout(name, layoutA, layoutB) {
    expect(nameLayout(name, layoutA))
      .toEqual(nameLayout(name, layoutB));
  }

  function isEqual(a, b) {
    // computeLayout and computeDOMLayout output a tree with same ordered elements
    return JSON.stringify(a) === JSON.stringify(b);
  }

  function printNode(node) {
    console.log(
      JSON.stringify(node)
        .replace(/"([a-zA-Z]+)":/g, '$1: ')
        .replace(/,/g, ', ')
        .replace(/"/g, '\'')
    );
  }
  function reduceTest(node) {
    function isWorking() {
      return isEqual(
        computeDOMLayout(node),
        computeLayout(node)
      );
    }
    if (isWorking()) {
      return console.log('Bail early, already working');
    }

    var isModified = true;

    function rec(node) {
      // Style
      for (var key in node.style) {
        var value = node.style[key];
        delete node.style[key];
        if (isWorking()) {
          node.style[key] = value;
        } else {
          isModified = true;
        }
      }
      // Round values
      for (var key in node.style) {
        var value = node.style[key];
        if (value > 100) {
          node.style[key] = Math.round(value / 100) * 100;
        } else if (value > 10) {
          node.style[key] = Math.round(value / 10) * 10;
        } else if (value > 0) {
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
        var value = node.children[i];
        node.children.splice(i, 1);
        if (isWorking() && node.children) {
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

    printNode(node);
    printNode(computeDOMLayout(node));
  }

reduceTest({ style : { top : 0, marginLeft : 18 }, children : [ { style : { left : -7, paddingRight : 2, alignItems : 'stretch' }, children : [ { style : { left : 9 } }, { style : { width : 377, top : 0, marginTop : 0, flexDirection : 'column' } }, { style : { paddingTop : 10 } } ] }, { style : { width : 222, paddingTop : 1, alignSelf : 'stretch' } }, { style : { width : 61, left : 3 } } ] })

  return {
    testLayout: function(node, expectedLayout) {
      var layout = computeLayout(node);
      var domLayout = computeDOMLayout(node);
      testNamedLayout('expected-dom', expectedLayout, domLayout);
      testNamedLayout('layout-dom', layout, domLayout);
    },
    testRandomLayout: function(node, i) {
      expect({i: i, node: node, layout: computeLayout(node)})
        .toEqual({i: i, node: node, layout: computeDOMLayout(node)});
    },
    computeDOMLayout: computeDOMLayout,
    reduceTest: reduceTest
  }
})();
