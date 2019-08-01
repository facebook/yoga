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
import ReactDOM from 'react-dom';
import EditValue from '../components/Playground/src/EditValue';
import Link from 'gatsby-link';
import './DocsSidebar.css';
import type {LayoutRecordT} from './Playground/src/LayoutRecord';

const TAG_PATTERN = /<controls prop="([A-Za-z]+)"><\/controls>/gi;

type Props = {
  markdown: string,
  onChange: (property: string, value: any) => void,
  layout: LayoutRecordT,
};

export default class DocsSidebar extends Component<Props> {
  componentDidMount() {
    this.renderControls(this.props);
  }

  componentWillReceiveProps(nextProps: Props) {
    this.renderControls(nextProps);
  }

  renderControls = (props: Props) => {
    let match;
    while ((match = TAG_PATTERN.exec(props.markdown))) {
      const prop = match[1];
      const element = window.document.querySelector(
        `controls[prop="${match[1]}"]`,
      );

      if (element) {
        if (element.childNodes.length !== 0) {
          console.warn(
            `The element <controls type="${prop}"> is not empty. It's content will be replaced by the react-component mounted in this element.`,
          );
        }
        ReactDOM.render(
          <EditValue
            property={prop}
            value={props.layout[prop]}
            onChange={(property, value) => {
              if (window.ga) {
                window.ga('send', {
                  hitType: 'event',
                  eventCategory: 'DocsSidebar',
                  eventAction: 'valueChanged',
                  eventLabel: prop,
                });
              }
              props.onChange(property, value);
            }}
          />,
          element,
        );
      }
    }
  };

  render() {
    return (
      <div className="DocsSidebar">
        <div
          className="markdown"
          dangerouslySetInnerHTML={{__html: this.props.markdown}}
        />
        <Link to="/docs" className="overview">
          BACK TO OVERVIEW
        </Link>
      </div>
    );
  }
}
