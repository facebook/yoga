/**
 * Copyright 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE-examples file in the root directory of this source tree.
 */

package com.facebook.samples.yoga;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.support.v7.app.ActionBarActivity;
import android.view.LayoutInflater;

import com.facebook.samples.yoga.R;
import com.facebook.soloader.SoLoader;
import com.facebook.yoga.android.YogaViewLayoutFactory;

/**
 * A (non-interactive) splash screen.  Displays for two seconds before calling the main activity.
 */
public class SplashScreenActivity extends ActionBarActivity {

  @Override
  public void onCreate(Bundle savedInstanceState) {
    LayoutInflater.from(this).setFactory(YogaViewLayoutFactory.getInstance());
    super.onCreate(savedInstanceState);
    SoLoader.init(this, false);

    setContentView(R.layout.splash_layout);

    new Handler(Looper.getMainLooper()).postDelayed(
        new Runnable() {
          @Override
          public void run() {
            startMainActivity();
          }
        },
        2000);
  }

  private void startMainActivity() {
    Intent intent = new Intent(this, MainActivity.class);
    startActivity(intent);
    this.finish();
  }
}
