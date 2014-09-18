package com.facebook.csslayout;

/**
 * The CSS style definition for a {@link CSSNode}.
 */
public class CSSStyle {

  public CSSFlexDirection flexDirection = CSSFlexDirection.COLUMN;
  public CSSJustify justifyContent = CSSJustify.FLEX_START;
  public CSSAlign alignItems = CSSAlign.FLEX_START;
  public CSSAlign alignSelf = CSSAlign.AUTO;
  public CSSPositionType positionType = CSSPositionType.RELATIVE;
  public float flex;

  public float marginTop;
  public float marginBottom;
  public float marginLeft;
  public float marginRight;

  public float paddingTop;
  public float paddingBottom;
  public float paddingLeft;
  public float paddingRight;

  public float positionTop = CSSConstants.UNDEFINED;
  public float positionBottom = CSSConstants.UNDEFINED;
  public float positionLeft = CSSConstants.UNDEFINED;
  public float positionRight = CSSConstants.UNDEFINED;

  public float borderTop;
  public float borderBottom;
  public float borderLeft;
  public float borderRight;

  public float width = CSSConstants.UNDEFINED;
  public float height = CSSConstants.UNDEFINED;
}
