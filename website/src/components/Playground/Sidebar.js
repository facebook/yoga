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
import {Icon} from 'antd';
import './Sidebar.css';

type Props = {
  onClose?: () => void,
  width?: number,
  children: any,
  floating?: boolean,
};

export default class Sidebar extends Component<Props> {
  render() {
    return (
      <div
        className={`Sidebar ${this.props.visible ? 'visible' : ''} ${
          this.props.floating ? 'floating' : ''
        }`}
        style={{width: this.props.width}}>
        {this.props.onClose && (
          <div className="SidebarClose">
            <Icon type="close" onClick={this.props.onClose} />
          </div>
        )}
        {this.props.children}
      </div>
    );
  }
}
