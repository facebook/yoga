/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

// @ts-nocheck

import {Unit, Direction} from './generated/YGEnums.ts';
import YGEnums from './generated/YGEnums.ts';

import type {
  Align,
  Display,
  Edge,
  Errata,
  ExperimentalFeature,
  FlexDirection,
  Gutter,
  Justify,
  MeasureMode,
  Overflow,
  PositionType,
  Wrap,
} from './generated/YGEnums.ts';

type Layout = {
  left: number;
  right: number;
  top: number;
  bottom: number;
  width: number;
  height: number;
};

type Size = {
  width: number;
  height: number;
};

type Value = {
  unit: Unit;
  value: number;
};

export type Config = {
  free(): void;
  isExperimentalFeatureEnabled(feature: ExperimentalFeature): boolean;
  setExperimentalFeatureEnabled(
    feature: ExperimentalFeature,
    enabled: boolean,
  ): void;
  setPointScaleFactor(factor: number): void;
  getErrata(): Errata;
  setErrata(errata: Errata): void;
  useWebDefaults(): boolean;
  setUseWebDefaults(useWebDefaults: boolean): void;
};

export type DirtiedFunction = (node: Node) => void;

export type MeasureFunction = (
  width: number,
  widthMode: MeasureMode,
  height: number,
  heightMode: MeasureMode,
) => Size;

export type Node = {
  calculateLayout(
    width?: number | 'auto',
    height?: number | 'auto',
    direction?: Direction,
  ): void;
  copyStyle(node: Node): void;
  free(): void;
  freeRecursive(): void;
  getAlignContent(): Align;
  getAlignItems(): Align;
  getAlignSelf(): Align;
  getAspectRatio(): number;
  getBorder(edge: Edge): number;
  getChild(index: number): Node;
  getChildCount(): number;
  getComputedBorder(edge: Edge): number;
  getComputedBottom(): number;
  getComputedHeight(): number;
  getComputedLayout(): Layout;
  getComputedLeft(): number;
  getComputedMargin(edge: Edge): number;
  getComputedPadding(edge: Edge): number;
  getComputedRight(): number;
  getComputedTop(): number;
  getComputedWidth(): number;
  getDisplay(): Display;
  getFlexBasis(): Value;
  getFlexDirection(): FlexDirection;
  getFlexGrow(): number;
  getFlexShrink(): number;
  getFlexWrap(): Wrap;
  getHeight(): Value;
  getJustifyContent(): Justify;
  getGap(gutter: Gutter): Value;
  getMargin(edge: Edge): Value;
  getMaxHeight(): Value;
  getMaxWidth(): Value;
  getMinHeight(): Value;
  getMinWidth(): Value;
  getOverflow(): Overflow;
  getPadding(edge: Edge): Value;
  getParent(): Node | null;
  getPosition(edge: Edge): Value;
  getPositionType(): PositionType;
  getWidth(): Value;
  insertChild(child: Node, index: number): void;
  isDirty(): boolean;
  isReferenceBaseline(): boolean;
  markDirty(): void;
  removeChild(child: Node): void;
  reset(): void;
  setAlignContent(alignContent: Align): void;
  setAlignItems(alignItems: Align): void;
  setAlignSelf(alignSelf: Align): void;
  setAspectRatio(aspectRatio: number): void;
  setBorder(edge: Edge, borderWidth: number): void;
  setDisplay(display: Display): void;
  setFlex(flex: number): void;
  setFlexBasis(flexBasis: number | 'auto' | `${number}%`): void;
  setFlexBasisPercent(flexBasis: number): void;
  setFlexBasisAuto(): void;
  setFlexDirection(flexDirection: FlexDirection): void;
  setFlexGrow(flexGrow: number): void;
  setFlexShrink(flexShrink: number): void;
  setFlexWrap(flexWrap: Wrap): void;
  setHeight(height: number | 'auto' | `${number}%`): void;
  setIsReferenceBaseline(isReferenceBaseline: boolean): void;
  setHeightAuto(): void;
  setHeightPercent(height: number): void;
  setJustifyContent(justifyContent: Justify): void;
  setGap(gutter: Gutter, gapLength: number): Value;
  setMargin(edge: Edge, margin: number | 'auto' | `${number}%`): void;
  setMarginAuto(edge: Edge): void;
  setMarginPercent(edge: Edge, margin: number): void;
  setMaxHeight(maxHeight: number | `${number}%`): void;
  setMaxHeightPercent(maxHeight: number): void;
  setMaxWidth(maxWidth: number | `${number}%`): void;
  setMaxWidthPercent(maxWidth: number): void;
  setDirtiedFunc(dirtiedFunc: DirtiedFunction | null): void;
  setMeasureFunc(measureFunc: MeasureFunction | null): void;
  setMinHeight(minHeight: number | `${number}%`): void;
  setMinHeightPercent(minHeight: number): void;
  setMinWidth(minWidth: number | `${number}%`): void;
  setMinWidthPercent(minWidth: number): void;
  setOverflow(overflow: Overflow): void;
  setPadding(edge: Edge, padding: number | `${number}%`): void;
  setPaddingPercent(edge: Edge, padding: number): void;
  setPosition(edge: Edge, position: number | `${number}%`): void;
  setPositionPercent(edge: Edge, position: number): void;
  setPositionType(positionType: PositionType): void;
  setWidth(width: number | 'auto' | `${number}%`): void;
  setWidthAuto(): void;
  setWidthPercent(width: number): void;
  unsetDirtiedFunc(): void;
  unsetMeasureFunc(): void;
};

