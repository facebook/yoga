
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Layout.h"

void init_css_node(css_node_t *node) {
  node->style.align_items = CSS_ALIGN_FLEX_START;

  // Some of the fields default to undefined and not 0
  node->style.dimensions[CSS_WIDTH] = CSS_UNDEFINED;
  node->style.dimensions[CSS_HEIGHT] = CSS_UNDEFINED;

  node->style.position[CSS_LEFT] = CSS_UNDEFINED;
  node->style.position[CSS_TOP] = CSS_UNDEFINED;
  node->style.position[CSS_RIGHT] = CSS_UNDEFINED;
  node->style.position[CSS_BOTTOM] = CSS_UNDEFINED;

  node->layout.dimensions[CSS_WIDTH] = CSS_UNDEFINED;
  node->layout.dimensions[CSS_HEIGHT] = CSS_UNDEFINED;
}

css_node_t *new_css_node() {
  css_node_t *node = calloc(1, sizeof(*node));
  init_css_node(node);
  return node;
}

void init_css_node_children(css_node_t *node, int children_count) {
  node->children = calloc(children_count, sizeof(css_node_t));
  for (int i = 0; i < children_count; ++i) {
    init_css_node(&node->children[i]);
  }
  node->children_count = children_count;
}

void cleanup_css_node(css_node_t *node) {
  for (int i = 0; i < node->children_count; ++i) {
    cleanup_css_node(&node->children[i]);
  }
  free(node->children);
}

void free_css_node(css_node_t *node) {
  cleanup_css_node(node);
  free(node);
}

void indent(int n) {
  for (int i = 0; i < n; ++i) {
    printf("  ");
  }
}

void print_number_0(const char *str, float number) {
  if (number != 0) {
    printf("%s: %g, ", str, number);
  }
}

void print_number_nan(const char *str, float number) {
  if (!isnan(number)) {
    printf("%s: %g, ", str, number);
  }
}

bool four_equal(float four[4]) {
  return
    four[0] == four[1] &&
    four[0] == four[2] &&
    four[0] == four[3];
}

void print_style(css_node_t *node, int level) {
  indent(level);
  printf("{");
  if (node->style.flex_direction == CSS_FLEX_DIRECTION_ROW) {
    printf("flexDirection: 'row', ");
  }

  if (node->style.justify_content == CSS_JUSTIFY_CENTER) {
    printf("justifyContent: 'center', ");
  } else if (node->style.justify_content == CSS_JUSTIFY_FLEX_END) {
    printf("justifyContent: 'flex-end', ");
  } else if (node->style.justify_content == CSS_JUSTIFY_SPACE_AROUND) {
    printf("justifyContent: 'space-around', ");
  } else if (node->style.justify_content == CSS_JUSTIFY_SPACE_BETWEEN) {
    printf("justifyContent: 'space-between', ");
  }

  if (node->style.align_items == CSS_ALIGN_CENTER) {
    printf("alignItems: 'center', ");
  } else if (node->style.align_items == CSS_ALIGN_FLEX_END) {
    printf("alignItems: 'flex-end', ");
  } else if (node->style.align_items == CSS_ALIGN_STRETCH) {
    printf("alignItems: 'stretch', ");
  }

  if (node->style.align_self == CSS_ALIGN_FLEX_START) {
    printf("alignSelf: 'flex-start', ");
  } else if (node->style.align_self == CSS_ALIGN_CENTER) {
    printf("alignSelf: 'center', ");
  } else if (node->style.align_self == CSS_ALIGN_FLEX_END) {
    printf("alignSelf: 'flex-end', ");
  } else if (node->style.align_self == CSS_ALIGN_STRETCH) {
    printf("alignSelf: 'stretch', ");
  }

  if (node->style.flex == CSS_FLEX_ONE) {
    printf("flex: 1, ");
  }

  if (four_equal(node->style.margin)) {
    print_number_0("margin", node->style.margin[CSS_LEFT]);
  } else {
    print_number_0("marginLeft", node->style.margin[CSS_LEFT]);
    print_number_0("marginRight", node->style.margin[CSS_RIGHT]);
    print_number_0("marginTop", node->style.margin[CSS_TOP]);
    print_number_0("marginBottom", node->style.margin[CSS_BOTTOM]);
  }

  if (four_equal(node->style.padding)) {
    print_number_0("padding", node->style.margin[CSS_LEFT]);
  } else {
    print_number_0("paddingLeft", node->style.padding[CSS_LEFT]);
    print_number_0("paddingRight", node->style.padding[CSS_RIGHT]);
    print_number_0("paddingTop", node->style.padding[CSS_TOP]);
    print_number_0("paddingBottom", node->style.padding[CSS_BOTTOM]);
  }

  if (four_equal(node->style.border)) {
    print_number_0("borderWidth", node->style.border[CSS_LEFT]);
  } else {
    print_number_0("borderLeftWidth", node->style.border[CSS_LEFT]);
    print_number_0("borderRightWidth", node->style.border[CSS_RIGHT]);
    print_number_0("borderTopWidth", node->style.border[CSS_TOP]);
    print_number_0("borderBottomWidth", node->style.border[CSS_BOTTOM]);
  }

  print_number_nan("width", node->style.dimensions[CSS_WIDTH]);
  print_number_nan("height", node->style.dimensions[CSS_HEIGHT]);

  print_number_nan("left", node->style.position[CSS_LEFT]);
  print_number_nan("right", node->style.position[CSS_RIGHT]);
  print_number_nan("top", node->style.position[CSS_TOP]);
  print_number_nan("bottom", node->style.position[CSS_BOTTOM]);

  if (node->children_count > 0) {
    printf("children: [\n");
    for (int i = 0; i < node->children_count; ++i) {
      print_style(&node->children[i], level + 1);
    }
    indent(level);
    printf("]},\n");
  } else {
    printf("},\n");
  }
}

