package com.facebook.csslayout;

/**
 * Where the output of {@link LayoutEngine#layoutNode(CSSNode, float)} will go in the CSSNode.
 */
public class CSSLayout {

  public float x;
  public float y;
  public float width = CSSConstants.UNDEFINED;
  public float height = CSSConstants.UNDEFINED;

  /**
   * This should always get called before calling {@link LayoutEngine#layoutNode(CSSNode, float)}
   */
  public void resetResult() {
    x = 0;
    y = 0;
    width = CSSConstants.UNDEFINED;
    height = CSSConstants.UNDEFINED;
  }

  public void copy(CSSLayout layout) {
    x = layout.x;
    y = layout.y;
    width = layout.width;
    height = layout.height;
  }

  @Override
  public String toString() {
    return "layout: {" +
        "x: " + x + ", " +
        "y: " + y + ", " +
        "width: " + width + ", " +
        "height: " + height +
        "}";
  }
}
