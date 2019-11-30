/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga;

import java.util.Arrays;
import java.util.List;

public class TestParametrization {
  public static Iterable<NodeFactory> nodeFactories() {
    NodeFactory nodeFactory = new NodeFactory() {
      @Override
      public YogaNode create() {
        return YogaNodeFactory.create();
      }

      @Override
      public YogaNode create(YogaConfig config) {
        return YogaNodeFactory.create(config);
      }

      @Override
      public String toString() {
        return "JNI";
      }
    };
    return Arrays.asList(nodeFactory);
  }


  public interface NodeFactory {
    YogaNode create();
    YogaNode create(YogaConfig config);
  }
}
