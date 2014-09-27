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
