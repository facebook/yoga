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
import yoga from 'yoga-layout';
import {Radio, Menu, Dropdown, Button, Icon} from 'antd';
import './YogaEnumSelect.css';
const RadioButton = Radio.Button;
const RadioGroup = Radio.Group;

type Props = {
  property: string,
  disabled?: boolean,
  value: string | number,
  onChange: (value: number) => void,
};

export default class YogaEnumSelect extends Component<Props> {
  values: Array<{key: string, value: number}>;

  constructor({property}: Props) {
    super();
    // $FlowFixMe
    this.values = Object.keys(yoga)
      .map(key => ({key, value: yoga[key]}))
      .filter(
        ({key}) => key.startsWith(property) && key !== `${property}_COUNT`,
      );
  }

  handleMenuClick = ({key}: {key: string}) => {
    this.props.onChange(yoga[key]);
  };

  render() {
    const {property, ...props} = this.props;
    const selected = this.values.find(
      ({key, value}) => value === this.props.value,
    );
    const replacer = new RegExp(`^${property}_`);

    return this.values.length > 3 ? (
      <Dropdown
        disabled={props.disabled}
        overlay={
          <Menu onClick={this.handleMenuClick}>
            {this.values.map(({key, value}) => (
              <Menu.Item key={key} value={value}>
                {key.replace(replacer, '')}
              </Menu.Item>
            ))}
          </Menu>
        }>
        <Button>
          {selected ? selected.key.replace(replacer, '') : 'undefiend'}{' '}
          <Icon type="down" />
        </Button>
      </Dropdown>
    ) : (
      <RadioGroup
        {...props}
        onChange={e => this.props.onChange(e.target.value)}
        defaultValue="a"
        className="YogaEnumSelect">
        {this.values.map(({key, value}) => (
          <RadioButton key={key} value={value}>
            {key.replace(new RegExp(`^${property}_`), '')}
          </RadioButton>
        ))}
      </RadioGroup>
    );
  }
}
