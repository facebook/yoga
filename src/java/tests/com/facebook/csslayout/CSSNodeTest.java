package com.facebook.csslayout;

import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

/**
 * Tests for {@link CSSNode}.
 */
public class CSSNodeTest {

  @Test
  public void testAddChildGetParent() {
    CSSNode parent = new CSSNode();
    CSSNode child = new CSSNode();

    assertNull(child.getParent());
    assertEquals(0, parent.getChildCount());

    parent.addChildAt(child, 0);

    assertEquals(1, parent.getChildCount());
    assertEquals(child, parent.getChildAt(0));
    assertEquals(parent, child.getParent());

    parent.removeChildAt(0);

    assertNull(child.getParent());
    assertEquals(0, parent.getChildCount());
  }

  @Test(expected = IllegalStateException.class)
  public void testCannotAddChildToMultipleParents() {
    CSSNode parent1 = new CSSNode();
    CSSNode parent2 = new CSSNode();
    CSSNode child = new CSSNode();

    parent1.addChildAt(child, 0);
    parent2.addChildAt(child, 0);
  }
}
