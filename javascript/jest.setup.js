/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

module.exports = async () => {
  if (process.env['SYNC'] == true && process.env['WASM'] == true) {
    global.Yoga = require("./dist/sync.wasm");
  } else if (process.env['SYNC'] == true) {
    global.Yoga = require("./dist/sync.asmjs");
  } else if (process.env['WASM'] == true) {
    global.Yoga = await require("./dist/index.wasm").loadYoga();
  } else {
    global.Yoga = await require("./dist/index.asmjs").loadYoga();
  }
}
