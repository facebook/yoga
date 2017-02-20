/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

package com.facebook.yoga.android;

import java.util.HashMap;
import java.util.Map;

import android.content.Context;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.content.res.TypedArray;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.util.AttributeSet;
import android.util.SparseArray;
import android.util.TypedValue;
import android.view.View;
import android.view.ViewGroup;

import com.facebook.yoga.android.R;
import com.facebook.yoga.YogaAlign;
import com.facebook.yoga.YogaConstants;
import com.facebook.yoga.YogaDirection;
import com.facebook.yoga.YogaEdge;
import com.facebook.yoga.YogaFlexDirection;
import com.facebook.yoga.YogaJustify;
import com.facebook.yoga.YogaMeasureFunction;
import com.facebook.yoga.YogaMeasureMode;
import com.facebook.yoga.YogaMeasureOutput;
import com.facebook.yoga.YogaNode;
import com.facebook.yoga.YogaNodeAPI;
import com.facebook.yoga.YogaOverflow;
import com.facebook.yoga.YogaPositionType;
import com.facebook.yoga.YogaWrap;

/**
 * A {@code ViewGroup} based on the Yoga layout engine.
 *
 * <p>
 * This class is designed to be as "plug and play" as possible.  That is, you can use it in XML
 * like this (note: to use {@code YogaLayout} you need to use the {@link YogaViewLayoutFactory}):
 * <p>
 * <pre>{@code
 * <YogaLayout
 *     xmlns:android="http://schemas.android.com/apk/res/android"
 *     xmlns:yoga="http://schemas.android.com/apk/res-auto"
 *     android:layout_width="match_parent"
 *     android:layout_height="match_parent"
 *     yoga:flex_direction="row"
 *     yoga:padding_all="10dp"
 *     >
 *     <TextView
 *         android:layout_width="match_parent"
 *         android:layout_height="match_parent"
 *         android:text="Hello, World!"
 *         yoga:flex="1"
 *         />
 * </YogaLayout>
 * }</pre>
 *
 * Under the hood, all views added to this {@code ViewGroup} are laid out using flexbox rules
 * and the Yoga engine.
 */
public class YogaLayout extends ViewGroup {
  private final Map<View, YogaNode> mYogaNodes;
  private final YogaNode mYogaNode;

  public YogaLayout(Context context) {
    this(context, null, 0);
  }

  public YogaLayout(Context context, AttributeSet attrs) {
    this(context, attrs, 0);
  }

  public YogaLayout(Context context, AttributeSet attrs, int defStyleAttr) {
    super(context, attrs, defStyleAttr);

    mYogaNode = new YogaNode();
    mYogaNodes = new HashMap<>();

    mYogaNode.setData(this);
    mYogaNode.setMeasureFunction(new ViewMeasureFunction());

    final LayoutParams layoutParams = new LayoutParams(context, attrs);
    applyLayoutParams(layoutParams, mYogaNode, this);
  }

  YogaNode getYogaNode() {
    return mYogaNode;
  }

  YogaNode getYogaNodeForView(View view) {
    return mYogaNodes.get(view);
  }

  /**
   * Adds a child view with the specified layout parameters.
   *
   * In the typical View is added, this constructs a {@code YogaNode} for this child and applies all
   * the {@code yoga:*} attributes.  The Toga node is added to the Yoga tree and the child is added
   * to this ViewGroup.
   *
   * If the child is a {@link YogaLayout} itself, we do not construct a new Yoga node for that
   * child, but use its root node instead.
   *
   * If the child is a {@link VirtualYogaLayout}, we also use its Yoga node, but we also instruct it
   * to transfer all of its children to this {@link YogaLayout} while preserving the Yoga tree (so
   * that the layout of its children is correct).  The {@link VirtualYogaLayout} is then not added
   * to the View hierarchy.
   *
   * <p><strong>Note:</strong> do not invoke this method from
   * {@code #draw(android.graphics.Canvas)}, {@code onDraw(android.graphics.Canvas)},
   * {@code #dispatchDraw(android.graphics.Canvas)} or any related method.</p>
   *
   * @param child the child view to add
   * @param index the position at which to add the child or -1 to add last
   * @param params the layout parameters to set on the child
   */
  @Override
  public void addView(View child, int index, ViewGroup.LayoutParams params) {
    // Internal nodes (which this is now) cannot have measure functions
    mYogaNode.setMeasureFunction(null);

    if (child instanceof VirtualYogaLayout) {
      ((VirtualYogaLayout) child).transferChildren(this);
      final YogaNode childNode = ((VirtualYogaLayout) child).getYogaNode();

      mYogaNode.addChildAt(childNode, mYogaNode.getChildCount());

      return;
    }

    super.addView(child, index, params);

    // It is possible that addView is being called as part of a transferal of children, in which
    // case we already know about the YogaNode and only need the Android View tree to be aware
    // that we now own this child.  If so, we don't need to do anything further
    if (mYogaNodes.containsKey(child)) {
      return;
    }

    YogaNode childNode;

    if (child instanceof YogaLayout) {
      childNode = ((YogaLayout) child).getYogaNode();
    } else {
      childNode = new YogaNode();

      childNode.setData(child);
      childNode.setMeasureFunction(new ViewMeasureFunction());
    }

    final LayoutParams lp = (LayoutParams) child.getLayoutParams();
    applyLayoutParams(lp, childNode, child);

    mYogaNodes.put(child, childNode);
    mYogaNode.addChildAt(childNode, mYogaNode.getChildCount());
  }

