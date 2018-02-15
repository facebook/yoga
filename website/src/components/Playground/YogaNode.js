/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 * @flow
 * @format
 */

import React, {Component} from 'react';
import yoga, {Node} from 'yoga-layout/dist/entry-browser';
import PositionGuide from './PositionGuide';
import PositionRecord from './PositionRecord';
import type {LayoutRecordT} from './LayoutRecord';
import type {Yoga$Direction} from 'yoga-layout';

import './YogaNode.css';

type Yoga$Node = any;

type ComputedLayout = {|
  left: number,
  top: number,
  width: number,
  height: number,
  children: Array<ComputedLayout>,
  node: Yoga$Node,
|};

type Props = {|
  layoutDefinition: LayoutRecordT,
  className?: string,
  computedLayout?: ComputedLayout,
  path: Array<number>,
  selectedNodePath?: ?Array<number>,
  direction?: Yoga$Direction,
  label?: string,
  showGuides: boolean,
  onClick?: (path: Array<number>) => void,
  onDoubleClick?: (path: Array<number>) => void,
|};

type State = {
  visible?: boolean,
};

export default class YogaNode extends Component<Props, State> {
  node: Yoga$Node;

  static defaultProps = {
    path: [],
    label: 'root',
    showGuides: true,
  };

  state = {};
  computedLayout: ?ComputedLayout;
  rootNode: ?Yoga$Node;

  constructor(props: Props) {
    super();
    if (!props.computedLayout) {
      // is root node
      this.calculateLayout(props);
      this.state = {
        visible: !Boolean(props.computedLayout),
      };
    }
  }

  componentDidMount() {
    setTimeout(() => this.setState({visible: true}), 200);
  }

  componentWillReceiveProps(nextProps: Props) {
    if (
      !nextProps.computedLayout &&
      (!this.props.layoutDefinition.equals(nextProps.layoutDefinition) ||
        this.props.direction !== nextProps.direction)
    ) {
      // is root node and the layout definition or settings changed
      this.calculateLayout(nextProps);
    }
  }

  componentWillUnmount() {
    if (this.rootNode) {
      this.rootNode.freeRecursive();
    }
  }

  calculateLayout(props: Props) {
    const root = this.createYogaNodes(props.layoutDefinition);
    root.calculateLayout(
      props.layoutDefinition.width,
      props.layoutDefinition.height,
      props.direction,
    );
    this.computedLayout = this.getComputedLayout(root);
    this.rootNode = root;
  }

  createYogaNodes = (layoutDefinition: LayoutRecordT): Yoga$Node => {
    const root = Node.create();
    root.setWidth(layoutDefinition.width);
    root.setHeight(layoutDefinition.height);
    root.setMinWidth(layoutDefinition.minWidth);
    root.setMaxWidth(layoutDefinition.maxWidth);
    root.setMinHeight(layoutDefinition.minHeight);
    root.setMaxHeight(layoutDefinition.maxHeight);
    root.setJustifyContent(layoutDefinition.justifyContent);
    root.setAlignItems(layoutDefinition.alignItems);
    root.setAlignSelf(layoutDefinition.alignSelf);
    root.setAlignContent(layoutDefinition.alignContent);
    root.setFlexGrow(layoutDefinition.flexGrow);
    root.setFlexShrink(layoutDefinition.flexShrink);

    root.setPadding(yoga.EDGE_TOP, layoutDefinition.padding.top);
    root.setPadding(yoga.EDGE_RIGHT, layoutDefinition.padding.right);
    root.setPadding(yoga.EDGE_BOTTOM, layoutDefinition.padding.bottom);
    root.setPadding(yoga.EDGE_LEFT, layoutDefinition.padding.left);

    root.setBorder(yoga.EDGE_TOP, layoutDefinition.border.top);
    root.setBorder(yoga.EDGE_RIGHT, layoutDefinition.border.right);
    root.setBorder(yoga.EDGE_BOTTOM, layoutDefinition.border.bottom);
    root.setBorder(yoga.EDGE_LEFT, layoutDefinition.border.left);

    root.setMargin(yoga.EDGE_TOP, layoutDefinition.margin.top);
    root.setMargin(yoga.EDGE_RIGHT, layoutDefinition.margin.right);
    root.setMargin(yoga.EDGE_BOTTOM, layoutDefinition.margin.bottom);
    root.setMargin(yoga.EDGE_LEFT, layoutDefinition.margin.left);

    root.setPosition(yoga.EDGE_TOP, layoutDefinition.position.top);
    root.setPosition(yoga.EDGE_RIGHT, layoutDefinition.position.right);
    root.setPosition(yoga.EDGE_BOTTOM, layoutDefinition.position.bottom);
    root.setPosition(yoga.EDGE_LEFT, layoutDefinition.position.left);

    root.setPositionType(layoutDefinition.positionType);

    root.setDisplay(yoga.DISPLAY_FLEX);
    root.setAspectRatio(layoutDefinition.aspectRatio);
    root.setFlexWrap(layoutDefinition.flexWrap);
    root.setFlexDirection(layoutDefinition.flexDirection);
    (layoutDefinition.children || [])
      .map(this.createYogaNodes)
      .forEach((node, i) => {
        root.insertChild(node, i);
      });

    return root;
  };

