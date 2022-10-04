/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga;

import com.facebook.soloader.SoLoader;

class TestUtil {
  static {
    SoLoader.loadLibrary("yoga_testutil_jni");
  }

  static native void startCountingNodes();
  static native int nodeCount();
  static native int stopCountingNodes();
}
