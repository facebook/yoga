
#include "../Layout.h"

#include <stdio.h>

int main()
{
  {
    printf("%s", "should layout node with alignItems: flex-start\n");
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
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
    css_node_t *root_node = new_css_node();

    css_node_t *node = root_node;
    node->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
    node->style.dimensions[CSS_WIDTH] = 100;

    init_css_node_children(node, 3);
    css_node_t *outer_node = node;
    {
      css_node_t *node = &outer_node->children[0];
      node->style.dimensions[CSS_HEIGHT] = 50;
      node->style.align_items = CSS_ALIGN_STRETCH;
      init_css_node_children(node, 3);
      css_node_t *outer_node = node;
      {
        css_node_t *node = &outer_node->children[0];
        node->style.dimensions[CSS_WIDTH] = 50;
      }

      node = &outer_node->children[0];
    }

    layoutNode(root_node);
    print_style(root_node, 0);
    print_layout(root_node, 0);

    free_css_node(root_node);
  }
}

