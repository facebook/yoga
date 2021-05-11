/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.samples.yoga;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;
import com.facebook.samples.yoga.R;

import java.util.Random;

public class BenchmarkLayout extends BenchmarkFragment {

  @Override
  public View onCreateView(
    LayoutInflater inflater,
    ViewGroup container,
    Bundle savedInstanceState) {
    super.onCreateView(inflater, container, savedInstanceState);

    Button b = (Button) rootLayout.findViewById(R.id.btn);
    b.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View v) {
        startBenchmark();
      }
    });

    return rootLayout;
  }

  protected void startBenchmark() {
    LayoutInflater inflater = LayoutInflater.from(getActivity());
    TextView textView = (TextView) rootLayout.findViewById(R.id.text);
    Random random = new Random();

    final int ITERATIONS = 500;

    BenchmarkAggregator yogaInflationAggregator = new BenchmarkAggregator("Yoga Layout");
    BenchmarkAggregator linearInflationAggregator = new BenchmarkAggregator("Linear Layout");
    View yogaView = inflater.inflate(yogaLayout, null);
    View linearView = inflater.inflate(linearLayout, null);
    for (int i = 0; i < ITERATIONS; i++) {
      randomizeText(yogaView);
      randomizeText(linearView);
      yogaView.measure(
          View.MeasureSpec.makeMeasureSpec(1000, View.MeasureSpec.EXACTLY),
          View.MeasureSpec.makeMeasureSpec(1000, View.MeasureSpec.EXACTLY));
      linearView.measure(
          View.MeasureSpec.makeMeasureSpec(1000, View.MeasureSpec.EXACTLY),
          View.MeasureSpec.makeMeasureSpec(1000, View.MeasureSpec.EXACTLY));
      yogaInflationAggregator.startTrace();
      yogaView.layout(0, 0, yogaView.getMeasuredWidth(), yogaView.getMeasuredHeight());
      yogaInflationAggregator.endTrace();
      linearInflationAggregator.startTrace();
      linearView.layout(0, 0, linearView.getMeasuredWidth(), linearView.getMeasuredHeight());
      linearInflationAggregator.endTrace();
    }

    textView.setText(
        yogaInflationAggregator.toString()+
            "\n"+
            linearInflationAggregator.toString());
    Log.i(
      "YogaLayoutBenchmark",
      yogaInflationAggregator.toString()+
        "\n"+
        linearInflationAggregator.toString());
  }
}
