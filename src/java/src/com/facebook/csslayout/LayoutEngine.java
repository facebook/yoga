/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
package com.facebook.csslayout;

import static com.facebook.csslayout.CSSConstants.isUndefined;
import static com.facebook.csslayout.CSSLayout.DIMENSION_HEIGHT;
import static com.facebook.csslayout.CSSLayout.DIMENSION_WIDTH;
import static com.facebook.csslayout.CSSLayout.POSITION_BOTTOM;
import static com.facebook.csslayout.CSSLayout.POSITION_LEFT;
import static com.facebook.csslayout.CSSLayout.POSITION_RIGHT;
import static com.facebook.csslayout.CSSLayout.POSITION_TOP;

/**
 * Calculates layouts based on CSS style. See {@link #layoutNode(CSSNode, float)}.
 */
public class LayoutEngine {

  private static final int CSS_FLEX_DIRECTION_COLUMN =
      CSSFlexDirection.COLUMN.ordinal();
  private static final int CSS_FLEX_DIRECTION_COLUMN_REVERSE =
      CSSFlexDirection.COLUMN_REVERSE.ordinal();
  private static final int CSS_FLEX_DIRECTION_ROW =
      CSSFlexDirection.ROW.ordinal();
  private static final int CSS_FLEX_DIRECTION_ROW_REVERSE =
      CSSFlexDirection.ROW_REVERSE.ordinal();

  private static final int CSS_POSITION_RELATIVE = CSSPositionType.RELATIVE.ordinal();
  private static final int CSS_POSITION_ABSOLUTE = CSSPositionType.ABSOLUTE.ordinal();

  private static final int[] leading = {
      POSITION_TOP,
      POSITION_BOTTOM,
      POSITION_LEFT,
      POSITION_RIGHT,
  };

  private static final int[] trailing = {
      POSITION_BOTTOM,
      POSITION_TOP,
      POSITION_RIGHT,
      POSITION_LEFT,
  };

  private static final int[] pos = {
      POSITION_TOP,
      POSITION_BOTTOM,
      POSITION_LEFT,
      POSITION_RIGHT,
  };

  private static final int[] dim = {
      DIMENSION_HEIGHT,
      DIMENSION_HEIGHT,
      DIMENSION_WIDTH,
      DIMENSION_WIDTH,
  };

  private static boolean isDimDefined(CSSNode node, int axis) {
    float value = node.style.dimensions[dim[axis]];
    return !isUndefined(value) && value > 0.0;
  }

  private static boolean isPosDefined(CSSNode node, int position) {
    return !isUndefined(node.style.position[position]);
  }

  private static float getPosition(CSSNode node, int position) {
    float result = node.style.position[position];
    return isUndefined(result) ? 0 : result;
  }

  private static float getLeadingMargin(CSSNode node, int axis) {
    if (isRowDirection(axis)) {
      float leadingMargin = node.style.margin.getRaw(Spacing.START);
      if (!isUndefined(leadingMargin)) {
        return leadingMargin;
      }
    }

    return node.style.margin.get(leading[axis]);
  }

  private static float getTrailingMargin(CSSNode node, int axis) {
    if (isRowDirection(axis)) {
      float trailingMargin = node.style.margin.getRaw(Spacing.END);
      if (!isUndefined(trailingMargin)) {
        return trailingMargin;
      }
    }

    return node.style.margin.get(trailing[axis]);
  }

  private static float getLeadingPadding(CSSNode node, int axis) {
    if (isRowDirection(axis)) {
      float leadingPadding = node.style.padding.getRaw(Spacing.START);
      if (!isUndefined(leadingPadding)) {
        return leadingPadding;
      }
    }

    return node.style.padding.get(leading[axis]);
  }

  private static float getTrailingPadding(CSSNode node, int axis) {
    if (isRowDirection(axis)) {
      float trailingPadding = node.style.padding.getRaw(Spacing.END);
      if (!isUndefined(trailingPadding)) {
        return trailingPadding;
      }
    }

    return node.style.padding.get(trailing[axis]);
  }

  private static float getLeadingBorder(CSSNode node, int axis) {
    if (isRowDirection(axis)) {
      float leadingBorder = node.style.border.getRaw(Spacing.START);
      if (!isUndefined(leadingBorder)) {
        return leadingBorder;
      }
    }

    return node.style.border.get(leading[axis]);
  }

