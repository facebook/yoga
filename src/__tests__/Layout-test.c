
#include "../Layout.h"

#include <stdio.h>
#include <stdbool.h>

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

int main()
{
  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_WIDTH] = 100;
      node->style.dimensions[CSS_HEIGHT] = 200;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 100;
      node->layout.dimensions[CSS_HEIGHT] = 200;
    }

    test("should layout a single node with width and height", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 3);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 500;
        node->style.dimensions[CSS_HEIGHT] = 500;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 250;
        node->style.dimensions[CSS_HEIGHT] = 250;
        node = &outer_node_1->children[2];
        node->style.dimensions[CSS_WIDTH] = 125;
        node->style.dimensions[CSS_HEIGHT] = 125;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 3);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 500;
        node->layout.dimensions[CSS_HEIGHT] = 500;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 500;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 250;
        node->layout.dimensions[CSS_HEIGHT] = 250;
        node = &outer_node_1->children[2];
        node->layout.position[CSS_TOP] = 750;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 125;
        node->layout.dimensions[CSS_HEIGHT] = 125;
      }
    }

    test("should layout node with children", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 500;
        node->style.dimensions[CSS_HEIGHT] = 500;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 500;
        node->style.dimensions[CSS_HEIGHT] = 500;
        init_css_node_children(node, 2);
        {
          css_node_t *outer_node_2 = node;
          css_node_t *node;
          node = &outer_node_2->children[0];
          node->style.dimensions[CSS_WIDTH] = 250;
          node->style.dimensions[CSS_HEIGHT] = 250;
          node = &outer_node_2->children[1];
          node->style.dimensions[CSS_WIDTH] = 250;
          node->style.dimensions[CSS_HEIGHT] = 250;
        }
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 500;
        node->layout.dimensions[CSS_HEIGHT] = 500;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 500;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 500;
        node->layout.dimensions[CSS_HEIGHT] = 500;
        init_css_node_children(node, 2);
        {
          css_node_t *outer_node_2 = node;
          css_node_t *node;
          node = &outer_node_2->children[0];
          node->layout.position[CSS_TOP] = 0;
          node->layout.position[CSS_LEFT] = 0;
          node->layout.dimensions[CSS_WIDTH] = 250;
          node->layout.dimensions[CSS_HEIGHT] = 250;
          node = &outer_node_2->children[1];
          node->layout.position[CSS_TOP] = 250;
          node->layout.position[CSS_LEFT] = 0;
          node->layout.dimensions[CSS_WIDTH] = 250;
          node->layout.dimensions[CSS_HEIGHT] = 250;
        }
      }
    }

    test("should layout node with nested children", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_WIDTH] = 100;
      node->style.dimensions[CSS_HEIGHT] = 200;
      node->style.margin[CSS_LEFT] = 10;
      node->style.margin[CSS_TOP] = 10;
      node->style.margin[CSS_RIGHT] = 10;
      node->style.margin[CSS_BOTTOM] = 10;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 10;
      node->layout.position[CSS_LEFT] = 10;
      node->layout.dimensions[CSS_WIDTH] = 100;
      node->layout.dimensions[CSS_HEIGHT] = 200;
    }

    test("should layout node with margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      node->style.margin[CSS_LEFT] = 10;
      node->style.margin[CSS_TOP] = 10;
      node->style.margin[CSS_RIGHT] = 10;
      node->style.margin[CSS_BOTTOM] = 10;
      init_css_node_children(node, 3);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node->style.margin[CSS_LEFT] = 50;
        node->style.margin[CSS_TOP] = 50;
        node->style.margin[CSS_RIGHT] = 50;
        node->style.margin[CSS_BOTTOM] = 50;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node->style.margin[CSS_LEFT] = 25;
        node->style.margin[CSS_TOP] = 25;
        node->style.margin[CSS_RIGHT] = 25;
        node->style.margin[CSS_BOTTOM] = 25;
        node = &outer_node_1->children[2];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node->style.margin[CSS_LEFT] = 10;
        node->style.margin[CSS_TOP] = 10;
        node->style.margin[CSS_RIGHT] = 10;
        node->style.margin[CSS_BOTTOM] = 10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 10;
      node->layout.position[CSS_LEFT] = 10;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 3);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 50;
        node->layout.position[CSS_LEFT] = 50;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 225;
        node->layout.position[CSS_LEFT] = 25;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[2];
        node->layout.position[CSS_TOP] = 360;
        node->layout.position[CSS_LEFT] = 10;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with several children", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 200;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 300;
        node->style.dimensions[CSS_HEIGHT] = 150;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 200;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 100;
        node->layout.dimensions[CSS_WIDTH] = 300;
        node->layout.dimensions[CSS_HEIGHT] = 150;
      }
    }

    test("should layout node with row flex direction", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_WIDTH] = 300;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 200;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 300;
        node->style.dimensions[CSS_HEIGHT] = 150;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 300;
      node->layout.dimensions[CSS_HEIGHT] = 350;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 200;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 200;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 300;
        node->layout.dimensions[CSS_HEIGHT] = 150;
      }
    }

    test("should layout node based on children main dimensions", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 200;
        node = &outer_node_1->children[1];
        node->style.flex = CSS_FLEX_ONE;
        node->style.dimensions[CSS_WIDTH] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 200;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 200;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 800;
      }
    }

    test("should layout node with flex", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.flex = CSS_FLEX_ONE;
        node->style.dimensions[CSS_WIDTH] = 1000;
        init_css_node_children(node, 1);
        {
          css_node_t *outer_node_2 = node;
          css_node_t *node;
          node = &outer_node_2->children[0];
          node->style.flex = CSS_FLEX_ONE;
          node->style.dimensions[CSS_WIDTH] = 1000;
          init_css_node_children(node, 1);
          {
            css_node_t *outer_node_3 = node;
            css_node_t *node;
            node = &outer_node_3->children[0];
            node->style.flex = CSS_FLEX_ONE;
            node->style.dimensions[CSS_WIDTH] = 1000;
          }
        }
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 1000;
        node->layout.dimensions[CSS_HEIGHT] = 1000;
        init_css_node_children(node, 1);
        {
          css_node_t *outer_node_2 = node;
          css_node_t *node;
          node = &outer_node_2->children[0];
          node->layout.position[CSS_TOP] = 0;
          node->layout.position[CSS_LEFT] = 0;
          node->layout.dimensions[CSS_WIDTH] = 1000;
          node->layout.dimensions[CSS_HEIGHT] = 1000;
          init_css_node_children(node, 1);
          {
            css_node_t *outer_node_3 = node;
            css_node_t *node;
            node = &outer_node_3->children[0];
            node->layout.position[CSS_TOP] = 0;
            node->layout.position[CSS_LEFT] = 0;
            node->layout.dimensions[CSS_WIDTH] = 1000;
            node->layout.dimensions[CSS_HEIGHT] = 1000;
          }
        }
      }
    }

    test("should layout node with flex recursively", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      node->style.margin[CSS_LEFT] = 5;
      node->style.margin[CSS_TOP] = 10;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node->style.margin[CSS_LEFT] = 15;
        node->style.margin[CSS_TOP] = 50;
        node->style.margin[CSS_BOTTOM] = 20;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node->style.margin[CSS_LEFT] = 30;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 10;
      node->layout.position[CSS_LEFT] = 5;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 50;
        node->layout.position[CSS_LEFT] = 15;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 170;
        node->layout.position[CSS_LEFT] = 30;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with targeted margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.justify_content = CSS_JUSTIFY_FLEX_START;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 100;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: flex-start", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 800;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 900;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: flex-end", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 900;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: space-between", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 200;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 700;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: space-around", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.justify_content = CSS_JUSTIFY_CENTER;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 400;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 500;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: center", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.flex = CSS_FLEX_ONE;
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 1000;
      }
    }

    test("should layout node with flex override height", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.align_items = CSS_ALIGN_FLEX_START;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 200;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 200;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 100;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItems: flex-start", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.align_items = CSS_ALIGN_CENTER;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 200;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 400;
        node->layout.dimensions[CSS_WIDTH] = 200;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 100;
        node->layout.position[CSS_LEFT] = 450;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItems: center", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.align_items = CSS_ALIGN_FLEX_END;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 200;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 800;
        node->layout.dimensions[CSS_WIDTH] = 200;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 100;
        node->layout.position[CSS_LEFT] = 900;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItems: flex-end", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.align_items = CSS_ALIGN_FLEX_END;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_WIDTH] = 200;
        node->style.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->style.align_self = CSS_ALIGN_CENTER;
        node->style.dimensions[CSS_WIDTH] = 100;
        node->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 800;
        node->layout.dimensions[CSS_WIDTH] = 200;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 100;
        node->layout.position[CSS_LEFT] = 450;
        node->layout.dimensions[CSS_WIDTH] = 100;
        node->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with alignSelf overrides alignItems", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.align_items = CSS_ALIGN_STRETCH;
      node->style.dimensions[CSS_WIDTH] = 1000;
      node->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 1000;
      node->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 1000;
        node->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItem: stretch", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout empty node", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.margin[CSS_LEFT] = 5;
        node->style.margin[CSS_TOP] = 5;
        node->style.margin[CSS_RIGHT] = 5;
        node->style.margin[CSS_BOTTOM] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 10;
      node->layout.dimensions[CSS_HEIGHT] = 10;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 5;
        node->layout.position[CSS_LEFT] = 5;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout child with margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_HEIGHT] = 100;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->style.dimensions[CSS_HEIGHT] = 200;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 100;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 100;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 200;
      }
    }

    test("should not shrink children if not enough space", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.justify_content = CSS_JUSTIFY_CENTER;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("should layout for center", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node->style.dimensions[CSS_HEIGHT] = 100;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.margin[CSS_TOP] = 10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 100;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 100;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout flex-end taking into account margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.align_items = CSS_ALIGN_FLEX_END;
        init_css_node_children(node, 2);
        {
          css_node_t *outer_node_2 = node;
          css_node_t *node;
          node = &outer_node_2->children[0];
          node->style.margin[CSS_LEFT] = 10;
          node->style.margin[CSS_TOP] = 10;
          node->style.margin[CSS_RIGHT] = 10;
          node->style.margin[CSS_BOTTOM] = 10;
          node = &outer_node_2->children[1];
          node->style.dimensions[CSS_HEIGHT] = 100;
        }
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 20;
      node->layout.dimensions[CSS_HEIGHT] = 120;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 20;
        node->layout.dimensions[CSS_HEIGHT] = 120;
        init_css_node_children(node, 2);
        {
          css_node_t *outer_node_2 = node;
          css_node_t *node;
          node = &outer_node_2->children[0];
          node->layout.position[CSS_TOP] = 10;
          node->layout.position[CSS_LEFT] = 10;
          node->layout.dimensions[CSS_WIDTH] = 0;
          node->layout.dimensions[CSS_HEIGHT] = 0;
          node = &outer_node_2->children[1];
          node->layout.position[CSS_TOP] = 20;
          node->layout.position[CSS_LEFT] = 20;
          node->layout.dimensions[CSS_WIDTH] = 0;
          node->layout.dimensions[CSS_HEIGHT] = 100;
        }
      }
    }

    test("should layout alignItems with margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.flex = CSS_FLEX_ONE;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout flex inside of an empty element", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.align_items = CSS_ALIGN_STRETCH;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.margin[CSS_LEFT] = 10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 10;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 10;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout alignItems stretch and margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.padding[CSS_LEFT] = 5;
      node->style.padding[CSS_TOP] = 5;
      node->style.padding[CSS_RIGHT] = 5;
      node->style.padding[CSS_BOTTOM] = 5;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 10;
      node->layout.dimensions[CSS_HEIGHT] = 10;
    }

    test("should layout node with padding", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.padding[CSS_LEFT] = 5;
      node->style.padding[CSS_TOP] = 5;
      node->style.padding[CSS_RIGHT] = 5;
      node->style.padding[CSS_BOTTOM] = 5;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 10;
      node->layout.dimensions[CSS_HEIGHT] = 10;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 5;
        node->layout.position[CSS_LEFT] = 5;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with padding and a child", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.padding[CSS_LEFT] = 5;
      node->style.padding[CSS_TOP] = 5;
      node->style.padding[CSS_RIGHT] = 5;
      node->style.padding[CSS_BOTTOM] = 5;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.margin[CSS_LEFT] = 5;
        node->style.margin[CSS_TOP] = 5;
        node->style.margin[CSS_RIGHT] = 5;
        node->style.margin[CSS_BOTTOM] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 20;
      node->layout.dimensions[CSS_HEIGHT] = 20;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 10;
        node->layout.position[CSS_LEFT] = 10;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with padding and a child with margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.align_self = CSS_ALIGN_STRETCH;
        node->style.padding[CSS_LEFT] = 10;
        node->style.padding[CSS_TOP] = 10;
        node->style.padding[CSS_RIGHT] = 10;
        node->style.padding[CSS_BOTTOM] = 10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 20;
      node->layout.dimensions[CSS_HEIGHT] = 20;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 20;
        node->layout.dimensions[CSS_HEIGHT] = 20;
      }
    }

    test("should layout node with padding and stretch", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.padding[CSS_LEFT] = 50;
      node->style.padding[CSS_TOP] = 50;
      node->style.padding[CSS_RIGHT] = 50;
      node->style.padding[CSS_BOTTOM] = 50;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.align_self = CSS_ALIGN_STRETCH;
        node->style.padding[CSS_LEFT] = 10;
        node->style.padding[CSS_TOP] = 10;
        node->style.padding[CSS_RIGHT] = 10;
        node->style.padding[CSS_BOTTOM] = 10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 120;
      node->layout.dimensions[CSS_HEIGHT] = 120;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 50;
        node->layout.position[CSS_LEFT] = 50;
        node->layout.dimensions[CSS_WIDTH] = 20;
        node->layout.dimensions[CSS_HEIGHT] = 20;
      }
    }

    test("should layout node with inner & outer padding and stretch", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.align_self = CSS_ALIGN_STRETCH;
        init_css_node_children(node, 1);
        {
          css_node_t *outer_node_2 = node;
          css_node_t *node;
          node = &outer_node_2->children[0];
          node->style.margin[CSS_LEFT] = 16;
          node->style.margin[CSS_TOP] = 16;
          node->style.margin[CSS_RIGHT] = 16;
          node->style.margin[CSS_BOTTOM] = 16;
        }
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 32;
      node->layout.dimensions[CSS_HEIGHT] = 32;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 32;
        node->layout.dimensions[CSS_HEIGHT] = 32;
        init_css_node_children(node, 1);
        {
          css_node_t *outer_node_2 = node;
          css_node_t *node;
          node = &outer_node_2->children[0];
          node->layout.position[CSS_TOP] = 16;
          node->layout.position[CSS_LEFT] = 16;
          node->layout.dimensions[CSS_WIDTH] = 0;
          node->layout.dimensions[CSS_HEIGHT] = 0;
        }
      }
    }

    test("should layout node with stretch and child with margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.position[CSS_LEFT] = 5;
      node->style.position[CSS_TOP] = 5;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 5;
      node->layout.position[CSS_LEFT] = 5;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("should layout node with top and left", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node->style.dimensions[CSS_HEIGHT] = 10;
      node->style.padding[CSS_TOP] = 5;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 10;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 7.5;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with height, padding and space-around", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.position[CSS_BOTTOM] = 5;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = -5;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("should layout node with bottom", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.position[CSS_TOP] = 10;
      node->style.position[CSS_BOTTOM] = 5;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 10;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("should layout node with both top and bottom", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node->style.dimensions[CSS_WIDTH] = 500;
      init_css_node_children(node, 3);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.flex = CSS_FLEX_ONE;
        node = &outer_node_1->children[1];
        node->style.position_type = CSS_POSITION_ABSOLUTE;
        node->style.dimensions[CSS_WIDTH] = 50;
        node = &outer_node_1->children[2];
        node->style.flex = CSS_FLEX_ONE;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 500;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 3);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 250;
        node->layout.dimensions[CSS_HEIGHT] = 0;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 250;
        node->layout.dimensions[CSS_WIDTH] = 50;
        node->layout.dimensions[CSS_HEIGHT] = 0;
        node = &outer_node_1->children[2];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 250;
        node->layout.dimensions[CSS_WIDTH] = 250;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with position: absolute", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.position_type = CSS_POSITION_ABSOLUTE;
        node->style.margin[CSS_RIGHT] = 15;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with child with position: absolute and margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.align_self = CSS_ALIGN_CENTER;
        node->style.position_type = CSS_POSITION_ABSOLUTE;
        node->style.padding[CSS_RIGHT] = 12;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 12;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with position: absolute, padding and alignSelf: center", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_HEIGHT] = 5;
      node->style.padding[CSS_BOTTOM] = 20;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 20;
    }

    test("should work with height smaller than paddingBottom", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_WIDTH] = 5;
      node->style.padding[CSS_LEFT] = 20;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 20;
      node->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("should work with width smaller than paddingLeft", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        init_css_node_children(node, 1);
        {
          css_node_t *outer_node_2 = node;
          css_node_t *node;
          node = &outer_node_2->children[0];
          node->style.dimensions[CSS_WIDTH] = 400;
        }
        node = &outer_node_1->children[1];
        node->style.align_self = CSS_ALIGN_STRETCH;
        node->style.dimensions[CSS_WIDTH] = 200;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 400;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 400;
        node->layout.dimensions[CSS_HEIGHT] = 0;
        init_css_node_children(node, 1);
        {
          css_node_t *outer_node_2 = node;
          css_node_t *node;
          node = &outer_node_2->children[0];
          node->layout.position[CSS_TOP] = 0;
          node->layout.position[CSS_LEFT] = 0;
          node->layout.dimensions[CSS_WIDTH] = 400;
          node->layout.dimensions[CSS_HEIGHT] = 0;
        }
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 200;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with specified width and stretch", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.padding[CSS_LEFT] = 5;
      node->style.padding[CSS_TOP] = 5;
      node->style.padding[CSS_RIGHT] = 5;
      node->style.padding[CSS_BOTTOM] = 5;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.position_type = CSS_POSITION_ABSOLUTE;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 10;
      node->layout.dimensions[CSS_HEIGHT] = 10;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 5;
        node->layout.position[CSS_LEFT] = 5;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with padding and child with position absolute", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->style.position_type = CSS_POSITION_ABSOLUTE;
        node->style.position[CSS_LEFT] = 10;
        node->style.position[CSS_TOP] = 10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 100;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 100;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 10;
        node->layout.position[CSS_LEFT] = 10;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with position absolute, top and left", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.padding[CSS_LEFT] = 20;
      node->style.padding[CSS_TOP] = 20;
      node->style.padding[CSS_RIGHT] = 20;
      node->style.padding[CSS_BOTTOM] = 20;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.position_type = CSS_POSITION_ABSOLUTE;
        node->style.position[CSS_LEFT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 40;
      node->layout.dimensions[CSS_HEIGHT] = 40;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 20;
        node->layout.position[CSS_LEFT] = 5;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with padding and child position absolute, left", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.position_type = CSS_POSITION_ABSOLUTE;
        node->style.margin[CSS_TOP] = 5;
        node->style.position[CSS_TOP] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 10;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with position: absolute, top and marginTop", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.position_type = CSS_POSITION_ABSOLUTE;
        node->style.margin[CSS_LEFT] = 5;
        node->style.position[CSS_LEFT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 10;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with position: absolute, left and marginLeft", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node->style.dimensions[CSS_HEIGHT] = 200;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.position_type = CSS_POSITION_ABSOLUTE;
        node = &outer_node_1->children[1];
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 200;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 100;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 100;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with space-around and child position absolute", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node->style.dimensions[CSS_WIDTH] = 700;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.flex = CSS_FLEX_ONE;
        node->style.margin[CSS_LEFT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 700;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 5;
        node->layout.dimensions[CSS_WIDTH] = 695;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with flex and main margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node->style.dimensions[CSS_WIDTH] = 700;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.flex = CSS_FLEX_ONE;
        node = &outer_node_1->children[1];
        node->style.flex = CSS_FLEX_ONE;
        node->style.padding[CSS_RIGHT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 700;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 347.5;
        node->layout.dimensions[CSS_HEIGHT] = 0;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 347.5;
        node->layout.dimensions[CSS_WIDTH] = 352.5;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with multiple flex and padding", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node->style.dimensions[CSS_WIDTH] = 700;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.flex = CSS_FLEX_ONE;
        node = &outer_node_1->children[1];
        node->style.flex = CSS_FLEX_ONE;
        node->style.margin[CSS_LEFT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 700;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 347.5;
        node->layout.dimensions[CSS_HEIGHT] = 0;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 352.5;
        node->layout.dimensions[CSS_WIDTH] = 347.5;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with multiple flex and margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_HEIGHT] = 300;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.dimensions[CSS_HEIGHT] = 600;
        node = &outer_node_1->children[1];
        node->style.flex = CSS_FLEX_ONE;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 300;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 600;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 600;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with flex and overflow", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node->style.dimensions[CSS_WIDTH] = 600;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.flex = CSS_FLEX_ONE;
        node->style.position_type = CSS_POSITION_ABSOLUTE;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 600;
      node->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with flex and position absolute", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.dimensions[CSS_HEIGHT] = 500;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.flex = CSS_FLEX_ONE;
        node = &outer_node_1->children[1];
        node->style.flex = CSS_FLEX_ONE;
        node->style.position_type = CSS_POSITION_ABSOLUTE;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 500;
      init_css_node_children(node, 2);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 500;
        node = &outer_node_1->children[1];
        node->layout.position[CSS_TOP] = 500;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with double flex and position absolute", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.border[CSS_LEFT] = 5;
      node->style.border[CSS_TOP] = 5;
      node->style.border[CSS_RIGHT] = 5;
      node->style.border[CSS_BOTTOM] = 5;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 10;
      node->layout.dimensions[CSS_HEIGHT] = 10;
    }

    test("should layout node with borderWidth", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.border[CSS_TOP] = 1;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.position_type = CSS_POSITION_ABSOLUTE;
        node->style.position[CSS_TOP] = -1;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 0;
      node->layout.dimensions[CSS_HEIGHT] = 1;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 0;
        node->layout.position[CSS_LEFT] = 0;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with borderWidth and position: absolute, top", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node = root_node;
      node->style.border[CSS_LEFT] = 1;
      node->style.border[CSS_TOP] = 1;
      node->style.border[CSS_RIGHT] = 1;
      node->style.border[CSS_BOTTOM] = 1;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->style.position_type = CSS_POSITION_ABSOLUTE;
        node->style.position[CSS_LEFT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node = root_layout;
      node->layout.position[CSS_TOP] = 0;
      node->layout.position[CSS_LEFT] = 0;
      node->layout.dimensions[CSS_WIDTH] = 2;
      node->layout.dimensions[CSS_HEIGHT] = 2;
      init_css_node_children(node, 1);
      {
        css_node_t *outer_node_1 = node;
        css_node_t *node;
        node = &outer_node_1->children[0];
        node->layout.position[CSS_TOP] = 1;
        node->layout.position[CSS_LEFT] = 6;
        node->layout.dimensions[CSS_WIDTH] = 0;
        node->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with borderWidth and position: absolute, top. cross axis", root_node, root_layout);
  }
}

