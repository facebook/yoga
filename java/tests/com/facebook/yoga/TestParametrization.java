/*
 *  Copyright (c) 2018-present, Facebook, Inc.
 *
 *  This source code is licensed under the MIT license found in the LICENSE
 *  file in the root directory of this source tree.
 *
 */
package com.facebook.yoga;

import java.util.Arrays;

public class TestParametrization {
  public static Iterable<NodeFactory> nodeFactories() {
    return Arrays.asList(
        new NodeFactory() {
          @Override
          public YogaNode create() {
            return new YogaNode();
          }

          @Override
          public YogaNode create(YogaConfig config) {
            return new YogaNode(config);
          }

          @Override
          public String toString() {
            return "JNI";
          }
        },
        new NodeFactory() {
          @Override
          public YogaNode create() {
            return new YogaNode(true);
          }

          @Override
          public YogaNode create(YogaConfig config) {
            return new YogaNode(true, config);
          }

          @Override
          public String toString() {
            return "ByteBuffer";
          }
        });
  }

  public interface NodeFactory {
    YogaNode create();

    YogaNode create(YogaConfig config);
  }
}
