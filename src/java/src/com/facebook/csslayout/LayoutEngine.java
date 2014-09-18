package com.facebook.csslayout;

public class LayoutEngine {

  private static boolean isUndefined(float f) {
    return Float.compare(f, CSSConstants.UNDEFINED) == 0;
  }

  private static int getLeading(CSSFlexDirection axis) {
    return axis == CSSFlexDirection.COLUMN ? CSSConstants.POSITION_INDEX_TOP : CSSConstants.POSITION_INDEX_LEFT;
  }

  private static int getTrailing(CSSFlexDirection axis) {
    return axis == CSSFlexDirection.COLUMN ? CSSConstants.POSITION_INDEX_BOTTOM : CSSConstants.POSITION_INDEX_RIGHT;
  }

  private static int getPos(CSSFlexDirection axis) {
    return axis == CSSFlexDirection.COLUMN ? CSSConstants.POSITION_INDEX_TOP : CSSConstants.POSITION_INDEX_LEFT;
  }

  private static int getDim(CSSFlexDirection axis) {
    return axis == CSSFlexDirection.COLUMN ? CSSConstants.DIMENSION_INDEX_HEIGHT : CSSConstants.DIMENSION_INDEX_WIDTH;
  }

  private static boolean isDimDefined(CSSNode node, CSSFlexDirection axis) {
    return !isUndefined(node.style.dimensions[getDim(axis)]);
  }

  private static boolean isPosDefined(CSSNode node, int cssPosition) {
    return !isUndefined(node.style.position[cssPosition]);
  }

  private static float getPosition(CSSNode node, int cssPosition) {
    float result = node.style.position[cssPosition];
    return isUndefined(result) ? 0 : result;
  }

  private static float getMargin(CSSNode node, int cssPosition) {
    return node.style.margin[cssPosition];
  }

  private static float getPadding(CSSNode node, int cssPosition) {
    return Math.max(0, node.style.padding[cssPosition]);
  }

  private static float getBorder(CSSNode node, int cssPosition) {
    return Math.max(0, node.style.border[cssPosition]);
  }

  private static float getPaddingAndBorder(CSSNode node, int cssPosition) {
    return getPadding(node, cssPosition) + getBorder(node, cssPosition);
  }

  private static float getMarginAxis(CSSNode node, CSSFlexDirection axis) {
    return getMargin(node, getLeading(axis)) + getMargin(node, getTrailing(axis));
  }

  private static float getPaddingAndBorderAxis(CSSNode node, CSSFlexDirection axis) {
    return getPaddingAndBorder(node, getLeading(axis)) + getPaddingAndBorder(node, getTrailing(axis));
  }

  private static void setDimensionFromStyle(CSSNode node, CSSFlexDirection axis) {
    // The parent already computed us a width or height. We just skip it
    if (!isUndefined(node.layout.dimensions[getDim(axis)])) {
      return;
    }
    // We only run if there's a width or height defined
    if (!isDimDefined(node, axis)) {
      return;
    }

    // The dimensions can never be smaller than the padding and border
    node.layout.dimensions[getDim(axis)] = Math.max(
        node.style.dimensions[getDim(axis)],
        getPaddingAndBorderAxis(node, axis)
    );
  }

  private static float getRelativePosition(CSSNode node, CSSFlexDirection axis) {
    float lead = node.style.position[getLeading(axis)];
    if (!isUndefined(lead)) {
      return lead;
    }
    return -getPosition(node, getTrailing(axis));
  }

  private static float getFlex(CSSNode node) {
    return node.style.flex;
  }

  private static boolean isFlex(CSSNode node) {
    return getPositionType(node) == CSSPositionType.RELATIVE && getFlex(node) > 0;
  }

  private static CSSFlexDirection getFlexDirection(CSSNode node) {
    return node.style.flex_direction;
  }

  private static CSSPositionType getPositionType(CSSNode node) {
    return node.style.position_type;
  }

  private static CSSAlign getAlignItem(CSSNode node, CSSNode child) {
    if (child.style.align_self != CSSAlign.AUTO) {
      return child.style.align_self;
    }
    return node.style.align_items;
  }

  private static CSSJustify getJustifyContent(CSSNode node) {
    return node.style.justify_content;
  }

  private static boolean isMeasureDefined(CSSNode node) {
    return node.isMeasureDefined();
  }

  private static float getDimWithMargin(CSSNode node, CSSFlexDirection axis) {
    return node.layout.dimensions[getDim(axis)] +
        getMargin(node, getLeading(axis)) +
        getMargin(node, getTrailing(axis));
  }

