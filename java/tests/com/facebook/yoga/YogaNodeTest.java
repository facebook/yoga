/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotSame;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicBoolean;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

@RunWith(Parameterized.class)
public class YogaNodeTest {
  @Parameterized.Parameters(name = "{0}")
  public static Iterable<TestParametrization.NodeFactory> nodeFactories() {
    return TestParametrization.nodeFactories();
  }

  @Parameterized.Parameter public TestParametrization.NodeFactory mNodeFactory;

  @Test
  public void testInit() {
    TestUtil.startCountingNodes();
    final YogaNode node = createNode();
    assertEquals(1, TestUtil.stopCountingNodes());
  }

  @Test
  public void testBaseline() {
    final YogaNode root = createNode();
    root.setFlexDirection(YogaFlexDirection.ROW);
    root.setAlignItems(YogaAlign.BASELINE);
    root.setWidth(100);
    root.setHeight(100);

    final YogaNode child1 = createNode();
    child1.setWidth(40);
    child1.setHeight(40);
    root.addChildAt(child1, 0);

    final YogaNode child2 = createNode();
    child2.setWidth(40);
    child2.setHeight(40);
    child2.setBaselineFunction(new YogaBaselineFunction() {
        public float baseline(YogaNode node, float width, float height) {
          return 0;
        }
    });
    root.addChildAt(child2, 1);

    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);

