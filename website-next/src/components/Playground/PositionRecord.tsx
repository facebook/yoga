/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import {Record} from 'immutable';

export type PositionRecordType = ReturnType<PositionRecordFactory>;

export type PositionRecordFactory = Record.Factory<{
  top: string | number;
  right: string | number;
  bottom: string | number;
  left: string | number;
}>;

const r: PositionRecordFactory = Record({
  top: 0,
  right: 0,
  bottom: 0,
  left: 0,
});

export default r;
