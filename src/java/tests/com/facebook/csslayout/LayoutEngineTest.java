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
    style.calculateLayout(CSSConstants.UNDEFINED);
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
        areFloatsEqual(
            a.layout.position[CSSConstants.POSITION_INDEX_TOP],
            b.layout.position[CSSConstants.POSITION_INDEX_TOP]) &&
        areFloatsEqual(
            a.layout.position[CSSConstants.POSITION_INDEX_LEFT],
            b.layout.position[CSSConstants.POSITION_INDEX_LEFT]) &&
        areFloatsEqual(
            a.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH],
            b.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH]) &&
        areFloatsEqual(
            a.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT],
            b.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT]);
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
    }

    test("should layout a single node with width and height", root_node, root_layout);
  }

  @Test
  public void testCase1()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 500;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 250;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 250;
        node_1 = node_0.getChildAt(2);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 125;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 125;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 500;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 500;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 250;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 250;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 750;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 125;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 125;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 500;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 500;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 500;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 250;
          node_2.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 250;
          node_2 = node_1.getChildAt(1);
          node_2.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 250;
          node_2.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 250;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 500;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 500;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 500;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 500;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 250;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 250;
          node_2 = node_1.getChildAt(1);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 250;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 250;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 250;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 10;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 10;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 10;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 10;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 10;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 10;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
    }

    test("should layout node with margin", root_node, root_layout);
  }

  @Test
  public void testCase4()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 10;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 10;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 10;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 10;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 50;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 50;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 50;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 50;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 25;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 25;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 25;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 25;
        node_1 = node_0.getChildAt(2);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 10;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 10;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 10;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 10;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 10;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 50;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 50;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 225;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 25;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 360;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 10;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 300;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 150;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 300;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 150;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 300;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 300;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 150;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 300;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 350;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 200;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 300;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 150;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 200;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 800;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.flex = 1;
          node_2.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.style.flex = 1;
            node_3.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
          }
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
            node_3.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
            node_3.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
            node_3.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 10;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 15;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 50;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 20;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 30;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 10;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 50;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 15;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 170;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 30;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.style.justify_content = CSSJustify.FLEX_START;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 100;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.style.justify_content = CSSJustify.FLEX_END;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 800;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 900;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.style.justify_content = CSSJustify.SPACE_BETWEEN;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 900;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.style.justify_content = CSSJustify.SPACE_AROUND;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 200;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 700;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.style.justify_content = CSSJustify.CENTER;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 400;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 500;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
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
      node_0.style.align_items = CSSAlign.FLEX_START;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 100;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.style.align_items = CSSAlign.CENTER;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 400;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 100;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 450;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.style.align_items = CSSAlign.FLEX_END;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 800;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 100;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 900;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.style.align_items = CSSAlign.FLEX_END;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.align_self = CSSAlign.CENTER;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 800;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 100;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 450;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.style.align_items = CSSAlign.STRETCH;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1000;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 5;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 5;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 5;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 10;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 5;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 100;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
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
      node_0.style.justify_content = CSSJustify.CENTER;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
    }

    test("should layout for center", root_node, root_layout);
  }

  @Test
  public void testCase25()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justify_content = CSSJustify.FLEX_END;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 100;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
        node_1.style.align_items = CSSAlign.FLEX_END;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 10;
          node_2.style.margin[CSSConstants.POSITION_INDEX_TOP] = 10;
          node_2.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 10;
          node_2.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 10;
          node_2 = node_1.getChildAt(1);
          node_2.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 20;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 120;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 20;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 120;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 10;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 10;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
          node_2 = node_1.getChildAt(1);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 20;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 20;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.align_items = CSSAlign.STRETCH;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 10;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 10;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 10;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 10;
    }

    test("should layout node with padding", root_node, root_layout);
  }

  @Test
  public void testCase30()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 10;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 5;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 5;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 5;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 5;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 20;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 10;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 10;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
        node_1.style.align_self = CSSAlign.STRETCH;
        node_1.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 10;
        node_1.style.padding[CSSConstants.POSITION_INDEX_TOP] = 10;
        node_1.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 10;
        node_1.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 20;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 20;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 20;
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
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 50;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 50;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 50;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.align_self = CSSAlign.STRETCH;
        node_1.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 10;
        node_1.style.padding[CSSConstants.POSITION_INDEX_TOP] = 10;
        node_1.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 10;
        node_1.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 120;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 120;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 50;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 50;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 20;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 20;
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
        node_1.style.align_self = CSSAlign.STRETCH;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 16;
          node_2.style.margin[CSSConstants.POSITION_INDEX_TOP] = 16;
          node_2.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 16;
          node_2.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 16;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 32;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 32;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 32;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 32;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 16;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 16;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 5;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
    }

    test("should layout node with top and left", root_node, root_layout);
  }

  @Test
  public void testCase36()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justify_content = CSSJustify.SPACE_AROUND;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 10;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 7.5f;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.position[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = -5;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
    }

    test("should layout node with bottom", root_node, root_layout);
  }

  @Test
  public void testCase38()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = 10;
      node_0.style.position[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 10;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
    }

    test("should layout node with both top and bottom", root_node, root_layout);
  }

  @Test
  public void testCase39()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 500;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 50;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 500;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 250;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 250;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 50;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 250;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 250;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 15;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
        node_1.style.align_self = CSSAlign.CENTER;
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 12;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 12;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 20;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 20;
    }

    test("should work with height smaller than paddingBottom", root_node, root_layout);
  }

  @Test
  public void testCase43()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 20;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 20;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
          node_2.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 400;
        }
        node_1 = node_0.getChildAt(1);
        node_1.style.align_self = CSSAlign.STRETCH;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 400;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 400;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 400;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
        }
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 10;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 5;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.position[CSSConstants.POSITION_INDEX_LEFT] = 10;
        node_1.style.position[CSSConstants.POSITION_INDEX_TOP] = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 10;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 10;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 20;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 20;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 20;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 40;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 40;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 20;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 5;
        node_1.style.position[CSSConstants.POSITION_INDEX_TOP] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 10;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 5;
        node_1.style.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 10;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.justify_content = CSSJustify.SPACE_AROUND;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1 = node_0.getChildAt(1);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 100;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 100;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 700;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 700;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 695;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 700;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 700;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 347.5f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 347.5f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 352.5f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 700;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 700;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 347.5f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 352.5f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 347.5f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 300;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 600;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 300;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 600;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 600;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 600;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 600;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 500;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 500;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 500;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 5;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 5;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 10;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 10;
    }

    test("should layout node with borderWidth", root_node, root_layout);
  }

  @Test
  public void testCase58()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.position[CSSConstants.POSITION_INDEX_TOP] = -1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 2;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 2;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 1;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 6;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.align_self = CSSAlign.STRETCH;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 20;
        node_1.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 20;
        node_1.style.padding[CSSConstants.POSITION_INDEX_TOP] = 20;
        node_1.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 20;
        node_1.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 20;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 50;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 40;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 20;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 40;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 40;
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
        node_1.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 5;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 5;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -8;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 33;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("should layout node with just text", root_node, root_layout);
  }

  @Test
  public void testCase64()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 10;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 10;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("should layout node with text and width", root_node, root_layout);
  }

  @Test
  public void testCase65()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 5;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 5;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 5;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 181;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 28;
    }

    test("should layout node with text, padding and margin", root_node, root_layout);
  }

  @Test
  public void testCase66()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 300;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.align_self = CSSAlign.STRETCH;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.align_self = CSSAlign.STRETCH;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 300;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 300;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 300;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
        node_1.style.flex_direction = CSSFlexDirection.ROW;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 500;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 500;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 500;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 500;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 130;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.align_items = CSSAlign.STRETCH;
        node_1.style.align_self = CSSAlign.STRETCH;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 130;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 36;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 130;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 36;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 130;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 36;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.align_items = CSSAlign.STRETCH;
        node_1.style.align_self = CSSAlign.STRETCH;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 130;
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 36;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 36;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 130;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 36;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 36;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 36;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 10;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 10;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 10;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 10;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 10;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 10;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 10;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 76;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 20;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 20;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 36;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 36;
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
      node_0.style.justify_content = CSSJustify.SPACE_BETWEEN;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 900;
        node_1 = node_0.getChildAt(1);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 900;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 900;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.justify_content = CSSJustify.FLEX_END;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 900;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -700;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 900;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
        node_1.style.flex_direction = CSSFlexDirection.ROW;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 20;
          node_2.style.margin[CSSConstants.POSITION_INDEX_TOP] = 20;
          node_2.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 20;
          node_2.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 20;
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 58;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 58;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 20;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 20;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 171;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 20;
          node_2.style.margin[CSSConstants.POSITION_INDEX_TOP] = 20;
          node_2.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 20;
          node_2.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 20;
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 76;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 200;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 76;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 20;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 20;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 160;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 36;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.style.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.style.position[CSSConstants.POSITION_INDEX_RIGHT] = 0;
        node_1.style.position[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 25;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 25;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 75;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.style.align_items = CSSAlign.STRETCH;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 80;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 7;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 7;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 7;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 7;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 80;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 68;
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
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "loooooooooong with space";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 100;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 36;
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
      node_0.style.justify_content = CSSJustify.FLEX_START;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 620;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 595;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 13;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 7;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 7;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 7;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 7;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 3;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 620;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 595;
    }

    test("Random #0", root_node, root_layout);
  }

  @Test
  public void testCase82()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 603;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 18;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 14;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 2;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = 6;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 6;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -5;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 603;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 54;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #3", root_node, root_layout);
  }

  @Test
  public void testCase85()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.COLUMN;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 255;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -3;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 8;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 255;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 15;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.justify_content = CSSJustify.SPACE_AROUND;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 426;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 497;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 14;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 7;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 2;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = -1;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 426;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 497;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
    }

    test("Random #10", root_node, root_layout);
  }

  @Test
  public void testCase92()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.COLUMN;
      node_0.style.align_items = CSSAlign.FLEX_END;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 179;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 7;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 17;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 16;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = -4;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex_direction = CSSFlexDirection.ROW;
        node_1.style.align_self = CSSAlign.CENTER;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 277;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 6;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -10;
        node_1.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 4;
        node_1.style.padding[CSSConstants.POSITION_INDEX_TOP] = 4;
        node_1.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 4;
        node_1.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 4;
        node_1.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 11;
        node_1.style.border[CSSConstants.POSITION_INDEX_LEFT] = 1;
        node_1.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
        node_1.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 1;
        node_1.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
        node_1.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
        node_1.style.position[CSSConstants.POSITION_INDEX_TOP] = 1;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 7;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -4;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 179;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 52;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 18;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -49.5f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 277;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 28;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #12", root_node, root_layout);
  }

  @Test
  public void testCase94()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.justify_content = CSSJustify.SPACE_AROUND;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 551;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -9;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = -9;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -9;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -9;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 12;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 8;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 12;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -1;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 551;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 19;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.style.flex_direction = CSSFlexDirection.COLUMN;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 809;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 8;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 6;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 16;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 8;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 6;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 809;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.style.justify_content = CSSJustify.FLEX_START;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 5;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 7;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 10;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 8;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 6;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 14;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 10;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
    }

    test("Random #19", root_node, root_layout);
  }

  @Test
  public void testCase101()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 161;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 261;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 3;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 2;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex_direction = CSSFlexDirection.COLUMN;
        node_1.style.flex = 1;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 860;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 424;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 10;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 10;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 10;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 10;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 5;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -7;
        node_1.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 5;
        node_1.style.padding[CSSConstants.POSITION_INDEX_TOP] = 5;
        node_1.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 5;
        node_1.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
        node_1.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 5;
        node_1.style.padding[CSSConstants.POSITION_INDEX_TOP] = 15;
        node_1.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 9;
        node_1.style.border[CSSConstants.POSITION_INDEX_TOP] = 2;
        node_1.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 3;
        node_1.style.position[CSSConstants.POSITION_INDEX_LEFT] = 4;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 3;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 161;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 261;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 10;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 17;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 155;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 424;
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
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 596;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 12;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 16;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 15;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 15;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 15;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 15;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = -7;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 12;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -7;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 596;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 50;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #24", root_node, root_layout);
  }

  @Test
  public void testCase106()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justify_content = CSSJustify.SPACE_AROUND;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 846;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 19;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 19;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 19;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 19;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -7;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 18;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 6;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 19;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -7;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 18;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 846;
    }

    test("Random #25", root_node, root_layout);
  }

  @Test
  public void testCase107()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 726;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 15;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = -1;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 15;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 15;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 726;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 3;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #27", root_node, root_layout);
  }

  @Test
  public void testCase109()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justify_content = CSSJustify.FLEX_START;
      node_0.style.align_items = CSSAlign.STRETCH;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -2;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 19;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = -3;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = -3;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 24;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 9;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #32", root_node, root_layout);
  }

  @Test
  public void testCase114()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.COLUMN;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 315;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = -2;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -4;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 18;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 3;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 4;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = -2;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = -4;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 4;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 21;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 315;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #34", root_node, root_layout);
  }

  @Test
  public void testCase116()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.COLUMN;
      node_0.style.justify_content = CSSJustify.SPACE_BETWEEN;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 819;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 1;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = -3;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 18;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 3;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex_direction = CSSFlexDirection.ROW;
        node_1.style.align_self = CSSAlign.STRETCH;
        node_1.style.flex = 8;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 532;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 8;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 8;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 8;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 8;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 16;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 9;
        node_1.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 7;
        node_1.style.padding[CSSConstants.POSITION_INDEX_TOP] = 7;
        node_1.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 7;
        node_1.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 7;
        node_1.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 8;
        node_1.style.padding[CSSConstants.POSITION_INDEX_TOP] = 5;
        node_1.style.position[CSSConstants.POSITION_INDEX_LEFT] = 4;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = -3;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 6;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 579;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 819;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 8;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 40;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 532;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 802;
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
      node_0.style.align_items = CSSAlign.CENTER;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 13;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 13;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 13;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 13;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 1;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = 8;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 21;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 13;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 1;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 1;
    }

    test("Random #36", root_node, root_layout);
  }

  @Test
  public void testCase118()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.align_items = CSSAlign.FLEX_END;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 632;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 907;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -3;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 5;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 1;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 6;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 3;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = -9;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = 4;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 9;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -12;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 632;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 907;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #41", root_node, root_layout);
  }

  @Test
  public void testCase123()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justify_content = CSSJustify.FLEX_END;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 398;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 198;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 9;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = -9;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 13;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 6;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = -2;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = -2;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = -11;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 7;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 398;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 198;
    }

    test("Random #42", root_node, root_layout);
  }

  @Test
  public void testCase124()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.COLUMN;
      node_0.style.justify_content = CSSJustify.SPACE_AROUND;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 514;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 5;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 3;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 6;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 5;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 21;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 6;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 514;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.style.justify_content = CSSJustify.CENTER;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 952;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -2;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = -2;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -2;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -2;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 2;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 12;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 3;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = -10;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = -9;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -2;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 952;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 3;
    }

    test("Random #45", root_node, root_layout);
  }

  @Test
  public void testCase127()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 937;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = -2;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -2;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 937;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 19;
    }

    test("Random #46", root_node, root_layout);
  }

  @Test
  public void testCase128()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 530;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 726;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -5;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = -5;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -5;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -5;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 10;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 3;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex_direction = CSSFlexDirection.ROW;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 195;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = -2;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 15;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 12;
        node_1.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 14;
        node_1.style.border[CSSConstants.POSITION_INDEX_TOP] = 2;
        node_1.style.position[CSSConstants.POSITION_INDEX_TOP] = -1;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
        node_1 = node_0.getChildAt(1);
        node_1.style.justify_content = CSSJustify.SPACE_BETWEEN;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 638;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 753;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 19;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 3;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 10;
        node_1.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 14;
        node_1.style.padding[CSSConstants.POSITION_INDEX_TOP] = 14;
        node_1.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 14;
        node_1.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 14;
        node_1.style.padding[CSSConstants.POSITION_INDEX_TOP] = 18;
        node_1.style.position[CSSConstants.POSITION_INDEX_LEFT] = -7;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "loooooooooong with space";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = -5;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 10;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 530;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 726;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 2;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 195;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 20;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 6;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 224;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 638;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 753;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #48", root_node, root_layout);
  }

  @Test
  public void testCase130()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.COLUMN;
      node_0.style.justify_content = CSSJustify.FLEX_START;
      node_0.style.align_items = CSSAlign.STRETCH;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 194;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 1;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = -7;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -6;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 18;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 18;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 18;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 18;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = -7;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 36;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 194;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 803;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 826;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 19;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -3;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -6;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 2;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = -6;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 13;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 803;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 826;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #54", root_node, root_layout);
  }

  @Test
  public void testCase136()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 134;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 394;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 9;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 9;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 17;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = -2;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 7;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 16;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 134;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 394;
    }

    test("Random #55", root_node, root_layout);
  }

  @Test
  public void testCase137()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.COLUMN;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 216;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 721;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = -6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 2;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = -1;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -8;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -10;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 19;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = -1;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 2;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 216;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 721;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #57", root_node, root_layout);
  }

  @Test
  public void testCase139()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.align_items = CSSAlign.FLEX_START;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 173;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 11;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 11;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 11;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 11;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 10;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 17;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 15;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 5;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 8;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 17;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 18;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 173;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 5;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #61", root_node, root_layout);
  }

  @Test
  public void testCase143()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 671;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 603;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 14;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -10;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 17;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 14;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 671;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 603;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #66", root_node, root_layout);
  }

  @Test
  public void testCase148()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justify_content = CSSJustify.SPACE_BETWEEN;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 516;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 712;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 15;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 15;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 15;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 15;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -8;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 11;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 17;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 17;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 17;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 17;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 4;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = 4;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 19;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -8;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 516;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 712;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.style.flex_direction = CSSFlexDirection.COLUMN;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 486;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 19;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 19;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 19;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 19;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 10;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 3;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 8;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = -6;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex_direction = CSSFlexDirection.ROW;
        node_1.style.justify_content = CSSJustify.FLEX_START;
        node_1.style.align_items = CSSAlign.STRETCH;
        node_1.style.flex = 1;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 482;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 818;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 14;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -9;
        node_1.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 14;
        node_1.style.border[CSSConstants.POSITION_INDEX_LEFT] = 1;
        node_1.style.border[CSSConstants.POSITION_INDEX_TOP] = 2;
        node_1.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 0;
        node_1.style.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 13;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 24;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 486;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 812;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 3;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 482;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 818;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
            node_3.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
            node_3.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
            node_3.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.style.flex_direction = CSSFlexDirection.COLUMN;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 12;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 12;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 12;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 12;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -9;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 10;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 18;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 10;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 1;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = 7;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.align_items = CSSAlign.FLEX_START;
        node_1.style.align_self = CSSAlign.CENTER;
        node_1.style.position_type = CSSPositionType.ABSOLUTE;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -6;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = -6;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -6;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -6;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 10;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
        node_1.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 15;
        node_1.style.padding[CSSConstants.POSITION_INDEX_TOP] = 15;
        node_1.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 15;
        node_1.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 15;
        node_1.style.border[CSSConstants.POSITION_INDEX_LEFT] = 1;
        node_1.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
        node_1.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 1;
        node_1.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
        node_1.style.border[CSSConstants.POSITION_INDEX_LEFT] = 3;
        node_1.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
        node_1.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
        node_1.style.position[CSSConstants.POSITION_INDEX_LEFT] = -7;
        node_1.style.position[CSSConstants.POSITION_INDEX_TOP] = -9;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.flex_direction = CSSFlexDirection.ROW;
          node_2.style.justify_content = CSSJustify.CENTER;
          node_2.style.align_items = CSSAlign.FLEX_END;
          node_2.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 6;
          node_2.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 16;
          node_2.style.padding[CSSConstants.POSITION_INDEX_TOP] = 6;
          node_2.style.border[CSSConstants.POSITION_INDEX_LEFT] = 2;
          node_2.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 19;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -9;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 20;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 12;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = -15;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -12;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 42;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 54;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[CSSConstants.POSITION_INDEX_TOP] = 16;
          node_2.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 18;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 2;
          node_2.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 7;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #74", root_node, root_layout);
  }

  @Test
  public void testCase156()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.align_items = CSSAlign.FLEX_END;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 332;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 18;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 18;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 18;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 18;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -5;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 12;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 12;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 12;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 12;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = -9;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = -5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex_direction = CSSFlexDirection.ROW;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 818;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 543;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -2;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = -2;
        node_1.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -2;
        node_1.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -2;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 8;
        node_1.style.margin[CSSConstants.POSITION_INDEX_TOP] = 14;
        node_1.style.padding[CSSConstants.POSITION_INDEX_TOP] = 10;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 13;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 9;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 332;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 571;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = 27;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 21;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 818;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 543;
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
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 885;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 13;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -2;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 7;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = -4;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 9;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 7;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 885;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #78", root_node, root_layout);
  }

  @Test
  public void testCase160()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justify_content = CSSJustify.FLEX_END;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 332;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 7;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 7;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 7;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 7;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 17;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -6;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 16;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 6;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 1;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = -2;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 15;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 8;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 20;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 332;
    }

    test("Random #79", root_node, root_layout);
  }

  @Test
  public void testCase161()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.COLUMN;
      node_0.style.justify_content = CSSJustify.SPACE_BETWEEN;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 410;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 614;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -2;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = -2;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -2;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -2;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 3;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = -7;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 6;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 17;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -2;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 410;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 614;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
    }

    test("Random #82", root_node, root_layout);
  }

  @Test
  public void testCase164()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.COLUMN;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 978;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 446;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 10;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 10;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 10;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 10;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -4;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = -4;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = -4;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.align_self = CSSAlign.FLEX_END;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 256;
        node_1.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 883;
        node_1.style.margin[CSSConstants.POSITION_INDEX_LEFT] = -8;
        node_1.style.border[CSSConstants.POSITION_INDEX_LEFT] = 0;
        node_1.style.border[CSSConstants.POSITION_INDEX_TOP] = 3;
        node_1.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
        node_1.style.position[CSSConstants.POSITION_INDEX_LEFT] = 8;
        node_1.style.position[CSSConstants.POSITION_INDEX_TOP] = -3;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "small";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = -4;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = -8;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 978;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 446;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[CSSConstants.POSITION_INDEX_TOP] = -3;
        node_1.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 730;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 256;
        node_1.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 883;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #85", root_node, root_layout);
  }

  @Test
  public void testCase167()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justify_content = CSSJustify.CENTER;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = -4;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 6;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 11;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 7;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 7;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 11;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 3;
    }

    test("Random #86", root_node, root_layout);
  }

  @Test
  public void testCase168()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justify_content = CSSJustify.FLEX_START;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 335;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 17;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 17;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 17;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 17;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 16;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 9;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 14;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = 7;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 24;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 16;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 335;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 32;
    }

    test("Random #87", root_node, root_layout);
  }

  @Test
  public void testCase169()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justify_content = CSSJustify.SPACE_AROUND;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 903;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 7;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 7;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 7;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 7;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 13;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 7;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 7;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 903;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #88", root_node, root_layout);
  }

  @Test
  public void testCase170()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 380;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 824;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 13;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 13;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 13;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 13;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 18;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 4;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 6;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 17;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 7;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 0;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = -6;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 13;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 7;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 380;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 824;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #93", root_node, root_layout);
  }

  @Test
  public void testCase175()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justify_content = CSSJustify.FLEX_END;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 922;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = 6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_RIGHT] = 6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 6;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 18;
      node_0.style.margin[CSSConstants.POSITION_INDEX_TOP] = -10;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 15;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 3;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_RIGHT] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_LEFT] = 2;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = -10;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 18;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 922;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 22;
    }

    test("Random #94", root_node, root_layout);
  }

  @Test
  public void testCase176()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justify_content = CSSJustify.CENTER;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 779;
      node_0.style.margin[CSSConstants.POSITION_INDEX_LEFT] = 3;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 19;
      node_0.style.padding[CSSConstants.POSITION_INDEX_LEFT] = 17;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 17;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 17;
      node_0.style.padding[CSSConstants.POSITION_INDEX_BOTTOM] = 17;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 15;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 3;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = 9;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "loooooooooong with space";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 9;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 6;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 779;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 50;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 34.671875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 0;
    }

    test("Random #97", root_node, root_layout);
  }

  @Test
  public void testCase179()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flex_direction = CSSFlexDirection.ROW;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 770;
      node_0.style.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 873;
      node_0.style.margin[CSSConstants.POSITION_INDEX_BOTTOM] = 15;
      node_0.style.padding[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.style.padding[CSSConstants.POSITION_INDEX_RIGHT] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.style.border[CSSConstants.POSITION_INDEX_BOTTOM] = 0;
      node_0.style.position[CSSConstants.POSITION_INDEX_LEFT] = 9;
      node_0.style.position[CSSConstants.POSITION_INDEX_TOP] = 1;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 1;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 9;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 770;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 873;
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
      node_0.layout.position[CSSConstants.POSITION_INDEX_TOP] = 0;
      node_0.layout.position[CSSConstants.POSITION_INDEX_LEFT] = 0;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = 172.421875f;
      node_0.layout.dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = 18;
    }

    test("Random #99", root_node, root_layout);
  }
}
