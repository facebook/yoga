/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

namespace Facebook.Yoga
{
    public delegate void Logger(
        YogaConfig config,
        YogaNode node,
        YogaLogLevel level,
        string message);
}
