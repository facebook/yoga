package com.facebook.csslayout;

import org.junit.Assert;
import org.junit.Test;

/**
 * Tests for {@link LayoutEngine}
 */
public class LayoutEngineTest {

  private static class TestCSSNode extends CSSNode {

    public String context = null;

    public TestCSSNode getChildAt(int i) {
      return (TestCSSNode) super.getChildAt(i);
    }
  }

  private static CSSNode.MeasureFunction sTestMeasureFunction = new CSSNode.MeasureFunction() {

    @Override
    public void measure(CSSNode node, float width, MeasureOutput measureOutput) {
      TestCSSNode testCSSNode = (TestCSSNode) node;
      if (Float.isNaN(width)) {
        width = 1000000;
      }
      if (testCSSNode.context.equals("small")) {
        measureOutput.width = Math.min(33, width);
        measureOutput.height = 18;
        return;
      }
      if (testCSSNode.context.equals("loooooooooong with space")) {
        measureOutput.width = width >= 171 ? 171 : Math.max(100, width);
        measureOutput.height = width >= 171 ? 18 : 36;
        return;
      }
      throw new RuntimeException(
          "Got unexpected text that we don't know how to measure: " + testCSSNode.context);
    }
  };

  private static void test(String message, CSSNode style, CSSNode expectedLayout) {
    style.calculateLayout();
    assertLayoutsEqual(message, style, expectedLayout);
  }

  private static void addChildren(CSSNode node, int numChildren) {
    for (int i = 0; i < numChildren; i++) {
      node.addChildAt(new TestCSSNode(), i);
    }
  }

