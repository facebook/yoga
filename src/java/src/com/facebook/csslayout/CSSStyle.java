package com.facebook.csslayout;

/**
 * The CSS style definition for a {@link CSSNode}.
 */
public class CSSStyle {

  public CSSFlexDirection flex_direction = CSSFlexDirection.COLUMN;
  public CSSJustify justify_content = CSSJustify.FLEX_START;
  public CSSAlign align_items = CSSAlign.FLEX_START;
  public CSSAlign align_self = CSSAlign.AUTO;
  public CSSPositionType position_type = CSSPositionType.RELATIVE;
  public float flex;
  public final float[] margin = new float[4];
  public final float[] position = {
      CSSConstants.UNDEFINED,
      CSSConstants.UNDEFINED,
      CSSConstants.UNDEFINED,
      CSSConstants.UNDEFINED};
  public final float[] padding = new float[4];
  public final float[] border = new float[4];
  public final float[] dimensions = {CSSConstants.UNDEFINED, CSSConstants.UNDEFINED};
}
