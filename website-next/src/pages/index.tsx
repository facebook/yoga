/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import React from 'react';
import clsx from 'clsx';
import Link from '@docusaurus/Link';
import Layout from '@theme/Layout';

import styles from './index.module.css';

import YogaLogo from '../../static/img/logo.svg';
import Playground from '../components/Playground';

function HeroSection() {
  return (
    <header className={clsx('hero', styles.heroBanner)}>
      <div className={clsx('row', 'container', styles.heroRow)}>
        <div className="col col--6">
          <h1 className="hero__title">Yoga</h1>
          <p className="hero__subtitle">
            A portable layout engine targeting web standards
          </p>

          <Link className="button button--primary button--lg" to="/docs/intro">
            Learn more
          </Link>
        </div>
        <div className="col col--2">
          <YogaLogo className={styles.heroLogo} />
        </div>
      </div>
    </header>
  );
}

const playgroundCode = `
<YogaRoot useWebDefaults={false}>
  <Node
    style={{
      flexDirection: "row",
      flexWrap: "wrap",
      width: 350,
      height: 350,
      padding: 10,
      gap: 10,
   }}
  >
    <Node style={{width: 140, height: 150}} />
    <Node style={{width: 80, height: 60}} />
    <Node style={{flex: 1}} />
    <Node style={{width: 100, height: 150}} />
    <Node style={{flex: 1, padding: 5}}>
      <Node style={{width: "70%", flex: 1, justifyContent: "center"}}>
        <Node style={{width: 60, height: 60, marginLeft: 80}}>
          <Node style={{width: 30, height: 30}} />
        </Node>
        <Node style={{width: 60, height: 60, marginLeft: 10}} />
      </Node>
    </Node>
  </Node>
</YogaRoot>
`.trim();

function PlaygroundSection() {
  return (
    <main className={styles.playgroundSection}>
      <Playground height="580px" code={playgroundCode} autoFocus={true} />
    </main>
  );
}

export default function Home(): JSX.Element {
  return (
    <Layout>
      <HeroSection />
      <PlaygroundSection />
    </Layout>
  );
}
