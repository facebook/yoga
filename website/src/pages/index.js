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
import ReactNativeLogo from './logos/reactnative.png';
import LithoLogo from './logos/litho.png';
import ComponentKitLogo from './logos/componentkit.png';
import Link from 'gatsby-link';
import Footer from '../components/Footer';

const HeroSection = () => (
  <Padded>
    <Row className="hero">
      <Col md={12} sm={24} xs={24}>
        <h3>INTRODUCING</h3>
        <h1>
          Flexible Layouts <br /> with Yoga
        </h1>
        <p>
          Build flexible layouts on any platform with a highly optimized layout
          engine designed with speed, size, and ease of use in mind. Yoga is
          open source and ready for you to use today.
        </p>

        <Link to="/docs">
          <Button type="primary" className="button">
            LEARN MORE
          </Button>
        </Link>
      </Col>
      <Col md={12} sm={0} xs={0}>
        <div className="blueprint blueprint-container">
          <div className="blueprint blueprint-avatar" />
          <div className="blueprint blueprint-title" />
          <div className="blueprint blueprint-subtitle" />
          <div className="blueprint blueprint-content" />
        </div>
      </Col>
    </Row>
  </Padded>
);

const PlaygroundSection = () => (
  <Row>
    <Col lg={24} md={0} sm={0} xs={0}>
      <Playground selectedNodePath={[]} showGuides={false} height={601} />
    </Col>
  </Row>
);

const AboutSectionOne = () => (
  <Padded className="about-section">
    <Row>
      <Col xl={16} lg={16} md={24} sm={24} xs={24}>
        <h1>Foundation of Many Open Source&nbsp;UI Frameworks</h1>
        <p>
          There are a large number of open source UI Frameworks which rely on
          Yoga to power their layout. Yoga enables these frameworks to perform
          layout in a simple and intuitive way across all platforms. This allows
          engineers across platforms to collaborate more easily. Yoga allows
          these frameworks to calculate layouts off the main thread to help
          ensure optimal UI performance.
        </p>
      </Col>
    </Row>
    <div className="logo-group">
      <a href="https://fblitho.com" target="_blank" className="logo">
        <img src={LithoLogo} />
        <h3>Litho</h3>
      </a>
      <a href="https://componentkit.org" target="_blank" className="logo">
        <img src={ComponentKitLogo} />
        <h3>ComponentKit</h3>
      </a>
      <a
        href="http://facebook.github.io/react-native/"
        target="_blank"
        className="logo">
        <img src={ReactNativeLogo} />
        <h3>React Native</h3>
      </a>
    </div>
  </Padded>
);

const AboutSectionTwo = () => (
  <Padded className="about-section">
    <Row>
      <Col xl={16} lg={16} md={24} sm={24} xs={24}>
        <h1>Why You May Consider Yoga</h1>

        <h3>PERFORMANCE</h3>
        <p>
          Yoga was built to be fast and performance will always be one of Yoga's
          primary goals. We believe that for a layout engine to be able to power
          any range of applications it needs to be fast and never stand in the
          way of a fluid user experience.
        </p>

        <h3>CROSS PLATFORM</h3>
        <p>
          Yoga is built with cross platform in mind. To ensure Yoga can be used
          anywhere we have written is in portable C/C++ and tried to keep both
          the dependencies and final binary size impact as low as possible. This
          means you can use Yoga on iOS and Android, sharing knowledge and
          potentially code between platforms.
        </p>

        <h3>EASY TO LEARN</h3>
        <p>
          With Yoga we have focused on making it as easy as possible to pick up
          and learn. With interactive documentation pages and a fully fledged
          layout editor we believe that any engineering team can get up to speed
          in record time. If you are using Yoga with any of the major UI
          frameworks we even provide generated code from the layout editor.
        </p>
      </Col>
    </Row>
  </Padded>
);

export default () => (
  <Page className="landing-page">
    <HeroSection />
    <PlaygroundSection />
    <AboutSectionOne />
    <hr />
    <AboutSectionTwo />
    <Footer />
  </Page>
);
