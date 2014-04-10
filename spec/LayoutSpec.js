
function setupIframe(callback) {
  var iframe = document.createElement('iframe');
  document.body.appendChild(iframe);
  var doc = iframe.contentDocument;

  var link = document.createElement('link');
  link.setAttribute('rel', 'stylesheet');
  link.setAttribute('type', 'text/css');
  link.setAttribute('href', 'style.css');
  doc.head.appendChild(link);

  requestAnimationFrame(function wait() {
    if (doc.styleSheets.length) {
      callback(iframe);
    } else {
      requestAnimationFrame(wait);
    }
  })
}

var iframe = null;

function computeDOMLayout(node) {
  var body = iframe.contentDocument.body;

  function transfer(div, node, name, ext) {
    if (name in node.style) {
      div.style[name] = node.style[name] + (ext || '');
    }
  }

  function renderNode(parent, node) {
    var div = document.createElement('div');
    transfer(div, node, 'width', 'px');
    transfer(div, node, 'height', 'px');
    transfer(div, node, 'margin', 'px');
    transfer(div, node, 'marginLeft', 'px');
    transfer(div, node, 'marginTop', 'px');
    transfer(div, node, 'marginBottom', 'px');
    transfer(div, node, 'marginRight', 'px');
    transfer(div, node, 'flexDirection');
    transfer(div, node, 'flex');
    transfer(div, node, 'justifyContent');
    transfer(div, node, 'alignSelf');
    transfer(div, node, 'alignItems');
    parent.appendChild(div);
    (node.children || []).forEach(function(child) {
      renderNode(div, child);
    });
    return div;
  }

  var div = renderNode(body, node);

  function buildLayout(parentRect, div) {
    var rect = div.getBoundingClientRect();
    var result = {
      width: rect.width,
      height: rect.height,
      top: rect.top - parentRect.top,
      left: rect.left - parentRect.left
    };

    var children = [];
    for (var child = div.firstChild; child; child = child.nextSibling) {
      children.push(buildLayout(result, child));
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

function testLayout(node, expectedLayout) {
  var layout = computeLayout(node);
  var domLayout = computeDOMLayout(node);
  testNamedLayout('expected-dom', expectedLayout, domLayout);
  testNamedLayout('layout-dom', layout, domLayout);
}

describe('Layout', function() {
  beforeEach(function(done) {
    if (iframe) {
      done();
    } else {
      setupIframe(function(ifrm) { iframe = ifrm; done(); });
    }
  });

  it('should layout a single node with width and height', function() {
    testLayout({
      style: {width: 100, height: 200}
    }, {
      width: 100, height: 200, top: 0, left: 0
    });
  });

  it('should layout node with children', function() {
    testLayout({
      style: {width: 1000, height: 1000},
      children: [
        {style: {width: 500, height: 500}},
        {style: {width: 250, height: 250}},
        {style: {width: 125, height: 125}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 500, height: 500, top: 0, left: 0},
        {width: 250, height: 250, top: 500, left: 0},
        {width: 125, height: 125, top: 750, left: 0}
      ]
    });
  });

  it('should layout node with nested children', function() {
    testLayout({
      style: {width: 1000, height: 1000},
      children: [{
        style: {width: 500, height: 500}
      }, {
        style: {width: 500, height: 500},
        children: [
          {style: {width: 250, height: 250}},
          {style: {width: 250, height: 250}}
        ]
      }]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [{
        width: 500, height: 500, top: 0, left: 0
      }, {
        width: 500, height: 500, top: 500, left: 0,
        children: [
          {width: 250, height: 250, top: 0, left: 0},
          {width: 250, height: 250, top: 250, left: 0},
        ]
      }]
    });
  });

  it('should layout node with margin', function() {
    testLayout({
      style: {width: 100, height: 200, margin: 10}
    }, {
      width: 100, height: 200, top: 10, left: 10
    });
  });

  it('should layout node with several children', function() {
    testLayout({
      style: {width: 1000, height: 1000, margin: 10},
      children: [
        {style: {width: 100, height: 100, margin: 50}},
        {style: {width: 100, height: 100, margin: 25}},
        {style: {width: 100, height: 100, margin: 10}}
      ]
    }, {
      width: 1000, height: 1000, top: 10, left: 10,
      children: [
        {width: 100, height: 100, top: 50, left: 50},
        {width: 100, height: 100, top: 225, left: 25},
        {width: 100, height: 100, top: 360, left: 10}
      ]
    });
  });

  it('should layout node with row flex direction', function() {
    testLayout({
      style: {width: 1000, height: 1000, flexDirection: 'row'},
      children: [
        {style: {width: 100, height: 200}},
        {style: {width: 300, height: 150}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 100, height: 200, top: 0, left: 0},
        {width: 300, height: 150, top: 0, left: 100}
      ]
    });
  });

  it('should layout node based on children main dimensions', function() {
    testLayout({
      style: {width: 300},
      children: [
        {style: {width: 100, height: 200}},
        {style: {width: 300, height: 150}}
      ]
    }, {
      width: 300, height: 350, top: 0, left: 0,
      children: [
        {width: 100, height: 200, top: 0, left: 0},
        {width: 300, height: 150, top: 200, left: 0}
      ]
    });
  });

  it('should layout node with flex', function() {
    testLayout({
      style: {width: 1000, height: 1000},
      children: [
        {style: {width: 100, height: 200}},
        {style: {width: 100, flex: 1}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 100, height: 200, top: 0, left: 0},
        {width: 100, height: 800, top: 200, left: 0}
      ]
    });
  });

  it('should layout node with flex recursively', function() {
    testLayout({
      style: {width: 1000, height: 1000},
      children: [{
        style: {width: 1000, flex: 1},
        children: [{
          style: {width: 1000, flex: 1},
          children: [{
            style: {width: 1000, flex: 1}
          }]
        }]
      }]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [{
        width: 1000, height: 1000, top: 0, left: 0,
        children: [{
          width: 1000, height: 1000, top: 0, left: 0,
          children: [{
            width: 1000, height: 1000, top: 0, left: 0
          }]
        }]
      }]
    });
  });

  it('should layout node with targeted margin', function() {
    testLayout({
      style: {width: 1000, height: 1000, marginTop: 10, marginLeft: 5},
      children: [
        {style: {width: 100, height: 100,
                 marginTop: 50, marginLeft: 15, marginBottom: 20}},
        {style: {width: 100, height: 100, marginLeft: 30}}
      ]
    }, {
      width: 1000, height: 1000, top: 10, left: 5,
      children: [
        {width: 100, height: 100, top: 50, left: 15},
        {width: 100, height: 100, top: 170, left: 30}
      ]
    });
  });

  it('should layout node with justifyContent: flex-start', function() {
    testLayout({
      style: {width: 1000, height: 1000, justifyContent: 'flex-start'},
      children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 100, height: 100, top: 0, left: 0},
        {width: 100, height: 100, top: 100, left: 0}
      ]
    });
  });

  it('should layout node with justifyContent: flex-end', function() {
    testLayout({
      style: {width: 1000, height: 1000, justifyContent: 'flex-end'},
      children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 100, height: 100, top: 800, left: 0},
        {width: 100, height: 100, top: 900, left: 0}
      ]
    });
  });

  it('should layout node with justifyContent: space-between', function() {
    testLayout({
      style: {width: 1000, height: 1000, justifyContent: 'space-between'},
      children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 100, height: 100, top: 0, left: 0},
        {width: 100, height: 100, top: 900, left: 0}
      ]
    });
  });

  it('should layout node with justifyContent: space-around', function() {
    testLayout({
      style: {width: 1000, height: 1000, justifyContent: 'space-around'},
      children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 100, height: 100, top: 200, left: 0},
        {width: 100, height: 100, top: 700, left: 0}
      ]
    });
  });

  it('should layout node with justifyContent: center', function() {
    testLayout({
      style: {width: 1000, height: 1000, justifyContent: 'center'},
      children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 100, height: 100, top: 400, left: 0},
        {width: 100, height: 100, top: 500, left: 0}
      ]
    });
  });

  it('should layout node with flex override height', function() {
    testLayout({
      style: {width: 1000, height: 1000},
      children: [
        {style: {width: 100, height: 100, flex: 1}},
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 100, height: 1000, top: 0, left: 0}
      ]
    });
  });

  it('should layout node with alignItems: flex-start', function() {
    testLayout({
      style: {width: 1000, height: 1000, alignItems: 'flex-start'},
      children: [
        {style: {width: 200, height: 100}},
        {style: {width: 100, height: 100}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 200, height: 100, top: 0, left: 0},
        {width: 100, height: 100, top: 100, left: 0},
      ]
    });
  });

  it('should layout node with alignItems: center', function() {
    testLayout({
      style: {width: 1000, height: 1000, alignItems: 'center'},
      children: [
        {style: {width: 200, height: 100}},
        {style: {width: 100, height: 100}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 200, height: 100, top: 0, left: 400},
        {width: 100, height: 100, top: 100, left: 450},
      ]
    });
  });

  it('should layout node with alignItems: flex-end', function() {
    testLayout({
      style: {width: 1000, height: 1000, alignItems: 'flex-end'},
      children: [
        {style: {width: 200, height: 100}},
        {style: {width: 100, height: 100}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 200, height: 100, top: 0, left: 800},
        {width: 100, height: 100, top: 100, left: 900},
      ]
    });
  });

  it('should layout node with alignSelf overrides alignItems', function() {
    testLayout({
      style: {width: 1000, height: 1000, alignItems: 'flex-end'},
      children: [
        {style: {width: 200, height: 100}},
        {style: {width: 100, height: 100, alignSelf: 'center'}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 200, height: 100, top: 0, left: 800},
        {width: 100, height: 100, top: 100, left: 450},
      ]
    });
  });

  it('should layout node with alignItem: stretch', function() {
    testLayout({
      style: {width: 1000, height: 1000, alignItems: 'stretch'},
      children: [
        {style: {height: 100}}
      ]
    }, {
      width: 1000, height: 1000, top: 0, left: 0,
      children: [
        {width: 1000, height: 100, top: 0, left: 0}
      ]
    });
  });

  it('should layout empty node', function() {
    testLayout({
      style: {},
      children: [
        {style: {}}
      ]
    }, {
      width: 0, height: 0, top: 0, left: 0,
      children: [
        {width: 0, height: 0, top: 0, left: 0}
      ]
    });
  });

});

