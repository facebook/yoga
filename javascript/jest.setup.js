/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

module.exports = async () => {
  if (process.env["SYNC"] == true && process.env["WASM"] == true) {
    global.Yoga = require("./dist/entrypoint/wasm-sync");
  } else if (process.env["SYNC"] == true) {
    global.Yoga = require("./dist/entrypoint/asmjs-sync");
  } else if (process.env["WASM"] == true) {
    global.Yoga = await require("./dist/entrypoint/wasm-async").loadYoga();
  } else {
    global.Yoga = await require("./dist/entrypoint/asmjs-async").loadYoga();
  }
};

Object.defineProperty(global, "YGBENCHMARK", {
  get: () => global.test,
});
