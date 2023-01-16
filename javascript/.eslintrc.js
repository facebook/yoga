/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

module.exports = {
  root: true,
  ignorePatterns: ["dist/**", "**/*.d.ts"],
  parser: "@babel/eslint-parser",
  extends: [
    "eslint:recommended",
    "plugin:jest/recommended",
    "plugin:prettier/recommended",
  ],
  rules: {
    "no-var": "error",
    "prefer-arrow-callback": "error",
    "prefer-const": "error",
    "prefer-object-spread": "error",
    "prefer-spread": "error",
    "require-await": "error",
  },
  env: {
    commonjs: true,
    es6: true,
  },
  overrides: [
    {
      files: ["jest.*", "just.config.js", "tests/**"],
      env: {
        node: true,
      },
      globals: {
        getMeasureCounter: "writable",
        getMeasureCounterMax: "writable",
        getMeasureCounterMin: "writable",
        Yoga: "writable",
        YGBENCHMARK: "writable",
      },
    },
  ],
};
