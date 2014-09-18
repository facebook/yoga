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
    root.markLayoutApplied();
    for (int i = 0; i < root.getChildCount(); i++) {
      markLayoutAppliedForTree(root.getChildAt(i));
    }
  }

  @Test
  public void testCachesFullTree() {
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);

    root.calculateLayout();
    assertTreeHasNewLayout(true, root);
    markLayoutAppliedForTree(root);

    root.calculateLayout();
    assertTreeHasNewLayout(false, root);
  }

  @Test
  public void testInvalidatesCacheWhenChildAdded() {
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    CSSNode c0c1 = new CSSNode();
    c0c1.setStyleWidth(200);
    c0c1.setStyleHeight(200);
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);

    root.calculateLayout();
    assertTreeHasNewLayout(true, root);
    markLayoutAppliedForTree(root);

    root.calculateLayout();
    assertTreeHasNewLayout(false, root);

    c0.addChildAt(c0c1, 1);

    root.calculateLayout();
    assertTrue(root.hasNewLayout());
    assertTrue(c0.hasNewLayout());
    assertTrue(c0c1.hasNewLayout());

    assertFalse(c0c0.hasNewLayout());
    assertFalse(c1.hasNewLayout());
  }

  @Test
  public void testInvalidatesCacheWhenEnumPropertyChanges() {
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);

    root.calculateLayout();
    assertTreeHasNewLayout(true, root);
    markLayoutAppliedForTree(root);

    root.calculateLayout();
    assertTreeHasNewLayout(false, root);

    c1.setAlignSelf(CSSAlign.CENTER);
    root.calculateLayout();

    assertTrue(root.hasNewLayout());
    assertTrue(c1.hasNewLayout());

    assertFalse(c0.hasNewLayout());
    assertFalse(c0c0.hasNewLayout());
  }

  @Test
  public void testInvalidatesCacheWhenFloatPropertyChanges() {
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);

    root.calculateLayout();
    assertTreeHasNewLayout(true, root);
    markLayoutAppliedForTree(root);

    root.calculateLayout();
    assertTreeHasNewLayout(false, root);

    c1.setMarginLeft(10);
    root.calculateLayout();

    assertTrue(root.hasNewLayout());
    assertTrue(c1.hasNewLayout());

    assertFalse(c0.hasNewLayout());
    assertFalse(c0c0.hasNewLayout());
  }

  @Test
  public void testInvalidatesFullTreeWhenParentWidthChanges() {
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);

    root.calculateLayout();
    assertTreeHasNewLayout(true, root);
    markLayoutAppliedForTree(root);

    root.calculateLayout();
    assertTreeHasNewLayout(false, root);

    c0.setStyleWidth(200);
    root.calculateLayout();

    assertTrue(root.hasNewLayout());
    assertTrue(c0.hasNewLayout());
    assertTrue(c0c0.hasNewLayout());

    assertFalse(c1.hasNewLayout());
  }

  @Test
  public void testDoesNotInvalidateCacheWhenPropertyIsTheSame() {
    CSSNode root = new CSSNode();
    CSSNode c0 = new CSSNode();
    CSSNode c1 = new CSSNode();
    CSSNode c0c0 = new CSSNode();
    root.addChildAt(c0, 0);
    root.addChildAt(c1, 1);
    c0.addChildAt(c0c0, 0);
    root.setStyleWidth(200);

    root.calculateLayout();
    assertTreeHasNewLayout(true, root);
    markLayoutAppliedForTree(root);

    root.calculateLayout();
    assertTreeHasNewLayout(false, root);

    root.setStyleWidth(200);
    root.calculateLayout();
    assertTreeHasNewLayout(false, root);
  }
}
