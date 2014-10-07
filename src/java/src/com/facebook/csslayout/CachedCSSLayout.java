package com.facebook.csslayout;

/**
 * CSSLayout with additional information about the conditions under which it was generated.
 * {@link #requestedWidth} and {@link #requestedHeight} are the width and height the parent set on
 * this node before calling layout visited us.
 */
public class CachedCSSLayout extends CSSLayout {

  public float requestedWidth = CSSConstants.UNDEFINED;
  public float requestedHeight = CSSConstants.UNDEFINED;
  public float parentMaxWidth = CSSConstants.UNDEFINED;
}
