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
const yoga = require('./asm');

// $FlowFixMe ret will not be null here
module.exports = entry(yoga());

export type {
  Yoga$Justify,
  Yoga$Align,
  Yoga$FlexDirection,
  Yoga$Direction,
  Yoga$Wrap,
  Yoga$Gutter,
  Yoga$Edge,
  Yoga$Display,
  Yoga$Unit,
  Yoga$Overflow,
  Yoga$PositionType,
  Yoga$ExperimentalFeature,
} from './YGEnums.js';

export type {Yoga$Node, Yoga$Config} from './entry';
