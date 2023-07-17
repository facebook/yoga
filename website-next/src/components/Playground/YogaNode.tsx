/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import React, {Component} from 'react';
import Yoga from 'yoga-layout/sync';
import PositionGuide from './PositionGuide';
import PositionRecord from './PositionRecord';
import LayoutRecord from './LayoutRecord';
import type {LayoutRecordType} from './LayoutRecord';
import {Direction, Display, Edge, Node, Wrap} from 'yoga-layout/sync';

import './YogaNode.css';

type ComputedLayout = {
  left: number;
  top: number;
  width: number;
  height: number;
  children: Array<ComputedLayout>;
  node: Node;
};

type Props = {
  layoutDefinition: LayoutRecordType;
  className?: string;
  computedLayout?: ComputedLayout;
  path: Array<number>;
  selectedNodePath?: Array<number>;
  direction?: Direction;
  label?: string;
  showGuides: boolean;
  onClick?: (path: Array<number>) => void;
  onDoubleClick?: (path: Array<number>) => void;
};

type State = {
  visible?: boolean;
  hovered: boolean;
};

export default class YogaNode extends Component<Props, State> {
  node: Node;
  _ref: HTMLDivElement;

  static defaultProps = {
    path: [],
    label: 'root',
    showGuides: true,
  };

  state = {
    hovered: false,
    visible: false,
  };
  computedLayout?: ComputedLayout;
  rootNode?: Node;

  constructor(props: Props) {
    super(props);
    if (!props.computedLayout) {
      // is root node
      this.calculateLayout(props);
      this.state = {
        hovered: false,
        visible: !props.computedLayout,
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

  onMouseMove = e => {
    this.setState({hovered: e.target === this._ref});
  };

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

  createYogaNodes = (layoutDefinition: LayoutRecordType): Node => {
    const root = Yoga.Node.create();

    const defaultLayout = LayoutRecord({});
    [
      'width',
      'height',
      'minWidth',
      'maxWidth',
      'minHeight',
      'maxHeight',
      'justifyContent',
      'alignItems',
      'alignSelf',
      'alignContent',
      'flexGrow',
      'flexShrink',
      'positionType',
      'aspectRatio',
      'flexWrap',
      'flexDirection',
    ].forEach(key => {
      try {
        const value =
          layoutDefinition[key] === ''
            ? defaultLayout[key]
            : layoutDefinition[key];
        root[`set${key[0].toUpperCase()}${key.substr(1)}`](value);
      } catch (e) {
        // Do nothing on failure
      }
    });

    ['padding', 'margin', 'position', 'border'].forEach(key => {
      ['top', 'right', 'bottom', 'left'].forEach(direction => {
        try {
          root[`set${key[0].toUpperCase()}${key.substr(1)}`](
            Yoga[`EDGE_${direction.toUpperCase()}`],
            layoutDefinition[key][direction],
          );
        } catch (e) {
          // Do nothing on failure
        }
      });
    });

    root.setDisplay(Display.Flex);

    (layoutDefinition.children || [])
      .map(this.createYogaNodes)
      .forEach((node, i) => {
        root.insertChild(node, i);
      });
    return root;
  };

  getComputedLayout = (node: Node): ComputedLayout => {
    return {
      ...node.getComputedLayout(),
      node,
      children: Array(node.getChildCount()).map((_, i) =>
        this.getComputedLayout(node.getChild(i)),
      ),
    };
  };

  onClick = (e: React.MouseEvent) => {
    const {onClick} = this.props;
    if (onClick) {
      e.stopPropagation();
      onClick(this.props.path);
    }
  };

  onDoubleClick = (e: React.MouseEvent) => {
    const {onDoubleClick} = this.props;
    if (onDoubleClick) {
      e.stopPropagation();
      onDoubleClick(this.props.path);
    }
  };

  onMouseLeave = (_e: React.MouseEvent) => this.setState({hovered: false});

  showPositionGuides({node}: ComputedLayout) {
    const padding = PositionRecord({
      top: node.getComputedPadding(Edge.Top),
      left: node.getComputedPadding(Edge.Left),
      right: node.getComputedPadding(Edge.Right),
      bottom: node.getComputedPadding(Edge.Bottom),
    });
    const border = PositionRecord({
      top: node.getComputedBorder(Edge.Top),
      left: node.getComputedBorder(Edge.Left),
      right: node.getComputedBorder(Edge.Right),
      bottom: node.getComputedBorder(Edge.Bottom),
    });
    const margin = PositionRecord({
      top: node.getComputedMargin(Edge.Top),
      left: node.getComputedMargin(Edge.Left),
      right: node.getComputedMargin(Edge.Right),
      bottom: node.getComputedMargin(Edge.Bottom),
    });
    const position = PositionRecord({
      top: node.getPosition(Edge.Top).value,
      left: node.getPosition(Edge.Left).value,
      right: node.getPosition(Edge.Right).value,
      bottom: node.getPosition(Edge.Bottom).value,
    });

    return [
      <PositionGuide
        key="border"
        inset
        position={border}
        color="rgba(251, 170, 51, 0.15)"
        reverse={node.getFlexWrap() === Wrap.WrapReverse}
      />,
      <PositionGuide
        key="padding"
        inset
        offset={border}
        position={padding}
        color="rgba(123, 179, 41, 0.1)"
        reverse={node.getFlexWrap() === Wrap.WrapReverse}
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
    const {layoutDefinition, className, path, selectedNodePath, label} =
      this.props;

    const computedLayout: ComputedLayout =
      this.props.computedLayout || this.computedLayout;
    const {left, top, width, height, children} = computedLayout;

    const isFocused = selectedNodePath && selectedNodePath.length === 0;

    return (
      <div
        className={`YogaNode ${isFocused ? 'focused' : ''} ${className || ''} ${
          this.state.visible ? '' : 'invisible'
        } ${this.state.hovered ? 'hover' : ''}`}
        style={path.length == 0 ? {width, height} : {left, top, width, height}}
        onDoubleClick={this.onDoubleClick}
        onMouseMove={this.onMouseMove}
        onMouseLeave={this.onMouseLeave}
        ref={ref => {
          this._ref = ref;
        }}
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
