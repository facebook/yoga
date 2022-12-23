/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

const wrapAsm = require('./wrapAsm');
const loadYoga = require('./asmjs-async');

module.exports = {
  load: () => loadYoga().then(wrapAsm),
  ...require('./YGEnums'),
}
