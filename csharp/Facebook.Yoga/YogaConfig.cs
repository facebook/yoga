/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

using System;
using System.Runtime.InteropServices;

#if __IOS__
using ObjCRuntime;
#endif
#if ENABLE_IL2CPP
using AOT;
#endif

namespace Facebook.Yoga
{
    public class YogaConfig
    {
        internal static readonly YogaConfig Default = new YogaConfig(YGConfigHandle.Default);
        private static YogaLogger _managedLogger;

        private YGConfigHandle _ygConfig;
        private Logger _logger;

        private YogaConfig(YGConfigHandle ygConfig)
        {
            _ygConfig = ygConfig;
            if (_ygConfig.IsInvalid)
            {
                throw new InvalidOperationException("Failed to allocate native memory");
            }

            _ygConfig.SetContext(this);

            if (_ygConfig == YGConfigHandle.Default)
            {
                _managedLogger = LoggerInternal;
                Native.YGInteropSetLogger(_managedLogger);
            }
        }

        public YogaConfig()
            : this(Native.YGConfigNew())
        {
        }

        internal YGConfigHandle Handle
        {
            get {
                return _ygConfig;
            }
        }

#if (UNITY_IOS && !UNITY_EDITOR) || ENABLE_IL2CPP || __IOS__
        [MonoPInvokeCallback(typeof(YogaLogger))]
#endif
        private static void LoggerInternal(
            IntPtr unmanagedConfigPtr,
            IntPtr unmanagedNodePtr,
            YogaLogLevel level,
            string message)
        {
            var config = YGConfigHandle.GetManaged(unmanagedConfigPtr);
            if (config == null || config._logger == null)
            {
                // Default logger
                System.Diagnostics.Debug.WriteLine(message);
            }
            else
            {
                var node = YGNodeHandle.GetManaged(unmanagedNodePtr);
                config._logger(config, node, level, message);
            }

            if (level == YogaLogLevel.Error || level == YogaLogLevel.Fatal)
            {
                throw new InvalidOperationException(message);
            }
        }

        public Logger Logger
        {
            get {
                return _logger;
            }

            set {
                _logger = value;
            }
        }

        public void SetExperimentalFeatureEnabled(
            YogaExperimentalFeature feature,
            bool enabled)
        {
            Native.YGConfigSetExperimentalFeatureEnabled(_ygConfig, feature, enabled);
        }

        public bool IsExperimentalFeatureEnabled(YogaExperimentalFeature feature)
        {
            return Native.YGConfigIsExperimentalFeatureEnabled(_ygConfig, feature);
        }

        public bool UseWebDefaults
        {
            get
            {
                return Native.YGConfigGetUseWebDefaults(_ygConfig);
            }

            set
            {
                Native.YGConfigSetUseWebDefaults(_ygConfig, value);
            }
        }

        public bool UseLegacyStretchBehaviour
        {
            get
            {
                return Native.YGConfigGetUseLegacyStretchBehaviour(_ygConfig);
            }

            set
            {
                Native.YGConfigSetUseLegacyStretchBehaviour(_ygConfig, value);
            }
        }

        public float PointScaleFactor
        {
            set
            {
                Native.YGConfigSetPointScaleFactor(_ygConfig, value);
            }
        }

        public static int GetInstanceCount()
        {
            return Native.YGConfigGetInstanceCount();
        }

        public static void SetDefaultLogger(Logger logger)
        {
            Default.Logger = logger;
        }
    }
}
