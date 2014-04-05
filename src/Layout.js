
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

  function layoutNode(node) {
    var mainAxis = node.style.flexDirection === 'row' ? 'row' : 'column';
    var crossAxis = mainAxis === 'row' ? 'column' : 'row';

    var mainDimInStyle = dim[mainAxis] in node.style;
    if (mainDimInStyle) {
      node.layout[dim[mainAxis]] = node.style[dim[mainAxis]];
    }

    var mainPos = 0;
    var children = [];
    (node.children || []).forEach(function(child) {
      child.layout[pos[mainAxis]] = mainPos;
      child.layout[pos[crossAxis]] = 0;
      layoutNode(child);

      mainPos += child.layout[dim[mainAxis]] + 2 * getMargin(child);
    });

    if (!mainDimInStyle) {
      node.layout[dim[mainAxis]] = mainPos;
    }
    node.layout[dim[crossAxis]] = node.style[dim[crossAxis]];
    node.layout.top += getMargin(node);
    node.layout.left += getMargin(node);
  }

  fillNodes(node);
  node.layout.top = 0;
  node.layout.left = 0;

  layoutNode(node);
  return extractNodes(node);
}

