/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.samples.yoga;

import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.lang.Math;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.text.DateFormat;
import java.util.Date;

import android.content.Context;
import android.util.Log;
import android.os.Environment;

import static java.util.Collections.sort;

public class BenchmarkAggregator {

  private final int GRAPH_WIDTH = 30;
  private final int GRAPH_HEIGHT = 6;

  private List<Long> times;
  private boolean tracing;
  private long lastTraceStart;

  private boolean statsFresh;
  private long mean;
  private long variance;
  private long stddev;
  private long min;
  private long max;
  private long p10;
  private long p50;
  private long p90;

  private String name;

  public BenchmarkAggregator(String name) {
    times = new ArrayList<>();
    tracing = false;
    this.name = name;
  }

  public void startTrace() {
    if (tracing) {
      throw new RuntimeException("Cannot start trace while running previous one");
    }
    tracing = true;
    lastTraceStart = System.nanoTime();
  }

  public void endTrace() {
    if (!tracing) {
      throw new RuntimeException("Cannot stop trace if none are running!");
    }
    times.add(System.nanoTime() - lastTraceStart);
    tracing = false;
    statsFresh = false;
  }

  private void computeStats() {
    if (statsFresh) {
      return;
    }

    sort(times);

    min = Long.MAX_VALUE;
    max = -1;
    mean = 0;
    for (long f: times) {
      mean += f;
      if (f < min) {
        min = f;
      }
      if (f > max) {
        max = f;
      }
    }
    mean /= times.size();

    variance = 0;
    for (long f: times) {
      variance += (f-mean)*(f-mean);
    }
    variance /= times.size();
    stddev = (long) Math.sqrt((double) variance);

    p10 = times.get(times.size()*10/100);
    p50 = times.get(times.size()*50/100);
    p90 = times.get(times.size()*90/100);

    statsFresh = true;
  }

  public String toString() {
    computeStats();
    return String.format(
        "%s:\n" +
            "| %d samples\n" +
            "| Mean %.3f\u00B1%.3fms\n" + // plusminus
            "| Min %.3fms ; Max %.3fms\n" +
            "| p10 %.3fms ; p50 %.3fms ; p90 %.3fms\n" +
            "%s",
        name,
        times.size(),
        mean/10e6,
        stddev/10e6,
        min/10e6,
        max/10e6,
        p10/10e6,
        p50/10e6,
        p90/10e6,
        makeGraph());
  }

  private String makeGraph() {
    char canvas[][] = new char[GRAPH_HEIGHT][GRAPH_WIDTH];
    for (int i = 0; i < GRAPH_HEIGHT; i++)
      for (int j = 0; j < GRAPH_WIDTH; j++)
        canvas[i][j] = ' ';

    long bucketSize = (p90 - p10) / GRAPH_WIDTH+1;
    int bucketCount[] = new int[GRAPH_WIDTH];
    for (long time : times) {
      if (time<p90 && time>p10) {
        bucketCount[(int) ((time - p10) / bucketSize)]++;
      }
    }

    int maxBucket = 0;
    for (int i = 0; i < GRAPH_WIDTH; i++)
      if (bucketCount[i] > maxBucket) {
        maxBucket = bucketCount[i];
      }

    for (int i = 0; i < GRAPH_HEIGHT; i++)
      for (int j = 0; j < GRAPH_WIDTH; j++)
        if (i < bucketCount[j] * GRAPH_HEIGHT / maxBucket) {
          canvas[i][j] = 'Z';
        }

    String graph = new String();
    for (int i = 0; i < GRAPH_HEIGHT; i++)
    {
      int percentage = 100 * (GRAPH_HEIGHT - i - 1) * maxBucket / (times.size() * GRAPH_HEIGHT);
      graph += String.format("| %2d%% ", percentage);
      for (int j = 0; j < GRAPH_WIDTH; j++)
        graph += canvas[GRAPH_HEIGHT-1-i][j];
      graph += '\n';
    }

    graph += "|     p10";
    for (int i = 0; i < GRAPH_WIDTH-6; i++)
      graph += " ";
    graph += "p90\n";
    return graph;
  }

  /**
   * Dumps the collected times to a file on the device.  This allows us to grab the raw data
   * and perform more in-depth analysis.
   */
  public void dump(Context context) {
    String state = Environment.getExternalStorageState();
    if (!Environment.MEDIA_MOUNTED.equals(state)) {
      Log.e("YogaLayoutBenchmark","No external file storage");
      return;
    }

    SimpleDateFormat format = new SimpleDateFormat("yyyyMMddHHmmss");
    String filename = format.format(new Date()) + "_" + name.replace(' ','_');
    File file = new File(context.getExternalFilesDir(
            Environment.DIRECTORY_DOCUMENTS), filename);

    try {
      PrintWriter printWriter = new PrintWriter(file);
      for (long l : times) {
        printWriter.println(l);
      }
      printWriter.close();

      Log.i("YogaLayoutBenchmark","Benchmark data saved in "+file.getPath());
    } catch (java.io.IOException e) {
      Log.e("YogaLayoutBenchmark", "Could not save benchmark data", e);
    }
  }
}
