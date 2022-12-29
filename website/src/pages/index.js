/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

import {Button} from 'antd';
import React from 'react';
import Page from '../components/Page';
import Padded from '../components/Padded';
import Playground from '../components/Playground/src';
import {Row, Col} from 'antd';
import './index.css';
import ReactNativeLogo from './logos/reactnative.png';
import LithoLogo from './logos/litho.png';
import ComponentKitLogo from './logos/componentkit.png';
import ReactPDFLogo from './logos/reactpdf.png';
import Link from 'gatsby-link';
import Footer from '../components/Footer';

const playgroundInitialState = {
  width: 500,
  height: 500,
  alignItems: 1,
  padding: {
    top: '20',
    right: '20',
    bottom: '20',
    left: '20',
  },
  children: [
    {
      width: 100,
      height: 100,
      minWidth: null,
      maxWidth: null,
      minHeight: null,
      maxHeight: null,
    },
    {
      width: 100,
      height: 100,
      margin: {
        right: '20',
        left: '20',
      },
      flexGrow: '1',
      minWidth: null,
      maxWidth: null,
      minHeight: null,
      maxHeight: null,
    },
    {
      width: 100,
      height: 100,
      minWidth: null,
      maxWidth: null,
      minHeight: null,
      maxHeight: null,
    },
  ],
  minWidth: null,
  maxWidth: null,
  minHeight: null,
  maxHeight: null,
};

const HeroSection = () => (
  <Padded>
    <Row className="hero">
      <Col md={12} sm={24} xs={24}>
        <h3>INTRODUCING</h3>
        <h1>
          Flexible Layouts <br /> with Yoga
        </h1>
        <p>
          Build flexible layouts on any platform with a highly optimized open
          source layout engine designed with speed, size, and ease of use in
          mind.
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
      <Playground
        selectedNodePath={[]}
        showGuides={true}
        height={601}
        layoutDefinition={playgroundInitialState}
      />
    </Col>
  </Row>
);

const AboutSectionOne = () => (
  <Padded className="about-section">
    <Row>
      <Col xl={16} lg={16} md={24} sm={24} xs={24}>
        <h1>Open Source Adoption</h1>
        <p>
          Yoga already powers widely used open source frameworks. It enables
          these frameworks to offer a simple and intuitive layout API that
          allows for engineers to collaborate more easily across platforms. Yoga
          has unlocked exciting features such as calculating layouts off of the
          main thread to help ensure smooth UI performance.
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
        href="https://reactnative.dev"
        target="_blank"
        className="logo">
        <img src={ReactNativeLogo} />
        <h3>React Native</h3>
      </a>
      <a href="https://react-pdf.org/" target="_blank" className="logo">
        <img src={ReactPDFLogo} />
        <h3>React-PDF</h3>
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
          primary goals. For a layout engine to be able to power any range of
          applications, it needs to be fast and never stand in the way of a
          fluid user experience.
        </p>

        <h3>CROSS PLATFORM</h3>
        <p>
          Yoga is built with cross platform in mind. To ensure Yoga can be used
          anywhere, it was written in portable C/C++ and has a low number of
          dependencies and small binary size. This means Yoga can be used on iOS
          and Android, sharing knowledge, and potentially code, between
          platforms.
        </p>

        <h3>EASY TO LEARN</h3>
        <p>
          Yoga is easy to pick up and learn. The interactive documentation pages
          and a fully fledged layout editor makes it easy to play and learn all
          the features. If used with any of the major UI frameworks the layout
          editor even provides code generation.
        </p>
      </Col>
    </Row>
  </Padded>
);

export default () => (
  <div>
    <Page className="landing-page" title="A cross-platform layout engine">
      <HeroSection />
      <PlaygroundSection />
      <AboutSectionOne />
      <hr />
      <AboutSectionTwo />
      <Footer />
    </Page>
  </div>
);
