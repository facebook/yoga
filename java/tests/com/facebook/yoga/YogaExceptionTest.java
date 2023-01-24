/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
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
import java.util.concurrent.atomic.AtomicReference;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

@RunWith(Parameterized.class)
public class YogaExceptionTest {
  @Parameterized.Parameters(name = "{0}")
  public static Iterable<TestParametrization.NodeFactory> nodeFactories() {
    return TestParametrization.nodeFactories();
  }

  @Parameterized.Parameter public TestParametrization.NodeFactory mNodeFactory;

  @Test(expected = RuntimeException.class)
  public void testBaselineThrows() {
    final YogaNode root = createNode();
    root.setFlexDirection(YogaFlexDirection.ROW);
    root.setAlignItems(YogaAlign.BASELINE);

    final YogaNode child1 = createNode();
    root.addChildAt(child1, 0);

    final YogaNode child2 = createNode();
    child2.setBaselineFunction(new YogaBaselineFunction() {
        public float baseline(YogaNode node, float width, float height) {
          throw new RuntimeException();
        }
    });
    root.addChildAt(child2, 1);

    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
  }

  @Test
  public void testBaselineThrowsAndStops() {
    final YogaNode root = createNode();
    root.setFlexDirection(YogaFlexDirection.ROW);
    root.setAlignItems(YogaAlign.BASELINE);

    final YogaNode child1 = createNode();
    root.addChildAt(child1, 0);

    final YogaNode child2 = createNode();
    final AtomicReference<Exception> expected = new AtomicReference();
    child2.setBaselineFunction(new YogaBaselineFunction() {
        public float baseline(YogaNode node, float width, float height) {
          RuntimeException e = new RuntimeException();
          expected.set(e);
          throw e;
        }
    });
    root.addChildAt(child2, 1);

    final YogaNode child3 = createNode();
    final AtomicBoolean child3Called = new AtomicBoolean();
    child3.setBaselineFunction(new YogaBaselineFunction() {
        public float baseline(YogaNode node, float width, float height) {
          child3Called.set(true);
          return 1.0f;
        }
    });
    root.addChildAt(child3, 2);

    try {
      root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
      fail();
    } catch (RuntimeException e) {
      assertEquals(expected.get(), e);
    }
    assertFalse(child3Called.get());
  }

  @Test(expected = RuntimeException.class)
  public void testMeasureThrows() {
    final YogaNode node = createNode();
    node.setMeasureFunction(new YogaMeasureFunction() {
        public long measure(
            YogaNode node,
            float width,
            YogaMeasureMode widthMode,
            float height,
            YogaMeasureMode heightMode) {
          throw new RuntimeException();
        }
    });
    node.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
  }

  @Test
  public void testMeasureThrowsAndStops() {
    final YogaNode root = createNode();
    root.setFlexDirection(YogaFlexDirection.ROW);
    root.setAlignItems(YogaAlign.BASELINE);

    final YogaNode child1 = createNode();
    root.addChildAt(child1, 0);

    final YogaNode child2 = createNode();
    final AtomicReference<Exception> expected = new AtomicReference();
    child2.setMeasureFunction(new YogaMeasureFunction() {
        public long measure(
            YogaNode node,
            float width,
            YogaMeasureMode widthMode,
            float height,
            YogaMeasureMode heightMode) {
          RuntimeException e = new RuntimeException();
          expected.set(e);
          throw e;
        }
    });
    root.addChildAt(child2, 1);

    final YogaNode child3 = createNode();
    final AtomicBoolean child3Called = new AtomicBoolean();
    child3.setMeasureFunction(new YogaMeasureFunction() {
        public long measure(
            YogaNode node,
            float width,
            YogaMeasureMode widthMode,
            float height,
            YogaMeasureMode heightMode) {
          child3Called.set(true);
          return 1;
        }
    });
    root.addChildAt(child3, 2);

    try {
      root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
      fail();
    } catch (RuntimeException e) {
      assertEquals(expected.get(), e);
    }
    assertFalse(child3Called.get());
  }

  private YogaNode createNode() {
    return mNodeFactory.create();
  }

  private YogaNode createNode(YogaConfig config) {
    return mNodeFactory.create(config);
  }
}
