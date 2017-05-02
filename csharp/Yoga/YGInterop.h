/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#pragma once

#include <yoga/Yoga.h>

YG_EXTERN_C_BEGIN

typedef int (*YGInteropLogger)(const void *unmanagedConfigPtr,
                               const void *unmanagedNodePtr,
                               YGLogLevel level,
                               const char *message);

WIN_EXPORT YGConfigRef YGConfigGetDefault();

WIN_EXPORT void YGInteropSetLogger(YGInteropLogger managedLogger);

YG_EXTERN_C_END
