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
    public delegate YogaSize YogaMeasureFunc(
        IntPtr unmanagedNodePtr,
        float width,
        YogaMeasureMode widthMode,
        float height,
        YogaMeasureMode heightMode);
}
