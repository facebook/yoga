var Yoga = require("../sources/entry-" + process.env.TEST_ENTRY);

global.getMeasureCounter = function (cb, staticWidth, staticHeight) {

    var counter = 0;

    return {

        inc: function (width, widthMode, height, heightMode) {

            counter += 1;

            return cb ? cb(width, widthMode, height, heightMode) : new Yoga.Size(staticWidth, staticHeight);

        },

        get: function () {

            return counter;

        }

    };

}

global.getMeasureCounterMax = function () {

    return getMeasureCounter(function (width, widthMode, height, heightMode) {

        var measuredWidth = widthMode === Yoga.MEASURE_MODE_UNDEFINED ? 10 : width;
        var measuredHeight = heightMode === Yoga.MEASURE_MODE_UNDEFINED ? 10 : height;

        return new Yoga.Size(measuredWidth, measuredHeight);

    });

};

global.getMeasureCounterMin = function () {

    return getMeasureCounter(function (width, widthMode, height, heightMode) {

        var measuredWidth = widthMode === Yoga.MEASURE_MODE_UNDEFINED || (widthMode == Yoga.MEASURE_MODE_AT_MOST && width > 10) ? 10 : width;
        var measuredHeight = heightMode === Yoga.MEASURE_MODE_UNDEFINED || (heightMode == Yoga.MEASURE_MODE_AT_MOST && height > 10) ? 10 : height;

        return new Yoga.Size(measuredWidth, measuredHeight);

    });

};
