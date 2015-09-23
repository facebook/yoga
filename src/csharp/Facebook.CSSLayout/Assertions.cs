/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using System.Diagnostics;

namespace Facebook.CSSLayout
{
    static class Assertions
    {
        public static T assertNotNull<T>(T v) where T : class
        {
            Debug.Assert(v != null);
            return v;
        }
    }
}
