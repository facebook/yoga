/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import wrapAssembly from '../wrapAssembly';

export * from '../generated/YGEnums';
export type {
  Config,
  DirtiedFunction,
  MeasureFunction,
  Node,
  Yoga,
} from '../wrapAssembly';

const loadAssembly = require('../../binaries/wasm-sync-web');
const Yoga = wrapAssembly(loadAssembly());
export default Yoga;
