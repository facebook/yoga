/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
/* globals layoutTestUtils */

var textSizes = layoutTestUtils.textSizes;
var preDefinedTextSizes = layoutTestUtils.preDefinedTextSizes;

describe('Layout tests consts', function() {
  it('keeps browser text measurements in sync with predefined consts', function() {
    expect(preDefinedTextSizes).toEqual(
      textSizes,
      'Looks like browser has updated its text measurements functions. ' +
      'You need to update `preDefinedTextSizes` in Layout-test-utils.js'
    );
  });
});
