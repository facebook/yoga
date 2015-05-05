/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
package com.facebook.csslayout;

/**
 * Calculates layouts based on CSS style. See {@link #layoutNode(CSSNode, float)}.
 */
public class LayoutEngine {

  private static enum PositionIndex {
    TOP,
    LEFT,
    BOTTOM,
    RIGHT,
  }

  private static enum DimensionIndex {
    WIDTH,
    HEIGHT,
  }

  private static void setLayoutPosition(CSSNode node, PositionIndex position, float value) {
    switch (position) {
      case TOP:
        node.layout.y = value;
        break;
      case LEFT:
        node.layout.x = value;
        break;
      default:
        throw new RuntimeException("Didn't get TOP or LEFT!");
    }
  }

  private static float getLayoutPosition(CSSNode node, PositionIndex position) {
    switch (position) {
      case TOP:
        return node.layout.y;
      case LEFT:
        return node.layout.x;
      default:
        throw new RuntimeException("Didn't get TOP or LEFT!");
    }
  }

  private static void setLayoutDimension(CSSNode node, DimensionIndex dimension, float value) {
    switch (dimension) {
      case WIDTH:
        node.layout.width = value;
        break;
      case HEIGHT:
        node.layout.height = value;
        break;
      default:
        throw new RuntimeException("Someone added a third dimension...");
    }
  }

  private static float getLayoutDimension(CSSNode node, DimensionIndex dimension) {
    switch (dimension) {
      case WIDTH:
        return node.layout.width;
      case HEIGHT:
        return node.layout.height;
      default:
        throw new RuntimeException("Someone added a third dimension...");
    }
  }

  private static float getStylePosition(CSSNode node, PositionIndex position) {
    switch (position) {
      case TOP:
        return node.style.positionTop;
      case BOTTOM:
        return node.style.positionBottom;
      case LEFT:
        return node.style.positionLeft;
      case RIGHT:
        return node.style.positionRight;
      default:
        throw new RuntimeException("Someone added a new cardinal direction...");
    }
  }

  private static float getStyleDimension(CSSNode node, DimensionIndex dimension) {
    switch (dimension) {
      case WIDTH:
        return node.style.width;
      case HEIGHT:
        return node.style.height;
      default:
        throw new RuntimeException("Someone added a third dimension...");
    }
  }

  private static PositionIndex getLeading(CSSFlexDirection axis) {
    return axis == CSSFlexDirection.COLUMN ? PositionIndex.TOP : PositionIndex.LEFT;
  }

  private static PositionIndex getTrailing(CSSFlexDirection axis) {
    return axis == CSSFlexDirection.COLUMN ? PositionIndex.BOTTOM : PositionIndex.RIGHT;
  }

  private static PositionIndex getPos(CSSFlexDirection axis) {
    return axis == CSSFlexDirection.COLUMN ? PositionIndex.TOP : PositionIndex.LEFT;
  }

  private static DimensionIndex getDim(CSSFlexDirection axis) {
    return axis == CSSFlexDirection.COLUMN ? DimensionIndex.HEIGHT : DimensionIndex.WIDTH;
  }

  private static boolean isDimDefined(CSSNode node, CSSFlexDirection axis) {
    float value = getStyleDimension(node, getDim(axis));
    return !CSSConstants.isUndefined(value) && value > 0.0;
  }

  private static boolean isPosDefined(CSSNode node, PositionIndex position) {
    return !CSSConstants.isUndefined(getStylePosition(node, position));
  }

  private static float getPosition(CSSNode node, PositionIndex position) {
    float result = getStylePosition(node, position);
    return CSSConstants.isUndefined(result) ? 0 : result;
  }

  private static float getMargin(CSSNode node, PositionIndex position) {
    switch (position) {
      case TOP:
        return node.style.margin[Spacing.TOP];
      case BOTTOM:
        return node.style.margin[Spacing.BOTTOM];
      case LEFT:
        return node.style.margin[Spacing.LEFT];
      case RIGHT:
        return node.style.margin[Spacing.RIGHT];
      default:
        throw new RuntimeException("Someone added a new cardinal direction...");
    }
  }

  private static float getPadding(CSSNode node, PositionIndex position) {
    switch (position) {
      case TOP:
        return node.style.padding[Spacing.TOP];
      case BOTTOM:
        return node.style.padding[Spacing.BOTTOM];
      case LEFT:
        return node.style.padding[Spacing.LEFT];
      case RIGHT:
        return node.style.padding[Spacing.RIGHT];
      default:
        throw new RuntimeException("Someone added a new cardinal direction...");
    }
  }

