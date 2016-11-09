/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

namespace Facebook.CSSLayout
{
    public class MeasureOutput
    {
        public static long Make(int width, int height)
        {
          return (long)(((ulong) width) << 32 | ((ulong) height));
        }

        public static int GetWidth(long measureOutput)
        {
          return (int) (0xFFFFFFFF & (measureOutput >> 32));
        }

        public static int GetHeight(long measureOutput)
        {
          return (int) (0xFFFFFFFF & measureOutput);
        }
    }
}
