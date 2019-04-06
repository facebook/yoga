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
import YogaEnumSelect from './YogaEnumSelect';
import YogaPositionEditor from './YogaPositionEditor';
import {Input} from 'antd';

type Props<T> = {
  property: string,
  disabled?: boolean,
  value?: ?T,
  onChange: (property: string, value: T) => void,
};

export default (props: Props<*>) => {
  if (YogaEnumSelect.availableProperties.indexOf(props.property) > -1) {
    return <YogaEnumSelect {...props} />;
  } else if (
    YogaPositionEditor.availableProperties.indexOf(props.property) > -1
  ) {
    return <YogaPositionEditor {...props} />;
  } else {
    return (
      <Input
        type="text"
        {...props}
        onChange={e => props.onChange(props.property, e.target.value)}
        placeholder={props.placeholder || 'undefined'}
        onFocus={e => e.target.select()}
        value={Number.isNaN(props.value) ? '' : props.value}
      />
    );
  }
};
