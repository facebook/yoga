
#include "../Layout.h"

#include <stdio.h>

int main()
{
  {
    printf("%s", "should layout a single node with width and height\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with children\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 3);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
      node = &outer_node->children[2];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with nested children\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
      node->style.dimensions[CSS_WIDTH] = 500;
      node->style.dimensions[CSS_HEIGHT] = 500;
      init_css_node_children(node, 2);
      css_node_t *outer_node = node;
      {
        css_node_t *node;
        node = &outer_node->children[0];
        node = &outer_node->children[1];
      }
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with margin\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with several children\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    node->style.margin[CSS_LEFT] = 10;
    node->style.margin[CSS_TOP] = 10;
    node->style.margin[CSS_RIGHT] = 10;
    node->style.margin[CSS_BOTTOM] = 10;
    init_css_node_children(node, 3);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
      node = &outer_node->children[2];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with row flex direction\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node based on children main dimensions\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.dimensions[CSS_WIDTH] = 300;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with flex\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with flex recursively\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node->style.flex = CSS_FLEX_ONE;
      node->style.dimensions[CSS_WIDTH] = 1000;
      init_css_node_children(node, 1);
      css_node_t *outer_node = node;
      {
        css_node_t *node;
        node = &outer_node->children[0];
        node->style.flex = CSS_FLEX_ONE;
        node->style.dimensions[CSS_WIDTH] = 1000;
        init_css_node_children(node, 1);
        css_node_t *outer_node = node;
        {
          css_node_t *node;
          node = &outer_node->children[0];
        }
      }
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with targeted margin\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    node->style.margin[CSS_LEFT] = 5;
    node->style.margin[CSS_TOP] = 10;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with justifyContent: flex-start\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.justify_content = CSS_JUSTIFY_FLEX_START;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with justifyContent: flex-end\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.justify_content = CSS_JUSTIFY_FLEX_END;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with justifyContent: space-between\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with justifyContent: space-around\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with justifyContent: center\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.justify_content = CSS_JUSTIFY_CENTER;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with flex override height\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with alignItems: flex-start\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.align_items = CSS_ALIGN_FLEX_START;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with alignItems: center\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.align_items = CSS_ALIGN_CENTER;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with alignItems: flex-end\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.align_items = CSS_ALIGN_FLEX_END;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with alignSelf overrides alignItems\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.align_items = CSS_ALIGN_FLEX_END;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with alignItem: stretch\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.align_items = CSS_ALIGN_STRETCH;
    node->style.dimensions[CSS_WIDTH] = 1000;
    node->style.dimensions[CSS_HEIGHT] = 1000;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout empty node\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout child with margin\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should not shrink children if not enough space\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.dimensions[CSS_HEIGHT] = 100;
    init_css_node_children(node, 2);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node = &outer_node->children[1];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout for center\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout flex-end taking into account margin\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.justify_content = CSS_JUSTIFY_FLEX_END;
    node->style.dimensions[CSS_HEIGHT] = 100;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout alignItems with margin\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node->style.align_items = CSS_ALIGN_FLEX_END;
      init_css_node_children(node, 2);
      css_node_t *outer_node = node;
      {
        css_node_t *node;
        node = &outer_node->children[0];
        node = &outer_node->children[1];
      }
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout flex inside of an empty element\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout alignItems stretch and margin\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.align_items = CSS_ALIGN_STRETCH;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with padding\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with padding and a child\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.padding[CSS_LEFT] = 5;
    node->style.padding[CSS_TOP] = 5;
    node->style.padding[CSS_RIGHT] = 5;
    node->style.padding[CSS_BOTTOM] = 5;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with padding and a child with margin\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.padding[CSS_LEFT] = 5;
    node->style.padding[CSS_TOP] = 5;
    node->style.padding[CSS_RIGHT] = 5;
    node->style.padding[CSS_BOTTOM] = 5;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with padding and stretch\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with inner & outer padding and stretch\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.padding[CSS_LEFT] = 50;
    node->style.padding[CSS_TOP] = 50;
    node->style.padding[CSS_RIGHT] = 50;
    node->style.padding[CSS_BOTTOM] = 50;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with stretch and child with margin\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
      node->style.align_self = CSS_ALIGN_STRETCH;
      init_css_node_children(node, 1);
      css_node_t *outer_node = node;
      {
        css_node_t *node;
        node = &outer_node->children[0];
      }
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with top and left\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with height, padding and space-around\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
    node->style.dimensions[CSS_HEIGHT] = 10;
    node->style.padding[CSS_TOP] = 5;
    init_css_node_children(node, 1);
    css_node_t *outer_node = node;
    {
      css_node_t *node;
      node = &outer_node->children[0];
    }
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with bottom\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }

  {
    printf("%s", "should layout node with both top and bottom\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);
    free_css_node(root_node);
  }
}

