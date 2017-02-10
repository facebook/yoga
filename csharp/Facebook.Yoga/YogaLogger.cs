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
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void Func(YogaLogLevel level, string message);

        private static bool _initialized;
        private static Func _managedLogger = null;

        public static Func Logger = null;

        public static void Initialize()
        {
            if (!_initialized)
            {
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
#if __IOS__
                Native.YGInteropSetLogger(ManagedLogger);
#else
                Native.YGInteropSetLogger(_managedLogger);
#endif
                _initialized = true;
            }
        }

#if __IOS__
		delegate void ManagedLoggerCallback(YogaLogLevel level, string message);

		[ObjCRuntime.MonoPInvokeCallback(typeof(ManagedLoggerCallback))]
		public static void ManagedLogger(YogaLogLevel level, string message)
		{
			if (Logger != null)
			{
				Logger(level, message);
			}

			if (level == YogaLogLevel.Error)
			{
				throw new InvalidOperationException(message);
			}
		}
#endif
    }
}
