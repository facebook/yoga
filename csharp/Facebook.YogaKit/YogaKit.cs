/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

using System.Collections.Generic;
using Facebook.Yoga;

namespace Facebook.YogaKit
{
	public static partial class YogaKit
	{
		internal static Dictionary<YogaNode, object> Bridges = new Dictionary<YogaNode, object>();
	}
}
