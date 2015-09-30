/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using System;
using NUnit.Framework;

namespace Facebook.CSSLayout.Tests
{
        
/**
 * Tests for {@link LayoutEngine}
 */
public class LayoutEngineTest
{
    const int POSITION_LEFT = CSSLayout.POSITION_LEFT;
    const int POSITION_TOP = CSSLayout.POSITION_TOP;
    const int POSITION_RIGHT = CSSLayout.POSITION_RIGHT;
    const int POSITION_BOTTOM = CSSLayout.POSITION_BOTTOM;
    const int DIMENSION_HEIGHT = CSSLayout.DIMENSION_HEIGHT;
    const int DIMENSION_WIDTH = CSSLayout.DIMENSION_WIDTH;
    
    static readonly MeasureFunction sTestMeasureFunction = (node, width) =>
    {
        if (CSSConstants.IsUndefined(width)) {
            width = 10000000;
        }

        TestCSSNode testNode = (TestCSSNode) node;
        if (testNode.context.Equals(TestConstants.SMALL_TEXT))
        {
            return new MeasureOutput(
                Math.Min(width, TestConstants.SMALL_WIDTH),
                TestConstants.SMALL_HEIGHT);
        } else if (testNode.context.Equals(TestConstants.LONG_TEXT))
        {
            return new MeasureOutput(width >= TestConstants.BIG_WIDTH
                ? TestConstants.BIG_WIDTH
                : Math.Max(TestConstants.BIG_MIN_WIDTH, width),
                width >= TestConstants.BIG_WIDTH
                    ? TestConstants.SMALL_HEIGHT
                    : TestConstants.BIG_HEIGHT);
        } else {
            throw new Exception("Got unknown test: " + testNode.context);
        }
    };

    private class TestCSSNode : CSSNode {

        public String context = null;

        public TestCSSNode getChildAt(int i) {
            return (TestCSSNode) base[i];
        }
    }

    private static void test(String message, CSSNode style, CSSNode expectedLayout) {
        style.CalculateLayout();
        assertLayoutsEqual(message, style, expectedLayout);
}

    private static void addChildren(TestCSSNode node, int numChildren) {
        for (int i = 0; i < numChildren; i++) {
            node.addChildAt(new TestCSSNode(), i);
        }
    }

    private static void assertLayoutsEqual(String message, CSSNode actual, CSSNode expected) {
        Assert.True(
            areLayoutsEqual(actual, expected), 
            message + "\nActual:\n" + actual.ToString() + "\nExpected:\n" + expected.ToString()
            );
}

    private static bool areLayoutsEqual(CSSNode a, CSSNode b) {
        bool doNodesHaveSameLayout =
            areFloatsEqual(a.layout.position[POSITION_LEFT], b.layout.position[POSITION_LEFT]) &&
            areFloatsEqual(a.layout.position[POSITION_TOP], b.layout.position[POSITION_TOP]) &&
            areFloatsEqual(a.layout.dimensions[DIMENSION_WIDTH], b.layout.dimensions[DIMENSION_WIDTH]) &&
            areFloatsEqual(a.layout.dimensions[DIMENSION_HEIGHT], b.layout.dimensions[DIMENSION_HEIGHT]);
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

    private static bool areFloatsEqual(float a, float b) {
        return Math.Abs(a - b) < .00001f;
    }

    /** START_GENERATED **/
    [Test]
    public void TestCase0()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
    }

    test("should layout a single node with width and height", root_node, root_layout);
  }

