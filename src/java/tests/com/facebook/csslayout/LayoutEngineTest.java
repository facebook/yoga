/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
package com.facebook.csslayout;

import org.junit.Assert;
import org.junit.Test;

/**
 * Tests for {@link LayoutEngine}
 */
public class LayoutEngineTest {

  private static final CSSNode.MeasureFunction sTestMeasureFunction =
      new CSSNode.MeasureFunction() {

    @Override
    public void measure(CSSNode node, float width, MeasureOutput measureOutput) {
      if (CSSConstants.isUndefined(width)) {
        width = 10000000;
      }

      TestCSSNode testNode = (TestCSSNode) node;
      if (testNode.context.equals(TestConstants.SMALL_TEXT)) {
        measureOutput.width = Math.min(width, TestConstants.SMALL_WIDTH);
        measureOutput.height = TestConstants.SMALL_HEIGHT;
      } else if (testNode.context.equals(TestConstants.LONG_TEXT)) {
        measureOutput.width = width >= TestConstants.BIG_WIDTH ?
            TestConstants.BIG_WIDTH : Math.max(TestConstants.BIG_MIN_WIDTH, width);
        measureOutput.height = width >= TestConstants.BIG_WIDTH ?
            TestConstants.SMALL_HEIGHT : TestConstants.BIG_HEIGHT;
      } else {
        throw new RuntimeException("Got unknown test: " + testNode.context);
      }
    }
  };

  private static class TestCSSNode extends CSSNode {

    public String context = null;

    public TestCSSNode getChildAt(int i) {
      return (TestCSSNode) super.getChildAt(i);
    }
  }

  private static void test(String message, CSSNode style, CSSNode expectedLayout) {
    CSSLayoutContext layoutContext = new CSSLayoutContext();
    style.calculateLayout(layoutContext);
    assertLayoutsEqual(message, style, expectedLayout);
  }

  private static void addChildren(TestCSSNode node, int numChildren) {
    for (int i = 0; i < numChildren; i++) {
      node.addChildAt(new TestCSSNode(), i);
    }
  }

  private static void assertLayoutsEqual(String message, CSSNode actual, CSSNode expected) {
    Assert.assertTrue(
        message + "\nActual:\n" + actual.toString() + "\nExpected:\n" + expected.toString(),
        areLayoutsEqual(actual, expected));
  }