  private static float getTrailingBorder(CSSNode node, int axis) {
    if (isRowDirection(axis)) {
      float trailingBorder = node.style.border.getRaw(Spacing.END);
      if (!isUndefined(trailingBorder)) {
        return trailingBorder;
      }
    }

    return node.style.border.get(trailing[axis]);
  }

  private static float getLeadingPaddingAndBorder(CSSNode node, int axis) {
    return getLeadingPadding(node, axis) + getLeadingBorder(node, axis);
  }

  private static float getTrailingPaddingAndBorder(CSSNode node, int axis) {
    return getTrailingPadding(node, axis) + getTrailingBorder(node, axis);
  }

  private static float getBorderAxis(CSSNode node, int axis) {
    return getLeadingBorder(node, axis) + getTrailingBorder(node, axis);
  }

  private static float getMarginAxis(CSSNode node, int axis) {
    return getLeadingMargin(node, axis) + getTrailingMargin(node, axis);
  }

  private static float getPaddingAndBorderAxis(CSSNode node, int axis) {
    return getLeadingPaddingAndBorder(node, axis) + getTrailingPaddingAndBorder(node, axis);
  }

  private static float boundAxis(CSSNode node, int axis, float value) {
    float min = CSSConstants.UNDEFINED;
    float max = CSSConstants.UNDEFINED;

    if (isColumnDirection(axis)) {
      min = node.style.minHeight;
      max = node.style.maxHeight;
    } else if (isRowDirection(axis)) {
      min = node.style.minWidth;
      max = node.style.maxWidth;
    }

    float boundValue = value;

    if (!isUndefined(max) && max >= 0.0 && boundValue > max) {
      boundValue = max;
    }
    if (!isUndefined(min) && min >= 0.0 && boundValue < min) {
      boundValue = min;
    }

    return boundValue;
  }

  private static void setDimensionFromStyle(CSSNode node, int axis) {
    // The parent already computed us a width or height. We just skip it
    if (!isUndefined(node.layout.dimensions[dim[axis]])) {
      return;
    }
    // We only run if there's a width or height defined
    if (!isDimDefined(node, axis)) {
      return;
    }

    // The dimensions can never be smaller than the padding and border
    float maxLayoutDimension = Math.max(
        boundAxis(node, axis, node.style.dimensions[dim[axis]]),
        getPaddingAndBorderAxis(node, axis));
    node.layout.dimensions[dim[axis]] = maxLayoutDimension;
  }

  private static void setTrailingPosition(
      CSSNode node,
      CSSNode child,
      int axis) {
    child.layout.position[trailing[axis]] = node.layout.dimensions[dim[axis]] -
        child.layout.dimensions[dim[axis]] - child.layout.position[pos[axis]];
  }

  private static float getRelativePosition(CSSNode node, int axis) {
    float lead = node.style.position[leading[axis]];
    if (!isUndefined(lead)) {
      return lead;
    }
    return -getPosition(node, trailing[axis]);
  }

  private static float getFlex(CSSNode node) {
    return node.style.flex;
  }

  private static boolean isRowDirection(int flexDirection) {
    return flexDirection == CSS_FLEX_DIRECTION_ROW ||
           flexDirection == CSS_FLEX_DIRECTION_ROW_REVERSE;
  }

  private static boolean isColumnDirection(int flexDirection) {
    return flexDirection == CSS_FLEX_DIRECTION_COLUMN ||
           flexDirection == CSS_FLEX_DIRECTION_COLUMN_REVERSE;
  }

  private static int resolveAxis(
      int axis,
      CSSDirection direction) {
    if (direction == CSSDirection.RTL) {
      if (axis == CSS_FLEX_DIRECTION_ROW) {
        return CSS_FLEX_DIRECTION_ROW_REVERSE;
      } else if (axis == CSS_FLEX_DIRECTION_ROW_REVERSE) {
        return CSS_FLEX_DIRECTION_ROW;
      }
    }

    return axis;
  }

  private static CSSDirection resolveDirection(CSSNode node, CSSDirection parentDirection) {
    CSSDirection direction = node.style.direction;
    if (direction == CSSDirection.INHERIT) {
      direction = (parentDirection == null ? CSSDirection.LTR : parentDirection);
    }

    return direction;
  }

  private static int getFlexDirection(CSSNode node) {
    return node.style.flexDirection.ordinal();
  }

