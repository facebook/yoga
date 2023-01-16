/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

const {
  argv,
  cleanTask,
  copyTask,
  eslintTask,
  logger,
  jestTask,
  option,
  parallel,
  series,
  spawn,
  task,
} = require("just-scripts");

const glob = require("glob");
const which = require("which");

const node = process.execPath;

option("fix");

task("clean", cleanTask({ paths: ["build", "dist"] }));

task(
  "prepare-for-build",
  parallel(
    babelTransformTask({ paths: ["src_js"], dest: "dist" }),
    copyTask({ paths: ["src_js/**/*.d.ts"], dest: "dist" }),
    emcmakeGenerateTask()
  )
);

function defineFlavor(flavor, env) {
  task(`cmake-build:${flavor}`, cmakeBuildTask({ targets: [flavor] }));
  task(`jest:${flavor}`, jestTask({ env }));
  task(
    `test:${flavor}`,
    series("prepare-for-build", `cmake-build:${flavor}`, `jest:${flavor}`)
  );
}

defineFlavor("asmjs-async", { WASM: 0, SYNC: 0 });
defineFlavor("asmjs-sync", { WASM: 0, SYNC: 1 });
defineFlavor("wasm-async", { WASM: 1, SYNC: 0 });
defineFlavor("wasm-sync", { WASM: 1, SYNC: 1 });

task("cmake-build:all", cmakeBuildTask());
task(
  "cmake-build:async",
  cmakeBuildTask({ targets: ["asmjs-async", "wasm-async"] })
);
task(
  "cmake-build:sync",
  cmakeBuildTask({ targets: ["asmjs-sync", "wasm-sync"] })
);

task("build", series("prepare-for-build", "cmake-build:all"));

task(
  "test",
  series(
    "prepare-for-build",
    series("cmake-build:asmjs-async", "jest:asmjs-async"),
    series("cmake-build:asmjs-sync", "jest:asmjs-sync"),
    series("cmake-build:wasm-async", "jest:wasm-async"),
    series("cmake-build:wasm-sync", "jest:wasm-sync")
  )
);

task(
  "benchmark",
  series("prepare-for-build", "cmake-build:sync", runBenchTask())
);

task(
  "lint",
  series(eslintTask({ fix: argv().fix }), clangFormatTask({ fix: argv().fix }))
);

function babelTransformTask(opts) {
  return () => {
    const args = [...opts.paths, "--source-maps", "--out-dir", opts.dest];
    logger.info(`Transforming [${opts.paths.join(",")}] to '${opts.dest}'`);

    return spawn(node, [require.resolve("@babel/cli/bin/babel"), ...args]);
  };
}

function runBenchTask() {
  return () => {
    const files = glob.sync("./tests/Benchmarks/**/*.js");
    const args = ["./tests/run-bench.js", ...files];
    logger.info(args.join(" "));

    return spawn(node, args, { stdio: "inherit" });
  };
}

function emcmakeGenerateTask() {
  return () => {
    const emcmake = which.sync("emcmake");
    const ninja = which.sync("ninja", { nothrow: true });
    const args = [
      "cmake",
      "-S",
      ".",
      "-B",
      "build",
      ...(ninja ? ["-G", "Ninja"] : []),
    ];
    logger.info(["emcmake", ...args].join(" "));

    return spawn(emcmake, args);
  };
}

function cmakeBuildTask(opts) {
  return () => {
    const cmake = which.sync("cmake");
    const args = [
      "--build",
      "build",
      ...(opts?.targets ? ["--target", ...opts.targets] : []),
    ];
    logger.info(["cmake", ...args].join(" "));

    return spawn(cmake, args, { stdio: "inherit" });
  };
}

function clangFormatTask(opts) {
  return () => {
    const args = [
      ...(opts.fix ? ["-i"] : ["--dry-run", "--Werror"]),
      ...glob.sync("**/*.{h,hh,hpp,c,cpp,cc,m,mm}"),
    ];
    logger.info(["clang-format", ...args].join(" "));

    return spawn(node, [require.resolve("clang-format"), ...args], {
      stdio: "inherit",
    });
  };
}
