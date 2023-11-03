/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import type {LayoutRecordType} from './LayoutRecord';
import type {Direction} from 'yoga-layout';

import Tabs from '@theme/Tabs';
import TabItem from '@theme/TabItem';

import React from 'react';
import EditValue from './EditValue';
import styles from './Editor.module.css';

type Props = {
  node: LayoutRecordType;
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  onChangeLayout: (key: string, value: any) => void;
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  onChangeSetting: (key: string, value: any) => void;
  direction: Direction;
  selectedNodeIsRoot: boolean;
  onRemove?: () => void;
  onAdd?: () => void;
};

export default function Editor(props: Props) {
  const {node, selectedNodeIsRoot} = props;
  const disabled = node == null;

  return (
    <div className={styles.editor}>
      <Tabs block={true}>
        <TabItem
          value="flex"
          label="Flex"
          className={styles.tabItem}
          default={true}>
          <h2>Direction</h2>
          <EditValue
            property="direction"
            value={props.direction}
            onChange={props.onChangeSetting}
          />
          <h2>Flex Direction</h2>
          <EditValue
            disabled={disabled}
            property="flexDirection"
            value={node ? node.flexDirection : undefined}
            onChange={props.onChangeLayout}
          />

          <div className="row margin--none">
            <div className="col col--4">
              <h2>Basis</h2>
              <EditValue
                // @ts-ignore
                type="text"
                property="flexBasis"
                placeholder="auto"
                disabled={disabled || selectedNodeIsRoot}
                value={node ? node.flexBasis : undefined}
                onChange={props.onChangeLayout}
              />
            </div>
            <div className="col col--4">
              <h2>Grow</h2>
              <EditValue
                // @ts-ignore
                type="text"
                property="flexGrow margin--none"
                placeholder="0"
                disabled={disabled || selectedNodeIsRoot}
                value={node ? node.flexGrow : undefined}
                onChange={props.onChangeLayout}
              />
            </div>
            <div className="col col--4">
              <h2>Shrink</h2>
              <EditValue
                // @ts-ignore
                type="text"
                property="flexShrink"
                placeholder="1"
                disabled={disabled || selectedNodeIsRoot}
                value={node ? node.flexShrink : undefined}
                onChange={props.onChangeLayout}
              />
            </div>
          </div>

          <h2>Flex Wrap</h2>
          <EditValue
            disabled={disabled}
            property="flexWrap"
            value={node ? node.flexWrap : undefined}
            onChange={props.onChangeLayout}
          />
        </TabItem>
        <TabItem value="alignment" label="Alignment" className={styles.tabItem}>
          <h2>Justify Content</h2>
          <EditValue
            disabled={disabled}
            property="justifyContent"
            value={node ? node.justifyContent : undefined}
            onChange={props.onChangeLayout}
          />

          <h2>Align Items</h2>
          <EditValue
            disabled={disabled}
            property="alignItems"
            value={node ? node.alignItems : undefined}
            onChange={props.onChangeLayout}
          />

          <h2>Align Self</h2>
          <EditValue
            disabled={disabled || selectedNodeIsRoot}
            property="alignSelf"
            value={node ? node.alignSelf : undefined}
            onChange={props.onChangeLayout}
          />

          <h2>Align Content</h2>
          <EditValue
            disabled={disabled}
            property="alignContent"
            value={node ? node.alignContent : undefined}
            onChange={props.onChangeLayout}
          />
        </TabItem>
        <TabItem value="layout" label="Layout" className={styles.tabItem}>
          <h2>Width &times; Height</h2>
          <div className="row margin--none">
            <div className="col col--6">
              <EditValue
                // @ts-ignore
                type="text"
                placeholder="auto"
                property="width"
                disabled={disabled}
                value={node ? node.width : undefined}
                onChange={props.onChangeLayout}
              />
            </div>
            <div className="col col--6">
              <EditValue
                // @ts-ignore
                type="text"
                placeholder="auto"
                property="height"
                disabled={disabled}
                value={node ? node.height : undefined}
                onChange={props.onChangeLayout}
              />
            </div>
          </div>
          <h2>Max-Width &times; Max-Height</h2>
          <div className="row margin--none">
            <div className="col col--6">
              <EditValue
                // @ts-ignore
                type="text"
                placeholder="none"
                property="maxWidth"
                disabled={disabled}
                value={node ? node.maxWidth : undefined}
                onChange={props.onChangeLayout}
              />
            </div>
            <div className="col col--6">
              <EditValue
                // @ts-ignore
                type="text"
                placeholder="none"
                property="maxHeight"
                disabled={disabled}
                value={node ? node.maxHeight : undefined}
                onChange={props.onChangeLayout}
              />
            </div>
          </div>
          <h2>Min-Width &times; Min-Height</h2>
          <div className="row margin--none">
            <div className="col col--6">
              <EditValue
                // @ts-ignore
                type="text"
                placeholder="0"
                property="minWidth"
                disabled={disabled}
                value={node ? node.minWidth : undefined}
                onChange={props.onChangeLayout}
              />
            </div>
            <div className="col col--6">
              <EditValue
                // @ts-ignore
                type="text"
                placeholder="0"
                property="minHeight"
                disabled={disabled}
                value={node ? node.minHeight : undefined}
                onChange={props.onChangeLayout}
              />
            </div>
          </div>

          <h2>Aspect Ratio</h2>
          <EditValue
            // @ts-ignore
            type="text"
            placeholder="auto"
            property="aspectRatio"
            disabled={disabled}
            value={node ? node.aspectRatio : undefined}
            onChange={props.onChangeLayout}
          />

          {['padding', 'border', 'margin'].map(property => (
            <EditValue
              property={property}
              key={property}
              value={node ? node[property] : undefined}
              onChange={props.onChangeLayout}
              disabled={property === 'margin' && selectedNodeIsRoot}
            />
          ))}
          <h2>Position Type</h2>

          <EditValue
            disabled={disabled || selectedNodeIsRoot}
            property="positionType"
            value={node ? node.positionType : undefined}
            onChange={props.onChangeLayout}
          />
          <EditValue
            disabled={selectedNodeIsRoot}
            property="position"
            value={node ? node.position : undefined}
            onChange={props.onChangeLayout}
          />
        </TabItem>
      </Tabs>

      <div className={styles.editorButtons}>
        <button
          className="button button--block button--primary button--sm"
          disabled={!props.onRemove}
          onClick={props.onAdd}>
          add child
        </button>
        <button
          className="button button--block button--danger button--sm"
          disabled={!props.onRemove}
          onClick={props.onAdd}>
          remove
        </button>
      </div>
    </div>
  );
}
