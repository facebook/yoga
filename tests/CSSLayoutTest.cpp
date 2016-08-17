/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <CSSLayout/CSSLayout-internal.h>
#include <CSSLayoutTestUtils/CSSLayoutTestUtils.h>

#include <gtest/gtest.h>

TEST(CSSLayoutTest, test_layout_single_node_constant_width_height) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_children) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 500;
      node_1->style.dimensions[CSSDimensionHeight] = 500;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 250;
      node_1->style.dimensions[CSSDimensionHeight] = 250;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 125;
      node_1->style.dimensions[CSSDimensionHeight] = 125;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 500;
      node_1->layout.dimensions[CSSDimensionHeight] = 500;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 500;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 250;
      node_1->layout.dimensions[CSSDimensionHeight] = 250;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 750;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 125;
      node_1->layout.dimensions[CSSDimensionHeight] = 125;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_children_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 500;
      node_1->style.dimensions[CSSDimensionHeight] = 500;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 250;
      node_1->style.dimensions[CSSDimensionHeight] = 250;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 125;
      node_1->style.dimensions[CSSDimensionHeight] = 125;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 500;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 500;
      node_1->layout.dimensions[CSSDimensionHeight] = 500;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 250;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 250;
      node_1->layout.dimensions[CSSDimensionHeight] = 250;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 125;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 125;
      node_1->layout.dimensions[CSSDimensionHeight] = 125;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_nested_children) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 500;
      node_1->style.dimensions[CSSDimensionHeight] = 500;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 500;
      node_1->style.dimensions[CSSDimensionHeight] = 500;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 250;
        node_2->style.dimensions[CSSDimensionHeight] = 250;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->style.dimensions[CSSDimensionWidth] = 250;
        node_2->style.dimensions[CSSDimensionHeight] = 250;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 500;
      node_1->layout.dimensions[CSSDimensionHeight] = 500;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 500;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 500;
      node_1->layout.dimensions[CSSDimensionHeight] = 500;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 250;
        node_2->layout.dimensions[CSSDimensionHeight] = 250;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->layout.position[CSSEdgeTop] = 250;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 250;
        node_2->layout.dimensions[CSSDimensionHeight] = 250;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_nested_children_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 500;
      node_1->style.dimensions[CSSDimensionHeight] = 500;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.flexDirection = CSSFlexDirectionColumnReverse;
      node_1->style.dimensions[CSSDimensionWidth] = 500;
      node_1->style.dimensions[CSSDimensionHeight] = 500;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 250;
        node_2->style.dimensions[CSSDimensionHeight] = 250;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->style.dimensions[CSSDimensionWidth] = 250;
        node_2->style.dimensions[CSSDimensionHeight] = 250;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 500;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 500;
      node_1->layout.dimensions[CSSDimensionHeight] = 500;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 500;
      node_1->layout.dimensions[CSSDimensionHeight] = 500;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 250;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 250;
        node_2->layout.dimensions[CSSDimensionHeight] = 250;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 250;
        node_2->layout.dimensions[CSSDimensionHeight] = 250;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    node_0->style.margin[CSSEdgeLeft] = 10;
    node_0->style.margin[CSSEdgeTop] = 10;
    node_0->style.margin[CSSEdgeRight] = 10;
    node_0->style.margin[CSSEdgeBottom] = 10;
    node_0->style.margin[CSSEdgeStart] = 10;
    node_0->style.margin[CSSEdgeEnd] = 10;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 10;
    node_0->layout.position[CSSEdgeLeft] = 10;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_several_children) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    node_0->style.margin[CSSEdgeLeft] = 10;
    node_0->style.margin[CSSEdgeTop] = 10;
    node_0->style.margin[CSSEdgeRight] = 10;
    node_0->style.margin[CSSEdgeBottom] = 10;
    node_0->style.margin[CSSEdgeStart] = 10;
    node_0->style.margin[CSSEdgeEnd] = 10;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.margin[CSSEdgeLeft] = 50;
      node_1->style.margin[CSSEdgeTop] = 50;
      node_1->style.margin[CSSEdgeRight] = 50;
      node_1->style.margin[CSSEdgeBottom] = 50;
      node_1->style.margin[CSSEdgeStart] = 50;
      node_1->style.margin[CSSEdgeEnd] = 50;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.margin[CSSEdgeLeft] = 25;
      node_1->style.margin[CSSEdgeTop] = 25;
      node_1->style.margin[CSSEdgeRight] = 25;
      node_1->style.margin[CSSEdgeBottom] = 25;
      node_1->style.margin[CSSEdgeStart] = 25;
      node_1->style.margin[CSSEdgeEnd] = 25;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 10;
    node_0->layout.position[CSSEdgeLeft] = 10;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 50;
      node_1->layout.position[CSSEdgeLeft] = 50;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 225;
      node_1->layout.position[CSSEdgeLeft] = 25;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 360;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_several_children_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    node_0->style.margin[CSSEdgeLeft] = 10;
    node_0->style.margin[CSSEdgeTop] = 10;
    node_0->style.margin[CSSEdgeRight] = 10;
    node_0->style.margin[CSSEdgeBottom] = 10;
    node_0->style.margin[CSSEdgeStart] = 10;
    node_0->style.margin[CSSEdgeEnd] = 10;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.margin[CSSEdgeLeft] = 50;
      node_1->style.margin[CSSEdgeTop] = 50;
      node_1->style.margin[CSSEdgeRight] = 50;
      node_1->style.margin[CSSEdgeBottom] = 50;
      node_1->style.margin[CSSEdgeStart] = 50;
      node_1->style.margin[CSSEdgeEnd] = 50;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.margin[CSSEdgeLeft] = 25;
      node_1->style.margin[CSSEdgeTop] = 25;
      node_1->style.margin[CSSEdgeRight] = 25;
      node_1->style.margin[CSSEdgeBottom] = 25;
      node_1->style.margin[CSSEdgeStart] = 25;
      node_1->style.margin[CSSEdgeEnd] = 25;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 10;
    node_0->layout.position[CSSEdgeLeft] = 10;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 850;
      node_1->layout.position[CSSEdgeLeft] = 50;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 675;
      node_1->layout.position[CSSEdgeLeft] = 25;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 540;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_rtl_with_revers) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRowReverse;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 300;
      node_1->style.dimensions[CSSDimensionHeight] = 150;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 100;
      node_1->layout.dimensions[CSSDimensionWidth] = 300;
      node_1->layout.dimensions[CSSDimensionHeight] = 150;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_flexDirection_row) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 300;
      node_1->style.dimensions[CSSDimensionHeight] = 150;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 100;
      node_1->layout.dimensions[CSSDimensionWidth] = 300;
      node_1->layout.dimensions[CSSDimensionHeight] = 150;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_flexDirection_row_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 300;
      node_1->style.dimensions[CSSDimensionHeight] = 150;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 900;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 600;
      node_1->layout.dimensions[CSSDimensionWidth] = 300;
      node_1->layout.dimensions[CSSDimensionHeight] = 150;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_based_on_children_main_dimensions) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 300;
      node_1->style.dimensions[CSSDimensionHeight] = 150;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 350;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 200;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 300;
      node_1->layout.dimensions[CSSDimensionHeight] = 150;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_based_on_children_main_dimensions_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 300;
      node_1->style.dimensions[CSSDimensionHeight] = 150;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 350;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 150;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 300;
      node_1->layout.dimensions[CSSDimensionHeight] = 150;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_flex) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 200;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 800;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_flex_in_revese) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 800;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 800;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_flex_recursively) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 1000;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        CSSNodeStyleSetFlex(node_2, 1);
        node_2->style.dimensions[CSSDimensionWidth] = 1000;
        init_css_node_children(node_2, 1);
        {
          CSSNode *node_3;
          node_3 = CSSNodeGetChild(node_2, 0);
          CSSNodeStyleSetFlex(node_3, 1);
          node_3->style.dimensions[CSSDimensionWidth] = 1000;
        }
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 1000;
      node_1->layout.dimensions[CSSDimensionHeight] = 1000;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 1000;
        node_2->layout.dimensions[CSSDimensionHeight] = 1000;
        init_css_node_children(node_2, 1);
        {
          CSSNode *node_3;
          node_3 = CSSNodeGetChild(node_2, 0);
          node_3->layout.position[CSSEdgeTop] = 0;
          node_3->layout.position[CSSEdgeLeft] = 0;
          node_3->layout.dimensions[CSSDimensionWidth] = 1000;
          node_3->layout.dimensions[CSSDimensionHeight] = 1000;
        }
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_flex_recursively_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.flexDirection = CSSFlexDirectionColumnReverse;
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 1000;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.flexDirection = CSSFlexDirectionColumnReverse;
        CSSNodeStyleSetFlex(node_2, 1);
        node_2->style.dimensions[CSSDimensionWidth] = 1000;
        init_css_node_children(node_2, 1);
        {
          CSSNode *node_3;
          node_3 = CSSNodeGetChild(node_2, 0);
          node_3->style.flexDirection = CSSFlexDirectionColumnReverse;
          CSSNodeStyleSetFlex(node_3, 1);
          node_3->style.dimensions[CSSDimensionWidth] = 1000;
        }
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 1000;
      node_1->layout.dimensions[CSSDimensionHeight] = 1000;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 1000;
        node_2->layout.dimensions[CSSDimensionHeight] = 1000;
        init_css_node_children(node_2, 1);
        {
          CSSNode *node_3;
          node_3 = CSSNodeGetChild(node_2, 0);
          node_3->layout.position[CSSEdgeTop] = 0;
          node_3->layout.position[CSSEdgeLeft] = 0;
          node_3->layout.dimensions[CSSDimensionWidth] = 1000;
          node_3->layout.dimensions[CSSDimensionHeight] = 1000;
        }
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_targeted_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    node_0->style.margin[CSSEdgeLeft] = 5;
    node_0->style.margin[CSSEdgeTop] = 10;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.margin[CSSEdgeLeft] = 15;
      node_1->style.margin[CSSEdgeTop] = 50;
      node_1->style.margin[CSSEdgeBottom] = 20;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.margin[CSSEdgeLeft] = 30;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 10;
    node_0->layout.position[CSSEdgeLeft] = 5;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 50;
      node_1->layout.position[CSSEdgeLeft] = 15;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 170;
      node_1->layout.position[CSSEdgeLeft] = 30;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_targeted_margin_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    node_0->style.margin[CSSEdgeLeft] = 5;
    node_0->style.margin[CSSEdgeTop] = 10;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.margin[CSSEdgeLeft] = 15;
      node_1->style.margin[CSSEdgeTop] = 50;
      node_1->style.margin[CSSEdgeBottom] = 20;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.margin[CSSEdgeLeft] = 30;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 10;
    node_0->layout.position[CSSEdgeLeft] = 5;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 880;
      node_1->layout.position[CSSEdgeLeft] = 15;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 730;
      node_1->layout.position[CSSEdgeLeft] = 30;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_justifyContent_flex_start) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifyFlexStart;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_justifyContent_flex_start_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.justifyContent = CSSJustifyFlexStart;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 900;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 800;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_justifyContent_flex_end) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifyFlexEnd;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 800;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 900;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_justifyContent_flex_end_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.justifyContent = CSSJustifyFlexEnd;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_justifyContent_space_between) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifySpaceBetween;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 900;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_justifyContent_space_between_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.justifyContent = CSSJustifySpaceBetween;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 900;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_justifyContent_space_around) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifySpaceAround;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 200;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 700;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_justifyContent_space_around_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.justifyContent = CSSJustifySpaceAround;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 700;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 200;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_justifyContent_center) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifyCenter;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 400;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 500;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_justifyContent_center_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.justifyContent = CSSJustifyCenter;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 500;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 400;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_flex_with_override_height) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 1000;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_alignItems_flex_start) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.alignItems = CSSAlignFlexStart;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_alignItems_flex_start_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.alignItems = CSSAlignFlexStart;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 900;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 800;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_alignItems_center) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.alignItems = CSSAlignCenter;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 400;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 450;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_alignItems_center_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.alignItems = CSSAlignCenter;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 900;
      node_1->layout.position[CSSEdgeLeft] = 400;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 800;
      node_1->layout.position[CSSEdgeLeft] = 450;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_alignItems_flex_end) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.alignItems = CSSAlignFlexEnd;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 800;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 900;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_alignItems_flex_end_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.alignItems = CSSAlignFlexEnd;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 900;
      node_1->layout.position[CSSEdgeLeft] = 800;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 800;
      node_1->layout.position[CSSEdgeLeft] = 900;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_alignSelf_overrides_alignItems) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.alignItems = CSSAlignFlexEnd;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.alignSelf = CSSAlignCenter;
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 800;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 450;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_alignSelf_overrides_alignItems_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.alignItems = CSSAlignFlexEnd;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.alignSelf = CSSAlignCenter;
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 900;
      node_1->layout.position[CSSEdgeLeft] = 800;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 800;
      node_1->layout.position[CSSEdgeLeft] = 450;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_alignItems_stretch) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.alignItems = CSSAlignStretch;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 1000;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_alignItems_stretch_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.alignItems = CSSAlignStretch;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 900;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 1000;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_empty_node) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_empty_node_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    init_css_node_children(node_0, 1);
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_child_with_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.margin[CSSEdgeLeft] = 5;
      node_1->style.margin[CSSEdgeTop] = 5;
      node_1->style.margin[CSSEdgeRight] = 5;
      node_1->style.margin[CSSEdgeBottom] = 5;
      node_1->style.margin[CSSEdgeStart] = 5;
      node_1->style.margin[CSSEdgeEnd] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 10;
    node_0->layout.dimensions[CSSDimensionHeight] = 10;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 5;
      node_1->layout.position[CSSEdgeLeft] = 5;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_child_with_margin_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.margin[CSSEdgeLeft] = 5;
      node_1->style.margin[CSSEdgeTop] = 5;
      node_1->style.margin[CSSEdgeRight] = 5;
      node_1->style.margin[CSSEdgeBottom] = 5;
      node_1->style.margin[CSSEdgeStart] = 5;
      node_1->style.margin[CSSEdgeEnd] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 10;
    node_0->layout.dimensions[CSSDimensionHeight] = 10;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 5;
      node_1->layout.position[CSSEdgeLeft] = 5;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_not_shrink_children_if_not_enough_space) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionHeight] = 200;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_not_shrink_children_if_not_enough_space_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionHeight] = 200;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = -200;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_for_center) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifyCenter;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_flex_end_with_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifyFlexEnd;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.margin[CSSEdgeTop] = 10;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_flex_end_with_margin_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.justifyContent = CSSJustifyFlexEnd;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.margin[CSSEdgeTop] = 10;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 10;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_alignItems_with_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignItems = CSSAlignFlexEnd;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.margin[CSSEdgeLeft] = 10;
        node_2->style.margin[CSSEdgeTop] = 10;
        node_2->style.margin[CSSEdgeRight] = 10;
        node_2->style.margin[CSSEdgeBottom] = 10;
        node_2->style.margin[CSSEdgeStart] = 10;
        node_2->style.margin[CSSEdgeEnd] = 10;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->style.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 20;
    node_0->layout.dimensions[CSSDimensionHeight] = 120;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 20;
      node_1->layout.dimensions[CSSDimensionHeight] = 120;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 10;
        node_2->layout.position[CSSEdgeLeft] = 10;
        node_2->layout.dimensions[CSSDimensionWidth] = 0;
        node_2->layout.dimensions[CSSDimensionHeight] = 0;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->layout.position[CSSEdgeTop] = 20;
        node_2->layout.position[CSSEdgeLeft] = 20;
        node_2->layout.dimensions[CSSDimensionWidth] = 0;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_alignItems_with_margin_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.flexDirection = CSSFlexDirectionColumnReverse;
      node_1->style.alignItems = CSSAlignFlexEnd;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.margin[CSSEdgeLeft] = 10;
        node_2->style.margin[CSSEdgeTop] = 10;
        node_2->style.margin[CSSEdgeRight] = 10;
        node_2->style.margin[CSSEdgeBottom] = 10;
        node_2->style.margin[CSSEdgeStart] = 10;
        node_2->style.margin[CSSEdgeEnd] = 10;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->style.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 20;
    node_0->layout.dimensions[CSSDimensionHeight] = 120;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 20;
      node_1->layout.dimensions[CSSDimensionHeight] = 120;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 110;
        node_2->layout.position[CSSEdgeLeft] = 10;
        node_2->layout.dimensions[CSSDimensionWidth] = 0;
        node_2->layout.dimensions[CSSDimensionHeight] = 0;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 20;
        node_2->layout.dimensions[CSSDimensionWidth] = 0;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_flex_inside_empty_node) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_alignItems_stretch_with_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.alignItems = CSSAlignStretch;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.margin[CSSEdgeLeft] = 10;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 10;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_alignItems_stretch_with_margin_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.alignItems = CSSAlignStretch;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.margin[CSSEdgeLeft] = 10;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 10;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_padding) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.padding[CSSEdgeLeft] = 5;
    node_0->style.padding[CSSEdgeTop] = 5;
    node_0->style.padding[CSSEdgeRight] = 5;
    node_0->style.padding[CSSEdgeBottom] = 5;
    node_0->style.padding[CSSEdgeStart] = 5;
    node_0->style.padding[CSSEdgeEnd] = 5;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 10;
    node_0->layout.dimensions[CSSDimensionHeight] = 10;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_padding_and_child) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.padding[CSSEdgeLeft] = 5;
    node_0->style.padding[CSSEdgeTop] = 5;
    node_0->style.padding[CSSEdgeRight] = 5;
    node_0->style.padding[CSSEdgeBottom] = 5;
    node_0->style.padding[CSSEdgeStart] = 5;
    node_0->style.padding[CSSEdgeEnd] = 5;
    init_css_node_children(node_0, 1);
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 10;
    node_0->layout.dimensions[CSSDimensionHeight] = 10;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 5;
      node_1->layout.position[CSSEdgeLeft] = 5;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_padding_and_child_with_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.padding[CSSEdgeLeft] = 5;
    node_0->style.padding[CSSEdgeTop] = 5;
    node_0->style.padding[CSSEdgeRight] = 5;
    node_0->style.padding[CSSEdgeBottom] = 5;
    node_0->style.padding[CSSEdgeStart] = 5;
    node_0->style.padding[CSSEdgeEnd] = 5;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.margin[CSSEdgeLeft] = 5;
      node_1->style.margin[CSSEdgeTop] = 5;
      node_1->style.margin[CSSEdgeRight] = 5;
      node_1->style.margin[CSSEdgeBottom] = 5;
      node_1->style.margin[CSSEdgeStart] = 5;
      node_1->style.margin[CSSEdgeEnd] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 20;
    node_0->layout.dimensions[CSSDimensionHeight] = 20;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 10;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_padding_and_stretch) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignSelf = CSSAlignStretch;
      node_1->style.padding[CSSEdgeLeft] = 10;
      node_1->style.padding[CSSEdgeTop] = 10;
      node_1->style.padding[CSSEdgeRight] = 10;
      node_1->style.padding[CSSEdgeBottom] = 10;
      node_1->style.padding[CSSEdgeStart] = 10;
      node_1->style.padding[CSSEdgeEnd] = 10;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 20;
    node_0->layout.dimensions[CSSDimensionHeight] = 20;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 20;
      node_1->layout.dimensions[CSSDimensionHeight] = 20;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_inner_outer_padding_and_stretch) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.padding[CSSEdgeLeft] = 50;
    node_0->style.padding[CSSEdgeTop] = 50;
    node_0->style.padding[CSSEdgeRight] = 50;
    node_0->style.padding[CSSEdgeBottom] = 50;
    node_0->style.padding[CSSEdgeStart] = 50;
    node_0->style.padding[CSSEdgeEnd] = 50;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignSelf = CSSAlignStretch;
      node_1->style.padding[CSSEdgeLeft] = 10;
      node_1->style.padding[CSSEdgeTop] = 10;
      node_1->style.padding[CSSEdgeRight] = 10;
      node_1->style.padding[CSSEdgeBottom] = 10;
      node_1->style.padding[CSSEdgeStart] = 10;
      node_1->style.padding[CSSEdgeEnd] = 10;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 120;
    node_0->layout.dimensions[CSSDimensionHeight] = 120;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 50;
      node_1->layout.position[CSSEdgeLeft] = 50;
      node_1->layout.dimensions[CSSDimensionWidth] = 20;
      node_1->layout.dimensions[CSSDimensionHeight] = 20;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_pstretch_and_child_with_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignSelf = CSSAlignStretch;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.margin[CSSEdgeLeft] = 16;
        node_2->style.margin[CSSEdgeTop] = 16;
        node_2->style.margin[CSSEdgeRight] = 16;
        node_2->style.margin[CSSEdgeBottom] = 16;
        node_2->style.margin[CSSEdgeStart] = 16;
        node_2->style.margin[CSSEdgeEnd] = 16;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 32;
    node_0->layout.dimensions[CSSDimensionHeight] = 32;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 32;
      node_1->layout.dimensions[CSSDimensionHeight] = 32;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 16;
        node_2->layout.position[CSSEdgeLeft] = 16;
        node_2->layout.dimensions[CSSDimensionWidth] = 0;
        node_2->layout.dimensions[CSSDimensionHeight] = 0;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_top_and_left) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.position[CSSEdgeLeft] = 5;
    node_0->style.position[CSSEdgeTop] = 5;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 5;
    node_0->layout.position[CSSEdgeLeft] = 5;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_height_padding_space_around) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifySpaceAround;
    node_0->style.dimensions[CSSDimensionHeight] = 10;
    node_0->style.padding[CSSEdgeTop] = 5;
    init_css_node_children(node_0, 1);
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 10;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 7.5;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_bottom) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.position[CSSEdgeBottom] = 5;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = -5;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_top_and_bottom) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.position[CSSEdgeTop] = 10;
    node_0->style.position[CSSEdgeBottom] = 5;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 10;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_absolute_position) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 500;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 500;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 250;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 250;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 250;
      node_1->layout.dimensions[CSSDimensionWidth] = 250;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_absolute_position_and_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.margin[CSSEdgeRight] = 15;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_absolute_position_and_padding_and_alignSelf_center) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignSelf = CSSAlignCenter;
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.padding[CSSEdgeRight] = 12;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 12;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_work_with_height_smaller_than_padding_bottom) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionHeight] = 5;
    node_0->style.padding[CSSEdgeBottom] = 20;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 20;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_work_with_width_smaller_than_padding_left) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 5;
    node_0->style.padding[CSSEdgeLeft] = 20;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 20;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_width_and_stretch) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 400;
      }
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.alignSelf = CSSAlignStretch;
      node_1->style.dimensions[CSSDimensionWidth] = 200;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 400;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 400;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 400;
        node_2->layout.dimensions[CSSDimensionHeight] = 0;
      }
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_padding_and_absolute_child) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.padding[CSSEdgeLeft] = 5;
    node_0->style.padding[CSSEdgeTop] = 5;
    node_0->style.padding[CSSEdgeRight] = 5;
    node_0->style.padding[CSSEdgeBottom] = 5;
    node_0->style.padding[CSSEdgeStart] = 5;
    node_0->style.padding[CSSEdgeEnd] = 5;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 10;
    node_0->layout.dimensions[CSSDimensionHeight] = 10;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 5;
      node_1->layout.position[CSSEdgeLeft] = 5;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_absolute_node_with_top_and_left) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.position[CSSEdgeLeft] = 10;
      node_1->style.position[CSSEdgeTop] = 10;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 10;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_padding_and_absolute_child_position_left) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.padding[CSSEdgeLeft] = 20;
    node_0->style.padding[CSSEdgeTop] = 20;
    node_0->style.padding[CSSEdgeRight] = 20;
    node_0->style.padding[CSSEdgeBottom] = 20;
    node_0->style.padding[CSSEdgeStart] = 20;
    node_0->style.padding[CSSEdgeEnd] = 20;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.position[CSSEdgeLeft] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 40;
    node_0->layout.dimensions[CSSDimensionHeight] = 40;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 20;
      node_1->layout.position[CSSEdgeLeft] = 5;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_absolute_node_with_top_and_margin_top) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.margin[CSSEdgeTop] = 5;
      node_1->style.position[CSSEdgeTop] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 10;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_absolute_node_with_left_and_margin_left) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.margin[CSSEdgeLeft] = 5;
      node_1->style.position[CSSEdgeLeft] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_space_around_and_absolute_child) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifySpaceAround;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1 = CSSNodeGetChild(node_0, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_space_around_and_absolute_child_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.justifyContent = CSSJustifySpaceAround;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1 = CSSNodeGetChild(node_0, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_flex_and_main_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 700;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.margin[CSSEdgeLeft] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 700;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 5;
      node_1->layout.dimensions[CSSDimensionWidth] = 695;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_flex_and_main_margin_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 700;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.margin[CSSEdgeRight] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 700;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 695;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_multiple_flex_and_padding) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 700;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.padding[CSSEdgeRight] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 700;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 347.5;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 347.5;
      node_1->layout.dimensions[CSSDimensionWidth] = 352.5;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_multiple_flex_and_padding_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 700;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.padding[CSSEdgeLeft] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 700;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 352.5;
      node_1->layout.dimensions[CSSDimensionWidth] = 347.5;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 352.5;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_multiple_flex_and_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 700;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.margin[CSSEdgeLeft] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 700;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 347.5;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 352.5;
      node_1->layout.dimensions[CSSDimensionWidth] = 347.5;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_multiple_flex_and_margin_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 700;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.margin[CSSEdgeRight] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 700;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 352.5;
      node_1->layout.dimensions[CSSDimensionWidth] = 347.5;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 347.5;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_flex_and_overflow) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionHeight] = 300;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 600;
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 300;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 600;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 600;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_absolute_node_with_flex) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 600;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      CSSNodeStyleSetFlex(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 600;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_absolute_node_with_flex_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 600;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      CSSNodeStyleSetFlex(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 600;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 600;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_absolute_node_with_double_flex) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionHeight] = 500;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      CSSNodeStyleSetFlex(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 500;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 500;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 500;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_border_width) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.border[CSSEdgeLeft] = 5;
    node_0->style.border[CSSEdgeTop] = 5;
    node_0->style.border[CSSEdgeRight] = 5;
    node_0->style.border[CSSEdgeBottom] = 5;
    node_0->style.border[CSSEdgeStart] = 5;
    node_0->style.border[CSSEdgeEnd] = 5;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 10;
    node_0->layout.dimensions[CSSDimensionHeight] = 10;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_absolute_node_with_border_width_position_top) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.border[CSSEdgeTop] = 1;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.position[CSSEdgeTop] = -1;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 1;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_absolute_node_with_border_width_position_top_cross_axis) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.border[CSSEdgeLeft] = 1;
    node_0->style.border[CSSEdgeTop] = 1;
    node_0->style.border[CSSEdgeRight] = 1;
    node_0->style.border[CSSEdgeBottom] = 1;
    node_0->style.border[CSSEdgeStart] = 1;
    node_0->style.border[CSSEdgeEnd] = 1;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.position[CSSEdgeLeft] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 2;
    node_0->layout.dimensions[CSSDimensionHeight] = 2;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 1;
      node_1->layout.position[CSSEdgeLeft] = 6;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_min_padding_align_stretch) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 50;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignSelf = CSSAlignStretch;
      node_1->style.margin[CSSEdgeLeft] = 20;
      node_1->style.padding[CSSEdgeLeft] = 20;
      node_1->style.padding[CSSEdgeTop] = 20;
      node_1->style.padding[CSSEdgeRight] = 20;
      node_1->style.padding[CSSEdgeBottom] = 20;
      node_1->style.padding[CSSEdgeStart] = 20;
      node_1->style.padding[CSSEdgeEnd] = 20;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 50;
    node_0->layout.dimensions[CSSDimensionHeight] = 40;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 20;
      node_1->layout.dimensions[CSSDimensionWidth] = 40;
      node_1->layout.dimensions[CSSDimensionHeight] = 40;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_negative_width) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = -31;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.border[CSSEdgeRight] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 5;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 5;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_min_padding_and_negative_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.border[CSSEdgeRight] = 1;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.margin[CSSEdgeRight] = -8;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_min_padding_and_negative_margin_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.border[CSSEdgeLeft] = 1;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.margin[CSSEdgeLeft] = -8;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 1;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_just_text) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->measure = measure;
    node_0->context = (char *) SMALL_TEXT;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = SMALL_WIDTH;
    node_0->layout.dimensions[CSSDimensionHeight] = SMALL_HEIGHT;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_fixed_width_and_custom_measure) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->measure = measure;
    node_0->context = (char *) MEASURE_WITH_RATIO_2;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_layout_node_with_fixed_height_and_custom_measure) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    node_0->measure = measure;
    node_0->context = (char *) MEASURE_WITH_RATIO_2;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_skip_measure_if_fixed_height_and_width) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    node_0->measure = measure;
    node_0->context = (char *) MEASURE_WITH_RATIO_2;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_measure) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->measure = measure;
    node_0->context = (char *) MEASURE_WITH_RATIO_2;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 99999;
    node_0->layout.dimensions[CSSDimensionHeight] = 99999;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_nested_stacks_with_measure) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumn;
    node_0->style.dimensions[CSSDimensionWidth] = 320;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->measure = measure;
      node_1->context = (char *) MEASURE_WITH_RATIO_2;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.flexDirection = CSSFlexDirectionRow;
      node_1->style.overflow = CSSOverflowHidden;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->measure = measure;
        node_2->context = (char *) MEASURE_WITH_RATIO_2;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->measure = measure;
        node_2->context = (char *) MEASURE_WITH_RATIO_2;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 320;
    node_0->layout.dimensions[CSSDimensionHeight] = 740;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 320;
      node_1->layout.dimensions[CSSDimensionHeight] = 640;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 640;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 320;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 200;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 200;
        node_2->layout.dimensions[CSSDimensionWidth] = 200;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_text_node_with_width) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 10;
    node_0->measure = measure;
    node_0->context = (char *) SMALL_TEXT;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 10;
    node_0->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_text_node_with_padding_and_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->measure = measure;
    node_0->context = (char *) LONG_TEXT;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = BIG_WIDTH;
    node_0->layout.dimensions[CSSDimensionHeight] = SMALL_HEIGHT;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_nested_alignSelf_stretch) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignSelf = CSSAlignStretch;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.alignSelf = CSSAlignStretch;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 300;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 300;
        node_2->layout.dimensions[CSSDimensionHeight] = 0;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_text_and_flex) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.flexDirection = CSSFlexDirectionRow;
      node_1->style.dimensions[CSSDimensionWidth] = 500;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        CSSNodeStyleSetFlex(node_2, 1);
        node_2->measure = measure;
        node_2->context = (char *) LONG_TEXT;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 500;
    node_0->layout.dimensions[CSSDimensionHeight] = SMALL_HEIGHT;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 500;
      node_1->layout.dimensions[CSSDimensionHeight] = SMALL_HEIGHT;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 500;
        node_2->layout.dimensions[CSSDimensionHeight] = SMALL_HEIGHT;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_text_and_flex_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.direction = CSSDirectionRTL;
      node_1->style.flexDirection = CSSFlexDirectionRow;
      node_1->style.dimensions[CSSDimensionWidth] = 500;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        CSSNodeStyleSetFlex(node_2, 1);
        node_2->measure = measure;
        node_2->context = (char *) LONG_TEXT;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 500;
    node_0->layout.dimensions[CSSDimensionHeight] = SMALL_HEIGHT;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 500;
      node_1->layout.dimensions[CSSDimensionHeight] = SMALL_HEIGHT;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 500;
        node_2->layout.dimensions[CSSDimensionHeight] = SMALL_HEIGHT;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_text_and_stretch) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 130;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignItems = CSSAlignStretch;
      node_1->style.alignSelf = CSSAlignStretch;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->measure = measure;
        node_2->context = (char *) LONG_TEXT;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 130;
    node_0->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 130;
      node_1->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 130;
        node_2->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_text_and_stretch_and_width) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignItems = CSSAlignStretch;
      node_1->style.alignSelf = CSSAlignStretch;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 130;
        node_2->measure = measure;
        node_2->context = (char *) LONG_TEXT;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 130;
        node_2->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_text_bounded_by_parent) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.alignSelf = CSSAlignFlexStart;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignSelf = CSSAlignFlexStart;
      node_1->measure = measure;
      node_1->context = (char *) LONG_TEXT;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_text_bounded_by_grand_parent) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.alignSelf = CSSAlignFlexStart;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.padding[CSSEdgeLeft] = 10;
    node_0->style.padding[CSSEdgeTop] = 10;
    node_0->style.padding[CSSEdgeRight] = 10;
    node_0->style.padding[CSSEdgeBottom] = 10;
    node_0->style.padding[CSSEdgeStart] = 10;
    node_0->style.padding[CSSEdgeEnd] = 10;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignSelf = CSSAlignFlexStart;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->measure = measure;
        node_2->context = (char *) LONG_TEXT;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 76;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 20;
      node_1->layout.position[CSSEdgeLeft] = 20;
      node_1->layout.dimensions[CSSDimensionWidth] = 60;
      node_1->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 60;
        node_2->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_space_between_negative_space) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifySpaceBetween;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 900;
      node_1 = CSSNodeGetChild(node_0, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 900;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 900;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_space_between_negative_space_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.justifyContent = CSSJustifySpaceBetween;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 900;
      node_1 = CSSNodeGetChild(node_0, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = -800;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 900;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = -800;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_flex_end_negative_remaining_space) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.justifyContent = CSSJustifyFlexEnd;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 900;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = -700;
      node_1->layout.dimensions[CSSDimensionWidth] = 900;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_flex_end_negative_remaining_space_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.justifyContent = CSSJustifyFlexEnd;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 900;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 900;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_text_direction_row) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.flexDirection = CSSFlexDirectionRow;
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.margin[CSSEdgeLeft] = 20;
        node_2->style.margin[CSSEdgeTop] = 20;
        node_2->style.margin[CSSEdgeRight] = 20;
        node_2->style.margin[CSSEdgeBottom] = 20;
        node_2->style.margin[CSSEdgeStart] = 20;
        node_2->style.margin[CSSEdgeEnd] = 20;
        node_2->measure = measure;
        node_2->context = (char *) SMALL_TEXT;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 58;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 58;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 20;
        node_2->layout.position[CSSEdgeLeft] = 20;
        node_2->layout.dimensions[CSSDimensionWidth] = SMALL_WIDTH;
        node_2->layout.dimensions[CSSDimensionHeight] = SMALL_HEIGHT;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_text_direction_row_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.flexDirection = CSSFlexDirectionRow;
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.margin[CSSEdgeLeft] = 20;
        node_2->style.margin[CSSEdgeTop] = 20;
        node_2->style.margin[CSSEdgeRight] = 20;
        node_2->style.margin[CSSEdgeBottom] = 20;
        node_2->style.margin[CSSEdgeStart] = 20;
        node_2->style.margin[CSSEdgeEnd] = 20;
        node_2->measure = measure;
        node_2->context = (char *) SMALL_TEXT;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 58;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 58;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 20;
        node_2->layout.position[CSSEdgeLeft] = 145;
        node_2->layout.dimensions[CSSDimensionWidth] = SMALL_WIDTH;
        node_2->layout.dimensions[CSSDimensionHeight] = SMALL_HEIGHT;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_text_with_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.margin[CSSEdgeLeft] = 20;
        node_2->style.margin[CSSEdgeTop] = 20;
        node_2->style.margin[CSSEdgeRight] = 20;
        node_2->style.margin[CSSEdgeBottom] = 20;
        node_2->style.margin[CSSEdgeStart] = 20;
        node_2->style.margin[CSSEdgeEnd] = 20;
        node_2->measure = measure;
        node_2->context = (char *) LONG_TEXT;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 76;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 76;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 20;
        node_2->layout.position[CSSEdgeLeft] = 20;
        node_2->layout.dimensions[CSSDimensionWidth] = 160;
        node_2->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_left_top_right_bottom) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.position[CSSEdgeLeft] = 0;
      node_1->style.position[CSSEdgeTop] = 0;
      node_1->style.position[CSSEdgeRight] = 0;
      node_1->style.position[CSSEdgeBottom] = 0;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_with_arbitrary_flex) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.alignSelf = CSSAlignFlexStart;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignSelf = CSSAlignFlexStart;
      CSSNodeStyleSetFlex(node_1, 2.5);
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.alignSelf = CSSAlignFlexStart;
      CSSNodeStyleSetFlex(node_1, 7.5);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 25;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 25;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 75;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_with_arbitrary_flex_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.alignSelf = CSSAlignFlexStart;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignSelf = CSSAlignFlexStart;
      CSSNodeStyleSetFlex(node_1, 2.5);
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.alignSelf = CSSAlignFlexStart;
      CSSNodeStyleSetFlex(node_1, 7.5);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 75;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 25;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 75;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_with_negative_flex_in_reverse) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionColumnReverse;
    node_0->style.alignSelf = CSSAlignFlexStart;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignSelf = CSSAlignFlexStart;
      CSSNodeStyleSetFlex(node_1, -2.5);
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.alignSelf = CSSAlignFlexStart;
      CSSNodeStyleSetFlex(node_1, 0);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_sibling) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.position[CSSEdgeLeft] = 0;
      node_1->style.position[CSSEdgeRight] = 0;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 50;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_top_bottom) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.position[CSSEdgeTop] = 0;
      node_1->style.position[CSSEdgeBottom] = 20;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 80;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_justifyContent_center) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.justifyContent = CSSJustifyCenter;
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.position[CSSEdgeLeft] = 0;
      node_1->style.position[CSSEdgeTop] = 0;
      node_1->style.position[CSSEdgeRight] = 0;
      node_1->style.position[CSSEdgeBottom] = 0;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 100;
        node_2->style.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 50;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 100;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_bottom) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.position[CSSEdgeBottom] = 0;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_right) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.position[CSSEdgeRight] = 0;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 100;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_bottom_right) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.dimensions[CSSDimensionHeight] = 10;
      node_1->style.position[CSSEdgeBottom] = 0;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 90;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 10;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_right_width) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.dimensions[CSSDimensionWidth] = 10;
      node_1->style.position[CSSEdgeRight] = 0;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 90;
      node_1->layout.dimensions[CSSDimensionWidth] = 10;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_top_with_right_width_and_no_parent_dimension) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.dimensions[CSSDimensionHeight] = 10;
      node_1->style.position[CSSEdgeBottom] = 0;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = -10;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 10;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest,
     test_should_layout_absolute_node_left_with_right_width_and_no_parent_dimension) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.dimensions[CSSDimensionWidth] = 10;
      node_1->style.position[CSSEdgeRight] = 0;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = -10;
      node_1->layout.dimensions[CSSDimensionWidth] = 10;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest,
     test_should_layout_node_with_border_bottom__insidejustifyContent_space_between_container) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifySpaceBetween;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.border[CSSEdgeBottom] = 1;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 1;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 1;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest,
     test_should_layout_node_with_negative_margin_top_inside_justifyContent_center_container) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifyCenter;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.margin[CSSEdgeTop] = -6;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = -3;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest,
     test_should_layout_node_with_margin_top_inside_justifyContent_center_container) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifyCenter;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.margin[CSSEdgeTop] = 20;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 20;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 20;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_border_bottom_and_flex_end_with_empty_child) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.justifyContent = CSSJustifyFlexEnd;
    node_0->style.border[CSSEdgeBottom] = 5;
    init_css_node_children(node_0, 1);
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 5;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_children_of_container_with_left) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 800;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.position[CSSEdgeLeft] = 5;
      init_css_node_children(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 800;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 5;
      node_1->layout.dimensions[CSSDimensionWidth] = 800;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 800;
        node_2->layout.dimensions[CSSDimensionHeight] = 0;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_flexWrap) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.flexWrap = CSSWrapTypeWrap;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 40;
      node_1->style.dimensions[CSSDimensionHeight] = 10;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 40;
      node_1->style.dimensions[CSSDimensionHeight] = 10;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 40;
      node_1->style.dimensions[CSSDimensionHeight] = 10;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 20;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 40;
      node_1->layout.dimensions[CSSDimensionHeight] = 10;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 40;
      node_1->layout.dimensions[CSSDimensionWidth] = 40;
      node_1->layout.dimensions[CSSDimensionHeight] = 10;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 10;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 40;
      node_1->layout.dimensions[CSSDimensionHeight] = 10;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_flexWrap_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.flexWrap = CSSWrapTypeWrap;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 40;
      node_1->style.dimensions[CSSDimensionHeight] = 10;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 40;
      node_1->style.dimensions[CSSDimensionHeight] = 10;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 40;
      node_1->style.dimensions[CSSDimensionHeight] = 10;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 20;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 60;
      node_1->layout.dimensions[CSSDimensionWidth] = 40;
      node_1->layout.dimensions[CSSDimensionHeight] = 10;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 20;
      node_1->layout.dimensions[CSSDimensionWidth] = 40;
      node_1->layout.dimensions[CSSDimensionHeight] = 10;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 10;
      node_1->layout.position[CSSEdgeLeft] = 60;
      node_1->layout.dimensions[CSSDimensionWidth] = 40;
      node_1->layout.dimensions[CSSDimensionHeight] = 10;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_flexWrap_and_line_bigger_than_container) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexWrap = CSSWrapTypeWrap;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionHeight] = 200;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 0;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_max_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    node_0->style.maxDimensions[CSSDimensionWidth] = 90;
    node_0->style.maxDimensions[CSSDimensionHeight] = 190;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 90;
    node_0->layout.dimensions[CSSDimensionHeight] = 190;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_min_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    node_0->style.minDimensions[CSSDimensionWidth] = 110;
    node_0->style.minDimensions[CSSDimensionHeight] = 210;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 110;
    node_0->layout.dimensions[CSSDimensionHeight] = 210;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_min_and_max_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    node_0->style.maxDimensions[CSSDimensionWidth] = 90;
    node_0->style.maxDimensions[CSSDimensionHeight] = 190;
    node_0->style.minDimensions[CSSDimensionWidth] = 110;
    node_0->style.minDimensions[CSSDimensionHeight] = 210;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 110;
    node_0->layout.dimensions[CSSDimensionHeight] = 210;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_min_and_max_bounds_and_width) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    node_0->style.maxDimensions[CSSDimensionWidth] = 80;
    node_0->style.maxDimensions[CSSDimensionHeight] = 180;
    node_0->style.minDimensions[CSSDimensionWidth] = 90;
    node_0->style.minDimensions[CSSDimensionHeight] = 190;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 90;
    node_0->layout.dimensions[CSSDimensionHeight] = 190;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_negative_min_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    node_0->style.minDimensions[CSSDimensionWidth] = -10;
    node_0->style.minDimensions[CSSDimensionHeight] = -20;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_negative_max_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    node_0->style.maxDimensions[CSSDimensionWidth] = -10;
    node_0->style.maxDimensions[CSSDimensionHeight] = -20;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_max_bounds_and_larger_padded_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.maxDimensions[CSSDimensionWidth] = 30;
    node_0->style.maxDimensions[CSSDimensionHeight] = 10;
    node_0->style.padding[CSSEdgeLeft] = 20;
    node_0->style.padding[CSSEdgeTop] = 15;
    node_0->style.padding[CSSEdgeRight] = 20;
    node_0->style.padding[CSSEdgeBottom] = 15;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 40;
    node_0->layout.dimensions[CSSDimensionHeight] = 30;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_min_bounds_and_smaller_padded_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.minDimensions[CSSDimensionWidth] = 50;
    node_0->style.minDimensions[CSSDimensionHeight] = 40;
    node_0->style.padding[CSSEdgeLeft] = 20;
    node_0->style.padding[CSSEdgeTop] = 15;
    node_0->style.padding[CSSEdgeRight] = 20;
    node_0->style.padding[CSSEdgeBottom] = 15;
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 50;
    node_0->layout.dimensions[CSSDimensionHeight] = 40;
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_min_bounds_and_flex) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.minDimensions[CSSDimensionWidth] = 200;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 50;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 250;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_min_bounds_and_flex_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.minDimensions[CSSDimensionWidth] = 200;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 250;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 50;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_flex_size_within_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.maxDimensions[CSSDimensionWidth] = 110;
      node_1->style.minDimensions[CSSDimensionWidth] = 90;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 100;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 200;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_flex_size_within_bounds_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.maxDimensions[CSSDimensionWidth] = 110;
      node_1->style.minDimensions[CSSDimensionWidth] = 90;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 200;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 100;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_max_bounds_and_flex) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.maxDimensions[CSSDimensionWidth] = 60;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 120;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 120;
      node_1->layout.dimensions[CSSDimensionWidth] = 60;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 180;
      node_1->layout.dimensions[CSSDimensionWidth] = 120;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_max_bounds_and_flex_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.maxDimensions[CSSDimensionWidth] = 60;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 180;
      node_1->layout.dimensions[CSSDimensionWidth] = 120;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 120;
      node_1->layout.dimensions[CSSDimensionWidth] = 60;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 120;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_all_children_max_bounds_and_flex) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.maxDimensions[CSSDimensionWidth] = 60;
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.maxDimensions[CSSDimensionWidth] = 60;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.maxDimensions[CSSDimensionWidth] = 60;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 60;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 60;
      node_1->layout.dimensions[CSSDimensionWidth] = 60;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 120;
      node_1->layout.dimensions[CSSDimensionWidth] = 60;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_all_children_max_bounds_and_flex_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.maxDimensions[CSSDimensionWidth] = 60;
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.maxDimensions[CSSDimensionWidth] = 60;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.maxDimensions[CSSDimensionWidth] = 60;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 240;
      node_1->layout.dimensions[CSSDimensionWidth] = 60;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 180;
      node_1->layout.dimensions[CSSDimensionWidth] = 60;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 120;
      node_1->layout.dimensions[CSSDimensionWidth] = 60;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_all_children_min_bounds_and_flex) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.minDimensions[CSSDimensionWidth] = 120;
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.minDimensions[CSSDimensionWidth] = 120;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.minDimensions[CSSDimensionWidth] = 120;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 120;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 120;
      node_1->layout.dimensions[CSSDimensionWidth] = 120;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 240;
      node_1->layout.dimensions[CSSDimensionWidth] = 120;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_all_children_min_bounds_and_flex_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.minDimensions[CSSDimensionWidth] = 120;
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.minDimensions[CSSDimensionWidth] = 120;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.minDimensions[CSSDimensionWidth] = 120;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 180;
      node_1->layout.dimensions[CSSDimensionWidth] = 120;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 60;
      node_1->layout.dimensions[CSSDimensionWidth] = 120;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = -60;
      node_1->layout.dimensions[CSSDimensionWidth] = 120;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_prefill_child_size_within_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.maxDimensions[CSSDimensionWidth] = 310;
      node_1->style.minDimensions[CSSDimensionWidth] = 290;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 300;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_prefill_child_size_within_max_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.maxDimensions[CSSDimensionWidth] = 290;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 290;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_prefill_child_size_within_min_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.minDimensions[CSSDimensionWidth] = 310;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 310;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_set_parent_size_based_on_bounded_children) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.maxDimensions[CSSDimensionWidth] = 300;
    node_0->style.maxDimensions[CSSDimensionHeight] = 700;
    node_0->style.minDimensions[CSSDimensionWidth] = 100;
    node_0->style.minDimensions[CSSDimensionHeight] = 500;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 300;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 300;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 600;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 300;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 300;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 300;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_set_parent_size_based_on_max_bounded_children) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.maxDimensions[CSSDimensionWidth] = 100;
    node_0->style.maxDimensions[CSSDimensionHeight] = 500;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 300;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 300;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 500;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 300;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 300;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 300;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_set_parent_size_based_on_min_bounded_children) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.minDimensions[CSSDimensionWidth] = 300;
    node_0->style.minDimensions[CSSDimensionHeight] = 700;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 300;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 200;
      node_1->style.dimensions[CSSDimensionHeight] = 300;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 700;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 300;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 300;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 300;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_keep_stretched_size_within_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.alignItems = CSSAlignStretch;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.maxDimensions[CSSDimensionWidth] = 1100;
      node_1->style.maxDimensions[CSSDimensionHeight] = 110;
      node_1->style.minDimensions[CSSDimensionWidth] = 900;
      node_1->style.minDimensions[CSSDimensionHeight] = 90;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 1000;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_keep_stretched_size_within_max_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.alignItems = CSSAlignStretch;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.maxDimensions[CSSDimensionWidth] = 900;
      node_1->style.maxDimensions[CSSDimensionHeight] = 90;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 90;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 900;
      node_1->layout.dimensions[CSSDimensionHeight] = 90;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_keep_stretched_size_within_min_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.alignItems = CSSAlignStretch;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.minDimensions[CSSDimensionWidth] = 1100;
      node_1->style.minDimensions[CSSDimensionHeight] = 110;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 110;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 1100;
      node_1->layout.dimensions[CSSDimensionHeight] = 110;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_keep_cross_axis_within_min_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.minDimensions[CSSDimensionWidth] = 100;
      node_1->style.minDimensions[CSSDimensionHeight] = 110;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 110;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 110;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_keep_cross_axis_within_min_bounds_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.minDimensions[CSSDimensionWidth] = 100;
      node_1->style.minDimensions[CSSDimensionHeight] = 110;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 110;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 900;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 110;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_top_left_max_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.maxDimensions[CSSDimensionWidth] = 500;
      node_1->style.maxDimensions[CSSDimensionHeight] = 600;
      node_1->style.position[CSSEdgeLeft] = 100;
      node_1->style.position[CSSEdgeTop] = 100;
      node_1->style.position[CSSEdgeRight] = 100;
      node_1->style.position[CSSEdgeBottom] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 100;
      node_1->layout.dimensions[CSSDimensionWidth] = 500;
      node_1->layout.dimensions[CSSDimensionHeight] = 600;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_top_left_min_bounds) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.minDimensions[CSSDimensionWidth] = 900;
      node_1->style.minDimensions[CSSDimensionHeight] = 1000;
      node_1->style.position[CSSEdgeLeft] = 100;
      node_1->style.position[CSSEdgeTop] = 100;
      node_1->style.position[CSSEdgeRight] = 100;
      node_1->style.position[CSSEdgeBottom] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 100;
      node_1->layout.dimensions[CSSDimensionWidth] = 900;
      node_1->layout.dimensions[CSSDimensionHeight] = 1000;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_center_flex_item_with_max_size) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.justifyContent = CSSJustifyCenter;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.dimensions[CSSDimensionHeight] = 1000;
      node_1->style.maxDimensions[CSSDimensionWidth] = 600;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 200;
      node_1->layout.dimensions[CSSDimensionWidth] = 600;
      node_1->layout.dimensions[CSSDimensionHeight] = 1000;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_correctly_size_flex_items_with_flexBasis_and_max_width) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 1000;
    node_0->style.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 1000;
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 1000;
      node_1->style.maxDimensions[CSSDimensionWidth] = 200;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 1000;
    node_0->layout.dimensions[CSSDimensionHeight] = 1000;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 800;
      node_1->layout.dimensions[CSSDimensionHeight] = 1000;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 800;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 1000;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_absolute_parent) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 400;
    node_0->style.dimensions[CSSDimensionHeight] = 400;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.padding[CSSEdgeLeft] = 10;
      node_1->style.padding[CSSEdgeTop] = 10;
      node_1->style.padding[CSSEdgeRight] = 10;
      node_1->style.padding[CSSEdgeBottom] = 10;
      node_1->style.padding[CSSEdgeStart] = 10;
      node_1->style.padding[CSSEdgeEnd] = 10;
      node_1->style.position[CSSEdgeLeft] = 100;
      node_1->style.position[CSSEdgeTop] = 100;
      node_1->style.position[CSSEdgeRight] = 100;
      node_1->style.position[CSSEdgeBottom] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.positionType = CSSPositionTypeAbsolute;
        node_2->style.position[CSSEdgeLeft] = 10;
        node_2->style.position[CSSEdgeTop] = 10;
        node_2->style.position[CSSEdgeRight] = 10;
        node_2->style.position[CSSEdgeBottom] = 10;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 400;
    node_0->layout.dimensions[CSSDimensionHeight] = 400;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 100;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 10;
        node_2->layout.position[CSSEdgeLeft] = 10;
        node_2->layout.dimensions[CSSDimensionWidth] = 180;
        node_2->layout.dimensions[CSSDimensionHeight] = 180;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_absolute_parent_with_border) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 400;
    node_0->style.dimensions[CSSDimensionHeight] = 400;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.positionType = CSSPositionTypeAbsolute;
      node_1->style.padding[CSSEdgeLeft] = 10;
      node_1->style.padding[CSSEdgeTop] = 10;
      node_1->style.padding[CSSEdgeRight] = 10;
      node_1->style.padding[CSSEdgeBottom] = 10;
      node_1->style.padding[CSSEdgeStart] = 10;
      node_1->style.padding[CSSEdgeEnd] = 10;
      node_1->style.border[CSSEdgeLeft] = 1;
      node_1->style.border[CSSEdgeTop] = 1;
      node_1->style.border[CSSEdgeRight] = 1;
      node_1->style.border[CSSEdgeBottom] = 1;
      node_1->style.border[CSSEdgeStart] = 1;
      node_1->style.border[CSSEdgeEnd] = 1;
      node_1->style.position[CSSEdgeLeft] = 100;
      node_1->style.position[CSSEdgeTop] = 100;
      node_1->style.position[CSSEdgeRight] = 100;
      node_1->style.position[CSSEdgeBottom] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.positionType = CSSPositionTypeAbsolute;
        node_2->style.position[CSSEdgeLeft] = 10;
        node_2->style.position[CSSEdgeTop] = 10;
        node_2->style.position[CSSEdgeRight] = 10;
        node_2->style.position[CSSEdgeBottom] = 10;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 400;
    node_0->layout.dimensions[CSSDimensionHeight] = 400;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 100;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 11;
        node_2->layout.position[CSSEdgeLeft] = 11;
        node_2->layout.dimensions[CSSDimensionWidth] = 178;
        node_2->layout.dimensions[CSSDimensionHeight] = 178;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_absolute_node_with_parent_with_padding_and_flex) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 400;
    node_0->style.dimensions[CSSDimensionHeight] = 400;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.padding[CSSEdgeLeft] = 10;
      node_1->style.padding[CSSEdgeTop] = 10;
      node_1->style.padding[CSSEdgeRight] = 10;
      node_1->style.padding[CSSEdgeBottom] = 10;
      node_1->style.padding[CSSEdgeStart] = 10;
      node_1->style.padding[CSSEdgeEnd] = 10;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.positionType = CSSPositionTypeAbsolute;
        node_2->style.position[CSSEdgeLeft] = 10;
        node_2->style.position[CSSEdgeTop] = 10;
        node_2->style.position[CSSEdgeRight] = 10;
        node_2->style.position[CSSEdgeBottom] = 10;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 400;
    node_0->layout.dimensions[CSSDimensionHeight] = 400;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 400;
      node_1->layout.dimensions[CSSDimensionHeight] = 400;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 10;
        node_2->layout.position[CSSEdgeLeft] = 10;
        node_2->layout.dimensions[CSSDimensionWidth] = 380;
        node_2->layout.dimensions[CSSDimensionHeight] = 380;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_nested_nodes_with_mixed_directions) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.flexDirection = CSSFlexDirectionRow;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 50;
        node_2->style.dimensions[CSSDimensionHeight] = 50;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->style.dimensions[CSSDimensionWidth] = 50;
        node_2->style.dimensions[CSSDimensionHeight] = 50;
      }
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.direction = CSSDirectionLTR;
      node_1->style.flexDirection = CSSFlexDirectionRow;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 50;
        node_2->style.dimensions[CSSDimensionHeight] = 50;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->style.dimensions[CSSDimensionWidth] = 50;
        node_2->style.dimensions[CSSDimensionHeight] = 50;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 150;
        node_2->layout.dimensions[CSSDimensionWidth] = 50;
        node_2->layout.dimensions[CSSDimensionHeight] = 50;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 100;
        node_2->layout.dimensions[CSSDimensionWidth] = 50;
        node_2->layout.dimensions[CSSDimensionHeight] = 50;
      }
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 50;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      init_css_node_children(node_1, 2);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 50;
        node_2->layout.dimensions[CSSDimensionHeight] = 50;
        node_2 = CSSNodeGetChild(node_1, 1);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 50;
        node_2->layout.dimensions[CSSDimensionWidth] = 50;
        node_2->layout.dimensions[CSSDimensionHeight] = 50;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_correctly_space_wrapped_nodes) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.justifyContent = CSSJustifySpaceBetween;
    node_0->style.flexWrap = CSSWrapTypeWrap;
    node_0->style.dimensions[CSSDimensionWidth] = 320;
    node_0->style.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 6);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 3);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 4);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 5);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 320;
    node_0->layout.dimensions[CSSDimensionHeight] = 200;
    init_css_node_children(node_0, 6);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 110;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 220;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 3);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 4);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 110;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 5);
      node_1->layout.position[CSSEdgeTop] = 100;
      node_1->layout.position[CSSEdgeLeft] = 220;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_prefer_start_end_padding) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    node_0->style.padding[CSSEdgeLeft] = 5;
    node_0->style.padding[CSSEdgeRight] = 5;
    node_0->style.padding[CSSEdgeStart] = 15;
    node_0->style.padding[CSSEdgeEnd] = 15;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 50;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 50;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 15;
      node_1->layout.dimensions[CSSDimensionWidth] = 170;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_prefer_start_end_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 5;
      node_1->style.margin[CSSEdgeRight] = 5;
      node_1->style.margin[CSSEdgeStart] = 15;
      node_1->style.margin[CSSEdgeEnd] = 15;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 50;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 15;
      node_1->layout.dimensions[CSSDimensionWidth] = 170;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_prefer_start_end_border) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    node_0->style.border[CSSEdgeLeft] = 5;
    node_0->style.border[CSSEdgeRight] = 5;
    node_0->style.border[CSSEdgeStart] = 15;
    node_0->style.border[CSSEdgeEnd] = 15;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 50;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 50;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 15;
      node_1->layout.dimensions[CSSDimensionWidth] = 170;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_start_end_padding) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    node_0->style.padding[CSSEdgeStart] = 15;
    node_0->style.padding[CSSEdgeEnd] = 5;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 50;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 50;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 15;
      node_1->layout.dimensions[CSSDimensionWidth] = 180;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_start_end_padding_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    node_0->style.padding[CSSEdgeStart] = 15;
    node_0->style.padding[CSSEdgeEnd] = 5;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 50;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 50;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 5;
      node_1->layout.dimensions[CSSDimensionWidth] = 180;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_start_end_margin) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeStart] = 15;
      node_1->style.margin[CSSEdgeEnd] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 50;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 15;
      node_1->layout.dimensions[CSSDimensionWidth] = 180;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_start_end_margin_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.direction = CSSDirectionRTL;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeStart] = 15;
      node_1->style.margin[CSSEdgeEnd] = 5;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 50;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 5;
      node_1->layout.dimensions[CSSDimensionWidth] = 180;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_start_end_border) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    node_0->style.border[CSSEdgeStart] = 15;
    node_0->style.border[CSSEdgeEnd] = 5;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 50;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 50;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 15;
      node_1->layout.dimensions[CSSDimensionWidth] = 180;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_start_end_border_rtl) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.direction = CSSDirectionRTL;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    node_0->style.border[CSSEdgeStart] = 15;
    node_0->style.border[CSSEdgeEnd] = 5;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionHeight] = 50;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 50;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 5;
      node_1->layout.dimensions[CSSDimensionWidth] = 180;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_zero_width) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 200;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 0;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 0;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_propagate_size_contraints_from_flex_parent) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.alignItems = CSSAlignFlexStart;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 10;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 10;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.flexDirection = CSSFlexDirectionColumn;
      node_1->style.alignItems = CSSAlignFlexStart;
      CSSNodeStyleSetFlex(node_1, 1);
      node_1->style.dimensions[CSSDimensionHeight] = 10;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        CSSNodeStyleSetFlex(node_2, 1);
        node_2->style.dimensions[CSSDimensionHeight] = 10;
        node_2->measure = measure;
        node_2->context = (char *) MEASURE_WITH_MATCH_PARENT;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 10;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 10;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 50;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 10;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 50;
        node_2->layout.dimensions[CSSDimensionHeight] = 10;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_content_of_item_stretched_late) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.alignItems = CSSAlignStretch;
    node_0->style.dimensions[CSSDimensionWidth] = 150;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.flexDirection = CSSFlexDirectionRow;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.flexDirection = CSSFlexDirectionRow;
        init_css_node_children(node_2, 1);
        {
          CSSNode *node_3;
          node_3 = CSSNodeGetChild(node_2, 0);
          node_3->style.alignSelf = CSSAlignCenter;
        }
      }
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionHeight] = 150;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 150;
    node_0->layout.dimensions[CSSDimensionHeight] = 150;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 10;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 140;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 0;
        node_2->layout.dimensions[CSSDimensionHeight] = 140;
        init_css_node_children(node_2, 1);
        {
          CSSNode *node_3;
          node_3 = CSSNodeGetChild(node_2, 0);
          node_3->layout.position[CSSEdgeTop] = 70;
          node_3->layout.position[CSSEdgeLeft] = 0;
          node_3->layout.dimensions[CSSDimensionWidth] = 0;
          node_3->layout.dimensions[CSSDimensionHeight] = 0;
        }
      }
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 150;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_with_sibling_dependent_position) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 200;
        node_2->style.dimensions[CSSDimensionHeight] = 200;
      }
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      init_css_node_children(node_1, 1);
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 210;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 200;
      node_1->layout.dimensions[CSSDimensionHeight] = 200;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 200;
        node_2->layout.dimensions[CSSDimensionHeight] = 200;
      }
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 210;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 190;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 190;
        node_2->layout.dimensions[CSSDimensionHeight] = 0;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_node_undefined_cross_axis_and_alignSelf_stretch) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.alignSelf = CSSAlignFlexStart;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.alignSelf = CSSAlignStretch;
      node_1->style.dimensions[CSSDimensionWidth] = 1;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionHeight] = 150;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 11;
    node_0->layout.dimensions[CSSDimensionHeight] = 150;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 10;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 0;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 1;
      node_1->layout.dimensions[CSSDimensionHeight] = 150;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 11;
      node_1->layout.dimensions[CSSDimensionWidth] = 0;
      node_1->layout.dimensions[CSSDimensionHeight] = 150;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_center_items_within_stretched_layout) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 100;
        node_2->style.dimensions[CSSDimensionHeight] = 100;
      }
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.flexDirection = CSSFlexDirectionColumn;
        node_2->style.alignItems = CSSAlignCenter;
        init_css_node_children(node_2, 1);
        {
          CSSNode *node_3;
          node_3 = CSSNodeGetChild(node_2, 0);
          node_3->style.dimensions[CSSDimensionWidth] = 50;
          node_3->style.dimensions[CSSDimensionHeight] = 50;
        }
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 200;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 2);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 100;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 100;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 100;
        node_2->layout.dimensions[CSSDimensionHeight] = 50;
        init_css_node_children(node_2, 1);
        {
          CSSNode *node_3;
          node_3 = CSSNodeGetChild(node_2, 0);
          node_3->layout.position[CSSEdgeTop] = 0;
          node_3->layout.position[CSSEdgeLeft] = 25;
          node_3->layout.dimensions[CSSDimensionWidth] = 50;
          node_3->layout.dimensions[CSSDimensionHeight] = 50;
        }
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_not_shrink_column_node_when_there_is_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 100;
        node_2->style.dimensions[CSSDimensionHeight] = 25;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 25;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 100;
        node_2->layout.dimensions[CSSDimensionHeight] = 25;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_shrink_column_node_when_there_is_no_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 100;
        node_2->style.dimensions[CSSDimensionHeight] = 200;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 100;
        node_2->layout.dimensions[CSSDimensionHeight] = 200;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest,
     test_should_not_shrink_column_node_with_siblings_when_there_is_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 25;
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 100;
        node_2->style.dimensions[CSSDimensionHeight] = 30;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 15;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 25;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 25;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 30;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 100;
        node_2->layout.dimensions[CSSDimensionHeight] = 30;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 55;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 15;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_shrink_column_node_with_siblings_when_there_is_no_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 25;
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 100;
        node_2->style.dimensions[CSSDimensionHeight] = 80;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 15;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 25;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 25;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 60;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 100;
        node_2->layout.dimensions[CSSDimensionHeight] = 80;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 85;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 15;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(
    CSSLayoutTest,
    test_should_shrink_column_nodes_proporional_to_their_main_size_when_there_is_no_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 30;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 40;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionWidth] = 100;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 22.5;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 22.5;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 40;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 62.5;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 37.5;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_not_shrink_visible_row_node_when_there_is_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 25;
        node_2->style.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 25;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 25;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_shrink_visible_row_node_when_there_is_no_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 200;
        node_2->style.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 200;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest,
     test_should_not_shrink_visible_row_node_with_siblings_when_there_is_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 25;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 30;
        node_2->style.dimensions[CSSDimensionHeight] = 100;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 15;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 25;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 25;
      node_1->layout.dimensions[CSSDimensionWidth] = 30;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 30;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 55;
      node_1->layout.dimensions[CSSDimensionWidth] = 15;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest,
     test_should_shrink_visible_row_node_with_siblings_when_there_is_no_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 25;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 80;
        node_2->style.dimensions[CSSDimensionHeight] = 100;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 15;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 25;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 25;
      node_1->layout.dimensions[CSSDimensionWidth] = 60;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 80;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 85;
      node_1->layout.dimensions[CSSDimensionWidth] = 15;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_shrink_visible_row_nodes_when_there_is_no_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionWidth] = 30;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 40;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 2);
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 22.5;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 22.5;
      node_1->layout.dimensions[CSSDimensionWidth] = 40;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 62.5;
      node_1->layout.dimensions[CSSDimensionWidth] = 37.5;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_not_shrink_hidden_row_node_when_there_is_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.overflow = CSSOverflowHidden;
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 25;
        node_2->style.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 25;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 25;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_shrink_hidden_row_node_when_there_is_no_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.overflow = CSSOverflowHidden;
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 200;
        node_2->style.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 1);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 200;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest,
     test_should_not_shrink_hidden_row_node_with_siblings_when_there_is_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 25;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.overflow = CSSOverflowHidden;
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 30;
        node_2->style.dimensions[CSSDimensionHeight] = 100;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 15;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 25;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 25;
      node_1->layout.dimensions[CSSDimensionWidth] = 30;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 30;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 55;
      node_1->layout.dimensions[CSSDimensionWidth] = 15;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest,
     test_should_shrink_hidden_row_node_with_siblings_when_there_is_no_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 25;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.overflow = CSSOverflowHidden;
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->style.dimensions[CSSDimensionWidth] = 80;
        node_2->style.dimensions[CSSDimensionHeight] = 100;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 15;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 25;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 25;
      node_1->layout.dimensions[CSSDimensionWidth] = 60;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 80;
        node_2->layout.dimensions[CSSDimensionHeight] = 100;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 85;
      node_1->layout.dimensions[CSSDimensionWidth] = 15;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest,
     test_should_shrink_hidden_row_nodes_propertional_to_main_size_when_there_is_no_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 100;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.overflow = CSSOverflowHidden;
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionWidth] = 30;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 40;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.overflow = CSSOverflowHidden;
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 100;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 22.5;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 22.5;
      node_1->layout.dimensions[CSSDimensionWidth] = 40;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 62.5;
      node_1->layout.dimensions[CSSDimensionWidth] = 37.5;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_not_shrink_text_node_with_siblings_when_there_is_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 213;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 25;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.flexDirection = CSSFlexDirectionRow;
      node_1->style.alignItems = CSSAlignFlexStart;
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->measure = measure;
        node_2->context = (char *) LONG_TEXT;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 15;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 213;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 25;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 25;
      node_1->layout.dimensions[CSSDimensionWidth] = BIG_WIDTH;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = BIG_WIDTH;
        node_2->layout.dimensions[CSSDimensionHeight] = SMALL_HEIGHT;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 197;
      node_1->layout.dimensions[CSSDimensionWidth] = 15;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_shrink_text_node_with_siblings_when_there_is_no_space_left_over) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.dimensions[CSSDimensionWidth] = 140;
    node_0->style.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 25;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.flexDirection = CSSFlexDirectionRow;
      node_1->style.alignItems = CSSAlignFlexStart;
      CSSNodeStyleSetFlex(node_1, -1);
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        CSSNodeStyleSetFlex(node_2, -1);
        node_2->measure = measure;
        node_2->context = (char *) LONG_TEXT;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 15;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 140;
    node_0->layout.dimensions[CSSDimensionHeight] = 100;
    init_css_node_children(node_0, 3);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 0;
      node_1->layout.dimensions[CSSDimensionWidth] = 25;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 25;
      node_1->layout.dimensions[CSSDimensionWidth] = 100;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      init_css_node_children(node_1, 1);
      {
        CSSNode *node_2;
        node_2 = CSSNodeGetChild(node_1, 0);
        node_2->layout.position[CSSEdgeTop] = 0;
        node_2->layout.position[CSSEdgeLeft] = 0;
        node_2->layout.dimensions[CSSDimensionWidth] = 100;
        node_2->layout.dimensions[CSSDimensionHeight] = BIG_HEIGHT;
      }
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 0;
      node_1->layout.position[CSSEdgeLeft] = 125;
      node_1->layout.dimensions[CSSDimensionWidth] = 15;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_should_layout_with_alignContent_stretch_and_alignItems_flex_start) {
  CSSNode *root_node = new_test_css_node();
  {
    CSSNode *node_0 = root_node;
    node_0->style.flexDirection = CSSFlexDirectionRow;
    node_0->style.alignContent = CSSAlignStretch;
    node_0->style.alignItems = CSSAlignFlexStart;
    node_0->style.flexWrap = CSSWrapTypeWrap;
    node_0->style.dimensions[CSSDimensionWidth] = 300;
    node_0->style.dimensions[CSSDimensionHeight] = 380;
    init_css_node_children(node_0, 15);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 3);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 4);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 5);
      node_1->style.alignSelf = CSSAlignFlexStart;
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 6);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 7);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 100;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 8);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 9);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 10);
      node_1->style.alignSelf = CSSAlignFlexStart;
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 11);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 12);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 13);
      node_1->style.alignSelf = CSSAlignFlexStart;
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
      node_1 = CSSNodeGetChild(node_0, 14);
      node_1->style.dimensions[CSSDimensionWidth] = 50;
      node_1->style.dimensions[CSSDimensionHeight] = 50;
      node_1->style.margin[CSSEdgeLeft] = 10;
      node_1->style.margin[CSSEdgeTop] = 10;
      node_1->style.margin[CSSEdgeRight] = 10;
      node_1->style.margin[CSSEdgeBottom] = 10;
      node_1->style.margin[CSSEdgeStart] = 10;
      node_1->style.margin[CSSEdgeEnd] = 10;
    }
  }

  CSSNode *root_layout = new_test_css_node();
  {
    CSSNode *node_0 = root_layout;
    node_0->layout.position[CSSEdgeTop] = 0;
    node_0->layout.position[CSSEdgeLeft] = 0;
    node_0->layout.dimensions[CSSDimensionWidth] = 300;
    node_0->layout.dimensions[CSSDimensionHeight] = 380;
    init_css_node_children(node_0, 15);
    {
      CSSNode *node_1;
      node_1 = CSSNodeGetChild(node_0, 0);
      node_1->layout.position[CSSEdgeTop] = 10;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      node_1 = CSSNodeGetChild(node_0, 1);
      node_1->layout.position[CSSEdgeTop] = 10;
      node_1->layout.position[CSSEdgeLeft] = 80;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      node_1 = CSSNodeGetChild(node_0, 2);
      node_1->layout.position[CSSEdgeTop] = 10;
      node_1->layout.position[CSSEdgeLeft] = 150;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      node_1 = CSSNodeGetChild(node_0, 3);
      node_1->layout.position[CSSEdgeTop] = 10;
      node_1->layout.position[CSSEdgeLeft] = 220;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      node_1 = CSSNodeGetChild(node_0, 4);
      node_1->layout.position[CSSEdgeTop] = 92.5;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 5);
      node_1->layout.position[CSSEdgeTop] = 92.5;
      node_1->layout.position[CSSEdgeLeft] = 80;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      node_1 = CSSNodeGetChild(node_0, 6);
      node_1->layout.position[CSSEdgeTop] = 92.5;
      node_1->layout.position[CSSEdgeLeft] = 150;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      node_1 = CSSNodeGetChild(node_0, 7);
      node_1->layout.position[CSSEdgeTop] = 92.5;
      node_1->layout.position[CSSEdgeLeft] = 220;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 100;
      node_1 = CSSNodeGetChild(node_0, 8);
      node_1->layout.position[CSSEdgeTop] = 225;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      node_1 = CSSNodeGetChild(node_0, 9);
      node_1->layout.position[CSSEdgeTop] = 225;
      node_1->layout.position[CSSEdgeLeft] = 80;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      node_1 = CSSNodeGetChild(node_0, 10);
      node_1->layout.position[CSSEdgeTop] = 225;
      node_1->layout.position[CSSEdgeLeft] = 150;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      node_1 = CSSNodeGetChild(node_0, 11);
      node_1->layout.position[CSSEdgeTop] = 225;
      node_1->layout.position[CSSEdgeLeft] = 220;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      node_1 = CSSNodeGetChild(node_0, 12);
      node_1->layout.position[CSSEdgeTop] = 307.5;
      node_1->layout.position[CSSEdgeLeft] = 10;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      node_1 = CSSNodeGetChild(node_0, 13);
      node_1->layout.position[CSSEdgeTop] = 307.5;
      node_1->layout.position[CSSEdgeLeft] = 80;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
      node_1 = CSSNodeGetChild(node_0, 14);
      node_1->layout.position[CSSEdgeTop] = 307.5;
      node_1->layout.position[CSSEdgeLeft] = 150;
      node_1->layout.dimensions[CSSDimensionWidth] = 50;
      node_1->layout.dimensions[CSSDimensionHeight] = 50;
    }
  }

  ASSERT_TRUE(test(root_node, root_layout));
}

TEST(CSSLayoutTest, test_dirty_node) {
  CSSNode *root_node = new_test_css_node();
  ASSERT_FALSE(root_node->isDirty);

  CSSNodeStyleSetWidth(root_node, 100);
  CSSNodeStyleSetHeight(root_node, 100);
  ASSERT_TRUE(root_node->isDirty);

  CSSNodeCalculateLayout(root_node, 100, 100, CSSDirectionLTR);
  ASSERT_FALSE(root_node->isDirty);
}
