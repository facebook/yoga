/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import type {Config} from 'jest';

const config: Config = {
  setupFiles: ['./jest.setup.ts'],
  testRegex: '/tests/.*\\.test\\.[jt]s$',
  moduleNameMapper: {
    'yoga-layout':
      process.env['SYNC'] === '1' && process.env['WASM'] === '1'
        ? 'yoga-layout/wasm-sync'
        : process.env['SYNC'] === '1'
        ? 'yoga-layout/asmjs-sync'
        : process.env['WASM'] === '1'
        ? 'yoga-layout/wasm-async'
        : 'yoga-layout/asmjs-async',
  },
};

export default config;
