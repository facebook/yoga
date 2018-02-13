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
import {Tooltip, notification, Button, Input} from 'antd';
import './URLShortener.css';

const API_KEY = 'AIzaSyCRvdtNY07SGUokChS8oA9EaYJafFL0zMI';

export default class URLShortener extends Component<{}> {
  _ref: ?HTMLElement = null;

  onClick = () => {
    fetch(`https://www.googleapis.com/urlshortener/v1/url?key=${API_KEY}`, {
      method: 'POST',
      headers: {
        Accept: 'application/json',
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        kind: 'urlshortener#url',
        longUrl: window.location.href,
      }),
    })
      .then(res => res.json())
      .then(({id}) => {
        notification.open({
          message: 'Created short URL',
          description: (
            <Input
              value={id}
              autoFocus
              ref={ref => {
                if (ref) {
                  ref.input.select();
                }
              }}
            />
          ),
          placement: 'bottomLeft',
        });
      });
  };

  render() {
    return (
      <Tooltip title="Copy URL">
        <Button
          className="URLShortener"
          onClick={this.onClick}
          icon="share-alt"
          type="primary"
          shape="circle"
          size="large"
        />
      </Tooltip>
    );
  }
}
