/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "YGInterop.h"

static YGInteropLogger gManagedLogger;

static int unmanagedLogger(const YGConfigRef config,
                           const YGNodeRef node,
                           YGLogLevel level,
                           const char *format,
                           va_list args) {
  int result = 0;
  if (gManagedLogger) {
    char message[8192];
    result = vsnprintf(message, sizeof(message), format, args);
    (*gManagedLogger)(config, node, level, message);
  }
  return result;
}

void YGInteropSetLogger(YGInteropLogger managedLogger) {
  gManagedLogger = managedLogger;
  YGSetLogger(YGConfigGetDefault(), &unmanagedLogger);
}
