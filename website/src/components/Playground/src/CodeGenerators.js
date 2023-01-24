/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

import React, {Component} from 'react';
import {Menu, Button, Row, Col, Dropdown, Icon, Modal, Tooltip} from 'antd';
import SyntaxHighlighter, {
  registerLanguage,
} from 'react-syntax-highlighter/prism-light';
import styles from 'react-syntax-highlighter/styles/prism/prism';
import CodeJavaScript from './CodeJavaScript';
import CodeLitho from './CodeLitho';
import CodeReactNative from './CodeReactNative';
import CodeComponentKit from './CodeComponentKit';
import jsx from 'react-syntax-highlighter/languages/prism/jsx';
//import javascript from 'react-syntax-highlighter/languages/prism/javascript';
import java from 'react-syntax-highlighter/languages/prism/java';
import objectivec from 'react-syntax-highlighter/languages/prism/objectivec';
registerLanguage('jsx', jsx);
//registerLanguage('javascript', javascript);
registerLanguage('java', java);
registerLanguage('objectivec', objectivec);

import './CodeGenerators.css';

import type {LayoutRecordT} from './LayoutRecord';
import type {Yoga$Direction} from 'yoga-layout';

type Props = {
  layoutDefinition: LayoutRecordT,
  direction: Yoga$Direction,
};
type State = {
  showModal: ?string,
  copied: boolean,
};

const LANGUAGES = {
  litho: {
    title: 'Litho',
    generator: CodeLitho,
    syntax: 'java',
  },
  componentKit: {
    title: 'ComponentKit',
    generator: CodeComponentKit,
    syntax: 'objectivec',
  },
  reactNative: {
    title: 'React Native',
    generator: CodeReactNative,
    syntax: 'jsx',
  },
};
['Litho', 'ComponentKit', 'React Native'];

export default class CodeGenerators extends Component<Props, State> {
  state = {
    showModal: null,
    copied: false,
  };

  _ref: ?HTMLTextAreaElement;

  onClick = ({key}: {key: string}) => {
    this.setState({showModal: key});
    if (window.ga) {
      window.ga('send', {
        hitType: 'event',
        eventCategory: 'CodeGenerators',
        eventAction: 'show',
        eventLabel: key,
      });
    }
  };

  onCopy = () => {
    if (this._ref) {
      this._ref.select();
      document.execCommand('Copy');
      this.setState({copied: true});
    }
  };

  render() {
    const {showModal} = this.state;

    const menu = (
      <Menu onClick={this.onClick}>
        {Object.keys(LANGUAGES).map(key => (
          <Menu.Item key={key}>{LANGUAGES[key].title}</Menu.Item>
        ))}
      </Menu>
    );

    const code = showModal
      ? LANGUAGES[showModal].generator(
          this.props.layoutDefinition,
          this.props.direction,
        )
      : '';

    return [
      <Modal
        key="modal"
        title={
          showModal ? (
            <div className="CodeGeneratorsTitle">
              {LANGUAGES[showModal].title}
              <Tooltip
                title={this.state.copied ? 'Copied!' : 'Click to copy'}
                onVisibleChange={() => this.setState({copied: false})}>
                <a onClick={this.onCopy}>copy to clipboard</a>
              </Tooltip>
            </div>
          ) : (
            ''
          )
        }
        visible={Boolean(showModal)}
        footer={null}
        bodyStyle={{padding: 0}}
        onCancel={() => this.setState({showModal: null})}>
        {showModal && (
          <div>
            <textarea
              className="CodeGeneratorsCopyText"
              value={code}
              ref={ref => {
                this._ref = ref;
              }}
            />
            <SyntaxHighlighter
              language={LANGUAGES[showModal].syntax}
              style={styles}
              customStyle={{fontSize: '13px', backgroundColor: 'white'}}
              lineNumberStyle={{userSelect: 'none', opacity: 0.5}}
              codeTagProps={{style: {tabSize: 4}}}
              showLineNumbers>
              {code}
            </SyntaxHighlighter>
          </div>
        )}
      </Modal>,
      <Dropdown overlay={menu} key="dropdown" trigger={['click']}>
        <Button>
          Get Code <Icon type="down" />
        </Button>
      </Dropdown>,
    ];
  }
}