  private static int getCrossFlexDirection(
      int flexDirection,
      CSSDirection direction) {
    if (isColumnDirection(flexDirection)) {
      return resolveAxis(CSS_FLEX_DIRECTION_ROW, direction);
    } else {
      return CSS_FLEX_DIRECTION_COLUMN;
    }
  }

  private static CSSAlign getAlignItem(CSSNode node, CSSNode child) {
    if (child.style.alignSelf != CSSAlign.AUTO) {
      return child.style.alignSelf;
    }
    return node.style.alignItems;
  }

  private static boolean isFlexWrap(CSSNode node) {
    return node.style.flexWrap == CSSWrap.WRAP;
  }

  private static boolean isFlex(CSSNode node) {
    return node.style.positionType == CSSPositionType.RELATIVE && node.style.flex > 0;
  }

  private static boolean isMeasureDefined(CSSNode node) {
    return node.isMeasureDefined();
  }

  private static float getDimWithMargin(CSSNode node, int axis) {
    return node.layout.dimensions[dim[axis]] +
        getLeadingMargin(node, axis) +
        getTrailingMargin(node, axis);
  }

  private static boolean needsRelayout(CSSNode node, float parentMaxWidth) {
    return node.isDirty() ||
        !FloatUtil.floatsEqual(
            node.lastLayout.requestedHeight,
            node.layout.dimensions[DIMENSION_HEIGHT]) ||
        !FloatUtil.floatsEqual(
            node.lastLayout.requestedWidth,
            node.layout.dimensions[DIMENSION_WIDTH]) ||
        !FloatUtil.floatsEqual(node.lastLayout.parentMaxWidth, parentMaxWidth);
  }

  /*package*/ static void layoutNode(
      CSSLayoutContext layoutContext,
      CSSNode node,
      float parentMaxWidth,
      CSSDirection parentDirection) {
    if (needsRelayout(node, parentMaxWidth)) {
      node.lastLayout.requestedWidth = node.layout.dimensions[DIMENSION_WIDTH];
      node.lastLayout.requestedHeight = node.layout.dimensions[DIMENSION_HEIGHT];
      node.lastLayout.parentMaxWidth = parentMaxWidth;

      layoutNodeImpl(layoutContext, node, parentMaxWidth, parentDirection);
      node.lastLayout.copy(node.layout);
    } else {
      node.layout.copy(node.lastLayout);
    }

    node.markHasNewLayout();
  }

