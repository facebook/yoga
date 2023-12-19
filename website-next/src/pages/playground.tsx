/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import Layout from '@theme/Layout';
import {useLocation} from '@docusaurus/router';
import lzString from 'lz-string';

import Playground from '../components/Playground';

import styles from './playground.module.css';
import useIsBrowser from '@docusaurus/useIsBrowser';

const defaultCode = `
<Layout config={{useWebDefaults: false}}>
  <Node style={{width: 350, height: 350, padding: 20}}>
    <Node style={{flex: 1}} />
  </Node>
</Layout>
`.trim();

export default function PlaygroundPage(): JSX.Element {
  const code = useCodeFromQueryParam();

  return (
    // @ts-ignore missing prop for `wrapperClassName`
    <Layout wrapperClassName={styles.bg} title="Playground">
      <Playground
        height="max(80vh, 600px)"
        code={code}
        autoFocus={true}
        key={String(useIsBrowser())}
      />
    </Layout>
  );
}

function useCodeFromQueryParam(): string {
  const location = useLocation();

  // We don't know the query param ahead of time when doing SSR, so just render
  // blank to avoid the appearance of code changing.
  if (!useIsBrowser()) {
    return '';
  }

  const params = new URLSearchParams(location.search);
  const codeParam = params.get('code');
  return codeParam
    ? lzString.decompressFromEncodedURIComponent(codeParam)
    : defaultCode;
}
