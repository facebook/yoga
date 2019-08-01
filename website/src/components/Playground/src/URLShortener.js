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
import {Tooltip, notification, Button, Input} from 'antd';
import './URLShortener.css';

type State = {
  shortURL: ?string,
  loading: boolean,
};

export default class URLShortener extends Component<{}, State> {
  _ref: ?HTMLElement = null;

  state = {
    loading: false,
    shortURL: null,
  };

  componentDidMount() {
    window.addEventListener('popstate', this.onHashChange);
  }

  componentWillUnmount() {
    window.removeEventListener('popstate', this.onHashChange);
  }

  onHashChange = () => {
    this.setState({shortURL: null});
  };

  onClick = () => {
    this.setState(
      {
        loading: true,
      },
      () => {
        if (window.ga) {
          window.ga('send', {
            hitType: 'event',
            eventCategory: 'URLShortener',
            eventAction: 'created',
          });
        }

        fetch(
          `https://cors-anywhere.herokuapp.com/tinyurl.com/api-create.php?url=${
            window.location.href
          }`,
        )
          .then(res => res.text())
          .then(shortURL => this.setState({shortURL, loading: false}))
          .catch(() => this.setState({shortURL: null, loading: false}));
      },
    );
  };

  render() {
    return this.state.shortURL ? (
      <Input
        value={this.state.shortURL}
        autoFocus
        ref={ref => {
          if (ref) {
            ref.input.select();
          }
        }}
      />
    ) : (
      <Button
        className="URLShortener"
        onClick={this.onClick}
        icon="share-alt"
        disabled={this.state.loading}
        type="primary">
        Share URL
      </Button>
    );
  }
}
