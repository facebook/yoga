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
const encmake = which.sync("emcmake");
const ninja = which.sync("ninja", { nothrow: true });
const node = which.sync("node");
const npx = which.sync("npx");

task(
  "copy-dts",
  copyTask({
    paths: ["./src_js/**/*.d.ts"],
    dest: "./dist",
  })
);

task("babel", () =>
  spawn(npx, ["babel", "src_js", "--source-maps", "--out-dir", "dist"])
);

task("cmake-generate", () =>
  spawn(encmake, [
    "cmake",
    "-S",
    ".",
    "-B",
    "build",
    ...(ninja ? ["-G", "Ninja"] : []),
  ])
);

task("prepare", parallel("copy-dts", "babel", "cmake-generate"));

function cmakeBuildTask(targets) {
  return () =>
    spawn(
      cmake,
      ["--build", "build", ...(targets ? ["--target", ...targets] : [])],
      { stdio: "inherit" }
    );
}

task("cmake-build:all", cmakeBuildTask());
task("cmake-build:async", cmakeBuildTask(["asmjs-async", "wasm-async"]));
task("cmake-build:sync", cmakeBuildTask(["asmjs-sync", "wasm-sync"]));
task("cmake-build:asmjs-async", cmakeBuildTask(["asmjs-async"]));
task("cmake-build:asmjs-sync", cmakeBuildTask(["asmjs-sync"]));
task("cmake-build:wasm-async", cmakeBuildTask(["wasm-async"]));
task("cmake-build:wasm-sync", cmakeBuildTask(["wasm-sync"]));

task("jest:asmjs-async", jestTask({ env: { WASM: false, SYNC: false } }));
task("jest:asmjs-sync", jestTask({ env: { WASM: false, SYNC: true } }));
task("jest:wasm-async", jestTask({ env: { WASM: true, SYNC: false } }));
task("jest:wasm-sync", jestTask({ env: { WASM: true, SYNC: true } }));

task(
  "test:asmjs-async",
  series("prepare", "cmake-build:asmjs-async", "jest:asmjs-async")
);
task(
  "test:asmjs-sync",
  series("prepare", "cmake-build:asmjs-sync", "jest:asmjs-sync")
);
task(
  "test:wasm-async",
  series("prepare", "cmake-build:wasm-async", "jest:wasm-async")
);
task(
  "test:wasm-sync",
  series("prepare", "cmake-build:wasm-sync", "jest:wasm-sync")
);

task("run-bench", () =>
  spawn(
    node,
    ["./tests/run-bench.js", ...glob.sync("./tests/Benchmarks/**/*.js")],
    { stdio: "inherit" }
  )
);

task("build", series("prepare", "cmake-build:all"));

task(
  "test",
  series(
    "prepare",
    series(
      series("cmake-build:asmjs-async", "jest:asmjs-async"),
      series("cmake-build:asmjs-sync", "jest:asmjs-sync"),
      series("cmake-build:wasm-async", "jest:wasm-async"),
      series("cmake-build:wasm-sync", "jest:wasm-sync")
    )
  )
);

task("benchmark", series("prepare", "cmake-build:sync", "run-bench"));
