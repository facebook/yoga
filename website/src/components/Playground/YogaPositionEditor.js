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

import React, {Component} from 'react';
import {Input} from 'antd';
import PositionRecord from './PositionRecord';
import type {PositionRecordT} from './PositionRecord';
import './YogaPositionEditor.css';

type Property = 'position' | 'margin' | 'padding' | 'border';

type Props = {
  value: PositionRecordT,
  property: Property,
  onChange: (property: Property, value: PositionRecordT) => void,
};

export default class YogaPositionEditor extends Component<Props> {
  static availableProperties = ['position', 'margin', 'padding', 'border'];

  static defaultProps = {
    value: PositionRecord(),
  };

  render() {
    const {onChange, value, property} = this.props;
    return (
      <div className="YogaPositionEditor">
        <Input
          type="text"
          value={value.top}
          onChange={e => onChange(property, value.set('top', e.target.value))}
        />
        <div className="YogaPositionEditorRow">
          <Input
            type="text"
            value={value.left}
            onChange={e =>
              onChange(property, value.set('left', e.target.value))
            }
          />
          {property}
          <Input
            type="text"
            value={value.right}
            onChange={e =>
              onChange(property, value.set('right', e.target.value))
            }
          />
        </div>
        <Input
          type="text"
          value={value.bottom}
          onChange={e =>
            onChange(property, value.set('bottom', e.target.value))
          }
        />
      </div>
    );
  }
}
