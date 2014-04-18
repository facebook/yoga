
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
    }
  }
})();