  private static void layoutNodeImpl(
      CSSLayoutContext layoutContext,
      CSSNode node,
      float parentMaxWidth,
      CSSDirection parentDirection) {
    for (int i = 0; i < node.getChildCount(); i++) {
      node.getChildAt(i).layout.resetResult();
    }

    /** START_GENERATED **/
  
    CSSDirection direction = resolveDirection(node, parentDirection);
    int mainAxis = resolveAxis(getFlexDirection(node), direction);
    int crossAxis = getCrossFlexDirection(mainAxis, direction);
    int resolvedRowAxis = resolveAxis(CSS_FLEX_DIRECTION_ROW, direction);
  
    // Handle width and height style attributes
    setDimensionFromStyle(node, mainAxis);
    setDimensionFromStyle(node, crossAxis);
  
    // Set the resolved resolution in the node's layout
    node.layout.direction = direction;
  
    // The position is set by the parent, but we need to complete it with a
    // delta composed of the margin and left/top/right/bottom
    node.layout.position[leading[mainAxis]] += getLeadingMargin(node, mainAxis) +
      getRelativePosition(node, mainAxis);
    node.layout.position[trailing[mainAxis]] += getTrailingMargin(node, mainAxis) +
      getRelativePosition(node, mainAxis);
    node.layout.position[leading[crossAxis]] += getLeadingMargin(node, crossAxis) +
      getRelativePosition(node, crossAxis);
    node.layout.position[trailing[crossAxis]] += getTrailingMargin(node, crossAxis) +
      getRelativePosition(node, crossAxis);
  
    // Inline immutable values from the target node to avoid excessive method
    // invocations during the layout calculation.
    int childCount = node.getChildCount();
    float paddingAndBorderAxisResolvedRow = getPaddingAndBorderAxis(node, resolvedRowAxis);
  
    if (isMeasureDefined(node)) {
      boolean isResolvedRowDimDefined = !isUndefined(node.layout.dimensions[dim[resolvedRowAxis]]);
  
      float width = CSSConstants.UNDEFINED;
      if (isDimDefined(node, resolvedRowAxis)) {
        width = node.style.dimensions[DIMENSION_WIDTH];
      } else if (isResolvedRowDimDefined) {
        width = node.layout.dimensions[dim[resolvedRowAxis]];
      } else {
        width = parentMaxWidth -
          getMarginAxis(node, resolvedRowAxis);
      }
      width -= paddingAndBorderAxisResolvedRow;
  
      // We only need to give a dimension for the text if we haven't got any
      // for it computed yet. It can either be from the style attribute or because
      // the element is flexible.
      boolean isRowUndefined = !isDimDefined(node, resolvedRowAxis) && !isResolvedRowDimDefined;
      boolean isColumnUndefined = !isDimDefined(node, CSS_FLEX_DIRECTION_COLUMN) &&
        isUndefined(node.layout.dimensions[dim[CSS_FLEX_DIRECTION_COLUMN]]);
  
      // Let's not measure the text if we already know both dimensions
      if (isRowUndefined || isColumnUndefined) {
        MeasureOutput measureDim = node.measure(
          
          layoutContext.measureOutput,
          width
        );
        if (isRowUndefined) {
          node.layout.dimensions[DIMENSION_WIDTH] = measureDim.width +
            paddingAndBorderAxisResolvedRow;
        }
        if (isColumnUndefined) {
          node.layout.dimensions[DIMENSION_HEIGHT] = measureDim.height +
            getPaddingAndBorderAxis(node, CSS_FLEX_DIRECTION_COLUMN);
        }
      }
      if (childCount == 0) {
        return;
      }
    }
  
    boolean isNodeFlexWrap = isFlexWrap(node);
  
    float leadingPaddingAndBorderMain = getLeadingPaddingAndBorder(node, mainAxis);
    float leadingPaddingAndBorderCross = getLeadingPaddingAndBorder(node, crossAxis);
    float paddingAndBorderAxisMain = getPaddingAndBorderAxis(node, mainAxis);
    float paddingAndBorderAxisCross = getPaddingAndBorderAxis(node, crossAxis);
  
    boolean isMainDimDefined = !isUndefined(node.layout.dimensions[dim[mainAxis]]);
    boolean isCrossDimDefined = !isUndefined(node.layout.dimensions[dim[crossAxis]]);
    boolean isMainRowDirection = isRowDirection(mainAxis);
  
    int i;
    int ii;
    CSSNode child;
    int axis;
  
    // Pre-fill some dimensions straight from the parent
    for (i = 0; i < childCount; ++i) {
      child = node.getChildAt(i);
      // Pre-fill cross axis dimensions when the child is using stretch before
      // we call the recursive layout pass
      if (getAlignItem(node, child) == CSSAlign.STRETCH &&
          child.style.positionType == CSSPositionType.RELATIVE &&
          isCrossDimDefined &&
          !isDimDefined(child, crossAxis)) {
        child.layout.dimensions[dim[crossAxis]] = Math.max(
          boundAxis(child, crossAxis, node.layout.dimensions[dim[crossAxis]] -
            paddingAndBorderAxisCross - getMarginAxis(child, crossAxis)),
          // You never want to go smaller than padding
          getPaddingAndBorderAxis(child, crossAxis)
        );
      } else if (child.style.positionType == CSSPositionType.ABSOLUTE) {
        // Pre-fill dimensions when using absolute position and both offsets for the axis are defined (either both
        // left and right or top and bottom).
        for (ii = 0; ii < 2; ii++) {
          axis = (ii != 0) ? CSS_FLEX_DIRECTION_ROW : CSS_FLEX_DIRECTION_COLUMN;
          if (!isUndefined(node.layout.dimensions[dim[axis]]) &&
              !isDimDefined(child, axis) &&
              isPosDefined(child, leading[axis]) &&
              isPosDefined(child, trailing[axis])) {
            child.layout.dimensions[dim[axis]] = Math.max(
              boundAxis(child, axis, node.layout.dimensions[dim[axis]] -
                getPaddingAndBorderAxis(node, axis) -
                getMarginAxis(child, axis) -
                getPosition(child, leading[axis]) -
                getPosition(child, trailing[axis])),
              // You never want to go smaller than padding
              getPaddingAndBorderAxis(child, axis)
            );
          }
        }
      }
    }
  
    float definedMainDim = CSSConstants.UNDEFINED;
    if (isMainDimDefined) {
      definedMainDim = node.layout.dimensions[dim[mainAxis]] - paddingAndBorderAxisMain;
    }
  
    // We want to execute the next two loops one per line with flex-wrap
    int startLine = 0;
    int endLine = 0;
    // int nextOffset = 0;
    int alreadyComputedNextLayout = 0;
    // We aggregate the total dimensions of the container in those two variables
    float linesCrossDim = 0;
    float linesMainDim = 0;
    int linesCount = 0;
    while (endLine < childCount) {
      // <Loop A> Layout non flexible children and count children by type
  
      // mainContentDim is accumulation of the dimensions and margin of all the
      // non flexible children. This will be used in order to either set the
      // dimensions of the node if none already exist, or to compute the
      // remaining space left for the flexible children.
      float mainContentDim = 0;
  
      // There are three kind of children, non flexible, flexible and absolute.
      // We need to know how many there are in order to distribute the space.
      int flexibleChildrenCount = 0;
      float totalFlexible = 0;
      int nonFlexibleChildrenCount = 0;
  
      float maxWidth;
      for (i = startLine; i < childCount; ++i) {
        child = node.getChildAt(i);
        float nextContentDim = 0;
  
        // It only makes sense to consider a child flexible if we have a computed
        // dimension for the node.
        if (isMainDimDefined && isFlex(child)) {
          flexibleChildrenCount++;
          totalFlexible += child.style.flex;
  
          // Even if we don't know its exact size yet, we already know the padding,
          // border and margin. We'll use this partial information, which represents
          // the smallest possible size for the child, to compute the remaining
          // available space.
          nextContentDim = getPaddingAndBorderAxis(child, mainAxis) +
            getMarginAxis(child, mainAxis);
  
        } else {
          maxWidth = CSSConstants.UNDEFINED;
          if (!isMainRowDirection) {
            if (isDimDefined(node, resolvedRowAxis)) {
              maxWidth = node.layout.dimensions[dim[resolvedRowAxis]] -
                paddingAndBorderAxisResolvedRow;
            } else {
              maxWidth = parentMaxWidth -
                getMarginAxis(node, resolvedRowAxis) -
                paddingAndBorderAxisResolvedRow;
            }
          }
  
          // This is the main recursive call. We layout non flexible children.
          if (alreadyComputedNextLayout == 0) {
            layoutNode(layoutContext, child, maxWidth, direction);
          }
  
          // Absolute positioned elements do not take part of the layout, so we
          // don't use them to compute mainContentDim
          if (child.style.positionType == CSSPositionType.RELATIVE) {
            nonFlexibleChildrenCount++;
            // At this point we know the final size and margin of the element.
            nextContentDim = getDimWithMargin(child, mainAxis);
          }
        }
  
        // The element we are about to add would make us go to the next line
        if (isNodeFlexWrap &&
            isMainDimDefined &&
            mainContentDim + nextContentDim > definedMainDim &&
            // If there's only one element, then it's bigger than the content
            // and needs its own line
            i != startLine) {
          nonFlexibleChildrenCount--;
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
      float leadingMainDim = 0;
      float betweenMainDim = 0;
  
      // The remaining available space that needs to be allocated
      float remainingMainDim = 0;
      if (isMainDimDefined) {
        remainingMainDim = definedMainDim - mainContentDim;
      } else {
        remainingMainDim = Math.max(mainContentDim, 0) - mainContentDim;
      }
  
      // If there are flexible children in the mix, they are going to fill the
      // remaining space
      if (flexibleChildrenCount != 0) {
        float flexibleMainDim = remainingMainDim / totalFlexible;
        float baseMainDim;
        float boundMainDim;
  
        // Iterate over every child in the axis. If the flex share of remaining
        // space doesn't meet min/max bounds, remove this child from flex
        // calculations.
        for (i = startLine; i < endLine; ++i) {
          child = node.getChildAt(i);
          if (isFlex(child)) {
            baseMainDim = flexibleMainDim * child.style.flex +
                getPaddingAndBorderAxis(child, mainAxis);
            boundMainDim = boundAxis(child, mainAxis, baseMainDim);
  
            if (baseMainDim != boundMainDim) {
              remainingMainDim -= boundMainDim;
              totalFlexible -= child.style.flex;
            }
          }
        }
        flexibleMainDim = remainingMainDim / totalFlexible;
  
        // The non flexible children can overflow the container, in this case
        // we should just assume that there is no space available.
        if (flexibleMainDim < 0) {
          flexibleMainDim = 0;
        }
        // We iterate over the full array and only apply the action on flexible
        // children. This is faster than actually allocating a new array that
        // contains only flexible children.
        for (i = startLine; i < endLine; ++i) {
          child = node.getChildAt(i);
          if (isFlex(child)) {
            // At this point we know the final size of the element in the main
            // dimension
            child.layout.dimensions[dim[mainAxis]] = boundAxis(child, mainAxis,
              flexibleMainDim * child.style.flex + getPaddingAndBorderAxis(child, mainAxis)
            );
  
            maxWidth = CSSConstants.UNDEFINED;
            if (isDimDefined(node, resolvedRowAxis)) {
              maxWidth = node.layout.dimensions[dim[resolvedRowAxis]] -
                paddingAndBorderAxisResolvedRow;
            } else if (!isMainRowDirection) {
              maxWidth = parentMaxWidth -
                getMarginAxis(node, resolvedRowAxis) -
                paddingAndBorderAxisResolvedRow;
            }
  
            // And we recursively call the layout algorithm for this child
            layoutNode(layoutContext, child, maxWidth, direction);
          }
        }
  
      // We use justifyContent to figure out how to allocate the remaining
      // space available
      } else {
        CSSJustify justifyContent = node.style.justifyContent;
        if (justifyContent == CSSJustify.CENTER) {
          leadingMainDim = remainingMainDim / 2;
        } else if (justifyContent == CSSJustify.FLEX_END) {
          leadingMainDim = remainingMainDim;
        } else if (justifyContent == CSSJustify.SPACE_BETWEEN) {
          remainingMainDim = Math.max(remainingMainDim, 0);
          if (flexibleChildrenCount + nonFlexibleChildrenCount - 1 != 0) {
            betweenMainDim = remainingMainDim /
              (flexibleChildrenCount + nonFlexibleChildrenCount - 1);
          } else {
            betweenMainDim = 0;
          }
        } else if (justifyContent == CSSJustify.SPACE_AROUND) {
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
      float crossDim = 0;
      float mainDim = leadingMainDim + leadingPaddingAndBorderMain;
  
      for (i = startLine; i < endLine; ++i) {
        child = node.getChildAt(i);
        child.lineIndex = linesCount;
  
        if (child.style.positionType == CSSPositionType.ABSOLUTE &&
            isPosDefined(child, leading[mainAxis])) {
          // In case the child is position absolute and has left/top being
          // defined, we override the position to whatever the user said
          // (and margin/border).
          child.layout.position[pos[mainAxis]] = getPosition(child, leading[mainAxis]) +
            getLeadingBorder(node, mainAxis) +
            getLeadingMargin(child, mainAxis);
        } else {
          // If the child is position absolute (without top/left) or relative,
          // we put it at the current accumulated offset.
          child.layout.position[pos[mainAxis]] += mainDim;
  
          // Define the trailing position accordingly.
          if (isMainDimDefined) {
            setTrailingPosition(node, child, mainAxis);
          }
        }
  
        // Now that we placed the element, we need to update the variables
        // We only need to do that for relative elements. Absolute elements
        // do not take part in that phase.
        if (child.style.positionType == CSSPositionType.RELATIVE) {
          // The main dimension is the sum of all the elements dimension plus
          // the spacing.
          mainDim += betweenMainDim + getDimWithMargin(child, mainAxis);
          // The cross dimension is the max of the elements dimension since there
          // can only be one element in that cross dimension.
          crossDim = Math.max(crossDim, boundAxis(child, crossAxis, getDimWithMargin(child, crossAxis)));
        }
      }
  
      float containerCrossAxis = node.layout.dimensions[dim[crossAxis]];
      if (!isCrossDimDefined) {
        containerCrossAxis = Math.max(
          // For the cross dim, we add both sides at the end because the value
          // is aggregate via a max function. Intermediate negative values
          // can mess this computation otherwise
          boundAxis(node, crossAxis, crossDim + paddingAndBorderAxisCross),
          paddingAndBorderAxisCross
        );
      }
  
      // <Loop D> Position elements in the cross axis
      for (i = startLine; i < endLine; ++i) {
        child = node.getChildAt(i);
  
        if (child.style.positionType == CSSPositionType.ABSOLUTE &&
            isPosDefined(child, leading[crossAxis])) {
          // In case the child is absolutely positionned and has a
          // top/left/bottom/right being set, we override all the previously
          // computed positions to set it correctly.
          child.layout.position[pos[crossAxis]] = getPosition(child, leading[crossAxis]) +
            getLeadingBorder(node, crossAxis) +
            getLeadingMargin(child, crossAxis);
  
        } else {
          float leadingCrossDim = leadingPaddingAndBorderCross;
  
          // For a relative children, we're either using alignItems (parent) or
          // alignSelf (child) in order to determine the position in the cross axis
          if (child.style.positionType == CSSPositionType.RELATIVE) {
            CSSAlign alignItem = getAlignItem(node, child);
            if (alignItem == CSSAlign.STRETCH) {
              // You can only stretch if the dimension has not already been set
              // previously.
              if (!isDimDefined(child, crossAxis)) {
                child.layout.dimensions[dim[crossAxis]] = Math.max(
                  boundAxis(child, crossAxis, containerCrossAxis -
                    paddingAndBorderAxisCross - getMarginAxis(child, crossAxis)),
                  // You never want to go smaller than padding
                  getPaddingAndBorderAxis(child, crossAxis)
                );
              }
            } else if (alignItem != CSSAlign.FLEX_START) {
              // The remaining space between the parent dimensions+padding and child
              // dimensions+margin.
              float remainingCrossDim = containerCrossAxis -
                paddingAndBorderAxisCross - getDimWithMargin(child, crossAxis);
  
              if (alignItem == CSSAlign.CENTER) {
                leadingCrossDim += remainingCrossDim / 2;
              } else { // CSSAlign.FLEX_END
                leadingCrossDim += remainingCrossDim;
              }
            }
          }
  
          // And we apply the position
          child.layout.position[pos[crossAxis]] += linesCrossDim + leadingCrossDim;
  
          // Define the trailing position accordingly.
          if (isCrossDimDefined) {
            setTrailingPosition(node, child, crossAxis);
          }
        }
      }
  
      linesCrossDim += crossDim;
      linesMainDim = Math.max(linesMainDim, mainDim);
      linesCount += 1;
      startLine = endLine;
    }
  
    // <Loop E>
    //
    // Note(prenaux): More than one line, we need to layout the crossAxis
    // according to alignContent.
    //
    // Note that we could probably remove <Loop D> and handle the one line case
    // here too, but for the moment this is safer since it won't interfere with
    // previously working code.
    //
    // See specs:
    // http://www.w3.org/TR/2012/CR-css3-flexbox-20120918/#layout-algorithm
    // section 9.4
    //
    if (linesCount > 1 && isCrossDimDefined) {
      float nodeCrossAxisInnerSize = node.layout.dimensions[dim[crossAxis]] -
          paddingAndBorderAxisCross;
      float remainingAlignContentDim = nodeCrossAxisInnerSize - linesCrossDim;
  
      float crossDimLead = 0;
      float currentLead = leadingPaddingAndBorderCross;
  
      CSSAlign alignContent = node.style.alignContent;
      if (alignContent == CSSAlign.FLEX_END) {
        currentLead += remainingAlignContentDim;
      } else if (alignContent == CSSAlign.CENTER) {
        currentLead += remainingAlignContentDim / 2;
      } else if (alignContent == CSSAlign.STRETCH) {
        if (nodeCrossAxisInnerSize > linesCrossDim) {
          crossDimLead = (remainingAlignContentDim / linesCount);
        }
      }
  
      int endIndex = 0;
      for (i = 0; i < linesCount; ++i) {
        int startIndex = endIndex;
  
        // compute the line's height and find the endIndex
        float lineHeight = 0;
        for (ii = startIndex; ii < childCount; ++ii) {
          child = node.getChildAt(ii);
          if (child.style.positionType != CSSPositionType.RELATIVE) {
            continue;
          }
          if (child.lineIndex != i) {
            break;
          }
          if (!isUndefined(child.layout.dimensions[dim[crossAxis]])) {
            lineHeight = Math.max(
              lineHeight,
              child.layout.dimensions[dim[crossAxis]] + getMarginAxis(child, crossAxis)
            );
          }
        }
        endIndex = ii;
        lineHeight += crossDimLead;
  
        for (ii = startIndex; ii < endIndex; ++ii) {
          child = node.getChildAt(ii);
          if (child.style.positionType != CSSPositionType.RELATIVE) {
            continue;
          }
  
          CSSAlign alignContentAlignItem = getAlignItem(node, child);
          if (alignContentAlignItem == CSSAlign.FLEX_START) {
            child.layout.position[pos[crossAxis]] = currentLead + getLeadingMargin(child, crossAxis);
          } else if (alignContentAlignItem == CSSAlign.FLEX_END) {
            child.layout.position[pos[crossAxis]] = currentLead + lineHeight - getTrailingMargin(child, crossAxis) - child.layout.dimensions[dim[crossAxis]];
          } else if (alignContentAlignItem == CSSAlign.CENTER) {
            float childHeight = child.layout.dimensions[dim[crossAxis]];
            child.layout.position[pos[crossAxis]] = currentLead + (lineHeight - childHeight) / 2;
          } else if (alignContentAlignItem == CSSAlign.STRETCH) {
            child.layout.position[pos[crossAxis]] = currentLead + getLeadingMargin(child, crossAxis);
            // TODO(prenaux): Correctly set the height of items with undefined
            //                (auto) crossAxis dimension.
          }
        }
  
        currentLead += lineHeight;
      }
    }
  
    boolean needsMainTrailingPos = false;
    boolean needsCrossTrailingPos = false;
  
    // If the user didn't specify a width or height, and it has not been set
    // by the container, then we set it via the children.
    if (!isMainDimDefined) {
      node.layout.dimensions[dim[mainAxis]] = Math.max(
        // We're missing the last padding at this point to get the final
        // dimension
        boundAxis(node, mainAxis, linesMainDim + getTrailingPaddingAndBorder(node, mainAxis)),
        // We can never assign a width smaller than the padding and borders
        paddingAndBorderAxisMain
      );
  
      needsMainTrailingPos = true;
    }
  
    if (!isCrossDimDefined) {
      node.layout.dimensions[dim[crossAxis]] = Math.max(
        // For the cross dim, we add both sides at the end because the value
        // is aggregate via a max function. Intermediate negative values
        // can mess this computation otherwise
        boundAxis(node, crossAxis, linesCrossDim + paddingAndBorderAxisCross),
        paddingAndBorderAxisCross
      );
  
      needsCrossTrailingPos = true;
    }
  
    // <Loop F> Set trailing position if necessary
    if (needsMainTrailingPos || needsCrossTrailingPos) {
      for (i = 0; i < childCount; ++i) {
        child = node.getChildAt(i);
  
        if (needsMainTrailingPos) {
          setTrailingPosition(node, child, mainAxis);
        }
  
        if (needsCrossTrailingPos) {
          setTrailingPosition(node, child, crossAxis);
        }
      }
    }
  
    // <Loop G> Calculate dimensions for absolutely positioned elements
    for (i = 0; i < childCount; ++i) {
      child = node.getChildAt(i);
      if (child.style.positionType == CSSPositionType.ABSOLUTE) {
        // Pre-fill dimensions when using absolute position and both offsets for the axis are defined (either both
        // left and right or top and bottom).
        for (ii = 0; ii < 2; ii++) {
          axis = (ii != 0) ? CSS_FLEX_DIRECTION_ROW : CSS_FLEX_DIRECTION_COLUMN;
          if (!isUndefined(node.layout.dimensions[dim[axis]]) &&
              !isDimDefined(child, axis) &&
              isPosDefined(child, leading[axis]) &&
              isPosDefined(child, trailing[axis])) {
            child.layout.dimensions[dim[axis]] = Math.max(
              boundAxis(child, axis, node.layout.dimensions[dim[axis]] -
                getBorderAxis(node, axis) -
                getMarginAxis(child, axis) -
                getPosition(child, leading[axis]) -
                getPosition(child, trailing[axis])
              ),
              // You never want to go smaller than padding
              getPaddingAndBorderAxis(child, axis)
            );
          }
        }
        for (ii = 0; ii < 2; ii++) {
          axis = (ii != 0) ? CSS_FLEX_DIRECTION_ROW : CSS_FLEX_DIRECTION_COLUMN;
          if (isPosDefined(child, trailing[axis]) &&
              !isPosDefined(child, leading[axis])) {
            child.layout.position[leading[axis]] =
              node.layout.dimensions[dim[axis]] -
              child.layout.dimensions[dim[axis]] -
              getPosition(child, trailing[axis]);
          }
        }
      }
    }
  }
  /** END_GENERATED **/
}
