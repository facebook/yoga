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

namespace Facebook.Yoga
{
    internal static class YogaLogger
    {
#if !__IOS__
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void Func(YogaLogLevel level, string message);
#endif
        private static bool _initialized;
#if !__IOS__
        private static Func _managedLogger = null;

        public static Func Logger = null;
#endif
        public static void Initialize()
        {
            if (!_initialized)
            {
#if !__IOS__
                _managedLogger = (level, message) => {
                    if (Logger != null)
                    {
                        Logger(level, message);
                    }

                    if (level == YogaLogLevel.Error)
                    {
                        throw new InvalidOperationException(message);
                    }
                };
                Native.YGInteropSetLogger(_managedLogger);
#endif
                _initialized = true;
            }
        }
    }
}
