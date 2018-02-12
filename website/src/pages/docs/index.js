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
import Page from '../../components/Page';
import Padded from '../../components/Padded';
import {Row, Col} from 'antd';

export default () => (
  <Page>
    <Padded>
      <h1>Documentation</h1>
      <p>
        Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam quis
        urna in lacus rutrum vehicula. Curabitur vitae dictum ante, sollicitudin
        sollicitudin tortor. Morbi a vehicula justo. Proin luctus tellus vitae
        nulla bibendum gravida. Duis varius cursus erat ut tempus. Fusce ex
        arcu, accumsan et ultricies at, fermentum sit amet lectus. Donec a neque
        nec leo pharetra fermentum.
      </p>
      <Row>
        <Col md={6} sm={12} xs={24}>
          <h2>Getting Started</h2>
          <Link to="">Litho</Link>
          <br />
          <Link to="">ComponentKit</Link>
          <br />
          <Link to="">React Native</Link>
          <br />
          <Link to="">Addin Yoga to a project</Link>
        </Col>
        <Col md={6} sm={12} xs={24}>
          <h2>Properties</h2>
          <Link to="">Width and height</Link>
          <br />
          <Link to="">Max/min width and height</Link>
          <br />
          <Link to="docs/flexDirection">Flex direction</Link>
          <br />
          <Link to="">Justify content</Link>
          <br />
          <Link to="">Align items/self</Link>
          <br />
          <Link to="">Flex basis, grow and shrink</Link>
          <br />
          <Link to="">Margins, paddings, and borders</Link>
          <br />
          <Link to="">Flex wrap</Link>
          <br />
          <Link to="">Align content</Link>
          <br />
          <Link to="">Absolute layout</Link>
          <br />
          <Link to="">Aspect ratio</Link>
          <br />
          <Link to="">Layout direction</Link>
        </Col>
        <Col md={6} sm={12} xs={24}>
          <h2>Examples</h2>
          <Link to="">Overlays</Link>
          <br />
          <Link to="">Floating buttons</Link>
          <br />
          <Link to="">Flexible text</Link>
        </Col>
        <Col md={6} sm={12} xs={24}>
          <h2>Contributing</h2>
          <Link to="">Check out the code</Link>
          <br />
          <Link to="">Running the test suite</Link>
          <br />
          <Link to="">Making a change</Link>
          <br />
          <Link to="">Adding a test</Link>
          <br />
          <Link to="">Adding documentation</Link>
          <br />
          <Link to="">Opening a pull request</Link>
        </Col>
      </Row>
    </Padded>
  </Page>
);
