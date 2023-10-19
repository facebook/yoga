/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

module.exports = {
  presets: [
    ['@babel/preset-env', {
      targets: "> 5%, maintained node versions",

      // Preserve ES Modules
      modules: false,
    }],
    ['@babel/preset-typescript', {
      "rewriteImportExtensions": true
    }],
  ],
};
