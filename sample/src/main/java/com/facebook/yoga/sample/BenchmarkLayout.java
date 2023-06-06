/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga.sample;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

public class BenchmarkLayout extends BenchmarkFragment {

  @Override
  public View onCreateView(
          LayoutInflater inflater,
          ViewGroup container,
          Bundle savedInstanceState) {
    super.onCreateView(inflater, container, savedInstanceState);

    Button b = rootLayout.findViewById(R.id.btn);
    b.setOnClickListener(v -> startBenchmark());

    return rootLayout;
  }

  protected void startBenchmark() {
    LayoutInflater inflater = LayoutInflater.from(getActivity());
    TextView textView = rootLayout.findViewById(R.id.text);

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
            yogaInflationAggregator +
                    "\n" +
                    linearInflationAggregator);
    Log.i(
            "YogaLayoutBenchmark",
            yogaInflationAggregator +
                    "\n" +
                    linearInflationAggregator);
  }
}
