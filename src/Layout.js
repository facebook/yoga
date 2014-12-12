/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var computeLayout = (function() {

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
    return 'stretch';
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
    return node.style.flex;
  }

  function isFlex(node) {
    return (
      getPositionType(node) === CSS_POSITION_RELATIVE &&
      getFlex(node) > 0
    );
  }

  function isFlexWrap(node) {
    return node.style.flexWrap === 'wrap';
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

  function isMeasureDefined(node) {
    return 'measure' in node.style;
  }

  function getPosition(node, pos) {
    if (pos in node.style) {
      return node.style[pos];
    }
    return 0;
  }

  // When the user specifically sets a value for width or height
  function setDimensionFromStyle(node, axis) {
    // The parent already computed us a width or height. We just skip it
    if (!isUndefined(node.layout[dim[axis]])) {
      return;
    }
    // We only run if there's a width or height defined
    if (!isDimDefined(node, axis)) {
      return;
    }

    // The dimensions can never be smaller than the padding and border
    node.layout[dim[axis]] = fmaxf(
      node.style[dim[axis]],
      getPaddingAndBorderAxis(node, axis)
    );
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

  var CSS_UNDEFINED = undefined;

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

  return function layoutNode(node, parentMaxWidth) {
    var/*css_flex_direction_t*/ mainAxis = getFlexDirection(node);
    var/*css_flex_direction_t*/ crossAxis = mainAxis === CSS_FLEX_DIRECTION_ROW ?
      CSS_FLEX_DIRECTION_COLUMN :
      CSS_FLEX_DIRECTION_ROW;

    // Handle width and height style attributes
    setDimensionFromStyle(node, mainAxis);
    setDimensionFromStyle(node, crossAxis);

    // The position is set by the parent, but we need to complete it with a
    // delta composed of the margin and left/top/right/bottom
    node.layout[leading[mainAxis]] += getMargin(node, leading[mainAxis]) +
      getRelativePosition(node, mainAxis);
    node.layout[leading[crossAxis]] += getMargin(node, leading[crossAxis]) +
      getRelativePosition(node, crossAxis);

    if (isMeasureDefined(node)) {
      var/*float*/ width = CSS_UNDEFINED;
      if (isDimDefined(node, CSS_FLEX_DIRECTION_ROW)) {
        width = node.style.width;
      } else if (!isUndefined(node.layout[dim[CSS_FLEX_DIRECTION_ROW]])) {
        width = node.layout[dim[CSS_FLEX_DIRECTION_ROW]];
      } else {
        width = parentMaxWidth -
          getMarginAxis(node, CSS_FLEX_DIRECTION_ROW);
      }
      width -= getPaddingAndBorderAxis(node, CSS_FLEX_DIRECTION_ROW);

      // We only need to give a dimension for the text if we haven't got any
      // for it computed yet. It can either be from the style attribute or because
      // the element is flexible.
      var/*bool*/ isRowUndefined = !isDimDefined(node, CSS_FLEX_DIRECTION_ROW) &&
        isUndefined(node.layout[dim[CSS_FLEX_DIRECTION_ROW]]);
      var/*bool*/ isColumnUndefined = !isDimDefined(node, CSS_FLEX_DIRECTION_COLUMN) &&
        isUndefined(node.layout[dim[CSS_FLEX_DIRECTION_COLUMN]]);

      // Let's not measure the text if we already know both dimensions
      if (isRowUndefined || isColumnUndefined) {
        var/*css_dim_t*/ measure_dim = node.style.measure(
          /*(c)!node->context,*/
          width
        );
        if (isRowUndefined) {
          node.layout.width = measure_dim.width +
            getPaddingAndBorderAxis(node, CSS_FLEX_DIRECTION_ROW);
        }
        if (isColumnUndefined) {
          node.layout.height = measure_dim.height +
            getPaddingAndBorderAxis(node, CSS_FLEX_DIRECTION_COLUMN);
        }
      }
      return;
    }

    // Pre-fill some dimensions straight from the parent
    for (var/*int*/ i = 0; i < node.children.length; ++i) {
      var/*css_node_t**/ child = node.children[i];
      // Pre-fill cross axis dimensions when the child is using stretch before
      // we call the recursive layout pass
      if (getAlignItem(node, child) === CSS_ALIGN_STRETCH &&
          getPositionType(child) === CSS_POSITION_RELATIVE &&
          !isUndefined(node.layout[dim[crossAxis]]) &&
          !isDimDefined(child, crossAxis)) {
        child.layout[dim[crossAxis]] = fmaxf(
          node.layout[dim[crossAxis]] -
            getPaddingAndBorderAxis(node, crossAxis) -
            getMarginAxis(child, crossAxis),
          // You never want to go smaller than padding
          getPaddingAndBorderAxis(child, crossAxis)
        );
      } else if (getPositionType(child) == CSS_POSITION_ABSOLUTE) {
        // Pre-fill dimensions when using absolute position and both offsets for the axis are defined (either both
        // left and right or top and bottom).
        for (var/*int*/ ii = 0; ii < 2; ii++) {
          var/*css_flex_direction_t*/ axis = (ii != 0) ? CSS_FLEX_DIRECTION_ROW : CSS_FLEX_DIRECTION_COLUMN;
          if (!isUndefined(node.layout[dim[axis]]) &&
              !isDimDefined(child, axis) &&
              isPosDefined(child, leading[axis]) &&
              isPosDefined(child, trailing[axis])) {
            child.layout[dim[axis]] = fmaxf(
              node.layout[dim[axis]] -
              getPaddingAndBorderAxis(node, axis) -
              getMarginAxis(child, axis) -
              getPosition(child, leading[axis]) -
              getPosition(child, trailing[axis]),
              // You never want to go smaller than padding
              getPaddingAndBorderAxis(child, axis)
            );
          }
        }
      }
    }

    var/*float*/ definedMainDim = CSS_UNDEFINED;
    if (!isUndefined(node.layout[dim[mainAxis]])) {
      definedMainDim = node.layout[dim[mainAxis]] -
          getPaddingAndBorderAxis(node, mainAxis);
    }

    // We want to execute the next two loops one per line with flex-wrap
    var/*int*/ startLine = 0;
    var/*int*/ endLine = 0;
    var/*int*/ nextOffset = 0;
    var/*int*/ alreadyComputedNextLayout = 0;
    // We aggregate the total dimensions of the container in those two variables
    var/*float*/ linesCrossDim = 0;
    var/*float*/ linesMainDim = 0;
    while (endLine < node.children.length) {
      // <Loop A> Layout non flexible children and count children by type

      // mainContentDim is accumulation of the dimensions and margin of all the
      // non flexible children. This will be used in order to either set the
      // dimensions of the node if none already exist, or to compute the
      // remaining space left for the flexible children.
      var/*float*/ mainContentDim = 0;

      // There are three kind of children, non flexible, flexible and absolute.
      // We need to know how many there are in order to distribute the space.
      var/*int*/ flexibleChildrenCount = 0;
      var/*float*/ totalFlexible = 0;
      var/*int*/ nonFlexibleChildrenCount = 0;
      for (var/*int*/ i = startLine; i < node.children.length; ++i) {
        var/*css_node_t**/ child = node.children[i];
        var/*float*/ nextContentDim = 0;

        // It only makes sense to consider a child flexible if we have a computed
        // dimension for the node.
        if (!isUndefined(node.layout[dim[mainAxis]]) && isFlex(child)) {
          flexibleChildrenCount++;
          totalFlexible += getFlex(child);

          // Even if we don't know its exact size yet, we already know the padding,
          // border and margin. We'll use this partial information to compute the
          // remaining space.
          nextContentDim = getPaddingAndBorderAxis(child, mainAxis) +
            getMarginAxis(child, mainAxis);

        } else {
          var/*float*/ maxWidth = CSS_UNDEFINED;
          if (mainAxis === CSS_FLEX_DIRECTION_ROW) {
            // do nothing
          } else if (isDimDefined(node, CSS_FLEX_DIRECTION_ROW)) {
            maxWidth = node.layout[dim[CSS_FLEX_DIRECTION_ROW]] -
              getPaddingAndBorderAxis(node, CSS_FLEX_DIRECTION_ROW);
          } else {
            maxWidth = parentMaxWidth -
              getMarginAxis(node, CSS_FLEX_DIRECTION_ROW) -
              getPaddingAndBorderAxis(node, CSS_FLEX_DIRECTION_ROW);
          }

          // This is the main recursive call. We layout non flexible children.
          if (alreadyComputedNextLayout === 0) {
            layoutNode(child, maxWidth);
          }

          // Absolute positioned elements do not take part of the layout, so we
          // don't use them to compute mainContentDim
          if (getPositionType(child) === CSS_POSITION_RELATIVE) {
            nonFlexibleChildrenCount++;
            // At this point we know the final size and margin of the element.
            nextContentDim = getDimWithMargin(child, mainAxis);
          }
        }

        // The element we are about to add would make us go to the next line
        if (isFlexWrap(node) &&
            !isUndefined(node.layout[dim[mainAxis]]) &&
            mainContentDim + nextContentDim > definedMainDim &&
            // If there's only one element, then it's bigger than the content
            // and needs its own line
            i !== startLine) {
          alreadyComputedNextLayout = 1;
          break;
        }
        alreadyComputedNextLayout = 0;
        mainContentDim += nextContentDim;
        endLine = i + 1;
      }

      // <Loop B> Layout flexible children and allocate empty space

      // In order to position the elements in the main axis, we have two
      // controls. The space between the beginning and the first element
      // and the space between each two elements.
      var/*float*/ leadingMainDim = 0;
      var/*float*/ betweenMainDim = 0;

      // The remaining available space that needs to be allocated
      var/*float*/ remainingMainDim = 0;
      if (!isUndefined(node.layout[dim[mainAxis]])) {
        remainingMainDim = definedMainDim - mainContentDim;
      } else {
        remainingMainDim = fmaxf(mainContentDim, 0) - mainContentDim;
      }

      // If there are flexible children in the mix, they are going to fill the
      // remaining space
      if (flexibleChildrenCount !== 0) {
        var/*float*/ flexibleMainDim = remainingMainDim / totalFlexible;

        // The non flexible children can overflow the container, in this case
        // we should just assume that there is no space available.
        if (flexibleMainDim < 0) {
          flexibleMainDim = 0;
        }
        // We iterate over the full array and only apply the action on flexible
        // children. This is faster than actually allocating a new array that
        // contains only flexible children.
        for (var/*int*/ i = startLine; i < endLine; ++i) {
          var/*css_node_t**/ child = node.children[i];
          if (isFlex(child)) {
            // At this point we know the final size of the element in the main
            // dimension
            child.layout[dim[mainAxis]] = flexibleMainDim * getFlex(child) +
              getPaddingAndBorderAxis(child, mainAxis);

            var/*float*/ maxWidth = CSS_UNDEFINED;
            if (mainAxis === CSS_FLEX_DIRECTION_ROW) {
              // do nothing
            } else if (isDimDefined(node, CSS_FLEX_DIRECTION_ROW)) {
              maxWidth = node.layout[dim[CSS_FLEX_DIRECTION_ROW]] -
                getPaddingAndBorderAxis(node, CSS_FLEX_DIRECTION_ROW);
            } else {
              maxWidth = parentMaxWidth -
                getMarginAxis(node, CSS_FLEX_DIRECTION_ROW) -
                getPaddingAndBorderAxis(node, CSS_FLEX_DIRECTION_ROW);
            }

            // And we recursively call the layout algorithm for this child
            layoutNode(child, maxWidth);
          }
        }

      // We use justifyContent to figure out how to allocate the remaining
      // space available
      } else {
        var/*css_justify_t*/ justifyContent = getJustifyContent(node);
        if (justifyContent === CSS_JUSTIFY_FLEX_START) {
          // Do nothing
        } else if (justifyContent === CSS_JUSTIFY_CENTER) {
          leadingMainDim = remainingMainDim / 2;
        } else if (justifyContent === CSS_JUSTIFY_FLEX_END) {
          leadingMainDim = remainingMainDim;
        } else if (justifyContent === CSS_JUSTIFY_SPACE_BETWEEN) {
          remainingMainDim = fmaxf(remainingMainDim, 0);
          if (flexibleChildrenCount + nonFlexibleChildrenCount - 1 !== 0) {
            betweenMainDim = remainingMainDim /
              (flexibleChildrenCount + nonFlexibleChildrenCount - 1);
          } else {
            betweenMainDim = 0;
          }
        } else if (justifyContent === CSS_JUSTIFY_SPACE_AROUND) {
          // Space on the edges is half of the space between elements
          betweenMainDim = remainingMainDim /
            (flexibleChildrenCount + nonFlexibleChildrenCount);
          leadingMainDim = betweenMainDim / 2;
        }
      }

      // <Loop C> Position elements in the main axis and compute dimensions

      // At this point, all the children have their dimensions set. We need to
      // find their position. In order to do that, we accumulate data in
      // variables that are also useful to compute the total dimensions of the
      // container!
      var/*float*/ crossDim = 0;
      var/*float*/ mainDim = leadingMainDim +
        getPaddingAndBorder(node, leading[mainAxis]);

      for (var/*int*/ i = startLine; i < endLine; ++i) {
        var/*css_node_t**/ child = node.children[i];

        if (getPositionType(child) === CSS_POSITION_ABSOLUTE &&
            isPosDefined(child, leading[mainAxis])) {
          // In case the child is position absolute and has left/top being
          // defined, we override the position to whatever the user said
          // (and margin/border).
          child.layout[pos[mainAxis]] = getPosition(child, leading[mainAxis]) +
            getBorder(node, leading[mainAxis]) +
            getMargin(child, leading[mainAxis]);
        } else {
          // If the child is position absolute (without top/left) or relative,
          // we put it at the current accumulated offset.
          child.layout[pos[mainAxis]] += mainDim;
        }

        // Now that we placed the element, we need to update the variables
        // We only need to do that for relative elements. Absolute elements
        // do not take part in that phase.
        if (getPositionType(child) === CSS_POSITION_RELATIVE) {
          // The main dimension is the sum of all the elements dimension plus
          // the spacing.
          mainDim += betweenMainDim + getDimWithMargin(child, mainAxis);
          // The cross dimension is the max of the elements dimension since there
          // can only be one element in that cross dimension.
          crossDim = fmaxf(crossDim, getDimWithMargin(child, crossAxis));
        }
      }

      var/*float*/ containerMainAxis = node.layout[dim[mainAxis]];
      // If the user didn't specify a width or height, and it has not been set
      // by the container, then we set it via the children.
      if (isUndefined(node.layout[dim[mainAxis]])) {
        containerMainAxis = fmaxf(
          // We're missing the last padding at this point to get the final
          // dimension
          mainDim + getPaddingAndBorder(node, trailing[mainAxis]),
          // We can never assign a width smaller than the padding and borders
          getPaddingAndBorderAxis(node, mainAxis)
        );
      }

      var/*float*/ containerCrossAxis = node.layout[dim[crossAxis]];
      if (isUndefined(node.layout[dim[crossAxis]])) {
        containerCrossAxis = fmaxf(
          // For the cross dim, we add both sides at the end because the value
          // is aggregate via a max function. Intermediate negative values
          // can mess this computation otherwise
          crossDim + getPaddingAndBorderAxis(node, crossAxis),
          getPaddingAndBorderAxis(node, crossAxis)
        );
      }

      // <Loop D> Position elements in the cross axis

      for (var/*int*/ i = startLine; i < endLine; ++i) {
        var/*css_node_t**/ child = node.children[i];

        if (getPositionType(child) === CSS_POSITION_ABSOLUTE &&
            isPosDefined(child, leading[crossAxis])) {
          // In case the child is absolutely positionned and has a
          // top/left/bottom/right being set, we override all the previously
          // computed positions to set it correctly.
          child.layout[pos[crossAxis]] = getPosition(child, leading[crossAxis]) +
            getBorder(node, leading[crossAxis]) +
            getMargin(child, leading[crossAxis]);

        } else {
          var/*float*/ leadingCrossDim = getPaddingAndBorder(node, leading[crossAxis]);

          // For a relative children, we're either using alignItems (parent) or
          // alignSelf (child) in order to determine the position in the cross axis
          if (getPositionType(child) === CSS_POSITION_RELATIVE) {
            var/*css_align_t*/ alignItem = getAlignItem(node, child);
            if (alignItem === CSS_ALIGN_FLEX_START) {
              // Do nothing
            } else if (alignItem === CSS_ALIGN_STRETCH) {
              // You can only stretch if the dimension has not already been set
              // previously.
              if (!isDimDefined(child, crossAxis)) {
                child.layout[dim[crossAxis]] = fmaxf(
                  containerCrossAxis -
                    getPaddingAndBorderAxis(node, crossAxis) -
                    getMarginAxis(child, crossAxis),
                  // You never want to go smaller than padding
                  getPaddingAndBorderAxis(child, crossAxis)
                );
              }
            } else {
              // The remaining space between the parent dimensions+padding and child
              // dimensions+margin.
              var/*float*/ remainingCrossDim = containerCrossAxis -
                getPaddingAndBorderAxis(node, crossAxis) -
                getDimWithMargin(child, crossAxis);

              if (alignItem === CSS_ALIGN_CENTER) {
                leadingCrossDim += remainingCrossDim / 2;
              } else { // CSS_ALIGN_FLEX_END
                leadingCrossDim += remainingCrossDim;
              }
            }
          }

          // And we apply the position
          child.layout[pos[crossAxis]] += linesCrossDim + leadingCrossDim;
        }
      }

      linesCrossDim += crossDim;
      linesMainDim = fmaxf(linesMainDim, mainDim);
      startLine = endLine;
    }

    // If the user didn't specify a width or height, and it has not been set
    // by the container, then we set it via the children.
    if (isUndefined(node.layout[dim[mainAxis]])) {
      node.layout[dim[mainAxis]] = fmaxf(
        // We're missing the last padding at this point to get the final
        // dimension
        linesMainDim + getPaddingAndBorder(node, trailing[mainAxis]),
        // We can never assign a width smaller than the padding and borders
        getPaddingAndBorderAxis(node, mainAxis)
      );
    }

    if (isUndefined(node.layout[dim[crossAxis]])) {
      node.layout[dim[crossAxis]] = fmaxf(
        // For the cross dim, we add both sides at the end because the value
        // is aggregate via a max function. Intermediate negative values
        // can mess this computation otherwise
        linesCrossDim + getPaddingAndBorderAxis(node, crossAxis),
        getPaddingAndBorderAxis(node, crossAxis)
      );
    }

    // <Loop E> Calculate dimensions for absolutely positioned elements

    for (var/*int*/ i = 0; i < node.children.length; ++i) {
      var/*css_node_t**/ child = node.children[i];
      if (getPositionType(child) == CSS_POSITION_ABSOLUTE) {
        // Pre-fill dimensions when using absolute position and both offsets for the axis are defined (either both
        // left and right or top and bottom).
        for (var/*int*/ ii = 0; ii < 2; ii++) {
          var/*css_flex_direction_t*/ axis = (ii !== 0) ? CSS_FLEX_DIRECTION_ROW : CSS_FLEX_DIRECTION_COLUMN;
          if (!isUndefined(node.layout[dim[axis]]) &&
              !isDimDefined(child, axis) &&
              isPosDefined(child, leading[axis]) &&
              isPosDefined(child, trailing[axis])) {
            child.layout[dim[axis]] = fmaxf(
              node.layout[dim[axis]] -
              getPaddingAndBorderAxis(node, axis) -
              getMarginAxis(child, axis) -
              getPosition(child, leading[axis]) -
              getPosition(child, trailing[axis]),
              // You never want to go smaller than padding
              getPaddingAndBorderAxis(child, axis)
            );
          }
        }
        for (var/*int*/ ii = 0; ii < 2; ii++) {
          var/*css_flex_direction_t*/ axis = (ii !== 0) ? CSS_FLEX_DIRECTION_ROW : CSS_FLEX_DIRECTION_COLUMN;
          if (isPosDefined(child, trailing[axis]) &&
              !isPosDefined(child, leading[axis])) {
            child.layout[leading[axis]] =
              node.layout[dim[axis]] -
              child.layout[dim[axis]] -
              getPosition(child, trailing[axis]);
          }
        }
      }
    }
  };
})();

if (typeof module === 'object') {
  module.exports = computeLayout;
}

