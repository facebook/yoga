/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

const {
  copyTask,
  jestTask,
  parallel,
  series,
  spawn,
  task,
} = require("just-scripts");
const glob = require("glob");
const which = require("which");

const cmake = which.sync("cmake");
const emcmake = which.sync("emcmake");
const ninja = which.sync("ninja", { nothrow: true });
const node = which.sync("node");
const npx = which.sync("npx");

task("copy-dts", copyTask({ paths: ["./src_js/**/*.d.ts"], dest: "./dist" }));

task("babel", () =>
  spawn(npx, ["babel", "src_js", "--source-maps", "--out-dir", "dist"])
);

task("cmake-generate", () =>
  spawn(emcmake, [
    "cmake",
    "-S",
    ".",
    "-B",
    "build",
    ...(ninja ? ["-G", "Ninja"] : []),
  ])
);

function prepareTask() {
  return parallel("cmake-generate", "copy-dts", "babel");
}

function runBenchTask() {
  const files = glob.sync("./tests/Benchmarks/**/*.js");
  return () =>
    spawn(node, ["./tests/run-bench.js", ...files], { stdio: "inherit" });
}

function cmakeBuildTask(targets) {
  return () =>
    spawn(
      cmake,
      ["--build", "build", ...(targets ? ["--target", ...targets] : [])],
      { stdio: "inherit" }
    );
}

function buildFlavor(flavor, env) {
  task(`cmake-build:${flavor}`, cmakeBuildTask([flavor]));
  task(`jest:${flavor}`, jestTask({ env }));
  task(
    `test:${flavor}`,
    series(prepareTask(), `cmake-build:${flavor}`, `jest:${flavor}`)
  );
}

buildFlavor("asmjs-async", { WASM: 0, SYNC: 0 });
buildFlavor("asmjs-sync", { WASM: 0, SYNC: 1 });
buildFlavor("wasm-async", { WASM: 1, SYNC: 0 });
buildFlavor("wasm-sync", { WASM: 1, SYNC: 1 });

task("cmake-build:all", cmakeBuildTask());
task("cmake-build:async", cmakeBuildTask(["asmjs-async", "wasm-async"]));
task("cmake-build:sync", cmakeBuildTask(["asmjs-sync", "wasm-sync"]));

task("build", series(prepareTask(), "cmake-build:all"));

task(
  "test",
  series(
    prepareTask(),
    series("cmake-build:asmjs-async", "jest:asmjs-async"),
    series("cmake-build:asmjs-sync", "jest:asmjs-sync"),
    series("cmake-build:wasm-async", "jest:wasm-async"),
    series("cmake-build:wasm-sync", "jest:wasm-sync")
  )
);

task("benchmark", series(prepareTask(), "cmake-build:sync", runBenchTask()));
