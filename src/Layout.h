#ifndef __LAYOUT_H
#define __LAYOUT_H


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

typedef enum {
  CSS_POSITION_RELATIVE = 0,
  CSS_POSITION_ABSOLUTE
} css_position_type_t;

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
  css_position_type_t position_type;
  float margin[4];
  float position[4];
  /**
   * You should skip all the rules that contain negative values for the
   * following attributes. For example:
   *   {padding: 10, paddingLeft: -5}
   * should output:
   *   {left: 10 ...}
   * the following two are incorrect:
   *   {left: -5 ...}
   *   {left: 0 ...}
   */
  float padding[4];
  float border[4];
  float dimensions[2];
} css_style_t;

typedef struct css_node {
  css_style_t style;
  css_layout_t layout;
  struct css_node *children;
  int children_count;
} css_node_t;


// Lifecycle of nodes and children
css_node_t *new_css_node();
void init_css_node_children(css_node_t *node, int children_count);
void free_css_node(css_node_t *node);

// Print utilities
void print_style(css_node_t *node, int level);
void print_layout(css_node_t *node, int level);

// Function that computes the layout!
void layoutNode(css_node_t *node);

#endif
