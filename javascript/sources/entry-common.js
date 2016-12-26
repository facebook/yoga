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

    class Node extends lib.Node {

    }

    function setExperimentalFeatureEnabled(... args) {

        return lib.setExperimentalFeatureEnabled(... args);

    }

    function isExperimentalFeatureEnabled(... args) {

        return lib.isExperimentalFeatureEnabled(... args);

    }

    bind(`Layout`, Layout);

    return Object.assign({ Layout, Node, setExperimentalFeatureEnabled, isExperimentalFeatureEnabled }, constants);

};
