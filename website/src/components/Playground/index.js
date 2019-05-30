/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

import React, {Component} from 'react';
import yoga from 'yoga-layout/dist/entry-browser';
import YogaNode from './YogaNode';
import CodeGenerators from './CodeGenerators';
import URLShortener from './URLShortener';
import Editor from './Editor';
import {List, setIn} from 'immutable';
import PositionRecord from './PositionRecord';
import LayoutRecord from './LayoutRecord';
import Sidebar from './Sidebar';
import {Row, Col, Button} from 'antd';
import btoa from 'btoa';
import type {LayoutRecordT} from './LayoutRecord';
import type {Yoga$Direction} from 'yoga-layout';
import './index.css';

type Props = {
  layoutDefinition: Object,
  direction: Yoga$Direction,
  maxDepth: number,
  maxChildren?: number,
  minChildren?: number,
  selectedNodePath?: Array<number>,
  showGuides: boolean,
  className?: string,
  height?: string | number,
  persist?: boolean,
  renderSidebar?: (layoutDefinition: LayoutRecordT, onChange: Function) => any,
};

type State = {
  selectedNodePath: ?Array<number>,
  layoutDefinition: LayoutRecordT,
  direction: Yoga$Direction,
};

function getPath(path: Array<number>): Array<mixed> {
  return path.reduce((acc, cv) => acc.concat('children', cv), []);
}

export default class Playground extends Component<Props, State> {
  _containerRef: ?HTMLElement;

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
    direction: yoga.DIRECTION_LTR,
    maxDepth: 3,
    showGuides: true,
    persist: false,
  };

  rehydrate = (node: Object): LayoutRecord => {
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

  onMouseDown = (e: MouseEvent) => {
    if (e.target === this._containerRef) {
      this.hideSidePanes();
    }
  };

  hideSidePanes() {
    if (!Boolean(this.props.renderSidebar)) {
      // only unselect if we don't have an external sidebar, otherwise the
      // sidebar may rely on a certain node to be selected
      this.setState({
        selectedNodePath: null,
      });
    }
  }

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
        .push(LayoutRecord({width: 100, height: 100}));
      this.modifyAtPath(path, updatedChildren);
    }
  };

  modifyAtPath(
    path: Array<any>,
    value: any,
    selectedNodePath?: ?Array<number> = this.state.selectedNodePath,
  ) {
    // $FlowFixMe
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
    layoutDefinition: LayoutRecordT = this.state.layoutDefinition,
  ): string =>
    btoa(JSON.stringify(this.removeUnchangedProperties(layoutDefinition)));

  removeUnchangedProperties = (node: LayoutRecordT): Object => {
    const untouchedLayout = LayoutRecord({});
    const untouchedPosition = PositionRecord({});
    const result = {};
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
    const selectedNode: ?LayoutRecordT = (
      this.state.selectedNodePath || []
    ).reduce(
      (node: LayoutRecordT, cv) => node.children.get(cv),
      this.state.layoutDefinition,
    );
    return selectedNode ? selectedNode.children.size : 0;
  };

  render() {
    const {layoutDefinition, selectedNodePath, direction} = this.state;
    const {height} = this.props;

    const selectedNode: ?LayoutRecordT = selectedNodePath
      ? layoutDefinition.getIn(getPath(selectedNodePath))
      : null;

    const playground = (
      <div
        className={`Playground ${this.props.renderSidebar ? '' : 'standalone'}`}
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
        {!this.props.renderSidebar && (
          <Sidebar>
            <div className="Actions">
              <Row gutter={15}>
                <Col span={12}>
                  <CodeGenerators
                    layoutDefinition={layoutDefinition}
                    direction={direction}
                  />
                </Col>
                <Col span={12}>
                  {this.props.persist ? (
                    <URLShortener />
                  ) : (
                    <Button
                      href={`/playground?${this.getHash()}`}
                      type="primary">
                      Open Playground
                    </Button>
                  )}
                </Col>
              </Row>
            </div>
            {this.state.selectedNodePath ? (
              <Editor
                node={selectedNode}
                selectedNodeIsRoot={
                  selectedNodePath ? selectedNodePath.length === 0 : false
                }
                onChangeLayout={this.onChangeLayout}
                onChangeSetting={(key, value) => this.setState({[key]: value})}
                direction={direction}
                onRemove={
                  selectedNodePath && selectedNodePath.length > 0
                    ? this.onRemove
                    : undefined
                }
                onAdd={
                  selectedNodePath &&
                  selectedNodePath.length < this.props.maxDepth
                    ? this.onAdd
                    : undefined
                }
              />
            ) : (
              <div className="NoContent">
                Select a node to edit its properties
              </div>
            )}
          </Sidebar>
        )}
      </div>
    );

    if (this.props.renderSidebar) {
      return (
        <div className={`PlaygroundContainer ${this.props.className || ''}`}>
          <div>
            {this.props.renderSidebar(
              layoutDefinition.getIn(getPath(selectedNodePath)),
              this.onChangeLayout,
            )}
          </div>
          {playground}
        </div>
      );
    } else {
      return playground;
    }
  }
}
