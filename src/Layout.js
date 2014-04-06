
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

  function capitalizeFirst(str) {
    return str.charAt(0).toUpperCase() + str.slice(1);
  }

  function getMargin(location, node) {
    var key = 'margin' + capitalizeFirst(location);
    if (key in node.style) {
      return node.style[key];
    }

    key = 'margin' + capitalizeFirst(axis[location]);
    if (key in node.style) {
      return node.style[key];
    }

    if ('margin' in node.style) {
      return node.style.margin;
    }

    return 0;
  }

  var axis = {
    left: 'horizontal',
    right: 'horizontal',
    top: 'vertical',
    bottom: 'vertical'
  };
  var leading = {
    row: 'left',
    column: 'top'
  };
  var trailing = {
    row: 'right',
    column: 'bottom'
  };
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
      mainPos += child.layout[dim[mainAxis]] +
        getMargin(leading[mainAxis], child) +
        getMargin(trailing[mainAxis], child);
    });

    if (node.layout[dim[mainAxis]] === undefined && !mainDimInStyle) {
      node.layout[dim[mainAxis]] = mainPos;
    }
    node.layout[dim[crossAxis]] = node.style[dim[crossAxis]];
    node.layout[leading[mainAxis]] += getMargin(leading[mainAxis], node);
    node.layout[leading[crossAxis]] += getMargin(leading[crossAxis], node);
  }

  fillNodes(node);
  node.layout.top = 0;
  node.layout.left = 0;

  layoutNode(node);
  return extractNodes(node);
}

