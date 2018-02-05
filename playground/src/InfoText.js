// @flow
import React, {Component} from 'react';
import {Popover, Icon} from 'antd';
import './InfoText.css';

type Props = {
  children: any,
};

export default class InfoText extends Component<Props> {
  render() {
    return (
      <Popover
        content={<div className="InfoText">{this.props.children}</div>}
        trigger="hover">
        <Icon className="InfoTextIcon" type="info-circle-o" />
      </Popover>
    );
  }
}
