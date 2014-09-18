package com.facebook.csslayout;

import org.junit.Assert;
import org.junit.Test;

/**
 * Tests for {@link LayoutEngine}
 */
public class LayoutEngineTest {

  private static void test(String message, CSSNode style, CSSNode expectedLayout) {
    style.calculateLayout();
    assertLayoutsEqual(message, style, expectedLayout);
  }

  private static void addChildren(CSSNode node, int numChildren) {
    for (int i = 0; i < numChildren; i++) {
      node.addChildAt(new CSSNode(), i);
    }
  }

  private static void assertLayoutsEqual(String message, CSSNode actual, CSSNode expected) {
    Assert.assertTrue(
        message + "\nActual:\n" + actual.toString() + "\nExpected:\n" + expected.toString(),
        areLayoutsEqual(actual, expected));
  }

  private static boolean areLayoutsEqual(CSSNode a, CSSNode b) {
    boolean doNodesHaveSameLayout =
        areFloatsEqual(a.layout.x, b.layout.x) &&
        areFloatsEqual(a.layout.y, b.layout.y) &&
        areFloatsEqual(a.layout.width, b.layout.width) &&
        areFloatsEqual(a.layout.height, b.layout.height);
    if (!doNodesHaveSameLayout) {
      return false;
    }
    for (int i = 0; i < a.getChildCount(); i++) {
      if (!areLayoutsEqual(a.getChildAt(i), b.getChildAt(i))) {
        return false;
      }
    }
    return true;
  }

  private static boolean areFloatsEqual(float a, float b) {
    return Math.abs(a - b) < .00001f;
  }

  //
  // GENERATED TEST CODE GOES BELOW -- see transpile.html
  // (everything below this point is generated)
  //

