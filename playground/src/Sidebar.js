// @flow
import React, {Component} from 'react';
import {Icon} from 'antd';
import './Sidebar.css';

type Props = {
  onClose?: () => void,
  width?: number,
  children: any,
};

export default class Sidebar extends Component<Props> {
  render() {
    return (
      <div
        className={`Sidebar ${this.props.visible ? 'visible' : ''}`}
        style={{width: this.props.width}}>
        {this.props.onClose && (
          <div className="SidebarClose">
            <Icon type="close" onClick={this.props.onClose} />
          </div>
        )}
        {this.props.children}
      </div>
    );
  }
}
