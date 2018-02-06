// @flow
import React, {Component} from 'react';
import yoga from 'yoga-layout';
import YogaNode from './YogaNode';
import Editor from './Editor';
import {List, setIn} from 'immutable';
import PositionRecord from './PositionRecord';
import LayoutRecord from './LayoutRecord';
import Toolbar from './Toolbar';
import Code from './Code';
import Sidebar from './Sidebar';
import type {LayoutRecordT} from './LayoutRecord';
import type {Yoga$Direction} from 'yoga-layout';
import './Playground.css';

type Props = {
  layoutDefinition: LayoutRecordT,
  direction: Yoga$Direction,
  maxDepth: number,
  maxChildren?: number,
  minChildren?: number,
};
type State = {
  selectedNodePath: ?Array<number>,
  layoutDefinition: LayoutRecordT,
  direction: Yoga$Direction,
  showCode: boolean,
};

function getPath(path: Array<number>): Array<mixed> {
  return path.reduce((acc, cv) => acc.concat('children', cv), []);
}

export default class App extends Component<Props, State> {
  _containerRef: ?HTMLElement;

  static defaultProps = {
    layoutDefinition: LayoutRecord({
      width: 800,
      height: 400,
      justifyContent: yoga.JUSTIFY_SPACE_BETWEEN,
      alignItems: yoga.ALIGN_FLEX_START,
      children: List([LayoutRecord(), LayoutRecord()]),
      padding: PositionRecord({
        left: '10',
        top: '10',
        right: '10',
        bottom: '10',
      }),
      margin: PositionRecord({
        left: '20',
        top: '70',
      }),
    }),
    direction: yoga.DIRECTION_LTR,
    maxDepth: 3,
    showCode: false,
  };

  state = {
    selectedNodePath: null,
    layoutDefinition: this.props.layoutDefinition,
    direction: this.props.direction,
    showCode: false,
  };

  componentDidMount() {
    document.addEventListener('keydown', this.onKeyDown);

    // rehydrate
    if (window.location.hash && window.location.hash.length > 1) {
      try {
        const restoredState = JSON.parse(atob(window.location.hash.substr(1)));
        this.setState({layoutDefinition: this.rehydrate(restoredState)});
      } catch (e) {
        window.location.hash = '';
      }
    }
  }

  componentWillUnmount() {
    document.removeEventListener('keydown', this.onKeyDown);
  }

  rehydrate = (node: Object): LayoutRecord => {
    let record = LayoutRecord(node);
    record = record.set('padding', PositionRecord(record.padding));
    record = record.set('border', PositionRecord(record.border));
    record = record.set('margin', PositionRecord(record.margin));
    record = record.set('position', PositionRecord(record.position));
    record = record.set('children', List(record.children.map(this.rehydrate)));
    return record;
  };

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
    this.setState({
      selectedNodePath: null,
      showCode: false,
    });
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
      const updatedChildren = layoutDefinition.getIn(path).push(LayoutRecord());
      this.modifyAtPath(
        path,
        updatedChildren,
        selectedNodePath.concat(updatedChildren.size - 1),
      );
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

    window.location.hash = btoa(
      JSON.stringify(this.removeUnchangedProperties(layoutDefinition)),
    );
  }

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

  onToggleCode = () => {
    this.setState({
      selectedNodePath: this.state.showCode
        ? this.state.selectedNodePath
        : null,
      showCode: !this.state.showCode,
    });
  };

  render() {
    const {layoutDefinition, selectedNodePath} = this.state;

    const selectedNode: ?LayoutRecordT = selectedNodePath
      ? layoutDefinition.getIn(getPath(selectedNodePath))
      : null;

    return (
      <div
        className="App"
        onMouseDown={this.onMouseDown}
        ref={ref => {
          this._containerRef = ref;
        }}>
        <Toolbar
          onShowCode={
            !this.state.showCode
              ? () => this.setState({selectedNodePath: null, showCode: true})
              : undefined
          }
        />
        <YogaNode
          layoutDefinition={layoutDefinition}
          selectedNodePath={selectedNodePath}
          onClick={selectedNodePath =>
            this.setState({selectedNodePath, showCode: false})
          }
          onDoubleClick={this.onAdd}
          direction={this.state.direction}
        />
        <Sidebar visible={Boolean(selectedNodePath) && !this.state.showCode}>
          <Editor
            node={selectedNode}
            selectedNodeIsRoot={
              selectedNodePath ? selectedNodePath.length === 0 : false
            }
            onChangeLayout={this.onChangeLayout}
            onChangeSetting={(key, value) => this.setState({[key]: value})}
            direction={this.state.direction}
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
        </Sidebar>
        <Sidebar
          width={500}
          visible={this.state.showCode}
          onClose={() => this.setState({showCode: false})}>
          <Code
            layoutDefinition={layoutDefinition}
            direction={this.state.direction}
          />
        </Sidebar>
      </div>
    );
  }
}