  private static boolean areLayoutsEqual(CSSNode a, CSSNode b) {
    boolean doNodesHaveSameLayout =
        areFloatsEqual(a.layout.left, b.layout.left) &&
        areFloatsEqual(a.layout.top, b.layout.top) &&
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

  /** START_GENERATED **/
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 500;
        node_1.layout.left = 0;
        node_1.layout.width = 250;
        node_1.layout.height = 250;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 750;
        node_1.layout.left = 0;
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
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 500;
        node_1.layout.left = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 250;
        node_1.layout.left = 0;
        node_1.layout.width = 250;
        node_1.layout.height = 250;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 125;
        node_1.layout.left = 0;
        node_1.layout.width = 125;
        node_1.layout.height = 125;
      }
    }

    test("should layout node with children in reverse", root_node, root_layout);
  }

  @Test
  public void testCase3()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 500;
        node_1.layout.left = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 500;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 250;
          node_2.layout.height = 250;
          node_2 = node_1.getChildAt(1);
          node_2.layout.top = 250;
          node_2.layout.left = 0;
          node_2.layout.width = 250;
          node_2.layout.height = 250;
        }
      }
    }

    test("should layout node with nested children", root_node, root_layout);
  }

  @Test
  public void testCase4()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 500;
        node_1.style.height = 500;
        node_1 = node_0.getChildAt(1);
        node_1.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 500;
        node_1.layout.left = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 500;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 250;
          node_2.layout.left = 0;
          node_2.layout.width = 250;
          node_2.layout.height = 250;
          node_2 = node_1.getChildAt(1);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 250;
          node_2.layout.height = 250;
        }
      }
    }

    test("should layout node with nested children in reverse", root_node, root_layout);
  }

  @Test
  public void testCase5()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 200;
      node_0.setMargin(Spacing.LEFT, 10);
      node_0.setMargin(Spacing.TOP, 10);
      node_0.setMargin(Spacing.RIGHT, 10);
      node_0.setMargin(Spacing.BOTTOM, 10);
      node_0.setMargin(Spacing.START, 10);
      node_0.setMargin(Spacing.END, 10);
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 10;
      node_0.layout.left = 10;
      node_0.layout.width = 100;
      node_0.layout.height = 200;
    }

    test("should layout node with margin", root_node, root_layout);
  }

  @Test
  public void testCase6()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      node_0.setMargin(Spacing.LEFT, 10);
      node_0.setMargin(Spacing.TOP, 10);
      node_0.setMargin(Spacing.RIGHT, 10);
      node_0.setMargin(Spacing.BOTTOM, 10);
      node_0.setMargin(Spacing.START, 10);
      node_0.setMargin(Spacing.END, 10);
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.setMargin(Spacing.LEFT, 50);
        node_1.setMargin(Spacing.TOP, 50);
        node_1.setMargin(Spacing.RIGHT, 50);
        node_1.setMargin(Spacing.BOTTOM, 50);
        node_1.setMargin(Spacing.START, 50);
        node_1.setMargin(Spacing.END, 50);
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.setMargin(Spacing.LEFT, 25);
        node_1.setMargin(Spacing.TOP, 25);
        node_1.setMargin(Spacing.RIGHT, 25);
        node_1.setMargin(Spacing.BOTTOM, 25);
        node_1.setMargin(Spacing.START, 25);
        node_1.setMargin(Spacing.END, 25);
        node_1 = node_0.getChildAt(2);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 10;
      node_0.layout.left = 10;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 50;
        node_1.layout.left = 50;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 225;
        node_1.layout.left = 25;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 360;
        node_1.layout.left = 10;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with several children", root_node, root_layout);
  }

  @Test
  public void testCase7()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      node_0.setMargin(Spacing.LEFT, 10);
      node_0.setMargin(Spacing.TOP, 10);
      node_0.setMargin(Spacing.RIGHT, 10);
      node_0.setMargin(Spacing.BOTTOM, 10);
      node_0.setMargin(Spacing.START, 10);
      node_0.setMargin(Spacing.END, 10);
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.setMargin(Spacing.LEFT, 50);
        node_1.setMargin(Spacing.TOP, 50);
        node_1.setMargin(Spacing.RIGHT, 50);
        node_1.setMargin(Spacing.BOTTOM, 50);
        node_1.setMargin(Spacing.START, 50);
        node_1.setMargin(Spacing.END, 50);
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.setMargin(Spacing.LEFT, 25);
        node_1.setMargin(Spacing.TOP, 25);
        node_1.setMargin(Spacing.RIGHT, 25);
        node_1.setMargin(Spacing.BOTTOM, 25);
        node_1.setMargin(Spacing.START, 25);
        node_1.setMargin(Spacing.END, 25);
        node_1 = node_0.getChildAt(2);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 10;
      node_0.layout.left = 10;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 850;
        node_1.layout.left = 50;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 675;
        node_1.layout.left = 25;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 540;
        node_1.layout.left = 10;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with several children in reverse", root_node, root_layout);
  }

  @Test
  public void testCase8()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.ROW_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 100;
        node_1.layout.width = 300;
        node_1.layout.height = 150;
      }
    }

    test("should layout rtl with reverse correctly", root_node, root_layout);
  }

  @Test
  public void testCase9()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 100;
        node_1.layout.width = 300;
        node_1.layout.height = 150;
      }
    }

    test("should layout node with row flex direction", root_node, root_layout);
  }

  @Test
  public void testCase10()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 900;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 600;
        node_1.layout.width = 300;
        node_1.layout.height = 150;
      }
    }

    test("should layout node with row flex direction in rtl", root_node, root_layout);
  }

  @Test
  public void testCase11()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 350;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 200;
        node_1.layout.left = 0;
        node_1.layout.width = 300;
        node_1.layout.height = 150;
      }
    }

    test("should layout node based on children main dimensions", root_node, root_layout);
  }

  @Test
  public void testCase12()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 350;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 150;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 300;
        node_1.layout.height = 150;
      }
    }

    test("should layout node based on children main dimensions in reverse", root_node, root_layout);
  }

  @Test
  public void testCase13()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 200;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 800;
      }
    }

    test("should layout node with just flex", root_node, root_layout);
  }

  @Test
  public void testCase14()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 800;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 800;
      }
    }

    test("should layout node with just flex in reverse", root_node, root_layout);
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 1000;
        node_1.layout.height = 1000;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 1000;
          node_2.layout.height = 1000;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.layout.top = 0;
            node_3.layout.left = 0;
            node_3.layout.width = 1000;
            node_3.layout.height = 1000;
          }
        }
      }
    }

    test("should layout node with flex recursively", root_node, root_layout);
  }

  @Test
  public void testCase16()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
        node_1.style.flex = 1;
        node_1.style.width = 1000;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
          node_2.style.flex = 1;
          node_2.style.width = 1000;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
            node_3.style.flex = 1;
            node_3.style.width = 1000;
          }
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 1000;
        node_1.layout.height = 1000;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 1000;
          node_2.layout.height = 1000;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.layout.top = 0;
            node_3.layout.left = 0;
            node_3.layout.width = 1000;
            node_3.layout.height = 1000;
          }
        }
      }
    }

    test("should layout node with flex recursively in reverse", root_node, root_layout);
  }

  @Test
  public void testCase17()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      node_0.setMargin(Spacing.LEFT, 5);
      node_0.setMargin(Spacing.TOP, 10);
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.setMargin(Spacing.LEFT, 15);
        node_1.setMargin(Spacing.TOP, 50);
        node_1.setMargin(Spacing.BOTTOM, 20);
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.setMargin(Spacing.LEFT, 30);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 10;
      node_0.layout.left = 5;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 50;
        node_1.layout.left = 15;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 170;
        node_1.layout.left = 30;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with targeted margin", root_node, root_layout);
  }

  @Test
  public void testCase18()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
      node_0.style.width = 1000;
      node_0.style.height = 1000;
      node_0.setMargin(Spacing.LEFT, 5);
      node_0.setMargin(Spacing.TOP, 10);
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.setMargin(Spacing.LEFT, 15);
        node_1.setMargin(Spacing.TOP, 50);
        node_1.setMargin(Spacing.BOTTOM, 20);
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.setMargin(Spacing.LEFT, 30);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 10;
      node_0.layout.left = 5;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 880;
        node_1.layout.left = 15;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 730;
        node_1.layout.left = 30;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with targeted margin in reverse", root_node, root_layout);
  }

  @Test
  public void testCase19()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: flex-start", root_node, root_layout);
  }

  @Test
  public void testCase20()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 900;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 800;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: flex-start in reverse", root_node, root_layout);
  }

  @Test
  public void testCase21()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 800;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 900;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: flex-end", root_node, root_layout);
  }

  @Test
  public void testCase22()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: flex-end in reverse", root_node, root_layout);
  }

  @Test
  public void testCase23()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 900;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: space-between", root_node, root_layout);
  }

  @Test
  public void testCase24()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 900;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: space-between in reverse", root_node, root_layout);
  }

  @Test
  public void testCase25()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 200;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 700;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: space-around", root_node, root_layout);
  }

  @Test
  public void testCase26()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 700;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 200;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: space-around in reverse", root_node, root_layout);
  }

  @Test
  public void testCase27()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 400;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 500;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: center", root_node, root_layout);
  }

  @Test
  public void testCase28()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 500;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 400;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with justifyContent: center in reverse", root_node, root_layout);
  }

  @Test
  public void testCase29()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 1000;
      }
    }

    test("should layout node with flex override height", root_node, root_layout);
  }

  @Test
  public void testCase30()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignItems: flex-start", root_node, root_layout);
  }

  @Test
  public void testCase31()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 900;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 800;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignItems: flex-start in reverse", root_node, root_layout);
  }

  @Test
  public void testCase32()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 400;
        node_1.layout.width = 200;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 100;
        node_1.layout.left = 450;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignItems: center", root_node, root_layout);
  }

  @Test
  public void testCase33()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 900;
        node_1.layout.left = 400;
        node_1.layout.width = 200;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 800;
        node_1.layout.left = 450;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignItems: center in reverse", root_node, root_layout);
  }

  @Test
  public void testCase34()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 800;
        node_1.layout.width = 200;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 100;
        node_1.layout.left = 900;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignItems: flex-end", root_node, root_layout);
  }

  @Test
  public void testCase35()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 900;
        node_1.layout.left = 800;
        node_1.layout.width = 200;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 800;
        node_1.layout.left = 900;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignItems: flex-end in reverse", root_node, root_layout);
  }

  @Test
  public void testCase36()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 800;
        node_1.layout.width = 200;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 100;
        node_1.layout.left = 450;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignSelf overrides alignItems", root_node, root_layout);
  }

  @Test
  public void testCase37()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 900;
        node_1.layout.left = 800;
        node_1.layout.width = 200;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 800;
        node_1.layout.left = 450;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignSelf overrides alignItems in reverse", root_node, root_layout);
  }

  @Test
  public void testCase38()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 1000;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignItem: stretch", root_node, root_layout);
  }

  @Test
  public void testCase39()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 900;
        node_1.layout.left = 0;
        node_1.layout.width = 1000;
        node_1.layout.height = 100;
      }
    }

    test("should layout node with alignItem: stretch in reverse", root_node, root_layout);
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
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout empty node", root_node, root_layout);
  }

  @Test
  public void testCase41()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout empty node in reverse", root_node, root_layout);
  }

  @Test
  public void testCase42()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMargin(Spacing.LEFT, 5);
        node_1.setMargin(Spacing.TOP, 5);
        node_1.setMargin(Spacing.RIGHT, 5);
        node_1.setMargin(Spacing.BOTTOM, 5);
        node_1.setMargin(Spacing.START, 5);
        node_1.setMargin(Spacing.END, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 5;
        node_1.layout.left = 5;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout child with margin", root_node, root_layout);
  }

  @Test
  public void testCase43()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMargin(Spacing.LEFT, 5);
        node_1.setMargin(Spacing.TOP, 5);
        node_1.setMargin(Spacing.RIGHT, 5);
        node_1.setMargin(Spacing.BOTTOM, 5);
        node_1.setMargin(Spacing.START, 5);
        node_1.setMargin(Spacing.END, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 5;
        node_1.layout.left = 5;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout child with margin in reverse", root_node, root_layout);
  }

  @Test
  public void testCase44()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 200;
      }
    }

    test("should not shrink children if not enough space", root_node, root_layout);
  }

  @Test
  public void testCase45()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = -200;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 200;
      }
    }

    test("should not shrink children if not enough space in reverse", root_node, root_layout);
  }

  @Test
  public void testCase46()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.CENTER;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("should layout for center", root_node, root_layout);
  }

  @Test
  public void testCase47()
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
        node_1.setMargin(Spacing.TOP, 10);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout flex-end taking into account margin", root_node, root_layout);
  }

  @Test
  public void testCase48()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
      node_0.style.justifyContent = CSSJustify.FLEX_END;
      node_0.style.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMargin(Spacing.TOP, 10);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 10;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout flex-end taking into account margin in reverse", root_node, root_layout);
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
        node_1.style.alignItems = CSSAlign.FLEX_END;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.setMargin(Spacing.LEFT, 10);
          node_2.setMargin(Spacing.TOP, 10);
          node_2.setMargin(Spacing.RIGHT, 10);
          node_2.setMargin(Spacing.BOTTOM, 10);
          node_2.setMargin(Spacing.START, 10);
          node_2.setMargin(Spacing.END, 10);
          node_2 = node_1.getChildAt(1);
          node_2.style.height = 100;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 20;
      node_0.layout.height = 120;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 20;
        node_1.layout.height = 120;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 10;
          node_2.layout.left = 10;
          node_2.layout.width = 0;
          node_2.layout.height = 0;
          node_2 = node_1.getChildAt(1);
          node_2.layout.top = 20;
          node_2.layout.left = 20;
          node_2.layout.width = 0;
          node_2.layout.height = 100;
        }
      }
    }

    test("should layout alignItems with margin", root_node, root_layout);
  }

  @Test
  public void testCase50()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
        node_1.style.alignItems = CSSAlign.FLEX_END;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.setMargin(Spacing.LEFT, 10);
          node_2.setMargin(Spacing.TOP, 10);
          node_2.setMargin(Spacing.RIGHT, 10);
          node_2.setMargin(Spacing.BOTTOM, 10);
          node_2.setMargin(Spacing.START, 10);
          node_2.setMargin(Spacing.END, 10);
          node_2 = node_1.getChildAt(1);
          node_2.style.height = 100;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 20;
      node_0.layout.height = 120;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 20;
        node_1.layout.height = 120;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 110;
          node_2.layout.left = 10;
          node_2.layout.width = 0;
          node_2.layout.height = 0;
          node_2 = node_1.getChildAt(1);
          node_2.layout.top = 0;
          node_2.layout.left = 20;
          node_2.layout.width = 0;
          node_2.layout.height = 100;
        }
      }
    }

    test("should layout alignItems with margin in reverse", root_node, root_layout);
  }

  @Test
  public void testCase51()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout flex inside of an empty element", root_node, root_layout);
  }

  @Test
  public void testCase52()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.STRETCH;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMargin(Spacing.LEFT, 10);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 10;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout alignItems stretch and margin", root_node, root_layout);
  }

  @Test
  public void testCase53()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
      node_0.style.alignItems = CSSAlign.STRETCH;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMargin(Spacing.LEFT, 10);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 10;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout alignItems stretch and margin in reverse", root_node, root_layout);
  }

  @Test
  public void testCase54()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setPadding(Spacing.LEFT, 5);
      node_0.setPadding(Spacing.TOP, 5);
      node_0.setPadding(Spacing.RIGHT, 5);
      node_0.setPadding(Spacing.BOTTOM, 5);
      node_0.setPadding(Spacing.START, 5);
      node_0.setPadding(Spacing.END, 5);
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
    }

    test("should layout node with padding", root_node, root_layout);
  }

  @Test
  public void testCase55()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setPadding(Spacing.LEFT, 5);
      node_0.setPadding(Spacing.TOP, 5);
      node_0.setPadding(Spacing.RIGHT, 5);
      node_0.setPadding(Spacing.BOTTOM, 5);
      node_0.setPadding(Spacing.START, 5);
      node_0.setPadding(Spacing.END, 5);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 5;
        node_1.layout.left = 5;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with padding and a child", root_node, root_layout);
  }

  @Test
  public void testCase56()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setPadding(Spacing.LEFT, 5);
      node_0.setPadding(Spacing.TOP, 5);
      node_0.setPadding(Spacing.RIGHT, 5);
      node_0.setPadding(Spacing.BOTTOM, 5);
      node_0.setPadding(Spacing.START, 5);
      node_0.setPadding(Spacing.END, 5);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMargin(Spacing.LEFT, 5);
        node_1.setMargin(Spacing.TOP, 5);
        node_1.setMargin(Spacing.RIGHT, 5);
        node_1.setMargin(Spacing.BOTTOM, 5);
        node_1.setMargin(Spacing.START, 5);
        node_1.setMargin(Spacing.END, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 20;
      node_0.layout.height = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 10;
        node_1.layout.left = 10;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with padding and a child with margin", root_node, root_layout);
  }

  @Test
  public void testCase57()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        node_1.setPadding(Spacing.LEFT, 10);
        node_1.setPadding(Spacing.TOP, 10);
        node_1.setPadding(Spacing.RIGHT, 10);
        node_1.setPadding(Spacing.BOTTOM, 10);
        node_1.setPadding(Spacing.START, 10);
        node_1.setPadding(Spacing.END, 10);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 20;
      node_0.layout.height = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 20;
        node_1.layout.height = 20;
      }
    }

    test("should layout node with padding and stretch", root_node, root_layout);
  }

  @Test
  public void testCase58()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setPadding(Spacing.LEFT, 50);
      node_0.setPadding(Spacing.TOP, 50);
      node_0.setPadding(Spacing.RIGHT, 50);
      node_0.setPadding(Spacing.BOTTOM, 50);
      node_0.setPadding(Spacing.START, 50);
      node_0.setPadding(Spacing.END, 50);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        node_1.setPadding(Spacing.LEFT, 10);
        node_1.setPadding(Spacing.TOP, 10);
        node_1.setPadding(Spacing.RIGHT, 10);
        node_1.setPadding(Spacing.BOTTOM, 10);
        node_1.setPadding(Spacing.START, 10);
        node_1.setPadding(Spacing.END, 10);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 120;
      node_0.layout.height = 120;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 50;
        node_1.layout.left = 50;
        node_1.layout.width = 20;
        node_1.layout.height = 20;
      }
    }

    test("should layout node with inner & outer padding and stretch", root_node, root_layout);
  }

  @Test
  public void testCase59()
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
          node_2.setMargin(Spacing.LEFT, 16);
          node_2.setMargin(Spacing.TOP, 16);
          node_2.setMargin(Spacing.RIGHT, 16);
          node_2.setMargin(Spacing.BOTTOM, 16);
          node_2.setMargin(Spacing.START, 16);
          node_2.setMargin(Spacing.END, 16);
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 32;
      node_0.layout.height = 32;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 32;
        node_1.layout.height = 32;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 16;
          node_2.layout.left = 16;
          node_2.layout.width = 0;
          node_2.layout.height = 0;
        }
      }
    }

    test("should layout node with stretch and child with margin", root_node, root_layout);
  }

  @Test
  public void testCase60()
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
      node_0.layout.top = 5;
      node_0.layout.left = 5;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("should layout node with top and left", root_node, root_layout);
  }

  @Test
  public void testCase61()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_AROUND;
      node_0.style.height = 10;
      node_0.setPadding(Spacing.TOP, 5);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 7.5f;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with height, padding and space-around", root_node, root_layout);
  }

  @Test
  public void testCase62()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.positionBottom = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = -5;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("should layout node with bottom", root_node, root_layout);
  }

  @Test
  public void testCase63()
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
      node_0.layout.top = 10;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
    }

    test("should layout node with both top and bottom", root_node, root_layout);
  }

  @Test
  public void testCase64()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 500;
      node_0.layout.height = 0;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 250;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 250;
        node_1.layout.width = 50;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 0;
        node_1.layout.left = 250;
        node_1.layout.width = 250;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with position: absolute", root_node, root_layout);
  }

  @Test
  public void testCase65()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.setMargin(Spacing.RIGHT, 15);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with child with position: absolute and margin", root_node, root_layout);
  }

  @Test
  public void testCase66()
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
        node_1.setPadding(Spacing.RIGHT, 12);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 12;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with position: absolute, padding and alignSelf: center", root_node, root_layout);
  }

  @Test
  public void testCase67()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.height = 5;
      node_0.setPadding(Spacing.BOTTOM, 20);
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 20;
    }

    test("should work with height smaller than paddingBottom", root_node, root_layout);
  }

  @Test
  public void testCase68()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 5;
      node_0.setPadding(Spacing.LEFT, 20);
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 20;
      node_0.layout.height = 0;
    }

    test("should work with width smaller than paddingLeft", root_node, root_layout);
  }

  @Test
  public void testCase69()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 400;
      node_0.layout.height = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 400;
        node_1.layout.height = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 400;
          node_2.layout.height = 0;
        }
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with specified width and stretch", root_node, root_layout);
  }

  @Test
  public void testCase70()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setPadding(Spacing.LEFT, 5);
      node_0.setPadding(Spacing.TOP, 5);
      node_0.setPadding(Spacing.RIGHT, 5);
      node_0.setPadding(Spacing.BOTTOM, 5);
      node_0.setPadding(Spacing.START, 5);
      node_0.setPadding(Spacing.END, 5);
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 5;
        node_1.layout.left = 5;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with padding and child with position absolute", root_node, root_layout);
  }

  @Test
  public void testCase71()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 10;
        node_1.layout.left = 10;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with position absolute, top and left", root_node, root_layout);
  }

  @Test
  public void testCase72()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setPadding(Spacing.LEFT, 20);
      node_0.setPadding(Spacing.TOP, 20);
      node_0.setPadding(Spacing.RIGHT, 20);
      node_0.setPadding(Spacing.BOTTOM, 20);
      node_0.setPadding(Spacing.START, 20);
      node_0.setPadding(Spacing.END, 20);
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 40;
      node_0.layout.height = 40;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 20;
        node_1.layout.left = 5;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with padding and child position absolute, left", root_node, root_layout);
  }

  @Test
  public void testCase73()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.setMargin(Spacing.TOP, 5);
        node_1.style.positionTop = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 10;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with position: absolute, top and marginTop", root_node, root_layout);
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
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.setMargin(Spacing.LEFT, 5);
        node_1.style.positionLeft = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 10;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with position: absolute, left and marginLeft", root_node, root_layout);
  }

  @Test
  public void testCase75()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with space-around and child position absolute", root_node, root_layout);
  }

  @Test
  public void testCase76()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with space-around and child position absolute in reverse", root_node, root_layout);
  }

  @Test
  public void testCase77()
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
        node_1.setMargin(Spacing.LEFT, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 700;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 5;
        node_1.layout.width = 695;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with flex and main margin", root_node, root_layout);
  }

  @Test
  public void testCase78()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 700;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.setMargin(Spacing.RIGHT, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 700;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 695;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with flex and main margin in rtl", root_node, root_layout);
  }

  @Test
  public void testCase79()
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
        node_1.setPadding(Spacing.RIGHT, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 700;
      node_0.layout.height = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 347.5f;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 347.5f;
        node_1.layout.width = 352.5f;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with multiple flex and padding", root_node, root_layout);
  }

  @Test
  public void testCase80()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 700;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.setPadding(Spacing.LEFT, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 700;
      node_0.layout.height = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 352.5f;
        node_1.layout.width = 347.5f;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 352.5f;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with multiple flex and padding in rtl", root_node, root_layout);
  }

  @Test
  public void testCase81()
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
        node_1.setMargin(Spacing.LEFT, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 700;
      node_0.layout.height = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 347.5f;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 352.5f;
        node_1.layout.width = 347.5f;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with multiple flex and margin", root_node, root_layout);
  }

  @Test
  public void testCase82()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 700;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.setMargin(Spacing.RIGHT, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 700;
      node_0.layout.height = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 352.5f;
        node_1.layout.width = 347.5f;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 347.5f;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with multiple flex and margin in rtl", root_node, root_layout);
  }

  @Test
  public void testCase83()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 300;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 600;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 600;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with flex and overflow", root_node, root_layout);
  }

  @Test
  public void testCase84()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 600;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with flex and position absolute", root_node, root_layout);
  }

  @Test
  public void testCase85()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 600;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 600;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with flex and position absolute in rtl", root_node, root_layout);
  }

  @Test
  public void testCase86()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 500;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 500;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with double flex and position absolute", root_node, root_layout);
  }

  @Test
  public void testCase87()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setBorder(Spacing.LEFT, 5);
      node_0.setBorder(Spacing.TOP, 5);
      node_0.setBorder(Spacing.RIGHT, 5);
      node_0.setBorder(Spacing.BOTTOM, 5);
      node_0.setBorder(Spacing.START, 5);
      node_0.setBorder(Spacing.END, 5);
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 10;
    }

    test("should layout node with borderWidth", root_node, root_layout);
  }

  @Test
  public void testCase88()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setBorder(Spacing.TOP, 1);
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with borderWidth and position: absolute, top", root_node, root_layout);
  }

  @Test
  public void testCase89()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setBorder(Spacing.LEFT, 1);
      node_0.setBorder(Spacing.TOP, 1);
      node_0.setBorder(Spacing.RIGHT, 1);
      node_0.setBorder(Spacing.BOTTOM, 1);
      node_0.setBorder(Spacing.START, 1);
      node_0.setBorder(Spacing.END, 1);
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 2;
      node_0.layout.height = 2;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 1;
        node_1.layout.left = 6;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with borderWidth and position: absolute, top. cross axis", root_node, root_layout);
  }

  @Test
  public void testCase90()
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
        node_1.setMargin(Spacing.LEFT, 20);
        node_1.setPadding(Spacing.LEFT, 20);
        node_1.setPadding(Spacing.TOP, 20);
        node_1.setPadding(Spacing.RIGHT, 20);
        node_1.setPadding(Spacing.BOTTOM, 20);
        node_1.setPadding(Spacing.START, 20);
        node_1.setPadding(Spacing.END, 20);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 50;
      node_0.layout.height = 40;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 20;
        node_1.layout.width = 40;
        node_1.layout.height = 40;
      }
    }

    test("should correctly take into account min padding for stretch", root_node, root_layout);
  }

  @Test
  public void testCase91()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = -31;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setBorder(Spacing.RIGHT, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 5;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 5;
        node_1.layout.height = 0;
      }
    }

    test("should layout node with negative width", root_node, root_layout);
  }

  @Test
  public void testCase92()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.setBorder(Spacing.RIGHT, 1);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMargin(Spacing.RIGHT, -8);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should handle negative margin and min padding correctly", root_node, root_layout);
  }

  @Test
  public void testCase93()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.setBorder(Spacing.LEFT, 1);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMargin(Spacing.LEFT, -8);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 1;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should handle negative margin and min padding correctly in rtl", root_node, root_layout);
  }

  @Test
  public void testCase94()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 18;
    }

    test("should layout node with just text", root_node, root_layout);
  }

  @Test
  public void testCase95()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 10;
      node_0.layout.height = 18;
    }

    test("should layout node with text and width", root_node, root_layout);
  }

  @Test
  public void testCase96()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 172.421875f;
      node_0.layout.height = 18;
    }

    test("should layout node with text, padding and margin", root_node, root_layout);
  }

  @Test
  public void testCase97()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 300;
        node_1.layout.height = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 300;
          node_2.layout.height = 0;
        }
      }
    }

    test("should layout node with nested alignSelf: stretch", root_node, root_layout);
  }

  @Test
  public void testCase98()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 500;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 18;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 500;
          node_2.layout.height = 18;
        }
      }
    }

    test("should layout node with text and flex", root_node, root_layout);
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
        node_1.style.direction = CSSDirection.RTL;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 500;
      node_0.layout.height = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 18;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 500;
          node_2.layout.height = 18;
        }
      }
    }

    test("should layout node with text and flex in rtl", root_node, root_layout);
  }

  @Test
  public void testCase100()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 130;
      node_0.layout.height = 36;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 130;
        node_1.layout.height = 36;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 130;
          node_2.layout.height = 36;
        }
      }
    }

    test("should layout node with text and stretch", root_node, root_layout);
  }

  @Test
  public void testCase101()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 36;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 36;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 130;
          node_2.layout.height = 36;
        }
      }
    }

    test("should layout node with text stretch and width", root_node, root_layout);
  }

  @Test
  public void testCase102()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignSelf = CSSAlign.FLEX_START;
      node_0.style.width = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.FLEX_START;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "loooooooooong with space";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 36;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100.4375f;
        node_1.layout.height = 36;
      }
    }

    test("should layout node with text bounded by parent", root_node, root_layout);
  }

  @Test
  public void testCase103()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignSelf = CSSAlign.FLEX_START;
      node_0.style.width = 100;
      node_0.setPadding(Spacing.LEFT, 10);
      node_0.setPadding(Spacing.TOP, 10);
      node_0.setPadding(Spacing.RIGHT, 10);
      node_0.setPadding(Spacing.BOTTOM, 10);
      node_0.setPadding(Spacing.START, 10);
      node_0.setPadding(Spacing.END, 10);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.FLEX_START;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 76;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 20;
        node_1.layout.left = 20;
        node_1.layout.width = 100.4375f;
        node_1.layout.height = 36;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 100.4375f;
          node_2.layout.height = 36;
        }
      }
    }

    test("should layout node with text bounded by grand-parent", root_node, root_layout);
  }

  @Test
  public void testCase104()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 900;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 900;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout space-between when remaining space is negative", root_node, root_layout);
  }

  @Test
  public void testCase105()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = -800;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 900;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = -800;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout space-between when remaining space is negative in reverse", root_node, root_layout);
  }

  @Test
  public void testCase106()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = -700;
        node_1.layout.width = 900;
        node_1.layout.height = 0;
      }
    }

    test("should layout flex-end when remaining space is negative", root_node, root_layout);
  }

  @Test
  public void testCase107()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 900;
        node_1.layout.height = 0;
      }
    }

    test("should layout flex-end when remaining space is negative in rtl", root_node, root_layout);
  }

  @Test
  public void testCase108()
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
          node_2.setMargin(Spacing.LEFT, 20);
          node_2.setMargin(Spacing.TOP, 20);
          node_2.setMargin(Spacing.RIGHT, 20);
          node_2.setMargin(Spacing.BOTTOM, 20);
          node_2.setMargin(Spacing.START, 20);
          node_2.setMargin(Spacing.END, 20);
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 58;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 58;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 20;
          node_2.layout.left = 20;
          node_2.layout.width = 172.421875f;
          node_2.layout.height = 18;
        }
      }
    }

    test("should layout text with flexDirection row", root_node, root_layout);
  }

  @Test
  public void testCase109()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
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
          node_2.setMargin(Spacing.LEFT, 20);
          node_2.setMargin(Spacing.TOP, 20);
          node_2.setMargin(Spacing.RIGHT, 20);
          node_2.setMargin(Spacing.BOTTOM, 20);
          node_2.setMargin(Spacing.START, 20);
          node_2.setMargin(Spacing.END, 20);
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 58;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 58;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 20;
          node_2.layout.left = 7.578125f;
          node_2.layout.width = 172.421875f;
          node_2.layout.height = 18;
        }
      }
    }

    test("should layout text with flexDirection row in rtl", root_node, root_layout);
  }

  @Test
  public void testCase110()
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
          node_2.setMargin(Spacing.LEFT, 20);
          node_2.setMargin(Spacing.TOP, 20);
          node_2.setMargin(Spacing.RIGHT, 20);
          node_2.setMargin(Spacing.BOTTOM, 20);
          node_2.setMargin(Spacing.START, 20);
          node_2.setMargin(Spacing.END, 20);
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 76;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 76;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 20;
          node_2.layout.left = 20;
          node_2.layout.width = 160;
          node_2.layout.height = 36;
        }
      }
    }

    test("should layout with text and margin", root_node, root_layout);
  }

  @Test
  public void testCase111()
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should layout with position absolute, top, left, bottom, right", root_node, root_layout);
  }

  @Test
  public void testCase112()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignSelf = CSSAlign.FLEX_START;
      node_0.style.width = 100;
      node_0.style.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.FLEX_START;
        node_1.style.flex = 2.5f;
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.FLEX_START;
        node_1.style.flex = 7.5f;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 25;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 25;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 75;
      }
    }

    test("should layout with arbitrary flex", root_node, root_layout);
  }

  @Test
  public void testCase113()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
      node_0.style.alignSelf = CSSAlign.FLEX_START;
      node_0.style.width = 100;
      node_0.style.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.FLEX_START;
        node_1.style.flex = 2.5f;
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.FLEX_START;
        node_1.style.flex = 7.5f;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 75;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 25;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 75;
      }
    }

    test("should layout with arbitrary flex in reverse", root_node, root_layout);
  }

  @Test
  public void testCase114()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.COLUMN_REVERSE;
      node_0.style.alignSelf = CSSAlign.FLEX_START;
      node_0.style.width = 100;
      node_0.style.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.FLEX_START;
        node_1.style.flex = -2.5f;
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.FLEX_START;
        node_1.style.flex = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout with negative flex in reverse", root_node, root_layout);
  }

  @Test
  public void testCase115()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 50;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionLeft = 0;
        node_1.style.positionRight = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 50;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 50;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 50;
        node_1.layout.height = 0;
      }
    }

    test("should layout with position: absolute and another sibling", root_node, root_layout);
  }

  @Test
  public void testCase116()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionTop = 0;
        node_1.style.positionBottom = 20;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 80;
      }
    }

    test("should calculate height properly with position: absolute top and bottom", root_node, root_layout);
  }

  @Test
  public void testCase117()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 200;
      node_0.style.height = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.justifyContent = CSSJustify.CENTER;
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionLeft = 0;
        node_1.style.positionTop = 0;
        node_1.style.positionRight = 0;
        node_1.style.positionBottom = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.width = 100;
          node_2.style.height = 100;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 200;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 50;
          node_2.layout.left = 0;
          node_2.layout.width = 100;
          node_2.layout.height = 100;
        }
      }
    }

    test("should layout with complicated position: absolute and justifyContent: center combo", root_node, root_layout);
  }

  @Test
  public void testCase118()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionBottom = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should calculate top properly with position: absolute bottom", root_node, root_layout);
  }

  @Test
  public void testCase119()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.positionRight = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 100;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should calculate left properly with position: absolute right", root_node, root_layout);
  }

  @Test
  public void testCase120()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.height = 10;
        node_1.style.positionBottom = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 90;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 10;
      }
    }

    test("should calculate top properly with position: absolute bottom and height", root_node, root_layout);
  }

  @Test
  public void testCase121()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.width = 10;
        node_1.style.positionRight = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 90;
        node_1.layout.width = 10;
        node_1.layout.height = 0;
      }
    }

    test("should calculate left properly with position: absolute right and width", root_node, root_layout);
  }

  @Test
  public void testCase122()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.height = 10;
        node_1.style.positionBottom = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = -10;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 10;
      }
    }

    test("should calculate top properly with position: absolute right, width, and no parent dimensions", root_node, root_layout);
  }

  @Test
  public void testCase123()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.width = 10;
        node_1.style.positionRight = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = -10;
        node_1.layout.width = 10;
        node_1.layout.height = 0;
      }
    }

    test("should calculate left properly with position: absolute right, width, and no parent dimensions", root_node, root_layout);
  }

  @Test
  public void testCase124()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_BETWEEN;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setBorder(Spacing.BOTTOM, 1);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 1;
      }
    }

    test("should layout border bottom inside of justify content space between container", root_node, root_layout);
  }

  @Test
  public void testCase125()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.CENTER;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMargin(Spacing.TOP, -6);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = -3;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout negative margin top inside of justify content center container", root_node, root_layout);
  }

  @Test
  public void testCase126()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.CENTER;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.setMargin(Spacing.TOP, 20);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 20;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout positive margin top inside of justify content center container", root_node, root_layout);
  }

  @Test
  public void testCase127()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_END;
      node_0.setBorder(Spacing.BOTTOM, 5);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout border bottom and flex end with an empty child", root_node, root_layout);
  }

  @Test
  public void testCase128()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 800;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionLeft = 5;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 800;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 5;
        node_1.layout.width = 800;
        node_1.layout.height = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 800;
          node_2.layout.height = 0;
        }
      }
    }

    test("should layout with children of a contain with left", root_node, root_layout);
  }

  @Test
  public void testCase129()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.flexWrap = CSSWrap.WRAP;
      node_0.style.width = 100;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 40;
        node_1.style.height = 10;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 40;
        node_1.style.height = 10;
        node_1 = node_0.getChildAt(2);
        node_1.style.width = 40;
        node_1.style.height = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 20;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 40;
        node_1.layout.height = 10;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 40;
        node_1.layout.width = 40;
        node_1.layout.height = 10;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 10;
        node_1.layout.left = 0;
        node_1.layout.width = 40;
        node_1.layout.height = 10;
      }
    }

    test("should layout flex-wrap", root_node, root_layout);
  }

  @Test
  public void testCase130()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.flexWrap = CSSWrap.WRAP;
      node_0.style.width = 100;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 40;
        node_1.style.height = 10;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 40;
        node_1.style.height = 10;
        node_1 = node_0.getChildAt(2);
        node_1.style.width = 40;
        node_1.style.height = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 20;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 60;
        node_1.layout.width = 40;
        node_1.layout.height = 10;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 20;
        node_1.layout.width = 40;
        node_1.layout.height = 10;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 10;
        node_1.layout.left = 60;
        node_1.layout.width = 40;
        node_1.layout.height = 10;
      }
    }

    test("should layout flex-wrap in rtl", root_node, root_layout);
  }

  @Test
  public void testCase131()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexWrap = CSSWrap.WRAP;
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
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 200;
      }
    }

    test("should layout flex wrap with a line bigger than container", root_node, root_layout);
  }

  @Test
  public void testCase132()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 200;
      node_0.style.maxWidth = 90;
      node_0.style.maxHeight = 190;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 90;
      node_0.layout.height = 190;
    }

    test("should use max bounds", root_node, root_layout);
  }

  @Test
  public void testCase133()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 200;
      node_0.style.minWidth = 110;
      node_0.style.minHeight = 210;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 110;
      node_0.layout.height = 210;
    }

    test("should use min bounds", root_node, root_layout);
  }

  @Test
  public void testCase134()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 200;
      node_0.style.maxWidth = 90;
      node_0.style.maxHeight = 190;
      node_0.style.minWidth = 110;
      node_0.style.minHeight = 210;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 110;
      node_0.layout.height = 210;
    }

    test("should use min bounds over max bounds", root_node, root_layout);
  }

  @Test
  public void testCase135()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 200;
      node_0.style.maxWidth = 80;
      node_0.style.maxHeight = 180;
      node_0.style.minWidth = 90;
      node_0.style.minHeight = 190;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 90;
      node_0.layout.height = 190;
    }

    test("should use min bounds over max bounds and natural width", root_node, root_layout);
  }

  @Test
  public void testCase136()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 200;
      node_0.style.minWidth = -10;
      node_0.style.minHeight = -20;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 200;
    }

    test("should ignore negative min bounds", root_node, root_layout);
  }

  @Test
  public void testCase137()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 100;
      node_0.style.height = 200;
      node_0.style.maxWidth = -10;
      node_0.style.maxHeight = -20;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 200;
    }

    test("should ignore negative max bounds", root_node, root_layout);
  }

  @Test
  public void testCase138()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.maxWidth = 30;
      node_0.style.maxHeight = 10;
      node_0.setPadding(Spacing.LEFT, 20);
      node_0.setPadding(Spacing.TOP, 15);
      node_0.setPadding(Spacing.RIGHT, 20);
      node_0.setPadding(Spacing.BOTTOM, 15);
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 40;
      node_0.layout.height = 30;
    }

    test("should use padded size over max bounds", root_node, root_layout);
  }

  @Test
  public void testCase139()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.minWidth = 50;
      node_0.style.minHeight = 40;
      node_0.setPadding(Spacing.LEFT, 20);
      node_0.setPadding(Spacing.TOP, 15);
      node_0.setPadding(Spacing.RIGHT, 20);
      node_0.setPadding(Spacing.BOTTOM, 15);
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 50;
      node_0.layout.height = 40;
    }

    test("should use min size over padded size", root_node, root_layout);
  }

  @Test
  public void testCase140()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.minWidth = 200;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 50;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 50;
        node_1.layout.width = 200;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 0;
        node_1.layout.left = 250;
        node_1.layout.width = 50;
        node_1.layout.height = 200;
      }
    }

    test("should override flex direction size with min bounds", root_node, root_layout);
  }

  @Test
  public void testCase141()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.minWidth = 200;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 250;
        node_1.layout.width = 50;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 50;
        node_1.layout.width = 200;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 50;
        node_1.layout.height = 200;
      }
    }

    test("should override flex direction size with min bounds in rtl", root_node, root_layout);
  }

  @Test
  public void testCase142()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.maxWidth = 110;
        node_1.style.minWidth = 90;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 100;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 0;
        node_1.layout.left = 200;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
      }
    }

    test("should not override flex direction size within bounds", root_node, root_layout);
  }

  @Test
  public void testCase143()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.maxWidth = 110;
        node_1.style.minWidth = 90;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 200;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 100;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 200;
      }
    }

    test("should not override flex direction size within bounds in rtl", root_node, root_layout);
  }

  @Test
  public void testCase144()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.maxWidth = 60;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 120;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 120;
        node_1.layout.width = 60;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 0;
        node_1.layout.left = 180;
        node_1.layout.width = 120;
        node_1.layout.height = 200;
      }
    }

    test("should override flex direction size with max bounds", root_node, root_layout);
  }

  @Test
  public void testCase145()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.maxWidth = 60;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 180;
        node_1.layout.width = 120;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 120;
        node_1.layout.width = 60;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 120;
        node_1.layout.height = 200;
      }
    }

    test("should override flex direction size with max bounds in rtl", root_node, root_layout);
  }

  @Test
  public void testCase146()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.maxWidth = 60;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.maxWidth = 60;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
        node_1.style.maxWidth = 60;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 60;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 60;
        node_1.layout.width = 60;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 0;
        node_1.layout.left = 120;
        node_1.layout.width = 60;
        node_1.layout.height = 200;
      }
    }

    test("should ignore flex size if fully max bound", root_node, root_layout);
  }

  @Test
  public void testCase147()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.maxWidth = 60;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.maxWidth = 60;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
        node_1.style.maxWidth = 60;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 240;
        node_1.layout.width = 60;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 180;
        node_1.layout.width = 60;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 0;
        node_1.layout.left = 120;
        node_1.layout.width = 60;
        node_1.layout.height = 200;
      }
    }

    test("should ignore flex size if fully max bound in rtl", root_node, root_layout);
  }

  @Test
  public void testCase148()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.minWidth = 120;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.minWidth = 120;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
        node_1.style.minWidth = 120;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 120;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 120;
        node_1.layout.width = 120;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 0;
        node_1.layout.left = 240;
        node_1.layout.width = 120;
        node_1.layout.height = 200;
      }
    }

    test("should ignore flex size if fully min bound", root_node, root_layout);
  }

  @Test
  public void testCase149()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.minWidth = 120;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.minWidth = 120;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
        node_1.style.minWidth = 120;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 180;
        node_1.layout.width = 120;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 60;
        node_1.layout.width = 120;
        node_1.layout.height = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 0;
        node_1.layout.left = -60;
        node_1.layout.width = 120;
        node_1.layout.height = 200;
      }
    }

    test("should ignore flex size if fully min bound in rtl", root_node, root_layout);
  }

  @Test
  public void testCase150()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.maxWidth = 310;
        node_1.style.minWidth = 290;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 300;
        node_1.layout.height = 200;
      }
    }

    test("should pre-fill child size within bounds", root_node, root_layout);
  }

  @Test
  public void testCase151()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.maxWidth = 290;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 290;
        node_1.layout.height = 200;
      }
    }

    test("should pre-fill child size within max bound", root_node, root_layout);
  }

  @Test
  public void testCase152()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 300;
      node_0.style.height = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.minWidth = 310;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 310;
        node_1.layout.height = 200;
      }
    }

    test("should pre-fill child size within min bounds", root_node, root_layout);
  }

  @Test
  public void testCase153()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.maxWidth = 300;
      node_0.style.maxHeight = 700;
      node_0.style.minWidth = 100;
      node_0.style.minHeight = 500;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 200;
        node_1.style.height = 300;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 200;
        node_1.style.height = 300;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 600;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 300;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 300;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 300;
      }
    }

    test("should set parents size based on bounded children", root_node, root_layout);
  }

  @Test
  public void testCase154()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.maxWidth = 100;
      node_0.style.maxHeight = 500;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 200;
        node_1.style.height = 300;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 200;
        node_1.style.height = 300;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 500;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 300;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 300;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 300;
      }
    }

    test("should set parents size based on max bounded children", root_node, root_layout);
  }

  @Test
  public void testCase155()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.minWidth = 300;
      node_0.style.minHeight = 700;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 200;
        node_1.style.height = 300;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 200;
        node_1.style.height = 300;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 300;
      node_0.layout.height = 700;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 300;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 300;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 300;
      }
    }

    test("should set parents size based on min bounded children", root_node, root_layout);
  }

  @Test
  public void testCase156()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.STRETCH;
      node_0.style.width = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 100;
        node_1.style.maxWidth = 1100;
        node_1.style.maxHeight = 110;
        node_1.style.minWidth = 900;
        node_1.style.minHeight = 90;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 1000;
        node_1.layout.height = 100;
      }
    }

    test("should keep stretched size within bounds", root_node, root_layout);
  }

  @Test
  public void testCase157()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.STRETCH;
      node_0.style.width = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 100;
        node_1.style.maxWidth = 900;
        node_1.style.maxHeight = 90;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 90;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 900;
        node_1.layout.height = 90;
      }
    }

    test("should keep stretched size within max bounds", root_node, root_layout);
  }

  @Test
  public void testCase158()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.STRETCH;
      node_0.style.width = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 100;
        node_1.style.minWidth = 1100;
        node_1.style.minHeight = 110;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 110;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 1100;
        node_1.layout.height = 110;
      }
    }

    test("should keep stretched size within min bounds", root_node, root_layout);
  }

  @Test
  public void testCase159()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 100;
        node_1.style.minWidth = 100;
        node_1.style.minHeight = 110;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 110;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 110;
      }
    }

    test("should keep cross axis size within min bounds", root_node, root_layout);
  }

  @Test
  public void testCase160()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.width = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 100;
        node_1.style.minWidth = 100;
        node_1.style.minHeight = 110;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 110;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 900;
        node_1.layout.width = 100;
        node_1.layout.height = 110;
      }
    }

    test("should keep cross axis size within min bounds in rtl", root_node, root_layout);
  }

  @Test
  public void testCase161()
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
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.maxWidth = 500;
        node_1.style.maxHeight = 600;
        node_1.style.positionLeft = 100;
        node_1.style.positionTop = 100;
        node_1.style.positionRight = 100;
        node_1.style.positionBottom = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 100;
        node_1.layout.left = 100;
        node_1.layout.width = 500;
        node_1.layout.height = 600;
      }
    }

    test("should layout node with position absolute, top and left and max bounds", root_node, root_layout);
  }

  @Test
  public void testCase162()
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
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.minWidth = 900;
        node_1.style.minHeight = 1000;
        node_1.style.positionLeft = 100;
        node_1.style.positionTop = 100;
        node_1.style.positionRight = 100;
        node_1.style.positionBottom = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 1000;
      node_0.layout.height = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 100;
        node_1.layout.left = 100;
        node_1.layout.width = 900;
        node_1.layout.height = 1000;
      }
    }

    test("should layout node with position absolute, top and left and min bounds", root_node, root_layout);
  }

  @Test
  public void testCase163()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 400;
      node_0.style.height = 400;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.setPadding(Spacing.LEFT, 10);
        node_1.setPadding(Spacing.TOP, 10);
        node_1.setPadding(Spacing.RIGHT, 10);
        node_1.setPadding(Spacing.BOTTOM, 10);
        node_1.setPadding(Spacing.START, 10);
        node_1.setPadding(Spacing.END, 10);
        node_1.style.positionLeft = 100;
        node_1.style.positionTop = 100;
        node_1.style.positionRight = 100;
        node_1.style.positionBottom = 100;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.positionType = CSSPositionType.ABSOLUTE;
          node_2.style.positionLeft = 10;
          node_2.style.positionTop = 10;
          node_2.style.positionRight = 10;
          node_2.style.positionBottom = 10;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 400;
      node_0.layout.height = 400;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 100;
        node_1.layout.left = 100;
        node_1.layout.width = 200;
        node_1.layout.height = 200;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 10;
          node_2.layout.left = 10;
          node_2.layout.width = 180;
          node_2.layout.height = 180;
        }
      }
    }

    test("should layout absolutely positioned node with absolutely positioned padded parent", root_node, root_layout);
  }

  @Test
  public void testCase164()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 400;
      node_0.style.height = 400;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.setPadding(Spacing.LEFT, 10);
        node_1.setPadding(Spacing.TOP, 10);
        node_1.setPadding(Spacing.RIGHT, 10);
        node_1.setPadding(Spacing.BOTTOM, 10);
        node_1.setPadding(Spacing.START, 10);
        node_1.setPadding(Spacing.END, 10);
        node_1.setBorder(Spacing.LEFT, 1);
        node_1.setBorder(Spacing.TOP, 1);
        node_1.setBorder(Spacing.RIGHT, 1);
        node_1.setBorder(Spacing.BOTTOM, 1);
        node_1.setBorder(Spacing.START, 1);
        node_1.setBorder(Spacing.END, 1);
        node_1.style.positionLeft = 100;
        node_1.style.positionTop = 100;
        node_1.style.positionRight = 100;
        node_1.style.positionBottom = 100;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.positionType = CSSPositionType.ABSOLUTE;
          node_2.style.positionLeft = 10;
          node_2.style.positionTop = 10;
          node_2.style.positionRight = 10;
          node_2.style.positionBottom = 10;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 400;
      node_0.layout.height = 400;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 100;
        node_1.layout.left = 100;
        node_1.layout.width = 200;
        node_1.layout.height = 200;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 11;
          node_2.layout.left = 11;
          node_2.layout.width = 178;
          node_2.layout.height = 178;
        }
      }
    }

    test("should layout absolutely positioned node with absolutely positioned padded and bordered parent", root_node, root_layout);
  }

  @Test
  public void testCase165()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 400;
      node_0.style.height = 400;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.setPadding(Spacing.LEFT, 10);
        node_1.setPadding(Spacing.TOP, 10);
        node_1.setPadding(Spacing.RIGHT, 10);
        node_1.setPadding(Spacing.BOTTOM, 10);
        node_1.setPadding(Spacing.START, 10);
        node_1.setPadding(Spacing.END, 10);
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.positionType = CSSPositionType.ABSOLUTE;
          node_2.style.positionLeft = 10;
          node_2.style.positionTop = 10;
          node_2.style.positionRight = 10;
          node_2.style.positionBottom = 10;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 400;
      node_0.layout.height = 400;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 400;
        node_1.layout.height = 400;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 10;
          node_2.layout.left = 10;
          node_2.layout.width = 380;
          node_2.layout.height = 380;
        }
      }
    }

    test("should layout absolutely positioned node with padded flex 1 parent", root_node, root_layout);
  }

  @Test
  public void testCase166()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.width = 200;
      node_0.style.height = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.ROW;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.width = 50;
          node_2.style.height = 50;
          node_2 = node_1.getChildAt(1);
          node_2.style.width = 50;
          node_2.style.height = 50;
        }
        node_1 = node_0.getChildAt(1);
        node_1.style.direction = CSSDirection.LTR;
        node_1.style.flexDirection = CSSFlexDirection.ROW;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.width = 50;
          node_2.style.height = 50;
          node_2 = node_1.getChildAt(1);
          node_2.style.width = 50;
          node_2.style.height = 50;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 50;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 150;
          node_2.layout.width = 50;
          node_2.layout.height = 50;
          node_2 = node_1.getChildAt(1);
          node_2.layout.top = 0;
          node_2.layout.left = 100;
          node_2.layout.width = 50;
          node_2.layout.height = 50;
        }
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 50;
        node_1.layout.left = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 50;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.top = 0;
          node_2.layout.left = 0;
          node_2.layout.width = 50;
          node_2.layout.height = 50;
          node_2 = node_1.getChildAt(1);
          node_2.layout.top = 0;
          node_2.layout.left = 50;
          node_2.layout.width = 50;
          node_2.layout.height = 50;
        }
      }
    }

    test("should layout nested nodes with mixed directions", root_node, root_layout);
  }

  @Test
  public void testCase167()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ROW;
      node_0.style.justifyContent = CSSJustify.SPACE_BETWEEN;
      node_0.style.flexWrap = CSSWrap.WRAP;
      node_0.style.width = 320;
      node_0.style.height = 200;
      addChildren(node_0, 6);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(2);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(3);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(4);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1 = node_0.getChildAt(5);
        node_1.style.width = 100;
        node_1.style.height = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 320;
      node_0.layout.height = 200;
      addChildren(node_0, 6);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.top = 0;
        node_1.layout.left = 110;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(2);
        node_1.layout.top = 0;
        node_1.layout.left = 220;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(3);
        node_1.layout.top = 100;
        node_1.layout.left = 0;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(4);
        node_1.layout.top = 100;
        node_1.layout.left = 110;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(5);
        node_1.layout.top = 100;
        node_1.layout.left = 220;
        node_1.layout.width = 100;
        node_1.layout.height = 100;
      }
    }

    test("should correctly space wrapped nodes", root_node, root_layout);
  }

  @Test
  public void testCase168()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 200;
      node_0.setPadding(Spacing.LEFT, 5);
      node_0.setPadding(Spacing.RIGHT, 5);
      node_0.setPadding(Spacing.START, 15);
      node_0.setPadding(Spacing.END, 15);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 50;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 15;
        node_1.layout.width = 170;
        node_1.layout.height = 50;
      }
    }

    test("should give start/end padding precedence over left/right padding", root_node, root_layout);
  }

  @Test
  public void testCase169()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 50;
        node_1.setMargin(Spacing.LEFT, 5);
        node_1.setMargin(Spacing.RIGHT, 5);
        node_1.setMargin(Spacing.START, 15);
        node_1.setMargin(Spacing.END, 15);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 15;
        node_1.layout.width = 170;
        node_1.layout.height = 50;
      }
    }

    test("should give start/end margin precedence over left/right margin", root_node, root_layout);
  }

  @Test
  public void testCase170()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 200;
      node_0.setBorder(Spacing.LEFT, 5);
      node_0.setBorder(Spacing.RIGHT, 5);
      node_0.setBorder(Spacing.START, 15);
      node_0.setBorder(Spacing.END, 15);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 50;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 15;
        node_1.layout.width = 170;
        node_1.layout.height = 50;
      }
    }

    test("should give start/end border precedence over left/right border", root_node, root_layout);
  }

  @Test
  public void testCase171()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 200;
      node_0.setPadding(Spacing.START, 15);
      node_0.setPadding(Spacing.END, 5);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 50;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 15;
        node_1.layout.width = 180;
        node_1.layout.height = 50;
      }
    }

    test("should layout node with correct start/end padding", root_node, root_layout);
  }

  @Test
  public void testCase172()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.width = 200;
      node_0.setPadding(Spacing.START, 15);
      node_0.setPadding(Spacing.END, 5);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 50;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 5;
        node_1.layout.width = 180;
        node_1.layout.height = 50;
      }
    }

    test("should layout node with correct start/end padding in rtl", root_node, root_layout);
  }

  @Test
  public void testCase173()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 50;
        node_1.setMargin(Spacing.START, 15);
        node_1.setMargin(Spacing.END, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 15;
        node_1.layout.width = 180;
        node_1.layout.height = 50;
      }
    }

    test("should layout node with correct start/end margin", root_node, root_layout);
  }

  @Test
  public void testCase174()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.direction = CSSDirection.RTL;
        node_1.style.height = 50;
        node_1.setMargin(Spacing.START, 15);
        node_1.setMargin(Spacing.END, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 5;
        node_1.layout.width = 180;
        node_1.layout.height = 50;
      }
    }

    test("should layout node with correct start/end margin in rtl", root_node, root_layout);
  }

  @Test
  public void testCase175()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.width = 200;
      node_0.setBorder(Spacing.START, 15);
      node_0.setBorder(Spacing.END, 5);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 50;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 15;
        node_1.layout.width = 180;
        node_1.layout.height = 50;
      }
    }

    test("should layout node with correct start/end border", root_node, root_layout);
  }

  @Test
  public void testCase176()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.width = 200;
      node_0.setBorder(Spacing.START, 15);
      node_0.setBorder(Spacing.END, 5);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.height = 50;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.top = 0;
      node_0.layout.left = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.top = 0;
        node_1.layout.left = 5;
        node_1.layout.width = 180;
        node_1.layout.height = 50;
      }
    }

    test("should layout node with correct start/end border in rtl", root_node, root_layout);
  }
  /** END_GENERATED **/
}