    [Test]
    public void TestCase1()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 500;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 250;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 250;
        node_1 = node_0.getChildAt(2);
        node_1.style.dimensions[DIMENSION_WIDTH] = 125;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 125;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 500;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 500;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 250;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 250;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 750;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 125;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 125;
      }
    }

    test("should layout node with children", root_node, root_layout);
  }

    [Test]
    public void TestCase2()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 500;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 250;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 250;
        node_1 = node_0.getChildAt(2);
        node_1.style.dimensions[DIMENSION_WIDTH] = 125;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 125;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 500;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 500;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 250;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 250;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 250;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 125;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 125;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 125;
      }
    }

    test("should layout node with children in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase3()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 500;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 500;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 500;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.dimensions[DIMENSION_WIDTH] = 250;
          node_2.style.dimensions[DIMENSION_HEIGHT] = 250;
          node_2 = node_1.getChildAt(1);
          node_2.style.dimensions[DIMENSION_WIDTH] = 250;
          node_2.style.dimensions[DIMENSION_HEIGHT] = 250;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 500;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 500;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 500;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 500;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 250;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 250;
          node_2 = node_1.getChildAt(1);
          node_2.layout.position[POSITION_TOP] = 250;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 250;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 250;
        }
      }
    }

    test("should layout node with nested children", root_node, root_layout);
  }

    [Test]
    public void TestCase4()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 500;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.style.flexDirection = CSSFlexDirection.ColumnReverse;
        node_1.style.dimensions[DIMENSION_WIDTH] = 500;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 500;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.dimensions[DIMENSION_WIDTH] = 250;
          node_2.style.dimensions[DIMENSION_HEIGHT] = 250;
          node_2 = node_1.getChildAt(1);
          node_2.style.dimensions[DIMENSION_WIDTH] = 250;
          node_2.style.dimensions[DIMENSION_HEIGHT] = 250;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 500;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 500;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 500;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 500;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 250;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 250;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 250;
          node_2 = node_1.getChildAt(1);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 250;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 250;
        }
      }
    }

    test("should layout node with nested children in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase5()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 10;
      node_0.layout.position[POSITION_LEFT] = 10;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
    }

    test("should layout node with margin", root_node, root_layout);
  }

    [Test]
    public void TestCase6()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
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
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.setMargin(Spacing.LEFT, 50);
        node_1.setMargin(Spacing.TOP, 50);
        node_1.setMargin(Spacing.RIGHT, 50);
        node_1.setMargin(Spacing.BOTTOM, 50);
        node_1.setMargin(Spacing.START, 50);
        node_1.setMargin(Spacing.END, 50);
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.setMargin(Spacing.LEFT, 25);
        node_1.setMargin(Spacing.TOP, 25);
        node_1.setMargin(Spacing.RIGHT, 25);
        node_1.setMargin(Spacing.BOTTOM, 25);
        node_1.setMargin(Spacing.START, 25);
        node_1.setMargin(Spacing.END, 25);
        node_1 = node_0.getChildAt(2);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
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
      node_0.layout.position[POSITION_TOP] = 10;
      node_0.layout.position[POSITION_LEFT] = 10;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 50;
        node_1.layout.position[POSITION_LEFT] = 50;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 225;
        node_1.layout.position[POSITION_LEFT] = 25;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 360;
        node_1.layout.position[POSITION_LEFT] = 10;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with several children", root_node, root_layout);
  }

    [Test]
    public void TestCase7()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
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
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.setMargin(Spacing.LEFT, 50);
        node_1.setMargin(Spacing.TOP, 50);
        node_1.setMargin(Spacing.RIGHT, 50);
        node_1.setMargin(Spacing.BOTTOM, 50);
        node_1.setMargin(Spacing.START, 50);
        node_1.setMargin(Spacing.END, 50);
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.setMargin(Spacing.LEFT, 25);
        node_1.setMargin(Spacing.TOP, 25);
        node_1.setMargin(Spacing.RIGHT, 25);
        node_1.setMargin(Spacing.BOTTOM, 25);
        node_1.setMargin(Spacing.START, 25);
        node_1.setMargin(Spacing.END, 25);
        node_1 = node_0.getChildAt(2);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
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
      node_0.layout.position[POSITION_TOP] = 10;
      node_0.layout.position[POSITION_LEFT] = 10;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 850;
        node_1.layout.position[POSITION_LEFT] = 50;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 675;
        node_1.layout.position[POSITION_LEFT] = 25;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 540;
        node_1.layout.position[POSITION_LEFT] = 10;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with several children in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase8()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.RowReverse;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 300;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 150;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 100;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 300;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 150;
      }
    }

    test("should layout rtl with reverse correctly", root_node, root_layout);
  }

    [Test]
    public void TestCase9()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 300;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 150;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 100;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 300;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 150;
      }
    }

    test("should layout node with row flex direction", root_node, root_layout);
  }

    [Test]
    public void TestCase10()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 300;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 150;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 900;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 600;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 300;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 150;
      }
    }

    test("should layout node with row flex direction in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase11()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 300;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 150;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 350;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 200;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 300;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 150;
      }
    }

    test("should layout node based on children main dimensions", root_node, root_layout);
  }

    [Test]
    public void TestCase12()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 300;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 150;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 350;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 150;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 300;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 150;
      }
    }

    test("should layout node based on children main dimensions in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase13()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 200;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 800;
      }
    }

    test("should layout node with just flex", root_node, root_layout);
  }

    [Test]
    public void TestCase14()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 800;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 800;
      }
    }

    test("should layout node with just flex in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase15()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.dimensions[DIMENSION_WIDTH] = 1000;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.flex = 1;
          node_2.style.dimensions[DIMENSION_WIDTH] = 1000;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.style.flex = 1;
            node_3.style.dimensions[DIMENSION_WIDTH] = 1000;
          }
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 1000;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 1000;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 1000;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 1000;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.layout.position[POSITION_TOP] = 0;
            node_3.layout.position[POSITION_LEFT] = 0;
            node_3.layout.dimensions[DIMENSION_WIDTH] = 1000;
            node_3.layout.dimensions[DIMENSION_HEIGHT] = 1000;
          }
        }
      }
    }

    test("should layout node with flex recursively", root_node, root_layout);
  }

    [Test]
    public void TestCase16()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.ColumnReverse;
        node_1.style.flex = 1;
        node_1.style.dimensions[DIMENSION_WIDTH] = 1000;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.flexDirection = CSSFlexDirection.ColumnReverse;
          node_2.style.flex = 1;
          node_2.style.dimensions[DIMENSION_WIDTH] = 1000;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.style.flexDirection = CSSFlexDirection.ColumnReverse;
            node_3.style.flex = 1;
            node_3.style.dimensions[DIMENSION_WIDTH] = 1000;
          }
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 1000;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 1000;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 1000;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 1000;
          addChildren(node_2, 1);
          {
            TestCSSNode node_3;
            node_3 = node_2.getChildAt(0);
            node_3.layout.position[POSITION_TOP] = 0;
            node_3.layout.position[POSITION_LEFT] = 0;
            node_3.layout.dimensions[DIMENSION_WIDTH] = 1000;
            node_3.layout.dimensions[DIMENSION_HEIGHT] = 1000;
          }
        }
      }
    }

    test("should layout node with flex recursively in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase17()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      node_0.setMargin(Spacing.LEFT, 5);
      node_0.setMargin(Spacing.TOP, 10);
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.setMargin(Spacing.LEFT, 15);
        node_1.setMargin(Spacing.TOP, 50);
        node_1.setMargin(Spacing.BOTTOM, 20);
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.setMargin(Spacing.LEFT, 30);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 10;
      node_0.layout.position[POSITION_LEFT] = 5;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 50;
        node_1.layout.position[POSITION_LEFT] = 15;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 170;
        node_1.layout.position[POSITION_LEFT] = 30;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with targeted margin", root_node, root_layout);
  }

    [Test]
    public void TestCase18()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      node_0.setMargin(Spacing.LEFT, 5);
      node_0.setMargin(Spacing.TOP, 10);
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.setMargin(Spacing.LEFT, 15);
        node_1.setMargin(Spacing.TOP, 50);
        node_1.setMargin(Spacing.BOTTOM, 20);
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.setMargin(Spacing.LEFT, 30);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 10;
      node_0.layout.position[POSITION_LEFT] = 5;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 880;
        node_1.layout.position[POSITION_LEFT] = 15;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 730;
        node_1.layout.position[POSITION_LEFT] = 30;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with targeted margin in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase19()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FlexStart;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: flex-start", root_node, root_layout);
  }

    [Test]
    public void TestCase20()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.justifyContent = CSSJustify.FlexStart;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 900;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 800;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: flex-start in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase21()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FlexEnd;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 800;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 900;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: flex-end", root_node, root_layout);
  }

    [Test]
    public void TestCase22()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.justifyContent = CSSJustify.FlexEnd;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: flex-end in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase23()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SpaceBetween;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 900;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: space-between", root_node, root_layout);
  }

    [Test]
    public void TestCase24()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.justifyContent = CSSJustify.SpaceBetween;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 900;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: space-between in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase25()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SpaceAround;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 200;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 700;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: space-around", root_node, root_layout);
  }

    [Test]
    public void TestCase26()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.justifyContent = CSSJustify.SpaceAround;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 700;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 200;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: space-around in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase27()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.Center;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 400;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 500;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: center", root_node, root_layout);
  }

    [Test]
    public void TestCase28()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.justifyContent = CSSJustify.Center;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 500;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 400;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with justifyContent: center in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase29()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      }
    }

    test("should layout node with flex override height", root_node, root_layout);
  }

    [Test]
    public void TestCase30()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.FlexStart;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItems: flex-start", root_node, root_layout);
  }

    [Test]
    public void TestCase31()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.alignItems = CSSAlign.FlexStart;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 900;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 800;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItems: flex-start in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase32()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.Center;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 400;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 450;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItems: center", root_node, root_layout);
  }

    [Test]
    public void TestCase33()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.alignItems = CSSAlign.Center;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 900;
        node_1.layout.position[POSITION_LEFT] = 400;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 800;
        node_1.layout.position[POSITION_LEFT] = 450;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItems: center in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase34()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.FlexEnd;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 800;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 900;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItems: flex-end", root_node, root_layout);
  }

    [Test]
    public void TestCase35()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.alignItems = CSSAlign.FlexEnd;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 900;
        node_1.layout.position[POSITION_LEFT] = 800;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 800;
        node_1.layout.position[POSITION_LEFT] = 900;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItems: flex-end in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase36()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.FlexEnd;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.Center;
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 800;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 450;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with alignSelf overrides alignItems", root_node, root_layout);
  }

    [Test]
    public void TestCase37()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.alignItems = CSSAlign.FlexEnd;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.Center;
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 900;
        node_1.layout.position[POSITION_LEFT] = 800;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 800;
        node_1.layout.position[POSITION_LEFT] = 450;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with alignSelf overrides alignItems in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase38()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.Stretch;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 1000;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItem: stretch", root_node, root_layout);
  }

    [Test]
    public void TestCase39()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.alignItems = CSSAlign.Stretch;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 900;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 1000;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout node with alignItem: stretch in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase40()
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout empty node", root_node, root_layout);
  }

    [Test]
    public void TestCase41()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout empty node in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase42()
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 10;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 5;
        node_1.layout.position[POSITION_LEFT] = 5;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout child with margin", root_node, root_layout);
  }

    [Test]
    public void TestCase43()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 10;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 5;
        node_1.layout.position[POSITION_LEFT] = 5;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout child with margin in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase44()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should not shrink children if not enough space", root_node, root_layout);
  }

    [Test]
    public void TestCase45()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = -200;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should not shrink children if not enough space in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase46()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.Center;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
    }

    test("should layout for center", root_node, root_layout);
  }

    [Test]
    public void TestCase47()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FlexEnd;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout flex-end taking into account margin", root_node, root_layout);
  }

    [Test]
    public void TestCase48()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.justifyContent = CSSJustify.FlexEnd;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 10;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout flex-end taking into account margin in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase49()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignItems = CSSAlign.FlexEnd;
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
          node_2.style.dimensions[DIMENSION_HEIGHT] = 100;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 20;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 120;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 20;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 120;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 10;
          node_2.layout.position[POSITION_LEFT] = 10;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 0;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 0;
          node_2 = node_1.getChildAt(1);
          node_2.layout.position[POSITION_TOP] = 20;
          node_2.layout.position[POSITION_LEFT] = 20;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 0;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 100;
        }
      }
    }

    test("should layout alignItems with margin", root_node, root_layout);
  }

    [Test]
    public void TestCase50()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.ColumnReverse;
        node_1.style.alignItems = CSSAlign.FlexEnd;
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
          node_2.style.dimensions[DIMENSION_HEIGHT] = 100;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 20;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 120;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 20;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 120;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 110;
          node_2.layout.position[POSITION_LEFT] = 10;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 0;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 0;
          node_2 = node_1.getChildAt(1);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 20;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 0;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 100;
        }
      }
    }

    test("should layout alignItems with margin in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase51()
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout flex inside of an empty element", root_node, root_layout);
  }

    [Test]
    public void TestCase52()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.Stretch;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 10;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 10;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout alignItems stretch and margin", root_node, root_layout);
  }

    [Test]
    public void TestCase53()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.alignItems = CSSAlign.Stretch;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 10;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 10;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout alignItems stretch and margin in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase54()
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 10;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 10;
    }

    test("should layout node with padding", root_node, root_layout);
  }

    [Test]
    public void TestCase55()
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 10;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 5;
        node_1.layout.position[POSITION_LEFT] = 5;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with padding and a child", root_node, root_layout);
  }

    [Test]
    public void TestCase56()
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 20;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 10;
        node_1.layout.position[POSITION_LEFT] = 10;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with padding and a child with margin", root_node, root_layout);
  }

    [Test]
    public void TestCase57()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.Stretch;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 20;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 20;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 20;
      }
    }

    test("should layout node with padding and stretch", root_node, root_layout);
  }

    [Test]
    public void TestCase58()
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
        node_1.style.alignSelf = CSSAlign.Stretch;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 120;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 120;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 50;
        node_1.layout.position[POSITION_LEFT] = 50;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 20;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 20;
      }
    }

    test("should layout node with inner & outer padding and stretch", root_node, root_layout);
  }

    [Test]
    public void TestCase59()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.Stretch;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 32;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 32;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 32;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 32;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 16;
          node_2.layout.position[POSITION_LEFT] = 16;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 0;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 0;
        }
      }
    }

    test("should layout node with stretch and child with margin", root_node, root_layout);
  }

    [Test]
    public void TestCase60()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.position[POSITION_LEFT] = 5;
      node_0.style.position[POSITION_TOP] = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 5;
      node_0.layout.position[POSITION_LEFT] = 5;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
    }

    test("should layout node with top and left", root_node, root_layout);
  }

    [Test]
    public void TestCase61()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SpaceAround;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 10;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 7.5f;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with height, padding and space-around", root_node, root_layout);
  }

    [Test]
    public void TestCase62()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.position[POSITION_BOTTOM] = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = -5;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
    }

    test("should layout node with bottom", root_node, root_layout);
  }

    [Test]
    public void TestCase63()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.position[POSITION_TOP] = 10;
      node_0.style.position[POSITION_BOTTOM] = 5;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 10;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
    }

    test("should layout node with both top and bottom", root_node, root_layout);
  }

    [Test]
    public void TestCase64()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 500;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1 = node_0.getChildAt(2);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 500;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 250;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 250;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 250;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 250;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with position: absolute", root_node, root_layout);
  }

    [Test]
    public void TestCase65()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.setMargin(Spacing.RIGHT, 15);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with child with position: absolute and margin", root_node, root_layout);
  }

    [Test]
    public void TestCase66()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.Center;
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.setPadding(Spacing.RIGHT, 12);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 12;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with position: absolute, padding and alignSelf: center", root_node, root_layout);
  }

    [Test]
    public void TestCase67()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 5;
      node_0.setPadding(Spacing.BOTTOM, 20);
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 20;
    }

    test("should work with height smaller than paddingBottom", root_node, root_layout);
  }

    [Test]
    public void TestCase68()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 5;
      node_0.setPadding(Spacing.LEFT, 20);
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 20;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
    }

    test("should work with width smaller than paddingLeft", root_node, root_layout);
  }

    [Test]
    public void TestCase69()
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
          node_2.style.dimensions[DIMENSION_WIDTH] = 400;
        }
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.Stretch;
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 400;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 400;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 400;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 0;
        }
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with specified width and stretch", root_node, root_layout);
  }

    [Test]
    public void TestCase70()
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
        node_1.style.positionType = CSSPositionType.Absolute;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 10;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 10;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 5;
        node_1.layout.position[POSITION_LEFT] = 5;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with padding and child with position absolute", root_node, root_layout);
  }

    [Test]
    public void TestCase71()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.position[POSITION_LEFT] = 10;
        node_1.style.position[POSITION_TOP] = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 10;
        node_1.layout.position[POSITION_LEFT] = 10;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with position absolute, top and left", root_node, root_layout);
  }

    [Test]
    public void TestCase72()
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
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.position[POSITION_LEFT] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 40;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 40;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 20;
        node_1.layout.position[POSITION_LEFT] = 5;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with padding and child position absolute, left", root_node, root_layout);
  }

    [Test]
    public void TestCase73()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.setMargin(Spacing.TOP, 5);
        node_1.style.position[POSITION_TOP] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 10;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with position: absolute, top and marginTop", root_node, root_layout);
  }

    [Test]
    public void TestCase74()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.setMargin(Spacing.LEFT, 5);
        node_1.style.position[POSITION_LEFT] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 10;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with position: absolute, left and marginLeft", root_node, root_layout);
  }

    [Test]
    public void TestCase75()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SpaceAround;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1 = node_0.getChildAt(1);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with space-around and child position absolute", root_node, root_layout);
  }

    [Test]
    public void TestCase76()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.justifyContent = CSSJustify.SpaceAround;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1 = node_0.getChildAt(1);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with space-around and child position absolute in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase77()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 700;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 700;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 5;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 695;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with flex and main margin", root_node, root_layout);
  }

    [Test]
    public void TestCase78()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 700;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 700;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 695;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with flex and main margin in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase79()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 700;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 700;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 347.5f;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 347.5f;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 352.5f;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with multiple flex and padding", root_node, root_layout);
  }

    [Test]
    public void TestCase80()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 700;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 700;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 352.5f;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 347.5f;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 352.5f;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with multiple flex and padding in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase81()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 700;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 700;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 347.5f;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 352.5f;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 347.5f;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with multiple flex and margin", root_node, root_layout);
  }

    [Test]
    public void TestCase82()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 700;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 700;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 352.5f;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 347.5f;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 347.5f;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with multiple flex and margin in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase83()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 300;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 600;
        node_1 = node_0.getChildAt(1);
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 300;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 600;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 600;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with flex and overflow", root_node, root_layout);
  }

    [Test]
    public void TestCase84()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 600;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 600;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with flex and position absolute", root_node, root_layout);
  }

    [Test]
    public void TestCase85()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 600;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 600;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 600;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with flex and position absolute in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase86()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 500;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flex = 1;
        node_1 = node_0.getChildAt(1);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.flex = 1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 500;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 500;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 500;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with double flex and position absolute", root_node, root_layout);
  }

    [Test]
    public void TestCase87()
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 10;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 10;
    }

    test("should layout node with borderWidth", root_node, root_layout);
  }

    [Test]
    public void TestCase88()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.setBorder(Spacing.TOP, 1);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.position[POSITION_TOP] = -1;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with borderWidth and position: absolute, top", root_node, root_layout);
  }

    [Test]
    public void TestCase89()
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
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.position[POSITION_LEFT] = 5;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 2;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 2;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 1;
        node_1.layout.position[POSITION_LEFT] = 6;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with borderWidth and position: absolute, top. cross axis", root_node, root_layout);
  }

    [Test]
    public void TestCase90()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.Stretch;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 50;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 40;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 20;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 40;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 40;
      }
    }

    test("should correctly take into account min padding for stretch", root_node, root_layout);
  }

    [Test]
    public void TestCase91()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = -31;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 5;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 5;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with negative width", root_node, root_layout);
  }

    [Test]
    public void TestCase92()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should handle negative margin and min padding correctly", root_node, root_layout);
  }

    [Test]
    public void TestCase93()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 1;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should handle negative margin and min padding correctly in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase94()
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 35;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 18;
    }

    test("should layout node with just text", root_node, root_layout);
  }

    [Test]
    public void TestCase95()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 10;
      node_0.setMeasureFunction(sTestMeasureFunction);
      node_0.context = "small";
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 10;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 18;
    }

    test("should layout node with text and width", root_node, root_layout);
  }

    [Test]
    public void TestCase96()
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 172;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 18;
    }

    test("should layout node with text, padding and margin", root_node, root_layout);
  }

    [Test]
    public void TestCase97()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.Stretch;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.alignSelf = CSSAlign.Stretch;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 300;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 300;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 0;
        }
      }
    }

    test("should layout node with nested alignSelf: stretch", root_node, root_layout);
  }

    [Test]
    public void TestCase98()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.Row;
        node_1.style.dimensions[DIMENSION_WIDTH] = 500;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 500;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 500;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 18;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 500;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 18;
        }
      }
    }

    test("should layout node with text and flex", root_node, root_layout);
  }

    [Test]
    public void TestCase99()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.direction = CSSDirection.RTL;
        node_1.style.flexDirection = CSSFlexDirection.Row;
        node_1.style.dimensions[DIMENSION_WIDTH] = 500;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 500;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 18;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 500;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 18;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 500;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 18;
        }
      }
    }

    test("should layout node with text and flex in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase100()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 130;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignItems = CSSAlign.Stretch;
        node_1.style.alignSelf = CSSAlign.Stretch;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 130;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 36;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 130;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 36;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 130;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 36;
        }
      }
    }

    test("should layout node with text and stretch", root_node, root_layout);
  }

    [Test]
    public void TestCase101()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignItems = CSSAlign.Stretch;
        node_1.style.alignSelf = CSSAlign.Stretch;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.dimensions[DIMENSION_WIDTH] = 130;
          node_2.setMeasureFunction(sTestMeasureFunction);
          node_2.context = "loooooooooong with space";
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 36;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 36;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 130;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 36;
        }
      }
    }

    test("should layout node with text stretch and width", root_node, root_layout);
  }

    [Test]
    public void TestCase102()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignSelf = CSSAlign.FlexStart;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.FlexStart;
        node_1.setMeasureFunction(sTestMeasureFunction);
        node_1.context = "loooooooooong with space";
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 36;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 36;
      }
    }

    test("should layout node with text bounded by parent", root_node, root_layout);
  }

    [Test]
    public void TestCase103()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignSelf = CSSAlign.FlexStart;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
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
        node_1.style.alignSelf = CSSAlign.FlexStart;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 76;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 20;
        node_1.layout.position[POSITION_LEFT] = 20;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 36;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 100;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 36;
        }
      }
    }

    test("should layout node with text bounded by grand-parent", root_node, root_layout);
  }

    [Test]
    public void TestCase104()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SpaceBetween;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 900;
        node_1 = node_0.getChildAt(1);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 900;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 900;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout space-between when remaining space is negative", root_node, root_layout);
  }

    [Test]
    public void TestCase105()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.justifyContent = CSSJustify.SpaceBetween;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 900;
        node_1 = node_0.getChildAt(1);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = -800;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 900;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = -800;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout space-between when remaining space is negative in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase106()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.justifyContent = CSSJustify.FlexEnd;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 900;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = -700;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 900;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout flex-end when remaining space is negative", root_node, root_layout);
  }

    [Test]
    public void TestCase107()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.justifyContent = CSSJustify.FlexEnd;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 900;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 900;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout flex-end when remaining space is negative in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase108()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.Row;
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 58;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 58;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 20;
          node_2.layout.position[POSITION_LEFT] = 20;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 172;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 18;
        }
      }
    }

    test("should layout text with flexDirection row", root_node, root_layout);
  }

    [Test]
    public void TestCase109()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.Row;
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 58;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 58;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 20;
          node_2.layout.position[POSITION_LEFT] = 8;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 172;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 18;
        }
      }
    }

    test("should layout text with flexDirection row in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase110()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 76;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 76;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 20;
          node_2.layout.position[POSITION_LEFT] = 20;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 160;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 36;
        }
      }
    }

    test("should layout with text and margin", root_node, root_layout);
  }

    [Test]
    public void TestCase111()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.position[POSITION_LEFT] = 0;
        node_1.style.position[POSITION_TOP] = 0;
        node_1.style.position[POSITION_RIGHT] = 0;
        node_1.style.position[POSITION_BOTTOM] = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should layout with position absolute, top, left, bottom, right", root_node, root_layout);
  }

    [Test]
    public void TestCase112()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignSelf = CSSAlign.FlexStart;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.FlexStart;
        node_1.style.flex = 2.5f;
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.FlexStart;
        node_1.style.flex = 7.5f;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 25;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 25;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 75;
      }
    }

    test("should layout with arbitrary flex", root_node, root_layout);
  }

    [Test]
    public void TestCase113()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.alignSelf = CSSAlign.FlexStart;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.FlexStart;
        node_1.style.flex = 2.5f;
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.FlexStart;
        node_1.style.flex = 7.5f;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 75;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 25;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 75;
      }
    }

    test("should layout with arbitrary flex in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase114()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.ColumnReverse;
      node_0.style.alignSelf = CSSAlign.FlexStart;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.alignSelf = CSSAlign.FlexStart;
        node_1.style.flex = -2.5f;
        node_1 = node_0.getChildAt(1);
        node_1.style.alignSelf = CSSAlign.FlexStart;
        node_1.style.flex = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout with negative flex in reverse", root_node, root_layout);
  }

    [Test]
    public void TestCase115()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.position[POSITION_LEFT] = 0;
        node_1.style.position[POSITION_RIGHT] = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 50;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout with position: absolute and another sibling", root_node, root_layout);
  }

    [Test]
    public void TestCase116()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.position[POSITION_TOP] = 0;
        node_1.style.position[POSITION_BOTTOM] = 20;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 80;
      }
    }

    test("should calculate height properly with position: absolute top and bottom", root_node, root_layout);
  }

    [Test]
    public void TestCase117()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.justifyContent = CSSJustify.Center;
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.position[POSITION_LEFT] = 0;
        node_1.style.position[POSITION_TOP] = 0;
        node_1.style.position[POSITION_RIGHT] = 0;
        node_1.style.position[POSITION_BOTTOM] = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.dimensions[DIMENSION_WIDTH] = 100;
          node_2.style.dimensions[DIMENSION_HEIGHT] = 100;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 50;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 100;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 100;
        }
      }
    }

    test("should layout with complicated position: absolute and justifyContent: center combo", root_node, root_layout);
  }

    [Test]
    public void TestCase118()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.position[POSITION_BOTTOM] = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should calculate top properly with position: absolute bottom", root_node, root_layout);
  }

    [Test]
    public void TestCase119()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.position[POSITION_RIGHT] = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 100;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should calculate left properly with position: absolute right", root_node, root_layout);
  }

    [Test]
    public void TestCase120()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 10;
        node_1.style.position[POSITION_BOTTOM] = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 90;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 10;
      }
    }

    test("should calculate top properly with position: absolute bottom and height", root_node, root_layout);
  }

    [Test]
    public void TestCase121()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.dimensions[DIMENSION_WIDTH] = 10;
        node_1.style.position[POSITION_RIGHT] = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 90;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 10;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should calculate left properly with position: absolute right and width", root_node, root_layout);
  }

    [Test]
    public void TestCase122()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 10;
        node_1.style.position[POSITION_BOTTOM] = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = -10;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 10;
      }
    }

    test("should calculate top properly with position: absolute right, width, and no parent dimensions", root_node, root_layout);
  }

    [Test]
    public void TestCase123()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.dimensions[DIMENSION_WIDTH] = 10;
        node_1.style.position[POSITION_RIGHT] = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = -10;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 10;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should calculate left properly with position: absolute right, width, and no parent dimensions", root_node, root_layout);
  }

    [Test]
    public void TestCase124()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.SpaceBetween;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 1;
      }
    }

    test("should layout border bottom inside of justify content space between container", root_node, root_layout);
  }

    [Test]
    public void TestCase125()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.Center;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = -3;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout negative margin top inside of justify content center container", root_node, root_layout);
  }

    [Test]
    public void TestCase126()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.Center;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 20;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 20;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout positive margin top inside of justify content center container", root_node, root_layout);
  }

    [Test]
    public void TestCase127()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.justifyContent = CSSJustify.FlexEnd;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 5;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout border bottom and flex end with an empty child", root_node, root_layout);
  }

    [Test]
    public void TestCase128()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 800;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.position[POSITION_LEFT] = 5;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 800;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 5;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 800;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 800;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 0;
        }
      }
    }

    test("should layout with children of a contain with left", root_node, root_layout);
  }

    [Test]
    public void TestCase129()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.flexWrap = CSSWrap.Wrap;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 40;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 10;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 40;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 10;
        node_1 = node_0.getChildAt(2);
        node_1.style.dimensions[DIMENSION_WIDTH] = 40;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 20;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 40;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 10;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 40;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 40;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 10;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 10;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 40;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 10;
      }
    }

    test("should layout flex-wrap", root_node, root_layout);
  }

    [Test]
    public void TestCase130()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.flexWrap = CSSWrap.Wrap;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 40;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 10;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 40;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 10;
        node_1 = node_0.getChildAt(2);
        node_1.style.dimensions[DIMENSION_WIDTH] = 40;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 10;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 20;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 60;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 40;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 10;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 20;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 40;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 10;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 10;
        node_1.layout.position[POSITION_LEFT] = 60;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 40;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 10;
      }
    }

    test("should layout flex-wrap in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase131()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexWrap = CSSWrap.Wrap;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 0;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should layout flex wrap with a line bigger than container", root_node, root_layout);
  }

    [Test]
    public void TestCase132()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
      node_0.style.maxWidth = 90;
      node_0.style.maxHeight = 190;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 90;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 190;
    }

    test("should use max bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase133()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
      node_0.style.minWidth = 110;
      node_0.style.minHeight = 210;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 110;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 210;
    }

    test("should use min bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase134()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
      node_0.style.maxWidth = 90;
      node_0.style.maxHeight = 190;
      node_0.style.minWidth = 110;
      node_0.style.minHeight = 210;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 110;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 210;
    }

    test("should use min bounds over max bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase135()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
      node_0.style.maxWidth = 80;
      node_0.style.maxHeight = 180;
      node_0.style.minWidth = 90;
      node_0.style.minHeight = 190;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 90;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 190;
    }

    test("should use min bounds over max bounds and natural width", root_node, root_layout);
  }

    [Test]
    public void TestCase136()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
      node_0.style.minWidth = -10;
      node_0.style.minHeight = -20;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
    }

    test("should ignore negative min bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase137()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 100;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
      node_0.style.maxWidth = -10;
      node_0.style.maxHeight = -20;
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
    }

    test("should ignore negative max bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase138()
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 40;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 30;
    }

    test("should use padded size over max bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase139()
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 50;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 40;
    }

    test("should use min size over padded size", root_node, root_layout);
  }

    [Test]
    public void TestCase140()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 50;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 250;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should override flex direction size with min bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase141()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 250;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 50;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should override flex direction size with min bounds in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase142()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 100;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 200;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should not override flex direction size within bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase143()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 200;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 100;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should not override flex direction size within bounds in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase144()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 120;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 120;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 60;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 180;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 120;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should override flex direction size with max bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase145()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 180;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 120;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 120;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 60;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 120;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should override flex direction size with max bounds in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase146()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 60;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 60;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 60;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 120;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 60;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should ignore flex size if fully max bound", root_node, root_layout);
  }

    [Test]
    public void TestCase147()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 240;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 60;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 180;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 60;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 120;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 60;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should ignore flex size if fully max bound in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase148()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 120;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 120;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 120;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 240;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 120;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should ignore flex size if fully min bound", root_node, root_layout);
  }

    [Test]
    public void TestCase149()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 3);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 180;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 120;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 60;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 120;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = -60;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 120;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should ignore flex size if fully min bound in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase150()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 300;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should pre-fill child size within bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase151()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 290;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should pre-fill child size within max bound", root_node, root_layout);
  }

    [Test]
    public void TestCase152()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 310;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
      }
    }

    test("should pre-fill child size within min bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase153()
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
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 300;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 300;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 600;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 300;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 300;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 300;
      }
    }

    test("should set parents size based on bounded children", root_node, root_layout);
  }

    [Test]
    public void TestCase154()
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
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 300;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 300;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 100;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 500;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 300;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 300;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 300;
      }
    }

    test("should set parents size based on max bounded children", root_node, root_layout);
  }

    [Test]
    public void TestCase155()
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
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 300;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 200;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 300;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 700;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 300;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 300;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 300;
      }
    }

    test("should set parents size based on min bounded children", root_node, root_layout);
  }

    [Test]
    public void TestCase156()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.Stretch;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.style.maxWidth = 1100;
        node_1.style.maxHeight = 110;
        node_1.style.minWidth = 900;
        node_1.style.minHeight = 90;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 100;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 1000;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should keep stretched size within bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase157()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.Stretch;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.style.maxWidth = 900;
        node_1.style.maxHeight = 90;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 90;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 900;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 90;
      }
    }

    test("should keep stretched size within max bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase158()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.alignItems = CSSAlign.Stretch;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.style.minWidth = 1100;
        node_1.style.minHeight = 110;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 110;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 1100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 110;
      }
    }

    test("should keep stretched size within min bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase159()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.style.minWidth = 100;
        node_1.style.minHeight = 110;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 110;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 110;
      }
    }

    test("should keep cross axis size within min bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase160()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.style.minWidth = 100;
        node_1.style.minHeight = 110;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 110;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 900;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 110;
      }
    }

    test("should keep cross axis size within min bounds in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase161()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.maxWidth = 500;
        node_1.style.maxHeight = 600;
        node_1.style.position[POSITION_LEFT] = 100;
        node_1.style.position[POSITION_TOP] = 100;
        node_1.style.position[POSITION_RIGHT] = 100;
        node_1.style.position[POSITION_BOTTOM] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 100;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 500;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 600;
      }
    }

    test("should layout node with position absolute, top and left and max bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase162()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.style.minWidth = 900;
        node_1.style.minHeight = 1000;
        node_1.style.position[POSITION_LEFT] = 100;
        node_1.style.position[POSITION_TOP] = 100;
        node_1.style.position[POSITION_RIGHT] = 100;
        node_1.style.position[POSITION_BOTTOM] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 1000;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 100;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 900;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 1000;
      }
    }

    test("should layout node with position absolute, top and left and min bounds", root_node, root_layout);
  }

    [Test]
    public void TestCase163()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 400;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 400;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
        node_1.setPadding(Spacing.LEFT, 10);
        node_1.setPadding(Spacing.TOP, 10);
        node_1.setPadding(Spacing.RIGHT, 10);
        node_1.setPadding(Spacing.BOTTOM, 10);
        node_1.setPadding(Spacing.START, 10);
        node_1.setPadding(Spacing.END, 10);
        node_1.style.position[POSITION_LEFT] = 100;
        node_1.style.position[POSITION_TOP] = 100;
        node_1.style.position[POSITION_RIGHT] = 100;
        node_1.style.position[POSITION_BOTTOM] = 100;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.positionType = CSSPositionType.Absolute;
          node_2.style.position[POSITION_LEFT] = 10;
          node_2.style.position[POSITION_TOP] = 10;
          node_2.style.position[POSITION_RIGHT] = 10;
          node_2.style.position[POSITION_BOTTOM] = 10;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 400;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 400;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 100;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 10;
          node_2.layout.position[POSITION_LEFT] = 10;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 180;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 180;
        }
      }
    }

    test("should layout absolutely positioned node with absolutely positioned padded parent", root_node, root_layout);
  }

    [Test]
    public void TestCase164()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 400;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 400;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.positionType = CSSPositionType.Absolute;
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
        node_1.style.position[POSITION_LEFT] = 100;
        node_1.style.position[POSITION_TOP] = 100;
        node_1.style.position[POSITION_RIGHT] = 100;
        node_1.style.position[POSITION_BOTTOM] = 100;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.positionType = CSSPositionType.Absolute;
          node_2.style.position[POSITION_LEFT] = 10;
          node_2.style.position[POSITION_TOP] = 10;
          node_2.style.position[POSITION_RIGHT] = 10;
          node_2.style.position[POSITION_BOTTOM] = 10;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 400;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 400;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 100;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 200;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 11;
          node_2.layout.position[POSITION_LEFT] = 11;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 178;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 178;
        }
      }
    }

    test("should layout absolutely positioned node with absolutely positioned padded and bordered parent", root_node, root_layout);
  }

    [Test]
    public void TestCase165()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 400;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 400;
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
          node_2.style.positionType = CSSPositionType.Absolute;
          node_2.style.position[POSITION_LEFT] = 10;
          node_2.style.position[POSITION_TOP] = 10;
          node_2.style.position[POSITION_RIGHT] = 10;
          node_2.style.position[POSITION_BOTTOM] = 10;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 400;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 400;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 400;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 400;
        addChildren(node_1, 1);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 10;
          node_2.layout.position[POSITION_LEFT] = 10;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 380;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 380;
        }
      }
    }

    test("should layout absolutely positioned node with padded flex 1 parent", root_node, root_layout);
  }

    [Test]
    public void TestCase166()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.flexDirection = CSSFlexDirection.Row;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.dimensions[DIMENSION_WIDTH] = 50;
          node_2.style.dimensions[DIMENSION_HEIGHT] = 50;
          node_2 = node_1.getChildAt(1);
          node_2.style.dimensions[DIMENSION_WIDTH] = 50;
          node_2.style.dimensions[DIMENSION_HEIGHT] = 50;
        }
        node_1 = node_0.getChildAt(1);
        node_1.style.direction = CSSDirection.LTR;
        node_1.style.flexDirection = CSSFlexDirection.Row;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.style.dimensions[DIMENSION_WIDTH] = 50;
          node_2.style.dimensions[DIMENSION_HEIGHT] = 50;
          node_2 = node_1.getChildAt(1);
          node_2.style.dimensions[DIMENSION_WIDTH] = 50;
          node_2.style.dimensions[DIMENSION_HEIGHT] = 50;
        }
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 2);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 150;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 50;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 50;
          node_2 = node_1.getChildAt(1);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 100;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 50;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 50;
        }
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 50;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 200;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        addChildren(node_1, 2);
        {
          TestCSSNode node_2;
          node_2 = node_1.getChildAt(0);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 0;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 50;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 50;
          node_2 = node_1.getChildAt(1);
          node_2.layout.position[POSITION_TOP] = 0;
          node_2.layout.position[POSITION_LEFT] = 50;
          node_2.layout.dimensions[DIMENSION_WIDTH] = 50;
          node_2.layout.dimensions[DIMENSION_HEIGHT] = 50;
        }
      }
    }

    test("should layout nested nodes with mixed directions", root_node, root_layout);
  }

    [Test]
    public void TestCase167()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.justifyContent = CSSJustify.SpaceBetween;
      node_0.style.flexWrap = CSSWrap.Wrap;
      node_0.style.dimensions[DIMENSION_WIDTH] = 320;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 6);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(2);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(3);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(4);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(5);
        node_1.style.dimensions[DIMENSION_WIDTH] = 100;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 320;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 200;
      addChildren(node_0, 6);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 110;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 220;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(3);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(4);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 110;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(5);
        node_1.layout.position[POSITION_TOP] = 100;
        node_1.layout.position[POSITION_LEFT] = 220;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 100;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
      }
    }

    test("should correctly space wrapped nodes", root_node, root_layout);
  }

    [Test]
    public void TestCase168()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      node_0.setPadding(Spacing.LEFT, 5);
      node_0.setPadding(Spacing.RIGHT, 5);
      node_0.setPadding(Spacing.START, 15);
      node_0.setPadding(Spacing.END, 15);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 15;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 170;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    test("should give start/end padding precedence over left/right padding", root_node, root_layout);
  }

    [Test]
    public void TestCase169()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 5);
        node_1.setMargin(Spacing.RIGHT, 5);
        node_1.setMargin(Spacing.START, 15);
        node_1.setMargin(Spacing.END, 15);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 15;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 170;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    test("should give start/end margin precedence over left/right margin", root_node, root_layout);
  }

    [Test]
    public void TestCase170()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      node_0.setBorder(Spacing.LEFT, 5);
      node_0.setBorder(Spacing.RIGHT, 5);
      node_0.setBorder(Spacing.START, 15);
      node_0.setBorder(Spacing.END, 15);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 15;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 170;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    test("should give start/end border precedence over left/right border", root_node, root_layout);
  }

    [Test]
    public void TestCase171()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      node_0.setPadding(Spacing.START, 15);
      node_0.setPadding(Spacing.END, 5);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 15;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 180;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    test("should layout node with correct start/end padding", root_node, root_layout);
  }

    [Test]
    public void TestCase172()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      node_0.setPadding(Spacing.START, 15);
      node_0.setPadding(Spacing.END, 5);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 5;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 180;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    test("should layout node with correct start/end padding in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase173()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.START, 15);
        node_1.setMargin(Spacing.END, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 15;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 180;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    test("should layout node with correct start/end margin", root_node, root_layout);
  }

    [Test]
    public void TestCase174()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.direction = CSSDirection.RTL;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.START, 15);
        node_1.setMargin(Spacing.END, 5);
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 5;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 180;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    test("should layout node with correct start/end margin in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase175()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      node_0.setBorder(Spacing.START, 15);
      node_0.setBorder(Spacing.END, 5);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 15;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 180;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    test("should layout node with correct start/end border", root_node, root_layout);
  }

    [Test]
    public void TestCase176()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.direction = CSSDirection.RTL;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      node_0.setBorder(Spacing.START, 15);
      node_0.setBorder(Spacing.END, 5);
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 50;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 5;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 180;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    test("should layout node with correct start/end border in rtl", root_node, root_layout);
  }

    [Test]
    public void TestCase177()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.dimensions[DIMENSION_WIDTH] = 200;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 0;
      }
    }

    TestCSSNode root_layout = new TestCSSNode();
    {
      TestCSSNode node_0 = root_layout;
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 200;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 0;
      addChildren(node_0, 1);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 0;
        node_1.layout.position[POSITION_LEFT] = 0;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 0;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 0;
      }
    }

    test("should layout node with a 0 width", root_node, root_layout);
  }

    [Test]
    public void TestCase178()
  {
    TestCSSNode root_node = new TestCSSNode();
    {
      TestCSSNode node_0 = root_node;
      node_0.style.flexDirection = CSSFlexDirection.Row;
      node_0.style.alignContent = CSSAlign.Stretch;
      node_0.style.alignItems = CSSAlign.FlexStart;
      node_0.style.flexWrap = CSSWrap.Wrap;
      node_0.style.dimensions[DIMENSION_WIDTH] = 300;
      node_0.style.dimensions[DIMENSION_HEIGHT] = 380;
      addChildren(node_0, 15);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(1);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(2);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(3);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(4);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(5);
        node_1.style.alignSelf = CSSAlign.FlexStart;
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(6);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(7);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 100;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(8);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(9);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(10);
        node_1.style.alignSelf = CSSAlign.FlexStart;
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(11);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(12);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(13);
        node_1.style.alignSelf = CSSAlign.FlexStart;
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
        node_1.setMargin(Spacing.LEFT, 10);
        node_1.setMargin(Spacing.TOP, 10);
        node_1.setMargin(Spacing.RIGHT, 10);
        node_1.setMargin(Spacing.BOTTOM, 10);
        node_1.setMargin(Spacing.START, 10);
        node_1.setMargin(Spacing.END, 10);
        node_1 = node_0.getChildAt(14);
        node_1.style.dimensions[DIMENSION_WIDTH] = 50;
        node_1.style.dimensions[DIMENSION_HEIGHT] = 50;
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
      node_0.layout.position[POSITION_TOP] = 0;
      node_0.layout.position[POSITION_LEFT] = 0;
      node_0.layout.dimensions[DIMENSION_WIDTH] = 300;
      node_0.layout.dimensions[DIMENSION_HEIGHT] = 380;
      addChildren(node_0, 15);
      {
        TestCSSNode node_1;
        node_1 = node_0.getChildAt(0);
        node_1.layout.position[POSITION_TOP] = 10;
        node_1.layout.position[POSITION_LEFT] = 10;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        node_1 = node_0.getChildAt(1);
        node_1.layout.position[POSITION_TOP] = 10;
        node_1.layout.position[POSITION_LEFT] = 80;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        node_1 = node_0.getChildAt(2);
        node_1.layout.position[POSITION_TOP] = 10;
        node_1.layout.position[POSITION_LEFT] = 150;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        node_1 = node_0.getChildAt(3);
        node_1.layout.position[POSITION_TOP] = 10;
        node_1.layout.position[POSITION_LEFT] = 220;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        node_1 = node_0.getChildAt(4);
        node_1.layout.position[POSITION_TOP] = 92.5f;
        node_1.layout.position[POSITION_LEFT] = 10;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(5);
        node_1.layout.position[POSITION_TOP] = 92.5f;
        node_1.layout.position[POSITION_LEFT] = 80;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        node_1 = node_0.getChildAt(6);
        node_1.layout.position[POSITION_TOP] = 92.5f;
        node_1.layout.position[POSITION_LEFT] = 150;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        node_1 = node_0.getChildAt(7);
        node_1.layout.position[POSITION_TOP] = 92.5f;
        node_1.layout.position[POSITION_LEFT] = 220;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 100;
        node_1 = node_0.getChildAt(8);
        node_1.layout.position[POSITION_TOP] = 225;
        node_1.layout.position[POSITION_LEFT] = 10;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        node_1 = node_0.getChildAt(9);
        node_1.layout.position[POSITION_TOP] = 225;
        node_1.layout.position[POSITION_LEFT] = 80;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        node_1 = node_0.getChildAt(10);
        node_1.layout.position[POSITION_TOP] = 225;
        node_1.layout.position[POSITION_LEFT] = 150;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        node_1 = node_0.getChildAt(11);
        node_1.layout.position[POSITION_TOP] = 225;
        node_1.layout.position[POSITION_LEFT] = 220;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        node_1 = node_0.getChildAt(12);
        node_1.layout.position[POSITION_TOP] = 307.5f;
        node_1.layout.position[POSITION_LEFT] = 10;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        node_1 = node_0.getChildAt(13);
        node_1.layout.position[POSITION_TOP] = 307.5f;
        node_1.layout.position[POSITION_LEFT] = 80;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
        node_1 = node_0.getChildAt(14);
        node_1.layout.position[POSITION_TOP] = 307.5f;
        node_1.layout.position[POSITION_LEFT] = 150;
        node_1.layout.dimensions[DIMENSION_WIDTH] = 50;
        node_1.layout.dimensions[DIMENSION_HEIGHT] = 50;
      }
    }

    test("should layout with alignContent: stretch, and alignItems: flex-start", root_node, root_layout);
  }
  /** END_GENERATED **/
}

}

