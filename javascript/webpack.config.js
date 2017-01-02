/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

module.exports = {

    entry: "./sources/entry-browser",

    output: {

        path: require("path").resolve(__dirname, "dist"),
        filename: "Yoga.bundle.js",

        libraryTarget: "umd",
        library: "Yoga"

    },

    node: {

        fs: "empty",
        module: "empty"

    },

    performance: {

        hints: false

    },

    plugins: [

        new (require("webpack").BannerPlugin)(require("fs").readFileSync(__dirname + "/../LICENSE", "utf8"))

    ]

};
