/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.samples.yoga;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.Menu;

import com.facebook.samples.yoga.R;
import com.facebook.soloader.SoLoader;
import com.facebook.yoga.android.YogaViewLayoutFactory;

/**
 * An activity to show off Yoga in Android.  This activity shows a simple layout (defined in
 * {@code main_layout.xml}) that shows off the awesome functionality of the Yoga layout engine
 * as well as some optimisations on layout systems that it facilitates.
 */
public class MainActivity extends AppCompatActivity {

  @Override
  public void onCreate(Bundle savedInstanceState) {
    LayoutInflater.from(this).setFactory(YogaViewLayoutFactory.getInstance());
    super.onCreate(savedInstanceState);
    SoLoader.init(this, false);

    setContentView(R.layout.main_layout);
  }

  @Override
  public boolean onCreateOptionsMenu(Menu menu) {
    MenuInflater inflater = getMenuInflater();
    inflater.inflate(R.menu.action_bar_home, menu);
    return true;
  }

  @Override
  public boolean onOptionsItemSelected(MenuItem item) {
    // There is only one option
    Intent intent = new Intent(this, BenchmarkActivity.class);
    startActivity(intent);
    this.finish();
    return true;
  }
}
