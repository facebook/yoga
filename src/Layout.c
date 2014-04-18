#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define CSS_UNDEFINED NAN

typedef enum {
  CSS_FLEX_DIRECTION_COLUMN = 0,
  CSS_FLEX_DIRECTION_ROW
} css_flex_direction_t;

typedef enum {
  CSS_JUSTIFY_FLEX_START = 0,
  CSS_JUSTIFY_CENTER,
  CSS_JUSTIFY_FLEX_END,
  CSS_JUSTIFY_SPACE_BETWEEN,
  CSS_JUSTIFY_SPACE_AROUND
} css_justify_t;

// Note: auto is only a valid value for alignSelf. It is NOT a valid value for
// alignItems.
typedef enum {
  CSS_ALIGN_AUTO = 0,
  CSS_ALIGN_FLEX_START,
  CSS_ALIGN_CENTER,
  CSS_ALIGN_FLEX_END,
  CSS_ALIGN_STRETCH
} css_align_t;

typedef enum {
  CSS_FLEX_NONE = 0,
  CSS_FLEX_ONE
} css_flex_t;

// Note: left and top are shared between position[2] and position[4], so
// they have to be before right and bottom.
typedef enum {
  CSS_LEFT = 0,
  CSS_TOP,
  CSS_RIGHT,
  CSS_BOTTOM
} css_position_t;

typedef enum {
  CSS_WIDTH = 0,
  CSS_HEIGHT
} css_dimension_t;


typedef struct {
  float position[2];
  float dimensions[2];
} css_layout_t;

typedef struct {
  css_flex_direction_t flex_direction;
  css_justify_t justify_content;
  css_align_t align_items;
  css_align_t align_self;
  css_flex_t flex;
  float margin[4];
  float padding[4];
  float position[4];
  float dimensions[2];
  css_layout_t layout;
} css_style_t;

typedef struct css_node {
  css_style_t style;
  css_layout_t layout;
  struct css_node **children;
  int children_count;
} css_node_t;

css_node_t *new_css_node() {
  css_node_t *node = malloc(sizeof(css_node_t));
  memset(node, 0, sizeof(css_node_t));

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

  return node;
}

void new_css_node_children(css_node_t *node, int children_count) {
  node->children = malloc(children_count * sizeof(css_node_t *));
  for (int i = 0; i < children_count; ++i) {
    node->children[i] = new_css_node();
  }
  node->children_count = children_count;
}

void free_css_node(css_node_t *node) {
  for (int i = 0; i < node->children_count; ++i) {
    free_css_node(node->children[i]);
  }
  free(node);
}

