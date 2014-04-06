
function computeLayout(node) {

  function fillNodes(node) {
    node.layout = {
      width: undefined,
      height: undefined,
      top: 0,
      left: 0
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

  var emptyArray = [];

  function layoutNode(node) {
    var mainAxis = node.style.flexDirection === 'row' ? 'row' : 'column';
    var crossAxis = mainAxis === 'row' ? 'column' : 'row';
    var children = node.children || emptyArray;

    var mainDimInStyle = dim[mainAxis] in node.style;
    if (mainDimInStyle) {
      node.layout[dim[mainAxis]] = node.style[dim[mainAxis]];
    }

    var mainContentDim = 0;
    var flexibleChildrenCount = 0;
    children.forEach(function(child) {
      if (!child.style.flex) {
        layoutNode(child);
        mainContentDim += child.layout[dim[mainAxis]];
      } else {
        flexibleChildrenCount++;
      }
    });

    var flexibleMainDim =
      (node.layout[dim[mainAxis]] - mainContentDim) / flexibleChildrenCount;
    children.forEach(function(child) {
      if (child.style.flex) {
        child.layout[dim[mainAxis]] = flexibleMainDim;
        layoutNode(child);
      }
    });

    var mainPos = 0;
    children.forEach(function(child) {
      child.layout[pos[mainAxis]] += mainPos;
      mainPos += child.layout[dim[mainAxis]] + 2 * getMargin(child);
    });

    if (node.layout[dim[mainAxis]] === undefined && !mainDimInStyle) {
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

