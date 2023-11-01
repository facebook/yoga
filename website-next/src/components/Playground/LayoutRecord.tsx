/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import {Record, List} from 'immutable';
import PositionRecord from './PositionRecord';
import type {PositionRecordType} from './PositionRecord';

import {Align, Justify, FlexDirection, Wrap, PositionType} from 'yoga-layout';

export type LayoutRecordType = ReturnType<LayoutRecordFactory>;

export type LayoutRecordFactory = Record.Factory<{
  width?: number | 'auto';
  height?: number | 'auto';
  minWidth?: number;
  minHeight?: number;
  maxWidth?: number;
  maxHeight?: number;
  justifyContent?: Justify;
  padding: PositionRecordType;
  border: PositionRecordType;
  margin: PositionRecordType;
  position: PositionRecordType;
  positionType: PositionType;
  alignItems?: Align;
  alignSelf?: Align;
  alignContent?: Align;
  flexDirection?: FlexDirection;
  flexBasis?: number | 'auto';
  flexGrow?: number;
  flexShrink?: number;
  flexWrap?: Wrap;
  aspectRatio?: number | 'auto';
  children?: List<LayoutRecordType>;
}>;

const r: LayoutRecordFactory = Record({
  width: 'auto',
  height: 'auto',
  justifyContent: Justify.FlexStart,
  alignItems: Align.Stretch,
  alignSelf: Align.Auto,
  alignContent: Align.Stretch,
  flexDirection: FlexDirection.Row,
  padding: PositionRecord(),
  margin: PositionRecord(),
  border: PositionRecord(),
  position: PositionRecord({
    left: NaN,
    top: NaN,
    right: NaN,
    bottom: NaN,
  }),
  positionType: PositionType.Relative,
  flexWrap: Wrap.NoWrap,
  flexBasis: 'auto',
  flexGrow: 0,
  flexShrink: 1,
  children: List(),
  aspectRatio: 'auto',
  minWidth: NaN,
  maxWidth: NaN,
  minHeight: NaN,
  maxHeight: NaN,
});

export default r;