  /**
   * Adds a view to this {@code ViewGroup} with an already given {@code YogaNode}.  Use
   * this function if you already have a Yoga node (and perhaps tree) associated with the view you
   * are adding, that you would like to preserve.
   *
   * @param child The view to add
   * @param node The Yoga node belonging to the view
   */
  public void addView(View child, YogaNode node) {
    mYogaNodes.put(child, node);
    addView(child);
  }

  @Override
  public void removeView(View view) {
    removeViewFromYogaTree(view, false);
    super.removeView(view);
  }

  @Override
  public void removeViewAt(int index) {
    removeViewFromYogaTree(getChildAt(index), false);
    super.removeViewAt(index);
  }

  @Override
  public void removeViewInLayout(View view) {
    removeViewFromYogaTree(view, true);
    super.removeViewInLayout(view);
  }

  @Override
  public void removeViews(int start, int count) {
    for (int i = start; i < start + count; i++) {
      removeViewFromYogaTree(getChildAt(i), false);
    }
    super.removeViews(start, count);
  }

  @Override
  public void removeViewsInLayout(int start, int count) {
    for (int i = start; i < start + count; i++) {
      removeViewFromYogaTree(getChildAt(i), true);
    }
    super.removeViewsInLayout(start, count);
  }

  @Override
  public void removeAllViews() {
    final int childCount = getChildCount();
    for (int i = 0; i < childCount; i++) {
      removeViewFromYogaTree(getChildAt(i), false);
    }
    super.removeAllViews();
  }

  @Override
  public void removeAllViewsInLayout() {
    final int childCount = getChildCount();
    for (int i = 0; i < childCount; i++) {
      removeViewFromYogaTree(getChildAt(i), true);
    }
    super.removeAllViewsInLayout();
  }

  private void removeViewFromYogaTree(View view, boolean inLayout) {
    final YogaNode node = mYogaNodes.get(view);
    if (node == null) {
      return;
    }

    final YogaNode parent = node.getParent();

    for (int i = 0; i < parent.getChildCount(); i++) {
      if (parent.getChildAt(i).equals(node)) {
        parent.removeChildAt(i);
        break;
      }
    }

    node.setData(null);
    mYogaNodes.remove(view);

    if (inLayout) {
      mYogaNode.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    }
  }

  private void applyLayoutRecursive(YogaNode node, float xOffset, float yOffset) {
    View view = (View) node.getData();
    if (view != null && view != this) {
      if (view.getVisibility() == GONE) {
        return;
      }
      view.measure(
          View.MeasureSpec.makeMeasureSpec(
              Math.round(node.getLayoutWidth()),
              View.MeasureSpec.EXACTLY),
          View.MeasureSpec.makeMeasureSpec(
              Math.round(node.getLayoutHeight()),
              View.MeasureSpec.EXACTLY));
      view.layout(
          Math.round(xOffset + node.getLayoutX()),
          Math.round(yOffset + node.getLayoutY()),
          Math.round(xOffset + node.getLayoutX() + node.getLayoutWidth()),
          Math.round(yOffset + node.getLayoutY() + node.getLayoutHeight()));
    }

    final int childrenCount = node.getChildCount();
    for (int i = 0; i < childrenCount; i++) {
      if (this.equals(view)) {
        applyLayoutRecursive(node.getChildAt(i), xOffset, yOffset);
      } else if (view instanceof YogaLayout) {
        continue;
      } else {
        applyLayoutRecursive(
            node.getChildAt(i),
            xOffset + node.getLayoutX(),
            yOffset + node.getLayoutY());
      }
    }
  }

