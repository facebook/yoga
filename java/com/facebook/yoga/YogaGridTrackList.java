/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Represents a list of grid tracks for use with grid-template-rows/columns.
 */
public class YogaGridTrackList {
  private final List<YogaGridTrackValue> tracks;

  public YogaGridTrackList() {
    this.tracks = new ArrayList<>();
  }

  public void addTrack(YogaGridTrackValue track) {
    tracks.add(track);
  }

  public List<YogaGridTrackValue> getTracks() {
    return Collections.unmodifiableList(tracks);
  }

  public int size() {
    return tracks.size();
  }

  public YogaGridTrackValue get(int index) {
    return tracks.get(index);
  }
}
