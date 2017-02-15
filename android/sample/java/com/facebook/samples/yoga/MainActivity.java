/**
 * Copyright 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE-examples file in the root directory of this source tree.
 */

package com.facebook.samples.yoga;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.LayoutInflater;

import com.facebook.samples.yoga.R;
import com.facebook.yoga.android.YogaViewLayoutFactory;

/**
 * An activity to show off Yoga in Android.  This activity shows a simple layout (defined in
 * {@code main_layout.xml}) that shows off the awesome functionality of the Yoga layout engine
 * as well as some optimisations on layout systems that it facilitates.
 */
public class MainActivity extends ActionBarActivity {

  @Override
  public void onCreate(Bundle savedInstanceState) {
    LayoutInflater.from(this).setFactory(YogaViewLayoutFactory.getInstance());
    super.onCreate(savedInstanceState);

    setContentView(R.layout.main_layout);
  }
}
