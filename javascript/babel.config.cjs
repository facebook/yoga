/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

module.exports = api => ({
  presets: [
    [
      '@babel/preset-env',
      {
        targets: [
          'maintained node versions',
          '> 0.5%, last 2 versions, Firefox ESR, not dead',
        ],
        // Do not transform to another module system
        modules: false,
      },
    ],
    [
      '@babel/preset-typescript',
      {
        rewriteImportExtensions: api.env('dist'),
      },
    ],
  ],
});
