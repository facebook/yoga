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

function HomepageHeader() {
  return (
    <header className={clsx('hero', styles.heroBanner)}>
      <div className={clsx(['row', styles.heroRow])}>
        <div className="col col--6">
          <h1 className="hero__title">Flexible Layouts with Yoga</h1>
          <p className="hero__subtitle">
            Yoga is an embeddable and performant flexbox layout engine with
            bindings for multiple languages.
          </p>

          <Link
            className="button button--secondary button--lg"
            to="/docs/intro">
            Learn more
          </Link>
        </div>
        <div className={clsx(['col col--6', styles.blueprintColumn])}>
          <div className={clsx([styles.blueprint, styles.blueprintContainer])}>
            <div className={clsx([styles.blueprint, styles.blueprintAvatar])} />
            <div className={clsx([styles.blueprint, styles.blueprintTitle])} />
            <div
              className={clsx([styles.blueprint, styles.blueprintSubtitle])}
            />
            <div
              className={clsx([styles.blueprint, styles.blueprintContent])}
            />
          </div>
        </div>
      </div>
    </header>
  );
}

const LazyPlayground = React.lazy(() => import('../components/Playground'));

function ClientPlayground() {
  const fallback = <div className={styles.playgroundFallback} />;

  return (
    <BrowserOnly fallback={fallback}>
      {() => (
        <Suspense fallback={fallback}>
          <LazyPlayground />
        </Suspense>
      )}
    </BrowserOnly>
  );
}

export default function Home(): JSX.Element {
  return (
    <Layout title="Yoga Layout | A cross-platform layout engine">
      <HomepageHeader />
      <main>
        <ClientPlayground />
      </main>
    </Layout>
  );
}
