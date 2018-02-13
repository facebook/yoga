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
import Link from 'gatsby-link';
import {Icon} from 'antd';
import './Toolbar.css';

type Props = {
  onShowCode?: () => void,
};

export default class Toolbar extends Component<Props> {
  render() {
    return (
      <div className="Toolbar">
        <Link to="/" className="logo">
          <img
            src="https://facebook.github.io/yoga/static/logo.svg"
            width="42"
            alt="Yoga logo"
          />
        </Link>
        
        <Link to="/docs" activeClassName="selected">Documentation</Link>
        <Link to="/playground" activeClassName="selected">Playground</Link>
        <a href="https://github.com/facebook/yoga">GitHub</a>

        {this.props.onShowCode && (
          <a className="ToolbarToggle" onClick={this.props.onShowCode}>
            <Icon type={'code-o'} />
            Code
          </a>
        )}
      </div>
    );
  }
}