  /*package*/ static void layoutNode(CSSNode node, float parentMaxWidth) {

    //
    // GENERATED LAYOUT CODE GOES BELOW -- see transpile.html
    // (everything below this point is generated)
    //

    CSSFlexDirection mainAxis = getFlexDirection(node);
    CSSFlexDirection crossAxis = mainAxis == CSSFlexDirection.ROW ?
        CSSFlexDirection.COLUMN :
        CSSFlexDirection.ROW;

    // Handle width and height style attributes
    setDimensionFromStyle(node, mainAxis);
    setDimensionFromStyle(node, crossAxis);

    // The position is set by the parent, but we need to complete it with a
    // delta composed of the margin and left/top/right/bottom
    node.layout.position[getLeading(mainAxis)] += getMargin(node, getLeading(mainAxis)) +
        getRelativePosition(node, mainAxis);
    node.layout.position[getLeading(crossAxis)] += getMargin(node, getLeading(crossAxis)) +
        getRelativePosition(node, crossAxis);

    if (isMeasureDefined(node)) {
      float width = CSSConstants.UNDEFINED;
      if (isDimDefined(node, CSSFlexDirection.ROW)) {
        width = node.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH];
      } else if (!isUndefined(node.layout.dimensions[getDim(CSSFlexDirection.ROW)])) {
        width = node.layout.dimensions[getDim(CSSFlexDirection.ROW)];
      } else {
        width = parentMaxWidth -
            getMarginAxis(node, CSSFlexDirection.ROW);
      }
      width -= getPaddingAndBorderAxis(node, CSSFlexDirection.ROW);

      // We only need to give a dimension for the text if we haven't got any
      // for it computed yet. It can either be from the style attribute or because
      // the element is flexible.
      boolean isRowUndefined = !isDimDefined(node, CSSFlexDirection.ROW) &&
          isUndefined(node.layout.dimensions[getDim(CSSFlexDirection.ROW)]);
      boolean isColumnUndefined = !isDimDefined(node, CSSFlexDirection.COLUMN) &&
          isUndefined(node.layout.dimensions[getDim(CSSFlexDirection.COLUMN)]);

      // Let's not measure the text if we already know both dimensions
      if (isRowUndefined || isColumnUndefined) {
        MeasureOutput measure_dim = node.measure(
            width
        );
        if (isRowUndefined) {
          node.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = measure_dim.width +
              getPaddingAndBorderAxis(node, CSSFlexDirection.ROW);
        }
        if (isColumnUndefined) {
          node.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = measure_dim.height +
              getPaddingAndBorderAxis(node, CSSFlexDirection.COLUMN);
        }
      }
      return;
    }

    // Pre-fill some dimensions straight from the parent
    for (int i = 0; i < node.getChildCount(); ++i) {
      CSSNode child = node.getChildAt(i);
      // Pre-fill cross axis dimensions when the child is using stretch before
      // we call the recursive layout pass
      if (getAlignItem(node, child) == CSSAlign.STRETCH &&
          getPositionType(child) == CSSPositionType.RELATIVE &&
          !isUndefined(node.layout.dimensions[getDim(crossAxis)]) &&
          !isDimDefined(child, crossAxis) &&
          !isPosDefined(child, getLeading(crossAxis))) {
        child.layout.dimensions[getDim(crossAxis)] = Math.max(
            node.layout.dimensions[getDim(crossAxis)] -
                getPaddingAndBorderAxis(node, crossAxis) -
                getMarginAxis(child, crossAxis),
            // You never want to go smaller than padding
            getPaddingAndBorderAxis(child, crossAxis)
        );
      } else if (getPositionType(child) == CSSPositionType.ABSOLUTE) {
        // Pre-fill dimensions when using absolute position and both offsets for the axis are defined (either both
        // left and right or top and bottom).
        for (int ii = 0; ii < 2; ii++) {
          CSSFlexDirection axis = (ii != 0) ? CSSFlexDirection.ROW : CSSFlexDirection.COLUMN;
          if (!isUndefined(node.layout.dimensions[getDim(axis)]) &&
              !isDimDefined(child, axis) &&
              isPosDefined(child, getLeading(axis)) &&
              isPosDefined(child, getTrailing(axis))) {
            child.layout.dimensions[getDim(axis)] = Math.max(
                node.layout.dimensions[getDim(axis)] -
                    getPaddingAndBorderAxis(node, axis) -
                    getMarginAxis(child, axis) -
                    getPosition(child, getLeading(axis)) -
                    getPosition(child, getTrailing(axis)),
                // You never want to go smaller than padding
                getPaddingAndBorderAxis(child, axis)
            );
          }
        }
      }
    }

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
    for (int i = 0; i < node.getChildCount(); ++i) {
      CSSNode child = node.getChildAt(i);

      // It only makes sense to consider a child flexible if we have a computed
      // dimension for the node.
      if (!isUndefined(node.layout.dimensions[getDim(mainAxis)]) && isFlex(child)) {
        flexibleChildrenCount++;
        totalFlexible += getFlex(child);

        // Even if we don't know its exact size yet, we already know the padding,
        // border and margin. We'll use this partial information to compute the
        // remaining space.
        mainContentDim += getPaddingAndBorderAxis(child, mainAxis) +
            getMarginAxis(child, mainAxis);

      } else {
        float maxWidth = CSSConstants.UNDEFINED;
        if (mainAxis == CSSFlexDirection.ROW) {
          // do nothing
        } else if (isDimDefined(node, CSSFlexDirection.ROW)) {
          maxWidth = node.layout.dimensions[getDim(CSSFlexDirection.ROW)] -
              getPaddingAndBorderAxis(node, CSSFlexDirection.ROW);
        } else {
          maxWidth = parentMaxWidth -
              getMarginAxis(node, CSSFlexDirection.ROW) -
              getPaddingAndBorderAxis(node, CSSFlexDirection.ROW);
        }

        // This is the main recursive call. We layout non flexible children.
        layoutNode(child, maxWidth);

        // Absolute positioned elements do not take part of the layout, so we
        // don't use them to compute mainContentDim
        if (getPositionType(child) == CSSPositionType.RELATIVE) {
          nonFlexibleChildrenCount++;
          // At this point we know the final size and margin of the element.
          mainContentDim += getDimWithMargin(child, mainAxis);
        }
      }
    }


