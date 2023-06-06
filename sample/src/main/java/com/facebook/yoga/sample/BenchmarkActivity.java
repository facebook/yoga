/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga.sample;

import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;
import androidx.fragment.app.FragmentTransaction;
import androidx.viewpager.widget.ViewPager;

import com.facebook.yoga.android.YogaViewLayoutFactory;

public class BenchmarkActivity extends AppCompatActivity {

  @Override
  public void onCreate(Bundle savedInstanceState) {
    LayoutInflater.from(this).setFactory(YogaViewLayoutFactory.getInstance());
    super.onCreate(savedInstanceState);

    setContentView(R.layout.benchmark_select_layout);

    ViewPager viewPager = findViewById(R.id.viewpager);
    viewPager.setAdapter(new PagerAdapter(getSupportFragmentManager()));

    final ActionBar actionBar = getSupportActionBar();
    actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);

    ActionBar.TabListener tabListener = new ActionBar.TabListener() {
      @Override
      public void onTabSelected(ActionBar.Tab tab, FragmentTransaction ft) {
        ViewPager viewPager = findViewById(R.id.viewpager);
        viewPager.setCurrentItem(tab.getPosition());
      }

      @Override
      public void onTabUnselected(ActionBar.Tab tab, FragmentTransaction ft) {
      }

      @Override
      public void onTabReselected(ActionBar.Tab tab, FragmentTransaction ft) {
      }
    };
    actionBar.addTab(
            actionBar.newTab()
                    .setText("Inflate")
                    .setTabListener(tabListener));
    actionBar.addTab(
            actionBar.newTab()
                    .setText("Measure")
                    .setTabListener(tabListener));
    actionBar.addTab(
            actionBar.newTab()
                    .setText("Layout")
                    .setTabListener(tabListener));

    viewPager.setOnPageChangeListener(
            new ViewPager.SimpleOnPageChangeListener() {
              @Override
              public void onPageSelected(int position) {
                // When swiping between pages, select the
                // corresponding tab.
                actionBar.setSelectedNavigationItem(position);
              }
            });

    viewPager.setOffscreenPageLimit(3);
  }

  @Override
  public boolean onCreateOptionsMenu(Menu menu) {
    MenuInflater inflater = getMenuInflater();
    inflater.inflate(R.menu.action_bar_benchmark, menu);
    return true;
  }

  @Override
  public boolean onOptionsItemSelected(MenuItem item) {
    // There is only one option
    Intent intent = new Intent(this, MainActivity.class);
    startActivity(intent);
    this.finish();
    return true;
  }

  public static class PagerAdapter extends FragmentPagerAdapter {
    public PagerAdapter(FragmentManager fm) {
      super(fm);
    }

    @Override
    public Fragment getItem(int i) {
      switch (i) {
        case 0:
          return new BenchmarkInflate();
        case 1:
          return new BenchmarkMeasure();
        default:
          return new BenchmarkLayout();
      }
    }

    @Override
    public int getCount() {
      return 3;
    }
  }
}
