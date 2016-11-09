/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using System;
using System.Runtime.InteropServices;

namespace Facebook.CSSLayout
{
    internal static class CSSAssert
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void FailFunc(string message);

        private static bool _assertInitialized;
        private static FailFunc _failFunc;

        public static void Initialize()
        {
            if (!_assertInitialized)
            {
                _failFunc = (message) => {
                    throw new InvalidOperationException(message);
                };
                Native.CSSAssertSetFailFunc(_failFunc);
                _assertInitialized = true;
            }
        }
    }
}
