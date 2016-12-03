/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "YGInterop.h"

static YGInteropLoggerFunc gManagedFunc;

static int unmanagedLogger(YGLogLevel level, const char *format, va_list args) {
  int result = 0;
  if (gManagedFunc) {
    char buffer[256];
    result = vsnprintf(buffer, sizeof(buffer), format, args);
    (*gManagedFunc)(level, buffer);
  }
  return result;
}

void YGInteropSetLogger(YGInteropLoggerFunc managedFunc) {
  gManagedFunc = managedFunc;
  YGSetLogger(&unmanagedLogger);
}
