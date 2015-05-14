/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
/* globals layoutTestUtils */

var testLayout = layoutTestUtils.testLayout;
var testFillNodes = layoutTestUtils.testFillNodes;
var testExtractNodes = layoutTestUtils.testExtractNodes;
var text = layoutTestUtils.text;
var texts = layoutTestUtils.texts;
var textSizes = layoutTestUtils.textSizes;

describe('Javascript Only', function() {
  it('should fill root node with layout, style, and children', function() {
    testFillNodes(
      {},
      {layout: {width: undefined, height: undefined, top: 0, left: 0, right: 0, bottom: 0}, style: {}, children: []}
    );
  });
  it('should fill root and child node with layout, style, and children', function() {
    testFillNodes(
      {children: [{}]},
      {layout: {width: undefined, height: undefined, top: 0, left: 0, right: 0, bottom: 0}, style: {}, children: [
        {layout: {width: undefined, height: undefined, top: 0, left: 0, right: 0, bottom: 0}, style: {}, children: []}
      ]}
    );
  });
  it('should pull out just the layout object from root', function() {
    testExtractNodes(
      {layout: {width: undefined, height: undefined, top: 0, left: 0}},
      {width: undefined, height: undefined, top: 0, left: 0}
    );
  });
  it('should pull out just the layout object from root and children', function() {
    testExtractNodes(
      {layout: {width: undefined, height: undefined, top: 0, left: 0}, children: [
        {layout: {width: undefined, height: undefined, top: 0, left: 0}}
      ]},
      {width: undefined, height: undefined, top: 0, left: 0, children: [
        {width: undefined, height: undefined, top: 0, left: 0}
      ]}
    );
  });
});


