
function computeLayout(node) {

  function fillNodes(node) {
    node.layout = {
      top: undefined,
      left: undefined,
      width: undefined,
      height: undefined
    };
    (node.children || []).forEach(fillNodes);
  }

  function extractNodes(node) {
    var layout = node.layout;
    delete node.layout;
    if (node.children) {
      layout.children = node.children.map(extractNodes);
    }
    return layout;
  }

  function getMargin(node) {
    if ('margin' in node.style) {
      return node.style.margin;
    }
    return 0;
  }

  var pos = {
    row: 'left',
    column: 'top'
  };
  var dim = {
    row: 'width',
    column: 'height'
  };

  function layoutNode(node, parent) {
    var mainAxis = node.style.flexDirection === 'row' ? 'row' : 'column';
    var crossAxis = mainAxis === 'row' ? 'column' : 'row';

    var mainDimInStyle = dim[mainAxis] in node.style;
    if (mainDimInStyle) {
      node.layout[dim[mainAxis]] = node.style[dim[mainAxis]];
    }

    var mainPos = 0;
    var children = [];
    (node.children || []).forEach(function(child) {
      var offset = {};
      offset[pos[mainAxis]] = mainPos;
      offset[pos[crossAxis]] = 0;
      layoutNode(child, offset);

      mainPos += child.layout[dim[mainAxis]] + 2 * getMargin(child);
    });

    if (!mainDimInStyle) {
      node.layout[dim[mainAxis]] = mainPos;
    }
    node.layout[dim[crossAxis]] = node.style[dim[crossAxis]];
    node.layout.top = getMargin(node) + parent.top;
    node.layout.left = getMargin(node) + parent.left;
  }

  fillNodes(node);
  layoutNode(node, {top: 0, left: 0});
  return extractNodes(node);
}

