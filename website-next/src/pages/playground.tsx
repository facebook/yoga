/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import React from 'react';
import Layout from '@theme/Layout';
import {useLocation} from '@docusaurus/router';

import Playground from '../components/Playground';

import styles from './playground.module.css';

export default function PlaygroundPage(): JSX.Element {
  const params = new URLSearchParams(useLocation().search);
  const codeParam = params.get('code');
  const code = codeParam ? atob(codeParam) : undefined;

  return (
    // @ts-ignore missing prop for `wrapperClassName`
    <Layout wrapperClassName={styles.bg} title="Playground">
      <Playground height="max(80vh, 600px)" code={code} autoFocus={true} />
    </Layout>
  );
}
