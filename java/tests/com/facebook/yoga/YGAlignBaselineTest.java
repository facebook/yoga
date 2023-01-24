/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga;

import static org.junit.Assert.assertEquals;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

@RunWith(Parameterized.class)
public class YGAlignBaselineTest {
  @Parameterized.Parameters(name = "{0}")
  public static Iterable<TestParametrization.NodeFactory> nodeFactories() {
    return TestParametrization.nodeFactories();
  }

  @Parameterized.Parameter public TestParametrization.NodeFactory mNodeFactory;

  private YogaBaselineFunction getBaselineFunc() {
    return new YogaBaselineFunction() {
      @Override
      public float baseline(YogaNode node, float width, float height) {
        return height / 2;
      }
    };
  }

  @Test
  public void test_align_baseline_parent_using_child_in_column_as_reference() {
    YogaConfig config = YogaConfigFactory.create();

    final YogaNode root = createYGNode(config, YogaFlexDirection.ROW, 1000f, 1000f, true);

    final YogaNode root_child0 = createYGNode(config, YogaFlexDirection.COLUMN, 500f, 600f, false);
    root.addChildAt(root_child0, 0);

    final YogaNode root_child1 = createYGNode(config, YogaFlexDirection.COLUMN, 500f, 800f, false);
    root.addChildAt(root_child1, 1);

    final YogaNode root_child1_child0 =
        createYGNode(config, YogaFlexDirection.COLUMN, 500f, 300f, false);
    root_child1.addChildAt(root_child1_child0, 0);

    final YogaNode root_child1_child1 =
        createYGNode(config, YogaFlexDirection.COLUMN, 500f, 400f, false);
    root_child1_child1.setBaselineFunction(getBaselineFunc());
    root_child1_child1.setIsReferenceBaseline(true);
    root_child1.addChildAt(root_child1_child1, 1);

    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);

    assertEquals(0f, root_child0.getLayoutX(), 0.0f);
    assertEquals(0f, root_child0.getLayoutY(), 0.0f);

    assertEquals(500f, root_child1.getLayoutX(), 0.0f);
    assertEquals(100f, root_child1.getLayoutY(), 0.0f);

    assertEquals(0f, root_child1_child0.getLayoutX(), 0.0f);
    assertEquals(0f, root_child1_child0.getLayoutY(), 0.0f);

    assertEquals(0f, root_child1_child1.getLayoutX(), 0.0f);
    assertEquals(300f, root_child1_child1.getLayoutY(), 0.0f);
  }

  @Test
  public void test_align_baseline_parent_using_child_in_row_as_reference() {
    YogaConfig config = YogaConfigFactory.create();

    final YogaNode root = createYGNode(config, YogaFlexDirection.ROW, 1000f, 1000f, true);

    final YogaNode root_child0 = createYGNode(config, YogaFlexDirection.COLUMN, 500f, 600f, false);
    root.addChildAt(root_child0, 0);

    final YogaNode root_child1 = createYGNode(config, YogaFlexDirection.ROW, 500f, 800f, true);
    root.addChildAt(root_child1, 1);

    final YogaNode root_child1_child0 =
        createYGNode(config, YogaFlexDirection.COLUMN, 500f, 500f, false);
    root_child1.addChildAt(root_child1_child0, 0);

    final YogaNode root_child1_child1 =
        createYGNode(config, YogaFlexDirection.COLUMN, 500f, 400f, false);
    root_child1_child1.setBaselineFunction(getBaselineFunc());
    root_child1_child1.setIsReferenceBaseline(true);
    root_child1.addChildAt(root_child1_child1, 1);

    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);

    assertEquals(0f, root_child0.getLayoutX(), 0.0f);
    assertEquals(0f, root_child0.getLayoutY(), 0.0f);

    assertEquals(500f, root_child1.getLayoutX(), 0.0f);
    assertEquals(100f, root_child1.getLayoutY(), 0.0f);

    assertEquals(0f, root_child1_child0.getLayoutX(), 0.0f);
    assertEquals(0f, root_child1_child0.getLayoutY(), 0.0f);

    assertEquals(500f, root_child1_child1.getLayoutX(), 0.0f);
    assertEquals(300f, root_child1_child1.getLayoutY(), 0.0f);
  }

  private YogaNode createYGNode(
      YogaConfig config,
      YogaFlexDirection flexDirection,
      float width,
      float height,
      boolean alignBaseline) {
    YogaNode node = mNodeFactory.create(config);
    node.setFlexDirection(flexDirection);
    node.setWidth(width);
    node.setHeight(height);
    if (alignBaseline) {
      node.setAlignItems(YogaAlign.BASELINE);
    }
    return node;
  }
}
