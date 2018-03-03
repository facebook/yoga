#pragma warning disable CS1587 // XML comment is not placed on a valid language element
#pragma warning disable CS1591 // Missing XML comment for publicly visible type or member
/**
 * Copyright (c) 2014-present, Facebook, Inc.
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
