
#include "Layout-test-utils.h"

bool are_layout_equal(css_node_t *a, css_node_t *b) {
  if (a->layout.dimensions[CSS_WIDTH] != b->layout.dimensions[CSS_WIDTH] ||
      a->layout.dimensions[CSS_HEIGHT] != b->layout.dimensions[CSS_HEIGHT] ||
      a->layout.position[CSS_TOP] != b->layout.position[CSS_TOP] ||
      a->layout.position[CSS_LEFT] != b->layout.position[CSS_LEFT] ||
      a->children_count != b->children_count) {
    return false;
  }
  for (int i = 0; i < a->children_count; ++i) {
    if (!are_layout_equal(&a->children[i], &b->children[i])) {
      return false;
    }
  }
  return true;
}

css_dim_t measure(void *context, css_measure_type_t type, float width) {
  const char *text = context;
  css_dim_t dim;
  if (strcmp(text, "small") == 0) {
    if (type == CSS_MEASURE_GROW || type == CSS_MEASURE_SHRINK) {
      dim.dimensions[CSS_WIDTH] = 33;
      dim.dimensions[CSS_HEIGHT] = 18;
      return dim;
    }
    dim.dimensions[CSS_WIDTH] = width;
    dim.dimensions[CSS_HEIGHT] = 18;
    return dim;
  }
  if (strcmp(text, "loooooooooong with space") == 0) {
    if (type == CSS_MEASURE_GROW) {
      dim.dimensions[CSS_WIDTH] = 171;
      dim.dimensions[CSS_HEIGHT] = 18;
      return dim;
    }
    if (type == CSS_MEASURE_SHRINK) {
      dim.dimensions[CSS_WIDTH] = 100;
      dim.dimensions[CSS_HEIGHT] = 36;
      return dim;
    }
    dim.dimensions[CSS_WIDTH] = width;
    dim.dimensions[CSS_HEIGHT] = width >= 171 ? 18 : 36;
    return dim;
  }

  // Should not go here
  dim.dimensions[CSS_WIDTH] = CSS_UNDEFINED;
  dim.dimensions[CSS_HEIGHT] = CSS_UNDEFINED;
  return dim;
}

void test(const char *name, css_node_t *style, css_node_t *expected_layout) {
  layoutNode(style);

  if (!are_layout_equal(style, expected_layout)) {
    printf("%sFAIL%s %s\n", "\x1B[31m", "\x1B[0m", name);

    printf("Input:    ");
    print_style(style, 0);
    printf("Output:   ");
    print_layout(style, 0);

    printf("Expected: ");
    print_layout(expected_layout, 0);
  } else {
    printf("%sPASS%s %s\n", "\x1B[32m", "\x1B[0m",  name);
  }

  free_css_node(style);
  free_css_node(expected_layout);
}