export type Yoga = {
  Config: {
    create(): Config;
    destroy(config: Config): void;
  };
  Node: {
    create(config?: Config): Node;
    createDefault(): Node;
    createWithConfig(config: Config): Node;
    destroy(node: Node): void;
  };
} & typeof YGEnums;

// eslint-disable-next-line @typescript-eslint/no-explicit-any
export default function wrapAssembly(lib: any): Yoga {
  function patch(prototype, name, fn) {
    const original = prototype[name];

    prototype[name] = function (...args) {
      return fn.call(this, original, ...args);
    };
  }

  for (const fnName of [
    'setPosition',
    'setMargin',
    'setFlexBasis',
    'setWidth',
    'setHeight',
    'setMinWidth',
    'setMinHeight',
    'setMaxWidth',
    'setMaxHeight',
    'setPadding',
  ]) {
    const methods = {
      [Unit.Point]: lib.Node.prototype[fnName],
      [Unit.Percent]: lib.Node.prototype[`${fnName}Percent`],
      [Unit.Auto]: lib.Node.prototype[`${fnName}Auto`],
    };

    patch(lib.Node.prototype, fnName, function (original, ...args) {
      // We patch all these functions to add support for the following calls:
      // .setWidth(100) / .setWidth("100%") / .setWidth(.getWidth()) / .setWidth("auto")

      const value = args.pop();
      let unit, asNumber;

      if (value === 'auto') {
        unit = Unit.Auto;
        asNumber = undefined;
      } else if (typeof value === 'object') {
        unit = value.unit;
        asNumber = value.valueOf();
      } else {
        unit =
          typeof value === 'string' && value.endsWith('%')
            ? Unit.Percent
            : Unit.Point;
        asNumber = parseFloat(value);
        if (!Number.isNaN(value) && Number.isNaN(asNumber)) {
          throw new Error(`Invalid value ${value} for ${fnName}`);
        }
      }

      if (!methods[unit])
        throw new Error(
          `Failed to execute "${fnName}": Unsupported unit '${value}'`,
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
        const {width, height} = measureFunction(...args);
        return {
          width: width ?? NaN,
          height: height ?? NaN,
        };
      },
    });
  }

  patch(lib.Node.prototype, 'setMeasureFunc', function (original, measureFunc) {
    // This patch is just a convenience patch, since it helps write more
    // idiomatic source code (such as .setMeasureFunc(null))
    if (measureFunc) {
      return original.call(this, wrapMeasureFunction(measureFunc));
    } else {
      return this.unsetMeasureFunc();
    }
  });

  function wrapDirtiedFunc(dirtiedFunction) {
    return lib.DirtiedCallback.implement({dirtied: dirtiedFunction});
  }

  patch(lib.Node.prototype, 'setDirtiedFunc', function (original, dirtiedFunc) {
    original.call(this, wrapDirtiedFunc(dirtiedFunc));
  });

  patch(lib.Config.prototype, 'free', function () {
    // Since we handle the memory allocation ourselves (via lib.Config.create),
    // we also need to handle the deallocation
    lib.Config.destroy(this);
  });

  patch(lib.Node, 'create', (_, config) => {
    // We decide the constructor we want to call depending on the parameters
    return config
      ? lib.Node.createWithConfig(config)
      : lib.Node.createDefault();
  });

  patch(lib.Node.prototype, 'free', function () {
    // Since we handle the memory allocation ourselves (via lib.Node.create),
    // we also need to handle the deallocation
    lib.Node.destroy(this);
  });

  patch(lib.Node.prototype, 'freeRecursive', function () {
    for (let t = 0, T = this.getChildCount(); t < T; ++t) {
      this.getChild(0).freeRecursive();
    }
    this.free();
  });

  patch(
    lib.Node.prototype,
    'calculateLayout',
    function (original, width = NaN, height = NaN, direction = Direction.LTR) {
      // Just a small patch to add support for the function default parameters
      return original.call(this, width, height, direction);
    },
  );

  return {
    Config: lib.Config,
    Node: lib.Node,
    ...YGEnums,
  };
}
