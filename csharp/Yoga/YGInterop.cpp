/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "YGInterop.h"

static YGInteropLogger gManagedLogger;

static int unmanagedLogger(
    const YGConfigRef config,
    const YGNodeRef node,
    YGLogLevel level,
    const char* format,
    va_list args) {
  int result = 0;
  if (gManagedLogger) {
    char message[8192];
    result = vsnprintf(message, sizeof(message), format, args);
    (*gManagedLogger)(config, node, level, message);
  }
  return result;
}

YOGA_EXPORT void YGInteropSetLogger(YGInteropLogger managedLogger) {
  gManagedLogger = managedLogger;
  YGConfigSetLogger(YGConfigGetDefault(), &unmanagedLogger);
}
