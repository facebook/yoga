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

public class BenchmarkMeasure extends BenchmarkFragment {

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

    BenchmarkAggregator yogaMeasureAggregator = new BenchmarkAggregator("Yoga Measure");
    BenchmarkAggregator linearMeasureAggregator = new BenchmarkAggregator("Linear Measure");
    View yogaView = inflater.inflate(yogaLayout, null);
    View linearView = inflater.inflate(linearLayout, null);
    for (int i = 0; i < ITERATIONS; i++) {
      randomizeText(yogaView);
      randomizeText(linearView);
      yogaMeasureAggregator.startTrace();
      yogaView.measure(
          View.MeasureSpec.makeMeasureSpec(1000, View.MeasureSpec.EXACTLY),
          View.MeasureSpec.makeMeasureSpec(1000, View.MeasureSpec.EXACTLY));
      yogaMeasureAggregator.endTrace();
      linearMeasureAggregator.startTrace();
      linearView.measure(
          View.MeasureSpec.makeMeasureSpec(1000, View.MeasureSpec.EXACTLY),
          View.MeasureSpec.makeMeasureSpec(1000, View.MeasureSpec.EXACTLY));
      linearMeasureAggregator.endTrace();
    }

    textView.setText(
        yogaMeasureAggregator.toString()+
            "\n"+
            linearMeasureAggregator.toString());
    Log.i(
      "YogaLayoutBenchmark",
      yogaMeasureAggregator.toString()+
        "\n"+
        linearMeasureAggregator.toString());

    yogaMeasureAggregator.dump(getActivity());
    linearMeasureAggregator.dump(getActivity());
  }
}
