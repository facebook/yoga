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
import './Sidebar.css';

type Props = {
  width?: number,
  children: any,
};

export default class Sidebar extends Component<Props> {
  render() {
    return (
      <div className="Sidebar" style={{width: this.props.width}}>
        {this.props.children}
      </div>
    );
  }
}
