
#include "Layout.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void test(const char *name, css_node_t *style, css_node_t *expected_layout);
css_dim_t measure(void *context, float width);
void init_css_node_children(css_node_t *node, int children_count);
css_node_t *new_test_css_node(void);
