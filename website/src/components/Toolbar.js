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
import Link from 'gatsby-link';
import {Icon, Row, Col} from 'antd';
import logo from '../pages/logos/logo.svg';
import './Toolbar.css';

type Props = {
  onShowCode?: () => void,
};

export default class Toolbar extends Component<Props> {
  render() {
    return (
      <div className="Toolbar">
        <Link to="/" className="logo">
          <img src={logo} width="42" alt="Yoga logo" />
        </Link>

        <Link to="/docs" activeClassName="selected">
          Documentation
        </Link>

        <Row>
          <Col lg={24} md={0} sm={0} xs={0}>
            <Link to="/playground" activeClassName="selected">
              Playground
            </Link>
          </Col>
        </Row>

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
