// @flow
import React, {Component} from 'react';
import SyntaxHighlighter, {
  registerLanguage,
} from 'react-syntax-highlighter/prism-light';
import styles from 'react-syntax-highlighter/styles/prism/prism';
import jsx from 'react-syntax-highlighter/languages/prism/jsx';
//import javascript from 'react-syntax-highlighter/languages/prism/javascript';
import java from 'react-syntax-highlighter/languages/prism/java';
import objectivec from 'react-syntax-highlighter/languages/prism/objectivec';
import type {LayoutRecordT} from './LayoutRecord';
import {Radio} from 'antd';
import CodeJavaScript from './CodeJavaScript';
import CodeLitho from './CodeLitho';
import CodeReactNative from './CodeReactNative';
import CodeComponentKit from './CodeComponentKit';
import './Code.css';
import type {Yoga$Direction} from 'yoga-layout';
const RadioButton = Radio.Button;
const RadioGroup = Radio.Group;
registerLanguage('jsx', jsx);
//registerLanguage('javascript', javascript);
registerLanguage('java', java);
registerLanguage('objectivec', objectivec);

type Language = 'JavaScript' | 'Litho' | 'ComponentKit' | 'React Native';

type Props = {
  layoutDefinition: LayoutRecordT,
  direction: Yoga$Direction,
  languages: Array<Language>,
};

type State = {
  language: Language,
};

export default class Code extends Component<Props, State> {
  static defaultProps = {
    languages: [/*'JavaScript', */ 'Litho', 'ComponentKit', 'React Native'],
  };

  state = {
    language: 'Litho',
  };

  generateCode(lang: Language): string {
    if (lang === 'JavaScript') {
      return CodeJavaScript(this.props.layoutDefinition, this.props.direction);
    } else if (lang === 'Litho') {
      return CodeLitho(this.props.layoutDefinition, this.props.direction);
    } else if (lang === 'ComponentKit') {
      return CodeComponentKit(
        this.props.layoutDefinition,
        this.props.direction,
      );
    } else if (lang === 'React Native') {
      return CodeReactNative(this.props.layoutDefinition, this.props.direction);
    } else {
      return '';
    }
  }

  getLanguage(): string {
    if (this.state.language === 'Litho') {
      return 'java';
    } else if (this.state.language === 'React Native') {
      return 'javascript';
    } else if (this.state.language === 'ComponentKit') {
      return 'objectivec';
    } else {
      return this.state.language;
    }
  }

  render() {
    return (
      <div className="Code">
        <RadioGroup
          className="CodeLanguageSelector"
          onChange={e => this.setState({language: e.target.value})}
          value={this.state.language}>
          {this.props.languages.map(lang => (
            <RadioButton key={lang} value={lang}>
              {lang}
            </RadioButton>
          ))}
        </RadioGroup>
        <div className="CodeContainer">
          <SyntaxHighlighter
            language={this.getLanguage()}
            style={styles}
            customStyle={{fontSize: '13px', backgroundColor: 'white'}}
            lineNumberStyle={{userSelect: 'none', opacity: 0.5}}
            codeTagProps={{style: {tabSize: 4}}}
            showLineNumbers>
            {this.generateCode(this.state.language)}
          </SyntaxHighlighter>
        </div>
      </div>
    );
  }
}
