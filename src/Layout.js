
var computeLayout = (function() {

  function fillNodes(node) {
    node.layout = {
      width: undefined,
      height: undefined,
      top: 0,
      left: 0
    };
    if (!node.style) {
      node.style = {};
    }
    if (!node.children) {
      node.children = [];
    }
    node.children.forEach(fillNodes);
  }

  function extractNodes(node) {
    var layout = node.layout;
    delete node.layout;
    if (node.children.length > 0) {
      layout.children = node.children.map(extractNodes);
    } else {
      delete node.children;
    }
    return layout;
  }

  function capitalizeFirst(str) {
    return str.charAt(0).toUpperCase() + str.slice(1);
  }

  function getSpacing(node, type, suffix, location) {
    var key = type + capitalizeFirst(location) + suffix;
    if (key in node.style) {
      return node.style[key];
    }

    key = type + suffix;
    if (key in node.style) {
      return node.style[key];
    }

    return 0;
  }

  function getPositiveSpacing(node, type, suffix, location) {
    var key = type + capitalizeFirst(location) + suffix;
    if (key in node.style && node.style[key] >= 0) {
      return node.style[key];
    }

    key = type + suffix;
    if (key in node.style && node.style[key] >= 0) {
      return node.style[key];
    }

    return 0;
  }

  function isUndefined(value) {
    return value === undefined;
  }

  function getMargin(node, location) {
    return getSpacing(node, 'margin', '', location);
  }

  function getPadding(node, location) {
    return getPositiveSpacing(node, 'padding', '', location);
  }

  function getBorder(node, location) {
    return getPositiveSpacing(node, 'border', 'Width', location);
  }

  function getPaddingAndBorder(node, location) {
    return getPadding(node, location) + getBorder(node, location);
  }

  function getMarginAxis(node, axis) {
    return getMargin(node, leading[axis]) + getMargin(node, trailing[axis]);
  }

  function getPaddingAndBorderAxis(node, axis) {
    return getPaddingAndBorder(node, leading[axis]) + getPaddingAndBorder(node, trailing[axis]);
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

  function getPositionType(node) {
    if ('position' in node.style) {
      return node.style.position;
    }
    return 'relative';
  }

  function getFlex(node) {
    return node.style.flex === 1;
  }

  function isFlex(node) {
    return getPositionType(node) === CSS_POSITION_RELATIVE && getFlex(node);
  }

  function getDimWithMargin(node, axis) {
    return node.layout[dim[axis]] + getMarginAxis(node, axis);
  }

  function isDimDefined(node, axis) {
    return !isUndefined(node.style[dim[axis]]) && node.style[dim[axis]] >= 0;
  }

  function isPosDefined(node, pos) {
    return !isUndefined(node.style[pos]);
  }

  function getPosition(node, pos) {
    if (pos in node.style) {
      return node.style[pos];
    }
    return 0;
  }

  function setDimension(node, axis) {
    if (isUndefined(node.layout[dim[axis]]) && isDimDefined(node, axis)) {
      node.layout[dim[axis]] = fmaxf(
        node.style[dim[axis]],
        getPaddingAndBorderAxis(node, axis)
      );
    }
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

  function fmaxf(a, b) {
    if (a > b) {
      return a;
    }
    return b;
  }

  var CSS_FLEX_DIRECTION_ROW = 'row';
  var CSS_FLEX_DIRECTION_COLUMN = 'column';

  var CSS_JUSTIFY_FLEX_START = 'flex-start';
  var CSS_JUSTIFY_CENTER = 'center';
  var CSS_JUSTIFY_FLEX_END = 'flex-end';
  var CSS_JUSTIFY_SPACE_BETWEEN = 'space-between';
  var CSS_JUSTIFY_SPACE_AROUND = 'space-around';

  var CSS_ALIGN_FLEX_START = 'flex-start';
  var CSS_ALIGN_CENTER = 'center';
  var CSS_ALIGN_FLEX_END = 'flex-end';
  var CSS_ALIGN_STRETCH = 'stretch';

  var CSS_POSITION_RELATIVE = 'relative';
  var CSS_POSITION_ABSOLUTE = 'absolute';

  function layoutNode(node) {
    var/*css_flex_direction_t*/ mainAxis = getFlexDirection(node);
    var/*css_flex_direction_t*/ crossAxis = mainAxis === CSS_FLEX_DIRECTION_ROW ?
      CSS_FLEX_DIRECTION_COLUMN :
      CSS_FLEX_DIRECTION_ROW;

    setDimension(node, mainAxis);
    setDimension(node, crossAxis);

    var/*float*/ mainContentDim = 0;
    var/*int*/ flexibleChildrenCount = 0;
    var/*int*/ absoluteChildrenCount = 0;
    for (var/*int*/ i = 0; i < node.children.length; ++i) {
      var/*css_node_t**/ child = node.children[i];
      if (isUndefined(node.layout[dim[mainAxis]]) || !isFlex(child)) {
        layoutNode(child);
        if (getPositionType(child) === CSS_POSITION_RELATIVE) {
          mainContentDim += getDimWithMargin(child, mainAxis);
        } else {
          absoluteChildrenCount++;
        }
      } else {
        flexibleChildrenCount++;
        mainContentDim += getPaddingAndBorderAxis(child, mainAxis) + getMarginAxis(child, mainAxis);
      }
    }

    var/*float*/ leadingMainDim = 0;
    var/*float*/ betweenMainDim = 0;
    if (!isUndefined(node.layout[dim[mainAxis]])) {
      var/*float*/ remainingMainDim = node.layout[dim[mainAxis]] -
        getPaddingAndBorderAxis(node, mainAxis) -
        mainContentDim;

      if (flexibleChildrenCount) {
        var/*float*/ flexibleMainDim = remainingMainDim / flexibleChildrenCount;
        if (flexibleMainDim < 0) {
          flexibleMainDim = 0;
        }
        for (var/*int*/ i = 0; i < node.children.length; ++i) {
          var/*css_node_t**/ child = node.children[i];
          if (isFlex(child)) {
            child.layout[dim[mainAxis]] = flexibleMainDim + getPaddingAndBorderAxis(child, mainAxis);
            layoutNode(child);
          }
        }
      } else {
        var/*css_justify_t*/ justifyContent = getJustifyContent(node);
        if (justifyContent === CSS_JUSTIFY_FLEX_START) {
          // Do nothing
        } else if (justifyContent === CSS_JUSTIFY_CENTER) {
          leadingMainDim = remainingMainDim / 2;
        } else if (justifyContent === CSS_JUSTIFY_FLEX_END) {
          leadingMainDim = remainingMainDim;
        } else if (justifyContent === CSS_JUSTIFY_SPACE_BETWEEN) {
          betweenMainDim = remainingMainDim / (node.children.length - absoluteChildrenCount - 1);
        } else if (justifyContent === CSS_JUSTIFY_SPACE_AROUND) {
          betweenMainDim = remainingMainDim / (node.children.length - absoluteChildrenCount);
          leadingMainDim = betweenMainDim / 2;
        }
      }
    }

    var/*float*/ crossDim = 0;
    var/*float*/ mainPos = getPaddingAndBorder(node, leading[mainAxis]) + leadingMainDim;
    for (var/*int*/ i = 0; i < node.children.length; ++i) {
      var/*css_node_t**/ child = node.children[i];
      if (getPositionType(child) === CSS_POSITION_ABSOLUTE && isPosDefined(child, leading[mainAxis])) {
        child.layout[pos[mainAxis]] = getPosition(child, leading[mainAxis]) +
          getBorder(node, leading[mainAxis]) +
          getMargin(child, leading[mainAxis]);
      } else {
        child.layout[pos[mainAxis]] += mainPos;
      }
      if (getPositionType(child) === CSS_POSITION_RELATIVE) {
        mainPos += getDimWithMargin(child, mainAxis) + betweenMainDim;

        if (!isUndefined(child.layout[dim[crossAxis]])) {
          var/*float*/ childCrossDim = getDimWithMargin(child, crossAxis);
          if (childCrossDim > crossDim) {
            crossDim = childCrossDim;
          }
        }
      }
    }

    mainPos += getPaddingAndBorder(node, trailing[mainAxis]);
    crossDim += getPaddingAndBorderAxis(node, crossAxis);

    if (isUndefined(node.layout[dim[mainAxis]]) && !isDimDefined(node, mainAxis)) {
      node.layout[dim[mainAxis]] = fmaxf(mainPos, getPaddingAndBorderAxis(node, mainAxis));
    }
    if (isUndefined(node.layout[dim[crossAxis]])) {
      node.layout[dim[crossAxis]] = fmaxf(crossDim, getPaddingAndBorderAxis(node, crossAxis));
    }

    for (var/*int*/ i = 0; i < node.children.length; ++i) {
      var/*css_node_t**/ child = node.children[i];

      if (getPositionType(child) === CSS_POSITION_RELATIVE) {
        var/*css_align_t*/ alignItem = getAlignItem(node, child);
        var/*float*/ remainingCrossDim = node.layout[dim[crossAxis]] -
          getDimWithMargin(child, crossAxis) -
          getPaddingAndBorderAxis(node, crossAxis);

        var/*float*/ leadingCrossDim = getPaddingAndBorder(node, leading[crossAxis]);
        if (alignItem === CSS_ALIGN_FLEX_START) {
          // Do nothing
        } else if (alignItem === CSS_ALIGN_CENTER) {
          leadingCrossDim += remainingCrossDim / 2;
        } else if (alignItem === CSS_ALIGN_FLEX_END) {
          leadingCrossDim += remainingCrossDim;
        } else if (alignItem === CSS_ALIGN_STRETCH) {
          if (!isDimDefined(child, crossAxis)) {
            child.layout[dim[crossAxis]] = fmaxf(
              node.layout[dim[crossAxis]] -
                getPaddingAndBorderAxis(node, crossAxis) -
                getMarginAxis(child, crossAxis),
              getPaddingAndBorderAxis(child, crossAxis)
            );
          }
        }
        child.layout[pos[crossAxis]] += leadingCrossDim;
      } else {
        if (isPosDefined(child, leading[crossAxis])) {
          child.layout[pos[crossAxis]] = getPosition(child, leading[crossAxis]) +
            getBorder(node, leading[crossAxis]) +
            getMargin(child, leading[crossAxis]);
        } else {
          child.layout[pos[crossAxis]] += getPaddingAndBorder(node, leading[crossAxis]);
        }
      }
    }

    node.layout[leading[mainAxis]] += getMargin(node, leading[mainAxis]) +
      getRelativePosition(node, mainAxis);
    node.layout[leading[crossAxis]] += getMargin(node, leading[crossAxis]) +
      getRelativePosition(node, crossAxis);
  }

  var fn = function(node) {
    fillNodes(node);
    layoutNode(node);
    return extractNodes(node);
  };
  fn.layoutNode = layoutNode;
  return fn;
})();


