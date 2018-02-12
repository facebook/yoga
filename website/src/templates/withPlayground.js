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
import Page from '../components/Page';
import Playground from '../components/Playground';
import DocsSidebar from '../components/DocsSidebar';
import YogaEnumSelect from '../components/Playground/YogaEnumSelect';

export default ({pathContext}) => {
  return (
    <Page>
      <Playground
        selectedNodePath={[]}
        showGuides={false}
        renderSidebar={(layout, onChange) => (
          <DocsSidebar>
            <div dangerouslySetInnerHTML={{__html: pathContext.html}} />
            <YogaEnumSelect
              property="FLEX_DIRECTION"
              value={layout.flexDirection}
              onChange={e => onChange('flexDirection', e)}
            />
          </DocsSidebar>
        )}
      />
    </Page>
  );
};
