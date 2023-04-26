/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import type { Yoga } from "./wrapAsm";

export type * from "./generated/YGEnums";
export type * from "./wrapAsm";

export function loadYoga(): Promise<Yoga>;
