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
      node_0.style.margin[Spacing.LEFT] = 10;
      node_0.style.margin[Spacing.TOP] = 10;
      node_0.style.margin[Spacing.RIGHT] = 10;
      node_0.style.margin[Spacing.BOTTOM] = 10;
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
      node_0.style.margin[Spacing.LEFT] = 10;
      node_0.style.margin[Spacing.TOP] = 10;
      node_0.style.margin[Spacing.RIGHT] = 10;
      node_0.style.margin[Spacing.BOTTOM] = 10;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.style.margin[Spacing.LEFT] = 50;
        node_1.style.margin[Spacing.TOP] = 50;
        node_1.style.margin[Spacing.RIGHT] = 50;
        node_1.style.margin[Spacing.BOTTOM] = 50;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.style.margin[Spacing.LEFT] = 25;
        node_1.style.margin[Spacing.TOP] = 25;
        node_1.style.margin[Spacing.RIGHT] = 25;
        node_1.style.margin[Spacing.BOTTOM] = 25;
        node_1 = node_0.getChildAt(2);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.style.margin[Spacing.LEFT] = 10;
        node_1.style.margin[Spacing.TOP] = 10;
        node_1.style.margin[Spacing.RIGHT] = 10;
        node_1.style.margin[Spacing.BOTTOM] = 10;
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

    test("should layout node with just flex", root_node, root_layout);
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
      node_0.style.margin[Spacing.LEFT] = 5;
      node_0.style.margin[Spacing.TOP] = 10;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.style.margin[Spacing.LEFT] = 15;
        node_1.style.margin[Spacing.TOP] = 50;
        node_1.style.margin[Spacing.BOTTOM] = 20;
        node_1 = node_0.getChildAt(1);
        node_1.style.width = 100;
        node_1.style.height = 100;
        node_1.style.margin[Spacing.LEFT] = 30;
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
        node_1.style.margin[Spacing.LEFT] = 5;
        node_1.style.margin[Spacing.TOP] = 5;
        node_1.style.margin[Spacing.RIGHT] = 5;
        node_1.style.margin[Spacing.BOTTOM] = 5;
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
        node_1.style.margin[Spacing.TOP] = 10;
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
          node_2.style.margin[Spacing.LEFT] = 10;
          node_2.style.margin[Spacing.TOP] = 10;
          node_2.style.margin[Spacing.RIGHT] = 10;
          node_2.style.margin[Spacing.BOTTOM] = 10;
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
        node_1.style.margin[Spacing.LEFT] = 10;
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
      node_0.style.padding[Spacing.LEFT] = 5;
      node_0.style.padding[Spacing.TOP] = 5;
      node_0.style.padding[Spacing.RIGHT] = 5;
      node_0.style.padding[Spacing.BOTTOM] = 5;
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
      node_0.style.padding[Spacing.LEFT] = 5;
      node_0.style.padding[Spacing.TOP] = 5;
      node_0.style.padding[Spacing.RIGHT] = 5;
      node_0.style.padding[Spacing.BOTTOM] = 5;
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
      node_0.style.padding[Spacing.LEFT] = 5;
      node_0.style.padding[Spacing.TOP] = 5;
      node_0.style.padding[Spacing.RIGHT] = 5;
      node_0.style.padding[Spacing.BOTTOM] = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.margin[Spacing.LEFT] = 5;
        node_1.style.margin[Spacing.TOP] = 5;
        node_1.style.margin[Spacing.RIGHT] = 5;
        node_1.style.margin[Spacing.BOTTOM] = 5;
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
        node_1.style.padding[Spacing.LEFT] = 10;
        node_1.style.padding[Spacing.TOP] = 10;
        node_1.style.padding[Spacing.RIGHT] = 10;
        node_1.style.padding[Spacing.BOTTOM] = 10;
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
      node_0.style.padding[Spacing.LEFT] = 50;
      node_0.style.padding[Spacing.TOP] = 50;
      node_0.style.padding[Spacing.RIGHT] = 50;
      node_0.style.padding[Spacing.BOTTOM] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.STRETCH;
        node_1.style.padding[Spacing.LEFT] = 10;
        node_1.style.padding[Spacing.TOP] = 10;
        node_1.style.padding[Spacing.RIGHT] = 10;
        node_1.style.padding[Spacing.BOTTOM] = 10;
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
          node_2.style.margin[Spacing.LEFT] = 16;
          node_2.style.margin[Spacing.TOP] = 16;
          node_2.style.margin[Spacing.RIGHT] = 16;
          node_2.style.margin[Spacing.BOTTOM] = 16;
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
      node_0.style.padding[Spacing.TOP] = 5;
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
        node_1.style.margin[Spacing.RIGHT] = 15;
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
        node_1.style.padding[Spacing.RIGHT] = 12;
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
      node_0.style.padding[Spacing.BOTTOM] = 20;
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
      node_0.style.padding[Spacing.LEFT] = 20;
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
      node_0.style.padding[Spacing.LEFT] = 5;
      node_0.style.padding[Spacing.TOP] = 5;
      node_0.style.padding[Spacing.RIGHT] = 5;
      node_0.style.padding[Spacing.BOTTOM] = 5;
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
      node_0.style.padding[Spacing.LEFT] = 20;
      node_0.style.padding[Spacing.TOP] = 20;
      node_0.style.padding[Spacing.RIGHT] = 20;
      node_0.style.padding[Spacing.BOTTOM] = 20;
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
        node_1.style.margin[Spacing.TOP] = 5;
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
        node_1.style.margin[Spacing.LEFT] = 5;
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
        node_1.style.margin[Spacing.LEFT] = 5;
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
        node_1.style.padding[Spacing.RIGHT] = 5;
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
        node_1.style.margin[Spacing.LEFT] = 5;
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
      node_0.style.border[Spacing.LEFT] = 5;
      node_0.style.border[Spacing.TOP] = 5;
      node_0.style.border[Spacing.RIGHT] = 5;
      node_0.style.border[Spacing.BOTTOM] = 5;
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
      node_0.style.border[Spacing.TOP] = 1;
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
      node_0.style.border[Spacing.LEFT] = 1;
      node_0.style.border[Spacing.TOP] = 1;
      node_0.style.border[Spacing.RIGHT] = 1;
      node_0.style.border[Spacing.BOTTOM] = 1;
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
        node_1.style.margin[Spacing.LEFT] = 20;
        node_1.style.padding[Spacing.LEFT] = 20;
        node_1.style.padding[Spacing.TOP] = 20;
        node_1.style.padding[Spacing.RIGHT] = 20;
        node_1.style.padding[Spacing.BOTTOM] = 20;
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
      node_0.style.width = -31;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.border[Spacing.RIGHT] = 5;
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
      node_0.style.border[Spacing.RIGHT] = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.margin[Spacing.RIGHT] = -8;
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
      node_0.layout.width = 34.671875f;
      node_0.layout.height = 16;
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
      node_0.layout.height = 16;
    }

    test("should layout node with text and width", root_node, root_layout);
  }

  @Test
  public void testCase65()
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
      node_0.layout.height = 16;
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
      node_0.layout.height = 16;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 500;
        node_1.layout.height = 16;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 500;
          node_2.layout.height = 16;
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
      node_0.layout.height = 32;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 130;
        node_1.layout.height = 32;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 130;
          node_2.layout.height = 32;
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
      node_0.layout.height = 32;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 32;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 130;
          node_2.layout.height = 32;
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
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 32;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 100.453125f;
        node_1.layout.height = 32;
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
      node_0.style.alignSelf = CSSAlign.FLEX_START;
      node_0.style.width = 100;
      node_0.style.padding[Spacing.LEFT] = 10;
      node_0.style.padding[Spacing.TOP] = 10;
      node_0.style.padding[Spacing.RIGHT] = 10;
      node_0.style.padding[Spacing.BOTTOM] = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.FLEX_START;
        node_1.style.margin[Spacing.LEFT] = 10;
        node_1.style.margin[Spacing.TOP] = 10;
        node_1.style.margin[Spacing.RIGHT] = 10;
        node_1.style.margin[Spacing.BOTTOM] = 10;
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
      node_0.layout.height = 72;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 20;
        node_1.layout.x = 20;
        node_1.layout.width = 100.453125f;
        node_1.layout.height = 32;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 100.453125f;
          node_2.layout.height = 32;
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
          node_2.style.margin[Spacing.LEFT] = 20;
          node_2.style.margin[Spacing.TOP] = 20;
          node_2.style.margin[Spacing.RIGHT] = 20;
          node_2.style.margin[Spacing.BOTTOM] = 20;
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
      node_0.layout.height = 56;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 56;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 20;
          node_2.layout.x = 20;
          node_2.layout.width = 172.421875f;
          node_2.layout.height = 16;
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
          node_2.style.margin[Spacing.LEFT] = 20;
          node_2.style.margin[Spacing.TOP] = 20;
          node_2.style.margin[Spacing.RIGHT] = 20;
          node_2.style.margin[Spacing.BOTTOM] = 20;
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
      node_0.layout.height = 72;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 72;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 20;
          node_2.layout.x = 20;
          node_2.layout.width = 160;
          node_2.layout.height = 32;
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
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 50;
      node_0.layout.height = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 50;
        node_1.layout.height = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 100;
        node_1.layout.x = 0;
        node_1.layout.width = 50;
        node_1.layout.height = 0;
      }
    }

    test("should layout with position: absolute and another sibling", root_node, root_layout);
  }

  @Test
  public void testCase80()
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
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 80;
      }
    }

    test("should calculate height properly with position: absolute top and bottom", root_node, root_layout);
  }

  @Test
  public void testCase81()
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
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 200;
      node_0.layout.height = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 200;
        node_1.layout.height = 200;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 50;
          node_2.layout.x = 0;
          node_2.layout.width = 100;
          node_2.layout.height = 100;
        }
      }
    }

    test("should layout with complicated position: absolute and justifyContent: center combo", root_node, root_layout);
  }

  @Test
  public void testCase82()
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

    test("should calculate top properly with position: absolute bottom", root_node, root_layout);
  }

  @Test
  public void testCase83()
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
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 100;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should calculate left properly with position: absolute right", root_node, root_layout);
  }

  @Test
  public void testCase84()
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
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 90;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 10;
      }
    }

    test("should calculate top properly with position: absolute bottom and height", root_node, root_layout);
  }

  @Test
  public void testCase85()
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
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 90;
        node_1.layout.width = 10;
        node_1.layout.height = 0;
      }
    }

    test("should calculate left properly with position: absolute right and width", root_node, root_layout);
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
        node_1.style.positionType = CSSPositionType.ABSOLUTE;
        node_1.style.height = 10;
        node_1.style.positionBottom = 0;
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
        node_1.layout.y = -10;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 10;
      }
    }

    test("should calculate top properly with position: absolute right, width, and no parent dimensions", root_node, root_layout);
  }

  @Test
  public void testCase87()
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
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = -10;
        node_1.layout.width = 10;
        node_1.layout.height = 0;
      }
    }

    test("should calculate left properly with position: absolute right, width, and no parent dimensions", root_node, root_layout);
  }

  @Test
  public void testCase88()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SPACE_BETWEEN;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.border[Spacing.BOTTOM] = 1;
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
        node_1.layout.height = 1;
      }
    }

    test("should layout border bottom inside of justify content space between container", root_node, root_layout);
  }

  @Test
  public void testCase89()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.CENTER;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.margin[Spacing.TOP] = -6;
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
        node_1.layout.y = -3;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout negative margin top inside of justify content center container", root_node, root_layout);
  }

  @Test
  public void testCase90()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.CENTER;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.margin[Spacing.TOP] = 20;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 0;
      node_0.layout.height = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 20;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 0;
      }
    }

    test("should layout positive margin top inside of justify content center container", root_node, root_layout);
  }

  @Test
  public void testCase91()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FLEX_END;
      node_0.style.border[Spacing.BOTTOM] = 5;
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
      node_0.layout.height = 5;
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

    test("should layout border bottom and flex end with an empty child", root_node, root_layout);
  }

  @Test
  public void testCase92()
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
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 800;
      node_0.layout.height = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 5;
        node_1.layout.width = 800;
        node_1.layout.height = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.y = 0;
          node_2.layout.x = 0;
          node_2.layout.width = 800;
          node_2.layout.height = 0;
        }
      }
    }

    test("should layout with children of a contain with left", root_node, root_layout);
  }

  @Test
  public void testCase93()
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
      node_0.layout.y = 0;
      node_0.layout.x = 0;
      node_0.layout.width = 100;
      node_0.layout.height = 20;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 40;
        node_1.layout.height = 10;
        node_1 = node_0.getChildAt(1);
        node_1.layout.y = 0;
        node_1.layout.x = 40;
        node_1.layout.width = 40;
        node_1.layout.height = 10;
        node_1 = node_0.getChildAt(2);
        node_1.layout.y = 10;
        node_1.layout.x = 0;
        node_1.layout.width = 40;
        node_1.layout.height = 10;
      }
    }

    test("should layout flex-wrap", root_node, root_layout);
  }

  @Test
  public void testCase94()
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
        node_1.layout.y = 0;
        node_1.layout.x = 0;
        node_1.layout.width = 0;
        node_1.layout.height = 200;
      }
    }

    test("should layout flex wrap with a line bigger than container", root_node, root_layout);
  }
  /** END_GENERATED **/
}