    // <Loop B> Layout flexible children and allocate empty space

    // In order to position the elements in the main axis, we have two
    // controls. The space between the beginning and the first element
    // and the space between each two elements.
    float leadingMainDim = 0;
    float betweenMainDim = 0;

    // If the dimensions of the current node is defined by its children, they
    // are all going to be packed together and we don't need to compute
    // anything.
    if (!isUndefined(node.layout.dimensions[getDim(mainAxis)])) {
      // The remaining available space that needs to be allocated
      float remainingMainDim = node.layout.dimensions[getDim(mainAxis)] -
          getPaddingAndBorderAxis(node, mainAxis) -
          mainContentDim;

      // If there are flexible children in the mix, they are going to fill the
      // remaining space
      if (flexibleChildrenCount != 0) {
        float flexibleMainDim = remainingMainDim / totalFlexible;

        // The non flexible children can overflow the container, in this case
        // we should just assume that there is no space available.
        if (flexibleMainDim < 0) {
          flexibleMainDim = 0;
        }
        // We iterate over the full array and only apply the action on flexible
        // children. This is faster than actually allocating a new array that
        // contains only flexible children.
        for (int i = 0; i < node.getChildCount(); ++i) {
          CSSNode child = node.getChildAt(i);
          if (isFlex(child)) {
            // At this point we know the final size of the element in the main
            // dimension
            child.layout.dimensions[getDim(mainAxis)] = flexibleMainDim * getFlex(child) +
                getPaddingAndBorderAxis(child, mainAxis);

            float maxWidth = CSSConstants.UNDEFINED;
            if (mainAxis == CSSFlexDirection.ROW) {
              // do nothing
            } else if (isDimDefined(node, CSSFlexDirection.ROW)) {
              maxWidth = node.layout.dimensions[getDim(CSSFlexDirection.ROW)] -
                  getPaddingAndBorderAxis(node, CSSFlexDirection.ROW);
            } else {
              maxWidth = parentMaxWidth -
                  getMarginAxis(node, CSSFlexDirection.ROW) -
                  getPaddingAndBorderAxis(node, CSSFlexDirection.ROW);
            }

            // And we recursively call the layout algorithm for this child
            layoutNode(child, maxWidth);
          }
        }

        // We use justifyContent to figure out how to allocate the remaining
        // space available
      } else {
        CSSJustify justifyContent = getJustifyContent(node);
        if (justifyContent == CSSJustify.FLEX_START) {
          // Do nothing
        } else if (justifyContent == CSSJustify.CENTER) {
          leadingMainDim = remainingMainDim / 2;
        } else if (justifyContent == CSSJustify.FLEX_END) {
          leadingMainDim = remainingMainDim;
        } else if (justifyContent == CSSJustify.SPACE_BETWEEN) {
          remainingMainDim = Math.max(remainingMainDim, 0);
          betweenMainDim = remainingMainDim /
              (flexibleChildrenCount + nonFlexibleChildrenCount - 1);
        } else if (justifyContent == CSSJustify.SPACE_AROUND) {
          // Space on the edges is half of the space between elements
          betweenMainDim = remainingMainDim /
              (flexibleChildrenCount + nonFlexibleChildrenCount);
          leadingMainDim = betweenMainDim / 2;
        }
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
    for (int i = 0; i < node.getChildCount(); ++i) {
      CSSNode child = node.getChildAt(i);

      if (getPositionType(child) == CSSPositionType.ABSOLUTE &&
          isPosDefined(child, getLeading(mainAxis))) {
        // In case the child is position absolute and has left/top being
        // defined, we override the position to whatever the user said
        // (and margin/border).
        child.layout.position[getPos(mainAxis)] = getPosition(child, getLeading(mainAxis)) +
            getBorder(node, getLeading(mainAxis)) +
            getMargin(child, getLeading(mainAxis));
      } else {
        // If the child is position absolute (without top/left) or relative,
        // we put it at the current accumulated offset.
        child.layout.position[getPos(mainAxis)] += mainDim;
      }

      // Now that we placed the element, we need to update the variables
      // We only need to do that for relative elements. Absolute elements
      // do not take part in that phase.
      if (getPositionType(child) == CSSPositionType.RELATIVE) {
        // The main dimension is the sum of all the elements dimension plus
        // the spacing.
        mainDim += betweenMainDim + getDimWithMargin(child, mainAxis);
        // The cross dimension is the max of the elements dimension since there
        // can only be one element in that cross dimension.
        crossDim = Math.max(crossDim, getDimWithMargin(child, crossAxis));
      }
    }

    // If the user didn't specify a width or height, and it has not been set
    // by the container, then we set it via the children.
    if (isUndefined(node.layout.dimensions[getDim(mainAxis)])) {
      node.layout.dimensions[getDim(mainAxis)] = Math.max(
          // We're missing the last padding at this point to get the final
          // dimension
          mainDim + getPaddingAndBorder(node, getTrailing(mainAxis)),
          // We can never assign a width smaller than the padding and borders
          getPaddingAndBorderAxis(node, mainAxis)
      );
    }

    if (isUndefined(node.layout.dimensions[getDim(crossAxis)])) {
      node.layout.dimensions[getDim(crossAxis)] = Math.max(
          // For the cross dim, we add both sides at the end because the value
          // is aggregate via a max function. Intermediate negative values
          // can mess this computation otherwise
          crossDim + getPaddingAndBorderAxis(node, crossAxis),
          getPaddingAndBorderAxis(node, crossAxis)
      );
    }


    // <Loop D> Position elements in the cross axis

    for (int i = 0; i < node.getChildCount(); ++i) {
      CSSNode child = node.getChildAt(i);

      if (getPositionType(child) == CSSPositionType.ABSOLUTE &&
          isPosDefined(child, getLeading(crossAxis))) {
        // In case the child is absolutely positionned and has a
        // top/left/bottom/right being set, we override all the previously
        // computed positions to set it correctly.
        child.layout.position[getPos(crossAxis)] = getPosition(child, getLeading(crossAxis)) +
            getBorder(node, getLeading(crossAxis)) +
            getMargin(child, getLeading(crossAxis));

      } else {
        float leadingCrossDim = getPaddingAndBorder(node, getLeading(crossAxis));

        // For a relative children, we're either using alignItems (parent) or
        // alignSelf (child) in order to determine the position in the cross axis
        if (getPositionType(child) == CSSPositionType.RELATIVE) {
          CSSAlign alignItem = getAlignItem(node, child);
          if (alignItem == CSSAlign.FLEX_START) {
            // Do nothing
          } else if (alignItem == CSSAlign.STRETCH) {
            // You can only stretch if the dimension has not already been set
            // previously.
            if (!isDimDefined(child, crossAxis)) {
              child.layout.dimensions[getDim(crossAxis)] = Math.max(
                  node.layout.dimensions[getDim(crossAxis)] -
                      getPaddingAndBorderAxis(node, crossAxis) -
                      getMarginAxis(child, crossAxis),
                  // You never want to go smaller than padding
                  getPaddingAndBorderAxis(child, crossAxis)
              );
            }
          } else {
            // The remaining space between the parent dimensions+padding and child
            // dimensions+margin.
            float remainingCrossDim = node.layout.dimensions[getDim(crossAxis)] -
                getPaddingAndBorderAxis(node, crossAxis) -
                getDimWithMargin(child, crossAxis);

            if (alignItem == CSSAlign.CENTER) {
              leadingCrossDim += remainingCrossDim / 2;
            } else { // CSSAlign.FLEX_END
              leadingCrossDim += remainingCrossDim;
            }
          }
        }

        // And we apply the position
        child.layout.position[getPos(crossAxis)] += leadingCrossDim;
      }
    }
  }
}
