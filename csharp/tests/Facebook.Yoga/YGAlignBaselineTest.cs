/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

using System;
using NUnit.Framework;

namespace Facebook.Yoga
{
    [TestFixture]
    public class YGAlignBaselineTest
    {
        [Test]
        public void Test_align_baseline_parent_using_child_in_column_as_reference()
        {
          YogaConfig config = new YogaConfig();
          YogaNode root = createYGNode(config, YogaFlexDirection.Row, 1000, 1000, true);

          YogaNode root_child0 = createYGNode(config, YogaFlexDirection.Column, 500, 600, false);
          root.Insert(0, root_child0);

          YogaNode root_child1 = createYGNode(config, YogaFlexDirection.Column, 500, 800, false);
          root.Insert(1, root_child1);

          YogaNode root_child1_child0 = createYGNode(config, YogaFlexDirection.Column, 500, 300, false);
          root_child1.Insert(0, root_child1_child0);

          YogaNode root_child1_child1 = createYGNode(config, YogaFlexDirection.Column, 500, 400, false);
          root_child1_child1.SetBaselineFunction((_, width, height) => {
              return height / 2;
          });
          root_child1_child1.IsReferenceBaseline = true;
          root_child1.Insert(1, root_child1_child1);

          root.CalculateLayout();

          Assert.AreEqual(0f, root_child0.LayoutX);
          Assert.AreEqual(0f, root_child0.LayoutY);

          Assert.AreEqual(500f, root_child1.LayoutX);
          Assert.AreEqual(100f, root_child1.LayoutY);

          Assert.AreEqual(0f, root_child1_child0.LayoutX);
          Assert.AreEqual(0f, root_child1_child0.LayoutY);

          Assert.AreEqual(0f, root_child1_child1.LayoutX);
          Assert.AreEqual(300f, root_child1_child1.LayoutY);
        }

        [Test]
        public void Test_align_baseline_parent_using_child_in_row_as_reference()
        {
          YogaConfig config = new YogaConfig();

          YogaNode root = createYGNode(config, YogaFlexDirection.Row, 1000, 1000, true);

          YogaNode root_child0 = createYGNode(config, YogaFlexDirection.Column, 500, 600, false);
          root.Insert(0, root_child0);

          YogaNode root_child1 = createYGNode(config, YogaFlexDirection.Row, 500, 800, true);
          root.Insert(1, root_child1);

          YogaNode root_child1_child0 = createYGNode(config, YogaFlexDirection.Row, 500, 500, false);
          root_child1.Insert(0, root_child1_child0);

          YogaNode root_child1_child1 = createYGNode(config, YogaFlexDirection.Row, 500, 400, false);
          root_child1_child1.SetBaselineFunction((_, width, height) => {
              return height / 2;
          });
          root_child1_child1.IsReferenceBaseline = true;
          root_child1.Insert(1, root_child1_child1);

          root.StyleDirection = YogaDirection.LTR;

          root.CalculateLayout();

          Assert.AreEqual(0f, root_child0.LayoutX);
          Assert.AreEqual(0f, root_child0.LayoutY);

          Assert.AreEqual(500f, root_child1.LayoutX);
          Assert.AreEqual(100f, root_child1.LayoutY);

          Assert.AreEqual(0f, root_child1_child0.LayoutX);
          Assert.AreEqual(0f, root_child1_child0.LayoutY);

          Assert.AreEqual(500f, root_child1_child1.LayoutX);
          Assert.AreEqual(300f, root_child1_child1.LayoutY);
        }

        private YogaNode createYGNode(YogaConfig config, YogaFlexDirection flexDirection, int width, int height, bool alignBaseline) {
          YogaNode node = new YogaNode(config);
          node.FlexDirection = flexDirection;
          node.Width = width;
          node.Height = height;
          if (alignBaseline) {
            node.AlignItems = YogaAlign.Baseline;
          }
          return node;
        }
    }
}
