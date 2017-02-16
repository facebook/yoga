/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using System;

namespace Facebook.Yoga
{
    internal static class YogaLogger
    {
        public delegate void Func(YogaLogLevel level, string message);

        private static bool _initialized;

        public static Func Logger = null;

        public static void Initialize()
        {
            if (!_initialized)
            {

                Native.YGInteropSetLogger(LoggerInternal);
                _initialized = true;
            }
        }

#if __IOS__
        [ObjCRuntime.MonoPInvokeCallback(typeof(Func))]
#endif
        public static void LoggerInternal(YogaLogLevel level, string message)
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

    }
}
