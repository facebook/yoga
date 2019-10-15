/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <fbjni/fbjni.h>
#include <yoga/testutil/testutil.h>

using namespace facebook;

namespace {

void startCountingNodes(jni::alias_ref<jclass>) {
  yoga::test::TestUtil::startCountingNodes();
}

jint nodeCount(jni::alias_ref<jclass>) {
  return yoga::test::TestUtil::nodeCount();
}

jint stopCountingNodes(jni::alias_ref<jclass>) {
  return yoga::test::TestUtil::stopCountingNodes();
}

} // namespace

jint JNI_OnLoad(JavaVM* vm, void*) {
  return jni::initialize(vm, [] {
    jni::registerNatives(
        "com/facebook/yoga/TestUtil",
        {
            makeNativeMethod("startCountingNodes", startCountingNodes),
            makeNativeMethod("nodeCount", nodeCount),
            makeNativeMethod("stopCountingNodes", stopCountingNodes),
        });
  });
}
