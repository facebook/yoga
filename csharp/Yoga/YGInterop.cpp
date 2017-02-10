/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "YGInterop.h"

typedef YGSize (*YGInteropMeasureFunc)(void *managed,
                                       float width,
                                       YGMeasureMode widthMode,
                                       float height,
                                       YGMeasureMode heightMode);
typedef float (*YGInteropBaselineFunc)(void *managed, const float width, const float height);

static YGInteropLoggerFunc gManagedLoggerFunc;
static YGInteropMeasureFunc gManagedMeasureFunc;
static YGInteropBaselineFunc gManagedBaselineFunc;

static int unmanagedLoggerFunc(YGLogLevel level, const char *format, va_list args) {
  int result = 0;
  if (gManagedLoggerFunc) {
    char buffer[256];
    result = vsnprintf(buffer, sizeof(buffer), format, args);
    (*gManagedLoggerFunc)(level, buffer);
  }
  return result;
}

void YGInteropSetLogger(YGInteropLoggerFunc managedFunc) {
  gManagedLoggerFunc = managedFunc;
  YGSetLogger(&unmanagedLoggerFunc);
}

static YGSize unmanagedMeasureFunc(YGNodeRef node,
                                   float width,
                                   YGMeasureMode widthMode,
                                   float height,
                                   YGMeasureMode heightMode) {
  YG_ASSERT(gManagedMeasureFunc, "Expect to set managed measure function");
  void *managed = YGNodeGetManaged(node);
  YG_ASSERT(managed, "Expect to set managed in node");
  return (*gManagedMeasureFunc)(managed, width, widthMode, height, heightMode);
}

void YGInteropNodeSetMeasureFunc(YGNodeRef node, YGInteropMeasureFunc managedFunc) {
  gManagedMeasureFunc = managedFunc;
  YGNodeSetMeasureFunc(node, &unmanagedMeasureFunc);
}

static float unmanagedBaselineFunc(YGNodeRef node, const float width, const float height) {
  YG_ASSERT(gManagedBaselineFunc, "Expect to set managed baseline function");
  void *managed = YGNodeGetManaged(node);
  YG_ASSERT(managed, "Expect to set managed in node");
  return (*gManagedBaselineFunc)(managed, width, height);
}

void YGInteropNodeSetBaselineFunc(YGNodeRef node, YGInteropBaselineFunc managedFunc) {
  gManagedBaselineFunc = managedFunc;
  YGNodeSetBaselineFunc(node, &unmanagedBaselineFunc);
}
