/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import React, {Suspense} from 'react';
import clsx from 'clsx';
import Link from '@docusaurus/Link';
import Layout from '@theme/Layout';
import BrowserOnly from '@docusaurus/BrowserOnly';

import styles from './index.module.css';

function HeroSection() {
  return (
    <header className={clsx('hero', styles.heroBanner)}>
      <div className={clsx('row', 'container', styles.heroRow)}>
        <div className="col col--6">
          <h1 className="hero__title">Yoga Layout</h1>
          <p className="hero__subtitle">
            A portable and perfomant layout engine targeting web standards
          </p>

          <Link className="button button--primary button--lg" to="/docs/intro">
            Learn more
          </Link>
        </div>
        <div className={clsx(['col col--6', styles.blueprintColumn])}>
          <div className={clsx([styles.blueprint, styles.blueprintContainer])}>
            <div className={styles.blueprintHeader}>
              <div
                className={clsx([styles.blueprint, styles.blueprintAvatar])}
              />
              <div
                className={clsx([styles.blueprint, styles.blueprintTitle])}
              />
              <div
                className={clsx([styles.blueprint, styles.blueprintSubtitle])}
              />
            </div>
            <div
              className={clsx([styles.blueprint, styles.blueprintContent])}
            />
          </div>
        </div>
      </div>
    </header>
  );
}

const LazyPlayground = React.lazy(
  () => import('../components/Playground/Playground'),
);

// Docusaurus SSR does not correctly support top-level await
// 1. https://github.com/facebook/docusaurus/issues/7238
// 2. https://github.com/facebook/docusaurus/issues/9468
function BrowserOnlyPlayground() {
  return (
    <BrowserOnly fallback={null}>
      {() => (
        <Suspense fallback={null}>
          <LazyPlayground className={styles.playground} />
        </Suspense>
      )}
    </BrowserOnly>
  );
}

function PlaygroundSection() {
  return (
    <main className={styles.playgroundSection}>
      <div className="container">
        <BrowserOnlyPlayground />
      </div>
    </main>
  );
}

export default function Home(): JSX.Element {
  return (
    <Layout title="Yoga Layout | A cross-platform layout engine">
      <HeroSection />
      <PlaygroundSection />
    </Layout>
  );
}
