/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#pragma once

#include <CSSLayout/CSSLayout.h>

CSS_EXTERN_C_BEGIN

typedef void (*CSSInteropLoggerFunc)(const char *message);

WIN_EXPORT void CSSInteropSetLogger(CSSInteropLoggerFunc managedFunc);

CSS_EXTERN_C_END
