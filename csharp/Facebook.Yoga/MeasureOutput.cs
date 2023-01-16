/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

namespace Facebook.Yoga
{
    public class MeasureOutput
    {
        public static YogaSize Make(float width, float height)
        {
            return new YogaSize { width = width, height = height};
        }
    }
}