describe('Layout', function() {
  it('should layout a single node with width and height', function() {
    testLayout({
      style: {width: 100, height: 200}
    }, {
      width: 100, height: 200, top: 0, left: 0
    });
  });

  it('should layout node with children', function() {
    testLayout(
      {style: {width: 1000, height: 1000}, children: [
        {style: {width: 500, height: 500}},
        {style: {width: 250, height: 250}},
        {style: {width: 125, height: 125}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 500, height: 500, top: 0, left: 0},
        {width: 250, height: 250, top: 500, left: 0},
        {width: 125, height: 125, top: 750, left: 0}
      ]}
    );
  });

  it('should layout node with children in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse'}, children: [
        {style: {width: 500, height: 500}},
        {style: {width: 250, height: 250}},
        {style: {width: 125, height: 125}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 500, height: 500, top: 500, left: 0},
        {width: 250, height: 250, top: 250, left: 0},
        {width: 125, height: 125, top: 125, left: 0}
      ]}
    );
  });

  it('should layout node with nested children', function() {
    testLayout(
      {style: {width: 1000, height: 1000}, children: [
        {style: {width: 500, height: 500}},
        {style: {width: 500, height: 500}, children: [
          {style: {width: 250, height: 250}},
          {style: {width: 250, height: 250}}
        ]}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 500, height: 500, top: 0, left: 0},
        {width: 500, height: 500, top: 500, left: 0, children: [
          {width: 250, height: 250, top: 0, left: 0},
          {width: 250, height: 250, top: 250, left: 0}
        ]}
      ]}
    );
  });

  it('should layout node with nested children in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse'}, children: [
        {style: {width: 500, height: 500}},
        {style: {width: 500, height: 500, flexDirection: 'column-reverse'}, children: [
          {style: {width: 250, height: 250}},
          {style: {width: 250, height: 250}}
        ]}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 500, height: 500, top: 500, left: 0},
        {width: 500, height: 500, top: 0, left: 0, children: [
          {width: 250, height: 250, top: 250, left: 0},
          {width: 250, height: 250, top: 0, left: 0}
        ]}
      ]}
    );
  });

  it('should layout node with margin', function() {
    testLayout(
      {style: {width: 100, height: 200, margin: 10}},
      {width: 100, height: 200, top: 10, left: 10}
    );
  });

  it('should layout node with several children', function() {
    testLayout(
      {style: {width: 1000, height: 1000, margin: 10}, children: [
        {style: {width: 100, height: 100, margin: 50}},
        {style: {width: 100, height: 100, margin: 25}},
        {style: {width: 100, height: 100, margin: 10}}
      ]},
      {width: 1000, height: 1000, top: 10, left: 10, children: [
        {width: 100, height: 100, top: 50, left: 50},
        {width: 100, height: 100, top: 225, left: 25},
        {width: 100, height: 100, top: 360, left: 10}
      ]}
    );
  });

  it('should layout node with several children in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse', margin: 10}, children: [
        {style: {width: 100, height: 100, margin: 50}},
        {style: {width: 100, height: 100, margin: 25}},
        {style: {width: 100, height: 100, margin: 10}}
      ]},
      {width: 1000, height: 1000, top: 10, left: 10, children: [
        {width: 100, height: 100, top: 850, left: 50},
        {width: 100, height: 100, top: 675, left: 25},
        {width: 100, height: 100, top: 540, left: 10}
      ]}
    );
  });

  it('should layout rtl with reverse correctly', function() {
    testLayout(
      {style: {width: 1000, height: 1000, direction: 'rtl', flexDirection: 'row-reverse'}, children: [
        {style: {width: 100, height: 200}},
        {style: {width: 300, height: 150}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 200, top: 0, left: 0},
        {width: 300, height: 150, top: 0, left: 100}
      ]}
    );
  });

  it('should layout node with row flex direction', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'row'}, children: [
        {style: {width: 100, height: 200}},
        {style: {width: 300, height: 150}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 200, top: 0, left: 0},
        {width: 300, height: 150, top: 0, left: 100}
      ]}
    );
  });

  it('should layout node with row flex direction in rtl', function() {
    testLayout(
      {style: {width: 1000, height: 1000, direction: 'rtl', flexDirection: 'row'}, children: [
        {style: {width: 100, height: 200}},
        {style: {width: 300, height: 150}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 200, top: 0, left: 900},
        {width: 300, height: 150, top: 0, left: 600}
      ]}
    );
  });

  it('should layout node based on children main dimensions', function() {
    testLayout(
      {style: {width: 300}, children: [
        {style: {width: 100, height: 200}},
        {style: {width: 300, height: 150}}
      ]},
      {width: 300, height: 350, top: 0, left: 0, children: [
        {width: 100, height: 200, top: 0, left: 0},
        {width: 300, height: 150, top: 200, left: 0}
      ]}
    );
  });

  it('should layout node based on children main dimensions in reverse', function() {
    testLayout(
      {style: {width: 300, flexDirection: 'column-reverse'}, children: [
        {style: {width: 100, height: 200}},
        {style: {width: 300, height: 150}}
      ]},
      {width: 300, height: 350, top: 0, left: 0, children: [
        {width: 100, height: 200, top: 150, left: 0},
        {width: 300, height: 150, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with just flex', function() {
    testLayout(
      {style: {width: 1000, height: 1000}, children: [
        {style: {width: 100, height: 200}},
        {style: {width: 100, flex: 1}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 200, top: 0, left: 0},
        {width: 100, height: 800, top: 200, left: 0}
      ]}
    );
  });

  it('should layout node with just flex in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse'}, children: [
        {style: {width: 100, height: 200}},
        {style: {width: 100, flex: 1}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 200, top: 800, left: 0},
        {width: 100, height: 800, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with flex recursively', function() {
    testLayout(
      {style: {width: 1000, height: 1000}, children: [
        {style: {width: 1000, flex: 1}, children: [
          {style: {width: 1000, flex: 1}, children: [
            {style: {width: 1000, flex: 1}}
          ]}
        ]}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 1000, height: 1000, top: 0, left: 0, children: [
          {width: 1000, height: 1000, top: 0, left: 0, children: [
            {width: 1000, height: 1000, top: 0, left: 0}
          ]}
        ]}
      ]}
    );
  });

  it('should layout node with flex recursively in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse'}, children: [
        {style: {width: 1000, flex: 1, flexDirection: 'column-reverse'}, children: [
          {style: {width: 1000, flex: 1, flexDirection: 'column-reverse'}, children: [
            {style: {width: 1000, flex: 1, flexDirection: 'column-reverse'}}
          ]}
        ]}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 1000, height: 1000, top: 0, left: 0, children: [
          {width: 1000, height: 1000, top: 0, left: 0, children: [
            {width: 1000, height: 1000, top: 0, left: 0}
          ]}
        ]}
      ]}
    );
  });

  it('should layout node with targeted margin', function() {
    testLayout(
      {style: {width: 1000, height: 1000, marginTop: 10, marginLeft: 5}, children: [
        {style: {width: 100, height: 100, marginTop: 50, marginLeft: 15, marginBottom: 20}},
        {style: {width: 100, height: 100, marginLeft: 30}}
      ]},
      {width: 1000, height: 1000, top: 10, left: 5, children: [
        {width: 100, height: 100, top: 50, left: 15},
        {width: 100, height: 100, top: 170, left: 30}
      ]}
    );
  });

  it('should layout node with targeted margin in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse', marginTop: 10, marginLeft: 5}, children: [
        {style: {width: 100, height: 100, marginTop: 50, marginLeft: 15, marginBottom: 20}},
        {style: {width: 100, height: 100, marginLeft: 30}}
      ]},
      {width: 1000, height: 1000, top: 10, left: 5, children: [
        {width: 100, height: 100, top: 880, left: 15},
        {width: 100, height: 100, top: 730, left: 30}
      ]}
    );
  });

  it('should layout node with justifyContent: flex-start', function() {
    testLayout(
      {style: {width: 1000, height: 1000, justifyContent: 'flex-start'}, children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 100, top: 0, left: 0},
        {width: 100, height: 100, top: 100, left: 0}
      ]}
    );
  });

  it('should layout node with justifyContent: flex-start in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse', justifyContent: 'flex-start'}, children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 100, top: 900, left: 0},
        {width: 100, height: 100, top: 800, left: 0}
      ]}
    );
  });

  it('should layout node with justifyContent: flex-end', function() {
    testLayout(
      {style: {width: 1000, height: 1000, justifyContent: 'flex-end'}, children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 100, top: 800, left: 0},
        {width: 100, height: 100, top: 900, left: 0}
      ]}
    );
  });

  it('should layout node with justifyContent: flex-end in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse', justifyContent: 'flex-end'}, children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 100, top: 100, left: 0},
        {width: 100, height: 100, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with justifyContent: space-between', function() {
    testLayout(
      {style: {width: 1000, height: 1000, justifyContent: 'space-between'}, children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 100, top: 0, left: 0},
        {width: 100, height: 100, top: 900, left: 0}
      ]}
    );
  });

  it('should layout node with justifyContent: space-between in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse', justifyContent: 'space-between'}, children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 100, top: 900, left: 0},
        {width: 100, height: 100, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with justifyContent: space-around', function() {
    testLayout(
      {style: {width: 1000, height: 1000, justifyContent: 'space-around'}, children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 100, top: 200, left: 0},
        {width: 100, height: 100, top: 700, left: 0}
      ]}
    );
  });

  it('should layout node with justifyContent: space-around in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse', justifyContent: 'space-around'}, children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 100, top: 700, left: 0},
        {width: 100, height: 100, top: 200, left: 0}
      ]}
    );
  });

  it('should layout node with justifyContent: center', function() {
    testLayout(
      {style: {width: 1000, height: 1000, justifyContent: 'center'}, children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 100, top: 400, left: 0},
        {width: 100, height: 100, top: 500, left: 0}
      ]}
    );
  });

  it('should layout node with justifyContent: center in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse', justifyContent: 'center'}, children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 100, top: 500, left: 0},
        {width: 100, height: 100, top: 400, left: 0}
      ]}
    );
  });

  it('should layout node with flex override height', function() {
    testLayout(
      {style: {width: 1000, height: 1000}, children: [
        {style: {width: 100, height: 100, flex: 1}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 100, height: 1000, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with alignItems: flex-start', function() {
    testLayout(
      {style: {width: 1000, height: 1000, alignItems: 'flex-start'}, children: [
        {style: {width: 200, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 200, height: 100, top: 0, left: 0},
        {width: 100, height: 100, top: 100, left: 0}
      ]}
    );
  });

  it('should layout node with alignItems: flex-start in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse', alignItems: 'flex-start'}, children: [
        {style: {width: 200, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 200, height: 100, top: 900, left: 0},
        {width: 100, height: 100, top: 800, left: 0}
      ]}
    );
  });

  it('should layout node with alignItems: center', function() {
    testLayout(
      {style: {width: 1000, height: 1000, alignItems: 'center'}, children: [
        {style: {width: 200, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 200, height: 100, top: 0, left: 400},
        {width: 100, height: 100, top: 100, left: 450}
      ]}
    );
  });

  it('should layout node with alignItems: center in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse', alignItems: 'center'}, children: [
        {style: {width: 200, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 200, height: 100, top: 900, left: 400},
        {width: 100, height: 100, top: 800, left: 450}
      ]}
    );
  });

  it('should layout node with alignItems: flex-end', function() {
    testLayout(
      {style: {width: 1000, height: 1000, alignItems: 'flex-end'}, children: [
        {style: {width: 200, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 200, height: 100, top: 0, left: 800},
        {width: 100, height: 100, top: 100, left: 900}
      ]}
    );
  });

  it('should layout node with alignItems: flex-end in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse', alignItems: 'flex-end'}, children: [
        {style: {width: 200, height: 100}},
        {style: {width: 100, height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 200, height: 100, top: 900, left: 800},
        {width: 100, height: 100, top: 800, left: 900}
      ]}
    );
  });

  it('should layout node with alignSelf overrides alignItems', function() {
    testLayout(
      {style: {width: 1000, height: 1000, alignItems: 'flex-end'}, children: [
        {style: {width: 200, height: 100}},
        {style: {width: 100, height: 100, alignSelf: 'center'}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 200, height: 100, top: 0, left: 800},
        {width: 100, height: 100, top: 100, left: 450}
      ]}
    );
  });

  it('should layout node with alignSelf overrides alignItems in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse', alignItems: 'flex-end'}, children: [
        {style: {width: 200, height: 100}},
        {style: {width: 100, height: 100, alignSelf: 'center'}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 200, height: 100, top: 900, left: 800},
        {width: 100, height: 100, top: 800, left: 450}
      ]}
    );
  });

  it('should layout node with alignItem: stretch', function() {
    testLayout(
      {style: {width: 1000, height: 1000, alignItems: 'stretch'}, children: [
        {style: {height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 1000, height: 100, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with alignItem: stretch in reverse', function() {
    testLayout(
      {style: {width: 1000, height: 1000, flexDirection: 'column-reverse', alignItems: 'stretch'}, children: [
        {style: {height: 100}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 1000, height: 100, top: 900, left: 0}
      ]}
    );
  });

  it('should layout empty node', function() {
    testLayout(
      {style: {}, children: [
        {style: {}}
      ]},
      {width: 0, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should layout empty node in reverse', function() {
    testLayout(
      {style: {flexDirection: 'column-reverse'}, children: [
        {style: {}}
      ]},
      {width: 0, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should layout child with margin', function() {
    testLayout(
      {style: {}, children: [
        {style: {margin: 5}}
      ]},
      {width: 10, height: 10, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 5, left: 5}
      ]}
    );
  });

  it('should layout child with margin in reverse', function() {
    testLayout(
      {style: {flexDirection: 'column-reverse'}, children: [
        {style: {margin: 5}}
      ]},
      {width: 10, height: 10, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 5, left: 5}
      ]}
    );
  });

  it('should not shrink children if not enough space', function() {
    testLayout(
      {style: {height: 100}, children: [
        {style: {height: 100}},
        {style: {height: 200}}
      ]},
      {width: 0, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 100, top: 0, left: 0},
        {width: 0, height: 200, top: 100, left: 0}
      ]}
    );
  });

  it('should not shrink children if not enough space in reverse', function() {
    testLayout(
      {style: {height: 100, flexDirection: 'column-reverse'}, children: [
        {style: {height: 100}},
        {style: {height: 200}}
      ]},
      {width: 0, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 100, top: 0, left: 0},
        {width: 0, height: 200, top: -200, left: 0}
      ]}
    );
  });

  it('should layout for center', function() {
    testLayout(
      {style: {justifyContent: 'center'}},
      {width: 0, height: 0, top: 0, left: 0}
    );
  });

  it('should layout flex-end taking into account margin', function() {
    testLayout(
      {style: {height: 100, justifyContent: 'flex-end'}, children: [
        {style: {marginTop: 10}}
      ]},
      {width: 0, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 100, left: 0}
      ]}
    );
  });

  it('should layout flex-end taking into account margin in reverse', function() {
    testLayout(
      {style: {height: 100, flexDirection: 'column-reverse', justifyContent: 'flex-end'}, children: [
        {style: {marginTop: 10}}
      ]},
      {width: 0, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 10, left: 0}
      ]}
    );
  });

  it('should layout alignItems with margin', function() {
    testLayout(
      {style: {}, children: [
        {style: {alignItems: 'flex-end'}, children: [
          {style: {margin: 10}},
          {style: {height: 100}}
        ]}
      ]},
      {width: 20, height: 120, top: 0, left: 0, children: [
        {width: 20, height: 120, top: 0, left: 0, children: [
          {width: 0, height: 0, top: 10, left: 10},
          {width: 0, height: 100, top: 20, left: 20}
        ]}
      ]}
    );
  });

  it('should layout alignItems with margin in reverse', function() {
    testLayout(
      {style: {}, children: [
        {style: {flexDirection: 'column-reverse', alignItems: 'flex-end'}, children: [
          {style: {margin: 10}},
          {style: {height: 100}}
        ]}
      ]},
      {width: 20, height: 120, top: 0, left: 0, children: [
        {width: 20, height: 120, top: 0, left: 0, children: [
          {width: 0, height: 0, top: 110, left: 10},
          {width: 0, height: 100, top: 0, left: 20}
        ]}
      ]}
    );
  });

  it('should layout flex inside of an empty element', function() {
    testLayout(
      {style: {}, children: [
        {style: {flex: 1}}
      ]},
      {width: 0, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should layout alignItems stretch and margin', function() {
    testLayout(
      {style: {alignItems: 'stretch'}, children: [
        {style: {marginLeft: 10}}
      ]},
      {width: 10, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 10}
      ]}
    );
  });

  it('should layout alignItems stretch and margin in reverse', function() {
    testLayout(
      {style: {flexDirection: 'column-reverse', alignItems: 'stretch'}, children: [
        {style: {marginLeft: 10}}
      ]},
      {width: 10, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 10}
      ]}
    );
  });

  it('should layout node with padding', function() {
    testLayout(
      {style: {padding: 5}},
      {width: 10, height: 10, top: 0, left: 0}
    );
  });

  it('should layout node with padding and a child', function() {
    testLayout(
      {style: {padding: 5}, children: [
        {style: {}}
      ]},
      {width: 10, height: 10, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 5, left: 5}
      ]}
    );
  });

  it('should layout node with padding and a child with margin', function() {
    testLayout(
      {style: {padding: 5}, children: [
        {style: {margin: 5}}
      ]},
      {width: 20, height: 20, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 10, left: 10}
      ]}
    );
  });

  it('should layout node with padding and stretch', function() {
    testLayout(
      {style: {}, children: [
        {style: {padding: 10, alignSelf: 'stretch'}}
      ]},
      {width: 20, height: 20, top: 0, left: 0, children: [
        {width: 20, height: 20, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with inner & outer padding and stretch', function() {
    testLayout(
      {style: {padding: 50}, children: [
        {style: {padding: 10, alignSelf: 'stretch'}}
      ]},
      {width: 120, height: 120, top: 0, left: 0, children: [
        {width: 20, height: 20, top: 50, left: 50}
      ]}
    );
  });

  it('should layout node with stretch and child with margin', function() {
    testLayout(
      {style: {}, children: [
        {style: {alignSelf: 'stretch'}, children: [
          {style: {margin: 16}}
        ]}
      ]},
      {width: 32, height: 32, top: 0, left: 0, children: [
        {width: 32, height: 32, top: 0, left: 0, children: [
          {width: 0, height: 0, top: 16, left: 16}
        ]}
      ]}
    );
  });

  it('should layout node with top and left', function() {
    testLayout(
      {style: {top: 5, left: 5}},
      {width: 0, height: 0, top: 5, left: 5}
    );
  });

  it('should layout node with height, padding and space-around', function() {
    testLayout(
      {style: {height: 10, paddingTop: 5, justifyContent: 'space-around'}, children: [
        {style: {}}
      ]},
      {width: 0, height: 10, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 7.5, left: 0}
      ]}
    );
  });

  it('should layout node with bottom', function() {
    testLayout(
      {style: {bottom: 5}},
      {width: 0, height: 0, top: -5, left: 0}
    );
  });

  it('should layout node with both top and bottom', function() {
    testLayout(
      {style: {top: 10, bottom: 5}},
      {width: 0, height: 0, top: 10, left: 0}
    );
  });

  it('should layout node with position: absolute', function() {
    testLayout(
      {style: {width: 500, flexDirection: 'row'}, children: [
        {style: {flex: 1}},
        {style: {position: 'absolute', width: 50}},
        {style: {flex: 1}}
      ]},
      {width: 500, height: 0, top: 0, left: 0, children: [
        {width: 250, height: 0, top: 0, left: 0},
        {width: 50, height: 0, top: 0, left: 250},
        {width: 250, height: 0, top: 0, left: 250}
      ]}
    );
  });

  it('should layout node with child with position: absolute and margin', function() {
    testLayout(
      {style: {}, children: [
        {style: {marginRight: 15, position: 'absolute'}}
      ]},
      {width: 0, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with position: absolute, padding and alignSelf: center', function() {
    testLayout(
      {style: {}, children: [
        {style: {paddingRight: 12, alignSelf: 'center', position: 'absolute'}}
      ]},
      {width: 0, height: 0, top: 0, left: 0, children: [
        {width: 12, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should work with height smaller than paddingBottom', function() {
    testLayout(
      {style: {height: 5, paddingBottom: 20}},
      {width: 0, height: 20, top: 0, left: 0}
    );
  });

  it('should work with width smaller than paddingLeft', function() {
    testLayout(
      {style: {width: 5, paddingLeft: 20}},
      {width: 20, height: 0, top: 0, left: 0}
    );
  });

  it('should layout node with specified width and stretch', function() {
    testLayout(
      {style: {}, children: [{
        style: {}, children: [
          {style: {width: 400}}
        ]},
        {style: {width: 200, alignSelf: 'stretch'}}
      ]},
      {width: 400, height: 0, top: 0, left: 0, children: [
        {width: 400, height: 0, top: 0, left: 0, children: [
          {width: 400, height: 0, top: 0, left: 0}
        ]},
        {width: 200, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with padding and child with position absolute', function() {
    testLayout(
      {style: {padding: 5}, children: [
        {style: {position: 'absolute'}}
      ]},
      {width: 10, height: 10, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 5, left: 5}
      ]}
    );
  });

  it('should layout node with position absolute, top and left', function() {
    testLayout(
      {style: {}, children: [
        {style: {height: 100}},
        {style: {position: 'absolute', top: 10, left: 10}}
      ]},
      {width: 0, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 100, top: 0, left: 0},
        {width: 0, height: 0, top: 10, left: 10}
      ]}
    );
  });

  it('should layout node with padding and child position absolute, left', function() {
    testLayout(
      {style: {padding: 20}, children: [
        {style: {left: 5, position: 'absolute'}}
      ]},
      {width: 40, height: 40, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 20, left: 5}
      ]}
    );
  });

  it('should layout node with position: absolute, top and marginTop', function() {
    testLayout(
      {style: {}, children: [
        {style: {top: 5, marginTop: 5, position: 'absolute'}}
      ]},
      {width: 0, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 10, left: 0}
      ]}
    );
  });

  it('should layout node with position: absolute, left and marginLeft', function() {
    testLayout(
      {style: {}, children: [
        {style: {left: 5, marginLeft: 5, position: 'absolute'}}
      ]},
      {width: 0, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 10}
      ]}
    );
  });

  it('should layout node with space-around and child position absolute', function() {
    testLayout(
      {style: {height: 200, justifyContent: 'space-around'}, children: [
        {style: {position: 'absolute'}},
        {style: {}}
      ]},
      {width: 0, height: 200, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 100, left: 0},
        {width: 0, height: 0, top: 100, left: 0}
      ]}
    );
  });

  it('should layout node with space-around and child position absolute in reverse', function() {
    testLayout(
      {style: {height: 200, flexDirection: 'column-reverse', justifyContent: 'space-around'}, children: [
        {style: {position: 'absolute'}},
        {style: {}}
      ]},
      {width: 0, height: 200, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 100, left: 0},
        {width: 0, height: 0, top: 100, left: 0}
      ]}
    );
  });

  it('should layout node with flex and main margin', function() {
    testLayout(
      {style: {width: 700, flexDirection: 'row'}, children: [
        {style: {marginLeft: 5, flex: 1}}
      ]},
      {width: 700, height: 0, top: 0, left: 0, children: [
        {width: 695, height: 0, top: 0, left: 5}
      ]}
    );
  });

  it('should layout node with flex and main margin in rtl', function() {
    testLayout(
      {style: {width: 700, direction: 'rtl', flexDirection: 'row'}, children: [
        {style: {marginRight: 5, flex: 1}}
      ]},
      {width: 700, height: 0, top: 0, left: 0, children: [
        {width: 695, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with multiple flex and padding', function() {
    testLayout(
      {style: {width: 700, flexDirection: 'row'}, children: [
        {style: {flex: 1}},
        {style: {paddingRight: 5, flex: 1}}
      ]},
      {width: 700, height: 0, top: 0, left: 0, children: [
        {width: 347.5, height: 0, top: 0, left: 0},
        {width: 352.5, height: 0, top: 0, left: 347.5}
      ]}
    );
  });

  it('should layout node with multiple flex and padding in rtl', function() {
    testLayout(
      {style: {width: 700, direction: 'rtl', flexDirection: 'row'}, children: [
        {style: {flex: 1}},
        {style: {paddingLeft: 5, flex: 1}}
      ]},
      {width: 700, height: 0, top: 0, left: 0, children: [
        {width: 347.5, height: 0, top: 0, left: 352.5},
        {width: 352.5, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with multiple flex and margin', function() {
    testLayout(
      {style: {width: 700, flexDirection: 'row'}, children: [
        {style: {flex: 1}},
        {style: {marginLeft: 5, flex: 1}}
      ]},
      {width: 700, height: 0, top: 0, left: 0, children: [
        {width: 347.5, height: 0, top: 0, left: 0},
        {width: 347.5, height: 0, top: 0, left: 352.5}
      ]}
    );
  });

  it('should layout node with multiple flex and margin in rtl', function() {
    testLayout(
      {style: {width: 700, direction: 'rtl', flexDirection: 'row'}, children: [
        {style: {flex: 1}},
        {style: {marginRight: 5, flex: 1}}
      ]},
      {width: 700, height: 0, top: 0, left: 0, children: [
        {width: 347.5, height: 0, top: 0, left: 352.5},
        {width: 347.5, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with flex and overflow', function() {
    testLayout(
      {style: {height: 300}, children: [
        {style: {height: 600}},
        {style: {flex: 1}}
      ]},
      {width: 0, height: 300, top: 0, left: 0, children: [
        {width: 0, height: 600, top: 0, left: 0},
        {width: 0, height: 0, top: 600, left: 0}
      ]}
    );
  });

  it('should layout node with flex and position absolute', function() {
    testLayout(
      {style: {width: 600, flexDirection: 'row'}, children: [
        {style: {flex: 1, position: 'absolute'}}
      ]},
      {width: 600, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with flex and position absolute in rtl', function() {
    testLayout(
      {style: {width: 600, direction: 'rtl', flexDirection: 'row'}, children: [
        {style: {flex: 1, position: 'absolute'}}
      ]},
      {width: 600, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 600}
      ]}
    );
  });

  it('should layout node with double flex and position absolute', function() {
    testLayout(
      {style: {height: 500}, children: [
        {style: {flex: 1}},
        {style: {flex: 1, position: 'absolute'}}
      ]},
      {width: 0, height: 500, top: 0, left: 0, children: [
        {width: 0, height: 500, top: 0, left: 0},
        {width: 0, height: 0, top: 500, left: 0}
      ]}
    );
  });

  it('should layout node with borderWidth', function() {
    testLayout(
      {style: {borderWidth: 5}},
      {width: 10, height: 10, top: 0, left: 0}
    );
  });

  it('should layout node with borderWidth and position: absolute, top', function() {
    testLayout(
      {style: {borderTopWidth: 1}, children: [
        {style: {top: -1, position: 'absolute'}}
      ]},
      {width: 0, height: 1, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with borderWidth and position: absolute, top. cross axis', function() {
    testLayout(
      {style: {borderWidth: 1}, children: [
        {style: {left: 5, position: 'absolute'}}
      ]},
      {width: 2, height: 2, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 1, left: 6}
      ]}
    );
  });

  it('should correctly take into account min padding for stretch', function() {
    testLayout(
      {style: {width: 50}, children: [
        {style: {marginLeft: 20, padding: 20, alignSelf: 'stretch'}}
      ]},
      {width: 50, height: 40, top: 0, left: 0, children: [
        {width: 40, height: 40, top: 0, left: 20}
      ]}
    );
  });

  it('should layout node with negative width', function() {
    testLayout(
      {style: {width: -31}, children: [
        {style: {borderRightWidth: 5}}
      ]},
      {width: 5, height: 0, top: 0, left: 0, children: [
        {width: 5, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should handle negative margin and min padding correctly', function() {
    testLayout(
      {style: {borderRightWidth: 1, flexDirection: 'row'}, children: [
        {style: {marginRight: -8}}
      ]},
      {width: 1, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should handle negative margin and min padding correctly in rtl', function() {
    testLayout(
      {style: {borderLeftWidth: 1, direction: 'rtl', flexDirection: 'row'}, children: [
        {style: {marginLeft: -8}}
      ]},
      {width: 1, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 1}
      ]}
    );
  });

  it('should layout node with just text', function() {
    testLayout(
      {style: {measure: text(texts.small)}},
      {width: textSizes.smallWidth, height: textSizes.smallHeight, top: 0, left: 0}
    );
  });

  it('should layout node with text and width', function() {
    testLayout(
      {style: {measure: text(texts.small), width: 10}},
      {width: 10, height: textSizes.smallHeight, top: 0, left: 0}
    );
  });

  it('should layout node with text, padding and margin', function() {
    testLayout(
      {style: {measure: text(texts.big)}},
      {width: textSizes.bigWidth, height: textSizes.smallHeight, top: 0, left: 0}
    );
  });

  it('should layout node with nested alignSelf: stretch', function() {
    testLayout(
      {style: {width: 300}, children: [
        {style: {alignSelf: 'stretch'}, children: [
          {style: {alignSelf: 'stretch'}}
        ]}
      ]},
      {width: 300, height: 0, top: 0, left: 0, children: [
        {width: 300, height: 0, top: 0, left: 0, children: [
          {width: 300, height: 0, top: 0, left: 0}
        ]}
      ]}
    );
  });

  it('should layout node with text and flex', function() {
    testLayout(
      {style: {}, children: [
        {style: {width: 500, flexDirection: 'row'}, children: [
          {style: {flex: 1, measure: text(texts.big)}}
        ]}
      ]},
      {width: 500, height: textSizes.smallHeight, top: 0, left: 0, children: [
        {width: 500, height: textSizes.smallHeight, top: 0, left: 0, children: [
          {width: 500, height: textSizes.smallHeight, top: 0, left: 0}
        ]}
      ]}
    );
  });

  it('should layout node with text and flex in rtl', function() {
    testLayout(
      {style: {}, children: [
        {style: {width: 500, direction: 'rtl', flexDirection: 'row'}, children: [
          {style: {flex: 1, measure: text(texts.big)}}
        ]}
      ]},
      {width: 500, height: textSizes.smallHeight, top: 0, left: 0, children: [
        {width: 500, height: textSizes.smallHeight, top: 0, left: 0, children: [
          {width: 500, height: textSizes.smallHeight, top: 0, left: 0}
        ]}
      ]}
    );
  });

  it('should layout node with text and stretch', function() {
    testLayout(
      {style: {width: 130}, children: [
        {style: {alignSelf: 'stretch', alignItems: 'stretch'}, children: [
          {style: {measure: text(texts.big)}}
        ]}
      ]},
      {width: 130, height: textSizes.bigHeight, top: 0, left: 0, children: [
        {width: 130, height: textSizes.bigHeight, top: 0, left: 0, children: [
          {width: 130, height: textSizes.bigHeight, top: 0, left: 0}
        ]}
      ]}
    );
  });

  it('should layout node with text stretch and width', function() {
    testLayout(
      {style: {width: 200}, children: [
        {style: {alignSelf: 'stretch', alignItems: 'stretch'}, children: [
          {style: {width: 130, measure: text(texts.big)}}
        ]}
      ]},
      {width: 200, height: textSizes.bigHeight, top: 0, left: 0, children: [
        {width: 200, height: textSizes.bigHeight, top: 0, left: 0, children: [
          {width: 130, height: textSizes.bigHeight, top: 0, left: 0}
        ]}
      ]}
    );
  });

  it('should layout node with text bounded by parent', function() {
    testLayout(
      {style: {width: 100, alignSelf: 'flex-start'}, children: [
        {style: {measure: text(texts.big), alignSelf: 'flex-start'}}
      ]},
      {width: 100, height: textSizes.bigHeight, top: 0, left: 0, children: [
        {width: textSizes.bigMinWidth, height: textSizes.bigHeight, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with text bounded by grand-parent', function() {
    testLayout(
      {style: {width: 100, padding: 10, alignSelf: 'flex-start'}, children: [
        {style: {margin: 10, alignSelf: 'flex-start'}, children: [
          {style: {measure: text(texts.big)}}
        ]}
      ]},
      {width: 100, height: 40 + textSizes.bigHeight, top: 0, left: 0, children: [
        {width: textSizes.bigMinWidth, height: textSizes.bigHeight, top: 20, left: 20, children: [
          {width: textSizes.bigMinWidth, height: textSizes.bigHeight, top: 0, left: 0}
        ]}
      ]}
    );
  });

  it('should layout space-between when remaining space is negative', function() {
    testLayout(
      {style: {height: 100, justifyContent: 'space-between'}, children: [
        {style: {height: 900}},
        {style: {}}
      ]},
      {width: 0, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 900, top: 0, left: 0},
        {width: 0, height: 0, top: 900, left: 0}
      ]}
    );
  });

  it('should layout space-between when remaining space is negative in reverse', function() {
    testLayout(
      {style: {height: 100, flexDirection: 'column-reverse', justifyContent: 'space-between'}, children: [
        {style: {height: 900}},
        {style: {}}
      ]},
      {width: 0, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 900, top: -800, left: 0},
        {width: 0, height: 0, top: -800, left: 0}
      ]}
    );
  });

  it('should layout flex-end when remaining space is negative', function() {
    testLayout(
      {style: {width: 200, flexDirection: 'row', justifyContent: 'flex-end'}, children: [
        {style: {width: 900}}
      ]},
      {width: 200, height: 0, top: 0, left: 0, children: [
        {width: 900, height: 0, top: 0, left: -700}
      ]}
    );
  });

  it('should layout flex-end when remaining space is negative in rtl', function() {
    testLayout(
      {style: {width: 200, direction: 'rtl', flexDirection: 'row', justifyContent: 'flex-end'}, children: [
        {style: {width: 900}}
      ]},
      {width: 200, height: 0, top: 0, left: 0, children: [
        {width: 900, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should layout text with flexDirection row', function() {
    testLayout(
      {style: {}, children: [
        {style: {width: 200, flexDirection: 'row'}, children: [
          {style: {margin: 20, measure: text(texts.big)}}
        ]}
      ]},
      {width: 200, height: textSizes.smallHeight + 40, top: 0, left: 0, children: [
        {width: 200, height: textSizes.smallHeight + 40, top: 0, left: 0, children: [
          {width: textSizes.bigWidth, height: textSizes.smallHeight, top: 20, left: 20}
        ]}
      ]}
    );
  });

  it('should layout text with flexDirection row in rtl', function() {
    testLayout(
      {style: { direction: 'rtl' }, children: [
        {style: {width: 200, flexDirection: 'row'}, children: [
          {style: {margin: 20, measure: text(texts.big)}}
        ]}
      ]},
      {width: 200, height: textSizes.smallHeight + 40, top: 0, left: 0, children: [
        {width: 200, height: textSizes.smallHeight + 40, top: 0, left: 0, children: [
          {width: textSizes.bigWidth, height: textSizes.smallHeight, top: 20, left: 7.578125}
        ]}
      ]}
    );
  });

  it('should layout with text and margin', function() {
    testLayout(
      {style: {}, children: [
        {style: {width: 200}, children: [
          {style: {margin: 20, measure: text(texts.big)}}
        ]}
      ]},
      {width: 200, height: textSizes.bigHeight + 40, top: 0, left: 0, children: [
        {width: 200, height: textSizes.bigHeight + 40, top: 0, left: 0, children: [
          {width: 160, height: textSizes.bigHeight, top: 20, left: 20}
        ]}
      ]}
    );
  });

  it('should layout with position absolute, top, left, bottom, right', function() {
    testLayout(
      {style: {width: 100, height: 100}, children: [
        {style: {position: 'absolute', top: 0, left: 0, bottom: 0, right: 0}}
      ]},
      {width: 100, height: 100, top: 0, left: 0, children: [
        {width: 100, height: 100, top: 0, left: 0}
      ]}
    );
  });

  it('should layout with arbitrary flex', function() {
    testLayout(
      {style: {width: 100, height: 100, alignSelf: 'flex-start'}, children: [
        {style: {flex: 2.5, alignSelf: 'flex-start'}},
        {style: {flex: 7.5, alignSelf: 'flex-start'}}
      ]},
      {width: 100, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 25, top: 0, left: 0},
        {width: 0, height: 75, top: 25, left: 0}
      ]}
    );
  });

  it('should layout with arbitrary flex in reverse', function() {
    testLayout(
      {style: {width: 100, height: 100, flexDirection: 'column-reverse', alignSelf: 'flex-start'}, children: [
        {style: {flex: 2.5, alignSelf: 'flex-start'}},
        {style: {flex: 7.5, alignSelf: 'flex-start'}}
      ]},
      {width: 100, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 25, top: 75, left: 0},
        {width: 0, height: 75, top: 0, left: 0}
      ]}
    );
  });

  it('should layout with negative flex in reverse', function() {
    testLayout(
      {style: {width: 100, height: 100, flexDirection: 'column-reverse', alignSelf: 'flex-start'}, children: [
        {style: {flex: -2.5, alignSelf: 'flex-start'}},
        {style: {flex: 0, alignSelf: 'flex-start'}}
      ]},
      {width: 100, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 100, left: 0},
        {width: 0, height: 0, top: 100, left: 0}
      ]}
    );
  });

  it('should layout with position: absolute and another sibling', function() {
    testLayout(
      {style: {}, children: [
        {style: {width: 50, height: 100}},
        {style: {position: 'absolute', left: 0, right: 0}}
      ]},
      {width: 50, height: 100, top: 0, left: 0, children: [
        {width: 50, height: 100, top: 0, left: 0},
        {width: 50, height: 0, top: 100, left: 0}
      ]}
    );
  });

  it('should calculate height properly with position: absolute top and bottom', function() {
    testLayout(
      {style: {height: 100}, children: [
        {style: {position: 'absolute', top: 0, bottom: 20}}
      ]},
      {width: 0, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 80, top: 0, left: 0}
      ]}
    );
  });

  it('should layout with complicated position: absolute and justifyContent: center combo', function() {
    testLayout(
      {style: {width: 200, height: 200}, children: [
        {style: {position: 'absolute', justifyContent: 'center', top: 0, left: 0, right: 0, bottom: 0}, children: [
          {style: {width: 100, height: 100}}
        ]}
      ]},
      {width: 200, height: 200, top: 0, left: 0, children: [
        {width: 200, height: 200, top: 0, left: 0, children: [
          {width: 100, height: 100, top: 50, left: 0}
        ]}
      ]}
    );
  });

  it('should calculate top properly with position: absolute bottom', function() {
    testLayout(
      {style: {height: 100}, children: [
        {style: {position: 'absolute', bottom: 0}}
      ]},
      {width: 0, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 100, left: 0}
      ]}
    );
  });

  it('should calculate left properly with position: absolute right', function() {
    testLayout(
      {style: {width: 100}, children: [
        {style: {position: 'absolute', right: 0}}
      ]},
      {width: 100, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 100}
      ]}
    );
  });

  it('should calculate top properly with position: absolute bottom and height', function() {
    testLayout(
      {style: {height: 100}, children: [
        {style: {height: 10, position: 'absolute', bottom: 0}}
      ]},
      {width: 0, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 10, top: 90, left: 0}
      ]}
    );
  });

  it('should calculate left properly with position: absolute right and width', function() {
    testLayout(
      {style: {width: 100}, children: [
        {style: {width: 10, position: 'absolute', right: 0}}
      ]},
      {width: 100, height: 0, top: 0, left: 0, children: [
        {width: 10, height: 0, top: 0, left: 90}
      ]}
    );
  });

  it('should calculate top properly with position: absolute right, width, and no parent dimensions', function() {
    testLayout(
      {style: {}, children: [
        {style: {height: 10, position: 'absolute', bottom: 0}}
      ]},
      {width: 0, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 10, top: -10, left: 0}
      ]}
    );
  });

  it('should calculate left properly with position: absolute right, width, and no parent dimensions', function() {
    testLayout(
      {style: {}, children: [
        {style: {width: 10, position: 'absolute', right: 0}}
      ]},
      {width: 0, height: 0, top: 0, left: 0, children: [
        {width: 10, height: 0, top: 0, left: -10}
      ]}
    );
  });

  it('should layout border bottom inside of justify content space between container', function() {
    testLayout(
      {style: {justifyContent: 'space-between'}, children: [
        {style: {borderBottomWidth: 1}}
      ]},
      {width: 0, height: 1, top: 0, left: 0, children: [
        {width: 0, height: 1, top: 0, left: 0}
      ]}
    );
  });

  it('should layout negative margin top inside of justify content center container', function() {
    testLayout(
      {style: {justifyContent: 'center'}, children: [
        {style: {marginTop: -6}}
      ]},
      {width: 0, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: -3, left: 0}
      ]}
    );
  });

  it('should layout positive margin top inside of justify content center container', function() {
    testLayout(
      {style: {justifyContent: 'center'}, children: [
        {style: {marginTop: 20}}
      ]},
      {width: 0, height: 20, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 20, left: 0}
      ]}
    );
  });

  it('should layout border bottom and flex end with an empty child', function() {
    testLayout(
      {style: {borderBottomWidth: 5, justifyContent: 'flex-end'}, children: [
        {style: {}}
      ]},
      {width: 0, height: 5, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 0}
      ]}
    );
  });

  it('should layout with children of a contain with left', function() {
    testLayout(
      {style: {width: 800}, children: [
        {style: {left: 5}, children: [
          {style: {}}
        ]}
      ]},
      {width: 800, height: 0, top: 0, left: 0, children: [
        {width: 800, height: 0, top: 0, left: 5, children: [
          {width: 800, height: 0, top: 0, left: 0}
        ]}
      ]}
    );
  });

  // This behavior is very weird. The child has a width of 0 but somehow the
  // parent has a width of 500. Looks like a bug rather than a feature.
  // https://code.google.com/p/chromium/issues/detail?id=441768
  xit('should layout with flex: 0 and a specific width', function() {
    testLayout(
      {style: {flexDirection: 'row'}, children: [
        {style: {width: 500, flex: 0}}
      ]},
      {width: 500, height: 0, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 0}
      ]}
    );
  });

  xit('should layout with nested padding', function() {
    testLayout(
      {style: {}, children: [
        {style: {}, children: [
          {style: {}}
        ]},
        {style: {padding: 5}}
      ]},
      {width: 10, height: 10, top: 0, left: 0, children: [
        {width: 10, height: 0, top: 0, left: 0, children: [
          {width: 10, height: 0, top: 0, left: 0}
        ]},
        {width: 10, height: 10, top: 0, left: 0}
      ]}
    );
  });

  it('should layout flex-wrap', function() {
    testLayout(
      {style: {flexWrap: 'wrap', flexDirection: 'row', width: 100}, children: [
        {style: {width: 40, height: 10}},
        {style: {width: 40, height: 10}},
        {style: {width: 40, height: 10}}
      ]},
      {width: 100, height: 20, top: 0, left: 0, children: [
        {width: 40, height: 10, top: 0, left: 0},
        {width: 40, height: 10, top: 0, left: 40},
        {width: 40, height: 10, top: 10, left: 0}
      ]}
    );
  });

  it('should layout flex-wrap in rtl', function() {
    testLayout(
      {style: {flexWrap: 'wrap', direction: 'rtl', flexDirection: 'row', width: 100}, children: [
        {style: {width: 40, height: 10}},
        {style: {width: 40, height: 10}},
        {style: {width: 40, height: 10}}
      ]},
      {width: 100, height: 20, top: 0, left: 0, children: [
        {width: 40, height: 10, top: 0, left: 60},
        {width: 40, height: 10, top: 0, left: 20},
        {width: 40, height: 10, top: 10, left: 60}
      ]}
    );
  });

  it('should layout flex wrap with a line bigger than container', function() {
    testLayout(
      {style: {height: 100, flexWrap: 'wrap'}, children: [
        {style: {height: 100}},
        {style: {height: 200}}
      ]},
      {width: 0, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 100, top: 0, left: 0},
        {width: 0, height: 200, top: 0, left: 0}
      ]}
    );
  });

  // The container should be width = 25 because the width of the two children
  // are 20 and 5. It's likely a bug in Chrome
  // https://code.google.com/p/chromium/issues/detail?id=247963#c16
  xit('should layout flex wrap with padding and borders', function() {
    testLayout(
      {style: {height: 100, flexWrap: 'wrap'}, children: [
        {style: {height: 500, paddingRight: 20}},
        {style: {borderLeftWidth: 5}}
      ]},
      {width: 20, height: 100, top: 0, left: 0, children: [
        {width: 20, height: 500, top: 0, left: 0},
        {width: 5, height: 0, top: 0, left: 20}
      ]}
    );
  });


  xit('should layout text with alignItems: stretch', function() {
    testLayout(
      {style: {width: 80, padding: 7, alignItems: 'stretch', measure: text(texts.big)}},
      {width: 80, height: 68, top: 0, left: 0}
    );
  });

  xit('should layout node with text and position absolute', function() {
    testLayout(
      {style: {}, children: [
        {style: {measure: text(texts.big)}}
      ]},
      {width: 0, height: 0, top: 0, left: 0, children: [
        {width: 100, height: textSizes.bigHeight, top: 0, left: 0}
      ]}
    );
  });

  it('should use max bounds', function() {
    testLayout(
      {style: {width: 100, height: 200, maxWidth: 90, maxHeight: 190}},
      {width: 90, height: 190, top: 0, left: 0}
    );
  });

  it('should use min bounds', function() {
    testLayout(
      {style: {width: 100, height: 200, minWidth: 110, minHeight: 210}},
      {width: 110, height: 210, top: 0, left: 0}
    );
  });

  it('should use min bounds over max bounds', function() {
    testLayout(
      {style: {width: 100, height: 200, minWidth: 110, maxWidth: 90, minHeight: 210, maxHeight: 190}},
      {width: 110, height: 210, top: 0, left: 0}
    );
  });

  it('should use min bounds over max bounds and natural width', function() {
    testLayout(
      {style: {width: 100, height: 200, minWidth: 90, maxWidth: 80, minHeight: 190, maxHeight: 180}},
      {width: 90, height: 190, top: 0, left: 0}
    );
  });

  it('should ignore negative min bounds', function() {
    testLayout(
      {style: {width: 100, height: 200, minWidth: -10, minHeight: -20}},
      {width: 100, height: 200, top: 0, left: 0}
    );
  });

  it('should ignore negative max bounds', function() {
    testLayout(
      {style: {width: 100, height: 200, maxWidth: -10, maxHeight: -20}},
      {width: 100, height: 200, top: 0, left: 0}
    );
  });

  it('should use padded size over max bounds', function() {
    testLayout(
      {style: {paddingTop: 15, paddingBottom: 15, paddingLeft: 20, paddingRight: 20, maxWidth: 30, maxHeight: 10}},
      {width: 40, height: 30, top: 0, left: 0}
    );
  });

  it('should use min size over padded size', function() {
    testLayout(
      {style: {paddingTop: 15, paddingBottom: 15, paddingLeft: 20, paddingRight: 20, minWidth: 50, minHeight: 40}},
      {width: 50, height: 40, top: 0, left: 0}
    );
  });

  it('should override flex direction size with min bounds', function() {
    testLayout(
      {style: {width: 300, height: 200, flexDirection: 'row'}, children: [
        {style: {flex: 1}},
        {style: {flex: 1, minWidth: 200}},
        {style: {flex: 1}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 50, height: 200, top: 0, left: 0},
        {width: 200, height: 200, top: 0, left: 50},
        {width: 50, height: 200, top: 0, left: 250}
      ]}
    );
  });

  it('should override flex direction size with min bounds in rtl', function() {
    testLayout(
      {style: {width: 300, height: 200, direction: 'rtl', flexDirection: 'row'}, children: [
        {style: {flex: 1}},
        {style: {flex: 1, minWidth: 200}},
        {style: {flex: 1}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 50, height: 200, top: 0, left: 250},
        {width: 200, height: 200, top: 0, left: 50},
        {width: 50, height: 200, top: 0, left: 0}
      ]}
    );
  });

  it('should not override flex direction size within bounds', function() {
    testLayout(
      {style: {width: 300, height: 200, flexDirection: 'row'}, children: [
        {style: {flex: 1}},
        {style: {flex: 1, minWidth: 90, maxWidth: 110}},
        {style: {flex: 1}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 100, height: 200, top: 0, left: 0},
        {width: 100, height: 200, top: 0, left: 100},
        {width: 100, height: 200, top: 0, left: 200}
      ]}
    );
  });

  it('should not override flex direction size within bounds in rtl', function() {
    testLayout(
      {style: {width: 300, height: 200, direction: 'rtl', flexDirection: 'row'}, children: [
        {style: {flex: 1}},
        {style: {flex: 1, minWidth: 90, maxWidth: 110}},
        {style: {flex: 1}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 100, height: 200, top: 0, left: 200},
        {width: 100, height: 200, top: 0, left: 100},
        {width: 100, height: 200, top: 0, left: 0}
      ]}
    );
  });

  it('should override flex direction size with max bounds', function() {
    testLayout(
      {style: {width: 300, height: 200, flexDirection: 'row'}, children: [
        {style: {flex: 1}},
        {style: {flex: 1, maxWidth: 60}},
        {style: {flex: 1}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 120, height: 200, top: 0, left: 0},
        {width: 60, height: 200, top: 0, left: 120},
        {width: 120, height: 200, top: 0, left: 180}
      ]}
    );
  });

  it('should override flex direction size with max bounds in rtl', function() {
    testLayout(
      {style: {width: 300, height: 200, direction: 'rtl', flexDirection: 'row'}, children: [
        {style: {flex: 1}},
        {style: {flex: 1, maxWidth: 60}},
        {style: {flex: 1}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 120, height: 200, top: 0, left: 180},
        {width: 60, height: 200, top: 0, left: 120},
        {width: 120, height: 200, top: 0, left: 0}
      ]}
    );
  });

  it('should ignore flex size if fully max bound', function() {
    testLayout(
      {style: {width: 300, height: 200, flexDirection: 'row'}, children: [
        {style: {flex: 1, maxWidth: 60}},
        {style: {flex: 1, maxWidth: 60}},
        {style: {flex: 1, maxWidth: 60}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 60, height: 200, top: 0, left: 0},
        {width: 60, height: 200, top: 0, left: 60},
        {width: 60, height: 200, top: 0, left: 120}
      ]}
    );
  });

  it('should ignore flex size if fully max bound in rtl', function() {
    testLayout(
      {style: {width: 300, height: 200, direction: 'rtl', flexDirection: 'row'}, children: [
        {style: {flex: 1, maxWidth: 60}},
        {style: {flex: 1, maxWidth: 60}},
        {style: {flex: 1, maxWidth: 60}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 60, height: 200, top: 0, left: 240},
        {width: 60, height: 200, top: 0, left: 180},
        {width: 60, height: 200, top: 0, left: 120}
      ]}
    );
  });

  it('should ignore flex size if fully min bound', function() {
    testLayout(
      {style: {width: 300, height: 200, flexDirection: 'row'}, children: [
        {style: {flex: 1, minWidth: 120}},
        {style: {flex: 1, minWidth: 120}},
        {style: {flex: 1, minWidth: 120}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 120, height: 200, top: 0, left: 0},
        {width: 120, height: 200, top: 0, left: 120},
        {width: 120, height: 200, top: 0, left: 240}
      ]}
    );
  });

  it('should ignore flex size if fully min bound in rtl', function() {
    testLayout(
      {style: {width: 300, height: 200, direction: 'rtl', flexDirection: 'row'}, children: [
        {style: {flex: 1, minWidth: 120}},
        {style: {flex: 1, minWidth: 120}},
        {style: {flex: 1, minWidth: 120}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 120, height: 200, top: 0, left: 180},
        {width: 120, height: 200, top: 0, left: 60},
        {width: 120, height: 200, top: 0, left: -60}
      ]}
    );
  });

  it('should pre-fill child size within bounds', function() {
    testLayout(
      {style: {width: 300, height: 200}, children: [
        {style: {flex: 1, minWidth: 290, maxWidth: 310}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 300, height: 200, top: 0, left: 0}
      ]}
    );
  });

  it('should pre-fill child size within max bound', function() {
    testLayout(
      {style: {width: 300, height: 200}, children: [
        {style: {flex: 1, maxWidth: 290}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 290, height: 200, top: 0, left: 0}
      ]}
    );
  });

  it('should pre-fill child size within min bounds', function() {
    testLayout(
      {style: {width: 300, height: 200}, children: [
        {style: {flex: 1, minWidth: 310}}
      ]},
      {width: 300, height: 200, top: 0, left: 0, children: [
        {width: 310, height: 200, top: 0, left: 0}
      ]}
    );
  });

  it('should set parents size based on bounded children', function() {
    testLayout(
      {style: {minWidth: 100, maxWidth: 300, minHeight: 500, maxHeight: 700}, children: [
        {style: {width: 200, height: 300}},
        {style: {width: 200, height: 300}}
      ]},
      {width: 200, height: 600, top: 0, left: 0, children: [
        {width: 200, height: 300, top: 0, left: 0},
        {width: 200, height: 300, top: 300, left: 0}
      ]}
    );
  });

  it('should set parents size based on max bounded children', function() {
    testLayout(
      {style: {maxWidth: 100, maxHeight: 500}, children: [
        {style: {width: 200, height: 300}},
        {style: {width: 200, height: 300}}
      ]},
      {width: 100, height: 500, top: 0, left: 0, children: [
        {width: 200, height: 300, top: 0, left: 0},
        {width: 200, height: 300, top: 300, left: 0}
      ]}
    );
  });

  it('should set parents size based on min bounded children', function() {
    testLayout(
      {style: {minWidth: 300, minHeight: 700}, children: [
        {style: {width: 200, height: 300}},
        {style: {width: 200, height: 300}}
      ]},
      {width: 300, height: 700, top: 0, left: 0, children: [
        {width: 200, height: 300, top: 0, left: 0},
        {width: 200, height: 300, top: 300, left: 0}
      ]}
    );
  });

  it('should keep stretched size within bounds', function() {
    testLayout(
      {style: {width: 1000, alignItems: 'stretch'}, children: [
        {style: {height: 100, minHeight: 90, maxHeight: 110, minWidth: 900, maxWidth: 1100}}
      ]},
      {width: 1000, height: 100, top: 0, left: 0, children: [
        {width: 1000, height: 100, top: 0, left: 0}
      ]}
    );
  });

  it('should keep stretched size within max bounds', function() {
    testLayout(
      {style: {width: 1000, alignItems: 'stretch'}, children: [
        {style: {height: 100, maxHeight: 90, maxWidth: 900}}
      ]},
      {width: 1000, height: 90, top: 0, left: 0, children: [
        {width: 900, height: 90, top: 0, left: 0}
      ]}
    );
  });

  it('should keep stretched size within min bounds', function() {
    testLayout(
      {style: {width: 1000, alignItems: 'stretch'}, children: [
        {style: {height: 100, minHeight: 110, minWidth: 1100}}
      ]},
      {width: 1000, height: 110, top: 0, left: 0, children: [
        {width: 1100, height: 110, top: 0, left: 0}
      ]}
    );
  });

  it('should keep cross axis size within min bounds', function() {
    testLayout(
      {style: {width: 1000, flexDirection: 'row'}, children: [
        {style: {height: 100, minHeight: 110, minWidth: 100}}
      ]},
      {width: 1000, height: 110, top: 0, left: 0, children: [
        {width: 100, height: 110, top: 0, left: 0}
      ]}
    );
  });

  it('should keep cross axis size within min bounds in rtl', function() {
    testLayout(
      {style: {width: 1000, direction: 'rtl', flexDirection: 'row'}, children: [
        {style: {height: 100, minHeight: 110, minWidth: 100}}
      ]},
      {width: 1000, height: 110, top: 0, left: 0, children: [
        {width: 100, height: 110, top: 0, left: 900}
      ]}
    );
  });

  it('should layout node with position absolute, top and left and max bounds', function() {
    testLayout(
      {style: {width: 1000, height: 1000}, children: [
        {style: {position: 'absolute', top: 100, left: 100, bottom: 100, right: 100, maxWidth: 500, maxHeight: 600}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 500, height: 600, top: 100, left: 100}
      ]}
    );
  });

  it('should layout node with position absolute, top and left and min bounds', function() {
    testLayout(
      {style: {width: 1000, height: 1000}, children: [
        {style: {position: 'absolute', top: 100, left: 100, bottom: 100, right: 100, minWidth: 900, minHeight: 1000}}
      ]},
      {width: 1000, height: 1000, top: 0, left: 0, children: [
        {width: 900, height: 1000, top: 100, left: 100}
      ]}
    );
  });

  xit('should layout minHeight with a flex child', function() {
    testLayout(
      {style: {minHeight: 800}, children: [
        {style: {flex: 1}}
      ]},
      {width: 0, height: 800, top: 0, left: 0, children: [
        {width: 0, height: 800, top: 0, left: 0}
      ]}
    );
  });

  xit('should layout node with a nested sibling child with width', function() {
    testLayout(
      {style: {}, children: [
        {style: {width: 5}},
        {style: {}, children: [
          {style: {}}
        ]}
      ]},
      {width: 5, height: 0, top: 0, left: 0, children: [
        {width: 5, height: 0, top: 0, left: 0},
        {width: 5, height: 0, top: 0, left: 0, children: [
          {width: 5, height: 0, top: 0, left: 0}
        ]}
      ]}
    );
  });

  it('should layout absolutely positioned node with absolutely positioned padded parent', function() {
    testLayout(
      {style: {width: 400, height: 400}, children: [
        {style: {position: 'absolute', top: 100, left: 100, right: 100, bottom: 100, padding: 10}, children: [
          {style: {position: 'absolute', top: 10, left: 10, right: 10, bottom: 10}}
        ]},
      ]},
      {width: 400, height: 400, top: 0, left: 0, children: [
        {width: 200, height: 200, top: 100, left: 100, children: [
          {width: 180, height: 180, top: 10, left: 10}
        ]}
      ]}
    );
  });

  it('should layout absolutely positioned node with absolutely positioned padded and bordered parent', function() {
    testLayout(
      {style: {width: 400, height: 400}, children: [
        {style: {position: 'absolute', top: 100, left: 100, right: 100, bottom: 100, padding: 10, borderWidth: 1}, children: [
          {style: {position: 'absolute', top: 10, left: 10, right: 10, bottom: 10}}
        ]},
      ]},
      {width: 400, height: 400, top: 0, left: 0, children: [
        {width: 200, height: 200, top: 100, left: 100, children: [
          {width: 178, height: 178, top: 11, left: 11}
        ]}
      ]}
    );
  });

  it('should layout absolutely positioned node with padded flex 1 parent', function() {
    testLayout(
      {style: {width: 400, height: 400}, children: [
        {style: {flex: 1, padding: 10}, children: [
          {style: {position: 'absolute', top: 10, left: 10, right: 10, bottom: 10}}
        ]},
      ]},
      {width: 400, height: 400, top: 0, left: 0, children: [
        {width: 400, height: 400, top: 0, left: 0, children: [
          {width: 380, height: 380, top: 10, left: 10}
        ]}
      ]}
    );
  });

  it('should layout nested nodes with mixed directions', function() {
    testLayout(
      {style: {width: 200, height: 200, direction: 'rtl'}, children: [
        {style: {flexDirection: 'row'}, children: [
          {style: {width: 50, height: 50}},
          {style: {width: 50, height: 50}}
        ]},
        {style: {direction: 'ltr', flexDirection: 'row'}, children: [
          {style: {width: 50, height: 50}},
          {style: {width: 50, height: 50}}
        ]}
      ]},
      {width: 200, height: 200, top: 0, left: 0, children: [
        {width: 200, height: 50, top: 0, left: 0, children: [
          {width: 50, height: 50, top: 0, left: 150},
          {width: 50, height: 50, top: 0, left: 100}
        ]},
        {width: 200, height: 50, top: 50, left: 0, children: [
          {width: 50, height: 50, top: 0, left: 0},
          {width: 50, height: 50, top: 0, left: 50}
        ]}
      ]}
    );
  });

  it('should correctly space wrapped nodes', function() {
    testLayout(
      {style: {width: 320, height: 200, flexDirection: 'row', justifyContent: 'space-between', flexWrap: 'wrap'}, children: [
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}},
        {style: {width: 100, height: 100}},
      ]},
      {width: 320, height: 200, top: 0, left: 0, children: [
        {width: 100, height: 100, top: 0, left: 0},
        {width: 100, height: 100, top: 0, left: 110},
        {width: 100, height: 100, top: 0, left: 220},
        {width: 100, height: 100, top: 100, left: 0},
        {width: 100, height: 100, top: 100, left: 110},
        {width: 100, height: 100, top: 100, left: 220},
      ]}
    );
  });

  it('should give start/end padding precedence over left/right padding', function() {
    testLayout(
      {style: {width: 200, paddingLeft: 5, paddingStart: 15, paddingRight: 5, paddingEnd: 15}, children: [
        {style: {height: 50}}
      ]},
      {width: 200, height: 50, top: 0, left: 0, children: [
        {width: 170, height: 50, top: 0, left: 15}
      ]}
    );
  });

  it('should give start/end margin precedence over left/right margin', function() {
    testLayout(
      {style: {width: 200}, children: [
        {style: {height: 50, marginLeft: 5, marginStart: 15, marginRight: 5, marginEnd: 15}}
      ]},
      {width: 200, height: 50, top: 0, left: 0, children: [
        {width: 170, height: 50, top: 0, left: 15}
      ]}
    );
  });

  it('should give start/end border precedence over left/right border', function() {
    testLayout(
      {style: {width: 200, borderLeftWidth: 5, borderStartWidth: 15, borderRightWidth: 5, borderEndWidth: 15}, children: [
        {style: {height: 50}}
      ]},
      {width: 200, height: 50, top: 0, left: 0, children: [
        {width: 170, height: 50, top: 0, left: 15}
      ]}
    );
  });

  it('should layout node with correct start/end padding', function() {
    testLayout(
      {style: {width: 200, paddingStart: 15, paddingEnd: 5}, children: [
        {style: {height: 50}}
      ]},
      {width: 200, height: 50, top: 0, left: 0, children: [
        {width: 180, height: 50, top: 0, left: 15}
      ]}
    );
  });

  it('should layout node with correct start/end padding in rtl', function() {
    testLayout(
      {style: {width: 200, direction: 'rtl', paddingStart: 15, paddingEnd: 5}, children: [
        {style: {height: 50}}
      ]},
      {width: 200, height: 50, top: 0, left: 0, children: [
        {width: 180, height: 50, top: 0, left: 5}
      ]}
    );
  });

  it('should layout node with correct start/end margin', function() {
    testLayout(
      {style: {width: 200}, children: [
        {style: {height: 50, marginStart: 15, marginEnd: 5}}
      ]},
      {width: 200, height: 50, top: 0, left: 0, children: [
        {width: 180, height: 50, top: 0, left: 15}
      ]}
    );
  });

  it('should layout node with correct start/end margin in rtl', function() {
    testLayout(
      {style: {width: 200}, children: [
        {style: {height: 50, direction: 'rtl', marginStart: 15, marginEnd: 5}}
      ]},
      {width: 200, height: 50, top: 0, left: 0, children: [
        {width: 180, height: 50, top: 0, left: 5}
      ]}
    );
  });

  it('should layout node with correct start/end border', function() {
    testLayout(
      {style: {width: 200, borderStartWidth: 15, borderEndWidth: 5}, children: [
        {style: {height: 50}}
      ]},
      {width: 200, height: 50, top: 0, left: 0, children: [
        {width: 180, height: 50, top: 0, left: 15}
      ]}
    );
  });

  it('should layout node with correct start/end border in rtl', function() {
    testLayout(
      {style: {width: 200, direction: 'rtl', borderStartWidth: 15, borderEndWidth: 5}, children: [
        {style: {height: 50}}
      ]},
      {width: 200, height: 50, top: 0, left: 0, children: [
        {width: 180, height: 50, top: 0, left: 5}
      ]}
    );
  });
});
