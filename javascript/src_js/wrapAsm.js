/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

const CONSTANTS = require("./generated/YGEnums");

module.exports = (lib) => {
  function patch(prototype, name, fn) {
    const original = prototype[name];

    prototype[name] = function (...args) {
      return fn.call(this, original, ...args);
    };
  }

  for (const fnName of [
    "setPosition",
    "setMargin",
    "setFlexBasis",
    "setWidth",
    "setHeight",
    "setMinWidth",
    "setMinHeight",
    "setMaxWidth",
    "setMaxHeight",
    "setPadding",
  ]) {
    const methods = {
      [CONSTANTS.UNIT_POINT]: lib.Node.prototype[fnName],
      [CONSTANTS.UNIT_PERCENT]: lib.Node.prototype[`${fnName}Percent`],
      [CONSTANTS.UNIT_AUTO]: lib.Node.prototype[`${fnName}Auto`],
    };

    patch(lib.Node.prototype, fnName, function (original, ...args) {
      // We patch all these functions to add support for the following calls:
      // .setWidth(100) / .setWidth("100%") / .setWidth(.getWidth()) / .setWidth("auto")

      const value = args.pop();
      let unit, asNumber;

      if (value === "auto") {
        unit = CONSTANTS.UNIT_AUTO;
        asNumber = undefined;
      } else if (typeof value === "object") {
        unit = value.unit;
        asNumber = value.valueOf();
      } else {
        unit =
          typeof value === "string" && value.endsWith("%")
            ? CONSTANTS.UNIT_PERCENT
            : CONSTANTS.UNIT_POINT;
        asNumber = parseFloat(value);
        if (!Number.isNaN(value) && Number.isNaN(asNumber)) {
          throw new Error(`Invalid value ${value} for ${fnName}`);
        }
      }

      if (!methods[unit])
        throw new Error(
          `Failed to execute "${fnName}": Unsupported unit '${value}'`
        );

      if (asNumber !== undefined) {
        return methods[unit].call(this, ...args, asNumber);
      } else {
        return methods[unit].call(this, ...args);
      }
    });
  }

  function wrapMeasureFunction(measureFunction) {
    return lib.MeasureCallback.implement({
      measure: (...args) => {
        const { width, height } = measureFunction(...args);
        return {
          width: width ?? NaN,
          height: height ?? NaN,
        };
      },
    });
  }

  patch(lib.Node.prototype, "setMeasureFunc", function (original, measureFunc) {
    // This patch is just a convenience patch, since it helps write more
    // idiomatic source code (such as .setMeasureFunc(null))
    if (measureFunc) {
      return original.call(this, wrapMeasureFunction(measureFunc));
    } else {
      return this.unsetMeasureFunc();
    }
  });

  function wrapDirtiedFunc(dirtiedFunction) {
    return lib.DirtiedCallback.implement({ dirtied: dirtiedFunction });
  }

  patch(lib.Node.prototype, "setDirtiedFunc", function (original, dirtiedFunc) {
    original.call(this, wrapDirtiedFunc(dirtiedFunc));
  });

  patch(lib.Config.prototype, "free", function () {
    // Since we handle the memory allocation ourselves (via lib.Config.create),
    // we also need to handle the deallocation
    lib.Config.destroy(this);
  });

  patch(lib.Node, "create", (_, config) => {
    // We decide the constructor we want to call depending on the parameters
    return config
      ? lib.Node.createWithConfig(config)
      : lib.Node.createDefault();
  });

  patch(lib.Node.prototype, "free", function () {
    // Since we handle the memory allocation ourselves (via lib.Node.create),
    // we also need to handle the deallocation
    lib.Node.destroy(this);
  });

  patch(lib.Node.prototype, "freeRecursive", function () {
    for (let t = 0, T = this.getChildCount(); t < T; ++t) {
      this.getChild(0).freeRecursive();
    }
    this.free();
  });

  patch(
    lib.Node.prototype,
    "calculateLayout",
    function (
      original,
      width = NaN,
      height = NaN,
      direction = CONSTANTS.DIRECTION_LTR
    ) {
      // Just a small patch to add support for the function default parameters
      return original.call(this, width, height, direction);
    }
  );

  return {
    Config: lib.Config,
    Node: lib.Node,
    ...CONSTANTS,
  };
};
