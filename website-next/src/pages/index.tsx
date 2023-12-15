/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

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
<Layout config={{useWebDefaults: false}}>
  <Node style={{width: 250, height: 475, padding: 10}}>
    <Node style={{flex: 1, rowGap: 10}}>
      <Node style={{height: 60}} />
      <Node style={{flex: 1, marginInline: 10}} />
      <Node style={{flex: 2, marginInline: 10}} />
      <Node
        style={{
          position: "absolute",
          width: "100%",
          bottom: 0,
          height: 64,
          flexDirection: "row",
          alignItems: "center",
          justifyContent: "space-around",
        }}
      >
        <Node style={{height: 40, width: 40}} />
        <Node style={{height: 40, width: 40}} />
        <Node style={{height: 40, width: 40}} />
        <Node style={{height: 40, width: 40}} />
      </Node>
    </Node>
  </Node>
</Layout>
`.trim();

function PlaygroundSection() {
  return (
    <main className={styles.playgroundSection}>
      <Playground height="600px" code={playgroundCode} autoFocus={true} />
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