  private static void assertLayoutsEqual(String message, CSSNode actual, CSSNode expected) {
    Assert.assertTrue(message + "\nActual:\n" + actual.toString() + "\nExpected:\n" + expected.toString(), areLayoutsEqual(actual, expected));
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 200;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
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

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 500;
        node_1.style.height = 500;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 500;
        node_1.style.height = 500;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.width = 250;
          node_2.style.height = 250;
          node_2 = node_1.getChildAt(1);
          node_2.style.width = 250;
          node_2.style.height = 250;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
          TestCSSNode node_2;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 200;
      node_0.style.marginLeft = 10;
      node_0.style.marginTop = 10;
      node_0.style.marginRight = 10;
      node_0.style.marginBottom = 10;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      node_0.style.marginLeft = 10;
      node_0.style.marginTop = 10;
      node_0.style.marginRight = 10;
      node_0.style.marginBottom = 10;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
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

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 10;
      node_0.layout.x = 10;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 300;
        node_1.style.height = 150;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 300;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 300;
        node_1.style.height = 150;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 350;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.width = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.width = 1000;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.flex = 1;
          node_2.style.width = 1000;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.style.flex = 1;
            node_3.style.width = 1000;
          }
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 1000;
        node_1.layout.height = 1000;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 1000;
          node_2.layout.height = 1000;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      node_0.style.marginLeft = 5;
      node_0.style.marginTop = 10;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 10;
      node_0.layout.x = 5;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_START;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_END;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_BETWEEN;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_AROUND;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.CENTER;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.FLEX_START;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 200;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.CENTER;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 200;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.FLEX_END;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 200;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.FLEX_END;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 200;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.CENTER;
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.STRETCH;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.marginLeft = 5;
        node_1.style.marginTop = 5;
        node_1.style.marginRight = 5;
        node_1.style.marginBottom = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.height = 200;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.CENTER;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_END;
      node_0.style.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.marginTop = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignItems = CSSAlign.FLEX_END;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
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

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 20;
      node_0.layout.height = 120;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 20;
        node_1.layout.height = 120;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.STRETCH;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.marginLeft = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.paddingLeft = 5;
      node_0.style.paddingTop = 5;
      node_0.style.paddingRight = 5;
      node_0.style.paddingBottom = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.paddingLeft = 5;
      node_0.style.paddingTop = 5;
      node_0.style.paddingRight = 5;
      node_0.style.paddingBottom = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.paddingLeft = 5;
      node_0.style.paddingTop = 5;
      node_0.style.paddingRight = 5;
      node_0.style.paddingBottom = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.marginLeft = 5;
        node_1.style.marginTop = 5;
        node_1.style.marginRight = 5;
        node_1.style.marginBottom = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 20;
      node_0.layout.height = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        node_1.style.paddingLeft = 10;
        node_1.style.paddingTop = 10;
        node_1.style.paddingRight = 10;
        node_1.style.paddingBottom = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 20;
      node_0.layout.height = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.paddingLeft = 50;
      node_0.style.paddingTop = 50;
      node_0.style.paddingRight = 50;
      node_0.style.paddingBottom = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        node_1.style.paddingLeft = 10;
        node_1.style.paddingTop = 10;
        node_1.style.paddingRight = 10;
        node_1.style.paddingBottom = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 120;
      node_0.layout.height = 120;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.marginLeft = 16;
          node_2.style.marginTop = 16;
          node_2.style.marginRight = 16;
          node_2.style.marginBottom = 16;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 32;
      node_0.layout.height = 32;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 32;
        node_1.layout.height = 32;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.positionLeft = 5;
      node_0.style.positionTop = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_AROUND;
      node_0.style.height = 10;
      node_0.style.paddingTop = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.positionBottom = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.positionTop = 10;
      node_0.style.positionBottom = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 500;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.width = 50;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 500;
      node_0.layout.height = 0;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.marginRight = 15;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.CENTER;
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.paddingRight = 12;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.height = 5;
      node_0.style.paddingBottom = 20;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 5;
      node_0.style.paddingLeft = 20;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.width = 400;
        }
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        node_1.style.width = 200;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 400;
      node_0.layout.height = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 400;
        node_1.layout.height = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.paddingLeft = 5;
      node_0.style.paddingTop = 5;
      node_0.style.paddingRight = 5;
      node_0.style.paddingBottom = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionLeft = 10;
        node_1.style.positionTop = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.paddingLeft = 20;
      node_0.style.paddingTop = 20;
      node_0.style.paddingRight = 20;
      node_0.style.paddingBottom = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionLeft = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 40;
      node_0.layout.height = 40;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.marginTop = 5;
        node_1.style.positionTop = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.marginLeft = 5;
        node_1.style.positionLeft = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_AROUND;
      node_0.style.height = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1 = node_0.getChildAt(1);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 700;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.marginLeft = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 700;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 700;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.paddingRight = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 700;
      node_0.layout.height = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 700;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.marginLeft = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 700;
      node_0.layout.height = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.height = 300;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 600;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 300;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 600;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 600;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.height = 500;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 500;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.borderLeft = 5;
      node_0.style.borderTop = 5;
      node_0.style.borderRight = 5;
      node_0.style.borderBottom = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.borderTop = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionTop = -1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.borderLeft = 1;
      node_0.style.borderTop = 1;
      node_0.style.borderRight = 1;
      node_0.style.borderBottom = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionLeft = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 2;
      node_0.layout.height = 2;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        node_1.style.marginLeft = 20;
        node_1.style.paddingLeft = 20;
        node_1.style.paddingTop = 20;
        node_1.style.paddingRight = 20;
        node_1.style.paddingBottom = 20;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 50;
      node_0.layout.height = 40;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.borderRight = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 5;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
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
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.borderRight = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.marginRight = -8;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 1;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should handle negative margin and min padding correctly", root_node, root_layout);
  }

  @Test
  public void testCase63()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 33;
      node_0.layout.height = 18;
    }

    test("should layout node with just text", root_node, root_layout);
  }

  @Test
  public void testCase64()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 10;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 18;
    }

    test("should layout node with text and width", root_node, root_layout);
  }

  @Test
  public void testCase65()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.marginLeft = 5;
      node_0.style.marginTop = 5;
      node_0.style.marginRight = 5;
      node_0.style.marginBottom = 5;
      node_0.style.paddingLeft = 5;
      node_0.style.paddingTop = 5;
      node_0.style.paddingRight = 5;
      node_0.style.paddingBottom = 5;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 5;
      node_0.layout.x = 5;
      node_0.layout.width = 181;
      node_0.layout.height = 28;
    }

    test("should layout node with text, padding and margin", root_node, root_layout);
  }

  @Test
  public void testCase66()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 300;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.alignSelf = CSSAlign.STRETCH;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 300;
        node_1.layout.height = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 300;
          node_2.layout.height = 0;
        }
      }
    }

    test("should layout node with nested alignSelf: stretch", root_node, root_layout);
  }

  @Test
  public void testCase67()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.ROW;
        node_1.style.width = 500;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.flex = 1;
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 500;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 18;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 500;
          node_2.layout.height = 18;
        }
      }
    }

    test("should layout node with text and flex", root_node, root_layout);
  }

  @Test
  public void testCase68()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 130;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignItems = CSSAlign.STRETCH;
        node_1.style.alignSelf = CSSAlign.STRETCH;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 130;
      node_0.layout.height = 36;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 130;
        node_1.layout.height = 36;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 130;
          node_2.layout.height = 36;
        }
      }
    }

    test("should layout node with text and stretch", root_node, root_layout);
  }

  @Test
  public void testCase69()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignItems = CSSAlign.STRETCH;
        node_1.style.alignSelf = CSSAlign.STRETCH;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.width = 130;
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 36;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 36;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 130;
          node_2.layout.height = 36;
        }
      }
    }

    test("should layout node with text stretch and width", root_node, root_layout);
  }

  @Test
  public void testCase70()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "loooooooooong with space";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 36;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 36;
      }
    }

    test("should layout node with text bounded by parent", root_node, root_layout);
  }

  @Test
  public void testCase71()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.paddingLeft = 10;
      node_0.style.paddingTop = 10;
      node_0.style.paddingRight = 10;
      node_0.style.paddingBottom = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.marginLeft = 10;
        node_1.style.marginTop = 10;
        node_1.style.marginRight = 10;
        node_1.style.marginBottom = 10;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 76;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 20;
        node_1.layout.x = 20;
        node_1.layout.width = 100;
        node_1.layout.height = 36;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 100;
          node_2.layout.height = 36;
        }
      }
    }

    test("should layout node with text bounded by grand-parent", root_node, root_layout);
  }

  @Test
  public void testCase72()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_BETWEEN;
      node_0.style.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 900;
        node_1 = node_0.getChildAt(1);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 900;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 900;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout space-between when remaining space is negative", root_node, root_layout);
  }

  @Test
  public void testCase73()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.justifyContent = CSSJustify.FLEX_END;
      node_0.style.width = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 900;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = -700;
        node_1.layout.width = 900;
        node_1.layout.height = 0;
      }
    }

    test("should layout flex-end when remaining space is negative", root_node, root_layout);
  }

  @Test
  public void testCase74()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.ROW;
        node_1.style.width = 200;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.marginLeft = 20;
          node_2.style.marginTop = 20;
          node_2.style.marginRight = 20;
          node_2.style.marginBottom = 20;
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 58;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 58;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 20;
          node_2.layout.x = 20;
          node_2.layout.width = 171;
          node_2.layout.height = 18;
        }
      }
    }

    test("should layout text with flexDirection row", root_node, root_layout);
  }

  @Test
  public void testCase75()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 200;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.marginLeft = 20;
          node_2.style.marginTop = 20;
          node_2.style.marginRight = 20;
          node_2.style.marginBottom = 20;
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 76;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 76;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 20;
          node_2.layout.x = 20;
          node_2.layout.width = 160;
          node_2.layout.height = 36;
        }
      }
    }

    test("should layout with text and margin", root_node, root_layout);
  }

  @Test
  public void testCase76()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionLeft = 0;
        node_1.style.positionTop = 0;
        node_1.style.positionRight = 0;
        node_1.style.positionBottom = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout with position absolute, top, left, bottom, right", root_node, root_layout);
  }

  @Test
  public void testCase77()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 2.5f;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 7.5f;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 25;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 25;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 75;
      }
    }

    test("should layout with arbitrary flex", root_node, root_layout);
  }

  @Test
  public void testCase78()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout with negative flex", root_node, root_layout);
  }

  @Test
  public void testCase79()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.STRETCH;
      node_0.style.width = 80;
      node_0.style.paddingLeft = 7;
      node_0.style.paddingTop = 7;
      node_0.style.paddingRight = 7;
      node_0.style.paddingBottom = 7;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 80;
      node_0.layout.height = 68;
    }

    test("should layout text with alignItems: stretch", root_node, root_layout);
  }

  @Test
  public void testCase80()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "loooooooooong with space";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 36;
      }
    }

    test("should layout node with text and position absolute", root_node, root_layout);
  }

  @Test
  public void testCase81()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_START;
      node_0.style.width = 620;
      node_0.style.height = 595;
      node_0.style.marginBottom = 13;
      node_0.style.paddingLeft = 7;
      node_0.style.paddingTop = 7;
      node_0.style.paddingRight = 7;
      node_0.style.paddingBottom = 7;
      node_0.style.borderRight = 3;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 620;
      node_0.layout.height = 595;
    }

    test("Random #0", root_node, root_layout);
  }

  @Test
  public void testCase82()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 603;
      node_0.style.marginLeft = -5;
      node_0.style.paddingTop = 18;
      node_0.style.paddingBottom = 14;
      node_0.style.borderLeft = 2;
      node_0.style.borderTop = 2;
      node_0.style.borderRight = 2;
      node_0.style.borderBottom = 2;
      node_0.style.borderLeft = 2;
      node_0.style.positionTop = 6;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 6;
      node_0.layout.x = -5;
      node_0.layout.width = 603;
      node_0.layout.height = 54;
    }

    test("Random #1", root_node, root_layout);
  }

  @Test
  public void testCase83()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("Random #2", root_node, root_layout);
  }

  @Test
  public void testCase84()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #3", root_node, root_layout);
  }

  @Test
  public void testCase85()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN;
      node_0.style.width = 255;
      node_0.style.marginRight = -6;
      node_0.style.marginBottom = -3;
      node_0.style.paddingLeft = 4;
      node_0.style.paddingTop = 4;
      node_0.style.paddingRight = 4;
      node_0.style.paddingBottom = 4;
      node_0.style.paddingTop = 8;
      node_0.style.borderLeft = 2;
      node_0.style.borderTop = 2;
      node_0.style.borderRight = 2;
      node_0.style.borderBottom = 2;
      node_0.style.borderLeft = 1;
      node_0.style.borderRight = 2;
      node_0.style.borderBottom = 1;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 255;
      node_0.layout.height = 15;
    }

    test("Random #4", root_node, root_layout);
  }

  @Test
  public void testCase86()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 34.671875f;
        node_1.layout.height = 18;
      }
    }

    test("Random #5", root_node, root_layout);
  }

  @Test
  public void testCase87()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.justifyContent = CSSJustify.SPACE_AROUND;
      node_0.style.width = 426;
      node_0.style.height = 497;
      node_0.style.marginTop = 1;
      node_0.style.marginRight = 14;
      node_0.style.paddingRight = 7;
      node_0.style.borderLeft = 2;
      node_0.style.borderRight = 2;
      node_0.style.positionTop = -1;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 426;
      node_0.layout.height = 497;
    }

    test("Random #6", root_node, root_layout);
  }

  @Test
  public void testCase88()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("Random #7", root_node, root_layout);
  }

  @Test
  public void testCase89()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "small";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 34.671875f;
        node_1.layout.height = 18;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 34.671875f;
          node_2.layout.height = 18;
        }
      }
    }

    test("Random #8", root_node, root_layout);
  }

  @Test
  public void testCase90()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #9", root_node, root_layout);
  }

  @Test
  public void testCase91()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("Random #10", root_node, root_layout);
  }

  @Test
  public void testCase92()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN;
      node_0.style.alignItems = CSSAlign.FLEX_END;
      node_0.style.width = 179;
      node_0.style.marginTop = 7;
      node_0.style.paddingLeft = 5;
      node_0.style.paddingTop = 17;
      node_0.style.paddingBottom = 16;
      node_0.style.borderTop = 0;
      node_0.style.borderBottom = 1;
      node_0.style.positionLeft = -4;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.ROW;
        node_1.style.alignSelf = CSSAlign.CENTER;
        node_1.style.width = 277;
        node_1.style.marginRight = 6;
        node_1.style.marginBottom = -10;
        node_1.style.paddingLeft = 4;
        node_1.style.paddingTop = 4;
        node_1.style.paddingRight = 4;
        node_1.style.paddingBottom = 4;
        node_1.style.paddingLeft = 11;
        node_1.style.borderLeft = 1;
        node_1.style.borderTop = 1;
        node_1.style.borderRight = 1;
        node_1.style.borderBottom = 1;
        node_1.style.borderTop = 1;
        node_1.style.positionTop = 1;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 7;
      node_0.layout.x = -4;
      node_0.layout.width = 179;
      node_0.layout.height = 52;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 18;
        node_1.layout.x = -49.5f;
        node_1.layout.width = 277;
        node_1.layout.height = 28;
      }
    }

    test("Random #11", root_node, root_layout);
  }

  @Test
  public void testCase93()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #12", root_node, root_layout);
  }

  @Test
  public void testCase94()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.justifyContent = CSSJustify.SPACE_AROUND;
      node_0.style.width = 551;
      node_0.style.marginLeft = -9;
      node_0.style.marginTop = -9;
      node_0.style.marginRight = -9;
      node_0.style.marginBottom = -9;
      node_0.style.marginTop = 12;
      node_0.style.borderTop = 1;
      node_0.style.positionLeft = 8;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 12;
      node_0.layout.x = -1;
      node_0.layout.width = 551;
      node_0.layout.height = 19;
    }

    test("Random #13", root_node, root_layout);
  }

  @Test
  public void testCase95()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "loooooooooong with space";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 172.421875f;
        node_1.layout.height = 18;
      }
    }

    test("Random #14", root_node, root_layout);
  }

  @Test
  public void testCase96()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN;
      node_0.style.width = 809;
      node_0.style.marginLeft = 6;
      node_0.style.marginTop = 8;
      node_0.style.marginRight = 6;
      node_0.style.paddingRight = 16;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 8;
      node_0.layout.x = 6;
      node_0.layout.width = 809;
      node_0.layout.height = 18;
    }

    test("Random #15", root_node, root_layout);
  }

  @Test
  public void testCase97()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #16", root_node, root_layout);
  }

  @Test
  public void testCase98()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("Random #17", root_node, root_layout);
  }

  @Test
  public void testCase99()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "small";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 34.671875f;
        node_1.layout.height = 18;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 34.671875f;
          node_2.layout.height = 18;
        }
      }
    }

    test("Random #18", root_node, root_layout);
  }

  @Test
  public void testCase100()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_START;
      node_0.style.marginLeft = 6;
      node_0.style.marginTop = 6;
      node_0.style.marginRight = 6;
      node_0.style.marginBottom = 6;
      node_0.style.marginRight = 5;
      node_0.style.marginBottom = 7;
      node_0.style.paddingRight = 10;
      node_0.style.positionLeft = 8;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 6;
      node_0.layout.x = 14;
      node_0.layout.width = 10;
      node_0.layout.height = 0;
    }

    test("Random #19", root_node, root_layout);
  }

  @Test
  public void testCase101()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 161;
      node_0.style.height = 261;
      node_0.style.marginLeft = 3;
      node_0.style.marginRight = 4;
      node_0.style.paddingTop = 2;
      node_0.style.borderLeft = 3;
      node_0.style.borderTop = 3;
      node_0.style.borderRight = 3;
      node_0.style.borderBottom = 3;
      node_0.style.borderRight = 0;
      node_0.style.borderBottom = 2;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.COLUMN;
        node_1.style.flex = 1;
        node_1.style.width = 860;
        node_1.style.height = 424;
        node_1.style.marginLeft = 10;
        node_1.style.marginTop = 10;
        node_1.style.marginRight = 10;
        node_1.style.marginBottom = 10;
        node_1.style.marginTop = 5;
        node_1.style.marginRight = -7;
        node_1.style.paddingLeft = 5;
        node_1.style.paddingTop = 5;
        node_1.style.paddingRight = 5;
        node_1.style.paddingBottom = 5;
        node_1.style.paddingLeft = 5;
        node_1.style.paddingTop = 15;
        node_1.style.paddingBottom = 9;
        node_1.style.borderTop = 2;
        node_1.style.borderBottom = 3;
        node_1.style.positionLeft = 4;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 3;
      node_0.layout.width = 161;
      node_0.layout.height = 261;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 10;
        node_1.layout.x = 17;
        node_1.layout.width = 155;
        node_1.layout.height = 424;
      }
    }

    test("Random #20", root_node, root_layout);
  }

  @Test
  public void testCase102()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 596;
      node_0.style.marginTop = 12;
      node_0.style.marginRight = 6;
      node_0.style.marginBottom = 16;
      node_0.style.paddingLeft = 15;
      node_0.style.paddingTop = 15;
      node_0.style.paddingRight = 15;
      node_0.style.paddingBottom = 15;
      node_0.style.borderLeft = 1;
      node_0.style.borderTop = 1;
      node_0.style.borderRight = 1;
      node_0.style.borderBottom = 1;
      node_0.style.positionLeft = -7;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 12;
      node_0.layout.x = -7;
      node_0.layout.width = 596;
      node_0.layout.height = 50;
    }

    test("Random #21", root_node, root_layout);
  }

  @Test
  public void testCase103()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #22", root_node, root_layout);
  }

  @Test
  public void testCase104()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("Random #23", root_node, root_layout);
  }

  @Test
  public void testCase105()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #24", root_node, root_layout);
  }

  @Test
  public void testCase106()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_AROUND;
      node_0.style.height = 846;
      node_0.style.marginLeft = 19;
      node_0.style.marginTop = 19;
      node_0.style.marginRight = 19;
      node_0.style.marginBottom = 19;
      node_0.style.marginLeft = -7;
      node_0.style.paddingLeft = 18;
      node_0.style.paddingTop = 6;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 19;
      node_0.layout.x = -7;
      node_0.layout.width = 18;
      node_0.layout.height = 846;
    }

    test("Random #25", root_node, root_layout);
  }

  @Test
  public void testCase107()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 726;
      node_0.style.marginLeft = 16;
      node_0.style.marginTop = 16;
      node_0.style.marginRight = 16;
      node_0.style.marginBottom = 16;
      node_0.style.marginTop = 15;
      node_0.style.marginBottom = 1;
      node_0.style.borderLeft = 2;
      node_0.style.borderTop = 2;
      node_0.style.borderRight = 2;
      node_0.style.borderBottom = 2;
      node_0.style.borderTop = 1;
      node_0.style.positionLeft = -1;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 15;
      node_0.layout.x = 15;
      node_0.layout.width = 726;
      node_0.layout.height = 3;
    }

    test("Random #26", root_node, root_layout);
  }

  @Test
  public void testCase108()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #27", root_node, root_layout);
  }

  @Test
  public void testCase109()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_START;
      node_0.style.alignItems = CSSAlign.STRETCH;
      node_0.style.marginLeft = 1;
      node_0.style.marginRight = -2;
      node_0.style.paddingLeft = 4;
      node_0.style.paddingTop = 4;
      node_0.style.paddingRight = 4;
      node_0.style.paddingBottom = 4;
      node_0.style.paddingLeft = 19;
      node_0.style.borderLeft = 1;
      node_0.style.borderTop = 1;
      node_0.style.positionTop = -3;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = -3;
      node_0.layout.x = 1;
      node_0.layout.width = 24;
      node_0.layout.height = 9;
    }

    test("Random #28", root_node, root_layout);
  }

  @Test
  public void testCase110()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #29", root_node, root_layout);
  }

  @Test
  public void testCase111()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "loooooooooong with space";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 172.421875f;
        node_1.layout.height = 18;
      }
    }

    test("Random #30", root_node, root_layout);
  }

  @Test
  public void testCase112()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("Random #31", root_node, root_layout);
  }

  @Test
  public void testCase113()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #32", root_node, root_layout);
  }

  @Test
  public void testCase114()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN;
      node_0.style.height = 315;
      node_0.style.marginTop = -2;
      node_0.style.marginRight = -4;
      node_0.style.marginBottom = 0;
      node_0.style.paddingLeft = 18;
      node_0.style.borderRight = 3;
      node_0.style.positionLeft = 4;
      node_0.style.positionTop = -2;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = -4;
      node_0.layout.x = 4;
      node_0.layout.width = 21;
      node_0.layout.height = 315;
    }

    test("Random #33", root_node, root_layout);
  }

  @Test
  public void testCase115()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #34", root_node, root_layout);
  }

  @Test
  public void testCase116()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN;
      node_0.style.justifyContent = CSSJustify.SPACE_BETWEEN;
      node_0.style.height = 819;
      node_0.style.marginLeft = 1;
      node_0.style.marginTop = 1;
      node_0.style.marginRight = 1;
      node_0.style.marginBottom = 1;
      node_0.style.marginTop = -3;
      node_0.style.marginBottom = 5;
      node_0.style.paddingLeft = 18;
      node_0.style.borderLeft = 2;
      node_0.style.borderRight = 3;
      node_0.style.positionLeft = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.ROW;
        node_1.style.alignSelf = CSSAlign.STRETCH;
        node_1.style.flex = 8;
        node_1.style.width = 532;
        node_1.style.marginLeft = 8;
        node_1.style.marginTop = 8;
        node_1.style.marginRight = 8;
        node_1.style.marginBottom = 8;
        node_1.style.marginLeft = 16;
        node_1.style.marginBottom = 9;
        node_1.style.paddingLeft = 7;
        node_1.style.paddingTop = 7;
        node_1.style.paddingRight = 7;
        node_1.style.paddingBottom = 7;
        node_1.style.paddingLeft = 8;
        node_1.style.paddingTop = 5;
        node_1.style.positionLeft = 4;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = -3;
      node_0.layout.x = 6;
      node_0.layout.width = 579;
      node_0.layout.height = 819;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 8;
        node_1.layout.x = 40;
        node_1.layout.width = 532;
        node_1.layout.height = 802;
      }
    }

    test("Random #35", root_node, root_layout);
  }

  @Test
  public void testCase117()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.CENTER;
      node_0.style.marginLeft = 13;
      node_0.style.marginTop = 13;
      node_0.style.marginRight = 13;
      node_0.style.marginBottom = 13;
      node_0.style.marginBottom = 0;
      node_0.style.borderTop = 1;
      node_0.style.borderRight = 1;
      node_0.style.positionTop = 8;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 21;
      node_0.layout.x = 13;
      node_0.layout.width = 1;
      node_0.layout.height = 1;
    }

    test("Random #36", root_node, root_layout);
  }

  @Test
  public void testCase118()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.alignItems = CSSAlign.FLEX_END;
      node_0.style.width = 632;
      node_0.style.height = 907;
      node_0.style.marginLeft = -3;
      node_0.style.marginTop = 5;
      node_0.style.marginRight = -6;
      node_0.style.marginBottom = -5;
      node_0.style.paddingLeft = 1;
      node_0.style.paddingTop = 1;
      node_0.style.paddingRight = 1;
      node_0.style.paddingBottom = 1;
      node_0.style.paddingBottom = 6;
      node_0.style.borderBottom = 3;
      node_0.style.positionLeft = -9;
      node_0.style.positionTop = 4;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 9;
      node_0.layout.x = -12;
      node_0.layout.width = 632;
      node_0.layout.height = 907;
    }

    test("Random #37", root_node, root_layout);
  }

  @Test
  public void testCase119()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #38", root_node, root_layout);
  }

  @Test
  public void testCase120()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #39", root_node, root_layout);
  }

  @Test
  public void testCase121()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #40", root_node, root_layout);
  }

  @Test
  public void testCase122()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #41", root_node, root_layout);
  }

  @Test
  public void testCase123()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_END;
      node_0.style.width = 398;
      node_0.style.height = 198;
      node_0.style.marginLeft = 9;
      node_0.style.marginTop = -9;
      node_0.style.marginRight = 13;
      node_0.style.marginBottom = 6;
      node_0.style.positionLeft = -2;
      node_0.style.positionTop = -2;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = -11;
      node_0.layout.x = 7;
      node_0.layout.width = 398;
      node_0.layout.height = 198;
    }

    test("Random #42", root_node, root_layout);
  }

  @Test
  public void testCase124()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN;
      node_0.style.justifyContent = CSSJustify.SPACE_AROUND;
      node_0.style.height = 514;
      node_0.style.marginLeft = 16;
      node_0.style.marginTop = 16;
      node_0.style.marginRight = 16;
      node_0.style.marginBottom = 16;
      node_0.style.marginTop = 5;
      node_0.style.marginRight = 3;
      node_0.style.paddingRight = 6;
      node_0.style.borderLeft = 0;
      node_0.style.borderTop = 0;
      node_0.style.borderRight = 0;
      node_0.style.borderBottom = 0;
      node_0.style.positionLeft = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 5;
      node_0.layout.x = 21;
      node_0.layout.width = 6;
      node_0.layout.height = 514;
    }

    test("Random #43", root_node, root_layout);
  }

  @Test
  public void testCase125()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 34.671875f;
        node_1.layout.height = 18;
      }
    }

    test("Random #44", root_node, root_layout);
  }

  @Test
  public void testCase126()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.CENTER;
      node_0.style.width = 952;
      node_0.style.marginLeft = -2;
      node_0.style.marginTop = -2;
      node_0.style.marginRight = -2;
      node_0.style.marginBottom = -2;
      node_0.style.marginTop = 1;
      node_0.style.marginBottom = 2;
      node_0.style.paddingLeft = 12;
      node_0.style.borderTop = 3;
      node_0.style.positionTop = -10;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = -9;
      node_0.layout.x = -2;
      node_0.layout.width = 952;
      node_0.layout.height = 3;
    }

    test("Random #45", root_node, root_layout);
  }

  @Test
  public void testCase127()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 937;
      node_0.style.borderLeft = 0;
      node_0.style.borderTop = 0;
      node_0.style.borderRight = 0;
      node_0.style.borderBottom = 0;
      node_0.style.borderTop = 1;
      node_0.style.positionLeft = -2;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = -2;
      node_0.layout.width = 937;
      node_0.layout.height = 19;
    }

    test("Random #46", root_node, root_layout);
  }

  @Test
  public void testCase128()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 530;
      node_0.style.height = 726;
      node_0.style.marginLeft = -5;
      node_0.style.marginTop = -5;
      node_0.style.marginRight = -5;
      node_0.style.marginBottom = -5;
      node_0.style.marginLeft = 10;
      node_0.style.paddingLeft = 2;
      node_0.style.borderTop = 3;
      node_0.style.positionLeft = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.ROW;
        node_1.style.width = 195;
        node_1.style.marginTop = -2;
        node_1.style.marginRight = 15;
        node_1.style.marginBottom = 12;
        node_1.style.paddingRight = 14;
        node_1.style.borderTop = 2;
        node_1.style.positionTop = -1;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
        node_1 = node_0.getChildAt(1);
        node_1.style.justifyContent = CSSJustify.SPACE_BETWEEN;
        node_1.style.width = 638;
        node_1.style.height = 753;
        node_1.style.marginLeft = 19;
        node_1.style.marginTop = 3;
        node_1.style.marginRight = 10;
        node_1.style.paddingLeft = 14;
        node_1.style.paddingTop = 14;
        node_1.style.paddingRight = 14;
        node_1.style.paddingBottom = 14;
        node_1.style.paddingTop = 18;
        node_1.style.positionLeft = -7;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "loooooooooong with space";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = -5;
      node_0.layout.x = 10;
      node_0.layout.width = 530;
      node_0.layout.height = 726;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 2;
        node_1.layout.width = 195;
        node_1.layout.height = 20;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 6;
        node_1.layout.x = 224;
        node_1.layout.width = 638;
        node_1.layout.height = 753;
      }
    }

    test("Random #47", root_node, root_layout);
  }

  @Test
  public void testCase129()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #48", root_node, root_layout);
  }

  @Test
  public void testCase130()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN;
      node_0.style.justifyContent = CSSJustify.FLEX_START;
      node_0.style.alignItems = CSSAlign.STRETCH;
      node_0.style.height = 194;
      node_0.style.marginLeft = 1;
      node_0.style.marginTop = 1;
      node_0.style.marginRight = 1;
      node_0.style.marginBottom = 1;
      node_0.style.marginTop = -7;
      node_0.style.marginRight = -6;
      node_0.style.paddingLeft = 18;
      node_0.style.paddingTop = 18;
      node_0.style.paddingRight = 18;
      node_0.style.paddingBottom = 18;
      node_0.style.borderBottom = 0;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = -7;
      node_0.layout.x = 1;
      node_0.layout.width = 36;
      node_0.layout.height = 194;
    }

    test("Random #49", root_node, root_layout);
  }

  @Test
  public void testCase131()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #50", root_node, root_layout);
  }

  @Test
  public void testCase132()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 34.671875f;
        node_1.layout.height = 18;
      }
    }

    test("Random #51", root_node, root_layout);
  }

  @Test
  public void testCase133()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 803;
      node_0.style.height = 826;
      node_0.style.marginLeft = 19;
      node_0.style.marginRight = -3;
      node_0.style.marginBottom = -6;
      node_0.style.paddingBottom = 5;
      node_0.style.borderLeft = 1;
      node_0.style.borderTop = 2;
      node_0.style.positionLeft = -6;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 13;
      node_0.layout.width = 803;
      node_0.layout.height = 826;
    }

    test("Random #52", root_node, root_layout);
  }

  @Test
  public void testCase134()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #53", root_node, root_layout);
  }

  @Test
  public void testCase135()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #54", root_node, root_layout);
  }

  @Test
  public void testCase136()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 134;
      node_0.style.height = 394;
      node_0.style.marginLeft = 16;
      node_0.style.marginTop = 16;
      node_0.style.marginRight = 16;
      node_0.style.marginBottom = 16;
      node_0.style.marginTop = 9;
      node_0.style.marginBottom = 9;
      node_0.style.paddingLeft = 17;
      node_0.style.paddingRight = 3;
      node_0.style.borderLeft = 3;
      node_0.style.borderTop = 3;
      node_0.style.borderRight = 3;
      node_0.style.borderBottom = 3;
      node_0.style.borderBottom = 1;
      node_0.style.positionTop = -2;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 7;
      node_0.layout.x = 16;
      node_0.layout.width = 134;
      node_0.layout.height = 394;
    }

    test("Random #55", root_node, root_layout);
  }

  @Test
  public void testCase137()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN;
      node_0.style.width = 216;
      node_0.style.height = 721;
      node_0.style.marginLeft = -6;
      node_0.style.marginTop = -6;
      node_0.style.marginRight = -6;
      node_0.style.marginBottom = -6;
      node_0.style.marginLeft = 2;
      node_0.style.marginTop = -1;
      node_0.style.marginRight = -8;
      node_0.style.marginBottom = -10;
      node_0.style.paddingLeft = 4;
      node_0.style.paddingTop = 19;
      node_0.style.paddingBottom = 2;
      node_0.style.borderLeft = 0;
      node_0.style.borderBottom = 0;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = -1;
      node_0.layout.x = 2;
      node_0.layout.width = 216;
      node_0.layout.height = 721;
    }

    test("Random #56", root_node, root_layout);
  }

  @Test
  public void testCase138()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #57", root_node, root_layout);
  }

  @Test
  public void testCase139()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.FLEX_START;
      node_0.style.width = 173;
      node_0.style.marginLeft = 11;
      node_0.style.marginTop = 11;
      node_0.style.marginRight = 11;
      node_0.style.marginBottom = 11;
      node_0.style.marginLeft = 10;
      node_0.style.marginTop = 17;
      node_0.style.marginRight = 15;
      node_0.style.paddingBottom = 5;
      node_0.style.borderBottom = 0;
      node_0.style.positionLeft = 8;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 17;
      node_0.layout.x = 18;
      node_0.layout.width = 173;
      node_0.layout.height = 5;
    }

    test("Random #58", root_node, root_layout);
  }

  @Test
  public void testCase140()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #59", root_node, root_layout);
  }

  @Test
  public void testCase141()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "loooooooooong with space";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 172.421875f;
        node_1.layout.height = 18;
      }
    }

    test("Random #60", root_node, root_layout);
  }

  @Test
  public void testCase142()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #61", root_node, root_layout);
  }

  @Test
  public void testCase143()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 671;
      node_0.style.height = 603;
      node_0.style.marginLeft = 14;
      node_0.style.marginRight = 6;
      node_0.style.marginBottom = -10;
      node_0.style.paddingLeft = 5;
      node_0.style.paddingTop = 17;
      node_0.style.borderTop = 0;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 14;
      node_0.layout.width = 671;
      node_0.layout.height = 603;
    }

    test("Random #62", root_node, root_layout);
  }

  @Test
  public void testCase144()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #63", root_node, root_layout);
  }

  @Test
  public void testCase145()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #64", root_node, root_layout);
  }

  @Test
  public void testCase146()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #65", root_node, root_layout);
  }

  @Test
  public void testCase147()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #66", root_node, root_layout);
  }

  @Test
  public void testCase148()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_BETWEEN;
      node_0.style.width = 516;
      node_0.style.height = 712;
      node_0.style.marginLeft = 15;
      node_0.style.marginTop = 15;
      node_0.style.marginRight = 15;
      node_0.style.marginBottom = 15;
      node_0.style.marginLeft = -8;
      node_0.style.marginRight = 11;
      node_0.style.paddingLeft = 17;
      node_0.style.paddingTop = 17;
      node_0.style.paddingRight = 17;
      node_0.style.paddingBottom = 17;
      node_0.style.paddingTop = 4;
      node_0.style.borderLeft = 1;
      node_0.style.borderTop = 1;
      node_0.style.borderRight = 1;
      node_0.style.borderBottom = 1;
      node_0.style.positionTop = 4;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 19;
      node_0.layout.x = -8;
      node_0.layout.width = 516;
      node_0.layout.height = 712;
    }

    test("Random #67", root_node, root_layout);
  }

  @Test
  public void testCase149()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 34.671875f;
        node_1.layout.height = 18;
      }
    }

    test("Random #68", root_node, root_layout);
  }

  @Test
  public void testCase150()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN;
      node_0.style.width = 486;
      node_0.style.marginLeft = 19;
      node_0.style.marginTop = 19;
      node_0.style.marginRight = 19;
      node_0.style.marginBottom = 19;
      node_0.style.marginLeft = 16;
      node_0.style.marginRight = 10;
      node_0.style.borderTop = 3;
      node_0.style.positionLeft = 8;
      node_0.style.positionTop = -6;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.ROW;
        node_1.style.justifyContent = CSSJustify.FLEX_START;
        node_1.style.alignItems = CSSAlign.STRETCH;
        node_1.style.flex = 1;
        node_1.style.width = 482;
        node_1.style.height = 818;
        node_1.style.marginRight = 14;
        node_1.style.marginBottom = -9;
        node_1.style.paddingBottom = 14;
        node_1.style.borderLeft = 1;
        node_1.style.borderTop = 2;
        node_1.style.borderRight = 0;
        node_1.style.positionTop = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 13;
      node_0.layout.x = 24;
      node_0.layout.width = 486;
      node_0.layout.height = 812;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 3;
        node_1.layout.x = 0;
        node_1.layout.width = 482;
        node_1.layout.height = 818;
      }
    }

    test("Random #69", root_node, root_layout);
  }

  @Test
  public void testCase151()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #70", root_node, root_layout);
  }

  @Test
  public void testCase152()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.setMeasureFunction(sTestMeasureFunction);
            node_3.context = "loooooooooong with space";
          }
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 172.421875f;
        node_1.layout.height = 18;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 172.421875f;
          node_2.layout.height = 18;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.layout.y = 0;
            node_3.layout.x = 0;
            node_3.layout.width = 172.421875f;
            node_3.layout.height = 18;
          }
        }
      }
    }

    test("Random #71", root_node, root_layout);
  }

  @Test
  public void testCase153()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN;
      node_0.style.marginLeft = 12;
      node_0.style.marginTop = 12;
      node_0.style.marginRight = 12;
      node_0.style.marginBottom = 12;
      node_0.style.marginLeft = -9;
      node_0.style.marginBottom = 10;
      node_0.style.paddingLeft = 18;
      node_0.style.paddingTop = 10;
      node_0.style.paddingRight = 1;
      node_0.style.paddingBottom = 2;
      node_0.style.borderLeft = 1;
      node_0.style.positionTop = 7;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignItems = CSSAlign.FLEX_START;
        node_1.style.alignSelf = CSSAlign.CENTER;
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.marginLeft = -6;
        node_1.style.marginTop = -6;
        node_1.style.marginRight = -6;
        node_1.style.marginBottom = -6;
        node_1.style.marginRight = 10;
        node_1.style.marginBottom = 0;
        node_1.style.paddingLeft = 15;
        node_1.style.paddingTop = 15;
        node_1.style.paddingRight = 15;
        node_1.style.paddingBottom = 15;
        node_1.style.borderLeft = 1;
        node_1.style.borderTop = 1;
        node_1.style.borderRight = 1;
        node_1.style.borderBottom = 1;
        node_1.style.borderLeft = 3;
        node_1.style.borderTop = 1;
        node_1.style.borderBottom = 0;
        node_1.style.positionLeft = -7;
        node_1.style.positionTop = -9;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.flexDirection = CSSFlexDirection.ROW;
          node_2.style.justifyContent = CSSJustify.CENTER;
          node_2.style.alignItems = CSSAlign.FLEX_END;
          node_2.style.marginRight = 6;
          node_2.style.marginBottom = 16;
          node_2.style.paddingTop = 6;
          node_2.style.borderLeft = 2;
          node_2.style.borderTop = 1;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 19;
      node_0.layout.x = -9;
      node_0.layout.width = 20;
      node_0.layout.height = 12;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = -15;
        node_1.layout.x = -12;
        node_1.layout.width = 42;
        node_1.layout.height = 54;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 16;
          node_2.layout.x = 18;
          node_2.layout.width = 2;
          node_2.layout.height = 7;
        }
      }
    }

    test("Random #72", root_node, root_layout);
  }

  @Test
  public void testCase154()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #73", root_node, root_layout);
  }

  @Test
  public void testCase155()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #74", root_node, root_layout);
  }

  @Test
  public void testCase156()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.alignItems = CSSAlign.FLEX_END;
      node_0.style.width = 332;
      node_0.style.marginLeft = 18;
      node_0.style.marginTop = 18;
      node_0.style.marginRight = 18;
      node_0.style.marginBottom = 18;
      node_0.style.marginRight = -5;
      node_0.style.paddingLeft = 12;
      node_0.style.paddingTop = 12;
      node_0.style.paddingRight = 12;
      node_0.style.paddingBottom = 12;
      node_0.style.paddingBottom = 2;
      node_0.style.borderLeft = 1;
      node_0.style.borderTop = 1;
      node_0.style.borderRight = 1;
      node_0.style.borderBottom = 1;
      node_0.style.borderLeft = 1;
      node_0.style.positionLeft = -9;
      node_0.style.positionTop = -5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.ROW;
        node_1.style.width = 818;
        node_1.style.height = 543;
        node_1.style.marginLeft = -2;
        node_1.style.marginTop = -2;
        node_1.style.marginRight = -2;
        node_1.style.marginBottom = -2;
        node_1.style.marginLeft = 8;
        node_1.style.marginTop = 14;
        node_1.style.paddingTop = 10;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 13;
      node_0.layout.x = 9;
      node_0.layout.width = 332;
      node_0.layout.height = 571;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 27;
        node_1.layout.x = 21;
        node_1.layout.width = 818;
        node_1.layout.height = 543;
      }
    }

    test("Random #75", root_node, root_layout);
  }

  @Test
  public void testCase157()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.height = 885;
      node_0.style.marginLeft = 13;
      node_0.style.marginBottom = -2;
      node_0.style.paddingLeft = 7;
      node_0.style.positionLeft = -4;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 9;
      node_0.layout.width = 7;
      node_0.layout.height = 885;
    }

    test("Random #76", root_node, root_layout);
  }

  @Test
  public void testCase158()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #77", root_node, root_layout);
  }

  @Test
  public void testCase159()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #78", root_node, root_layout);
  }

  @Test
  public void testCase160()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_END;
      node_0.style.height = 332;
      node_0.style.marginLeft = 7;
      node_0.style.marginTop = 7;
      node_0.style.marginRight = 7;
      node_0.style.marginBottom = 7;
      node_0.style.marginTop = 17;
      node_0.style.marginRight = -6;
      node_0.style.paddingLeft = 4;
      node_0.style.paddingTop = 4;
      node_0.style.paddingRight = 4;
      node_0.style.paddingBottom = 4;
      node_0.style.paddingLeft = 16;
      node_0.style.paddingTop = 6;
      node_0.style.borderLeft = 0;
      node_0.style.borderTop = 0;
      node_0.style.positionLeft = 1;
      node_0.style.positionTop = -2;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 15;
      node_0.layout.x = 8;
      node_0.layout.width = 20;
      node_0.layout.height = 332;
    }

    test("Random #79", root_node, root_layout);
  }

  @Test
  public void testCase161()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN;
      node_0.style.justifyContent = CSSJustify.SPACE_BETWEEN;
      node_0.style.width = 410;
      node_0.style.height = 614;
      node_0.style.marginLeft = -2;
      node_0.style.marginTop = -2;
      node_0.style.marginRight = -2;
      node_0.style.marginBottom = -2;
      node_0.style.marginTop = 16;
      node_0.style.marginRight = 3;
      node_0.style.marginBottom = -7;
      node_0.style.paddingTop = 6;
      node_0.style.borderLeft = 3;
      node_0.style.borderTop = 3;
      node_0.style.borderRight = 3;
      node_0.style.borderBottom = 3;
      node_0.style.borderBottom = 0;
      node_0.style.positionTop = 1;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 17;
      node_0.layout.x = -2;
      node_0.layout.width = 410;
      node_0.layout.height = 614;
    }

    test("Random #80", root_node, root_layout);
  }

  @Test
  public void testCase162()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #81", root_node, root_layout);
  }

  @Test
  public void testCase163()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("Random #82", root_node, root_layout);
  }

  @Test
  public void testCase164()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN;
      node_0.style.width = 978;
      node_0.style.height = 446;
      node_0.style.marginLeft = 10;
      node_0.style.marginTop = 10;
      node_0.style.marginRight = 10;
      node_0.style.marginBottom = 10;
      node_0.style.marginLeft = -4;
      node_0.style.marginTop = -4;
      node_0.style.positionLeft = -4;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.FLEX_END;
        node_1.style.width = 256;
        node_1.style.height = 883;
        node_1.style.marginLeft = -8;
        node_1.style.borderLeft = 0;
        node_1.style.borderTop = 3;
        node_1.style.borderBottom = 0;
        node_1.style.positionLeft = 8;
        node_1.style.positionTop = -3;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = -4;
      node_0.layout.x = -8;
      node_0.layout.width = 978;
      node_0.layout.height = 446;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = -3;
        node_1.layout.x = 730;
        node_1.layout.width = 256;
        node_1.layout.height = 883;
      }
    }

    test("Random #83", root_node, root_layout);
  }

  @Test
  public void testCase165()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #84", root_node, root_layout);
  }

  @Test
  public void testCase166()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #85", root_node, root_layout);
  }

  @Test
  public void testCase167()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.CENTER;
      node_0.style.marginRight = -4;
      node_0.style.marginBottom = 6;
      node_0.style.paddingLeft = 11;
      node_0.style.paddingBottom = 3;
      node_0.style.borderTop = 0;
      node_0.style.positionLeft = 7;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 7;
      node_0.layout.width = 11;
      node_0.layout.height = 3;
    }

    test("Random #86", root_node, root_layout);
  }

  @Test
  public void testCase168()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_START;
      node_0.style.width = 335;
      node_0.style.marginLeft = 17;
      node_0.style.marginTop = 17;
      node_0.style.marginRight = 17;
      node_0.style.marginBottom = 17;
      node_0.style.marginLeft = 16;
      node_0.style.marginBottom = 4;
      node_0.style.paddingRight = 9;
      node_0.style.paddingBottom = 14;
      node_0.style.positionTop = 7;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 24;
      node_0.layout.x = 16;
      node_0.layout.width = 335;
      node_0.layout.height = 32;
    }

    test("Random #87", root_node, root_layout);
  }

  @Test
  public void testCase169()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_AROUND;
      node_0.style.width = 903;
      node_0.style.marginLeft = 7;
      node_0.style.marginTop = 7;
      node_0.style.marginRight = 7;
      node_0.style.marginBottom = 7;
      node_0.style.marginBottom = 13;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 7;
      node_0.layout.x = 7;
      node_0.layout.width = 903;
      node_0.layout.height = 18;
    }

    test("Random #88", root_node, root_layout);
  }

  @Test
  public void testCase170()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 380;
      node_0.style.height = 824;
      node_0.style.marginLeft = 13;
      node_0.style.marginTop = 13;
      node_0.style.marginRight = 13;
      node_0.style.marginBottom = 13;
      node_0.style.marginRight = 18;
      node_0.style.paddingLeft = 4;
      node_0.style.paddingTop = 4;
      node_0.style.paddingRight = 4;
      node_0.style.paddingBottom = 4;
      node_0.style.paddingLeft = 6;
      node_0.style.paddingRight = 17;
      node_0.style.paddingBottom = 7;
      node_0.style.borderRight = 0;
      node_0.style.positionLeft = -6;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 13;
      node_0.layout.x = 7;
      node_0.layout.width = 380;
      node_0.layout.height = 824;
    }

    test("Random #89", root_node, root_layout);
  }

  @Test
  public void testCase171()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("Random #90", root_node, root_layout);
  }

  @Test
  public void testCase172()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #91", root_node, root_layout);
  }

  @Test
  public void testCase173()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #92", root_node, root_layout);
  }

  @Test
  public void testCase174()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #93", root_node, root_layout);
  }

  @Test
  public void testCase175()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_END;
      node_0.style.width = 922;
      node_0.style.marginLeft = 6;
      node_0.style.marginTop = 6;
      node_0.style.marginRight = 6;
      node_0.style.marginBottom = 6;
      node_0.style.marginLeft = 18;
      node_0.style.marginTop = -10;
      node_0.style.marginBottom = 15;
      node_0.style.paddingTop = 3;
      node_0.style.borderLeft = 0;
      node_0.style.borderTop = 0;
      node_0.style.borderRight = 0;
      node_0.style.borderBottom = 0;
      node_0.style.borderLeft = 2;
      node_0.style.borderTop = 1;
      node_0.style.borderBottom = 0;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = -10;
      node_0.layout.x = 18;
      node_0.layout.width = 922;
      node_0.layout.height = 22;
    }

    test("Random #94", root_node, root_layout);
  }

  @Test
  public void testCase176()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.CENTER;
      node_0.style.width = 779;
      node_0.style.marginLeft = 3;
      node_0.style.marginBottom = 19;
      node_0.style.paddingLeft = 17;
      node_0.style.paddingTop = 17;
      node_0.style.paddingRight = 17;
      node_0.style.paddingBottom = 17;
      node_0.style.paddingTop = 15;
      node_0.style.positionLeft = 3;
      node_0.style.positionTop = 9;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 9;
      node_0.layout.x = 6;
      node_0.layout.width = 779;
      node_0.layout.height = 50;
    }

    test("Random #95", root_node, root_layout);
  }

  @Test
  public void testCase177()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("Random #96", root_node, root_layout);
  }

  @Test
  public void testCase178()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("Random #97", root_node, root_layout);
  }

  @Test
  public void testCase179()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 770;
      node_0.style.height = 873;
      node_0.style.marginBottom = 15;
      node_0.style.paddingTop = 0;
      node_0.style.paddingRight = 0;
      node_0.style.borderTop = 0;
      node_0.style.borderBottom = 0;
      node_0.style.positionLeft = 9;
      node_0.style.positionTop = 1;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 1;
      node_0.layout.x = 9;
      node_0.layout.width = 770;
      node_0.layout.height = 873;
    }

    test("Random #98", root_node, root_layout);
  }

  @Test
  public void testCase180()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("Random #99", root_node, root_layout);
  }
}