  getComputedLayout = (node: Yoga$Node): ComputedLayout => {
    return {
      ...node.getComputedLayout(),
      node,
      children: Array.apply(null, Array(node.getChildCount())).map((_, i) =>
        this.getComputedLayout(node.getChild(i)),
      ),
    };
  };

  onClick = (e: SyntheticMouseEvent<>) => {
    const {onClick} = this.props;
    if (onClick) {
      e.stopPropagation();
      onClick(this.props.path);
    }
  };

  onDoubleClick = (e: SyntheticMouseEvent<>) => {
    const {onDoubleClick} = this.props;
    if (onDoubleClick) {
      e.stopPropagation();
      onDoubleClick(this.props.path);
    }
  };

  showPositionGuides({node}: ComputedLayout) {
    const padding = PositionRecord({
      top: node.getComputedPadding(yoga.EDGE_TOP),
      left: node.getComputedPadding(yoga.EDGE_LEFT),
      right: node.getComputedPadding(yoga.EDGE_RIGHT),
      bottom: node.getComputedPadding(yoga.EDGE_BOTTOM),
    });
    const border = PositionRecord({
      top: node.getComputedBorder(yoga.EDGE_TOP),
      left: node.getComputedBorder(yoga.EDGE_LEFT),
      right: node.getComputedBorder(yoga.EDGE_RIGHT),
      bottom: node.getComputedBorder(yoga.EDGE_BOTTOM),
    });
    const margin = PositionRecord({
      top: node.getComputedMargin(yoga.EDGE_TOP),
      left: node.getComputedMargin(yoga.EDGE_LEFT),
      right: node.getComputedMargin(yoga.EDGE_RIGHT),
      bottom: node.getComputedMargin(yoga.EDGE_BOTTOM),
    });
    const position = PositionRecord({
      top: node.getPosition(yoga.EDGE_TOP).value,
      left: node.getPosition(yoga.EDGE_LEFT).value,
      right: node.getPosition(yoga.EDGE_RIGHT).value,
      bottom: node.getPosition(yoga.EDGE_BOTTOM).value,
    });

    return [
      <PositionGuide
        key="border"
        inset
        position={border}
        color="rgba(251, 170, 51, 0.15)"
        reverse={node.getFlexWrap() === yoga.WRAP_WRAP_REVERSE}
      />,
      <PositionGuide
        key="padding"
        inset
        offset={border}
        position={padding}
        color="rgba(123, 179, 41, 0.1)"
        reverse={node.getFlexWrap() === yoga.WRAP_WRAP_REVERSE}
      />,
      <PositionGuide
        key="margin"
        position={margin}
        color="rgba(214, 43, 28, 0.1)"
      />,
      <PositionGuide
        key="position"
        offset={margin}
        position={position}
        color="rgba(115, 51, 205, 0.1)"
      />,
    ];
  }

  render() {
    const {
      layoutDefinition,
      className,
      path,
      selectedNodePath,
      label,
    } = this.props;

    // $FlowFixMe
    const computedLayout: ComputedLayout =
      this.props.computedLayout || this.computedLayout;
    const {left, top, width, height, children} = computedLayout;

    const isFocused = selectedNodePath && selectedNodePath.length === 0;

    return (
      <div
        className={`YogaNode ${isFocused ? 'focused' : ''} ${className || ''} ${
          this.state.visible ? '' : 'invisible'
        }`}
        style={path.length == 0 ? {width, height} : {left, top, width, height}}
        onDoubleClick={this.onDoubleClick}
        onClick={this.onClick}>
        {label && <div className="label">{label}</div>}
        {isFocused &&
          this.props.showGuides &&
          this.showPositionGuides(computedLayout)}
        {(children || []).map((child: ComputedLayout, i) => (
          <YogaNode
            key={i}
            computedLayout={child}
            label={String(i + 1)}
            layoutDefinition={layoutDefinition.children.get(i)}
            selectedNodePath={
              selectedNodePath &&
              selectedNodePath.length > 0 &&
              selectedNodePath[0] === i
                ? selectedNodePath.slice(1)
                : null
            }
            path={path.concat(i)}
            onClick={this.props.onClick}
            onDoubleClick={this.props.onDoubleClick}
            showGuides={this.props.showGuides}
          />
        ))}
      </div>
    );
  }
}
