/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import React, {Component} from 'react';
import {Direction} from 'yoga-layout';
import YogaNode from './YogaNode';
import Editor from './Editor';
import {List, setIn} from 'immutable';
import PositionRecord from './PositionRecord';
import LayoutRecord from './LayoutRecord';
import Sidebar from './Sidebar';
import type {LayoutRecordType} from './LayoutRecord';
import styles from './Playground.module.css';
import clsx from 'clsx';

type Props = {
  layoutDefinition?: LayoutRecordType;
  direction?: Direction;
  maxDepth?: number;
  maxChildren?: number;
  minChildren?: number;
  selectedNodePath?: Array<number>;
  showGuides?: boolean;
  className?: string;
  height?: string | number;
  persist?: boolean;
  renderSidebar?: (
    layoutDefinition: LayoutRecordType,
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    onChange: () => any,
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
  ) => any;
};

type State = {
  selectedNodePath?: Array<number>;
  layoutDefinition: LayoutRecordType;
  direction: Direction;
};

function getPath(path: Array<number>): Array<unknown> {
  return path.reduce((acc, cv) => acc.concat('children', cv), []);
}

export default class Playground extends Component<Props, State> {
  _containerRef?: HTMLElement;

  static defaultProps = {
    layoutDefinition: {
      width: 500,
      height: 500,
      children: [
        {width: 100, height: 100},
        {width: 100, height: 100},
        {width: 100, height: 100},
      ],
    },
    direction: Direction.LTR,
    maxDepth: 3,
    showGuides: true,
    persist: false,
  };

  rehydrate = (node: LayoutRecordType): LayoutRecordType => {
    let record = LayoutRecord(node);
    record = record.set('padding', PositionRecord(record.padding));
    record = record.set('border', PositionRecord(record.border));
    record = record.set('margin', PositionRecord(record.margin));
    record = record.set('position', PositionRecord(record.position));
    record = record.set('children', List(record.children.map(this.rehydrate)));
    return record;
  };

  state = {
    selectedNodePath: this.props.selectedNodePath,
    layoutDefinition: this.rehydrate(this.props.layoutDefinition),
    direction: this.props.direction,
  };

  componentDidMount() {
    document.addEventListener('keydown', this.onKeyDown);

    // rehydrate
    if (window.location.search && window.location.search.length > 1) {
      try {
        const restoredState = JSON.parse(
          atob(window.location.search.substr(1)),
        );
        this.setState({layoutDefinition: this.rehydrate(restoredState)});
      } catch (e) {
        window.history.replaceState(
          {},
          null,
          window.location.origin + window.location.pathname,
        );
      }
    }
  }

  componentWillUnmount() {
    document.removeEventListener('keydown', this.onKeyDown);
  }

  onKeyDown = (e: KeyboardEvent) => {
    if (e.key === 'Escape') {
      this.hideSidePanes();
    }
  };

  onMouseDown = (e: React.MouseEvent) => {
    if (e.target === this._containerRef) {
      this.hideSidePanes();
    }
  };

  hideSidePanes() {
    if (!this.props.renderSidebar) {
      // only unselect if we don't have an external sidebar, otherwise the
      // sidebar may rely on a certain node to be selected
      this.setState({
        selectedNodePath: null,
      });
    }
  }

  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  onChangeLayout = (key: string, value: any) => {
    const {selectedNodePath} = this.state;
    if (selectedNodePath) {
      this.modifyAtPath([...getPath(selectedNodePath), key], value);
    }
  };

  onRemove = () => {
    const {selectedNodePath, layoutDefinition} = this.state;
    if (selectedNodePath) {
      const index = selectedNodePath.pop();
      const path = getPath(selectedNodePath).concat('children');
      // @ts-ignore
      const updatedChildren = layoutDefinition.getIn(path).delete(index);
      this.modifyAtPath(path, updatedChildren);
      this.setState({selectedNodePath: null});
    }
  };

