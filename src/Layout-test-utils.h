/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "Layout.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void test(const char *name, css_node_t *style, css_node_t *expected_layout);
int tests_finished(void);
css_dim_t measure(void *context, float width);
void init_css_node_children(css_node_t *node, int children_count);
css_node_t *new_test_css_node(void);