void print_layout(css_node_t *node, int level) {
  indent(level);
  printf("{");
  printf("width: %g, ", node->layout.dimensions[CSS_WIDTH]);
  printf("height: %g, ", node->layout.dimensions[CSS_HEIGHT]);
  printf("top: %g, ", node->layout.position[CSS_TOP]);
  printf("left: %g, ", node->layout.position[CSS_LEFT]);

  if (node->children_count > 0) {
    printf("children: [\n");
    for (int i = 0; i < node->children_count; ++i) {
      print_layout(&node->children[i], level + 1);
    }
    indent(level);
    printf("]},\n");
  } else {
    printf("},\n");
  }
}



int leading[2] = {
  /* CSS_FLEX_DIRECTION_COLUMN = */ CSS_TOP,
  /* CSS_FLEX_DIRECTION_ROW = */ CSS_LEFT
};
int trailing[2] = {
  /* CSS_FLEX_DIRECTION_COLUMN = */ CSS_BOTTOM,
  /* CSS_FLEX_DIRECTION_ROW = */ CSS_RIGHT
};
int pos[2] = {
  /* CSS_FLEX_DIRECTION_COLUMN = */ CSS_TOP,
  /* CSS_FLEX_DIRECTION_ROW = */ CSS_LEFT
};
int dim[2] = {
  /* CSS_FLEX_DIRECTION_COLUMN = */ CSS_HEIGHT,
  /* CSS_FLEX_DIRECTION_ROW = */ CSS_WIDTH
};



bool isUndefined(float value) {
  return isnan(value);
}

float getMargin(css_node_t *node, int location) {
  return node->style.margin[location];
}

float getPadding(css_node_t *node, int location) {
  if (node->style.padding[location] >= 0) {
    return node->style.padding[location];
  }
  return 0;
}

float getBorder(css_node_t *node, int location) {
  if (node->style.border[location] >= 0) {
    return node->style.border[location];
  }
  return 0;
}

float getPaddingAndBorder(css_node_t *node, int location) {
  return getPadding(node, location) + getBorder(node, location);
}

float getMarginAxis(css_node_t *node, css_flex_direction_t axis) {
  return getMargin(node, leading[axis]) + getMargin(node, trailing[axis]);
}

