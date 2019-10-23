/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
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
