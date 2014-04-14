
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

  function getJustifyContent(node) {
    if ('justifyContent' in node.style) {
      return node.style.justifyContent;
    }
    return 'flex-start';
  }

  function getAlignItem(node, child) {
    if ('alignSelf' in child.style) {
      return child.style.alignSelf;
    }
    if ('alignItems' in node.style) {
      return node.style.alignItems;
    }
    return 'flex-start';
  }

  function getFlexDirection(node) {
    if ('flexDirection' in node.style) {
      return node.style.flexDirection;
    }
    return 'column';
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
    var mainAxis = getFlexDirection(node);
    var crossAxis = mainAxis === 'row' ? 'column' : 'row';
    var children = node.children || emptyArray;

    var mainDimInStyle = dim[mainAxis] in node.style;
    if (node.layout[dim[mainAxis]] === undefined && mainDimInStyle) {
      node.layout[dim[mainAxis]] = node.style[dim[mainAxis]];
    }

    var crossDimInStyle = dim[crossAxis] in node.style;
    if (node.layout[dim[crossAxis]] === undefined && crossDimInStyle) {
      node.layout[dim[crossAxis]] = node.style[dim[crossAxis]];
    }

    var mainContentDim = 0;
    var flexibleChildrenCount = 0;
    children.forEach(function(child) {
      if (!child.style.flex) {
        layoutNode(child);
        mainContentDim += child.layout[dim[mainAxis]] +
          getMargin(leading[mainAxis], child) +
          getMargin(trailing[mainAxis], child);
      } else {
        flexibleChildrenCount++;
      }
    });

    var leadingMainDim = 0;
    var betweenMainDim = 0;
    if (node.layout[dim[mainAxis]] !== undefined) {
      var remainingMainDim = node.layout[dim[mainAxis]] - mainContentDim;
      if (flexibleChildrenCount) {
        var flexibleMainDim = remainingMainDim / flexibleChildrenCount;
        children.forEach(function(child) {
          if (child.style.flex) {
            child.layout[dim[mainAxis]] = flexibleMainDim;
            layoutNode(child);
          }
        });
      } else {
        var justifyContent = getJustifyContent(node);
        if (justifyContent == 'flex-start') {
          // Do nothing
        } else if (justifyContent === 'flex-end') {
          leadingMainDim = remainingMainDim;
        } else if (justifyContent === 'center') {
          leadingMainDim = remainingMainDim / 2;
        } else if (justifyContent === 'space-between') {
          betweenMainDim = remainingMainDim / (children.length - 1);
        } else if (justifyContent === 'space-around') {
          betweenMainDim = remainingMainDim / children.length;
          leadingMainDim = betweenMainDim / 2;
        }
      }
    }

    var crossDim = 0;
    var mainPos = leadingMainDim;
    children.forEach(function(child) {
      child.layout[pos[mainAxis]] += mainPos;
      mainPos += child.layout[dim[mainAxis]] +
        getMargin(leading[mainAxis], child) +
        getMargin(trailing[mainAxis], child) +
        betweenMainDim;

      if (child.layout[dim[crossAxis]] !== undefined) {
        var childCrossDim = child.layout[dim[crossAxis]] +
          getMargin(leading[crossAxis], child) +
          getMargin(trailing[crossAxis], child);

        if (childCrossDim > crossDim) {
          crossDim = childCrossDim;
        }
      }
    });

    if (node.layout[dim[mainAxis]] === undefined && !mainDimInStyle) {
      node.layout[dim[mainAxis]] = Math.max(mainPos, 0);
    }
    if (node.layout[dim[crossAxis]] === undefined) {
      node.layout[dim[crossAxis]] = Math.max(crossDim, 0);
    }

    children.forEach(function(child) {
      var alignItem = getAlignItem(node, child);
      var remainingCrossDim = node.layout[dim[crossAxis]] - child.layout[dim[crossAxis]];
      var leadingCrossDim = 0;
      if (alignItem === 'flex-start') {
        // Do nothing
      } else if (alignItem === 'center') {
        leadingCrossDim = remainingCrossDim / 2;
      } else if (alignItem === 'flex-end') {
        leadingCrossDim = remainingCrossDim;
      } else if (alignItem === 'stretch') {
        child.layout[dim[crossAxis]] = node.layout[dim[crossAxis]] -
          getMargin(leading[crossAxis], child) -
          getMargin(trailing[crossAxis], child);
      }
      child.layout[pos[crossAxis]] += leadingCrossDim;
    });

    node.layout[leading[mainAxis]] += getMargin(leading[mainAxis], node);
    node.layout[leading[crossAxis]] += getMargin(leading[crossAxis], node);
  }

  fillNodes(node);
  node.layout.top = 0;
  node.layout.left = 0;

  layoutNode(node);
  return extractNodes(node);
}

