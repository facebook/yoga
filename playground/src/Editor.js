// @flow
import React, {Component} from 'react';
import {Row, Col, Button, Tabs, Input} from 'antd';
import YogaEnumSelect from './YogaEnumSelect';
import type {LayoutRecordT} from './LayoutRecord';
import type {Yoga$Direction} from 'yoga-layout';
import InfoText from './InfoText';
import YogaPositionEditor from './YogaPositionEditor';
import './Editor.css';
const TabPane = Tabs.TabPane;

type Props = {
  node: ?LayoutRecordT,
  onChangeLayout: (key: string, value: any) => void,
  onChangeSetting: (key: string, value: any) => void,
  direction: Yoga$Direction,
  selectedNodeIsRoot: boolean,
  onRemove?: () => void,
  onAdd?: () => void,
};

export default class Editor extends Component<Props> {
  componentDidMount() {
    document.addEventListener('keydown', this.onKeyDown);
  }

  componentWillUnmount() {
    document.removeEventListener('keydown', this.onKeyDown);
  }

  onKeyDown = (e: KeyboardEvent) => {
    if (
      (e.key === 'Delete' || e.key === 'Backspace') &&
      this.props.onRemove &&
      !(e.target instanceof HTMLInputElement)
    ) {
      this.props.onRemove();
    }
  };

  render() {
    const {node, selectedNodeIsRoot} = this.props;
    const disabled = !Boolean(node);

    return (
      <div className="Editor">
        <Tabs defaultActiveKey="1" className="EditorTabs">
          <TabPane tab="Flex" key="1">
            <h2>
              Direction
              <InfoText>
                The direction property specifies the text direction/writing
                direction
              </InfoText>
            </h2>
            <YogaEnumSelect
              property="DIRECTION"
              value={this.props.direction}
              onChange={e => this.props.onChangeSetting('direction', e)}
            />
            <h2>
              Flex direction
              <InfoText>Defining the direction of the main-axis</InfoText>
            </h2>
            <YogaEnumSelect
              disabled={disabled}
              property="FLEX_DIRECTION"
              value={node ? node.flexDirection : ''}
              onChange={e => this.props.onChangeLayout('flexDirection', e)}
            />

            <Row gutter={15} style={{marginTop: 30}}>
              <Col span={12}>
                <h2>
                  Flex grow
                  <InfoText>
                    Grow factor defined how much space this element should take
                    up, relative to it's siblings
                  </InfoText>
                </h2>
                <Input
                  type="text"
                  disabled={disabled || selectedNodeIsRoot}
                  value={node ? node.flexGrow : ''}
                  onChange={e =>
                    this.props.onChangeLayout('flexGrow', e.target.value)
                  }
                />
              </Col>
              <Col span={12}>
                <h2>
                  Flex shrink
                  <InfoText>
                    Shrink factor if elements don't fit into the parent node
                    anymore.
                  </InfoText>
                </h2>
                <Input
                  type="text"
                  disabled={disabled || selectedNodeIsRoot}
                  value={node ? node.flexShrink : ''}
                  onChange={e =>
                    this.props.onChangeLayout('flexShrink', e.target.value)
                  }
                />
              </Col>
            </Row>

            <h2>
              Flex wrap
              <InfoText>
                Wrapping behaviour when child nodes don't fit into a single line
              </InfoText>
            </h2>
            <YogaEnumSelect
              disabled={disabled}
              property="WRAP"
              value={node ? node.flexWrap : ''}
              onChange={e => this.props.onChangeLayout('flexWrap', e)}
            />
          </TabPane>
          <TabPane tab="Alignment" key="2">
            <h2>
              Justify content
              <InfoText>Aligns child nodes along the main-axis</InfoText>
            </h2>
            <YogaEnumSelect
              disabled={disabled}
              property="JUSTIFY"
              value={node ? node.justifyContent : ''}
              onChange={e => this.props.onChangeLayout('justifyContent', e)}
            />

            <h2>
              Align items
              <InfoText>Aligns child nodes along the cross-axis</InfoText>
            </h2>
            <YogaEnumSelect
              disabled={disabled}
              property="ALIGN"
              value={node ? node.alignItems : ''}
              onChange={e => this.props.onChangeLayout('alignItems', e)}
            />

            <h2>
              Align self
              <InfoText>
                Specifies alignment on the cross-axis for the node itself
              </InfoText>
            </h2>
            <YogaEnumSelect
              disabled={disabled || selectedNodeIsRoot}
              property="ALIGN"
              value={node ? node.alignSelf : ''}
              onChange={e => this.props.onChangeLayout('alignSelf', e)}
            />

            <h2>
              Align content
              <InfoText>
                Alignment of lines along the cross-axis when wrapping
              </InfoText>
            </h2>
            <YogaEnumSelect
              disabled={disabled}
              property="ALIGN"
              value={node ? node.alignContent : ''}
              onChange={e => this.props.onChangeLayout('alignContent', e)}
            />
          </TabPane>
          <TabPane tab="Layout" key="3">
            <h2>
              Width &times; height
              <InfoText>Dimensions of the node</InfoText>
            </h2>
            <Row gutter={15}>
              <Col span={12}>
                <Input
                  type="text"
                  placeholder="width"
                  disabled={disabled}
                  value={node ? node.width : ''}
                  onChange={e =>
                    this.props.onChangeLayout('width', e.target.value)
                  }
                />
              </Col>
              <Col span={12}>
                <Input
                  type="text"
                  placeholder="height"
                  disabled={disabled}
                  value={node ? node.height : ''}
                  onChange={e =>
                    this.props.onChangeLayout('height', e.target.value)
                  }
                />
              </Col>
            </Row>

            <h2>
              Aspect ratio
              <InfoText>
                Aspect radio is an additon by Yoga which is handy e.g. for nodes
                displaying videos
              </InfoText>
            </h2>
            <Input
              type="text"
              placeholder="Aspect ratio"
              disabled={disabled}
              value={node ? node.aspectRatio : ''}
              onChange={e =>
                this.props.onChangeLayout('aspectRatio', e.target.value)
              }
            />

            <h2>Box model</h2>
            {['padding', 'border', 'margin'].map(property => (
              <YogaPositionEditor
                property={property}
                key={property}
                value={node ? node[property] : undefined}
                onChange={value => this.props.onChangeLayout(property, value)}
              />
            ))}
            <h2>
              Position
              <InfoText>
                Relative position offsets the node from it's calculated
                position. Absolute position removes the node from the flexbox
                flow and positions it at the given position.
              </InfoText>
            </h2>

            <YogaEnumSelect
              disabled={disabled}
              property="POSITION_TYPE"
              value={node ? node.positionType : ''}
              onChange={e => this.props.onChangeLayout('positionType', e)}
            />
            <YogaPositionEditor
              property="position"
              value={node ? node.position : undefined}
              onChange={value => this.props.onChangeLayout('position', value)}
            />
          </TabPane>
        </Tabs>

        <Row gutter={15} className="EditorButtons">
          <Col span={12}>
            <Button
              icon="plus-circle-o"
              disabled={!Boolean(this.props.onAdd)}
              onClick={this.props.onAdd}
              type="primary">
              add child node
            </Button>
          </Col>
          <Col span={12}>
            <Button
              icon="close-circle-o"
              disabled={!Boolean(this.props.onRemove)}
              onClick={this.props.onRemove}
              type="danger">
              remove node
            </Button>
          </Col>
        </Row>
      </div>
    );
  }
}
