/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
package com.facebook.csslayout;

import org.junit.Test;

import static junit.framework.Assert.*;

/**
 * Tests for {@link LayoutEngine} and {@link CSSNode} to make sure layouts are only generated when
 * needed.
 */
public class LayoutCachingTest {

  private void assertTreeHasNewLayout(boolean expectedHasNewLayout, CSSNode root) {
    assertEquals(expectedHasNewLayout, root.hasNewLayout());

    for (int i = 0; i < root.getChildCount(); i++) {
      assertTreeHasNewLayout(expectedHasNewLayout, root.getChildAt(i));
    }
  }

  private void markLayoutAppliedForTree(CSSNode root) {
    root.markLayoutSeen();
    for (int i = 0; i < root.getChildCount(); i++) {
      markLayoutAppliedForTree(root.getChildAt(i));
    }
  }

  @Test
  public void testCachesFullTree() {
    CSSLayoutContext layoutContext = new CSSLayoutContext();
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);

    root.calculateLayout(layoutContext);
    assertTreeHasNewLayout(true, root);
    markLayoutAppliedForTree(root);

    root.calculateLayout(layoutContext);
    assertTrue(root.hasNewLayout());
    assertTreeHasNewLayout(false, c0);
    assertTreeHasNewLayout(false, c1);
  }

  @Test
  public void testInvalidatesCacheWhenChildAdded() {
    CSSLayoutContext layoutContext = new CSSLayoutContext();
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    CSSNode c0c1 = new CSSNode();
    CSSNode c1c0 = new CSSNode();
    c0c1.setStyleWidth(200);
    c0c1.setStyleHeight(200);
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);
    c0c0.addChildAt(c1c0, 0);

    root.calculateLayout(layoutContext);
    markLayoutAppliedForTree(root);

    c0.addChildAt(c0c1, 1);

    root.calculateLayout(layoutContext);
    assertTrue(root.hasNewLayout());
    assertTrue(c0.hasNewLayout());
    assertTrue(c0c1.hasNewLayout());

    assertTrue(c0c0.hasNewLayout());
    assertTrue(c1.hasNewLayout());

    assertFalse(c1c0.hasNewLayout());
  }

  @Test
  public void testInvalidatesCacheWhenEnumPropertyChanges() {
    CSSLayoutContext layoutContext = new CSSLayoutContext();
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);

    root.calculateLayout(layoutContext);
    markLayoutAppliedForTree(root);

    c1.setAlignSelf(CSSAlign.CENTER);
    root.calculateLayout(layoutContext);

    assertTrue(root.hasNewLayout());
    assertTrue(c1.hasNewLayout());

    assertTrue(c0.hasNewLayout());
    assertFalse(c0c0.hasNewLayout());
  }

  @Test
  public void testInvalidatesCacheWhenFloatPropertyChanges() {
    CSSLayoutContext layoutContext = new CSSLayoutContext();
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);

    root.calculateLayout(layoutContext);
    markLayoutAppliedForTree(root);

    c1.setMargin(Spacing.LEFT, 10);
    root.calculateLayout(layoutContext);

    assertTrue(root.hasNewLayout());
    assertTrue(c1.hasNewLayout());

    assertTrue(c0.hasNewLayout());
    assertFalse(c0c0.hasNewLayout());
  }

  @Test
  public void testInvalidatesFullTreeWhenParentWidthChanges() {
    CSSLayoutContext layoutContext = new CSSLayoutContext();
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    CSSNode c1c0 = new CSSNode();
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);
    c1.addChildAt(c1c0, 0);

    root.calculateLayout(layoutContext);
    markLayoutAppliedForTree(root);

    c0.setStyleWidth(200);
    root.calculateLayout(layoutContext);

    assertTrue(root.hasNewLayout());
    assertTrue(c0.hasNewLayout());
    assertTrue(c0c0.hasNewLayout());

    assertTrue(c1.hasNewLayout());
    assertFalse(c1c0.hasNewLayout());
  }

  @Test
  public void testDoesNotInvalidateCacheWhenPropertyIsTheSame() {
    CSSLayoutContext layoutContext = new CSSLayoutContext();
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);
    root.setStyleWidth(200);

    root.calculateLayout(layoutContext);
    markLayoutAppliedForTree(root);

    root.setStyleWidth(200);
    root.calculateLayout(layoutContext);

    assertTrue(root.hasNewLayout());
    assertTreeHasNewLayout(false, c0);
    assertTreeHasNewLayout(false, c1);
  }

  @Test
  public void testInvalidateCacheWhenHeightChangesPosition() {
    CSSLayoutContext layoutContext = new CSSLayoutContext();
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c1c0 = new CSSNode();
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c1.addChildAt(c1c0, 0);

    root.calculateLayout(layoutContext);
    markLayoutAppliedForTree(root);

    c0.setStyleHeight(100);
    root.calculateLayout(layoutContext);

    assertTrue(root.hasNewLayout());
    assertTrue(c0.hasNewLayout());
    assertTrue(c1.hasNewLayout());
    assertFalse(c1c0.hasNewLayout());
  }

  @Test
  public void testInvalidatesOnNewMeasureFunction() {
    CSSLayoutContext layoutContext = new CSSLayoutContext();
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);

    root.calculateLayout(layoutContext);
    markLayoutAppliedForTree(root);

    c1.setMeasureFunction(new CSSNode.MeasureFunction() {
      @Override
      public void measure(CSSNode node, float width, MeasureOutput measureOutput) {
        measureOutput.width = 100;
        measureOutput.height = 20;
      }
    });

    root.calculateLayout(layoutContext);

    assertTrue(root.hasNewLayout());
    assertTrue(c1.hasNewLayout());

    assertTrue(c0.hasNewLayout());
    assertFalse(c0c0.hasNewLayout());
  }
}
