/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import {getMeasureCounter} from '../tools/MeasureCounter.ts';
import {YGBENCHMARK} from '../tools/globals.ts';

import Yoga from 'yoga-layout';

const ITERATIONS = 2000;

YGBENCHMARK('Stack with flex', () => {
  const root = Yoga.Node.create();
  root.setWidth(100);
  root.setHeight(100);

  const measureCounter = getMeasureCounter();

  for (let i = 0; i < ITERATIONS; i++) {
    const child = Yoga.Node.create();
    child.setMeasureFunc(measureCounter.inc);
    child.setFlex(1);
    root.insertChild(child, 0);
  }

  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);
  root.freeRecursive();
});

YGBENCHMARK('Align stretch in undefined axis', () => {
  const root = Yoga.Node.create();

  const measureCounter = getMeasureCounter();

  for (let i = 0; i < ITERATIONS; i++) {
    const child = Yoga.Node.create();
    child.setMeasureFunc(measureCounter.inc);
    child.setHeight(20);
    root.insertChild(child, 0);
  }

  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);
  root.freeRecursive();
});

YGBENCHMARK('Nested flex', () => {
  const root = Yoga.Node.create();

  const measureCounter = getMeasureCounter();

  const iterations = Math.pow(ITERATIONS, 1 / 2);

  for (let i = 0; i < iterations; i++) {
    const child = Yoga.Node.create();
    child.setFlex(1);
    root.insertChild(child, 0);

    for (let ii = 0; ii < iterations; ii++) {
      const grandChild = Yoga.Node.create();
      grandChild.setMeasureFunc(measureCounter.inc);
      grandChild.setFlex(1);
      child.insertChild(grandChild, 0);
    }
  }

  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);
  root.freeRecursive();
});

YGBENCHMARK('Huge nested layout', () => {
  const root = Yoga.Node.create();

  const iterations = Math.pow(ITERATIONS, 1 / 4);

  for (let i = 0; i < iterations; i++) {
    const child = Yoga.Node.create();
    child.setFlexGrow(1);
    child.setWidth(10);
    child.setHeight(10);
    root.insertChild(child, 0);

    for (let ii = 0; ii < iterations; ii++) {
      const grandChild = Yoga.Node.create();
      grandChild.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
      grandChild.setFlexGrow(1);
      grandChild.setWidth(10);
      grandChild.setHeight(10);
      child.insertChild(grandChild, 0);

      for (let iii = 0; iii < iterations; iii++) {
        const grandGrandChild = Yoga.Node.create();
        grandGrandChild.setFlexGrow(1);
        grandGrandChild.setWidth(10);
        grandGrandChild.setHeight(10);
        grandChild.insertChild(grandGrandChild, 0);

        for (let iiii = 0; iiii < iterations; iiii++) {
          const grandGrandGrandChild = Yoga.Node.create();
          grandGrandGrandChild.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
          grandGrandGrandChild.setFlexGrow(1);
          grandGrandGrandChild.setWidth(10);
          grandGrandGrandChild.setHeight(10);
          grandGrandChild.insertChild(grandGrandGrandChild, 0);
        }
      }
    }
  }

  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);
  root.freeRecursive();
});
