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
import Link from 'gatsby-link';
import {Icon} from 'antd';
import './Footer.css';
import FacebookOSSLogo from './FacebookOSSLogo';

export default class Footer extends Component<{}> {
  render() {
    return (
      <div className="Footer">
        <a href="https://code.facebook.com/projects/" className="logoOSS">
          <FacebookOSSLogo />
          Facebook Open Source
        </a>
        <div className="SocialNetwork">
          <a href="https://github.com/facebook/yoga">GitHub</a>
          <a href="https://twitter.com/yogalayout">Twitter</a>
        </div>
      </div>
    );
  }
}