float getPaddingAndBorderAxis(css_node_t *node, css_flex_direction_t axis) {
  return getPaddingAndBorder(node, leading[axis]) + getPaddingAndBorder(node, trailing[axis]);
}

css_position_type_t getPositionType(css_node_t *node) {
  return node->style.position_type;
}

css_justify_t getJustifyContent(css_node_t *node) {
  return node->style.justify_content;
}

css_align_t getAlignItem(css_node_t *node, css_node_t *child) {
  if (child->style.align_self != CSS_ALIGN_AUTO) {
    return child->style.align_self;
  }
  return node->style.align_items;
}

css_flex_direction_t getFlexDirection(css_node_t *node) {
  return node->style.flex_direction;
}

css_flex_t getFlex(css_node_t *node) {
  return node->style.flex;
}

bool isFlex(css_node_t *node) {
  return getPositionType(node) == CSS_POSITION_RELATIVE && getFlex(node);
}

float getDimWithMargin(css_node_t *node, css_flex_direction_t axis) {
  return node->layout.dimensions[dim[axis]] +
    getMargin(node, leading[axis]) +
    getMargin(node, trailing[axis]);
}

bool isDimDefined(css_node_t *node, css_flex_direction_t axis) {
  return !isUndefined(node->style.dimensions[dim[axis]]);
}

bool isPosDefined(css_node_t *node, css_position_t pos) {
  return !isUndefined(node->style.position[pos]);
}

bool isMeasureDefined(css_node_t *node) {
  return node->style.measure;
}

float getPosition(css_node_t *node, css_position_t pos) {
  float result = node->style.position[pos];
  if (!isUndefined(result)) {
    return result;
  }
  return 0;
}

// When the user specifically sets a value for width or height
void setDimensionFromStyle(css_node_t *node, css_flex_direction_t axis) {
  // The parent already computed us a width or height. We just skip it
  if (!isUndefined(node->layout.dimensions[dim[axis]])) {
    return;
  }
  // We only run if there's a width or height defined
  if (!isDimDefined(node, axis)) {
    return;
  }

  // The dimensions can never be smaller than the padding and border
  node->layout.dimensions[dim[axis]] = fmaxf(
    node->style.dimensions[dim[axis]],
    getPaddingAndBorderAxis(node, axis)
  );
}

// If both left and right are defined, then use left. Otherwise return
// +left or -right depending on which is defined.
float getRelativePosition(css_node_t *node, css_flex_direction_t axis) {
  float lead = node->style.position[leading[axis]];
  if (!isUndefined(lead)) {
    return lead;
  }
  return -getPosition(node, trailing[axis]);
}

