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

import {Button} from 'antd';
import React from 'react';
import Page from '../components/Page';
import Padded from '../components/Padded';
import Playground from '../components/Playground';
import {Row, Col} from 'antd';
import './index.css';

export default () => (
  <Page>
    <Padded className="IndexPageSection">
      <Row>
        <Col span={12}>
          <h1>Flexible Layouts with Yoga</h1>
          <p>
            Build flexible layouts on any platform with a highly optimized
            layout engine designed with speed, size, and ease of use in mind.
          </p>
          <Button type="primary" className="button-spacing">
            Get started
          </Button>
          <Button type="primary" ghost>
            Try it out
          </Button>
        </Col>
        <Col span={12} />
      </Row>
    </Padded>
    <Playground selectedNodePath={[]} showGuides={false} height={501} />
    <Padded className="IndexPageSection">
      <Row>
        <Col span={12} />
        <Col span={12}>
          <h1>Integrated Into The Most Optimized Mobile Frameworks</h1>
          <p>
            Facebook makes use of Yoga to power most of their UI Frameworks.
            This ensured layout can be performed quickly and fluidly off of the
            main thread to ensure optimal performance. As an added benefit
            engineers familiar with one framework can get started quickly with
            another thanks to the shared layout engine.
          </p>
        </Col>
      </Row>
    </Padded>
    <Padded className="IndexPageSection">
      <Row>
        <Col span={12}>
          <h1>Proven In Productions</h1>
          <p>
            Yoga powers some of the largest apps in the world, including many of
            Facebook's products. This should help convince you that Yoga is
            ready to handle the scale of almost any app out there.
          </p>
        </Col>
        <Col span={12} />
      </Row>
    </Padded>
  </Page>
);
