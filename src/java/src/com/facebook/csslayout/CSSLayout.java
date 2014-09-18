package com.facebook.csslayout;

/**
 * Where the output of {@link LayoutEngine#layoutNode(CSSNode, float)} will go in the CSSNode.
 */
public class CSSLayout {

  public final float[] position = new float[2];
  public final float[] dimensions = {CSSConstants.UNDEFINED, CSSConstants.UNDEFINED};

  /**
   * This should always get called before calling {@link LayoutEngine#layoutNode(CSSNode, float)}
   */
  public void resetResult() {
    position[CSSConstants.POSITION_INDEX_TOP] = 0;
    position[CSSConstants.POSITION_INDEX_LEFT] = 0;
    dimensions[CSSConstants.DIMENSION_INDEX_WIDTH] = CSSConstants.UNDEFINED;
    dimensions[CSSConstants.DIMENSION_INDEX_HEIGHT] = CSSConstants.UNDEFINED;
  }
}