    assertEquals(0, (int) child1.getLayoutY());
    assertEquals(40, (int) child2.getLayoutY());
  }

  @Test
  public void testMeasure() {
    final YogaNode node = createNode();
    node.setMeasureFunction(new YogaMeasureFunction() {
        public long measure(
            YogaNode node,
            float width,
            YogaMeasureMode widthMode,
            float height,
            YogaMeasureMode heightMode) {
          return YogaMeasureOutput.make(100, 100);
        }
    });
    node.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    assertEquals(100, (int) node.getLayoutWidth());
    assertEquals(100, (int) node.getLayoutHeight());
  }

  @Test
  public void testMeasureFloat() {
    final YogaNode node = createNode();
    node.setMeasureFunction(new YogaMeasureFunction() {
        public long measure(
            YogaNode node,
            float width,
            YogaMeasureMode widthMode,
            float height,
            YogaMeasureMode heightMode) {
          return YogaMeasureOutput.make(100.5f, 100.5f);
        }
    });
    node.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    assertEquals(101f, node.getLayoutWidth(), 0.01f);
    assertEquals(101f, node.getLayoutHeight(), 0.01f);
  }

  @Test
  public void testMeasureFloatMin() {
    final YogaNode node = createNode();
    node.setMeasureFunction(new YogaMeasureFunction() {
        public long measure(
            YogaNode node,
            float width,
            YogaMeasureMode widthMode,
            float height,
            YogaMeasureMode heightMode) {
          return YogaMeasureOutput.make(Float.MIN_VALUE, Float.MIN_VALUE);
        }
    });
    node.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    assertEquals(Float.MIN_VALUE, node.getLayoutWidth(), 0.01f);
    assertEquals(Float.MIN_VALUE, node.getLayoutHeight(), 0.01f);
  }

  @Test
  public void testMeasureFloatBigNumber() {
    final YogaNode node = createNode();
    final float bigNumber = (float) 10E5;
    node.setMeasureFunction(
        new YogaMeasureFunction() {
          public long measure(
              YogaNode node,
              float width,
              YogaMeasureMode widthMode,
              float height,
              YogaMeasureMode heightMode) {
            return YogaMeasureOutput.make(bigNumber, bigNumber);
          }
        });
    node.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    assertEquals(bigNumber, node.getLayoutWidth(), 0.01f);
    assertEquals(bigNumber, node.getLayoutHeight(), 0.01f);
  }

  @Test
  public void testCopyStyle() {
    final YogaNode node0 = createNode();
    assertTrue(YogaConstants.isUndefined(node0.getMaxHeight()));

    final YogaNode node1 = createNode();
    node1.setMaxHeight(100);

    node0.copyStyle(node1);
    assertEquals(100, (int) node0.getMaxHeight().value);
  }

  @Test
  public void testLayoutMargin() {
    final YogaNode node = createNode();
    node.setWidth(100);
    node.setHeight(100);
    node.setMargin(YogaEdge.START, 1);
    node.setMargin(YogaEdge.END, 2);
    node.setMargin(YogaEdge.TOP, 3);
    node.setMargin(YogaEdge.BOTTOM, 4);
    node.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);

    assertEquals(1, (int) node.getLayoutMargin(YogaEdge.LEFT));
    assertEquals(2, (int) node.getLayoutMargin(YogaEdge.RIGHT));
    assertEquals(3, (int) node.getLayoutMargin(YogaEdge.TOP));
    assertEquals(4, (int) node.getLayoutMargin(YogaEdge.BOTTOM));
  }

  @Test
  public void testLayoutPadding() {
    final YogaNode node = createNode();
    node.setWidth(100);
    node.setHeight(100);
    node.setPadding(YogaEdge.START, 1);
    node.setPadding(YogaEdge.END, 2);
    node.setPadding(YogaEdge.TOP, 3);
    node.setPadding(YogaEdge.BOTTOM, 4);
    node.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);

    assertEquals(1, (int) node.getLayoutPadding(YogaEdge.LEFT));
    assertEquals(2, (int) node.getLayoutPadding(YogaEdge.RIGHT));
    assertEquals(3, (int) node.getLayoutPadding(YogaEdge.TOP));
    assertEquals(4, (int) node.getLayoutPadding(YogaEdge.BOTTOM));
  }

  @Test
  public void testLayoutBorder() {
    final YogaNode node = createNode();
    node.setWidth(100);
    node.setHeight(100);
    node.setBorder(YogaEdge.START, 1);
    node.setBorder(YogaEdge.END, 2);
    node.setBorder(YogaEdge.TOP, 3);
    node.setBorder(YogaEdge.BOTTOM, 4);
    node.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);

    assertEquals(1, (int) node.getLayoutBorder(YogaEdge.LEFT));
    assertEquals(2, (int) node.getLayoutBorder(YogaEdge.RIGHT));
    assertEquals(3, (int) node.getLayoutBorder(YogaEdge.TOP));
    assertEquals(4, (int) node.getLayoutBorder(YogaEdge.BOTTOM));
  }

  @Test
  public void testUseWebDefaults() {
    final YogaConfig config = YogaConfigFactory.create();
    config.setUseWebDefaults(true);
    final YogaNode node = createNode(config);
    assertEquals(YogaFlexDirection.ROW, node.getFlexDirection());
  }

  @Test
  public void testPercentPaddingOnRoot() {
    final YogaNode node = createNode();
    node.setPaddingPercent(YogaEdge.ALL, 10);
    node.calculateLayout(50, 50);

    assertEquals(5, (int) node.getLayoutPadding(YogaEdge.LEFT));
    assertEquals(5, (int) node.getLayoutPadding(YogaEdge.RIGHT));
    assertEquals(5, (int) node.getLayoutPadding(YogaEdge.TOP));
    assertEquals(5, (int) node.getLayoutPadding(YogaEdge.BOTTOM));
  }

  @Test
  public void testDefaultEdgeValues() {
    final YogaNode node = createNode();

    for (YogaEdge edge : YogaEdge.values()) {
      assertEquals(YogaUnit.UNDEFINED, node.getMargin(edge).unit);
      assertEquals(YogaUnit.UNDEFINED, node.getPadding(edge).unit);
      assertEquals(YogaUnit.UNDEFINED, node.getPosition(edge).unit);
      assertTrue(YogaConstants.isUndefined(node.getBorder(edge)));
    }
  }

  @Test
  public void testFlagShouldDiffLayoutWithoutLegacyStretchBehaviour() throws Exception {
    YogaConfig config = YogaConfigFactory.create();
    config.setShouldDiffLayoutWithoutLegacyStretchBehaviour(true);
    config.setUseLegacyStretchBehaviour(true);
    YogaNode root = createNode(config);
    root.setWidth(500);
    root.setHeight(500);
    YogaNode root_child0 = createNode(config);
    root_child0.setAlignItems(YogaAlign.FLEX_START);
    root.addChildAt(root_child0, 0);
    YogaNode root_child0_child0 = createNode(config);
    root_child0_child0.setFlexGrow(1);
    root_child0_child0.setFlexShrink(1);
    root_child0.addChildAt(root_child0_child0, 0);
    YogaNode root_child0_child0_child0 = createNode(config);
    root_child0_child0_child0.setFlexGrow(1);
    root_child0_child0_child0.setFlexShrink(1);
    root_child0_child0.addChildAt(root_child0_child0_child0, 0);
    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    assertTrue(((YogaNodeJNIBase) root).getDoesLegacyStretchFlagAffectsLayout());
  }

  @Test
  public void initiallyHasNewLayout() {
    YogaNode root = createNode();
    assertTrue(root.hasNewLayout());
  }

  @Test
  public void initialLayoutCanBeMarkedSeen() {
    YogaNode root = createNode();
    root.markLayoutSeen();
    assertFalse(root.hasNewLayout());
  }

  @Test
  public void calculatingLayoutMarksLayoutAsUnseen() {
    YogaNode root = createNode();
    root.markLayoutSeen();
    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    assertTrue(root.hasNewLayout());
  }

  @Test
  public void calculatedLayoutCanBeMarkedSeen() {
    YogaNode root = createNode();
    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    root.markLayoutSeen();
    assertFalse(root.hasNewLayout());
  }

  @Test
  public void recalculatingLayoutDoesMarkAsUnseen() {
    YogaNode root = createNode();
    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    root.markLayoutSeen();
    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    assertTrue(root.hasNewLayout());
  }

  @Test
  public void resetAlsoResetsLayoutSeen() {
    YogaNode root = createNode();
    root.markLayoutSeen();
    root.reset();
    assertTrue(root.hasNewLayout());
  }

  @Test
  public void directionIsPassedThrough() {
    YogaNode root = createNode();

    root.setDirection(YogaDirection.RTL);
    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);

    assertEquals(root.getLayoutDirection(), YogaDirection.RTL);
  }

  @Test
  public void testResetApiShouldResetAllLayoutOutputs() {
    YogaConfig config = YogaConfigFactory.create();
    config.setShouldDiffLayoutWithoutLegacyStretchBehaviour(true);
    config.setUseLegacyStretchBehaviour(true);
    YogaNode node = createNode(config);
    node.setWidth(100);
    node.setHeight(100);
    node.setMargin(YogaEdge.START, 1);
    node.setMargin(YogaEdge.END, 2);
    node.setMargin(YogaEdge.TOP, 3);
    node.setMargin(YogaEdge.BOTTOM, 4);
    node.setPadding(YogaEdge.START, 1);
    node.setPadding(YogaEdge.END, 2);
    node.setPadding(YogaEdge.TOP, 3);
    node.setPadding(YogaEdge.BOTTOM, 4);
    node.setBorder(YogaEdge.START, 1);
    node.setBorder(YogaEdge.END, 2);
    node.setBorder(YogaEdge.TOP, 3);
    node.setBorder(YogaEdge.BOTTOM, 4);
    node.setDirection(YogaDirection.RTL);
    node.markLayoutSeen();
    node.setMeasureFunction(new YogaMeasureFunction(){
      @Override
      public long measure(YogaNode node, float width, YogaMeasureMode widthMode, float height,
          YogaMeasureMode heightMode) {
        return YogaMeasureOutput.make(100, 100);
      }
    });
    node.setBaselineFunction(new YogaBaselineFunction(){

      @Override
      public float baseline(YogaNode node, float width, float height) {
        return height;
      }
    });
    node.setData(new ArrayList<>());

    node.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    node.reset();

    assertEquals(0, (int) node.getLayoutHeight());
    assertEquals(0, (int) node.getLayoutWidth());
    assertEquals(0, (int) node.getLayoutMargin(YogaEdge.LEFT));
    assertEquals(0, (int) node.getLayoutMargin(YogaEdge.RIGHT));
    assertEquals(0, (int) node.getLayoutMargin(YogaEdge.TOP));
    assertEquals(0, (int) node.getLayoutMargin(YogaEdge.BOTTOM));
    assertEquals(0, (int) node.getLayoutPadding(YogaEdge.LEFT));
    assertEquals(0, (int) node.getLayoutPadding(YogaEdge.RIGHT));
    assertEquals(0, (int) node.getLayoutPadding(YogaEdge.TOP));
    assertEquals(0, (int) node.getLayoutPadding(YogaEdge.BOTTOM));
    assertEquals(0, (int) node.getLayoutBorder(YogaEdge.LEFT));
    assertEquals(0, (int) node.getLayoutBorder(YogaEdge.RIGHT));
    assertEquals(0, (int) node.getLayoutBorder(YogaEdge.TOP));
    assertEquals(0, (int) node.getLayoutBorder(YogaEdge.BOTTOM));
    assertEquals(node.getLayoutDirection(), YogaDirection.INHERIT);
    assertTrue(node.hasNewLayout());
    assertFalse(node.isMeasureDefined());
    assertFalse(node.isBaselineDefined());
    assertFalse(((YogaNodeJNIBase) node).getDoesLegacyStretchFlagAffectsLayout());
    assertEquals(null, node.getData());
  }

  private YogaNode createNode() {
    return mNodeFactory.create();
  }

  private YogaNode createNode(YogaConfig config) {
    return mNodeFactory.create(config);
  }
}
