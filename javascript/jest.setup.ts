/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

module.exports = async () => {
  if (Boolean(process.env["SYNC"]) && Boolean(process.env["WASM"])) {
    globalThis.Yoga = require("./dist/entrypoint/wasm-sync");
  } else if (process.env["SYNC"]) {
    globalThis.Yoga = require("./dist/entrypoint/asmjs-sync");
  } else if (process.env["WASM"]) {
    globalThis.Yoga = await require("./dist/entrypoint/wasm-async").loadYoga();
  } else {
    globalThis.Yoga = await require("./dist/entrypoint/asmjs-async").loadYoga();
  }
};


Object.defineProperty(globalThis, "YGBENCHMARK", {
  get: () => globalThis.test,
});
