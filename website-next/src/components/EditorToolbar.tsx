/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import {useCallback, useEffect, useRef, useState} from 'react';
import clsx from 'clsx';

import CopyIcon from '../../static/img/copy.svg';
import LinkIcon from '../../static/img/link.svg';
import SuccessIcon from '@theme/Icon/Success';

import styles from './EditorToolbar.module.css';

export type Props = Readonly<{
  getCode: () => string;
  className?: string;
  style?: React.CSSProperties;
}>;

export default function EditorToolbar({
  getCode,
  className,
  style,
}: Props): JSX.Element {
  const handleCopy = useCallback(
    () => navigator.clipboard.writeText(getCode()),
    [],
  );

  const handleShare = useCallback(
    () =>
      navigator.clipboard.writeText(
        window.location.origin +
          `/playground?code=${encodeURIComponent(btoa(getCode()))}`,
      ),
    [],
  );

  return (
    <div className={clsx(styles.toolbar, className)} style={style}>
      <ToolbarButton Icon={CopyIcon} label="Copy" onClick={handleCopy} />
      <ToolbarButton Icon={LinkIcon} label="Share" onClick={handleShare} />
    </div>
  );
}

type ToolbarButtonProps = Readonly<{
  onClick: () => void;
  Icon: React.ComponentType<React.SVGProps<SVGSVGElement>>;
  label?: string;
}>;

function ToolbarButton({
  onClick,
  Icon,
  label,
}: ToolbarButtonProps): JSX.Element {
  const [isSuccess, setIsSuccess] = useState(false);
  const copyTimeout = useRef<number | undefined>(undefined);

  useEffect(() => () => window.clearTimeout(copyTimeout.current), []);

  const handleClick = useCallback(() => {
    onClick();
    setIsSuccess(true);
    copyTimeout.current = window.setTimeout(() => {
      setIsSuccess(false);
    }, 1000);
  }, []);

  return (
    <button
      type="button"
      className={clsx('clean-btn', isSuccess && styles.clicked)}
      onClick={handleClick}
      aria-label={label}>
      <span className={styles.iconSwitcher} aria-hidden="true">
        <Icon className={styles.actionIcon} />
        <SuccessIcon className={styles.successIcon} />
      </span>
    </button>
  );
}
