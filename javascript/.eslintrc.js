/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

module.exports = {
  extends: [
    "eslint:recommended",
    "plugin:jest/recommended",
    "plugin:prettier/recommended",
  ],
  parser: "@babel/eslint-parser",
  env: {
    commonjs: true,
    es6: true,
  },
  ignorePatterns: ["dist/**"],
  overrides: [
    {
      files: ["jest.*", "tests/**"],
      env: {
        node: true,
      },
      globals: {
        getMeasureCounter: "writable",
        getMeasureCounterMax: "writable",
        getMeasureCounterMin: "writable",
        Yoga: "writable",
      },
    },
  ],
};
