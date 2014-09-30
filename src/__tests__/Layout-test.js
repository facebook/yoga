/* globals layoutTestUtils */

var testLayout = layoutTestUtils.testLayout;
var text = layoutTestUtils.text;
var texts = layoutTestUtils.texts;
var textSizes = layoutTestUtils.textSizes;

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
          {width: 250, height: 250, top: 250, left: 0},
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

  it('should layout node with flex', function() {
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

  it('should layout node with flex override height', function() {
    testLayout(
      {style: {width: 1000, height: 1000}, children: [
        {style: {width: 100, height: 100, flex: 1}},
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
        {width: 100, height: 100, top: 100, left: 0},
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
        {width: 100, height: 100, top: 100, left: 450},
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
        {width: 100, height: 100, top: 100, left: 900},
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
        {width: 100, height: 100, top: 100, left: 450},
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

  it('should not shrink children if not enough space', function() {
    testLayout(
      {style: {height: 100}, children: [
        {style: {height: 100}},
        {style: {height: 200}},
      ]},
      {width: 0, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 100, top: 0, left: 0},
        {width: 0, height: 200, top: 100, left: 0}
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

  it('should layout flex inside of an empty element', function() {
    testLayout(
      {style: {}, children: [
        {style: {flex: 1}},
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
        {style: {flex: 1}},
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
    )
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

  it('should layout node with double flex and position absolute', function() {
    testLayout(
      {style: {height: 500}, children: [
        {style: {flex: 1}},
        {style: {flex: 1, position: 'absolute'}}
      ]},
      {width: 0, height: 500, top: 0, left: 0, children: [
        {width: 0, height: 500, top: 0, left: 0},
        {width: 0, height: 0, top: 500, left: 0},
      ]}
    )
  });

  it('should layout node with borderWidth', function() {
    testLayout(
      {style: {borderWidth: 5}},
      {width: 10, height: 10, top: 0, left: 0}
    )
  });

  it('should layout node with borderWidth and position: absolute, top', function() {
    testLayout(
      {style: {borderTopWidth: 1}, children: [
        {style: {top: -1, position: 'absolute'}}
      ]},
      {width: 0, height: 1, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 0}
      ]}
    )
  });

  it('should layout node with borderWidth and position: absolute, top. cross axis', function() {
    testLayout(
      {style: {borderWidth: 1}, children: [
        {style: {left: 5, position: 'absolute'}}
      ]},
      {width: 2, height: 2, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 1, left: 6}
      ]}
    )
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
      {style: {width: 100}, children: [
        {style: {measure: text(texts.big)}}
      ]},
      {width: 100, height: textSizes.bigHeight, top: 0, left: 0, children: [
        {width: textSizes.bigMinWidth, height: textSizes.bigHeight, top: 0, left: 0}
      ]}
    );
  });

  it('should layout node with text bounded by grand-parent', function() {
    testLayout(
      {style: {width: 100, padding: 10}, children: [
        {style: {margin: 10}, children: [
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

  it('should layout text with flexDirection row', function() {
    testLayout(
      {style: {}, children: [
        {style: {width: 200, flexDirection: 'row'}, children: [
          {style: {margin: 20, measure: text(texts.big)}}
        ]}
      ]},
      {width: 200, height: 58, top: 0, left: 0, children: [
        {width: 200, height: 58, top: 0, left: 0, children: [
          {width: textSizes.bigWidth, height: textSizes.smallHeight, top: 20, left: 20}
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
      {width: 200, height: 76, top: 0, left: 0, children: [
        {width: 200, height: 76, top: 0, left: 0, children: [
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
      {style: {width: 100, height: 100}, children: [
        {style: {flex: 2.5}},
        {style: {flex: 7.5}}
      ]},
      {width: 100, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 25, top: 0, left: 0},
        {width: 0, height: 75, top: 25, left: 0},
      ]}
    );
  });

  it('should layout with negative flex', function() {
    testLayout(
      {style: {width: 100, height: 100}, children: [
        {style: {flex: -2.5}},
        {style: {flex: 0}}
      ]},
      {width: 100, height: 100, top: 0, left: 0, children: [
        {width: 0, height: 0, top: 0, left: 0},
        {width: 0, height: 0, top: 0, left: 0},
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
        {width: 50, height: 0, top: 100, left: 0},
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

  it('should layout with position: absolute, bottom', function() {
    testLayout(
      {style: {width: 100, height: 100}, children: [
        {style: {position: 'absolute', top: 0, bottom: 20}}
      ]},
      {width: 100, height: 100, top: 0, left: 0, children: [
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

});

