/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
package com.facebook.csslayout;

/**
 * The CSS style definition for a {@link CSSNode}.
 */
public class CSSStyle {

  public CSSFlexDirection flexDirection = CSSFlexDirection.COLUMN;
  public CSSJustify justifyContent = CSSJustify.FLEX_START;
  public CSSAlign alignItems = CSSAlign.STRETCH;
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
