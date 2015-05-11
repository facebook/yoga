/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "Layout-test-utils.h"
#include <stdlib.h>

  /** START_GENERATED **/
#define SMALL_WIDTH 34.671875
#define SMALL_HEIGHT 18
#define BIG_WIDTH 172.421875
#define BIG_HEIGHT 36
#define BIG_MIN_WIDTH 100.4375
#define SMALL_TEXT "small"
#define LONG_TEXT "loooooooooong with space"
  /** END_GENERATED **/

typedef struct failed_test_t {
  struct failed_test_t *next;
  const char *name;
  css_node_t *style;
  css_node_t *expected;
} failed_test_t;

static failed_test_t *failed_test_head = NULL;
static failed_test_t *failed_test_tail = NULL;
static void add_failed_test(const char *name, css_node_t *style, css_node_t *expected) {
  failed_test_t *failed_test = malloc(sizeof(failed_test_t));
  failed_test->name = name;
  failed_test->style = style;
  failed_test->expected = expected;

  if (!failed_test_head) {
    failed_test_head = failed_test;
    failed_test_tail = failed_test;
  } else {
    failed_test_tail->next = failed_test;
    failed_test_tail = failed_test;
  }
}

static bool eq(float a, float b) {
  return fabs(a - b) < 0.0001;
}

static bool are_layout_equal(css_node_t *a, css_node_t *b) {
  if (!eq(a->layout.dimensions[CSS_WIDTH], b->layout.dimensions[CSS_WIDTH]) ||
      !eq(a->layout.dimensions[CSS_HEIGHT], b->layout.dimensions[CSS_HEIGHT]) ||
      !eq(a->layout.position[CSS_TOP], b->layout.position[CSS_TOP]) ||
      !eq(a->layout.position[CSS_LEFT], b->layout.position[CSS_LEFT]) ||
      !eq(a->children_count, b->children_count)) {
    return false;
  }
  for (int i = 0; i < a->children_count; ++i) {
    if (!are_layout_equal(a->get_child(a->context, i), b->get_child(b->context, i))) {
      return false;
    }
  }
  return true;
}

css_dim_t measure(void *context, float width) {
  const char *text = context;
  css_dim_t dim;
  if (width != width) {
    width = 1000000;
  }
  if (strcmp(text, SMALL_TEXT) == 0) {
    dim.dimensions[CSS_WIDTH] = fminf(SMALL_WIDTH, width);
    dim.dimensions[CSS_HEIGHT] = SMALL_HEIGHT;
    return dim;
  }
  if (strcmp(text, LONG_TEXT) == 0) {
    dim.dimensions[CSS_WIDTH] = width >= BIG_WIDTH ? BIG_WIDTH : fmaxf(BIG_MIN_WIDTH, width);
    dim.dimensions[CSS_HEIGHT] = width >= BIG_WIDTH ? SMALL_HEIGHT : BIG_HEIGHT;
    return dim;
  }

  // Should not go here
  dim.dimensions[CSS_WIDTH] = CSS_UNDEFINED;
  dim.dimensions[CSS_HEIGHT] = CSS_UNDEFINED;
  return dim;
}

void test(const char *name, css_node_t *style, css_node_t *expected_layout) {
  layoutNode(style, CSS_UNDEFINED, -1);

  if (!are_layout_equal(style, expected_layout)) {
    printf("%sF%s", "\x1B[31m", "\x1B[0m");
    add_failed_test(name, style, expected_layout);
  } else {
    printf("%s.%s", "\x1B[32m", "\x1B[0m");
    free_css_node(style);
    free_css_node(expected_layout);
  }
}

int tests_finished() {
  failed_test_t *failed_test = failed_test_head;
  printf("\n");

  int tests_failed = 0;
  while (failed_test) {
    printf("%sFAIL%s %s\n", "\x1B[31m", "\x1B[0m", failed_test->name);

    printf("Input:    ");
    print_css_node(failed_test->style, CSS_PRINT_STYLE | CSS_PRINT_CHILDREN);
    printf("Output:   ");
    print_css_node(failed_test->style, CSS_PRINT_LAYOUT | CSS_PRINT_CHILDREN);

    printf("Expected: ");
    print_css_node(failed_test->expected, CSS_PRINT_LAYOUT | CSS_PRINT_CHILDREN);

    free_css_node(failed_test->style);
    free_css_node(failed_test->expected);

    failed_test_t *next_failed_test = failed_test->next;
    free(failed_test);
    failed_test = next_failed_test;

    tests_failed++;
  }
  printf("\n\n");

  if (tests_failed > 0) {
    printf("TESTS FAILED: %d\n", tests_failed);
    return 1;
  } else {
    printf("ALL TESTS PASSED\n");
    return 0;
  }
}

static css_node_t* get_child(void *context, int i) {
  css_node_t* children = (css_node_t*)context;
  return &children[i];
}

static bool is_dirty(void *context) {
  (void)context; // remove unused warning
  return true;
}

static void init_test_css_node(css_node_t *node) {
  node->get_child = get_child;
  node->is_dirty = is_dirty;
}

css_node_t *new_test_css_node(void) {
  css_node_t *node = new_css_node();
  init_test_css_node(node);
  return node;
}

void init_css_node_children(css_node_t *node, int children_count) {
  node->context = calloc((size_t)children_count, sizeof(css_node_t));
  for (int i = 0; i < children_count; ++i) {
    init_css_node(node->get_child(node->context, i));
    init_test_css_node(node->get_child(node->context, i));
  }
  node->children_count = children_count;
}
