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
    public class YogaConfig
    {
        private Native.YGConfigHandle _ygConfig;

        public YogaConfig()
        {
            _ygConfig = Native.YGConfigNew();
            if (_ygConfig.IsInvalid)
            {
                throw new InvalidOperationException("Failed to allocate native memory");
            }
        }

        internal Native.YGConfigHandle Handle
        {
            get {
                return _ygConfig;
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

        public float PointScaleFactor
        {
            set
            {
                Native.YGConfigSetPointScaleFactor(_ygConfig, value);
            }
        }
    }
}
