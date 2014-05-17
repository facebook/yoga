
#include "../Layout.h"
#include "../Layout-test-utils.h"

int main()
{
  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 100;
      node_0->style.dimensions[CSS_HEIGHT] = 200;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 100;
      node_0->layout.dimensions[CSS_HEIGHT] = 200;
    }

    test("should layout a single node with width and height", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 3);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 500;
        node_1->style.dimensions[CSS_HEIGHT] = 500;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 250;
        node_1->style.dimensions[CSS_HEIGHT] = 250;
        node_1 = &node_0->children[2];
        node_1->style.dimensions[CSS_WIDTH] = 125;
        node_1->style.dimensions[CSS_HEIGHT] = 125;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 3);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 500;
        node_1->layout.dimensions[CSS_HEIGHT] = 500;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 500;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 250;
        node_1->layout.dimensions[CSS_HEIGHT] = 250;
        node_1 = &node_0->children[2];
        node_1->layout.position[CSS_TOP] = 750;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 125;
        node_1->layout.dimensions[CSS_HEIGHT] = 125;
      }
    }

    test("should layout node with children", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 500;
        node_1->style.dimensions[CSS_HEIGHT] = 500;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 500;
        node_1->style.dimensions[CSS_HEIGHT] = 500;
        init_css_node_children(node_1, 2);
        {
          css_node_t *node_2;
          node_2 = &node_1->children[0];
          node_2->style.dimensions[CSS_WIDTH] = 250;
          node_2->style.dimensions[CSS_HEIGHT] = 250;
          node_2 = &node_1->children[1];
          node_2->style.dimensions[CSS_WIDTH] = 250;
          node_2->style.dimensions[CSS_HEIGHT] = 250;
        }
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 500;
        node_1->layout.dimensions[CSS_HEIGHT] = 500;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 500;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 500;
        node_1->layout.dimensions[CSS_HEIGHT] = 500;
        init_css_node_children(node_1, 2);
        {
          css_node_t *node_2;
          node_2 = &node_1->children[0];
          node_2->layout.position[CSS_TOP] = 0;
          node_2->layout.position[CSS_LEFT] = 0;
          node_2->layout.dimensions[CSS_WIDTH] = 250;
          node_2->layout.dimensions[CSS_HEIGHT] = 250;
          node_2 = &node_1->children[1];
          node_2->layout.position[CSS_TOP] = 250;
          node_2->layout.position[CSS_LEFT] = 0;
          node_2->layout.dimensions[CSS_WIDTH] = 250;
          node_2->layout.dimensions[CSS_HEIGHT] = 250;
        }
      }
    }

    test("should layout node with nested children", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 100;
      node_0->style.dimensions[CSS_HEIGHT] = 200;
      node_0->style.margin[CSS_LEFT] = 10;
      node_0->style.margin[CSS_TOP] = 10;
      node_0->style.margin[CSS_RIGHT] = 10;
      node_0->style.margin[CSS_BOTTOM] = 10;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 10;
      node_0->layout.position[CSS_LEFT] = 10;
      node_0->layout.dimensions[CSS_WIDTH] = 100;
      node_0->layout.dimensions[CSS_HEIGHT] = 200;
    }

    test("should layout node with margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      node_0->style.margin[CSS_LEFT] = 10;
      node_0->style.margin[CSS_TOP] = 10;
      node_0->style.margin[CSS_RIGHT] = 10;
      node_0->style.margin[CSS_BOTTOM] = 10;
      init_css_node_children(node_0, 3);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1->style.margin[CSS_LEFT] = 50;
        node_1->style.margin[CSS_TOP] = 50;
        node_1->style.margin[CSS_RIGHT] = 50;
        node_1->style.margin[CSS_BOTTOM] = 50;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1->style.margin[CSS_LEFT] = 25;
        node_1->style.margin[CSS_TOP] = 25;
        node_1->style.margin[CSS_RIGHT] = 25;
        node_1->style.margin[CSS_BOTTOM] = 25;
        node_1 = &node_0->children[2];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1->style.margin[CSS_LEFT] = 10;
        node_1->style.margin[CSS_TOP] = 10;
        node_1->style.margin[CSS_RIGHT] = 10;
        node_1->style.margin[CSS_BOTTOM] = 10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 10;
      node_0->layout.position[CSS_LEFT] = 10;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 3);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 50;
        node_1->layout.position[CSS_LEFT] = 50;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 225;
        node_1->layout.position[CSS_LEFT] = 25;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[2];
        node_1->layout.position[CSS_TOP] = 360;
        node_1->layout.position[CSS_LEFT] = 10;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with several children", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 200;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 300;
        node_1->style.dimensions[CSS_HEIGHT] = 150;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 200;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 100;
        node_1->layout.dimensions[CSS_WIDTH] = 300;
        node_1->layout.dimensions[CSS_HEIGHT] = 150;
      }
    }

    test("should layout node with row flex direction", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 300;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 200;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 300;
        node_1->style.dimensions[CSS_HEIGHT] = 150;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 300;
      node_0->layout.dimensions[CSS_HEIGHT] = 350;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 200;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 200;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 300;
        node_1->layout.dimensions[CSS_HEIGHT] = 150;
      }
    }

    test("should layout node based on children main dimensions", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 200;
        node_1 = &node_0->children[1];
        node_1->style.flex = CSS_FLEX_ONE;
        node_1->style.dimensions[CSS_WIDTH] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 200;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 200;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 800;
      }
    }

    test("should layout node with flex", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex = CSS_FLEX_ONE;
        node_1->style.dimensions[CSS_WIDTH] = 1000;
        init_css_node_children(node_1, 1);
        {
          css_node_t *node_2;
          node_2 = &node_1->children[0];
          node_2->style.flex = CSS_FLEX_ONE;
          node_2->style.dimensions[CSS_WIDTH] = 1000;
          init_css_node_children(node_2, 1);
          {
            css_node_t *node_3;
            node_3 = &node_2->children[0];
            node_3->style.flex = CSS_FLEX_ONE;
            node_3->style.dimensions[CSS_WIDTH] = 1000;
          }
        }
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 1000;
        node_1->layout.dimensions[CSS_HEIGHT] = 1000;
        init_css_node_children(node_1, 1);
        {
          css_node_t *node_2;
          node_2 = &node_1->children[0];
          node_2->layout.position[CSS_TOP] = 0;
          node_2->layout.position[CSS_LEFT] = 0;
          node_2->layout.dimensions[CSS_WIDTH] = 1000;
          node_2->layout.dimensions[CSS_HEIGHT] = 1000;
          init_css_node_children(node_2, 1);
          {
            css_node_t *node_3;
            node_3 = &node_2->children[0];
            node_3->layout.position[CSS_TOP] = 0;
            node_3->layout.position[CSS_LEFT] = 0;
            node_3->layout.dimensions[CSS_WIDTH] = 1000;
            node_3->layout.dimensions[CSS_HEIGHT] = 1000;
          }
        }
      }
    }

    test("should layout node with flex recursively", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      node_0->style.margin[CSS_LEFT] = 5;
      node_0->style.margin[CSS_TOP] = 10;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1->style.margin[CSS_LEFT] = 15;
        node_1->style.margin[CSS_TOP] = 50;
        node_1->style.margin[CSS_BOTTOM] = 20;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1->style.margin[CSS_LEFT] = 30;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 10;
      node_0->layout.position[CSS_LEFT] = 5;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 50;
        node_1->layout.position[CSS_LEFT] = 15;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 170;
        node_1->layout.position[CSS_LEFT] = 30;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with targeted margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_START;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 100;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: flex-start", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 800;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 900;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: flex-end", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 900;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: space-between", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 200;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 700;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: space-around", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_CENTER;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 400;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 500;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: center", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex = CSS_FLEX_ONE;
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 1000;
      }
    }

    test("should layout node with flex override height", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_FLEX_START;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 200;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 200;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 100;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItems: flex-start", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_CENTER;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 200;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 400;
        node_1->layout.dimensions[CSS_WIDTH] = 200;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 100;
        node_1->layout.position[CSS_LEFT] = 450;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItems: center", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_FLEX_END;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 200;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 800;
        node_1->layout.dimensions[CSS_WIDTH] = 200;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 100;
        node_1->layout.position[CSS_LEFT] = 900;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItems: flex-end", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_FLEX_END;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_WIDTH] = 200;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->style.align_self = CSS_ALIGN_CENTER;
        node_1->style.dimensions[CSS_WIDTH] = 100;
        node_1->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 800;
        node_1->layout.dimensions[CSS_WIDTH] = 200;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 100;
        node_1->layout.position[CSS_LEFT] = 450;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with alignSelf overrides alignItems", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_STRETCH;
      node_0->style.dimensions[CSS_WIDTH] = 1000;
      node_0->style.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_HEIGHT] = 100;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1000;
      node_0->layout.dimensions[CSS_HEIGHT] = 1000;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 1000;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItem: stretch", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout empty node", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.margin[CSS_LEFT] = 5;
        node_1->style.margin[CSS_TOP] = 5;
        node_1->style.margin[CSS_RIGHT] = 5;
        node_1->style.margin[CSS_BOTTOM] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 10;
      node_0->layout.dimensions[CSS_HEIGHT] = 10;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 5;
        node_1->layout.position[CSS_LEFT] = 5;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout child with margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_HEIGHT] = 100;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->style.dimensions[CSS_HEIGHT] = 200;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 100;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 100;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 200;
      }
    }

    test("should not shrink children if not enough space", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_CENTER;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("should layout for center", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node_0->style.dimensions[CSS_HEIGHT] = 100;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.margin[CSS_TOP] = 10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 100;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 100;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout flex-end taking into account margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.align_items = CSS_ALIGN_FLEX_END;
        init_css_node_children(node_1, 2);
        {
          css_node_t *node_2;
          node_2 = &node_1->children[0];
          node_2->style.margin[CSS_LEFT] = 10;
          node_2->style.margin[CSS_TOP] = 10;
          node_2->style.margin[CSS_RIGHT] = 10;
          node_2->style.margin[CSS_BOTTOM] = 10;
          node_2 = &node_1->children[1];
          node_2->style.dimensions[CSS_HEIGHT] = 100;
        }
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 20;
      node_0->layout.dimensions[CSS_HEIGHT] = 120;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 20;
        node_1->layout.dimensions[CSS_HEIGHT] = 120;
        init_css_node_children(node_1, 2);
        {
          css_node_t *node_2;
          node_2 = &node_1->children[0];
          node_2->layout.position[CSS_TOP] = 10;
          node_2->layout.position[CSS_LEFT] = 10;
          node_2->layout.dimensions[CSS_WIDTH] = 0;
          node_2->layout.dimensions[CSS_HEIGHT] = 0;
          node_2 = &node_1->children[1];
          node_2->layout.position[CSS_TOP] = 20;
          node_2->layout.position[CSS_LEFT] = 20;
          node_2->layout.dimensions[CSS_WIDTH] = 0;
          node_2->layout.dimensions[CSS_HEIGHT] = 100;
        }
      }
    }

    test("should layout alignItems with margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex = CSS_FLEX_ONE;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout flex inside of an empty element", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_STRETCH;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.margin[CSS_LEFT] = 10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 10;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 10;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout alignItems stretch and margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.padding[CSS_LEFT] = 5;
      node_0->style.padding[CSS_TOP] = 5;
      node_0->style.padding[CSS_RIGHT] = 5;
      node_0->style.padding[CSS_BOTTOM] = 5;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 10;
      node_0->layout.dimensions[CSS_HEIGHT] = 10;
    }

    test("should layout node with padding", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.padding[CSS_LEFT] = 5;
      node_0->style.padding[CSS_TOP] = 5;
      node_0->style.padding[CSS_RIGHT] = 5;
      node_0->style.padding[CSS_BOTTOM] = 5;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 10;
      node_0->layout.dimensions[CSS_HEIGHT] = 10;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 5;
        node_1->layout.position[CSS_LEFT] = 5;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with padding and a child", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.padding[CSS_LEFT] = 5;
      node_0->style.padding[CSS_TOP] = 5;
      node_0->style.padding[CSS_RIGHT] = 5;
      node_0->style.padding[CSS_BOTTOM] = 5;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.margin[CSS_LEFT] = 5;
        node_1->style.margin[CSS_TOP] = 5;
        node_1->style.margin[CSS_RIGHT] = 5;
        node_1->style.margin[CSS_BOTTOM] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 20;
      node_0->layout.dimensions[CSS_HEIGHT] = 20;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 10;
        node_1->layout.position[CSS_LEFT] = 10;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with padding and a child with margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.align_self = CSS_ALIGN_STRETCH;
        node_1->style.padding[CSS_LEFT] = 10;
        node_1->style.padding[CSS_TOP] = 10;
        node_1->style.padding[CSS_RIGHT] = 10;
        node_1->style.padding[CSS_BOTTOM] = 10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 20;
      node_0->layout.dimensions[CSS_HEIGHT] = 20;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 20;
        node_1->layout.dimensions[CSS_HEIGHT] = 20;
      }
    }

    test("should layout node with padding and stretch", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.padding[CSS_LEFT] = 50;
      node_0->style.padding[CSS_TOP] = 50;
      node_0->style.padding[CSS_RIGHT] = 50;
      node_0->style.padding[CSS_BOTTOM] = 50;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.align_self = CSS_ALIGN_STRETCH;
        node_1->style.padding[CSS_LEFT] = 10;
        node_1->style.padding[CSS_TOP] = 10;
        node_1->style.padding[CSS_RIGHT] = 10;
        node_1->style.padding[CSS_BOTTOM] = 10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 120;
      node_0->layout.dimensions[CSS_HEIGHT] = 120;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 50;
        node_1->layout.position[CSS_LEFT] = 50;
        node_1->layout.dimensions[CSS_WIDTH] = 20;
        node_1->layout.dimensions[CSS_HEIGHT] = 20;
      }
    }

    test("should layout node with inner & outer padding and stretch", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.align_self = CSS_ALIGN_STRETCH;
        init_css_node_children(node_1, 1);
        {
          css_node_t *node_2;
          node_2 = &node_1->children[0];
          node_2->style.margin[CSS_LEFT] = 16;
          node_2->style.margin[CSS_TOP] = 16;
          node_2->style.margin[CSS_RIGHT] = 16;
          node_2->style.margin[CSS_BOTTOM] = 16;
        }
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 32;
      node_0->layout.dimensions[CSS_HEIGHT] = 32;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 32;
        node_1->layout.dimensions[CSS_HEIGHT] = 32;
        init_css_node_children(node_1, 1);
        {
          css_node_t *node_2;
          node_2 = &node_1->children[0];
          node_2->layout.position[CSS_TOP] = 16;
          node_2->layout.position[CSS_LEFT] = 16;
          node_2->layout.dimensions[CSS_WIDTH] = 0;
          node_2->layout.dimensions[CSS_HEIGHT] = 0;
        }
      }
    }

    test("should layout node with stretch and child with margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.position[CSS_LEFT] = 5;
      node_0->style.position[CSS_TOP] = 5;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 5;
      node_0->layout.position[CSS_LEFT] = 5;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("should layout node with top and left", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node_0->style.dimensions[CSS_HEIGHT] = 10;
      node_0->style.padding[CSS_TOP] = 5;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 10;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 7.5;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with height, padding and space-around", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.position[CSS_BOTTOM] = 5;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -5;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("should layout node with bottom", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.position[CSS_TOP] = 10;
      node_0->style.position[CSS_BOTTOM] = 5;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 10;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("should layout node with both top and bottom", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.dimensions[CSS_WIDTH] = 500;
      init_css_node_children(node_0, 3);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex = CSS_FLEX_ONE;
        node_1 = &node_0->children[1];
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.dimensions[CSS_WIDTH] = 50;
        node_1 = &node_0->children[2];
        node_1->style.flex = CSS_FLEX_ONE;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 500;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 3);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 250;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 250;
        node_1->layout.dimensions[CSS_WIDTH] = 50;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
        node_1 = &node_0->children[2];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 250;
        node_1->layout.dimensions[CSS_WIDTH] = 250;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with position: absolute", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.margin[CSS_RIGHT] = 15;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with child with position: absolute and margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.align_self = CSS_ALIGN_CENTER;
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.padding[CSS_RIGHT] = 12;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 12;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with position: absolute, padding and alignSelf: center", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_HEIGHT] = 5;
      node_0->style.padding[CSS_BOTTOM] = 20;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 20;
    }

    test("should work with height smaller than paddingBottom", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 5;
      node_0->style.padding[CSS_LEFT] = 20;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 20;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("should work with width smaller than paddingLeft", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        init_css_node_children(node_1, 1);
        {
          css_node_t *node_2;
          node_2 = &node_1->children[0];
          node_2->style.dimensions[CSS_WIDTH] = 400;
        }
        node_1 = &node_0->children[1];
        node_1->style.align_self = CSS_ALIGN_STRETCH;
        node_1->style.dimensions[CSS_WIDTH] = 200;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 400;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 400;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
        init_css_node_children(node_1, 1);
        {
          css_node_t *node_2;
          node_2 = &node_1->children[0];
          node_2->layout.position[CSS_TOP] = 0;
          node_2->layout.position[CSS_LEFT] = 0;
          node_2->layout.dimensions[CSS_WIDTH] = 400;
          node_2->layout.dimensions[CSS_HEIGHT] = 0;
        }
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 200;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with specified width and stretch", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.padding[CSS_LEFT] = 5;
      node_0->style.padding[CSS_TOP] = 5;
      node_0->style.padding[CSS_RIGHT] = 5;
      node_0->style.padding[CSS_BOTTOM] = 5;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 10;
      node_0->layout.dimensions[CSS_HEIGHT] = 10;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 5;
        node_1->layout.position[CSS_LEFT] = 5;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with padding and child with position absolute", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.position[CSS_LEFT] = 10;
        node_1->style.position[CSS_TOP] = 10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 100;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 100;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 10;
        node_1->layout.position[CSS_LEFT] = 10;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with position absolute, top and left", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.padding[CSS_LEFT] = 20;
      node_0->style.padding[CSS_TOP] = 20;
      node_0->style.padding[CSS_RIGHT] = 20;
      node_0->style.padding[CSS_BOTTOM] = 20;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.position[CSS_LEFT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 40;
      node_0->layout.dimensions[CSS_HEIGHT] = 40;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 20;
        node_1->layout.position[CSS_LEFT] = 5;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with padding and child position absolute, left", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.margin[CSS_TOP] = 5;
        node_1->style.position[CSS_TOP] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 10;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with position: absolute, top and marginTop", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.margin[CSS_LEFT] = 5;
        node_1->style.position[CSS_LEFT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 10;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with position: absolute, left and marginLeft", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node_0->style.dimensions[CSS_HEIGHT] = 200;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1 = &node_0->children[1];
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 200;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 100;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 100;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with space-around and child position absolute", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.dimensions[CSS_WIDTH] = 700;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex = CSS_FLEX_ONE;
        node_1->style.margin[CSS_LEFT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 700;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 5;
        node_1->layout.dimensions[CSS_WIDTH] = 695;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with flex and main margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.dimensions[CSS_WIDTH] = 700;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex = CSS_FLEX_ONE;
        node_1 = &node_0->children[1];
        node_1->style.flex = CSS_FLEX_ONE;
        node_1->style.padding[CSS_RIGHT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 700;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 347.5;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 347.5;
        node_1->layout.dimensions[CSS_WIDTH] = 352.5;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with multiple flex and padding", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.dimensions[CSS_WIDTH] = 700;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex = CSS_FLEX_ONE;
        node_1 = &node_0->children[1];
        node_1->style.flex = CSS_FLEX_ONE;
        node_1->style.margin[CSS_LEFT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 700;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 347.5;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 352.5;
        node_1->layout.dimensions[CSS_WIDTH] = 347.5;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with multiple flex and margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_HEIGHT] = 300;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.dimensions[CSS_HEIGHT] = 600;
        node_1 = &node_0->children[1];
        node_1->style.flex = CSS_FLEX_ONE;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 300;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 600;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 600;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with flex and overflow", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.dimensions[CSS_WIDTH] = 600;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex = CSS_FLEX_ONE;
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 600;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with flex and position absolute", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_HEIGHT] = 500;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex = CSS_FLEX_ONE;
        node_1 = &node_0->children[1];
        node_1->style.flex = CSS_FLEX_ONE;
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 500;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 500;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 500;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with double flex and position absolute", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.border[CSS_LEFT] = 5;
      node_0->style.border[CSS_TOP] = 5;
      node_0->style.border[CSS_RIGHT] = 5;
      node_0->style.border[CSS_BOTTOM] = 5;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 10;
      node_0->layout.dimensions[CSS_HEIGHT] = 10;
    }

    test("should layout node with borderWidth", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.border[CSS_TOP] = 1;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.position[CSS_TOP] = -1;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 1;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with borderWidth and position: absolute, top", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.border[CSS_LEFT] = 1;
      node_0->style.border[CSS_TOP] = 1;
      node_0->style.border[CSS_RIGHT] = 1;
      node_0->style.border[CSS_BOTTOM] = 1;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.position[CSS_LEFT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 2;
      node_0->layout.dimensions[CSS_HEIGHT] = 2;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 1;
        node_1->layout.position[CSS_LEFT] = 6;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with borderWidth and position: absolute, top. cross axis", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 50;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.align_self = CSS_ALIGN_STRETCH;
        node_1->style.margin[CSS_LEFT] = 20;
        node_1->style.padding[CSS_LEFT] = 20;
        node_1->style.padding[CSS_TOP] = 20;
        node_1->style.padding[CSS_RIGHT] = 20;
        node_1->style.padding[CSS_BOTTOM] = 20;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 50;
      node_0->layout.dimensions[CSS_HEIGHT] = 40;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 20;
        node_1->layout.dimensions[CSS_WIDTH] = 40;
        node_1->layout.dimensions[CSS_HEIGHT] = 40;
      }
    }

    test("should correctly take into account min padding for stretch", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.border[CSS_RIGHT] = 5;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 5;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 5;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should layout node with negative width", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.border[CSS_RIGHT] = 1;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.margin[CSS_RIGHT] = -8;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 1;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 0;
        node_1->layout.dimensions[CSS_HEIGHT] = 0;
      }
    }

    test("should handle negative margin and min padding correctly", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 33;
      node_0->layout.dimensions[CSS_HEIGHT] = 18;
    }

    test("should layout node with just text", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 10;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 10;
      node_0->layout.dimensions[CSS_HEIGHT] = 18;
    }

    test("should layout node with text and width", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.margin[CSS_LEFT] = 5;
      node_0->style.margin[CSS_TOP] = 5;
      node_0->style.margin[CSS_RIGHT] = 5;
      node_0->style.margin[CSS_BOTTOM] = 5;
      node_0->style.padding[CSS_LEFT] = 5;
      node_0->style.padding[CSS_TOP] = 5;
      node_0->style.padding[CSS_RIGHT] = 5;
      node_0->style.padding[CSS_BOTTOM] = 5;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 5;
      node_0->layout.position[CSS_LEFT] = 5;
      node_0->layout.dimensions[CSS_WIDTH] = 181;
      node_0->layout.dimensions[CSS_HEIGHT] = 28;
    }

    test("should layout node with text, padding and margin", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.measure = measure;
        node_1->style.measure_context = "loooooooooong with space";
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 0;
        node_1->layout.position[CSS_LEFT] = 0;
        node_1->layout.dimensions[CSS_WIDTH] = 100;
        node_1->layout.dimensions[CSS_HEIGHT] = 36;
      }
    }

    test("should layout node with text and position absolute", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #0", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node_0->style.align_items = CSS_ALIGN_FLEX_END;
      node_0->style.dimensions[CSS_WIDTH] = 860;
      node_0->style.margin[CSS_LEFT] = 10;
      node_0->style.margin[CSS_TOP] = 10;
      node_0->style.margin[CSS_RIGHT] = 1;
      node_0->style.margin[CSS_BOTTOM] = 2;
      node_0->style.border[CSS_LEFT] = 2;
      node_0->style.border[CSS_TOP] = 0;
      node_0->style.position[CSS_TOP] = 0;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 10;
      node_0->layout.position[CSS_LEFT] = 10;
      node_0->layout.dimensions[CSS_WIDTH] = 860;
      node_0->layout.dimensions[CSS_HEIGHT] = 18;
    }

    test("Random #1", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_HEIGHT] = 603;
      node_0->style.margin[CSS_TOP] = -5;
      node_0->style.padding[CSS_RIGHT] = 18;
      node_0->style.border[CSS_LEFT] = 2;
      node_0->style.border[CSS_TOP] = 2;
      node_0->style.border[CSS_RIGHT] = 2;
      node_0->style.border[CSS_BOTTOM] = 2;
      node_0->style.border[CSS_LEFT] = 2;
      node_0->style.border[CSS_TOP] = 2;
      node_0->style.position[CSS_LEFT] = 6;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -5;
      node_0->layout.position[CSS_LEFT] = 6;
      node_0->layout.dimensions[CSS_WIDTH] = 55;
      node_0->layout.dimensions[CSS_HEIGHT] = 603;
    }

    test("Random #2", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
      node_0->style.align_items = CSS_ALIGN_FLEX_START;
      node_0->style.margin[CSS_TOP] = 7;
      node_0->style.margin[CSS_RIGHT] = 10;
      node_0->style.margin[CSS_BOTTOM] = -1;
      node_0->style.padding[CSS_LEFT] = 1;
      node_0->style.padding[CSS_RIGHT] = 6;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 7;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 178;
      node_0->layout.dimensions[CSS_HEIGHT] = 18;
    }

    test("Random #3", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.dimensions[CSS_HEIGHT] = 140;
      node_0->style.margin[CSS_LEFT] = -3;
      node_0->style.margin[CSS_BOTTOM] = 11;
      node_0->style.padding[CSS_LEFT] = 14;
      node_0->style.padding[CSS_TOP] = 14;
      node_0->style.padding[CSS_RIGHT] = 14;
      node_0->style.padding[CSS_BOTTOM] = 14;
      node_0->style.padding[CSS_LEFT] = 5;
      node_0->style.position[CSS_LEFT] = -9;
      node_0->style.position[CSS_TOP] = 8;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 8;
      node_0->layout.position[CSS_LEFT] = -12;
      node_0->layout.dimensions[CSS_WIDTH] = 19;
      node_0->layout.dimensions[CSS_HEIGHT] = 140;
    }

    test("Random #4", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.dimensions[CSS_WIDTH] = 873;
      node_0->style.margin[CSS_LEFT] = 1;
      node_0->style.margin[CSS_TOP] = 1;
      node_0->style.margin[CSS_RIGHT] = 1;
      node_0->style.margin[CSS_BOTTOM] = 1;
      node_0->style.margin[CSS_LEFT] = 16;
      node_0->style.margin[CSS_TOP] = 18;
      node_0->style.padding[CSS_LEFT] = 10;
      node_0->style.padding[CSS_RIGHT] = 13;
      node_0->style.border[CSS_TOP] = 3;
      node_0->style.border[CSS_BOTTOM] = 1;
      node_0->style.position[CSS_TOP] = -3;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 15;
      node_0->layout.position[CSS_LEFT] = 16;
      node_0->layout.dimensions[CSS_WIDTH] = 873;
      node_0->layout.dimensions[CSS_HEIGHT] = 22;
    }

    test("Random #5", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_START;
      node_0->style.dimensions[CSS_WIDTH] = 255;
      node_0->style.margin[CSS_RIGHT] = -6;
      node_0->style.margin[CSS_BOTTOM] = -3;
      node_0->style.padding[CSS_LEFT] = 4;
      node_0->style.padding[CSS_TOP] = 4;
      node_0->style.padding[CSS_RIGHT] = 4;
      node_0->style.padding[CSS_BOTTOM] = 4;
      node_0->style.padding[CSS_TOP] = 8;
      node_0->style.border[CSS_LEFT] = 2;
      node_0->style.border[CSS_TOP] = 2;
      node_0->style.border[CSS_RIGHT] = 2;
      node_0->style.border[CSS_BOTTOM] = 2;
      node_0->style.border[CSS_LEFT] = 1;
      node_0->style.border[CSS_RIGHT] = 2;
      node_0->style.border[CSS_BOTTOM] = 1;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 255;
      node_0->layout.dimensions[CSS_HEIGHT] = 15;
    }

    test("Random #6", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_HEIGHT] = 116;
      node_0->style.margin[CSS_TOP] = 10;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.align_items = CSS_ALIGN_CENTER;
        node_1->style.align_self = CSS_ALIGN_FLEX_START;
        node_1->style.flex = CSS_FLEX_NONE;
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.dimensions[CSS_HEIGHT] = 633;
        node_1->style.margin[CSS_LEFT] = 19;
        node_1->style.margin[CSS_TOP] = 19;
        node_1->style.margin[CSS_RIGHT] = 19;
        node_1->style.margin[CSS_BOTTOM] = 19;
        node_1->style.margin[CSS_LEFT] = 3;
        node_1->style.margin[CSS_TOP] = 17;
        node_1->style.margin[CSS_RIGHT] = 8;
        node_1->style.border[CSS_LEFT] = 2;
        node_1->style.border[CSS_BOTTOM] = 0;
        node_1->style.position[CSS_LEFT] = -10;
        node_1->style.position[CSS_TOP] = 8;
        node_1->style.measure = measure;
        node_1->style.measure_context = "small";
        node_1 = &node_0->children[1];
        node_1->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
        node_1->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
        node_1->style.align_items = CSS_ALIGN_CENTER;
        node_1->style.align_self = CSS_ALIGN_FLEX_END;
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.margin[CSS_LEFT] = 4;
        node_1->style.margin[CSS_TOP] = 13;
        node_1->style.margin[CSS_RIGHT] = -2;
        node_1->style.margin[CSS_BOTTOM] = 1;
        node_1->style.padding[CSS_LEFT] = 2;
        node_1->style.padding[CSS_TOP] = 2;
        node_1->style.padding[CSS_RIGHT] = 2;
        node_1->style.padding[CSS_BOTTOM] = 2;
        node_1->style.padding[CSS_RIGHT] = 5;
        node_1->style.border[CSS_TOP] = 3;
        node_1->style.border[CSS_BOTTOM] = 3;
        node_1->style.position[CSS_LEFT] = -7;
        node_1->style.position[CSS_TOP] = -10;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 10;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 116;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 25;
        node_1->layout.position[CSS_LEFT] = -7;
        node_1->layout.dimensions[CSS_WIDTH] = 35;
        node_1->layout.dimensions[CSS_HEIGHT] = 633;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 3;
        node_1->layout.position[CSS_LEFT] = -3;
        node_1->layout.dimensions[CSS_WIDTH] = 7;
        node_1->layout.dimensions[CSS_HEIGHT] = 10;
      }
    }

    test("Random #7", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node_0->style.align_items = CSS_ALIGN_STRETCH;
      node_0->style.dimensions[CSS_WIDTH] = 426;
      node_0->style.dimensions[CSS_HEIGHT] = 497;
      node_0->style.margin[CSS_TOP] = 1;
      node_0->style.margin[CSS_RIGHT] = 14;
      node_0->style.padding[CSS_RIGHT] = 7;
      node_0->style.border[CSS_LEFT] = 2;
      node_0->style.border[CSS_RIGHT] = 2;
      node_0->style.position[CSS_TOP] = -1;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 426;
      node_0->layout.dimensions[CSS_HEIGHT] = 497;
    }

    test("Random #8", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #9", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #10", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_CENTER;
      node_0->style.align_items = CSS_ALIGN_FLEX_START;
      node_0->style.dimensions[CSS_WIDTH] = 477;
      node_0->style.dimensions[CSS_HEIGHT] = 300;
      node_0->style.margin[CSS_LEFT] = 9;
      node_0->style.padding[CSS_LEFT] = 0;
      node_0->style.padding[CSS_TOP] = 0;
      node_0->style.padding[CSS_RIGHT] = 0;
      node_0->style.padding[CSS_BOTTOM] = 0;
      node_0->style.padding[CSS_LEFT] = 0;
      node_0->style.padding[CSS_TOP] = 15;
      node_0->style.padding[CSS_RIGHT] = 17;
      node_0->style.padding[CSS_BOTTOM] = 16;
      node_0->style.position[CSS_TOP] = 0;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 9;
      node_0->layout.dimensions[CSS_WIDTH] = 477;
      node_0->layout.dimensions[CSS_HEIGHT] = 300;
    }

    test("Random #11", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_START;
      node_0->style.align_items = CSS_ALIGN_FLEX_END;
      node_0->style.dimensions[CSS_HEIGHT] = 601;
      node_0->style.margin[CSS_LEFT] = 17;
      node_0->style.margin[CSS_TOP] = 17;
      node_0->style.margin[CSS_RIGHT] = 17;
      node_0->style.margin[CSS_BOTTOM] = 17;
      node_0->style.border[CSS_LEFT] = 0;
      node_0->style.border[CSS_BOTTOM] = 2;
      node_0->style.position[CSS_LEFT] = 9;
      node_0->style.position[CSS_TOP] = -6;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 11;
      node_0->layout.position[CSS_LEFT] = 26;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 601;
    }

    test("Random #12", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #13", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 171;
      node_0->layout.dimensions[CSS_HEIGHT] = 18;
    }

    test("Random #14", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node_0->style.align_items = CSS_ALIGN_STRETCH;
      node_0->style.dimensions[CSS_WIDTH] = 551;
      node_0->style.margin[CSS_LEFT] = -9;
      node_0->style.margin[CSS_TOP] = -9;
      node_0->style.margin[CSS_RIGHT] = -9;
      node_0->style.margin[CSS_BOTTOM] = -9;
      node_0->style.margin[CSS_TOP] = 12;
      node_0->style.border[CSS_TOP] = 1;
      node_0->style.position[CSS_LEFT] = 8;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 12;
      node_0->layout.position[CSS_LEFT] = -1;
      node_0->layout.dimensions[CSS_WIDTH] = 551;
      node_0->layout.dimensions[CSS_HEIGHT] = 19;
    }

    test("Random #15", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #16", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #17", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.justify_content = CSS_JUSTIFY_CENTER;
      node_0->style.align_items = CSS_ALIGN_FLEX_START;
      node_0->style.dimensions[CSS_WIDTH] = 924;
      node_0->style.margin[CSS_LEFT] = -7;
      node_0->style.margin[CSS_TOP] = -7;
      node_0->style.margin[CSS_RIGHT] = -7;
      node_0->style.margin[CSS_BOTTOM] = -7;
      node_0->style.padding[CSS_TOP] = 8;
      node_0->style.border[CSS_TOP] = 2;
      node_0->style.border[CSS_RIGHT] = 3;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -7;
      node_0->layout.position[CSS_LEFT] = -7;
      node_0->layout.dimensions[CSS_WIDTH] = 924;
      node_0->layout.dimensions[CSS_HEIGHT] = 28;
    }

    test("Random #18", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node_0->style.margin[CSS_LEFT] = 2;
      node_0->style.margin[CSS_TOP] = 2;
      node_0->style.margin[CSS_RIGHT] = 2;
      node_0->style.margin[CSS_BOTTOM] = 2;
      node_0->style.margin[CSS_TOP] = 10;
      node_0->style.margin[CSS_RIGHT] = 8;
      node_0->style.padding[CSS_RIGHT] = 18;
      node_0->style.border[CSS_TOP] = 0;
      node_0->style.border[CSS_BOTTOM] = 3;
      node_0->style.position[CSS_LEFT] = -9;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
        node_1->style.justify_content = CSS_JUSTIFY_FLEX_START;
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.margin[CSS_LEFT] = 8;
        node_1->style.margin[CSS_TOP] = 8;
        node_1->style.margin[CSS_RIGHT] = 8;
        node_1->style.margin[CSS_BOTTOM] = 8;
        node_1->style.margin[CSS_TOP] = 2;
        node_1->style.margin[CSS_BOTTOM] = 17;
        node_1->style.padding[CSS_LEFT] = 11;
        node_1->style.padding[CSS_TOP] = 11;
        node_1->style.padding[CSS_RIGHT] = 11;
        node_1->style.padding[CSS_BOTTOM] = 11;
        node_1->style.padding[CSS_BOTTOM] = 2;
        node_1->style.border[CSS_TOP] = 2;
        node_1->style.position[CSS_LEFT] = 0;
        node_1->style.position[CSS_TOP] = 2;
        node_1->style.measure = measure;
        node_1->style.measure_context = "small";
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 10;
      node_0->layout.position[CSS_LEFT] = -7;
      node_0->layout.dimensions[CSS_WIDTH] = 18;
      node_0->layout.dimensions[CSS_HEIGHT] = 3;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 4;
        node_1->layout.position[CSS_LEFT] = 8;
        node_1->layout.dimensions[CSS_WIDTH] = 55;
        node_1->layout.dimensions[CSS_HEIGHT] = 33;
      }
    }

    test("Random #19", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.margin[CSS_LEFT] = 6;
      node_0->style.margin[CSS_TOP] = -10;
      node_0->style.margin[CSS_RIGHT] = 11;
      node_0->style.padding[CSS_LEFT] = 16;
      node_0->style.padding[CSS_TOP] = 16;
      node_0->style.padding[CSS_RIGHT] = 16;
      node_0->style.padding[CSS_BOTTOM] = 16;
      node_0->style.padding[CSS_TOP] = 13;
      node_0->style.border[CSS_LEFT] = 1;
      node_0->style.border[CSS_TOP] = 1;
      node_0->style.border[CSS_RIGHT] = 1;
      node_0->style.border[CSS_BOTTOM] = 1;
      node_0->style.position[CSS_LEFT] = -10;
      node_0->style.position[CSS_TOP] = 5;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -5;
      node_0->layout.position[CSS_LEFT] = -4;
      node_0->layout.dimensions[CSS_WIDTH] = 67;
      node_0->layout.dimensions[CSS_HEIGHT] = 49;
    }

    test("Random #20", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
      node_0->style.dimensions[CSS_WIDTH] = 34;
      node_0->style.dimensions[CSS_HEIGHT] = 324;
      node_0->style.margin[CSS_LEFT] = 15;
      node_0->style.margin[CSS_TOP] = 15;
      node_0->style.margin[CSS_RIGHT] = 15;
      node_0->style.margin[CSS_BOTTOM] = 15;
      node_0->style.margin[CSS_TOP] = 14;
      node_0->style.margin[CSS_RIGHT] = 13;
      node_0->style.margin[CSS_BOTTOM] = -10;
      node_0->style.border[CSS_LEFT] = 3;
      node_0->style.border[CSS_BOTTOM] = 3;
      node_0->style.position[CSS_LEFT] = 2;
      node_0->style.position[CSS_TOP] = -7;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 7;
      node_0->layout.position[CSS_LEFT] = 17;
      node_0->layout.dimensions[CSS_WIDTH] = 34;
      node_0->layout.dimensions[CSS_HEIGHT] = 324;
    }

    test("Random #21", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node_0->style.dimensions[CSS_WIDTH] = 943;
      node_0->style.dimensions[CSS_HEIGHT] = 497;
      node_0->style.margin[CSS_LEFT] = 7;
      node_0->style.margin[CSS_TOP] = -8;
      node_0->style.margin[CSS_BOTTOM] = 7;
      node_0->style.border[CSS_LEFT] = 3;
      node_0->style.position[CSS_LEFT] = -5;
      node_0->style.position[CSS_TOP] = -1;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -9;
      node_0->layout.position[CSS_LEFT] = 2;
      node_0->layout.dimensions[CSS_WIDTH] = 943;
      node_0->layout.dimensions[CSS_HEIGHT] = 497;
    }

    test("Random #22", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 373;
      node_0->style.dimensions[CSS_HEIGHT] = 999;
      node_0->style.margin[CSS_LEFT] = -10;
      node_0->style.margin[CSS_TOP] = -10;
      node_0->style.margin[CSS_RIGHT] = -10;
      node_0->style.margin[CSS_BOTTOM] = -10;
      node_0->style.margin[CSS_TOP] = 13;
      node_0->style.margin[CSS_RIGHT] = 11;
      node_0->style.padding[CSS_LEFT] = 4;
      node_0->style.position[CSS_TOP] = 5;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 18;
      node_0->layout.position[CSS_LEFT] = -10;
      node_0->layout.dimensions[CSS_WIDTH] = 373;
      node_0->layout.dimensions[CSS_HEIGHT] = 999;
    }

    test("Random #23", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
      node_0->style.margin[CSS_LEFT] = -3;
      node_0->style.margin[CSS_TOP] = -3;
      node_0->style.margin[CSS_RIGHT] = -3;
      node_0->style.margin[CSS_BOTTOM] = -3;
      node_0->style.margin[CSS_LEFT] = 17;
      node_0->style.margin[CSS_TOP] = 19;
      node_0->style.padding[CSS_LEFT] = 9;
      node_0->style.padding[CSS_TOP] = 9;
      node_0->style.padding[CSS_RIGHT] = 9;
      node_0->style.padding[CSS_BOTTOM] = 9;
      node_0->style.padding[CSS_TOP] = 15;
      node_0->style.border[CSS_LEFT] = 2;
      node_0->style.position[CSS_LEFT] = 5;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 19;
      node_0->layout.position[CSS_LEFT] = 22;
      node_0->layout.dimensions[CSS_WIDTH] = 20;
      node_0->layout.dimensions[CSS_HEIGHT] = 24;
    }

    test("Random #24", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_FLEX_START;
      node_0->style.padding[CSS_LEFT] = 6;
      node_0->style.padding[CSS_TOP] = 8;
      node_0->style.padding[CSS_RIGHT] = 6;
      node_0->style.border[CSS_RIGHT] = 3;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 48;
      node_0->layout.dimensions[CSS_HEIGHT] = 26;
    }

    test("Random #25", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 171;
      node_0->layout.dimensions[CSS_HEIGHT] = 18;
    }

    test("Random #26", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node_0->style.align_items = CSS_ALIGN_CENTER;
      node_0->style.dimensions[CSS_WIDTH] = 786;
      node_0->style.dimensions[CSS_HEIGHT] = 710;
      node_0->style.margin[CSS_LEFT] = -9;
      node_0->style.margin[CSS_TOP] = -9;
      node_0->style.margin[CSS_RIGHT] = -9;
      node_0->style.margin[CSS_BOTTOM] = -9;
      node_0->style.margin[CSS_LEFT] = 15;
      node_0->style.margin[CSS_RIGHT] = 0;
      node_0->style.margin[CSS_BOTTOM] = 16;
      node_0->style.padding[CSS_TOP] = 16;
      node_0->style.border[CSS_RIGHT] = 0;
      node_0->style.border[CSS_BOTTOM] = 0;
      node_0->style.position[CSS_LEFT] = 4;
      node_0->style.position[CSS_TOP] = -3;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -12;
      node_0->layout.position[CSS_LEFT] = 19;
      node_0->layout.dimensions[CSS_WIDTH] = 786;
      node_0->layout.dimensions[CSS_HEIGHT] = 710;
    }

    test("Random #27", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_START;
      node_0->style.align_items = CSS_ALIGN_STRETCH;
      node_0->style.dimensions[CSS_WIDTH] = 260;
      node_0->style.dimensions[CSS_HEIGHT] = 929;
      node_0->style.margin[CSS_TOP] = -7;
      node_0->style.margin[CSS_RIGHT] = -2;
      node_0->style.margin[CSS_BOTTOM] = 12;
      node_0->style.padding[CSS_LEFT] = 13;
      node_0->style.padding[CSS_RIGHT] = 9;
      node_0->style.padding[CSS_BOTTOM] = 15;
      node_0->style.border[CSS_RIGHT] = 1;
      node_0->style.position[CSS_LEFT] = 3;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -7;
      node_0->layout.position[CSS_LEFT] = 3;
      node_0->layout.dimensions[CSS_WIDTH] = 260;
      node_0->layout.dimensions[CSS_HEIGHT] = 929;
    }

    test("Random #28", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #29", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node_0->style.margin[CSS_LEFT] = 4;
      node_0->style.margin[CSS_TOP] = 4;
      node_0->style.margin[CSS_RIGHT] = 4;
      node_0->style.margin[CSS_BOTTOM] = 4;
      node_0->style.margin[CSS_RIGHT] = 5;
      node_0->style.margin[CSS_BOTTOM] = -8;
      node_0->style.padding[CSS_LEFT] = 4;
      node_0->style.padding[CSS_TOP] = 4;
      node_0->style.padding[CSS_RIGHT] = 4;
      node_0->style.padding[CSS_BOTTOM] = 4;
      node_0->style.padding[CSS_TOP] = 9;
      node_0->style.padding[CSS_RIGHT] = 11;
      node_0->style.border[CSS_LEFT] = 0;
      node_0->style.border[CSS_TOP] = 0;
      node_0->style.border[CSS_RIGHT] = 0;
      node_0->style.border[CSS_BOTTOM] = 0;
      node_0->style.border[CSS_RIGHT] = 0;
      node_0->style.position[CSS_TOP] = 9;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 13;
      node_0->layout.position[CSS_LEFT] = 4;
      node_0->layout.dimensions[CSS_WIDTH] = 15;
      node_0->layout.dimensions[CSS_HEIGHT] = 13;
    }

    test("Random #30", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #31", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 171;
      node_0->layout.dimensions[CSS_HEIGHT] = 18;
    }

    test("Random #32", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #33", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_CENTER;
      node_0->style.dimensions[CSS_WIDTH] = 498;
      node_0->style.dimensions[CSS_HEIGHT] = 478;
      node_0->style.margin[CSS_LEFT] = -3;
      node_0->style.margin[CSS_TOP] = -3;
      node_0->style.margin[CSS_RIGHT] = -3;
      node_0->style.margin[CSS_BOTTOM] = -3;
      node_0->style.margin[CSS_TOP] = 6;
      node_0->style.padding[CSS_RIGHT] = 13;
      node_0->style.padding[CSS_BOTTOM] = 12;
      node_0->style.border[CSS_RIGHT] = 2;
      node_0->style.position[CSS_LEFT] = 8;
      node_0->style.position[CSS_TOP] = -5;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 1;
      node_0->layout.position[CSS_LEFT] = 5;
      node_0->layout.dimensions[CSS_WIDTH] = 498;
      node_0->layout.dimensions[CSS_HEIGHT] = 478;
    }

    test("Random #34", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node_0->style.align_items = CSS_ALIGN_CENTER;
      node_0->style.dimensions[CSS_WIDTH] = 954;
      node_0->style.dimensions[CSS_HEIGHT] = 847;
      node_0->style.margin[CSS_RIGHT] = 11;
      node_0->style.border[CSS_LEFT] = 0;
      node_0->style.border[CSS_TOP] = 0;
      node_0->style.border[CSS_RIGHT] = 0;
      node_0->style.border[CSS_BOTTOM] = 0;
      node_0->style.border[CSS_TOP] = 1;
      node_0->style.border[CSS_RIGHT] = 2;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 954;
      node_0->layout.dimensions[CSS_HEIGHT] = 847;
    }

    test("Random #35", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.align_items = CSS_ALIGN_CENTER;
      node_0->style.dimensions[CSS_HEIGHT] = 184;
      node_0->style.margin[CSS_LEFT] = 9;
      node_0->style.margin[CSS_TOP] = 9;
      node_0->style.margin[CSS_RIGHT] = 9;
      node_0->style.margin[CSS_BOTTOM] = 9;
      node_0->style.padding[CSS_LEFT] = 9;
      node_0->style.padding[CSS_TOP] = 9;
      node_0->style.padding[CSS_RIGHT] = 9;
      node_0->style.padding[CSS_BOTTOM] = 9;
      node_0->style.padding[CSS_LEFT] = 15;
      node_0->style.padding[CSS_TOP] = 6;
      node_0->style.border[CSS_BOTTOM] = 1;
      node_0->style.position[CSS_LEFT] = 3;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 9;
      node_0->layout.position[CSS_LEFT] = 12;
      node_0->layout.dimensions[CSS_WIDTH] = 24;
      node_0->layout.dimensions[CSS_HEIGHT] = 184;
    }

    test("Random #36", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 171;
      node_0->layout.dimensions[CSS_HEIGHT] = 18;
    }

    test("Random #37", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
      node_0->style.align_items = CSS_ALIGN_STRETCH;
      node_0->style.dimensions[CSS_WIDTH] = 30;
      node_0->style.dimensions[CSS_HEIGHT] = 20;
      node_0->style.margin[CSS_LEFT] = 10;
      node_0->style.margin[CSS_RIGHT] = -4;
      node_0->style.margin[CSS_BOTTOM] = 18;
      node_0->style.padding[CSS_TOP] = 8;
      node_0->style.padding[CSS_RIGHT] = 8;
      node_0->style.padding[CSS_BOTTOM] = 11;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
        node_1->style.justify_content = CSS_JUSTIFY_FLEX_START;
        node_1->style.align_items = CSS_ALIGN_FLEX_START;
        node_1->style.flex = CSS_FLEX_NONE;
        node_1->style.margin[CSS_LEFT] = -4;
        node_1->style.margin[CSS_TOP] = -4;
        node_1->style.margin[CSS_RIGHT] = -4;
        node_1->style.margin[CSS_BOTTOM] = -4;
        node_1->style.margin[CSS_TOP] = 9;
        node_1->style.margin[CSS_RIGHT] = 6;
        node_1->style.margin[CSS_BOTTOM] = 17;
        node_1->style.padding[CSS_LEFT] = 5;
        node_1->style.padding[CSS_BOTTOM] = 8;
        node_1->style.measure = measure;
        node_1->style.measure_context = "small";
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 10;
      node_0->layout.dimensions[CSS_WIDTH] = 30;
      node_0->layout.dimensions[CSS_HEIGHT] = 20;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 17;
        node_1->layout.position[CSS_LEFT] = -4;
        node_1->layout.dimensions[CSS_WIDTH] = 20;
        node_1->layout.dimensions[CSS_HEIGHT] = 26;
      }
    }

    test("Random #38", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #39", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #40", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
      node_0->style.align_items = CSS_ALIGN_FLEX_START;
      node_0->style.dimensions[CSS_HEIGHT] = 502;
      node_0->style.margin[CSS_LEFT] = 15;
      node_0->style.margin[CSS_TOP] = 15;
      node_0->style.margin[CSS_RIGHT] = 15;
      node_0->style.margin[CSS_BOTTOM] = 15;
      node_0->style.margin[CSS_LEFT] = -2;
      node_0->style.margin[CSS_TOP] = 19;
      node_0->style.margin[CSS_RIGHT] = 1;
      node_0->style.margin[CSS_BOTTOM] = 1;
      node_0->style.padding[CSS_TOP] = 5;
      node_0->style.border[CSS_LEFT] = 1;
      node_0->style.border[CSS_TOP] = 1;
      node_0->style.border[CSS_RIGHT] = 1;
      node_0->style.border[CSS_BOTTOM] = 1;
      node_0->style.position[CSS_LEFT] = 4;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 19;
      node_0->layout.position[CSS_LEFT] = 2;
      node_0->layout.dimensions[CSS_WIDTH] = 35;
      node_0->layout.dimensions[CSS_HEIGHT] = 502;
    }

    test("Random #41", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #42", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.margin[CSS_TOP] = 19;
      node_0->style.margin[CSS_RIGHT] = 14;
      node_0->style.margin[CSS_BOTTOM] = -8;
      node_0->style.padding[CSS_TOP] = 1;
      node_0->style.border[CSS_LEFT] = 3;
      node_0->style.border[CSS_TOP] = 0;
      node_0->style.border[CSS_RIGHT] = 3;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 19;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 177;
      node_0->layout.dimensions[CSS_HEIGHT] = 19;
    }

    test("Random #43", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node_0->style.align_items = CSS_ALIGN_FLEX_END;
      node_0->style.dimensions[CSS_WIDTH] = 146;
      node_0->style.dimensions[CSS_HEIGHT] = 190;
      node_0->style.margin[CSS_LEFT] = 11;
      node_0->style.margin[CSS_TOP] = 11;
      node_0->style.margin[CSS_RIGHT] = 11;
      node_0->style.margin[CSS_BOTTOM] = 11;
      node_0->style.margin[CSS_BOTTOM] = 15;
      node_0->style.padding[CSS_RIGHT] = 6;
      node_0->style.border[CSS_RIGHT] = 2;
      node_0->style.position[CSS_TOP] = 3;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 14;
      node_0->layout.position[CSS_LEFT] = 11;
      node_0->layout.dimensions[CSS_WIDTH] = 146;
      node_0->layout.dimensions[CSS_HEIGHT] = 190;
    }

    test("Random #44", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
      node_0->style.justify_content = CSS_JUSTIFY_CENTER;
      node_0->style.dimensions[CSS_WIDTH] = 882;
      node_0->style.margin[CSS_LEFT] = -7;
      node_0->style.margin[CSS_TOP] = -7;
      node_0->style.margin[CSS_RIGHT] = -7;
      node_0->style.margin[CSS_BOTTOM] = -7;
      node_0->style.margin[CSS_RIGHT] = 19;
      node_0->style.padding[CSS_LEFT] = 0;
      node_0->style.padding[CSS_TOP] = 0;
      node_0->style.padding[CSS_RIGHT] = 0;
      node_0->style.padding[CSS_BOTTOM] = 0;
      node_0->style.padding[CSS_LEFT] = 18;
      node_0->style.padding[CSS_RIGHT] = 2;
      node_0->style.border[CSS_RIGHT] = 3;
      node_0->style.position[CSS_LEFT] = -3;
      node_0->style.position[CSS_TOP] = -3;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.align_self = CSS_ALIGN_CENTER;
        node_1->style.flex = CSS_FLEX_ONE;
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.margin[CSS_LEFT] = 4;
        node_1->style.margin[CSS_TOP] = 4;
        node_1->style.margin[CSS_RIGHT] = 4;
        node_1->style.margin[CSS_BOTTOM] = 4;
        node_1->style.margin[CSS_LEFT] = 7;
        node_1->style.margin[CSS_RIGHT] = 12;
        node_1->style.padding[CSS_LEFT] = 8;
        node_1->style.padding[CSS_TOP] = 6;
        node_1->style.border[CSS_TOP] = 0;
        node_1->style.border[CSS_RIGHT] = 1;
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -10;
      node_0->layout.position[CSS_LEFT] = -10;
      node_0->layout.dimensions[CSS_WIDTH] = 882;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 4;
        node_1->layout.position[CSS_LEFT] = 25;
        node_1->layout.dimensions[CSS_WIDTH] = 9;
        node_1->layout.dimensions[CSS_HEIGHT] = 6;
      }
    }

    test("Random #45", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #46", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 171;
      node_0->layout.dimensions[CSS_HEIGHT] = 18;
    }

    test("Random #47", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #48", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #49", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #50", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
      node_0->style.dimensions[CSS_WIDTH] = 646;
      node_0->style.dimensions[CSS_HEIGHT] = 615;
      node_0->style.margin[CSS_LEFT] = -8;
      node_0->style.margin[CSS_TOP] = -8;
      node_0->style.margin[CSS_RIGHT] = -8;
      node_0->style.margin[CSS_BOTTOM] = -8;
      node_0->style.margin[CSS_LEFT] = 13;
      node_0->style.margin[CSS_RIGHT] = -6;
      node_0->style.border[CSS_LEFT] = 1;
      node_0->style.border[CSS_TOP] = 1;
      node_0->style.border[CSS_RIGHT] = 1;
      node_0->style.border[CSS_BOTTOM] = 1;
      node_0->style.border[CSS_LEFT] = 3;
      node_0->style.border[CSS_TOP] = 3;
      node_0->style.border[CSS_BOTTOM] = 1;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
        node_1->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
        node_1->style.flex = CSS_FLEX_NONE;
        node_1->style.position_type = CSS_POSITION_RELATIVE;
        node_1->style.dimensions[CSS_HEIGHT] = 200;
        node_1->style.margin[CSS_TOP] = 4;
        node_1->style.margin[CSS_RIGHT] = 9;
        node_1->style.margin[CSS_BOTTOM] = 3;
        node_1->style.padding[CSS_BOTTOM] = 19;
        node_1->style.border[CSS_LEFT] = 2;
        node_1->style.border[CSS_TOP] = 2;
        node_1->style.border[CSS_RIGHT] = 2;
        node_1->style.border[CSS_BOTTOM] = 2;
        node_1->style.border[CSS_TOP] = 1;
        node_1->style.border[CSS_RIGHT] = 2;
        node_1->style.measure = measure;
        node_1->style.measure_context = "small";
        node_1 = &node_0->children[1];
        node_1->style.justify_content = CSS_JUSTIFY_FLEX_END;
        node_1->style.align_items = CSS_ALIGN_CENTER;
        node_1->style.position_type = CSS_POSITION_RELATIVE;
        node_1->style.dimensions[CSS_HEIGHT] = 836;
        node_1->style.margin[CSS_LEFT] = -2;
        node_1->style.margin[CSS_TOP] = -2;
        node_1->style.margin[CSS_RIGHT] = -2;
        node_1->style.margin[CSS_BOTTOM] = -2;
        node_1->style.margin[CSS_TOP] = -2;
        node_1->style.margin[CSS_RIGHT] = 16;
        node_1->style.margin[CSS_BOTTOM] = -1;
        node_1->style.padding[CSS_LEFT] = 9;
        node_1->style.padding[CSS_TOP] = 9;
        node_1->style.padding[CSS_RIGHT] = 9;
        node_1->style.padding[CSS_BOTTOM] = 9;
        node_1->style.padding[CSS_RIGHT] = 15;
        node_1->style.border[CSS_LEFT] = 2;
        node_1->style.border[CSS_TOP] = 2;
        node_1->style.border[CSS_RIGHT] = 2;
        node_1->style.border[CSS_BOTTOM] = 2;
        node_1->style.border[CSS_TOP] = 2;
        node_1->style.position[CSS_TOP] = -8;
        node_1->style.measure = measure;
        node_1->style.measure_context = "small";
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -8;
      node_0->layout.position[CSS_LEFT] = 13;
      node_0->layout.dimensions[CSS_WIDTH] = 646;
      node_0->layout.dimensions[CSS_HEIGHT] = 615;
      init_css_node_children(node_0, 2);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 7;
        node_1->layout.position[CSS_LEFT] = 3;
        node_1->layout.dimensions[CSS_WIDTH] = 37;
        node_1->layout.dimensions[CSS_HEIGHT] = 200;
        node_1 = &node_0->children[1];
        node_1->layout.position[CSS_TOP] = 200;
        node_1->layout.position[CSS_LEFT] = 1;
        node_1->layout.dimensions[CSS_WIDTH] = 61;
        node_1->layout.dimensions[CSS_HEIGHT] = 836;
      }
    }

    test("Random #51", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #52", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #53", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 171;
      node_0->layout.dimensions[CSS_HEIGHT] = 18;
    }

    test("Random #54", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_START;
      node_0->style.margin[CSS_LEFT] = 3;
      node_0->style.margin[CSS_TOP] = 3;
      node_0->style.margin[CSS_RIGHT] = 3;
      node_0->style.margin[CSS_BOTTOM] = 3;
      node_0->style.margin[CSS_LEFT] = -9;
      node_0->style.margin[CSS_RIGHT] = -3;
      node_0->style.padding[CSS_RIGHT] = 0;
      node_0->style.border[CSS_RIGHT] = 3;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 3;
      node_0->layout.position[CSS_LEFT] = -9;
      node_0->layout.dimensions[CSS_WIDTH] = 36;
      node_0->layout.dimensions[CSS_HEIGHT] = 18;
    }

    test("Random #55", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_WIDTH] = 800;
      node_0->style.dimensions[CSS_HEIGHT] = 878;
      node_0->style.margin[CSS_LEFT] = -10;
      node_0->style.margin[CSS_TOP] = -10;
      node_0->style.margin[CSS_RIGHT] = -10;
      node_0->style.margin[CSS_BOTTOM] = -10;
      node_0->style.margin[CSS_RIGHT] = -4;
      node_0->style.padding[CSS_TOP] = 18;
      node_0->style.padding[CSS_BOTTOM] = 0;
      node_0->style.border[CSS_BOTTOM] = 0;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -10;
      node_0->layout.position[CSS_LEFT] = -10;
      node_0->layout.dimensions[CSS_WIDTH] = 800;
      node_0->layout.dimensions[CSS_HEIGHT] = 878;
    }

    test("Random #56", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #57", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_CENTER;
      node_0->style.align_items = CSS_ALIGN_FLEX_START;
      node_0->style.dimensions[CSS_WIDTH] = 693;
      node_0->style.margin[CSS_LEFT] = 6;
      node_0->style.margin[CSS_TOP] = 6;
      node_0->style.margin[CSS_RIGHT] = 6;
      node_0->style.margin[CSS_BOTTOM] = 6;
      node_0->style.margin[CSS_LEFT] = 13;
      node_0->style.margin[CSS_RIGHT] = 17;
      node_0->style.margin[CSS_BOTTOM] = -9;
      node_0->style.padding[CSS_LEFT] = 4;
      node_0->style.padding[CSS_TOP] = 4;
      node_0->style.padding[CSS_RIGHT] = 4;
      node_0->style.padding[CSS_BOTTOM] = 4;
      node_0->style.padding[CSS_RIGHT] = 14;
      node_0->style.border[CSS_RIGHT] = 3;
      node_0->style.border[CSS_BOTTOM] = 0;
      node_0->style.position[CSS_LEFT] = 4;
      node_0->style.position[CSS_TOP] = -1;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 5;
      node_0->layout.position[CSS_LEFT] = 17;
      node_0->layout.dimensions[CSS_WIDTH] = 693;
      node_0->layout.dimensions[CSS_HEIGHT] = 8;
    }

    test("Random #58", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node_0->style.margin[CSS_LEFT] = 8;
      node_0->style.margin[CSS_TOP] = -5;
      node_0->style.margin[CSS_RIGHT] = 13;
      node_0->style.margin[CSS_BOTTOM] = 18;
      node_0->style.padding[CSS_LEFT] = 3;
      node_0->style.padding[CSS_TOP] = 3;
      node_0->style.padding[CSS_RIGHT] = 3;
      node_0->style.padding[CSS_BOTTOM] = 3;
      node_0->style.padding[CSS_LEFT] = 11;
      node_0->style.padding[CSS_BOTTOM] = 7;
      node_0->style.border[CSS_BOTTOM] = 1;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -5;
      node_0->layout.position[CSS_LEFT] = 8;
      node_0->layout.dimensions[CSS_WIDTH] = 185;
      node_0->layout.dimensions[CSS_HEIGHT] = 29;
    }

    test("Random #59", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.margin[CSS_LEFT] = -7;
      node_0->style.margin[CSS_TOP] = -7;
      node_0->style.margin[CSS_RIGHT] = -7;
      node_0->style.margin[CSS_BOTTOM] = -7;
      node_0->style.margin[CSS_LEFT] = 11;
      node_0->style.margin[CSS_TOP] = -2;
      node_0->style.margin[CSS_RIGHT] = -3;
      node_0->style.margin[CSS_BOTTOM] = 11;
      node_0->style.padding[CSS_RIGHT] = 2;
      node_0->style.border[CSS_LEFT] = 3;
      node_0->style.border[CSS_TOP] = 3;
      node_0->style.border[CSS_RIGHT] = 3;
      node_0->style.border[CSS_BOTTOM] = 3;
      node_0->style.position[CSS_LEFT] = 1;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex = CSS_FLEX_NONE;
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.margin[CSS_LEFT] = 1;
        node_1->style.margin[CSS_TOP] = 15;
        node_1->style.margin[CSS_RIGHT] = 5;
        node_1->style.margin[CSS_BOTTOM] = 12;
        node_1->style.border[CSS_RIGHT] = 3;
        node_1->style.border[CSS_BOTTOM] = 3;
        node_1->style.position[CSS_LEFT] = 0;
        node_1->style.position[CSS_TOP] = -5;
        node_1->style.measure = measure;
        node_1->style.measure_context = "small";
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -2;
      node_0->layout.position[CSS_LEFT] = 12;
      node_0->layout.dimensions[CSS_WIDTH] = 8;
      node_0->layout.dimensions[CSS_HEIGHT] = 6;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 13;
        node_1->layout.position[CSS_LEFT] = 4;
        node_1->layout.dimensions[CSS_WIDTH] = 36;
        node_1->layout.dimensions[CSS_HEIGHT] = 21;
      }
    }

    test("Random #60", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node_0->style.align_items = CSS_ALIGN_STRETCH;
      node_0->style.dimensions[CSS_HEIGHT] = 165;
      node_0->style.margin[CSS_RIGHT] = 5;
      node_0->style.padding[CSS_LEFT] = 17;
      node_0->style.padding[CSS_TOP] = 9;
      node_0->style.padding[CSS_BOTTOM] = 6;
      node_0->style.border[CSS_LEFT] = 3;
      node_0->style.position[CSS_TOP] = 8;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 8;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 53;
      node_0->layout.dimensions[CSS_HEIGHT] = 165;
    }

    test("Random #61", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
      node_0->style.dimensions[CSS_HEIGHT] = 173;
      node_0->style.margin[CSS_LEFT] = 19;
      node_0->style.margin[CSS_TOP] = 19;
      node_0->style.margin[CSS_RIGHT] = 19;
      node_0->style.margin[CSS_BOTTOM] = 19;
      node_0->style.margin[CSS_TOP] = -5;
      node_0->style.padding[CSS_TOP] = 19;
      node_0->style.padding[CSS_RIGHT] = 10;
      node_0->style.padding[CSS_BOTTOM] = 7;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -5;
      node_0->layout.position[CSS_LEFT] = 19;
      node_0->layout.dimensions[CSS_WIDTH] = 10;
      node_0->layout.dimensions[CSS_HEIGHT] = 173;
    }

    test("Random #62", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_FLEX_END;
      node_0->style.dimensions[CSS_WIDTH] = 686;
      node_0->style.dimensions[CSS_HEIGHT] = 156;
      node_0->style.margin[CSS_LEFT] = -4;
      node_0->style.margin[CSS_RIGHT] = 16;
      node_0->style.margin[CSS_BOTTOM] = 9;
      node_0->style.padding[CSS_LEFT] = 19;
      node_0->style.padding[CSS_TOP] = 19;
      node_0->style.padding[CSS_RIGHT] = 19;
      node_0->style.padding[CSS_BOTTOM] = 19;
      node_0->style.padding[CSS_LEFT] = 9;
      node_0->style.position[CSS_LEFT] = -4;
      node_0->style.position[CSS_TOP] = 3;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 3;
      node_0->layout.position[CSS_LEFT] = -8;
      node_0->layout.dimensions[CSS_WIDTH] = 686;
      node_0->layout.dimensions[CSS_HEIGHT] = 156;
    }

    test("Random #63", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #64", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
      node_0->style.justify_content = CSS_JUSTIFY_CENTER;
      node_0->style.dimensions[CSS_WIDTH] = 655;
      node_0->style.dimensions[CSS_HEIGHT] = 360;
      node_0->style.margin[CSS_LEFT] = -8;
      node_0->style.margin[CSS_TOP] = -8;
      node_0->style.margin[CSS_RIGHT] = -8;
      node_0->style.margin[CSS_BOTTOM] = -8;
      node_0->style.margin[CSS_TOP] = 5;
      node_0->style.padding[CSS_TOP] = 19;
      node_0->style.padding[CSS_BOTTOM] = 10;
      node_0->style.border[CSS_LEFT] = 0;
      node_0->style.border[CSS_BOTTOM] = 2;
      node_0->style.position[CSS_LEFT] = 6;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 5;
      node_0->layout.position[CSS_LEFT] = -2;
      node_0->layout.dimensions[CSS_WIDTH] = 655;
      node_0->layout.dimensions[CSS_HEIGHT] = 360;
    }

    test("Random #65", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #66", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
      node_0->style.dimensions[CSS_HEIGHT] = 662;
      node_0->style.margin[CSS_RIGHT] = 12;
      node_0->style.margin[CSS_BOTTOM] = -9;
      node_0->style.padding[CSS_TOP] = 15;
      node_0->style.padding[CSS_RIGHT] = 8;
      node_0->style.position[CSS_LEFT] = 2;
      node_0->style.position[CSS_TOP] = -8;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -8;
      node_0->layout.position[CSS_LEFT] = 2;
      node_0->layout.dimensions[CSS_WIDTH] = 8;
      node_0->layout.dimensions[CSS_HEIGHT] = 662;
    }

    test("Random #67", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_STRETCH;
      node_0->style.margin[CSS_LEFT] = 0;
      node_0->style.margin[CSS_TOP] = 0;
      node_0->style.margin[CSS_RIGHT] = 0;
      node_0->style.margin[CSS_BOTTOM] = 0;
      node_0->style.margin[CSS_LEFT] = 7;
      node_0->style.padding[CSS_TOP] = 2;
      node_0->style.border[CSS_RIGHT] = 1;
      node_0->style.position[CSS_LEFT] = -10;
      node_0->style.position[CSS_TOP] = -8;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -8;
      node_0->layout.position[CSS_LEFT] = -3;
      node_0->layout.dimensions[CSS_WIDTH] = 172;
      node_0->layout.dimensions[CSS_HEIGHT] = 20;
    }

    test("Random #68", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #69", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #70", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.dimensions[CSS_WIDTH] = 615;
      node_0->style.margin[CSS_LEFT] = 1;
      node_0->style.margin[CSS_TOP] = 1;
      node_0->style.margin[CSS_RIGHT] = 1;
      node_0->style.margin[CSS_BOTTOM] = 1;
      node_0->style.margin[CSS_TOP] = 17;
      node_0->style.position[CSS_TOP] = 9;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
        node_1->style.align_self = CSS_ALIGN_CENTER;
        node_1->style.flex = CSS_FLEX_NONE;
        node_1->style.dimensions[CSS_WIDTH] = 457;
        node_1->style.dimensions[CSS_HEIGHT] = 476;
        node_1->style.margin[CSS_LEFT] = 4;
        node_1->style.margin[CSS_TOP] = 4;
        node_1->style.margin[CSS_RIGHT] = 4;
        node_1->style.margin[CSS_BOTTOM] = 4;
        node_1->style.margin[CSS_RIGHT] = 1;
        node_1->style.padding[CSS_LEFT] = 9;
        node_1->style.padding[CSS_TOP] = 9;
        node_1->style.padding[CSS_RIGHT] = 9;
        node_1->style.padding[CSS_BOTTOM] = 9;
        node_1->style.padding[CSS_TOP] = 6;
        node_1->style.position[CSS_LEFT] = 0;
        node_1->style.measure = measure;
        node_1->style.measure_context = "small";
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 26;
      node_0->layout.position[CSS_LEFT] = 1;
      node_0->layout.dimensions[CSS_WIDTH] = 615;
      node_0->layout.dimensions[CSS_HEIGHT] = 484;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 4;
        node_1->layout.position[CSS_LEFT] = 4;
        node_1->layout.dimensions[CSS_WIDTH] = 457;
        node_1->layout.dimensions[CSS_HEIGHT] = 476;
      }
    }

    test("Random #71", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node_0->style.dimensions[CSS_WIDTH] = 468;
      node_0->style.dimensions[CSS_HEIGHT] = 523;
      node_0->style.margin[CSS_TOP] = -2;
      node_0->style.padding[CSS_LEFT] = 11;
      node_0->style.padding[CSS_TOP] = 11;
      node_0->style.padding[CSS_RIGHT] = 11;
      node_0->style.padding[CSS_BOTTOM] = 11;
      node_0->style.padding[CSS_LEFT] = 11;
      node_0->style.position[CSS_TOP] = 8;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 6;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 468;
      node_0->layout.dimensions[CSS_HEIGHT] = 523;
    }

    test("Random #72", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #73", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #74", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node_0->style.dimensions[CSS_WIDTH] = 933;
      node_0->style.margin[CSS_LEFT] = 5;
      node_0->style.margin[CSS_TOP] = 5;
      node_0->style.margin[CSS_RIGHT] = 5;
      node_0->style.margin[CSS_BOTTOM] = 5;
      node_0->style.margin[CSS_TOP] = 1;
      node_0->style.margin[CSS_BOTTOM] = 3;
      node_0->style.border[CSS_BOTTOM] = 1;
      node_0->style.position[CSS_TOP] = 7;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 8;
      node_0->layout.position[CSS_LEFT] = 5;
      node_0->layout.dimensions[CSS_WIDTH] = 933;
      node_0->layout.dimensions[CSS_HEIGHT] = 19;
    }

    test("Random #75", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_FLEX_START;
      node_0->style.dimensions[CSS_HEIGHT] = 486;
      node_0->style.margin[CSS_LEFT] = 1;
      node_0->style.margin[CSS_TOP] = 1;
      node_0->style.margin[CSS_RIGHT] = 1;
      node_0->style.margin[CSS_BOTTOM] = 1;
      node_0->style.margin[CSS_LEFT] = 17;
      node_0->style.margin[CSS_TOP] = 7;
      node_0->style.padding[CSS_LEFT] = 12;
      node_0->style.padding[CSS_TOP] = 12;
      node_0->style.padding[CSS_RIGHT] = 12;
      node_0->style.padding[CSS_BOTTOM] = 12;
      node_0->style.border[CSS_BOTTOM] = 1;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 7;
      node_0->layout.position[CSS_LEFT] = 17;
      node_0->layout.dimensions[CSS_WIDTH] = 24;
      node_0->layout.dimensions[CSS_HEIGHT] = 486;
    }

    test("Random #76", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
      node_0->style.dimensions[CSS_WIDTH] = 828;
      node_0->style.margin[CSS_LEFT] = -4;
      node_0->style.margin[CSS_TOP] = -4;
      node_0->style.margin[CSS_RIGHT] = -4;
      node_0->style.margin[CSS_BOTTOM] = -4;
      node_0->style.margin[CSS_RIGHT] = -8;
      node_0->style.padding[CSS_LEFT] = 2;
      node_0->style.padding[CSS_TOP] = 2;
      node_0->style.padding[CSS_RIGHT] = 2;
      node_0->style.padding[CSS_BOTTOM] = 2;
      node_0->style.padding[CSS_RIGHT] = 15;
      node_0->style.padding[CSS_BOTTOM] = 5;
      node_0->style.border[CSS_LEFT] = 0;
      node_0->style.border[CSS_TOP] = 0;
      node_0->style.border[CSS_RIGHT] = 0;
      node_0->style.border[CSS_BOTTOM] = 0;
      node_0->style.border[CSS_BOTTOM] = 3;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -4;
      node_0->layout.position[CSS_LEFT] = -4;
      node_0->layout.dimensions[CSS_WIDTH] = 828;
      node_0->layout.dimensions[CSS_HEIGHT] = 10;
    }

    test("Random #77", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
      node_0->style.align_items = CSS_ALIGN_CENTER;
      node_0->style.dimensions[CSS_WIDTH] = 539;
      node_0->style.dimensions[CSS_HEIGHT] = 473;
      node_0->style.margin[CSS_LEFT] = -2;
      node_0->style.margin[CSS_TOP] = -2;
      node_0->style.margin[CSS_RIGHT] = -2;
      node_0->style.margin[CSS_BOTTOM] = -2;
      node_0->style.margin[CSS_BOTTOM] = -6;
      node_0->style.padding[CSS_LEFT] = 3;
      node_0->style.padding[CSS_TOP] = 3;
      node_0->style.padding[CSS_RIGHT] = 3;
      node_0->style.padding[CSS_BOTTOM] = 3;
      node_0->style.padding[CSS_BOTTOM] = 9;
      node_0->style.border[CSS_LEFT] = 1;
      node_0->style.border[CSS_RIGHT] = 2;
      node_0->style.position[CSS_LEFT] = 1;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -2;
      node_0->layout.position[CSS_LEFT] = -1;
      node_0->layout.dimensions[CSS_WIDTH] = 539;
      node_0->layout.dimensions[CSS_HEIGHT] = 473;
    }

    test("Random #78", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #79", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_START;
      node_0->style.dimensions[CSS_WIDTH] = 746;
      node_0->style.dimensions[CSS_HEIGHT] = 357;
      node_0->style.margin[CSS_LEFT] = -8;
      node_0->style.margin[CSS_TOP] = -8;
      node_0->style.margin[CSS_RIGHT] = -8;
      node_0->style.margin[CSS_BOTTOM] = -8;
      node_0->style.padding[CSS_LEFT] = 3;
      node_0->style.padding[CSS_TOP] = 3;
      node_0->style.padding[CSS_RIGHT] = 3;
      node_0->style.padding[CSS_BOTTOM] = 3;
      node_0->style.padding[CSS_LEFT] = 1;
      node_0->style.padding[CSS_BOTTOM] = 14;
      node_0->style.border[CSS_LEFT] = 2;
      node_0->style.border[CSS_TOP] = 2;
      node_0->style.border[CSS_RIGHT] = 2;
      node_0->style.border[CSS_BOTTOM] = 2;
      node_0->style.border[CSS_RIGHT] = 1;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -8;
      node_0->layout.position[CSS_LEFT] = -8;
      node_0->layout.dimensions[CSS_WIDTH] = 746;
      node_0->layout.dimensions[CSS_HEIGHT] = 357;
    }

    test("Random #80", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #81", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.align_items = CSS_ALIGN_FLEX_END;
      node_0->style.dimensions[CSS_HEIGHT] = 459;
      node_0->style.margin[CSS_TOP] = 5;
      node_0->style.margin[CSS_RIGHT] = -1;
      node_0->style.border[CSS_RIGHT] = 3;
      node_0->style.border[CSS_BOTTOM] = 1;
      node_0->style.position[CSS_LEFT] = -2;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 5;
      node_0->layout.position[CSS_LEFT] = -2;
      node_0->layout.dimensions[CSS_WIDTH] = 174;
      node_0->layout.dimensions[CSS_HEIGHT] = 459;
    }

    test("Random #82", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.align_items = CSS_ALIGN_STRETCH;
      node_0->style.dimensions[CSS_HEIGHT] = 175;
      node_0->style.margin[CSS_LEFT] = 15;
      node_0->style.margin[CSS_TOP] = 15;
      node_0->style.margin[CSS_RIGHT] = 15;
      node_0->style.margin[CSS_BOTTOM] = 15;
      node_0->style.margin[CSS_LEFT] = -5;
      node_0->style.margin[CSS_RIGHT] = 2;
      node_0->style.padding[CSS_TOP] = 5;
      node_0->style.padding[CSS_RIGHT] = 12;
      node_0->style.position[CSS_TOP] = 9;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 24;
      node_0->layout.position[CSS_LEFT] = -5;
      node_0->layout.dimensions[CSS_WIDTH] = 183;
      node_0->layout.dimensions[CSS_HEIGHT] = 175;
    }

    test("Random #83", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_STRETCH;
      node_0->style.dimensions[CSS_HEIGHT] = 0;
      node_0->style.padding[CSS_LEFT] = 11;
      node_0->style.padding[CSS_TOP] = 11;
      node_0->style.padding[CSS_RIGHT] = 11;
      node_0->style.padding[CSS_BOTTOM] = 11;
      node_0->style.padding[CSS_LEFT] = 8;
      node_0->style.padding[CSS_TOP] = 17;
      node_0->style.border[CSS_LEFT] = 3;
      node_0->style.border[CSS_TOP] = 3;
      node_0->style.border[CSS_RIGHT] = 1;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 23;
      node_0->layout.dimensions[CSS_HEIGHT] = 31;
    }

    test("Random #84", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
      node_0->style.align_items = CSS_ALIGN_STRETCH;
      node_0->style.dimensions[CSS_HEIGHT] = 466;
      node_0->style.margin[CSS_LEFT] = 12;
      node_0->style.margin[CSS_TOP] = -4;
      node_0->style.margin[CSS_BOTTOM] = 0;
      node_0->style.border[CSS_BOTTOM] = 1;
      node_0->style.position[CSS_LEFT] = 1;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -4;
      node_0->layout.position[CSS_LEFT] = 13;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 466;
    }

    test("Random #85", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_CENTER;
      node_0->style.margin[CSS_LEFT] = 18;
      node_0->style.margin[CSS_TOP] = -4;
      node_0->style.padding[CSS_RIGHT] = 19;
      node_0->style.position[CSS_LEFT] = -6;
      node_0->style.position[CSS_TOP] = -5;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -9;
      node_0->layout.position[CSS_LEFT] = 12;
      node_0->layout.dimensions[CSS_WIDTH] = 52;
      node_0->layout.dimensions[CSS_HEIGHT] = 18;
    }

    test("Random #86", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node_0->style.align_items = CSS_ALIGN_FLEX_START;
      node_0->style.margin[CSS_TOP] = 18;
      node_0->style.margin[CSS_RIGHT] = 5;
      node_0->style.padding[CSS_LEFT] = 5;
      node_0->style.padding[CSS_TOP] = 5;
      node_0->style.padding[CSS_RIGHT] = 5;
      node_0->style.padding[CSS_BOTTOM] = 5;
      node_0->style.padding[CSS_TOP] = 5;
      node_0->style.border[CSS_LEFT] = 2;
      node_0->style.border[CSS_TOP] = 2;
      node_0->style.border[CSS_RIGHT] = 2;
      node_0->style.border[CSS_BOTTOM] = 2;
      node_0->style.position[CSS_TOP] = 4;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->style.align_self = CSS_ALIGN_CENTER;
        node_1->style.flex = CSS_FLEX_ONE;
        node_1->style.position_type = CSS_POSITION_ABSOLUTE;
        node_1->style.margin[CSS_LEFT] = 9;
        node_1->style.margin[CSS_TOP] = 19;
        node_1->style.padding[CSS_LEFT] = 17;
        node_1->style.padding[CSS_TOP] = 17;
        node_1->style.padding[CSS_RIGHT] = 17;
        node_1->style.padding[CSS_BOTTOM] = 17;
        node_1->style.padding[CSS_LEFT] = 15;
        node_1->style.border[CSS_RIGHT] = 2;
        node_1->style.position[CSS_LEFT] = 7;
        node_1->style.measure = measure;
        node_1->style.measure_context = "loooooooooong with space";
      }
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 22;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 14;
      node_0->layout.dimensions[CSS_HEIGHT] = 14;
      init_css_node_children(node_0, 1);
      {
        css_node_t *node_1;
        node_1 = &node_0->children[0];
        node_1->layout.position[CSS_TOP] = 26;
        node_1->layout.position[CSS_LEFT] = 18;
        node_1->layout.dimensions[CSS_WIDTH] = 134;
        node_1->layout.dimensions[CSS_HEIGHT] = 70;
      }
    }

    test("Random #87", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.dimensions[CSS_HEIGHT] = 924;
      node_0->style.margin[CSS_LEFT] = 2;
      node_0->style.margin[CSS_TOP] = 5;
      node_0->style.margin[CSS_RIGHT] = -2;
      node_0->style.margin[CSS_BOTTOM] = -9;
      node_0->style.padding[CSS_LEFT] = 19;
      node_0->style.padding[CSS_TOP] = 19;
      node_0->style.padding[CSS_RIGHT] = 19;
      node_0->style.padding[CSS_BOTTOM] = 19;
      node_0->style.padding[CSS_TOP] = 10;
      node_0->style.padding[CSS_BOTTOM] = 5;
      node_0->style.position[CSS_TOP] = 4;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 9;
      node_0->layout.position[CSS_LEFT] = 2;
      node_0->layout.dimensions[CSS_WIDTH] = 209;
      node_0->layout.dimensions[CSS_HEIGHT] = 924;
    }

    test("Random #88", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_CENTER;
      node_0->style.margin[CSS_LEFT] = -9;
      node_0->style.margin[CSS_TOP] = -9;
      node_0->style.margin[CSS_RIGHT] = -9;
      node_0->style.margin[CSS_BOTTOM] = -9;
      node_0->style.margin[CSS_BOTTOM] = -3;
      node_0->style.padding[CSS_LEFT] = 4;
      node_0->style.padding[CSS_TOP] = 4;
      node_0->style.padding[CSS_RIGHT] = 4;
      node_0->style.padding[CSS_BOTTOM] = 4;
      node_0->style.padding[CSS_LEFT] = 12;
      node_0->style.border[CSS_LEFT] = 1;
      node_0->style.border[CSS_TOP] = 1;
      node_0->style.border[CSS_RIGHT] = 1;
      node_0->style.border[CSS_BOTTOM] = 1;
      node_0->style.position[CSS_LEFT] = -10;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -9;
      node_0->layout.position[CSS_LEFT] = -19;
      node_0->layout.dimensions[CSS_WIDTH] = 18;
      node_0->layout.dimensions[CSS_HEIGHT] = 10;
    }

    test("Random #89", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_END;
      node_0->style.align_items = CSS_ALIGN_FLEX_END;
      node_0->style.dimensions[CSS_HEIGHT] = 819;
      node_0->style.margin[CSS_LEFT] = 1;
      node_0->style.margin[CSS_TOP] = 1;
      node_0->style.margin[CSS_RIGHT] = 1;
      node_0->style.margin[CSS_BOTTOM] = 1;
      node_0->style.margin[CSS_TOP] = -3;
      node_0->style.margin[CSS_BOTTOM] = 5;
      node_0->style.padding[CSS_LEFT] = 18;
      node_0->style.border[CSS_LEFT] = 2;
      node_0->style.border[CSS_RIGHT] = 3;
      node_0->style.position[CSS_LEFT] = 5;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -3;
      node_0->layout.position[CSS_LEFT] = 6;
      node_0->layout.dimensions[CSS_WIDTH] = 23;
      node_0->layout.dimensions[CSS_HEIGHT] = 819;
    }

    test("Random #90", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node_0->style.dimensions[CSS_WIDTH] = 532;
      node_0->style.margin[CSS_LEFT] = 8;
      node_0->style.margin[CSS_TOP] = 8;
      node_0->style.margin[CSS_RIGHT] = 8;
      node_0->style.margin[CSS_BOTTOM] = 8;
      node_0->style.margin[CSS_LEFT] = 16;
      node_0->style.margin[CSS_BOTTOM] = 9;
      node_0->style.padding[CSS_LEFT] = 7;
      node_0->style.padding[CSS_TOP] = 7;
      node_0->style.padding[CSS_RIGHT] = 7;
      node_0->style.padding[CSS_BOTTOM] = 7;
      node_0->style.padding[CSS_LEFT] = 8;
      node_0->style.padding[CSS_TOP] = 5;
      node_0->style.position[CSS_LEFT] = 4;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 8;
      node_0->layout.position[CSS_LEFT] = 20;
      node_0->layout.dimensions[CSS_WIDTH] = 532;
      node_0->layout.dimensions[CSS_HEIGHT] = 30;
    }

    test("Random #91", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.margin[CSS_LEFT] = 13;
      node_0->style.padding[CSS_LEFT] = 0;
      node_0->style.padding[CSS_TOP] = 0;
      node_0->style.padding[CSS_RIGHT] = 0;
      node_0->style.padding[CSS_BOTTOM] = 0;
      node_0->style.border[CSS_RIGHT] = 1;
      node_0->style.border[CSS_BOTTOM] = 1;
      node_0->style.position[CSS_LEFT] = 8;
      node_0->style.position[CSS_TOP] = -9;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -9;
      node_0->layout.position[CSS_LEFT] = 21;
      node_0->layout.dimensions[CSS_WIDTH] = 1;
      node_0->layout.dimensions[CSS_HEIGHT] = 1;
    }

    test("Random #92", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node_0->style.align_items = CSS_ALIGN_FLEX_END;
      node_0->style.dimensions[CSS_HEIGHT] = 632;
      node_0->style.margin[CSS_LEFT] = 11;
      node_0->style.margin[CSS_TOP] = 11;
      node_0->style.margin[CSS_RIGHT] = 11;
      node_0->style.margin[CSS_BOTTOM] = 11;
      node_0->style.margin[CSS_TOP] = -3;
      node_0->style.margin[CSS_RIGHT] = 5;
      node_0->style.margin[CSS_BOTTOM] = -6;
      node_0->style.padding[CSS_LEFT] = 1;
      node_0->style.border[CSS_LEFT] = 0;
      node_0->style.border[CSS_TOP] = 0;
      node_0->style.border[CSS_RIGHT] = 0;
      node_0->style.border[CSS_BOTTOM] = 0;
      node_0->style.position[CSS_LEFT] = 4;
      node_0->style.position[CSS_TOP] = 8;
      node_0->style.measure = measure;
      node_0->style.measure_context = "small";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 5;
      node_0->layout.position[CSS_LEFT] = 15;
      node_0->layout.dimensions[CSS_WIDTH] = 34;
      node_0->layout.dimensions[CSS_HEIGHT] = 632;
    }

    test("Random #93", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.align_items = CSS_ALIGN_CENTER;
      node_0->style.dimensions[CSS_WIDTH] = 625;
      node_0->style.margin[CSS_LEFT] = 1;
      node_0->style.margin[CSS_TOP] = 1;
      node_0->style.margin[CSS_RIGHT] = 1;
      node_0->style.margin[CSS_BOTTOM] = 1;
      node_0->style.margin[CSS_LEFT] = -9;
      node_0->style.margin[CSS_TOP] = 11;
      node_0->style.margin[CSS_RIGHT] = 15;
      node_0->style.margin[CSS_BOTTOM] = 10;
      node_0->style.padding[CSS_LEFT] = 19;
      node_0->style.border[CSS_LEFT] = 3;
      node_0->style.border[CSS_TOP] = 3;
      node_0->style.border[CSS_RIGHT] = 3;
      node_0->style.border[CSS_BOTTOM] = 3;
      node_0->style.border[CSS_TOP] = 2;
      node_0->style.position[CSS_LEFT] = -10;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 11;
      node_0->layout.position[CSS_LEFT] = -19;
      node_0->layout.dimensions[CSS_WIDTH] = 625;
      node_0->layout.dimensions[CSS_HEIGHT] = 23;
    }

    test("Random #94", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 0;
      node_0->layout.dimensions[CSS_WIDTH] = 0;
      node_0->layout.dimensions[CSS_HEIGHT] = 0;
    }

    test("Random #95", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_COLUMN;
      node_0->style.dimensions[CSS_WIDTH] = 88;
      node_0->style.dimensions[CSS_HEIGHT] = 657;
      node_0->style.margin[CSS_LEFT] = 3;
      node_0->style.margin[CSS_RIGHT] = -2;
      node_0->style.padding[CSS_LEFT] = 4;
      node_0->style.padding[CSS_TOP] = 4;
      node_0->style.padding[CSS_RIGHT] = 4;
      node_0->style.padding[CSS_BOTTOM] = 4;
      node_0->style.padding[CSS_LEFT] = 5;
      node_0->style.padding[CSS_TOP] = 0;
      node_0->style.padding[CSS_BOTTOM] = 19;
      node_0->style.border[CSS_LEFT] = 1;
      node_0->style.border[CSS_TOP] = 1;
      node_0->style.border[CSS_RIGHT] = 1;
      node_0->style.border[CSS_BOTTOM] = 1;
      node_0->style.border[CSS_LEFT] = 3;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 0;
      node_0->layout.position[CSS_LEFT] = 3;
      node_0->layout.dimensions[CSS_WIDTH] = 88;
      node_0->layout.dimensions[CSS_HEIGHT] = 657;
    }

    test("Random #96", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_AROUND;
      node_0->style.margin[CSS_LEFT] = -9;
      node_0->style.margin[CSS_TOP] = -9;
      node_0->style.margin[CSS_RIGHT] = -9;
      node_0->style.margin[CSS_BOTTOM] = -9;
      node_0->style.margin[CSS_LEFT] = 18;
      node_0->style.margin[CSS_TOP] = 15;
      node_0->style.margin[CSS_BOTTOM] = 0;
      node_0->style.padding[CSS_LEFT] = 6;
      node_0->style.padding[CSS_TOP] = 6;
      node_0->style.padding[CSS_RIGHT] = 6;
      node_0->style.padding[CSS_BOTTOM] = 6;
      node_0->style.padding[CSS_TOP] = 17;
      node_0->style.padding[CSS_BOTTOM] = 3;
      node_0->style.border[CSS_LEFT] = 0;
      node_0->style.border[CSS_TOP] = 0;
      node_0->style.border[CSS_RIGHT] = 0;
      node_0->style.border[CSS_BOTTOM] = 0;
      node_0->style.border[CSS_RIGHT] = 2;
      node_0->style.border[CSS_BOTTOM] = 3;
      node_0->style.position[CSS_TOP] = -4;
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 11;
      node_0->layout.position[CSS_LEFT] = 18;
      node_0->layout.dimensions[CSS_WIDTH] = 14;
      node_0->layout.dimensions[CSS_HEIGHT] = 23;
    }

    test("Random #97", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.justify_content = CSS_JUSTIFY_FLEX_START;
      node_0->style.align_items = CSS_ALIGN_FLEX_END;
      node_0->style.dimensions[CSS_WIDTH] = 83;
      node_0->style.margin[CSS_LEFT] = -8;
      node_0->style.margin[CSS_RIGHT] = -1;
      node_0->style.position[CSS_TOP] = -3;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = -3;
      node_0->layout.position[CSS_LEFT] = -8;
      node_0->layout.dimensions[CSS_WIDTH] = 83;
      node_0->layout.dimensions[CSS_HEIGHT] = 36;
    }

    test("Random #98", root_node, root_layout);
  }

  {
    css_node_t *root_node = new_css_node();
    {
      css_node_t *node_0 = root_node;
      node_0->style.flex_direction = CSS_FLEX_DIRECTION_ROW;
      node_0->style.justify_content = CSS_JUSTIFY_SPACE_BETWEEN;
      node_0->style.align_items = CSS_ALIGN_CENTER;
      node_0->style.dimensions[CSS_WIDTH] = 240;
      node_0->style.margin[CSS_LEFT] = 6;
      node_0->style.margin[CSS_TOP] = 6;
      node_0->style.margin[CSS_RIGHT] = 6;
      node_0->style.margin[CSS_BOTTOM] = 6;
      node_0->style.margin[CSS_LEFT] = 13;
      node_0->style.margin[CSS_TOP] = 6;
      node_0->style.margin[CSS_RIGHT] = -5;
      node_0->style.margin[CSS_BOTTOM] = 8;
      node_0->style.padding[CSS_TOP] = 0;
      node_0->style.border[CSS_LEFT] = 2;
      node_0->style.border[CSS_BOTTOM] = 2;
      node_0->style.position[CSS_TOP] = 9;
      node_0->style.measure = measure;
      node_0->style.measure_context = "loooooooooong with space";
    }

    css_node_t *root_layout = new_css_node();
    {
      css_node_t *node_0 = root_layout;
      node_0->layout.position[CSS_TOP] = 15;
      node_0->layout.position[CSS_LEFT] = 13;
      node_0->layout.dimensions[CSS_WIDTH] = 240;
      node_0->layout.dimensions[CSS_HEIGHT] = 20;
    }

    test("Random #99", root_node, root_layout);
  }
}

