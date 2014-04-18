
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

  function getSpacing(node, type, location) {
    var key = type + capitalizeFirst(location);
    if (key in node.style) {
      return node.style[key];
    }

    if (type in node.style) {
      return node.style[type];
    }

    return 0;
  }

  function getMargin(node, location) {
    return getSpacing(node, 'margin', location);
  }

  function getPadding(node, location) {
    return getSpacing(node, 'padding', location);
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

  function getFlex(node) {
    return node.style.flex === 1;
  }

  function getDimWithMargin(node, axis) {
    return node.layout[dim[axis]] +
      getMargin(node, leading[axis]) +
      getMargin(node, trailing[axis]);
  }

  function getPosition(node, pos) {
    if (pos in node.style) {
      return node.style[pos];
    }
    return 0;
  }

  // If both left and right are defined, then use left. Otherwise return
  // +left or -right depending on which is defined.
  function getRelativePosition(node, axis) {
    if (leading[axis] in node.style) {
      return getPosition(node, leading[axis]);
    }
    return -getPosition(node, trailing[axis]);
  }

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

  function isUndefined(value) {
    return value === undefined;
  }

  var emptyArray = [];

  function layoutNode(node) {
    var mainAxis = getFlexDirection(node);
    var crossAxis = mainAxis === 'row' ? 'column' : 'row';
    var children = node.children || emptyArray;

    var mainDimInStyle = dim[mainAxis] in node.style;
    if (isUndefined(node.layout[dim[mainAxis]]) && mainDimInStyle) {
      node.layout[dim[mainAxis]] = node.style[dim[mainAxis]];
    }

    var crossDimInStyle = dim[crossAxis] in node.style;
    if (isUndefined(node.layout[dim[crossAxis]]) && crossDimInStyle) {
      node.layout[dim[crossAxis]] = node.style[dim[crossAxis]];
    }

    var mainContentDim = 0;
    var flexibleChildrenCount = 0;
    children.forEach(function(child) {
      if (isUndefined(node.layout[dim[mainAxis]]) || !getFlex(child)) {
        layoutNode(child);
        mainContentDim += getDimWithMargin(child, mainAxis);
      } else {
        flexibleChildrenCount++;
      }
    });

    var leadingMainDim = 0;
    var betweenMainDim = 0;
    if (!isUndefined(node.layout[dim[mainAxis]])) {
      var remainingMainDim = node.layout[dim[mainAxis]] -
        getPadding(node, leading[mainAxis]) -
        getPadding(node, trailing[mainAxis]) -
        mainContentDim;

      if (flexibleChildrenCount) {
        var flexibleMainDim = remainingMainDim / flexibleChildrenCount;
        children.forEach(function(child) {
          if (getFlex(child)) {
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
    var mainPos = getPadding(node, leading[mainAxis]) + leadingMainDim;
    children.forEach(function(child) {
      child.layout[pos[mainAxis]] += mainPos;
      mainPos += getDimWithMargin(child, mainAxis) + betweenMainDim;

      if (!isUndefined(child.layout[dim[crossAxis]])) {
        var childCrossDim = getDimWithMargin(child, crossAxis);
        if (childCrossDim > crossDim) {
          crossDim = childCrossDim;
        }
      }
    });
    mainPos += getPadding(node, trailing[mainAxis]);
    crossDim += getPadding(node, leading[crossAxis]) +
      getPadding(node, trailing[crossAxis]);

    if (isUndefined(node.layout[dim[mainAxis]]) && !mainDimInStyle) {
      node.layout[dim[mainAxis]] = Math.max(mainPos, 0);
    }
    if (isUndefined(node.layout[dim[crossAxis]])) {
      node.layout[dim[crossAxis]] = Math.max(crossDim, 0);
    }

    children.forEach(function(child) {
      var alignItem = getAlignItem(node, child);
      var remainingCrossDim = node.layout[dim[crossAxis]] -
        getDimWithMargin(child, crossAxis) -
        getPadding(node, leading[crossAxis]) -
        getPadding(node, trailing[crossAxis]);

      var leadingCrossDim = getPadding(node, leading[crossAxis]);
      if (alignItem === 'flex-start') {
        // Do nothing
      } else if (alignItem === 'center') {
        leadingCrossDim += remainingCrossDim / 2;
      } else if (alignItem === 'flex-end') {
        leadingCrossDim += remainingCrossDim;
      } else if (alignItem === 'stretch') {
        child.layout[dim[crossAxis]] = node.layout[dim[crossAxis]] -
          getPadding(node, leading[crossAxis]) -
          getPadding(node, trailing[crossAxis]) -
          getMargin(child, leading[crossAxis]) -
          getMargin(child, trailing[crossAxis]);
      }
      child.layout[pos[crossAxis]] += leadingCrossDim;
    });

    node.layout[leading[mainAxis]] += getMargin(node, leading[mainAxis]) +
      getRelativePosition(node, mainAxis);
    node.layout[leading[crossAxis]] += getMargin(node, leading[crossAxis]) +
      getRelativePosition(node, crossAxis);
  }

  fillNodes(node);

  layoutNode(node);
  return extractNodes(node);
}

