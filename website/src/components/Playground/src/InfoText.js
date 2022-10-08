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
import {Popover, Icon} from 'antd';
import Link from 'gatsby-link';
import './InfoText.css';

type Props = {
  children: any,
  doclink: string,
};

export default class InfoText extends Component<Props> {
  render() {
    return (
      <Popover
        content={
          <div className="InfoText">
            <p>{this.props.children}</p>
            <Link className="docs-link" to={this.props.doclink}>
              DOCUMENTATION
            </Link>
          </div>
        }
        trigger="hover">
        <Icon className="InfoTextIcon" type="info-circle-o" />
      </Popover>
    );
  }
}
