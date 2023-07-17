/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

import React, {Component} from 'react';
import yoga from 'yoga-layout/dist/entry-browser';
import {Radio, Menu, Dropdown, Button, Icon} from 'antd';
import './YogaEnumSelect.css';
const RadioButton = Radio.Button;
const RadioGroup = Radio.Group;

const PROPERTY_LOOKUP = {
  flexDirection: 'FLEX_DIRECTION',
  direction: 'DIRECTION',
  justifyContent: 'JUSTIFY',
  alignSelf: 'ALIGN',
  alignContent: 'ALIGN',
  alignItems: 'ALIGN',
  positionType: 'POSITION_TYPE',
  flexWrap: 'WRAP',
};

type Property = $Keys<typeof PROPERTY_LOOKUP>;

type Props = {
  property: Property,
  disabled?: boolean,
  value: string | number,
  onChange: (property: Property, value: number) => void,
};

export default class YogaEnumSelect extends Component<Props> {
  static availableProperties = Object.keys(PROPERTY_LOOKUP);

  values: Array<{key: string, value: number}>;

  constructor({property}: Props) {
    super();
    property = PROPERTY_LOOKUP[property];
    // $FlowFixMe
    this.values = Object.keys(yoga)
      .map(key => ({key, value: yoga[key]}))
      .filter(
        ({key}) => key.startsWith(property) && key !== `${property}_COUNT`,
      );
  }

  handleMenuClick = ({key}: {key: string}) => {
    this.props.onChange(this.props.property, yoga[key]);
  };

  getTitle = (property: string, key: string): string => {
    const replacer = new RegExp(`^${property}_`);
    return key.replace(replacer, '').replace('_', ' ').toLowerCase();
  };

  render() {
    let {property, ...props} = this.props;
    property = PROPERTY_LOOKUP[property];
    const selected = this.values.find(
      ({key, value}) => value === this.props.value,
    );

    return this.values.length > 3 ? (
      <div className="YogaEnumSelect">
        <Dropdown
          trigger={['click']}
          disabled={props.disabled}
          overlay={
            <Menu onClick={this.handleMenuClick}>
              {this.values.map(({key, value}) => (
                <Menu.Item key={key} value={value}>
                  {this.getTitle(property, key)}
                </Menu.Item>
              ))}
            </Menu>
          }>
          <Button>
            {selected ? this.getTitle(property, selected.key) : ''}
            <Icon type="down" />
          </Button>
        </Dropdown>
      </div>
    ) : (
      <RadioGroup
        {...props}
        onChange={e => this.props.onChange(this.props.property, e.target.value)}
        defaultValue="a"
        className="YogaEnumSelect">
        {this.values.map(({key, value}) => (
          <RadioButton key={key} value={value}>
            {this.getTitle(property, key)}
          </RadioButton>
        ))}
      </RadioGroup>
    );
  }
}
