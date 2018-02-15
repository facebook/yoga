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
import './Footer.css';
import FacebookOSSLogo from './FacebookOSSLogo';

export default class Footer extends Component<{}> {
  render() {
    return (
      <div className="Footer">
        <Link to="/" className="logoOSS">
          <FacebookOSSLogo />
          Facebook Open Source
        </Link>
        <div className="SocialNetwork">
          <a href="https://code.facebook.com/projects/">Open Source</a>
          <a href="https://github.com/facebook/">Github</a>
          <a href="https://twitter.com/fbOpenSource">Twitter</a>
        </div>
        <a href="https://github.com/facebook/yoga">
          Contribute to this project on Github
        </a>
      </div>
    );
  }
}
