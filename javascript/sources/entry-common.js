/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

function patch(prototype, name, fn) {

    let original = prototype[name];

    prototype[name] = function (... args) {
        return fn.call(this, original, ... args);
    };

}

module.exports = function (bind, lib) {

    let constants = {};

    constants.ALIGN_AUTO = 0;
    constants.ALIGN_CENTER = 2;
    constants.ALIGN_FLEX_END = 3;
    constants.ALIGN_FLEX_START = 1;
    constants.ALIGN_STRETCH = 4;

    constants.DIRECTION_INHERIT = 0;
    constants.DIRECTION_LTR = 1;
    constants.DIRECTION_RTL = 2;

    constants.EDGE_ALL = 8;
    constants.EDGE_BOTTOM = 3;
    constants.EDGE_END = 5;
    constants.EDGE_HORIZONTAL = 6;
    constants.EDGE_LEFT = 0;
    constants.EDGE_RIGHT = 2;
    constants.EDGE_START = 4;
    constants.EDGE_TOP = 1;
    constants.EDGE_VERTICAL = 7;

    constants.FEATURE_ROUNDING = 0;
    constants.FEATURE_WEB_FLEX_BASIS = 1;

    constants.FLEX_DIRECTION_COLUMN = 0;
    constants.FLEX_DIRECTION_COLUMN_REVERSE = 1;
    constants.FLEX_DIRECTION_ROW = 2;
    constants.FLEX_DIRECTION_ROW_REVERSE = 3;

    constants.JUSTIFY_CENTER = 1;
    constants.JUSTIFY_FLEX_END = 2;
    constants.JUSTIFY_FLEX_START = 0;
    constants.JUSTIFY_SPACE_AROUND = 4;
    constants.JUSTIFY_SPACE_BETWEEN = 3;

    constants.MEASURE_MODE_UNDEFINED = 0;
    constants.MEASURE_MODE_EXACTLY = 1;
    constants.MEASURE_MODE_AT_MOST = 2;

    constants.OVERFLOW_HIDDEN = 1;
    constants.OVERFLOW_VISIBLE = 0;
    constants.OVERFLOW_SCROLL = 2;

    constants.POSITION_TYPE_ABSOLUTE = 1;
    constants.POSITION_TYPE_RELATIVE = 0;

    constants.WRAP_NO_WRAP = 0;
    constants.WRAP_WRAP = 1;

    constants.UNDEFINED = NaN;

    class Layout {

        constructor(left, right, top, bottom, width, height) {

            this.left = left;
            this.right = right;

            this.top = top;
            this.bottom = bottom;

            this.width = width;
            this.height = height;

        }

        fromJS(expose) {

            expose(this.left, this.right, this.top, this.bottom, this.width, this.height);

        }

        toString() {

            return `<Layout#${this.left}:${this.right};${this.top}:${this.bottom};${this.width}:${this.height}>`;

        }

    }

    class Size {

        static fromJS({ width, height }) {

            return new Size(width, height);

        }

        constructor(width, height) {

            this.width = width;
            this.height = height;

        }

        fromJS(expose) {

            expose(this.width, this.height);

        }

        toString() {

            return `<Size#${this.width}x${this.height}>`;

        }

    }

    patch(lib.Node.prototype, `free`, function () {

        // Since we handle the memory allocation ourselves (via lib.Node.create), we also need to handle the deallocation

        lib.Node.destroy(this);

    });

    patch(lib.Node.prototype, `freeRecursive`, function () {

        for (let t = 0, T = this.getChildCount(); t < T; ++t)
            this.getChild(0).freeRecursive();

        this.free();

    });

    patch(lib.Node.prototype, `setMeasureFunc`, function (original, measureFunc) {

        // This patch is just a convenience patch, since it helps write more idiomatic source code (such as .setMeasureFunc(null))
        // We also automatically convert the return value of the measureFunc to a Size object, so that we can return anything that has .width and .height properties

        if (measureFunc) {
            return original.call(this, (... args) => Size.fromJS(measureFunc(... args)));
        } else {
            return this.unsetMeasureFunc();
        }

    });

    patch(lib.Node.prototype, `calculateLayout`, function (original, width = constants.UNDEFINED, height = constants.UNDEFINED, direction = constants.DIRECTION_LTR) {

        // Just a small patch to add support for the function default parameters

        return original.call(this, width, height, direction);

    });

    function setExperimentalFeatureEnabled(... args) {

        return lib.setExperimentalFeatureEnabled(... args);

    }

    function isExperimentalFeatureEnabled(... args) {

        return lib.isExperimentalFeatureEnabled(... args);

    }

    function getInstanceCount(... args) {

        return lib.getInstanceCount(... args);

    }

    bind(`Layout`, Layout);
    bind(`Size`, Size);

    return Object.assign({

        Node: lib.Node,

        Layout,
        Size,

        setExperimentalFeatureEnabled,
        isExperimentalFeatureEnabled,

        getInstanceCount

    }, constants);

};
