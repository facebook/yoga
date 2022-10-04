/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga.android;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;

/**
 * A layout inflater factory.  This provides our custom {@link YogaViewLayoutFactory#onCreateView}
 * to the XML inflation system, allowing us to replace XML tags.
 */
public class YogaViewLayoutFactory implements LayoutInflater.Factory {
  private static YogaViewLayoutFactory sYogaViewLayoutFactory;

  /**
   * Obtains (and initialises if necessary) the singleton {@link YogaViewLayoutFactory}.
   *
   * @return The singleton instance
   */
  public static YogaViewLayoutFactory getInstance() {
    if (sYogaViewLayoutFactory == null) {
      sYogaViewLayoutFactory = new YogaViewLayoutFactory();
    }
    return sYogaViewLayoutFactory;
  }

  YogaViewLayoutFactory() {}

  /**
   * Hook for inflating from a LayoutInflater.  This hook replaces the cumbersome
   * {@code com.facebook.etc.YogaLayout} with simply {@code YogaLayout} in your XML and the same
   * with {@code VirtualYogaLayout}.
   *
   * @param name Tag name to be inflated.
   * @param context The context the view is being created in.
   * @param attrs Inflation attributes as specified in XML file.
   *
   * @return View Newly created view. Return null for the default behavior.
   */
  @Override
  public View onCreateView(String name, Context context, AttributeSet attrs) {
    if (YogaLayout.class.getSimpleName().equals(name)) {
      return new YogaLayout(context, attrs);
    }
    if (VirtualYogaLayout.class.getSimpleName().equals(name)) {
      return new VirtualYogaLayout(context, attrs);
    }
    return null;
  }
}
