/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 * @flow
 * @format
 */

import {Record} from 'immutable';
import type {RecordOf} from 'immutable';

export type PositionRecordT = RecordOf<{
  top: string,
  right: string,
  bottom: string,
  left: string,
}>;

const r: PositionRecordT = Record({
  top: '',
  right: '',
  bottom: '',
  left: '',
});

export default r;
