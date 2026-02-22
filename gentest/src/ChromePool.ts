/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import {Builder} from 'selenium-webdriver';
import {Options} from 'selenium-webdriver/chrome.js';
import type {WebDriver} from 'selenium-webdriver';

export interface ChromePool {
  acquire(): Promise<WebDriver>;
  release(driver: WebDriver): void;
  shutdown(): Promise<void>;
}

/**
 * Create a pool of headless Chrome WebDriver instances.
 * acquire() returns a driver when one is available; callers are
 * queued FIFO when all instances are busy.
 */
export function createChromePool(size: number): ChromePool {
  const available: WebDriver[] = [];
  const waitQueue: Array<(driver: WebDriver) => void> = [];
  const allDrivers: Promise<WebDriver>[] = [];

  function addDriver(driver: WebDriver): void {
    const waiter = waitQueue.shift();
    if (waiter) {
      waiter(driver);
    } else {
      available.push(driver);
    }
  }

  // Create all Chrome instances in parallel, making each available as it resolves
  for (let i = 0; i < size; i++) {
    const driverPromise = createDriver();
    allDrivers.push(driverPromise);
    driverPromise.then(addDriver);
  }

  return {
    acquire(): Promise<WebDriver> {
      const driver = available.pop();
      if (driver) {
        return Promise.resolve(driver);
      }
      return new Promise<WebDriver>(resolve => {
        waitQueue.push(resolve);
      });
    },

    release(driver: WebDriver): void {
      addDriver(driver);
    },

    async shutdown(): Promise<void> {
      const drivers = await Promise.all(allDrivers);
      await Promise.all(drivers.map(d => d.quit()));
    },
  };
}

function createDriver(): Promise<WebDriver> {
  const options = new Options();
  options.addArguments(
    '--force-device-scale-factor=1',
    '--window-position=0,0',
    '--hide-scrollbars',
    '--headless',
  );

  return new Builder().forBrowser('chrome').setChromeOptions(options).build();
}