  private static float getBorder(CSSNode node, PositionIndex position) {
    switch (position) {
      case TOP:
        return node.style.border[Spacing.TOP];
      case BOTTOM:
        return node.style.border[Spacing.BOTTOM];
      case LEFT:
        return node.style.border[Spacing.LEFT];
      case RIGHT:
        return node.style.border[Spacing.RIGHT];
      default:
        throw new RuntimeException("Someone added a new cardinal direction...");
    }
  }

  private static float getPaddingAndBorder(CSSNode node, PositionIndex position) {
    return getPadding(node, position) + getBorder(node, position);
  }

  private static float getBorderAxis(CSSNode node, CSSFlexDirection axis) {
    return getBorder(node, getLeading(axis)) + getBorder(node, getTrailing(axis));
  }

  private static float getMarginAxis(CSSNode node, CSSFlexDirection axis) {
    return getMargin(node, getLeading(axis)) + getMargin(node, getTrailing(axis));
  }

  private static float getPaddingAndBorderAxis(CSSNode node, CSSFlexDirection axis) {
    return getPaddingAndBorder(
        node,
        getLeading(axis)) + getPaddingAndBorder(node, getTrailing(axis));
  }

  private static float boundAxis(CSSNode node, CSSFlexDirection axis, float value) {
    float min = CSSConstants.UNDEFINED;
    float max = CSSConstants.UNDEFINED;

    if (axis == CSSFlexDirection.COLUMN) {
      min = node.style.minHeight;
      max = node.style.maxHeight;
    } else if (axis == CSSFlexDirection.ROW) {
      min = node.style.minWidth;
      max = node.style.maxWidth;
    }

    float boundValue = value;

    if (!CSSConstants.isUndefined(max) && max >= 0.0 && boundValue > max) {
      boundValue = max;
    }
    if (!CSSConstants.isUndefined(min) && min >= 0.0 && boundValue < min) {
      boundValue = min;
    }

    return boundValue;
  }

  private static void setDimensionFromStyle(CSSNode node, CSSFlexDirection axis) {
    // The parent already computed us a width or height. We just skip it
    if (!CSSConstants.isUndefined(getLayoutDimension(node, getDim(axis)))) {
      return;
    }
    // We only run if there's a width or height defined
    if (!isDimDefined(node, axis)) {
      return;
    }

    // The dimensions can never be smaller than the padding and border
    float maxLayoutDimension = Math.max(
        boundAxis(node, axis, getStyleDimension(node, getDim(axis))),
        getPaddingAndBorderAxis(node, axis));
    setLayoutDimension(node, getDim(axis), maxLayoutDimension);
  }

  private static float getRelativePosition(CSSNode node, CSSFlexDirection axis) {
    float lead = getStylePosition(node, getLeading(axis));
    if (!CSSConstants.isUndefined(lead)) {
      return lead;
    }
    return -getPosition(node, getTrailing(axis));
  }

  private static float getFlex(CSSNode node) {
    return node.style.flex;
  }

  private static CSSFlexDirection getFlexDirection(CSSNode node) {
    return node.style.flexDirection;
  }

  private static CSSPositionType getPositionType(CSSNode node) {
    return node.style.positionType;
  }

  private static CSSAlign getAlignItem(CSSNode node, CSSNode child) {
    if (child.style.alignSelf != CSSAlign.AUTO) {
      return child.style.alignSelf;
    }
    return node.style.alignItems;
  }

  private static CSSJustify getJustifyContent(CSSNode node) {
    return node.style.justifyContent;
  }

  private static boolean isFlexWrap(CSSNode node) {
    return node.style.flexWrap == CSSWrap.WRAP;
  }

  private static boolean isFlex(CSSNode node) {
    return getPositionType(node) == CSSPositionType.RELATIVE && getFlex(node) > 0;
  }

  private static boolean isMeasureDefined(CSSNode node) {
    return node.isMeasureDefined();
  }

  private static float getDimWithMargin(CSSNode node, CSSFlexDirection axis) {
    return getLayoutDimension(node, getDim(axis)) +
        getMargin(node, getLeading(axis)) +
        getMargin(node, getTrailing(axis));
  }

  private static boolean needsRelayout(CSSNode node, float parentMaxWidth) {
    return node.isDirty() ||
        !FloatUtil.floatsEqual(node.lastLayout.requestedHeight, node.layout.height) ||
        !FloatUtil.floatsEqual(node.lastLayout.requestedWidth, node.layout.width) ||
        !FloatUtil.floatsEqual(node.lastLayout.parentMaxWidth, parentMaxWidth);
  }

