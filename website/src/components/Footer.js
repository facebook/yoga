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

import React from 'react';
import Link from 'gatsby-link';
import './Footer.css';

export default () => (
  <footer className="Footer">
	<Link to="/docs">Docs</Link>
	<Link to="/playground">Playground</Link>
	<a href="https://github.com/facebook/yoga">GitHub</a>
  </footer>
);
