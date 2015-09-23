/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

namespace Facebook.CSSLayout
{

    /**
     * A context for holding values local to a given instance of layout computation.
     *
     * This is necessary for making layout thread-safe. A separate instance should
     * be used when {@link CSSNode#calculateLayout} is called concurrently on
     * different node hierarchies.
     */

    sealed class CSSLayoutContext
    {
        /*package*/
        public MeasureOutput measureOutput = new MeasureOutput();
    }
}