void layout_node(css_node_t *node) {
  node->layout.dimensions[CSS_WIDTH] = node->style.dimensions[CSS_WIDTH];
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

  print_number_0("marginLeft", node->style.margin[CSS_LEFT]);
  print_number_0("marginRight", node->style.margin[CSS_RIGHT]);
  print_number_0("marginTop", node->style.margin[CSS_TOP]);
  print_number_0("marginBottom", node->style.margin[CSS_BOTTOM]);

  print_number_0("paddingLeft", node->style.padding[CSS_LEFT]);
  print_number_0("paddingRight", node->style.padding[CSS_RIGHT]);
  print_number_0("paddingTop", node->style.padding[CSS_TOP]);
  print_number_0("paddingBottom", node->style.padding[CSS_BOTTOM]);

  print_number_nan("width", node->style.dimensions[CSS_WIDTH]);
  print_number_nan("height", node->style.dimensions[CSS_HEIGHT]);

  print_number_nan("left", node->style.position[CSS_LEFT]);
  print_number_nan("right", node->style.position[CSS_RIGHT]);
  print_number_nan("top", node->style.position[CSS_TOP]);
  print_number_nan("bottom", node->style.position[CSS_BOTTOM]);

  if (node->children_count > 0) {
    printf("children: [\n");
    for (int i = 0; i < node->children_count; ++i) {
      print_style(node->children[i], level + 1);
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
      print_layout(node->children[i], level + 1);
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
  return node->style.padding[location];
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

float getDimWithMargin(css_node_t *node, css_flex_direction_t axis) {
  return node->layout.dimensions[dim[axis]] +
    getMargin(node, leading[axis]) +
    getMargin(node, trailing[axis]);
}

bool isDimDefined(css_node_t *node, css_flex_direction_t axis) {
  return !isUndefined(node->style.dimensions[dim[axis]]);
}

float getPosition(css_node_t *node, css_position_t pos) {
  float result = node->style.position[pos];
  if (!isUndefined(result)) {
    return result;
  }
  return 0;
}

// If both left and right are defined, then use left. Otherwise return
// +left or -right depending on which is defined.
float getRelativePosition(css_node_t *node, css_flex_direction_t axis) {
  float lead = node->style.position[leading[axis]];
  if (!isUndefined(lead)) {
    return lead;
  }
  return getPosition(node, trailing[axis]);
}

void layoutNode(css_node_t *node) {
  css_flex_direction_t mainAxis = getFlexDirection(node);
  css_flex_direction_t crossAxis = mainAxis == CSS_FLEX_DIRECTION_ROW ?
    CSS_FLEX_DIRECTION_COLUMN :
    CSS_FLEX_DIRECTION_ROW;

  bool mainDimInStyle = isDimDefined(node, mainAxis);
  if (isUndefined(node->layout.dimensions[dim[mainAxis]]) && mainDimInStyle) {
    node->layout.dimensions[dim[mainAxis]] = node->style.dimensions[dim[mainAxis]];
  }

  bool crossDimInStyle = isDimDefined(node, crossAxis);
  if (isUndefined(node->layout.dimensions[dim[crossAxis]]) && crossDimInStyle) {
    node->layout.dimensions[dim[crossAxis]] = node->style.dimensions[dim[crossAxis]];
  }

  float mainContentDim = 0;
  int flexibleChildrenCount = 0;
  for (int i = 0; i < node->children_count; ++i) {
    css_node_t* child = node->children[i];
    if (isUndefined(node->layout.dimensions[dim[mainAxis]]) || !getFlex(child)) {
      layoutNode(child);
      mainContentDim += getDimWithMargin(child, mainAxis);
    } else {
      flexibleChildrenCount++;
    }
  }

  float leadingMainDim = 0;
  float betweenMainDim = 0;
  if (!isUndefined(node->layout.dimensions[dim[mainAxis]])) {
    float remainingMainDim = node->layout.dimensions[dim[mainAxis]] -
      getPadding(node, leading[mainAxis]) -
      getPadding(node, trailing[mainAxis]) -
      mainContentDim;

    if (flexibleChildrenCount) {
      float flexibleMainDim = remainingMainDim / flexibleChildrenCount;
      for (int i = 0; i < node->children_count; ++i) {
        css_node_t* child = node->children[i];
        if (getFlex(child)) {
          child->layout.dimensions[dim[mainAxis]] = flexibleMainDim;
          layoutNode(child);
        }
      }
    } else {
      css_justify_t justifyContent = getJustifyContent(node);
      if (justifyContent == CSS_JUSTIFY_FLEX_START) {
        // Do nothing
      } else if (justifyContent == CSS_JUSTIFY_CENTER) {
        leadingMainDim = remainingMainDim / 2;
      } else if (justifyContent == CSS_JUSTIFY_FLEX_END) {
        leadingMainDim = remainingMainDim;
      } else if (justifyContent == CSS_JUSTIFY_SPACE_BETWEEN) {
        betweenMainDim = remainingMainDim / (node->children_count - 1);
      } else if (justifyContent == CSS_JUSTIFY_SPACE_AROUND) {
        betweenMainDim = remainingMainDim / node->children_count;
        leadingMainDim = betweenMainDim / 2;
      }
    }
  }

  float crossDim = 0;
  float mainPos = getPadding(node, leading[mainAxis]) + leadingMainDim;
  for (int i = 0; i < node->children_count; ++i) {
    css_node_t* child = node->children[i];
    child->layout.position[pos[mainAxis]] += mainPos;
    mainPos += getDimWithMargin(child, mainAxis) + betweenMainDim;

    if (!isUndefined(child->layout.dimensions[dim[crossAxis]])) {
      float childCrossDim = getDimWithMargin(child, crossAxis);
      if (childCrossDim > crossDim) {
        crossDim = childCrossDim;
      }
    }
  }
  mainPos += getPadding(node, trailing[mainAxis]);
  crossDim += getPadding(node, leading[crossAxis]) +
    getPadding(node, trailing[crossAxis]);

  if (isUndefined(node->layout.dimensions[dim[mainAxis]]) && !mainDimInStyle) {
    node->layout.dimensions[dim[mainAxis]] = mainPos > 0 ? mainPos : 0;
  }
  if (isUndefined(node->layout.dimensions[dim[crossAxis]])) {
    node->layout.dimensions[dim[crossAxis]] = crossDim > 0 ? crossDim : 0;
  }

  for (int i = 0; i < node->children_count; ++i) {
    css_node_t* child = node->children[i];
    css_align_t alignItem = getAlignItem(node, child);
    float remainingCrossDim = node->layout.dimensions[dim[crossAxis]] -
      getDimWithMargin(child, crossAxis) -
      getPadding(node, leading[crossAxis]) -
      getPadding(node, trailing[crossAxis]);

    float leadingCrossDim = getPadding(node, leading[crossAxis]);
    if (alignItem == CSS_ALIGN_FLEX_START) {
      // Do nothing
    } else if (alignItem == CSS_ALIGN_CENTER) {
      leadingCrossDim += remainingCrossDim / 2;
    } else if (alignItem == CSS_ALIGN_FLEX_END) {
      leadingCrossDim += remainingCrossDim;
    } else if (alignItem == CSS_ALIGN_STRETCH) {
      child->layout.dimensions[dim[crossAxis]] = node->layout.dimensions[dim[crossAxis]] -
        getPadding(node, leading[crossAxis]) -
        getPadding(node, trailing[crossAxis]) -
        getMargin(child, leading[crossAxis]) -
        getMargin(child, trailing[crossAxis]);
    }
    child->layout.position[pos[crossAxis]] += leadingCrossDim;
  }

  node->layout.position[leading[mainAxis]] += getMargin(node, leading[mainAxis]) +
    getRelativePosition(node, mainAxis);
  node->layout.position[leading[crossAxis]] += getMargin(node, leading[crossAxis]) +
    getRelativePosition(node, crossAxis);
}


int main()
{
  css_node_t *node = new_css_node();
  node->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
  node->style.dimensions[CSS_WIDTH] = 100;
  node->style.align_items = CSS_ALIGN_STRETCH;

  new_css_node_children(node, 3);
  node->children[0]->style.dimensions[CSS_HEIGHT] = 50;
  layoutNode(node);

  print_style(node, 0);
  print_layout(node, 0);

  free_css_node(node);
  printf("Hello World\n");
}

