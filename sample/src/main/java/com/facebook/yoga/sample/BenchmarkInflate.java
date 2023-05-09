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

public class BenchmarkInflate extends BenchmarkFragment {

  @Override
  public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
    super.onCreateView(inflater, container, savedInstanceState);

    Button b = rootLayout.findViewById(R.id.btn);
    b.setOnClickListener(v -> startBenchmark());

    return rootLayout;
  }

  protected void startBenchmark() {
    LayoutInflater inflater = LayoutInflater.from(getActivity());
    TextView textView = rootLayout.findViewById(R.id.text);

    final int ITERATIONS = 500;

    inflater.inflate(yogaLayout, null);
    inflater.inflate(linearLayout, null);

    BenchmarkAggregator yogaInflationAggregator = new BenchmarkAggregator("Yoga Inflate");
    BenchmarkAggregator linearInflationAggregator = new BenchmarkAggregator("Linear Inflate");
    for (int i = 0; i < ITERATIONS; i++) {
      yogaInflationAggregator.startTrace();
      inflater.inflate(yogaLayout, null);
      yogaInflationAggregator.endTrace();
      linearInflationAggregator.startTrace();
      inflater.inflate(linearLayout, null);
      linearInflationAggregator.endTrace();
    }

    textView.setText(
            yogaInflationAggregator.toString() +
                    "\n" +
                    linearInflationAggregator.toString());
    Log.i(
            "YogaLayoutBenchmark",
            yogaInflationAggregator.toString() +
                    "\n" +
                    linearInflationAggregator.toString());
    rootLayout.invalidate();
  }
}