void layoutNode(css_node_t *node) {
  css_flex_direction_t mainAxis = getFlexDirection(node);
  css_flex_direction_t crossAxis = mainAxis == CSS_FLEX_DIRECTION_ROW ?
    CSS_FLEX_DIRECTION_COLUMN :
    CSS_FLEX_DIRECTION_ROW;

  // Handle width and height style attributes
  setDimensionFromStyle(node, mainAxis);
  setDimensionFromStyle(node, crossAxis);

  // The position is set by the parent, but we need to complete it with a
  // delta composed of the margin and left/top/right/bottom
  node->layout.position[leading[mainAxis]] += getMargin(node, leading[mainAxis]) +
    getRelativePosition(node, mainAxis);
  node->layout.position[leading[crossAxis]] += getMargin(node, leading[crossAxis]) +
    getRelativePosition(node, crossAxis);

  if (isMeasureDefined(node)) {
    float width = CSS_UNDEFINED;
    css_measure_type_t type = CSS_MEASURE_VALUE;

    if (isDimDefined(node, CSS_FLEX_DIRECTION_ROW)) {
      width = node->style.dimensions[CSS_WIDTH];
    } else if (getPositionType(node) == CSS_POSITION_ABSOLUTE) {
      type = CSS_MEASURE_SHRINK;
    } else {
      type = CSS_MEASURE_GROW;
    }

    css_dim_t measure_dim = node->style.measure(
      node->style.measure_context,
      type,
      width
    );
    if (!isDimDefined(node, CSS_FLEX_DIRECTION_ROW)) {
      node->layout.dimensions[CSS_WIDTH] = measure_dim.dimensions[CSS_WIDTH] +
        getPaddingAndBorderAxis(node, CSS_FLEX_DIRECTION_ROW);
    }
    if (!isDimDefined(node, CSS_FLEX_DIRECTION_COLUMN)) {
      node->layout.dimensions[CSS_HEIGHT] = measure_dim.dimensions[CSS_HEIGHT] +
        getPaddingAndBorderAxis(node, CSS_FLEX_DIRECTION_COLUMN);
    }
    return;
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
  int nonFlexibleChildrenCount = 0;
  for (int i = 0; i < node->children_count; ++i) {
    css_node_t* child = &node->children[i];

    // It only makes sense to consider a child flexible if we have a computed
    // dimension for the node->
    if (!isUndefined(node->layout.dimensions[dim[mainAxis]]) && isFlex(child)) {
      flexibleChildrenCount++;

      // Even if we don't know its exact size yet, we already know the padding,
      // border and margin. We'll use this partial information to compute the
      // remaining space.
      mainContentDim += getPaddingAndBorderAxis(child, mainAxis) +
        getMarginAxis(child, mainAxis);

    } else {
      // This is the main recursive call. We layout non flexible children.
      layoutNode(child);

      // Absolute positioned elements do not take part of the layout, so we
      // don't use them to compute mainContentDim
      if (getPositionType(child) == CSS_POSITION_RELATIVE) {
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
  if (!isUndefined(node->layout.dimensions[dim[mainAxis]])) {

    // The remaining available space that's needs to be allocated
    float remainingMainDim = node->layout.dimensions[dim[mainAxis]] -
      getPaddingAndBorderAxis(node, mainAxis) -
      mainContentDim;

    // If there are flexible children in the mix, they are going to fill the
    // remaining space
    if (flexibleChildrenCount) {
      float flexibleMainDim = remainingMainDim / flexibleChildrenCount;

      // The non flexible children can overflow the container, in this case
      // we should just assume that there is no space available.
      if (flexibleMainDim < 0) {
        flexibleMainDim = 0;
      }
      // We iterate over the full array and only apply the action on flexible
      // children. This is faster than actually allocating a new array that
      // contains only flexible children.
      for (int i = 0; i < node->children_count; ++i) {
        css_node_t* child = &node->children[i];
        if (isFlex(child)) {
          // At this point we know the final size of the element in the main
          // dimension
          child->layout.dimensions[dim[mainAxis]] = flexibleMainDim +
            getPaddingAndBorderAxis(child, mainAxis);

          // And we recursively call the layout algorithm for this child
          layoutNode(child);
        }
      }

    // We use justifyContent to figure out how to allocate the remaining
    // space available
    } else {
      css_justify_t justifyContent = getJustifyContent(node);
      if (justifyContent == CSS_JUSTIFY_FLEX_START) {
        // Do nothing
      } else if (justifyContent == CSS_JUSTIFY_CENTER) {
        leadingMainDim = remainingMainDim / 2;
      } else if (justifyContent == CSS_JUSTIFY_FLEX_END) {
        leadingMainDim = remainingMainDim;
      } else if (justifyContent == CSS_JUSTIFY_SPACE_BETWEEN) {
        betweenMainDim = remainingMainDim /
          (flexibleChildrenCount + nonFlexibleChildrenCount - 1);
      } else if (justifyContent == CSS_JUSTIFY_SPACE_AROUND) {
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
    getPaddingAndBorder(node, leading[mainAxis]);
  for (int i = 0; i < node->children_count; ++i) {
    css_node_t* child = &node->children[i];

    if (getPositionType(child) == CSS_POSITION_ABSOLUTE &&
        isPosDefined(child, leading[mainAxis])) {
      // In case the child is position absolute and has left/top being
      // defined, we override the position to whatever the user said
      // (and margin/border).
      child->layout.position[pos[mainAxis]] = getPosition(child, leading[mainAxis]) +
        getBorder(node, leading[mainAxis]) +
        getMargin(child, leading[mainAxis]);
    } else {
      // If the child is position absolute (without top/left) or relative,
      // we put it at the current accumulated offset.
      child->layout.position[pos[mainAxis]] += mainDim;
    }

    // Now that we placed the element, we need to update the variables
    // We only need to do that for relative elements. Absolute elements
    // do not take part in that phase.
    if (getPositionType(child) == CSS_POSITION_RELATIVE) {
      // The main dimension is the sum of all the elements dimension plus
      // the spacing.
      mainDim += betweenMainDim + getDimWithMargin(child, mainAxis);
      // The cross dimension is the max of the elements dimension since there
      // can only be one element in that cross dimension.
      crossDim = fmaxf(crossDim, getDimWithMargin(child, crossAxis));
    }
  }

  // If the user didn't specify a width or height, and it has not been set
  // by the container, then we set it via the children.
  if (isUndefined(node->layout.dimensions[dim[mainAxis]])) {
    node->layout.dimensions[dim[mainAxis]] = fmaxf(
      // We're missing the last padding at this point to get the final
      // dimension
      mainDim + getPaddingAndBorder(node, trailing[mainAxis]),
      // We can never assign a width smaller than the padding and borders
      getPaddingAndBorderAxis(node, mainAxis)
    );
  }

  if (isUndefined(node->layout.dimensions[dim[crossAxis]])) {
    node->layout.dimensions[dim[crossAxis]] = fmaxf(
      // For the cross dim, we add both sides at the end because the value
      // is aggregate via a max function. Intermediate negative values
      // can mess this computation otherwise
      crossDim + getPaddingAndBorderAxis(node, crossAxis),
      getPaddingAndBorderAxis(node, crossAxis)
    );
  }


  // <Loop D> Position elements in the cross axis

  for (int i = 0; i < node->children_count; ++i) {
    css_node_t* child = &node->children[i];

    if (getPositionType(child) == CSS_POSITION_ABSOLUTE &&
        isPosDefined(child, leading[crossAxis])) {
      // In case the child is absolutely positionned and has a
      // top/left/bottom/right being set, we override all the previously
      // computed positions to set it correctly.
      child->layout.position[pos[crossAxis]] = getPosition(child, leading[crossAxis]) +
        getBorder(node, leading[crossAxis]) +
        getMargin(child, leading[crossAxis]);

    } else {
      float leadingCrossDim = getPaddingAndBorder(node, leading[crossAxis]);

      // For a relative children, we're either using alignItems (parent) or
      // alignSelf (child) in order to determine the position in the cross axis
      if (getPositionType(child) == CSS_POSITION_RELATIVE) {
        css_align_t alignItem = getAlignItem(node, child);
        if (alignItem == CSS_ALIGN_FLEX_START) {
          // Do nothing
        } else if (alignItem == CSS_ALIGN_STRETCH) {
          // You can only stretch if the dimension has not already been set
          // previously.
          if (!isDimDefined(child, crossAxis)) {
            child->layout.dimensions[dim[crossAxis]] = fmaxf(
              node->layout.dimensions[dim[crossAxis]] -
                getPaddingAndBorderAxis(node, crossAxis) -
                getMarginAxis(child, crossAxis),
              // You never want to go smaller than padding
              getPaddingAndBorderAxis(child, crossAxis)
            );
          }
        } else {
          // The remaining space between the parent dimensions+padding and child
          // dimensions+margin.
          float remainingCrossDim = node->layout.dimensions[dim[crossAxis]] -
            getPaddingAndBorderAxis(node, crossAxis) -
            getDimWithMargin(child, crossAxis);

          if (alignItem == CSS_ALIGN_CENTER) {
            leadingCrossDim += remainingCrossDim / 2;
          } else { // CSS_ALIGN_FLEX_END
            leadingCrossDim += remainingCrossDim;
          }
        }
      }

      // And we apply the position
      child->layout.position[pos[crossAxis]] += leadingCrossDim;
    }
  }
}
