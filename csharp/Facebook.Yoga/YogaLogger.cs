/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

using System;
using System.Runtime.InteropServices;

namespace Facebook.Yoga
{
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void YogaLogger(
        IntPtr unmanagedConfigPtr,
        IntPtr unmanagedNotePtr,
        YogaLogLevel level,
        string message);
}
