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
     * The CSS style definition for a {@link CSSNode}.
     */
    sealed class CSSStyle
    {
        public CSSDirection direction = CSSDirection.Inherit;
        public CSSFlexDirection flexDirection = CSSFlexDirection.Column;
        public CSSJustify justifyContent = CSSJustify.FlexStart;
        public CSSAlign alignContent = CSSAlign.FlexStart;
        public CSSAlign alignItems = CSSAlign.Stretch;
        public CSSAlign alignSelf = CSSAlign.Auto;
        public CSSPositionType positionType = CSSPositionType.Relative;
        public CSSWrap flexWrap = CSSWrap.NoWrap;
        public float flex;

        public Spacing margin = new Spacing();
        public Spacing padding = new Spacing();
        public Spacing border = new Spacing();

        public float[] position = {
            CSSConstants.Undefined,
            CSSConstants.Undefined,
            CSSConstants.Undefined,
            CSSConstants.Undefined
        };

        public float[] dimensions = {
            CSSConstants.Undefined,
            CSSConstants.Undefined
        };

        public float minWidth = CSSConstants.Undefined;
        public float minHeight = CSSConstants.Undefined;

        public float maxWidth = CSSConstants.Undefined;
        public float maxHeight = CSSConstants.Undefined;
    }
}
