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

    }

};
