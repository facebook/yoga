
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

  function isUndefined(value) {
    return value == undefined;
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
    return node.style.flex == 1;
  }

  function getDimWithMargin(node, axis) {
    return node.layout[dim[axis]] +
      getMargin(node, leading[axis]) +
      getMargin(node, trailing[axis]);
  }

  function isDimDefined(node, axis) {
    return !isUndefined(node.style[dim[axis]]);
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

  function layoutNode(node) {
    var/*css_flex_direction_t*/ mainAxis = getFlexDirection(node);
    var/*css_flex_direction_t*/ crossAxis = mainAxis == CSS_FLEX_DIRECTION_ROW ?
      CSS_FLEX_DIRECTION_COLUMN :
      CSS_FLEX_DIRECTION_ROW;

    var/*bool*/ mainDimInStyle = isDimDefined(node, mainAxis);
    if (isUndefined(node.layout[dim[mainAxis]]) && mainDimInStyle) {
      node.layout[dim[mainAxis]] = node.style[dim[mainAxis]];
    }

    var/*bool*/ crossDimInStyle = isDimDefined(node, crossAxis);
    if (isUndefined(node.layout[dim[crossAxis]]) && crossDimInStyle) {
      node.layout[dim[crossAxis]] = node.style[dim[crossAxis]];
    }

    var/*float*/ mainContentDim = 0;
    var/*unsigned int*/ flexibleChildrenCount = 0;
    for (var/*unsigned int*/ i = 0; i < node.children.length; ++i) {
      var/*css_node_t**/ child = node.children[i];
      if (isUndefined(node.layout[dim[mainAxis]]) || !getFlex(child)) {
        layoutNode(child);
        mainContentDim += getDimWithMargin(child, mainAxis);
      } else {
        flexibleChildrenCount++;
      }
    }

    var/*float*/ leadingMainDim = 0;
    var/*float*/ betweenMainDim = 0;
    if (!isUndefined(node.layout[dim[mainAxis]])) {
      var/*float*/ remainingMainDim = node.layout[dim[mainAxis]] -
        getPadding(node, leading[mainAxis]) -
        getPadding(node, trailing[mainAxis]) -
        mainContentDim;

      if (flexibleChildrenCount) {
        var/*float*/ flexibleMainDim = remainingMainDim / flexibleChildrenCount;
        for (var/*unsigned int*/ i = 0; i < node.children.length; ++i) {
          var/*css_node_t**/ child = node.children[i];
          if (getFlex(child)) {
            child.layout[dim[mainAxis]] = flexibleMainDim;
            layoutNode(child);
          }
        }
      } else {
        var/*css_justify_t*/ justifyContent = getJustifyContent(node);
        if (justifyContent == CSS_JUSTIFY_FLEX_START) {
          // Do nothing
        } else if (justifyContent == CSS_JUSTIFY_CENTER) {
          leadingMainDim = remainingMainDim / 2;
        } else if (justifyContent == CSS_JUSTIFY_FLEX_END) {
          leadingMainDim = remainingMainDim;
        } else if (justifyContent == CSS_JUSTIFY_SPACE_BETWEEN) {
          betweenMainDim = remainingMainDim / (node.children.length - 1);
        } else if (justifyContent == CSS_JUSTIFY_SPACE_AROUND) {
          betweenMainDim = remainingMainDim / node.children.length;
          leadingMainDim = betweenMainDim / 2;
        }
      }
    }

    var/*float*/ crossDim = 0;
    var/*float*/ mainPos = getPadding(node, leading[mainAxis]) + leadingMainDim;
    for (var/*unsigned int*/ i = 0; i < node.children.length; ++i) {
      var/*css_node_t**/ child = node.children[i];
      child.layout[pos[mainAxis]] += mainPos;
      mainPos += getDimWithMargin(child, mainAxis) + betweenMainDim;

      if (!isUndefined(child.layout[dim[crossAxis]])) {
        var/*float*/ childCrossDim = getDimWithMargin(child, crossAxis);
        if (childCrossDim > crossDim) {
          crossDim = childCrossDim;
        }
      }
    }
    mainPos += getPadding(node, trailing[mainAxis]);
    crossDim += getPadding(node, leading[crossAxis]) +
      getPadding(node, trailing[crossAxis]);

    if (isUndefined(node.layout[dim[mainAxis]]) && !mainDimInStyle) {
      node.layout[dim[mainAxis]] = mainPos > 0 ? mainPos : 0;
    }
    if (isUndefined(node.layout[dim[crossAxis]])) {
      node.layout[dim[crossAxis]] = crossDim > 0 ? crossDim : 0;
    }

    for (var/*unsigned int*/ i = 0; i < node.children.length; ++i) {
      var/*css_node_t**/ child = node.children[i];
      var/*css_align_t*/ alignItem = getAlignItem(node, child);
      var/*float*/ remainingCrossDim = node.layout[dim[crossAxis]] -
        getDimWithMargin(child, crossAxis) -
        getPadding(node, leading[crossAxis]) -
        getPadding(node, trailing[crossAxis]);

      var/*float*/ leadingCrossDim = getPadding(node, leading[crossAxis]);
      if (alignItem == CSS_ALIGN_FLEX_START) {
        // Do nothing
      } else if (alignItem == CSS_ALIGN_CENTER) {
        leadingCrossDim += remainingCrossDim / 2;
      } else if (alignItem == CSS_ALIGN_FLEX_END) {
        leadingCrossDim += remainingCrossDim;
      } else if (alignItem == CSS_ALIGN_STRETCH) {
        child.layout[dim[crossAxis]] = node.layout[dim[crossAxis]] -
          getPadding(node, leading[crossAxis]) -
          getPadding(node, trailing[crossAxis]) -
          getMargin(child, leading[crossAxis]) -
          getMargin(child, trailing[crossAxis]);
      }
      child.layout[pos[crossAxis]] += leadingCrossDim;
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


var c_code = computeLayout.layoutNode.toString()
  .replace(/\.children\.length/g, '.children_count')
  .replace(/layout\[dim/g, 'layout.dimensions[dim')
  .replace(/layout\[pos/g, 'layout.position[pos')
  .replace(/layout\[leading/g, 'layout.position[leading')
  .replace(/style\[dim/g, 'style.dimensions[dim')
  .replace(/node\./g, 'node->')
  .replace(/child\./g, 'child->')
  .replace(/var\/\*([^\/]+)\*\//g, '$1')
  .replace(/\n  /g, '\n');

console.log(c_code);
