#!/usr/bin/env node
/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

require(`./tools`);

const fs = require(`fs`);
const vm = require(`vm`);

const WARMUP_ITERATIONS = 3;
const BENCHMARK_ITERATIONS = 10;

const testFiles = process.argv.slice(2).map((file) => {
  return fs.readFileSync(file).toString();
});

const testResults = new Map();

for (const type of ["asmjs", "wasm"]) {
  for (const file of testFiles) {
    vm.runInNewContext(
      file,
      Object.assign(Object.create(global), {
        Yoga: require(type === "asmjs"
          ? "../dist/entrypoint/asmjs-sync"
          : "../dist/entrypoint/wasm-sync"),
        YGBENCHMARK: function (name, fn) {
          let testEntry = testResults.get(name);

          if (testEntry === undefined)
            testResults.set(name, (testEntry = new Map()));

          for (let t = 0; t < WARMUP_ITERATIONS; ++t) fn();

          const start = Date.now();

          for (let t = 0; t < BENCHMARK_ITERATIONS; ++t) fn();

          const end = Date.now();

          testEntry.set(type, (end - start) / BENCHMARK_ITERATIONS);
        },
      })
    );
  }
}

console.log(
  `Note: those tests are independants; there is no time relation to be expected between them`
);

for (const [name, results] of testResults) {
  console.log();

  const min = Math.min(Infinity, ...results.values());

  console.log(name);

  for (const [type, result] of results) {
    console.log(
      `  - ${type}: ${result}ms (${Math.round((result / min) * 10000) / 100}%)`
    );
  }
}
