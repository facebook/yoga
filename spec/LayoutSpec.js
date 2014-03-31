
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

  function transferPx(div, node, name) {
    if (name in node.style) {
      div.style[name] = node.style[name] + 'px';
    }
  }

  function renderNode(parent, node) {
    var div = document.createElement('div');
    transferPx(div, node, 'width');
    transferPx(div, node, 'height');
    transferPx(div, node, 'margin');
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

function testLayout(node, expectedLayout) {
  var layout = computeLayout(node);
  var domLayout = computeDOMLayout(node);
  expect(layout).toEqual(expectedLayout)
  expect(layout).toEqual(domLayout);
  expect(expectedLayout).toEqual(domLayout);
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
});

