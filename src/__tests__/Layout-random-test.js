/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
/* globals layoutTestUtils */
var testRandomLayout = layoutTestUtils.testRandomLayout;
var computeLayout = layoutTestUtils.computeLayout;
var computeDOMLayout = layoutTestUtils.computeDOMLayout;
var reduceTest = layoutTestUtils.reduceTest;

describe('Random layout', function() {

  function RNG(seed) {
    this.state = seed;
  }
  RNG.prototype.nextFloat = function() {
    // LCG using GCC's constants
    this.state = (1103515245 * this.state + 12345) % 0x80000000;
    return this.state / (0x80000000 - 1);
  };

  var rng = new RNG(0);
  function randMinMax(node, chance, attribute, min, max) {
    if (rng.nextFloat() < chance) {
      if (attribute === 'right' || attribute === 'bottom') {
        return;
      }
      node.style[attribute] = Math.floor(rng.nextFloat() * (max - min)) + min;
    }
  }
  function randEnum(node, chance, attribute, enumValues) {
    if (rng.nextFloat() < chance) {
      node.style[attribute] = enumValues[Math.floor(rng.nextFloat() * enumValues.length)];
    }
  }

  function randSpacing(node, chance, type, suffix, min, max) {
    randMinMax(node, chance, type + suffix, min, max);
    randMinMax(node, chance, type + 'Left' + suffix, min, max);
    randMinMax(node, chance, type + 'Top' + suffix, min, max);
    randMinMax(node, chance, type + 'Right' + suffix, min, max);
    randMinMax(node, chance, type + 'Bottom' + suffix, min, max);
  }
  function generateRandomNode() {
    var node = {style: {}};
    randMinMax(node, 0.5, 'width', -100, 1000);
    randMinMax(node, 0.5, 'height', -100, 1000);
    randMinMax(node, 0.5, 'minWidth', -100, 1000);
    randMinMax(node, 0.5, 'minHeight', -100, 1000);
    randMinMax(node, 0.5, 'maxWidth', -100, 1000);
    randMinMax(node, 0.5, 'maxHeight', -100, 1000);
    randMinMax(node, 0.5, 'top', -10, 10);
    randMinMax(node, 0.5, 'left', -10, 10);
    randMinMax(node, 0.5, 'right', -10, 10);
    randMinMax(node, 0.5, 'bottom', -10, 10);
    randSpacing(node, 0.5, 'margin', '', -10, 20);
    randSpacing(node, 0.5, 'padding', '', -10, 20);
    randSpacing(node, 0.5, 'border', 'Width', -4, 4);
    randMinMax(node, 0.5, 'flex', -10, 10);
    randEnum(node, 0.5, 'flexDirection', ['column', 'row']);
    randEnum(node, 0.5, 'justifyContent', ['flex-start', 'center', 'flex-end', 'space-between', 'space-around']);
    randEnum(node, 0.5, 'alignItems', ['flex-start', 'center', 'flex-end', 'stretch']);
    randEnum(node, 0.5, 'alignSelf', ['flex-start', 'center', 'flex-end', 'stretch']);
    randEnum(node, 0.5, 'position', ['relative', 'absolute']);
    randEnum(node, 0.5, 'flexWrap', ['nowrap', 'wrap']);
    //randEnum(node, 0.5, 'measure', [text(texts.small), text(texts.big)]);

    // Chrome is doing some very weird things with this. Probably not worth supporting
    if (node.style.flex === 0) {
      delete node.style.flex;
    }

    if (node.style.measure) {
      // align-items: stretch on a text node makes it wrap in a different way.
      // We don't yet support this use case
      delete node.style.alignItems;

      // Text that is position: absolute behaves very strangely
      delete node.style.position;
    }

    function randChildren(node, chance) {
      while (rng.nextFloat() < chance) {
        if (!node.children) {
          node.children = [];
        }
        node.children.push(generateRandomNode());
      }
    }

    randChildren(node, 0.4);
    return node;
  }

  function checkRandomLayout(i, node) {
      it('should layout randomly #' + i + '.', function(node) {
        if (JSON.stringify(computeLayout(node)) !== JSON.stringify(computeDOMLayout(node))) {
          node = reduceTest(node);
        }

        testRandomLayout(node, i);
      }.bind(this, node));
  }

  for (var i = 0; i < 100; ++i) {
    var node = generateRandomNode();
    // The iframe's body has a natural width of 300 that it doesn't really make
    // to replicate in the test suite. The easiest workaround is not to test
    // alignSelf, position and flex properties on the root element.
    delete node.style.alignSelf;
    delete node.style.flex;
    delete node.style.position;

    checkRandomLayout.call(this, i, node);
  }

});