  /*package*/ static void layoutNode(
      CSSLayoutContext layoutContext,
      CSSNode node,
      float parentMaxWidth) {
    if (needsRelayout(node, parentMaxWidth)) {
      node.lastLayout.requestedWidth = node.layout.width;
      node.lastLayout.requestedHeight = node.layout.height;
      node.lastLayout.parentMaxWidth = parentMaxWidth;

      layoutNodeImpl(layoutContext, node, parentMaxWidth);
      node.lastLayout.copy(node.layout);
    } else {
      node.layout.copy(node.lastLayout);
    }

    node.markHasNewLayout();
  }

  private static void layoutNodeImpl(
      CSSLayoutContext layoutContext,
      CSSNode node,
      float parentMaxWidth) {
    for (int i = 0; i < node.getChildCount(); i++) {
      node.getChildAt(i).layout.resetResult();
    }

    /** START_GENERATED **/
  
  
    CSSFlexDirection mainAxis = getFlexDirection(node);
    CSSFlexDirection crossAxis = mainAxis == CSSFlexDirection.ROW ?
      CSSFlexDirection.COLUMN :
      CSSFlexDirection.ROW;
  
    // Handle width and height style attributes
    setDimensionFromStyle(node, mainAxis);
    setDimensionFromStyle(node, crossAxis);
  
    // The position is set by the parent, but we need to complete it with a
    // delta composed of the margin and left/top/right/bottom
    setLayoutPosition(node, getLeading(mainAxis), getLayoutPosition(node, getLeading(mainAxis)) + getMargin(node, getLeading(mainAxis)) +
      getRelativePosition(node, mainAxis));
    setLayoutPosition(node, getLeading(crossAxis), getLayoutPosition(node, getLeading(crossAxis)) + getMargin(node, getLeading(crossAxis)) +
      getRelativePosition(node, crossAxis));
  
    if (isMeasureDefined(node)) {
      float width = CSSConstants.UNDEFINED;
      if (isDimDefined(node, CSSFlexDirection.ROW)) {
        width = node.style.width;
      } else if (!CSSConstants.isUndefined(getLayoutDimension(node, getDim(CSSFlexDirection.ROW)))) {
        width = getLayoutDimension(node, getDim(CSSFlexDirection.ROW));
      } else {
        width = parentMaxWidth -
          getMarginAxis(node, CSSFlexDirection.ROW);
      }
      width -= getPaddingAndBorderAxis(node, CSSFlexDirection.ROW);
  
      // We only need to give a dimension for the text if we haven't got any
      // for it computed yet. It can either be from the style attribute or because
      // the element is flexible.
      boolean isRowUndefined = !isDimDefined(node, CSSFlexDirection.ROW) &&
        CSSConstants.isUndefined(getLayoutDimension(node, getDim(CSSFlexDirection.ROW)));
      boolean isColumnUndefined = !isDimDefined(node, CSSFlexDirection.COLUMN) &&
        CSSConstants.isUndefined(getLayoutDimension(node, getDim(CSSFlexDirection.COLUMN)));
  
      // Let's not measure the text if we already know both dimensions
      if (isRowUndefined || isColumnUndefined) {
        MeasureOutput measureDim = node.measure(
                    layoutContext.measureOutput,
          width
        );
        if (isRowUndefined) {
          node.layout.width = measureDim.width +
            getPaddingAndBorderAxis(node, CSSFlexDirection.ROW);
        }
        if (isColumnUndefined) {
          node.layout.height = measureDim.height +
            getPaddingAndBorderAxis(node, CSSFlexDirection.COLUMN);
        }
      }
      return;
    }
  
    int i;
    int ii;
    CSSNode child;
    CSSFlexDirection axis;
  
    // Pre-fill some dimensions straight from the parent
    for (i = 0; i < node.getChildCount(); ++i) {
      child = node.getChildAt(i);
      // Pre-fill cross axis dimensions when the child is using stretch before
      // we call the recursive layout pass
      if (getAlignItem(node, child) == CSSAlign.STRETCH &&
          getPositionType(child) == CSSPositionType.RELATIVE &&
          !CSSConstants.isUndefined(getLayoutDimension(node, getDim(crossAxis))) &&
          !isDimDefined(child, crossAxis)) {
        setLayoutDimension(child, getDim(crossAxis), Math.max(
          boundAxis(child, crossAxis, getLayoutDimension(node, getDim(crossAxis)) -
            getPaddingAndBorderAxis(node, crossAxis) -
            getMarginAxis(child, crossAxis)),
          // You never want to go smaller than padding
          getPaddingAndBorderAxis(child, crossAxis)
        ));
      } else if (getPositionType(child) == CSSPositionType.ABSOLUTE) {
        // Pre-fill dimensions when using absolute position and both offsets for the axis are defined (either both
        // left and right or top and bottom).
        for (ii = 0; ii < 2; ii++) {
          axis = (ii != 0) ? CSSFlexDirection.ROW : CSSFlexDirection.COLUMN;
          if (!CSSConstants.isUndefined(getLayoutDimension(node, getDim(axis))) &&
              !isDimDefined(child, axis) &&
              isPosDefined(child, getLeading(axis)) &&
              isPosDefined(child, getTrailing(axis))) {
            setLayoutDimension(child, getDim(axis), Math.max(
              boundAxis(child, axis, getLayoutDimension(node, getDim(axis)) -
                getPaddingAndBorderAxis(node, axis) -
                getMarginAxis(child, axis) -
                getPosition(child, getLeading(axis)) -
                getPosition(child, getTrailing(axis))),
              // You never want to go smaller than padding
              getPaddingAndBorderAxis(child, axis)
            ));
          }
        }
      }
    }
  
    float definedMainDim = CSSConstants.UNDEFINED;
    if (!CSSConstants.isUndefined(getLayoutDimension(node, getDim(mainAxis)))) {
      definedMainDim = getLayoutDimension(node, getDim(mainAxis)) -
          getPaddingAndBorderAxis(node, mainAxis);
    }
  
    // We want to execute the next two loops one per line with flex-wrap
    int startLine = 0;
    int endLine = 0;
    // int nextOffset = 0;
    int alreadyComputedNextLayout = 0;
    // We aggregate the total dimensions of the container in those two variables
    float linesCrossDim = 0;
    float linesMainDim = 0;
    while (endLine < node.getChildCount()) {
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
      for (i = startLine; i < node.getChildCount(); ++i) {
        child = node.getChildAt(i);
        float nextContentDim = 0;
  
        // It only makes sense to consider a child flexible if we have a computed
        // dimension for the node.
        if (!CSSConstants.isUndefined(getLayoutDimension(node, getDim(mainAxis))) && isFlex(child)) {
          flexibleChildrenCount++;
          totalFlexible = totalFlexible + getFlex(child);
  
          // Even if we don't know its exact size yet, we already know the padding,
          // border and margin. We'll use this partial information, which represents
          // the smallest possible size for the child, to compute the remaining
          // available space.
          nextContentDim = getPaddingAndBorderAxis(child, mainAxis) +
            getMarginAxis(child, mainAxis);
  
        } else {
          maxWidth = CSSConstants.UNDEFINED;
          if (mainAxis != CSSFlexDirection.ROW) {
            maxWidth = parentMaxWidth -
              getMarginAxis(node, CSSFlexDirection.ROW) -
              getPaddingAndBorderAxis(node, CSSFlexDirection.ROW);
  
            if (isDimDefined(node, CSSFlexDirection.ROW)) {
              maxWidth = getLayoutDimension(node, getDim(CSSFlexDirection.ROW)) -
                getPaddingAndBorderAxis(node, CSSFlexDirection.ROW);
            }
          }
  
          // This is the main recursive call. We layout non flexible children.
          if (alreadyComputedNextLayout == 0) {
            layoutNode(layoutContext, child, maxWidth);
          }
  
          // Absolute positioned elements do not take part of the layout, so we
          // don't use them to compute mainContentDim
          if (getPositionType(child) == CSSPositionType.RELATIVE) {
            nonFlexibleChildrenCount++;
            // At this point we know the final size and margin of the element.
            nextContentDim = getDimWithMargin(child, mainAxis);
          }
        }
  
        // The element we are about to add would make us go to the next line
        if (isFlexWrap(node) &&
            !CSSConstants.isUndefined(getLayoutDimension(node, getDim(mainAxis))) &&
            mainContentDim + nextContentDim > definedMainDim &&
            // If there's only one element, then it's bigger than the content
            // and needs its own line
            i != startLine) {
          alreadyComputedNextLayout = 1;
          break;
        }
        alreadyComputedNextLayout = 0;
        mainContentDim = mainContentDim + nextContentDim;
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
      if (!CSSConstants.isUndefined(getLayoutDimension(node, getDim(mainAxis)))) {
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
            baseMainDim = flexibleMainDim * getFlex(child) +
                getPaddingAndBorderAxis(child, mainAxis);
            boundMainDim = boundAxis(child, mainAxis, baseMainDim);
  
            if (baseMainDim != boundMainDim) {
              remainingMainDim -= boundMainDim;
              totalFlexible -= getFlex(child);
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
            setLayoutDimension(child, getDim(mainAxis), boundAxis(child, mainAxis,
              flexibleMainDim * getFlex(child) + getPaddingAndBorderAxis(child, mainAxis)
            ));
  
            maxWidth = CSSConstants.UNDEFINED;
            if (isDimDefined(node, CSSFlexDirection.ROW)) {
              maxWidth = getLayoutDimension(node, getDim(CSSFlexDirection.ROW)) -
                getPaddingAndBorderAxis(node, CSSFlexDirection.ROW);
            } else if (mainAxis != CSSFlexDirection.ROW) {
              maxWidth = parentMaxWidth -
                getMarginAxis(node, CSSFlexDirection.ROW) -
                getPaddingAndBorderAxis(node, CSSFlexDirection.ROW);
            }
  
            // And we recursively call the layout algorithm for this child
            layoutNode(layoutContext, child, maxWidth);
          }
        }
  
      // We use justifyContent to figure out how to allocate the remaining
      // space available
      } else {
        CSSJustify justifyContent = getJustifyContent(node);
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
      float mainDim = leadingMainDim +
        getPaddingAndBorder(node, getLeading(mainAxis));
  
      for (i = startLine; i < endLine; ++i) {
        child = node.getChildAt(i);
  
        if (getPositionType(child) == CSSPositionType.ABSOLUTE &&
            isPosDefined(child, getLeading(mainAxis))) {
          // In case the child is position absolute and has left/top being
          // defined, we override the position to whatever the user said
          // (and margin/border).
          setLayoutPosition(child, getPos(mainAxis), getPosition(child, getLeading(mainAxis)) +
            getBorder(node, getLeading(mainAxis)) +
            getMargin(child, getLeading(mainAxis)));
        } else {
          // If the child is position absolute (without top/left) or relative,
          // we put it at the current accumulated offset.
          setLayoutPosition(child, getPos(mainAxis), getLayoutPosition(child, getPos(mainAxis)) + mainDim);
        }
  
        // Now that we placed the element, we need to update the variables
        // We only need to do that for relative elements. Absolute elements
        // do not take part in that phase.
        if (getPositionType(child) == CSSPositionType.RELATIVE) {
          // The main dimension is the sum of all the elements dimension plus
          // the spacing.
          mainDim = mainDim + betweenMainDim + getDimWithMargin(child, mainAxis);
          // The cross dimension is the max of the elements dimension since there
          // can only be one element in that cross dimension.
          crossDim = Math.max(crossDim, boundAxis(child, crossAxis, getDimWithMargin(child, crossAxis)));
        }
      }
  
      float containerCrossAxis = getLayoutDimension(node, getDim(crossAxis));
      if (CSSConstants.isUndefined(getLayoutDimension(node, getDim(crossAxis)))) {
        containerCrossAxis = Math.max(
          // For the cross dim, we add both sides at the end because the value
          // is aggregate via a max function. Intermediate negative values
          // can mess this computation otherwise
          boundAxis(node, crossAxis, crossDim + getPaddingAndBorderAxis(node, crossAxis)),
          getPaddingAndBorderAxis(node, crossAxis)
        );
      }
  
      // <Loop D> Position elements in the cross axis
  
      for (i = startLine; i < endLine; ++i) {
        child = node.getChildAt(i);
  
        if (getPositionType(child) == CSSPositionType.ABSOLUTE &&
            isPosDefined(child, getLeading(crossAxis))) {
          // In case the child is absolutely positionned and has a
          // top/left/bottom/right being set, we override all the previously
          // computed positions to set it correctly.
          setLayoutPosition(child, getPos(crossAxis), getPosition(child, getLeading(crossAxis)) +
            getBorder(node, getLeading(crossAxis)) +
            getMargin(child, getLeading(crossAxis)));
  
        } else {
          float leadingCrossDim = getPaddingAndBorder(node, getLeading(crossAxis));
  
          // For a relative children, we're either using alignItems (parent) or
          // alignSelf (child) in order to determine the position in the cross axis
          if (getPositionType(child) == CSSPositionType.RELATIVE) {
            CSSAlign alignItem = getAlignItem(node, child);
            if (alignItem == CSSAlign.STRETCH) {
              // You can only stretch if the dimension has not already been set
              // previously.
              if (!isDimDefined(child, crossAxis)) {
                setLayoutDimension(child, getDim(crossAxis), Math.max(
                  boundAxis(child, crossAxis, containerCrossAxis -
                    getPaddingAndBorderAxis(node, crossAxis) -
                    getMarginAxis(child, crossAxis)),
                  // You never want to go smaller than padding
                  getPaddingAndBorderAxis(child, crossAxis)
                ));
              }
            } else if (alignItem != CSSAlign.FLEX_START) {
              // The remaining space between the parent dimensions+padding and child
              // dimensions+margin.
              float remainingCrossDim = containerCrossAxis -
                getPaddingAndBorderAxis(node, crossAxis) -
                getDimWithMargin(child, crossAxis);
  
              if (alignItem == CSSAlign.CENTER) {
                leadingCrossDim = leadingCrossDim + remainingCrossDim / 2;
              } else { // CSSAlign.FLEX_END
                leadingCrossDim = leadingCrossDim + remainingCrossDim;
              }
            }
          }
  
          // And we apply the position
          setLayoutPosition(child, getPos(crossAxis), getLayoutPosition(child, getPos(crossAxis)) + linesCrossDim + leadingCrossDim);
        }
      }
  
      linesCrossDim = linesCrossDim + crossDim;
      linesMainDim = Math.max(linesMainDim, mainDim);
      startLine = endLine;
    }
  
    // If the user didn't specify a width or height, and it has not been set
    // by the container, then we set it via the children.
    if (CSSConstants.isUndefined(getLayoutDimension(node, getDim(mainAxis)))) {
      setLayoutDimension(node, getDim(mainAxis), Math.max(
        // We're missing the last padding at this point to get the final
        // dimension
        boundAxis(node, mainAxis, linesMainDim + getPaddingAndBorder(node, getTrailing(mainAxis))),
        // We can never assign a width smaller than the padding and borders
        getPaddingAndBorderAxis(node, mainAxis)
      ));
    }
  
    if (CSSConstants.isUndefined(getLayoutDimension(node, getDim(crossAxis)))) {
      setLayoutDimension(node, getDim(crossAxis), Math.max(
        // For the cross dim, we add both sides at the end because the value
        // is aggregate via a max function. Intermediate negative values
        // can mess this computation otherwise
        boundAxis(node, crossAxis, linesCrossDim + getPaddingAndBorderAxis(node, crossAxis)),
        getPaddingAndBorderAxis(node, crossAxis)
      ));
    }
  
    // <Loop E> Calculate dimensions for absolutely positioned elements
  
    for (i = 0; i < node.getChildCount(); ++i) {
      child = node.getChildAt(i);
      if (getPositionType(child) == CSSPositionType.ABSOLUTE) {
        // Pre-fill dimensions when using absolute position and both offsets for the axis are defined (either both
        // left and right or top and bottom).
        for (ii = 0; ii < 2; ii++) {
          axis = (ii != 0) ? CSSFlexDirection.ROW : CSSFlexDirection.COLUMN;
          if (!CSSConstants.isUndefined(getLayoutDimension(node, getDim(axis))) &&
              !isDimDefined(child, axis) &&
              isPosDefined(child, getLeading(axis)) &&
              isPosDefined(child, getTrailing(axis))) {
            setLayoutDimension(child, getDim(axis), Math.max(
              boundAxis(child, axis, getLayoutDimension(node, getDim(axis)) -
                getBorderAxis(node, axis) -
                getMarginAxis(child, axis) -
                getPosition(child, getLeading(axis)) -
                getPosition(child, getTrailing(axis))
              ),
              // You never want to go smaller than padding
              getPaddingAndBorderAxis(child, axis)
            ));
          }
        }
        for (ii = 0; ii < 2; ii++) {
          axis = (ii != 0) ? CSSFlexDirection.ROW : CSSFlexDirection.COLUMN;
          if (isPosDefined(child, getTrailing(axis)) &&
              !isPosDefined(child, getLeading(axis))) {
            setLayoutPosition(child, getLeading(axis), getLayoutDimension(node, getDim(axis)) -
              getLayoutDimension(child, getDim(axis)) -
              getPosition(child, getTrailing(axis)));
          }
        }
      }
    }
  }
  /** END_GENERATED **/
}
