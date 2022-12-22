/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

const entry = require('./entry');
const yoga = require('./wasm');

module.exports = entry(yoga());

export type * from './YGEnums.js';
export type * from './entry';