  @Override
  protected void onLayout(boolean changed, int l, int t, int r, int b) {
    // Either we are a root of a tree, or this function is called by our parent's onLayout, in which
    // case our r-l and b-t are the size of our node.
    if (!(getParent() instanceof YogaLayout) &&
        Math.round(mYogaNode.getLayoutHeight()) != b-t &&
        Math.round(mYogaNode.getLayoutWidth()) != r-l) {
        createLayout(
            MeasureSpec.makeMeasureSpec(r - l, MeasureSpec.EXACTLY),
            MeasureSpec.makeMeasureSpec(b - t, MeasureSpec.EXACTLY));
    }

    applyLayoutRecursive(mYogaNode, 0, 0);
  }

  /**
   * This function is mostly unneeded, because Yoga is doing the measuring.  Hence we only need to
   * return accurate results if we are the root.
   *
   * @param widthMeasureSpec the suggested specification for the width
   * @param heightMeasureSpec the suggested specification for the height
   */
  @Override
  protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
    if (!(getParent() instanceof YogaLayout)) {
      createLayout(widthMeasureSpec, heightMeasureSpec);
    }

    setMeasuredDimension(
        Math.round(mYogaNode.getLayoutWidth()),
        Math.round(mYogaNode.getLayoutHeight()));
  }

  private void createLayout(int widthMeasureSpec, int heightMeasureSpec) {
    final int widthSize = MeasureSpec.getSize(widthMeasureSpec);
    final int heightSize = MeasureSpec.getSize(heightMeasureSpec);
    final int widthMode = MeasureSpec.getMode(widthMeasureSpec);
    final int heightMode = MeasureSpec.getMode(heightMeasureSpec);

    if (heightMode == MeasureSpec.EXACTLY) {
      mYogaNode.setHeight(heightSize);
    }
    if (widthMode == MeasureSpec.EXACTLY) {
      mYogaNode.setWidth(widthSize);
    }
    if (heightMode == MeasureSpec.AT_MOST) {
      mYogaNode.setMaxHeight(heightSize);
    }
    if (widthMode == MeasureSpec.AT_MOST) {
      mYogaNode.setMaxWidth(widthSize);
    }

    mYogaNode.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
  }

  /**
   * Applies the layout parameters to the YogaNode.  That is, this function is a translator from
   * {@code yoga:X="Y"} to {@code yogaNode.setX(Y);}, with some reasonable defaults.
   *
   * <p>
   * If the SDK version is high enough, and the {@code yoga:direction} is not set on
   * the component, the direction (LTR or RTL) is set according to the locale.
   *
   * <p>
   * The attributes {@code padding_top}, {@code padding_right} etc. default to those of the view's
   * drawable background, if it has one.
   *
   * @param layoutParameters The source set of params
   * @param node The destination node
   */
  protected static void applyLayoutParams(LayoutParams layoutParameters, YogaNode node, View view) {
    // JELLY_BEAN_MR1 (17) is the first version supporting getLayoutDirection()
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
      Configuration configuration = view.getResources().getConfiguration();
      if (configuration.getLayoutDirection() == LAYOUT_DIRECTION_RTL) {
        node.setDirection(YogaDirection.RTL);
      }
    }

    Drawable background = view.getBackground();
    if (background != null) {
      final Rect backgroundPadding = new Rect();
      if (background.getPadding(backgroundPadding)) {
        node.setPadding(YogaEdge.LEFT, backgroundPadding.left);
        node.setPadding(YogaEdge.TOP, backgroundPadding.top);
        node.setPadding(YogaEdge.RIGHT, backgroundPadding.right);
        node.setPadding(YogaEdge.BOTTOM, backgroundPadding.bottom);
      }
    }

    for (int i = 0; i < layoutParameters.attributes.size(); i++) {
      final int attribute = layoutParameters.attributes.keyAt(i);
      final float value = layoutParameters.attributes.valueAt(i);

      if (attribute == R.styleable.yoga_align_content) {
        node.setAlignContent(YogaAlign.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_align_items) {
        node.setAlignItems(YogaAlign.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_align_self) {
        node.setAlignSelf(YogaAlign.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_aspect_ratio) {
        node.setAspectRatio(value);
      } else if (attribute == R.styleable.yoga_border_left) {
        node.setBorder(YogaEdge.LEFT, value);
      } else if (attribute == R.styleable.yoga_border_top) {
        node.setBorder(YogaEdge.TOP, value);
      } else if (attribute == R.styleable.yoga_border_right) {
        node.setBorder(YogaEdge.RIGHT, value);
      } else if (attribute == R.styleable.yoga_border_bottom) {
        node.setBorder(YogaEdge.BOTTOM, value);
      } else if (attribute == R.styleable.yoga_border_start) {
        node.setBorder(YogaEdge.START, value);
      } else if (attribute == R.styleable.yoga_border_end) {
        node.setBorder(YogaEdge.END, value);
      } else if (attribute == R.styleable.yoga_border_horizontal) {
        node.setBorder(YogaEdge.HORIZONTAL, value);
      } else if (attribute == R.styleable.yoga_border_vertical) {
        node.setBorder(YogaEdge.VERTICAL, value);
      } else if (attribute == R.styleable.yoga_border_all) {
        node.setBorder(YogaEdge.ALL, value);
      } else if (attribute == R.styleable.yoga_direction) {
        node.setDirection(YogaDirection.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_flex) {
        node.setFlex(value);
      } else if (attribute == R.styleable.yoga_flex_basis) {
        node.setFlexBasis(value);
      } else if (attribute == R.styleable.yoga_flex_basis_percent) {
        node.setFlexBasisPercent(value);
      } else if (attribute == R.styleable.yoga_flex_direction) {
        node.setFlexDirection(YogaFlexDirection.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_flex_grow) {
        node.setFlexGrow(value);
      } else if (attribute == R.styleable.yoga_flex_shrink) {
        node.setFlexShrink(value);
      } else if (attribute == R.styleable.yoga_height) {
        node.setHeight(value);
      } else if (attribute == R.styleable.yoga_height_percent) {
        node.setHeightPercent(value);
      } else if (attribute == R.styleable.yoga_margin_left) {
        node.setMargin(YogaEdge.LEFT, value);
      } else if (attribute == R.styleable.yoga_justify_content) {
        node.setJustifyContent(YogaJustify.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_margin_top) {
        node.setMargin(YogaEdge.TOP, value);
      } else if (attribute == R.styleable.yoga_margin_right) {
        node.setMargin(YogaEdge.RIGHT, value);
      } else if (attribute == R.styleable.yoga_margin_bottom) {
        node.setMargin(YogaEdge.BOTTOM, value);
      } else if (attribute == R.styleable.yoga_margin_start) {
        node.setMargin(YogaEdge.START, value);
      } else if (attribute == R.styleable.yoga_margin_end) {
        node.setMargin(YogaEdge.END, value);
      } else if (attribute == R.styleable.yoga_margin_horizontal) {
        node.setMargin(YogaEdge.HORIZONTAL, value);
      } else if (attribute == R.styleable.yoga_margin_vertical) {
        node.setMargin(YogaEdge.VERTICAL, value);
      } else if (attribute == R.styleable.yoga_margin_all) {
        node.setMargin(YogaEdge.ALL, value);
      } else if (attribute == R.styleable.yoga_margin_percent_left) {
        node.setMarginPercent(YogaEdge.LEFT, value);
      } else if (attribute == R.styleable.yoga_margin_percent_top) {
        node.setMarginPercent(YogaEdge.TOP, value);
      } else if (attribute == R.styleable.yoga_margin_percent_right) {
        node.setMarginPercent(YogaEdge.RIGHT, value);
      } else if (attribute == R.styleable.yoga_margin_percent_bottom) {
        node.setMarginPercent(YogaEdge.BOTTOM, value);
      } else if (attribute == R.styleable.yoga_margin_percent_start) {
        node.setMarginPercent(YogaEdge.START, value);
      } else if (attribute == R.styleable.yoga_margin_percent_end) {
        node.setMarginPercent(YogaEdge.END, value);
      } else if (attribute == R.styleable.yoga_margin_percent_horizontal) {
        node.setMarginPercent(YogaEdge.HORIZONTAL, value);
      } else if (attribute == R.styleable.yoga_margin_percent_vertical) {
        node.setMarginPercent(YogaEdge.VERTICAL, value);
      } else if (attribute == R.styleable.yoga_margin_percent_all) {
        node.setMarginPercent(YogaEdge.ALL, value);
      } else if (attribute == R.styleable.yoga_max_height) {
        node.setMaxHeight(value);
      } else if (attribute == R.styleable.yoga_max_height_percent) {
        node.setMaxHeightPercent(value);
      } else if (attribute == R.styleable.yoga_max_width) {
        node.setMaxWidth(value);
      } else if (attribute == R.styleable.yoga_max_width_percent) {
        node.setMaxWidthPercent(value);
      } else if (attribute == R.styleable.yoga_min_height) {
        node.setMinHeight(value);
      } else if (attribute == R.styleable.yoga_min_height_percent) {
        node.setMinHeightPercent(value);
      } else if (attribute == R.styleable.yoga_min_width) {
        node.setMinWidth(value);
      } else if (attribute == R.styleable.yoga_min_width_percent) {
        node.setMinWidthPercent(value);
      } else if (attribute == R.styleable.yoga_overflow) {
        node.setOverflow(YogaOverflow.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_padding_left) {
        node.setPadding(YogaEdge.LEFT, value);
      } else if (attribute == R.styleable.yoga_padding_top) {
        node.setPadding(YogaEdge.TOP, value);
      } else if (attribute == R.styleable.yoga_padding_right) {
        node.setPadding(YogaEdge.RIGHT, value);
      } else if (attribute == R.styleable.yoga_padding_bottom) {
        node.setPadding(YogaEdge.BOTTOM, value);
      } else if (attribute == R.styleable.yoga_padding_start) {
        node.setPadding(YogaEdge.START, value);
      } else if (attribute == R.styleable.yoga_padding_end) {
        node.setPadding(YogaEdge.END, value);
      } else if (attribute == R.styleable.yoga_padding_horizontal) {
        node.setPadding(YogaEdge.HORIZONTAL, value);
      } else if (attribute == R.styleable.yoga_padding_vertical) {
        node.setPadding(YogaEdge.VERTICAL, value);
      } else if (attribute == R.styleable.yoga_padding_all) {
        node.setPadding(YogaEdge.ALL, value);
      } else if (attribute == R.styleable.yoga_padding_percent_left) {
        node.setPaddingPercent(YogaEdge.LEFT, value);
      } else if (attribute == R.styleable.yoga_padding_percent_top) {
        node.setPaddingPercent(YogaEdge.TOP, value);
      } else if (attribute == R.styleable.yoga_padding_percent_right) {
        node.setPaddingPercent(YogaEdge.RIGHT, value);
      } else if (attribute == R.styleable.yoga_padding_percent_bottom) {
        node.setPaddingPercent(YogaEdge.BOTTOM, value);
      } else if (attribute == R.styleable.yoga_padding_percent_start) {
        node.setPaddingPercent(YogaEdge.START, value);
      } else if (attribute == R.styleable.yoga_padding_percent_end) {
        node.setPaddingPercent(YogaEdge.END, value);
      } else if (attribute == R.styleable.yoga_padding_percent_horizontal) {
        node.setPaddingPercent(YogaEdge.HORIZONTAL, value);
      } else if (attribute == R.styleable.yoga_padding_percent_vertical) {
        node.setPaddingPercent(YogaEdge.VERTICAL, value);
      } else if (attribute == R.styleable.yoga_padding_percent_all) {
        node.setPaddingPercent(YogaEdge.ALL, value);
      } else if (attribute == R.styleable.yoga_position_left) {
        node.setPosition(YogaEdge.LEFT, value);
      } else if (attribute == R.styleable.yoga_position_top) {
        node.setPosition(YogaEdge.TOP, value);
      } else if (attribute == R.styleable.yoga_position_right) {
        node.setPosition(YogaEdge.RIGHT, value);
      } else if (attribute == R.styleable.yoga_position_bottom) {
        node.setPosition(YogaEdge.BOTTOM, value);
      } else if (attribute == R.styleable.yoga_position_start) {
        node.setPosition(YogaEdge.START, value);
      } else if (attribute == R.styleable.yoga_position_end) {
        node.setPosition(YogaEdge.END, value);
      } else if (attribute == R.styleable.yoga_position_horizontal) {
        node.setPosition(YogaEdge.HORIZONTAL, value);
      } else if (attribute == R.styleable.yoga_position_vertical) {
        node.setPosition(YogaEdge.VERTICAL, value);
      } else if (attribute == R.styleable.yoga_position_all) {
        node.setPosition(YogaEdge.ALL, value);
      } else if (attribute == R.styleable.yoga_position_percent_left) {
        node.setPositionPercent(YogaEdge.LEFT, value);
      } else if (attribute == R.styleable.yoga_position_percent_top) {
        node.setPositionPercent(YogaEdge.TOP, value);
      } else if (attribute == R.styleable.yoga_position_percent_right) {
        node.setPositionPercent(YogaEdge.RIGHT, value);
      } else if (attribute == R.styleable.yoga_position_percent_bottom) {
        node.setPositionPercent(YogaEdge.BOTTOM, value);
      } else if (attribute == R.styleable.yoga_position_percent_start) {
        node.setPositionPercent(YogaEdge.START, value);
      } else if (attribute == R.styleable.yoga_position_percent_end) {
        node.setPositionPercent(YogaEdge.END, value);
      } else if (attribute == R.styleable.yoga_position_percent_horizontal) {
        node.setPositionPercent(YogaEdge.HORIZONTAL, value);
      } else if (attribute == R.styleable.yoga_position_percent_vertical) {
        node.setPositionPercent(YogaEdge.VERTICAL, value);
      } else if (attribute == R.styleable.yoga_position_percent_all) {
        node.setPositionPercent(YogaEdge.ALL, value);
      } else if (attribute == R.styleable.yoga_position_type) {
        node.setPositionType(YogaPositionType.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_width) {
        node.setWidth(value);
      } else if (attribute == R.styleable.yoga_width_percent) {
        node.setWidthPercent(value);
      } else if (attribute == R.styleable.yoga_wrap) {
        node.setWrap(YogaWrap.fromInt(Math.round(value)));
      }
    }
  }

  @Override
  public ViewGroup.LayoutParams generateLayoutParams(AttributeSet attrs) {
    return new YogaLayout.LayoutParams(getContext(), attrs);
  }

  @Override
  protected ViewGroup.LayoutParams generateDefaultLayoutParams() {
    return new YogaLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                       ViewGroup.LayoutParams.MATCH_PARENT);
  }

  @Override
  protected ViewGroup.LayoutParams generateLayoutParams(ViewGroup.LayoutParams p) {
    return new YogaLayout.LayoutParams(p);
  }

  @Override
  protected boolean checkLayoutParams(ViewGroup.LayoutParams p) {
    return p instanceof LayoutParams;
  }

  /**
   * {@code YogaLayout.LayoutParams} are used by views to tell {@link YogaLayout} how they want to
   * be laid out.  More precisely, the specify the yoga parameters of the view.
   *
   * <p>
   * This is actually mostly a wrapper around a {@code SparseArray} that holds a mapping between
   * styleable id's ({@code R.styleable.yoga_*}) and the float of their values.  In cases where the
   * value is an enum or an integer, they should first be cast to int (with rounding) before using.
   */
  public static class LayoutParams extends ViewGroup.LayoutParams {

    /**
     * A mapping from attribute keys ({@code R.styleable.yoga_*}) to the float of their values.
     * For attributes like position_percent_left (float), this is the native type.  For attributes
     * like align_self (enums), the integer enum value is cast (rounding is used on the other side
     * to prevent precision errors).  Dimension attributes are stored as float pixels.
     */
    SparseArray<Float> attributes;

    /**
     * Constructs a set of layout params from a source set.  In the case that the source set is
     * actually a {@link YogaLayout.LayoutParams}, we can copy all the yoga attributes.  Otherwise
     * we start with a blank slate.
     *
     * @param source The layout params to copy from
     */
    public LayoutParams(ViewGroup.LayoutParams source) {
      super(source);
      if (source instanceof LayoutParams) {
        attributes = ((LayoutParams) source).attributes.clone();
      } else {
        attributes = new SparseArray<>();

        // Negative values include MATCH_PARENT and WRAP_CONTENT
        if (source.width >= 0) {
          attributes.put(R.styleable.yoga_width, (float) width);
        }
        if (source.height >= 0) {
          attributes.put(R.styleable.yoga_height, (float) height);
        }
      }
    }

    /**
     * Constructs a set of layout params, given width and height specs.  In this case, we can set
     * the {@code yoga:width} and {@code yoga:height} if we are given them explicitly.  If other
     * options (such as {@code match_parent} or {@code wrap_content} are given, then the parent
     * LayoutParams will store them, and we deal with them during layout. (see
     * {@link YogaLayout#createLayout})
     *
     * @param width the requested width, either a pixel size, {@code WRAP_CONTENT} or
     *        {@code MATCH_PARENT}.
     * @param height the requested height, either a pixel size, {@code WRAP_CONTENT} or
     *        {@code MATCH_PARENT}.
     */
    public LayoutParams(int width, int height) {
      super(width, height);
      attributes = new SparseArray<>();
      // Negative values include MATCH_PARENT and WRAP_CONTENT
      if (width >= 0) {
        attributes.put(R.styleable.yoga_width, (float) width);
      }
      if (height >= 0) {
        attributes.put(R.styleable.yoga_height, (float) height);
      }
    }

    /**
     * Constructs a set of layout params, given attributes.  Grabs all the {@code yoga:*}
     * defined in {@code ALL_YOGA_ATTRIBUTES} and collects the ones that are set in {@code attrs}.
     *
     * @param context the application environment
     * @param attrs the set of attributes from which to extract the yoga specific attributes
     */
    public LayoutParams(Context context, AttributeSet attrs) {
      super(context, attrs);
      attributes = new SparseArray<>();
      final TypedArray a = context.obtainStyledAttributes(attrs, R.styleable.yoga);

      // Negative values include MATCH_PARENT and WRAP_CONTENT
      if (width >= 0) {
        attributes.put(R.styleable.yoga_width, (float) width);
      }
      if (height >= 0) {
        attributes.put(R.styleable.yoga_height, (float) height);
      }

      final int attributeCount = a.getIndexCount();
      for (int i = 0; i < attributeCount; i++) {
        final int attribute = a.getIndex(i);
        final TypedValue val = new TypedValue();
        a.getValue(attribute, val);

        if (val.type == TypedValue.TYPE_DIMENSION) {
          attributes.put(
              attribute,
              (float) a.getDimensionPixelSize(attribute, 0));
        } else {
          attributes.put(attribute, a.getFloat(attribute, 0));
        }
      }
      a.recycle();
    }
  }

  /**
   * Wrapper around measure function for yoga leaves.
   */
  public static class ViewMeasureFunction implements YogaMeasureFunction {

    /**
     * A function to measure leaves of the Yoga tree.  Yoga needs some way to know how large
     * elements want to be.  This function passes that question directly through to the relevant
     * {@code View}'s measure function.
     *
     * @param node The yoga node to measure
     * @param width The suggested width from the parent
     * @param widthMode The type of suggestion for the width
     * @param height The suggested height from the parent
     * @param heightMode The type of suggestion for the height
     * @return A measurement output ({@code YogaMeasureOutput}) for the node
     */
    public long measure(
        YogaNodeAPI node,
        float width,
        YogaMeasureMode widthMode,
        float height,
        YogaMeasureMode heightMode) {
      final View view = (View) node.getData();
      if (view == null || view instanceof YogaLayout) {
        return YogaMeasureOutput.make(0, 0);
      }

      final int widthMeasureSpec = MeasureSpec.makeMeasureSpec(
          (int) width,
          viewMeasureSpecFromYogaMeasureMode(widthMode));
      final int heightMeasureSpec = MeasureSpec.makeMeasureSpec(
          (int) height,
          viewMeasureSpecFromYogaMeasureMode(heightMode));

      view.measure(widthMeasureSpec, heightMeasureSpec);

      return YogaMeasureOutput.make(view.getMeasuredWidth(), view.getMeasuredHeight());
    }

    private int viewMeasureSpecFromYogaMeasureMode(YogaMeasureMode mode) {
      if (mode == YogaMeasureMode.AT_MOST) {
        return MeasureSpec.AT_MOST;
      } else if (mode == YogaMeasureMode.EXACTLY) {
        return MeasureSpec.EXACTLY;
      } else {
        return MeasureSpec.UNSPECIFIED;
      }
    }
  }
}
