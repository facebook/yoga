/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

module.exports = async () => {
  if (process.env['SYNC'] === '1' && process.env['WASM'] === '1') {
    globalThis.Yoga = require('yoga-layout/wasm-sync').default;
  } else if (process.env['SYNC'] === '1') {
    globalThis.Yoga = require('yoga-layout/asmjs-sync').default;
  } else if (process.env['WASM'] === '1') {
    globalThis.Yoga = await require('yoga-layout/wasm-async').loadYoga();
  } else {
    globalThis.Yoga = await require('yoga-layout/asmjs-async').loadYoga();
  }
};

Object.defineProperty(globalThis, 'YGBENCHMARK', {
  get: () => globalThis.test,
});
