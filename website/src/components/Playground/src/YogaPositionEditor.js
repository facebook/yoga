/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
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
  disabled?: boolean,
  onChange: (property: Property, value: PositionRecordT) => void,
};

export default class YogaPositionEditor extends Component<Props> {
  static availableProperties = ['position', 'margin', 'padding', 'border'];

  static defaultProps = {
    value: PositionRecord(),
  };

  render() {
    const {onChange, value, property, disabled} = this.props;
    return (
      <div className="YogaPositionEditor">
        <Input
          type="text"
          value={Number.isNaN(value.top) ? '' : value.top}
          disabled={disabled}
          onChange={e => onChange(property, value.set('top', e.target.value))}
        />
        <div className="YogaPositionEditorRow">
          <Input
            type="text"
            value={Number.isNaN(value.left) ? '' : value.left}
            disabled={disabled}
            onChange={e =>
              onChange(property, value.set('left', e.target.value))
            }
          />
          {property.toUpperCase()}
          <Input
            type="text"
            value={Number.isNaN(value.right) ? '' : value.right}
            disabled={disabled}
            onChange={e =>
              onChange(property, value.set('right', e.target.value))
            }
          />
        </div>
        <Input
          type="text"
          value={Number.isNaN(value.bottom) ? '' : value.bottom}
          disabled={disabled}
          onChange={e =>
            onChange(property, value.set('bottom', e.target.value))
          }
        />
      </div>
    );
  }
}
