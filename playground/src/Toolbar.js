// @flow
import React, {Component} from 'react';
import {Icon} from 'antd';
import './Toolbar.css';

type Props = {
  onShowCode?: () => void,
};

export default class Toolbar extends Component<Props> {
  render() {
    return (
      <div className="Toolbar">
        <img
          src="https://facebook.github.io/yoga/static/logo.svg"
          width="42"
          alt="Yoga logo"
        />
        <h1>Yoga Playground</h1>
        <div className="ToolbarSpacer" />
        {this.props.onShowCode && (
          <a className="ToolbarToggle" onClick={this.props.onShowCode}>
            <Icon type={'code-o'} />
            Code
          </a>
        )}
      </div>
    );
  }
}
