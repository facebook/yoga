/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.samples.yoga;


import java.util.Random;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.ArrayAdapter;
import android.widget.AdapterView;

import com.facebook.samples.yoga.R;
import com.facebook.yoga.android.YogaLayout;

public class BenchmarkFragment extends Fragment implements AdapterView.OnItemSelectedListener {
  private LayoutInflater mInflater;

  protected com.facebook.yoga.android.YogaLayout rootLayout;
  protected int yogaLayout;
  protected int linearLayout;

  static final Random random = new Random();

  static void randomizeText(View root) {
    if (root instanceof TextView) {
      ((TextView) root).setText("" + random.nextInt(1000));
      ((TextView) root).setTextSize(10 + random.nextInt(20));
      ViewParent parent = root.getParent();
      if (parent instanceof YogaLayout) {
        ((YogaLayout) parent).invalidate(root);
      }
    } else if (root instanceof ViewGroup) {
      for (int i = 0; i < ((ViewGroup) root).getChildCount(); i++) {
        randomizeText(((ViewGroup) root).getChildAt(i));
      }
    }
  }

  public BenchmarkFragment() {
  }

  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
  }

  @Override
  public View onCreateView(
      LayoutInflater inflater,
      ViewGroup container,
      Bundle savedInstanceState) {
    mInflater = inflater;

    rootLayout = (YogaLayout) inflater.inflate(
        R.layout.benchmark_fragment,
        container,
        false);

    Spinner benchmarkSelect = (Spinner) rootLayout.findViewById(R.id.benchmarkSelect);
    String[] items = new String[]{"Basic", "Typical", "Nested"};
    ArrayAdapter<String> adapter = new ArrayAdapter<>(getActivity(), android.R.layout.simple_spinner_dropdown_item, items);
    benchmarkSelect.setAdapter(adapter);
    benchmarkSelect.setOnItemSelectedListener(this);
    return rootLayout;
  }

  @Override
  public void onItemSelected(AdapterView<?> parent, View view, int pos, long id) {
    switch (pos) {
      case 0:
        yogaLayout = R.layout.benchmark_layout_1;
        linearLayout = R.layout.benchmark_layout_1_linear;
        break;
      case 1:
        yogaLayout = R.layout.benchmark_layout_2;
        linearLayout = R.layout.benchmark_layout_2_linear;
        break;
      case 2:
      default:
        yogaLayout = R.layout.benchmark_layout_3;
        linearLayout = R.layout.benchmark_layout_3_linear;
        break;
    }
    updatePreview();
  }

  @Override
  public void onNothingSelected(AdapterView<?> parent) {
    yogaLayout = R.layout.benchmark_layout_1;
    linearLayout = R.layout.benchmark_layout_1_linear;
    updatePreview();
  }

  private void updatePreview() {
    LinearLayout previewLayout = (LinearLayout) rootLayout.findViewById(R.id.preview);
    View v  = mInflater.inflate(yogaLayout, rootLayout, false);
    v.setLayoutParams(new LinearLayout.LayoutParams(
        LinearLayout.LayoutParams.MATCH_PARENT,
        LinearLayout.LayoutParams.MATCH_PARENT));
    previewLayout.removeAllViews();
    previewLayout.addView(v);
  }
}
