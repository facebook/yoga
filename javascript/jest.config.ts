/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import type { Config } from "jest";

const config: Config = {
  setupFiles: ["./jest.setup.ts"],
  testRegex: "/tests/.*\\.test\\.[jt]s$",
};

export default config;
