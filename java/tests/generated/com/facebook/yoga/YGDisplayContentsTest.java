/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @generated SignedSource<<be0d102e74e15f15050520f21afcaee1>>
 * generated by gentest/gentest-driver.ts from gentest/fixtures/YGDisplayContentsTest.html
 */

package com.facebook.yoga;

import static org.junit.Assert.assertEquals;

import org.junit.Ignore;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import com.facebook.yoga.utils.TestUtils;

@RunWith(Parameterized.class)
public class YGDisplayContentsTest {
  @Parameterized.Parameters(name = "{0}")
  public static Iterable<TestParametrization.NodeFactory> nodeFactories() {
    return TestParametrization.nodeFactories();
  }

  @Parameterized.Parameter public TestParametrization.NodeFactory mNodeFactory;

  @Test
  public void test_test1() {
    YogaConfig config = YogaConfigFactory.create();

    final YogaNode root = createNode(config);
    root.setFlexDirection(YogaFlexDirection.ROW);
    root.setPositionType(YogaPositionType.ABSOLUTE);
    root.setWidth(100f);
    root.setHeight(100f);

    final YogaNode root_child0 = createNode(config);
    root_child0.setDisplay(YogaDisplay.CONTENTS);
    root.addChildAt(root_child0, 0);

    final YogaNode root_child0_child0 = createNode(config);
    root_child0_child0.setFlexGrow(1f);
    root_child0_child0.setFlexShrink(1f);
    root_child0_child0.setFlexBasisPercent(0f);
    root_child0_child0.setHeight(10f);
    root_child0.addChildAt(root_child0_child0, 0);

    final YogaNode root_child0_child1 = createNode(config);
    root_child0_child1.setFlexGrow(1f);
    root_child0_child1.setFlexShrink(1f);
    root_child0_child1.setFlexBasisPercent(0f);
    root_child0_child1.setHeight(20f);
    root_child0.addChildAt(root_child0_child1, 1);
    root.setDirection(YogaDirection.LTR);
    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);

    assertEquals(0f, root.getLayoutX(), 0.0f);
    assertEquals(0f, root.getLayoutY(), 0.0f);
    assertEquals(100f, root.getLayoutWidth(), 0.0f);
    assertEquals(100f, root.getLayoutHeight(), 0.0f);

    assertEquals(0f, root_child0.getLayoutX(), 0.0f);
    assertEquals(0f, root_child0.getLayoutY(), 0.0f);
    assertEquals(0f, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(0f, root_child0.getLayoutHeight(), 0.0f);

    assertEquals(0f, root_child0_child0.getLayoutX(), 0.0f);
    assertEquals(0f, root_child0_child0.getLayoutY(), 0.0f);
    assertEquals(50f, root_child0_child0.getLayoutWidth(), 0.0f);
    assertEquals(10f, root_child0_child0.getLayoutHeight(), 0.0f);

    assertEquals(50f, root_child0_child1.getLayoutX(), 0.0f);
    assertEquals(0f, root_child0_child1.getLayoutY(), 0.0f);
    assertEquals(50f, root_child0_child1.getLayoutWidth(), 0.0f);
    assertEquals(20f, root_child0_child1.getLayoutHeight(), 0.0f);

    root.setDirection(YogaDirection.RTL);
    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);

    assertEquals(0f, root.getLayoutX(), 0.0f);
    assertEquals(0f, root.getLayoutY(), 0.0f);
    assertEquals(100f, root.getLayoutWidth(), 0.0f);
    assertEquals(100f, root.getLayoutHeight(), 0.0f);

    assertEquals(0f, root_child0.getLayoutX(), 0.0f);
    assertEquals(0f, root_child0.getLayoutY(), 0.0f);
    assertEquals(0f, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(0f, root_child0.getLayoutHeight(), 0.0f);

    assertEquals(50f, root_child0_child0.getLayoutX(), 0.0f);
    assertEquals(0f, root_child0_child0.getLayoutY(), 0.0f);
    assertEquals(50f, root_child0_child0.getLayoutWidth(), 0.0f);
    assertEquals(10f, root_child0_child0.getLayoutHeight(), 0.0f);

    assertEquals(0f, root_child0_child1.getLayoutX(), 0.0f);
    assertEquals(0f, root_child0_child1.getLayoutY(), 0.0f);
    assertEquals(50f, root_child0_child1.getLayoutWidth(), 0.0f);
    assertEquals(20f, root_child0_child1.getLayoutHeight(), 0.0f);
  }

  private YogaNode createNode(YogaConfig config) {
    return mNodeFactory.create(config);
  }
}