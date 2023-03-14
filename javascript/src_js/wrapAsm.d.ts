/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import type {
  Align,
  Direction,
  Display,
  Edge,
  ExperimentalFeature,
  FlexDirection,
  Gutter,
  Justify,
  MeasureMode,
  Overflow,
  PositionType,
  Unit,
  Wrap,
} from "./generated/YGEnums";

import type * as YGEnums from "./generated/YGEnums";

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
    enabled: boolean
  ): void;
  setPointScaleFactor(factor: number): void;
  useLegacyStretchBehaviour(): boolean;
  setUseLegacyStretchBehaviour(useLegacyStretchBehaviour: boolean): void;
  useWebDefaults(): boolean;
  setUseWebDefaults(useWebDefaults: boolean): void;
};

export type MeasureFunction = (
  width: number,
  widthMode: MeasureMode,
  height: number,
  heightMode: MeasureMode
) => Size;

export type Node = {
  calculateLayout(width?: number, height?: number, direction?: Direction): void;
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
  setFlexBasis(flexBasis: number | "auto" | `${number}%`): void;
  setFlexBasisPercent(flexBasis: number): void;
  setFlexBasisAuto(): void;
  setFlexDirection(flexDirection: FlexDirection): void;
  setFlexGrow(flexGrow: number): void;
  setFlexShrink(flexShrink: number): void;
  setFlexWrap(flexWrap: Wrap): void;
  setHeight(height: number | "auto" | `${number}%`): void;
  setHeightAuto(): void;
  setHeightPercent(height: number): void;
  setJustifyContent(justifyContent: Justify): void;
  setGap(gutter: Gutter, gapLength: number): Value;
  setMargin(edge: Edge, margin: number | "auto" | `${number}%`): void;
  setMarginAuto(edge: Edge): void;
  setMarginPercent(edge: Edge, margin: number): void;
  setMaxHeight(maxHeight: number | `${number}%`): void;
  setMaxHeightPercent(maxHeight: number): void;
  setMaxWidth(maxWidth: number | `${number}%`): void;
  setMaxWidthPercent(maxWidth: number): void;
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
  setWidth(width: number | "auto" | `${number}%`): void;
  setWidthAuto(): void;
  setWidthPercent(width: number): void;
  unsetMeasureFunc(): void;
};

export type Yoga = {
  Config: {
    create(): Config;
    destroy(config: Config): any;
  };
  Node: {
    create(): Node;
    createDefault(): Node;
    createWithConfig(config: Config): Node;
    destroy(node: Node): any;
  };
} & typeof YGEnums;

declare const wrapAsm: () => Yoga;
export default wrapAsm;