  onAdd = () => {
    const {selectedNodePath, layoutDefinition} = this.state;
    if (selectedNodePath) {
      const path = getPath(selectedNodePath).concat('children');
      const updatedChildren = layoutDefinition
        .getIn(path)
        // @ts-ignore
        .push(LayoutRecord({width: 100, height: 100}));
      this.modifyAtPath(path, updatedChildren);
    }
  };

  modifyAtPath(
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    path: Array<any>,
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    value: any,
    selectedNodePath: Array<number> = this.state.selectedNodePath,
  ) {
    const layoutDefinition = setIn(this.state.layoutDefinition, path, value);
    this.setState({
      layoutDefinition,
      selectedNodePath,
    });

    if (this.props.persist) {
      window.history.replaceState(
        {},
        null,
        window.location.origin +
          window.location.pathname +
          '?' +
          this.getHash(layoutDefinition),
      );
    }
  }

  getHash = (
    layoutDefinition: LayoutRecordType = this.state.layoutDefinition,
  ): string =>
    btoa(JSON.stringify(this.removeUnchangedProperties(layoutDefinition)));

  removeUnchangedProperties = (
    node: LayoutRecordType,
  ): {children?: unknown} => {
    const untouchedLayout = LayoutRecord({});
    const untouchedPosition = PositionRecord({});
    const result: {children?: unknown} = {};
    if (!node.equals(untouchedLayout)) {
      Object.keys(node.toJS()).forEach(key => {
        if (key === 'children' && node.children.size > 0) {
          result.children = node.children
            .toJSON()
            .map(this.removeUnchangedProperties);
        } else if (
          node[key] instanceof PositionRecord &&
          !node[key].equals(untouchedPosition)
        ) {
          result[key] = {};
          Object.keys(untouchedPosition.toJS()).forEach(position => {
            if (node[key][position] !== untouchedPosition[position]) {
              result[key][position] = node[key][position];
            }
          });
        } else if (node[key] !== untouchedLayout[key]) {
          result[key] = node[key];
        }
      });
    }
    return result;
  };

  getChildrenCountForSelectedPath = (): number => {
    const selectedNode: LayoutRecordType = (
      this.state.selectedNodePath || []
    ).reduce(
      (node: LayoutRecordType, cv) => node.children.get(cv),
      this.state.layoutDefinition,
    );
    return selectedNode ? selectedNode.children.size : 0;
  };

  render() {
    const {layoutDefinition, selectedNodePath, direction} = this.state;
    const {height} = this.props;

    // @ts-ignore
    const selectedNode: LayoutRecordType | null = selectedNodePath
      ? layoutDefinition.getIn(getPath(selectedNodePath))
      : null;

    const playground = (
      <div
        className={styles.playground}
        onMouseDown={this.onMouseDown}
        style={{height, maxHeight: height}}
        ref={ref => {
          this._containerRef = ref;
        }}>
        <YogaNode
          layoutDefinition={layoutDefinition}
          selectedNodePath={selectedNodePath}
          onClick={selectedNodePath => this.setState({selectedNodePath})}
          onDoubleClick={this.onAdd}
          direction={direction}
          showGuides={this.props.showGuides}
        />
      </div>
    );

    const sidebarContent = this.props.renderSidebar
      ? this.props.renderSidebar(
          // @ts-ignore
          layoutDefinition.getIn(getPath(selectedNodePath)),
          this.onChangeLayout,
        )
      : this.state.selectedNodePath != null && (
          <Editor
            node={selectedNode}
            selectedNodeIsRoot={
              selectedNodePath ? selectedNodePath.length === 0 : false
            }
            onChangeLayout={this.onChangeLayout}
            onChangeSetting={(key, value) =>
              // @ts-ignore
              this.setState({[key]: value})
            }
            direction={direction}
            onRemove={
              selectedNodePath && selectedNodePath.length > 0
                ? this.onRemove
                : undefined
            }
            onAdd={
              selectedNodePath && selectedNodePath.length < this.props.maxDepth
                ? this.onAdd
                : undefined
            }
          />
        );

    return (
      <div className={clsx(styles.container, this.props.className)}>
        {playground}
        <Sidebar>{sidebarContent}</Sidebar>
      </div>
    );
  }
}