  @Test
  public void testCase0()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 200;
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 200;
    }

    test("should layout a single node with width and height", root_node, root_layout);
  }

  @Test
  public void testCase1()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 3);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 500;
        node_1.style.height = 500;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 250;
        node_1.style.height = 250;
        node_1 = node_0.getChildAt(2);
        node_1.style.width = 125;
        node_1.style.height = 125;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 3);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 500;
        node_1.layout.x = 0;
        node_1.layout.width = 250;
        node_1.layout.height = 250;
        node_1 = node_0.getChildAt(2);
        node_1.layout.y = 750;
        node_1.layout.x = 0;
        node_1.layout.width = 125;
        node_1.layout.height = 125;
      }
    }

    test("should layout node with children", root_node, root_layout);
  }

  @Test
  public void testCase2()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 500;
        node_1.style.height = 500;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 500;
        node_1.style.height = 500;
        addChildren(node_1, 2);
        {
          CSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.width = 250;
          node_2.style.height = 250;
          node_2 = node_1.getChildAt(1);
          node_2.style.width = 250;
          node_2.style.height = 250;
        }
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 500;
        node_1.layout.x = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 500;
        addChildren(node_1, 2);
        {
          CSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 250;
          node_2.layout.height = 250;
          node_2 = node_1.getChildAt(1);
          node_2.layout.y = 250;
          node_2.layout.x = 0;
          node_2.layout.width = 250;
          node_2.layout.height = 250;
        }
      }
    }

    test("should layout node with nested children", root_node, root_layout);
  }

  @Test
  public void testCase3()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 200;
      node_0.style.marginLeft = 10;
      node_0.style.marginTop = 10;
      node_0.style.marginRight = 10;
      node_0.style.marginBottom = 10;
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 10;
      node_0.layout.x = 10;
      node_0.layout.width = 100;
      node_0.layout.height = 200;
    }

    test("should layout node with margin", root_node, root_layout);
  }

  @Test
  public void testCase4()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      node_0.style.marginLeft = 10;
      node_0.style.marginTop = 10;
      node_0.style.marginRight = 10;
      node_0.style.marginBottom = 10;
      addChildren(node_0, 3);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.style.marginLeft = 50;
        node_1.style.marginTop = 50;
        node_1.style.marginRight = 50;
        node_1.style.marginBottom = 50;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.style.marginLeft = 25;
        node_1.style.marginTop = 25;
        node_1.style.marginRight = 25;
        node_1.style.marginBottom = 25;
        node_1 = node_0.getChildAt(2);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.style.marginLeft = 10;
        node_1.style.marginTop = 10;
        node_1.style.marginRight = 10;
        node_1.style.marginBottom = 10;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 10;
      node_0.layout.x = 10;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 3);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 50;
        node_1.layout.x = 50;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 225;
        node_1.layout.x = 25;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(2);
        node_1.layout.y = 360;
        node_1.layout.x = 10;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with several children", root_node, root_layout);
  }

  @Test
  public void testCase5()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 300;
        node_1.style.height = 150;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 0;
        node_1.layout.x = 100;
        node_1.layout.width = 300;
        node_1.layout.height = 150;
      }
    }

    test("should layout node with row flex direction", root_node, root_layout);
  }

  @Test
  public void testCase6()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.width = 300;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 300;
        node_1.style.height = 150;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 350;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 200;
        node_1.layout.x = 0;
        node_1.layout.width = 300;
        node_1.layout.height = 150;
      }
    }

    test("should layout node based on children main dimensions", root_node, root_layout);
  }

  @Test
  public void testCase7()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.width = 100;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 200;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 800;
      }
    }

    test("should layout node with flex", root_node, root_layout);
  }

  @Test
  public void testCase8()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.width = 1000;
        addChildren(node_1, 1);
        {
          CSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.flex = 1;
          node_2.style.width = 1000;
          addChildren(node_2, 1);
          {
            CSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.style.flex = 1;
            node_3.style.width = 1000;
          }
        }
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 1000;
        node_1.layout.height = 1000;
        addChildren(node_1, 1);
        {
          CSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 1000;
          node_2.layout.height = 1000;
          addChildren(node_2, 1);
          {
            CSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.layout.y = 0;
            node_3.layout.x = 0;
            node_3.layout.width = 1000;
            node_3.layout.height = 1000;
          }
        }
      }
    }

    test("should layout node with flex recursively", root_node, root_layout);
  }

  @Test
  public void testCase9()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      node_0.style.marginLeft = 5;
      node_0.style.marginTop = 10;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.style.marginLeft = 15;
        node_1.style.marginTop = 50;
        node_1.style.marginBottom = 20;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.style.marginLeft = 30;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 10;
      node_0.layout.x = 5;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 50;
        node_1.layout.x = 15;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 170;
        node_1.layout.x = 30;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with targeted margin", root_node, root_layout);
  }

  @Test
  public void testCase10()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_START;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 100;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: flex-start", root_node, root_layout);
  }

  @Test
  public void testCase11()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_END;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 800;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 900;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: flex-end", root_node, root_layout);
  }

  @Test
  public void testCase12()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_BETWEEN;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 900;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: space-between", root_node, root_layout);
  }

  @Test
  public void testCase13()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_AROUND;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 200;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 700;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: space-around", root_node, root_layout);
  }

  @Test
  public void testCase14()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.CENTER;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 400;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 500;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: center", root_node, root_layout);
  }

  @Test
  public void testCase15()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 1000;
      }
    }

    test("should layout node with flex override height", root_node, root_layout);
  }

  @Test
  public void testCase16()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.FLEX_START;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 200;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 100;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignItems: flex-start", root_node, root_layout);
  }

  @Test
  public void testCase17()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.CENTER;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 200;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 400;
        node_1.layout.width = 200;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 100;
        node_1.layout.x = 450;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignItems: center", root_node, root_layout);
  }

  @Test
  public void testCase18()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.FLEX_END;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 200;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 800;
        node_1.layout.width = 200;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 100;
        node_1.layout.x = 900;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignItems: flex-end", root_node, root_layout);
  }

  @Test
  public void testCase19()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.FLEX_END;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 200;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.CENTER;
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 800;
        node_1.layout.width = 200;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 100;
        node_1.layout.x = 450;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignSelf overrides alignItems", root_node, root_layout);
  }

  @Test
  public void testCase20()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.STRETCH;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 100;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 1000;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignItem: stretch", root_node, root_layout);
  }

  @Test
  public void testCase21()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout empty node", root_node, root_layout);
  }

  @Test
  public void testCase22()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.marginLeft = 5;
        node_1.style.marginTop = 5;
        node_1.style.marginRight = 5;
        node_1.style.marginBottom = 5;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 5;
        node_1.layout.x = 5;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout child with margin", root_node, root_layout);
  }

  @Test
  public void testCase23()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.height = 100;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.height = 200;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 100;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 200;
      }
    }

    test("should not shrink children if not enough space", root_node, root_layout);
  }

  @Test
  public void testCase24()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.CENTER;
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("should layout for center", root_node, root_layout);
  }

  @Test
  public void testCase25()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_END;
      node_0.style.height = 100;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.marginTop = 10;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 100;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout flex-end taking into account margin", root_node, root_layout);
  }

  @Test
  public void testCase26()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignItems = CSSAlign.FLEX_END;
        addChildren(node_1, 2);
        {
          CSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.marginLeft = 10;
          node_2.style.marginTop = 10;
          node_2.style.marginRight = 10;
          node_2.style.marginBottom = 10;
          node_2 = node_1.getChildAt(1);
          node_2.style.height = 100;
        }
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 20;
      node_0.layout.height = 120;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 20;
        node_1.layout.height = 120;
        addChildren(node_1, 2);
        {
          CSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 10;
          node_2.layout.x = 10;
          node_2.layout.width = 0;
          node_2.layout.height = 0;
          node_2 = node_1.getChildAt(1);
          node_2.layout.y = 20;
          node_2.layout.x = 20;
          node_2.layout.width = 0;
          node_2.layout.height = 100;
        }
      }
    }

    test("should layout alignItems with margin", root_node, root_layout);
  }

  @Test
  public void testCase27()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout flex inside of an empty element", root_node, root_layout);
  }

  @Test
  public void testCase28()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.STRETCH;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.marginLeft = 10;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 10;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout alignItems stretch and margin", root_node, root_layout);
  }

  @Test
  public void testCase29()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.paddingLeft = 5;
      node_0.style.paddingTop = 5;
      node_0.style.paddingRight = 5;
      node_0.style.paddingBottom = 5;
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
    }

    test("should layout node with padding", root_node, root_layout);
  }

  @Test
  public void testCase30()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.paddingLeft = 5;
      node_0.style.paddingTop = 5;
      node_0.style.paddingRight = 5;
      node_0.style.paddingBottom = 5;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 5;
        node_1.layout.x = 5;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with padding and a child", root_node, root_layout);
  }

  @Test
  public void testCase31()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.paddingLeft = 5;
      node_0.style.paddingTop = 5;
      node_0.style.paddingRight = 5;
      node_0.style.paddingBottom = 5;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.marginLeft = 5;
        node_1.style.marginTop = 5;
        node_1.style.marginRight = 5;
        node_1.style.marginBottom = 5;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 20;
      node_0.layout.height = 20;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 10;
        node_1.layout.x = 10;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with padding and a child with margin", root_node, root_layout);
  }

  @Test
  public void testCase32()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        node_1.style.paddingLeft = 10;
        node_1.style.paddingTop = 10;
        node_1.style.paddingRight = 10;
        node_1.style.paddingBottom = 10;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 20;
      node_0.layout.height = 20;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 20;
        node_1.layout.height = 20;
      }
    }

    test("should layout node with padding and stretch", root_node, root_layout);
  }

  @Test
  public void testCase33()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.paddingLeft = 50;
      node_0.style.paddingTop = 50;
      node_0.style.paddingRight = 50;
      node_0.style.paddingBottom = 50;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        node_1.style.paddingLeft = 10;
        node_1.style.paddingTop = 10;
        node_1.style.paddingRight = 10;
        node_1.style.paddingBottom = 10;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 120;
      node_0.layout.height = 120;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 50;
        node_1.layout.x = 50;
        node_1.layout.width = 20;
        node_1.layout.height = 20;
      }
    }

    test("should layout node with inner & outer padding and stretch", root_node, root_layout);
  }

  @Test
  public void testCase34()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        addChildren(node_1, 1);
        {
          CSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.marginLeft = 16;
          node_2.style.marginTop = 16;
          node_2.style.marginRight = 16;
          node_2.style.marginBottom = 16;
        }
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 32;
      node_0.layout.height = 32;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 32;
        node_1.layout.height = 32;
        addChildren(node_1, 1);
        {
          CSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 16;
          node_2.layout.x = 16;
          node_2.layout.width = 0;
          node_2.layout.height = 0;
        }
      }
    }

    test("should layout node with stretch and child with margin", root_node, root_layout);
  }

  @Test
  public void testCase35()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.positionLeft = 5;
      node_0.style.positionTop = 5;
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 5;
      node_0.layout.x = 5;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("should layout node with top and left", root_node, root_layout);
  }

  @Test
  public void testCase36()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_AROUND;
      node_0.style.height = 10;
      node_0.style.paddingTop = 5;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 7.5f;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with height, padding and space-around", root_node, root_layout);
  }

  @Test
  public void testCase37()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.positionBottom = 5;
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = -5;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("should layout node with bottom", root_node, root_layout);
  }

  @Test
  public void testCase38()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.positionTop = 10;
      node_0.style.positionBottom = 5;
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 10;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("should layout node with both top and bottom", root_node, root_layout);
  }

  @Test
  public void testCase39()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 500;
      addChildren(node_0, 3);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.width = 50;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 500;
      node_0.layout.height = 0;
      addChildren(node_0, 3);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 250;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 0;
        node_1.layout.x = 250;
        node_1.layout.width = 50;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(2);
        node_1.layout.y = 0;
        node_1.layout.x = 250;
        node_1.layout.width = 250;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with position: absolute", root_node, root_layout);
  }

  @Test
  public void testCase40()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.marginRight = 15;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with child with position: absolute and margin", root_node, root_layout);
  }

  @Test
  public void testCase41()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.CENTER;
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.paddingRight = 12;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 12;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with position: absolute, padding and alignSelf: center", root_node, root_layout);
  }

  @Test
  public void testCase42()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.height = 5;
      node_0.style.paddingBottom = 20;
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 20;
    }

    test("should work with height smaller than paddingBottom", root_node, root_layout);
  }

  @Test
  public void testCase43()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.width = 5;
      node_0.style.paddingLeft = 20;
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 20;
      node_0.layout.height = 0;
    }

    test("should work with width smaller than paddingLeft", root_node, root_layout);
  }

  @Test
  public void testCase44()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        addChildren(node_1, 1);
        {
          CSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.width = 400;
        }
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        node_1.style.width = 200;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 400;
      node_0.layout.height = 0;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 400;
        node_1.layout.height = 0;
        addChildren(node_1, 1);
        {
          CSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 400;
          node_2.layout.height = 0;
        }
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with specified width and stretch", root_node, root_layout);
  }

  @Test
  public void testCase45()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.paddingLeft = 5;
      node_0.style.paddingTop = 5;
      node_0.style.paddingRight = 5;
      node_0.style.paddingBottom = 5;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 5;
        node_1.layout.x = 5;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with padding and child with position absolute", root_node, root_layout);
  }

  @Test
  public void testCase46()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionLeft = 10;
        node_1.style.positionTop = 10;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 10;
        node_1.layout.x = 10;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with position absolute, top and left", root_node, root_layout);
  }

  @Test
  public void testCase47()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.paddingLeft = 20;
      node_0.style.paddingTop = 20;
      node_0.style.paddingRight = 20;
      node_0.style.paddingBottom = 20;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionLeft = 5;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 40;
      node_0.layout.height = 40;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 20;
        node_1.layout.x = 5;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with padding and child position absolute, left", root_node, root_layout);
  }

  @Test
  public void testCase48()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.marginTop = 5;
        node_1.style.positionTop = 5;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 10;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with position: absolute, top and marginTop", root_node, root_layout);
  }

  @Test
  public void testCase49()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.marginLeft = 5;
        node_1.style.positionLeft = 5;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 10;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with position: absolute, left and marginLeft", root_node, root_layout);
  }

  @Test
  public void testCase50()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_AROUND;
      node_0.style.height = 200;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1 = node_0.getChildAt(1);
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 200;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 100;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 100;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with space-around and child position absolute", root_node, root_layout);
  }

  @Test
  public void testCase51()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 700;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.marginLeft = 5;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 700;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 5;
        node_1.layout.width = 695;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with flex and main margin", root_node, root_layout);
  }

  @Test
  public void testCase52()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 700;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.paddingRight = 5;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 700;
      node_0.layout.height = 0;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 347.5f;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 0;
        node_1.layout.x = 347.5f;
        node_1.layout.width = 352.5f;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with multiple flex and padding", root_node, root_layout);
  }

  @Test
  public void testCase53()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 700;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.marginLeft = 5;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 700;
      node_0.layout.height = 0;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 347.5f;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 0;
        node_1.layout.x = 352.5f;
        node_1.layout.width = 347.5f;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with multiple flex and margin", root_node, root_layout);
  }

  @Test
  public void testCase54()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.height = 300;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 600;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 300;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 600;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 600;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with flex and overflow", root_node, root_layout);
  }

  @Test
  public void testCase55()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 600;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.flex = 1;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 600;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with flex and position absolute", root_node, root_layout);
  }

  @Test
  public void testCase56()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.height = 500;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.flex = 1;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 500;
      addChildren(node_0, 2);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 500;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with double flex and position absolute", root_node, root_layout);
  }

  @Test
  public void testCase57()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.borderLeft = 5;
      node_0.style.borderTop = 5;
      node_0.style.borderRight = 5;
      node_0.style.borderBottom = 5;
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
    }

    test("should layout node with borderWidth", root_node, root_layout);
  }

  @Test
  public void testCase58()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.borderTop = 1;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionTop = -1;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 1;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with borderWidth and position: absolute, top", root_node, root_layout);
  }

  @Test
  public void testCase59()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.borderLeft = 1;
      node_0.style.borderTop = 1;
      node_0.style.borderRight = 1;
      node_0.style.borderBottom = 1;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionLeft = 5;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 2;
      node_0.layout.height = 2;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 1;
        node_1.layout.x = 6;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with borderWidth and position: absolute, top. cross axis", root_node, root_layout);
  }

  @Test
  public void testCase60()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.width = 50;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        node_1.style.marginLeft = 20;
        node_1.style.paddingLeft = 20;
        node_1.style.paddingTop = 20;
        node_1.style.paddingRight = 20;
        node_1.style.paddingBottom = 20;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 50;
      node_0.layout.height = 40;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 20;
        node_1.layout.width = 40;
        node_1.layout.height = 40;
      }
    }

    test("should correctly take into account min padding for stretch", root_node, root_layout);
  }

  @Test
  public void testCase61()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.borderRight = 5;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 5;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 5;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with negative width", root_node, root_layout);
  }

  @Test
  public void testCase62()
  {
    CSSNode root_node = new CSSNode();
    {
      CSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.borderRight = 1;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.marginRight = -8;
      }
    }

    CSSNode root_layout = new CSSNode();
    {
      CSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        CSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should handle negative margin and min padding correctly", root_node, root_layout);
  }
}
