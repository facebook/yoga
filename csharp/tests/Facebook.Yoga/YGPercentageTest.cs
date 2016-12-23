/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

 // @Generated by gentest/gentest.rb from gentest/fixtures/YGPercentageTest.html

using System;
using NUnit.Framework;

namespace Facebook.Yoga
{
    [TestFixture]
    public class YGPercentageTest
    {
        [Test]
        public void Test_percentage_width_height()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.FlexDirection = YogaFlexDirection.Row;
            root.Width = 200;
            root.Height = 200;

            YogaNode root_child0 = new YogaNode();
            root_child0.Width = 30.Percent();
            root_child0.Height = 30.Percent();
            root.Insert(0, root_child0);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(60f, root_child0.LayoutWidth);
            Assert.AreEqual(60f, root_child0.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(140f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(60f, root_child0.LayoutWidth);
            Assert.AreEqual(60f, root_child0.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_position_left_top()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.FlexDirection = YogaFlexDirection.Row;
            root.Width = 400;
            root.Height = 400;

            YogaNode root_child0 = new YogaNode();
            root_child0.SetPosition(YogaEdge.Left, 10.Percent());
            root_child0.SetPosition(YogaEdge.Top, 20.Percent());
            root_child0.Width = 45.Percent();
            root_child0.Height = 55.Percent();
            root.Insert(0, root_child0);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(400f, root.LayoutWidth);
            Assert.AreEqual(400f, root.LayoutHeight);

            Assert.AreEqual(40f, root_child0.LayoutX);
            Assert.AreEqual(80f, root_child0.LayoutY);
            Assert.AreEqual(180f, root_child0.LayoutWidth);
            Assert.AreEqual(220f, root_child0.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(400f, root.LayoutWidth);
            Assert.AreEqual(400f, root.LayoutHeight);

            Assert.AreEqual(260f, root_child0.LayoutX);
            Assert.AreEqual(80f, root_child0.LayoutY);
            Assert.AreEqual(180f, root_child0.LayoutWidth);
            Assert.AreEqual(220f, root_child0.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_position_bottom_right()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.FlexDirection = YogaFlexDirection.Row;
            root.Width = 500;
            root.Height = 500;

            YogaNode root_child0 = new YogaNode();
            root_child0.SetPosition(YogaEdge.Right, 20.Percent());
            root_child0.SetPosition(YogaEdge.Bottom, 10.Percent());
            root_child0.Width = 55.Percent();
            root_child0.Height = 15.Percent();
            root.Insert(0, root_child0);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(500f, root.LayoutWidth);
            Assert.AreEqual(500f, root.LayoutHeight);

            Assert.AreEqual(-100f, root_child0.LayoutX);
            Assert.AreEqual(-50f, root_child0.LayoutY);
            Assert.AreEqual(275f, root_child0.LayoutWidth);
            Assert.AreEqual(75f, root_child0.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(500f, root.LayoutWidth);
            Assert.AreEqual(500f, root.LayoutHeight);

            Assert.AreEqual(125f, root_child0.LayoutX);
            Assert.AreEqual(-50f, root_child0.LayoutY);
            Assert.AreEqual(275f, root_child0.LayoutWidth);
            Assert.AreEqual(75f, root_child0.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_flex_basis()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.FlexDirection = YogaFlexDirection.Row;
            root.Width = 200;
            root.Height = 200;

            YogaNode root_child0 = new YogaNode();
            root_child0.FlexGrow = 1;
            root_child0.FlexBasis = 50.Percent();
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.FlexGrow = 1;
            root_child1.FlexBasis = 25.Percent();
            root.Insert(1, root_child1);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(125f, root_child0.LayoutWidth);
            Assert.AreEqual(200f, root_child0.LayoutHeight);

            Assert.AreEqual(125f, root_child1.LayoutX);
            Assert.AreEqual(0f, root_child1.LayoutY);
            Assert.AreEqual(75f, root_child1.LayoutWidth);
            Assert.AreEqual(200f, root_child1.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(75f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(125f, root_child0.LayoutWidth);
            Assert.AreEqual(200f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(0f, root_child1.LayoutY);
            Assert.AreEqual(75f, root_child1.LayoutWidth);
            Assert.AreEqual(200f, root_child1.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_flex_basis_cross()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.Width = 200;
            root.Height = 200;

            YogaNode root_child0 = new YogaNode();
            root_child0.FlexGrow = 1;
            root_child0.FlexBasis = 50.Percent();
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.FlexGrow = 1;
            root_child1.FlexBasis = 25.Percent();
            root.Insert(1, root_child1);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(200f, root_child0.LayoutWidth);
            Assert.AreEqual(125f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(125f, root_child1.LayoutY);
            Assert.AreEqual(200f, root_child1.LayoutWidth);
            Assert.AreEqual(75f, root_child1.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(200f, root_child0.LayoutWidth);
            Assert.AreEqual(125f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(125f, root_child1.LayoutY);
            Assert.AreEqual(200f, root_child1.LayoutWidth);
            Assert.AreEqual(75f, root_child1.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_flex_basis_cross_min_height()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.Width = 200;
            root.Height = 200;

            YogaNode root_child0 = new YogaNode();
            root_child0.FlexGrow = 1;
            root_child0.MinHeight = 60.Percent();
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.FlexGrow = 2;
            root_child1.MinHeight = 10.Percent();
            root.Insert(1, root_child1);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(200f, root_child0.LayoutWidth);
            Assert.AreEqual(140f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(140f, root_child1.LayoutY);
            Assert.AreEqual(200f, root_child1.LayoutWidth);
            Assert.AreEqual(60f, root_child1.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(200f, root_child0.LayoutWidth);
            Assert.AreEqual(140f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(140f, root_child1.LayoutY);
            Assert.AreEqual(200f, root_child1.LayoutWidth);
            Assert.AreEqual(60f, root_child1.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_flex_basis_main_max_height()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.FlexDirection = YogaFlexDirection.Row;
            root.Width = 200;
            root.Height = 200;

            YogaNode root_child0 = new YogaNode();
            root_child0.FlexGrow = 1;
            root_child0.FlexBasis = 10.Percent();
            root_child0.MaxHeight = 60.Percent();
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.FlexGrow = 4;
            root_child1.FlexBasis = 10.Percent();
            root_child1.MaxHeight = 20.Percent();
            root.Insert(1, root_child1);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(52f, root_child0.LayoutWidth);
            Assert.AreEqual(120f, root_child0.LayoutHeight);

            Assert.AreEqual(52f, root_child1.LayoutX);
            Assert.AreEqual(0f, root_child1.LayoutY);
            Assert.AreEqual(148f, root_child1.LayoutWidth);
            Assert.AreEqual(40f, root_child1.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(148f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(52f, root_child0.LayoutWidth);
            Assert.AreEqual(120f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(0f, root_child1.LayoutY);
            Assert.AreEqual(148f, root_child1.LayoutWidth);
            Assert.AreEqual(40f, root_child1.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_flex_basis_cross_max_height()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.Width = 200;
            root.Height = 200;

            YogaNode root_child0 = new YogaNode();
            root_child0.FlexGrow = 1;
            root_child0.FlexBasis = 10.Percent();
            root_child0.MaxHeight = 60.Percent();
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.FlexGrow = 4;
            root_child1.FlexBasis = 10.Percent();
            root_child1.MaxHeight = 20.Percent();
            root.Insert(1, root_child1);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(200f, root_child0.LayoutWidth);
            Assert.AreEqual(120f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(120f, root_child1.LayoutY);
            Assert.AreEqual(200f, root_child1.LayoutWidth);
            Assert.AreEqual(40f, root_child1.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(200f, root_child0.LayoutWidth);
            Assert.AreEqual(120f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(120f, root_child1.LayoutY);
            Assert.AreEqual(200f, root_child1.LayoutWidth);
            Assert.AreEqual(40f, root_child1.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_flex_basis_main_max_width()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.FlexDirection = YogaFlexDirection.Row;
            root.Width = 200;
            root.Height = 200;

            YogaNode root_child0 = new YogaNode();
            root_child0.FlexGrow = 1;
            root_child0.FlexBasis = 15.Percent();
            root_child0.MaxWidth = 60.Percent();
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.FlexGrow = 4;
            root_child1.FlexBasis = 10.Percent();
            root_child1.MaxWidth = 20.Percent();
            root.Insert(1, root_child1);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(120f, root_child0.LayoutWidth);
            Assert.AreEqual(200f, root_child0.LayoutHeight);

            Assert.AreEqual(120f, root_child1.LayoutX);
            Assert.AreEqual(0f, root_child1.LayoutY);
            Assert.AreEqual(40f, root_child1.LayoutWidth);
            Assert.AreEqual(200f, root_child1.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(80f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(120f, root_child0.LayoutWidth);
            Assert.AreEqual(200f, root_child0.LayoutHeight);

            Assert.AreEqual(40f, root_child1.LayoutX);
            Assert.AreEqual(0f, root_child1.LayoutY);
            Assert.AreEqual(40f, root_child1.LayoutWidth);
            Assert.AreEqual(200f, root_child1.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_flex_basis_cross_max_width()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.Width = 200;
            root.Height = 200;

            YogaNode root_child0 = new YogaNode();
            root_child0.FlexGrow = 1;
            root_child0.FlexBasis = 10.Percent();
            root_child0.MaxWidth = 60.Percent();
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.FlexGrow = 4;
            root_child1.FlexBasis = 15.Percent();
            root_child1.MaxWidth = 20.Percent();
            root.Insert(1, root_child1);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(120f, root_child0.LayoutWidth);
            Assert.AreEqual(50f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(50f, root_child1.LayoutY);
            Assert.AreEqual(40f, root_child1.LayoutWidth);
            Assert.AreEqual(150f, root_child1.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(80f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(120f, root_child0.LayoutWidth);
            Assert.AreEqual(50f, root_child0.LayoutHeight);

            Assert.AreEqual(160f, root_child1.LayoutX);
            Assert.AreEqual(50f, root_child1.LayoutY);
            Assert.AreEqual(40f, root_child1.LayoutWidth);
            Assert.AreEqual(150f, root_child1.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_flex_basis_main_min_width()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.FlexDirection = YogaFlexDirection.Row;
            root.Width = 200;
            root.Height = 200;

            YogaNode root_child0 = new YogaNode();
            root_child0.FlexGrow = 1;
            root_child0.FlexBasis = 15.Percent();
            root_child0.MinWidth = 60.Percent();
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.FlexGrow = 4;
            root_child1.FlexBasis = 10.Percent();
            root_child1.MinWidth = 20.Percent();
            root.Insert(1, root_child1);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(120f, root_child0.LayoutWidth);
            Assert.AreEqual(200f, root_child0.LayoutHeight);

            Assert.AreEqual(120f, root_child1.LayoutX);
            Assert.AreEqual(0f, root_child1.LayoutY);
            Assert.AreEqual(80f, root_child1.LayoutWidth);
            Assert.AreEqual(200f, root_child1.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(80f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(120f, root_child0.LayoutWidth);
            Assert.AreEqual(200f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(0f, root_child1.LayoutY);
            Assert.AreEqual(80f, root_child1.LayoutWidth);
            Assert.AreEqual(200f, root_child1.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_flex_basis_cross_min_width()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.Width = 200;
            root.Height = 200;

            YogaNode root_child0 = new YogaNode();
            root_child0.FlexGrow = 1;
            root_child0.FlexBasis = 10.Percent();
            root_child0.MinWidth = 60.Percent();
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.FlexGrow = 4;
            root_child1.FlexBasis = 15.Percent();
            root_child1.MinWidth = 20.Percent();
            root.Insert(1, root_child1);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(200f, root_child0.LayoutWidth);
            Assert.AreEqual(50f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(50f, root_child1.LayoutY);
            Assert.AreEqual(200f, root_child1.LayoutWidth);
            Assert.AreEqual(150f, root_child1.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(200f, root_child0.LayoutWidth);
            Assert.AreEqual(50f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(50f, root_child1.LayoutY);
            Assert.AreEqual(200f, root_child1.LayoutWidth);
            Assert.AreEqual(150f, root_child1.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_multiple_nested_with_padding_margin_and_percentage_values()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.Width = 200;
            root.Height = 200;

            YogaNode root_child0 = new YogaNode();
            root_child0.FlexGrow = 1;
            root_child0.FlexBasis = 10.Percent();
            root_child0.SetMargin(YogaEdge.Left, 5);
            root_child0.SetMargin(YogaEdge.Top, 5);
            root_child0.SetMargin(YogaEdge.Right, 5);
            root_child0.SetMargin(YogaEdge.Bottom, 5);
            root_child0.SetPadding(YogaEdge.Left, 3);
            root_child0.SetPadding(YogaEdge.Top, 3);
            root_child0.SetPadding(YogaEdge.Right, 3);
            root_child0.SetPadding(YogaEdge.Bottom, 3);
            root_child0.MinWidth = 60.Percent();
            root.Insert(0, root_child0);

            YogaNode root_child0_child0 = new YogaNode();
            root_child0_child0.SetMargin(YogaEdge.Left, 5);
            root_child0_child0.SetMargin(YogaEdge.Top, 5);
            root_child0_child0.SetMargin(YogaEdge.Right, 5);
            root_child0_child0.SetMargin(YogaEdge.Bottom, 5);
            root_child0_child0.SetPadding(YogaEdge.Left, 3.Percent());
            root_child0_child0.SetPadding(YogaEdge.Top, 3.Percent());
            root_child0_child0.SetPadding(YogaEdge.Right, 3.Percent());
            root_child0_child0.SetPadding(YogaEdge.Bottom, 3.Percent());
            root_child0_child0.Width = 50.Percent();
            root_child0.Insert(0, root_child0_child0);

            YogaNode root_child0_child0_child0 = new YogaNode();
            root_child0_child0_child0.SetMargin(YogaEdge.Left, 5.Percent());
            root_child0_child0_child0.SetMargin(YogaEdge.Top, 5.Percent());
            root_child0_child0_child0.SetMargin(YogaEdge.Right, 5.Percent());
            root_child0_child0_child0.SetMargin(YogaEdge.Bottom, 5.Percent());
            root_child0_child0_child0.SetPadding(YogaEdge.Left, 3);
            root_child0_child0_child0.SetPadding(YogaEdge.Top, 3);
            root_child0_child0_child0.SetPadding(YogaEdge.Right, 3);
            root_child0_child0_child0.SetPadding(YogaEdge.Bottom, 3);
            root_child0_child0_child0.Width = 45.Percent();
            root_child0_child0.Insert(0, root_child0_child0_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.FlexGrow = 4;
            root_child1.FlexBasis = 15.Percent();
            root_child1.MinWidth = 20.Percent();
            root.Insert(1, root_child1);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(5f, root_child0.LayoutX);
            Assert.AreEqual(5f, root_child0.LayoutY);
            Assert.AreEqual(190f, root_child0.LayoutWidth);
            Assert.AreEqual(48f, root_child0.LayoutHeight);

            Assert.AreEqual(8f, root_child0_child0.LayoutX);
            Assert.AreEqual(8f, root_child0_child0.LayoutY);
            Assert.AreEqual(92f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(25f, root_child0_child0.LayoutHeight);

            Assert.AreEqual(10f, root_child0_child0_child0.LayoutX);
            Assert.AreEqual(10f, root_child0_child0_child0.LayoutY);
            Assert.AreEqual(36f, root_child0_child0_child0.LayoutWidth);
            Assert.AreEqual(6f, root_child0_child0_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(58f, root_child1.LayoutY);
            Assert.AreEqual(200f, root_child1.LayoutWidth);
            Assert.AreEqual(142f, root_child1.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(5f, root_child0.LayoutX);
            Assert.AreEqual(5f, root_child0.LayoutY);
            Assert.AreEqual(190f, root_child0.LayoutWidth);
            Assert.AreEqual(48f, root_child0.LayoutHeight);

            Assert.AreEqual(90f, root_child0_child0.LayoutX);
            Assert.AreEqual(8f, root_child0_child0.LayoutY);
            Assert.AreEqual(92f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(25f, root_child0_child0.LayoutHeight);

            Assert.AreEqual(46f, root_child0_child0_child0.LayoutX);
            Assert.AreEqual(10f, root_child0_child0_child0.LayoutY);
            Assert.AreEqual(36f, root_child0_child0_child0.LayoutWidth);
            Assert.AreEqual(6f, root_child0_child0_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(58f, root_child1.LayoutY);
            Assert.AreEqual(200f, root_child1.LayoutWidth);
            Assert.AreEqual(142f, root_child1.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_margin_should_calculate_based_only_on_width()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.Width = 200;
            root.Height = 100;

            YogaNode root_child0 = new YogaNode();
            root_child0.FlexGrow = 1;
            root_child0.SetMargin(YogaEdge.Left, 10.Percent());
            root_child0.SetMargin(YogaEdge.Top, 10.Percent());
            root_child0.SetMargin(YogaEdge.Right, 10.Percent());
            root_child0.SetMargin(YogaEdge.Bottom, 10.Percent());
            root.Insert(0, root_child0);

            YogaNode root_child0_child0 = new YogaNode();
            root_child0_child0.Width = 10;
            root_child0_child0.Height = 10;
            root_child0.Insert(0, root_child0_child0);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(20f, root_child0.LayoutX);
            Assert.AreEqual(20f, root_child0.LayoutY);
            Assert.AreEqual(160f, root_child0.LayoutWidth);
            Assert.AreEqual(60f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child0_child0.LayoutX);
            Assert.AreEqual(0f, root_child0_child0.LayoutY);
            Assert.AreEqual(10f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0_child0.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(20f, root_child0.LayoutX);
            Assert.AreEqual(20f, root_child0.LayoutY);
            Assert.AreEqual(160f, root_child0.LayoutWidth);
            Assert.AreEqual(60f, root_child0.LayoutHeight);

            Assert.AreEqual(150f, root_child0_child0.LayoutX);
            Assert.AreEqual(0f, root_child0_child0.LayoutY);
            Assert.AreEqual(10f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0_child0.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_padding_should_calculate_based_only_on_width()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.Width = 200;
            root.Height = 100;

            YogaNode root_child0 = new YogaNode();
            root_child0.FlexGrow = 1;
            root_child0.SetPadding(YogaEdge.Left, 10.Percent());
            root_child0.SetPadding(YogaEdge.Top, 10.Percent());
            root_child0.SetPadding(YogaEdge.Right, 10.Percent());
            root_child0.SetPadding(YogaEdge.Bottom, 10.Percent());
            root.Insert(0, root_child0);

            YogaNode root_child0_child0 = new YogaNode();
            root_child0_child0.Width = 10;
            root_child0_child0.Height = 10;
            root_child0.Insert(0, root_child0_child0);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(200f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(10f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0_child0.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(200f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(170f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(10f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0_child0.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

        [Test]
        public void Test_percentage_absolute_position()
        {
            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, true);

            YogaNode root = new YogaNode();
            root.Width = 200;
            root.Height = 100;

            YogaNode root_child0 = new YogaNode();
            root_child0.PositionType = YogaPositionType.Absolute;
            root_child0.SetPosition(YogaEdge.Left, 30.Percent());
            root_child0.SetPosition(YogaEdge.Top, 10.Percent());
            root_child0.Width = 10;
            root_child0.Height = 10;
            root.Insert(0, root_child0);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(60f, root_child0.LayoutX);
            Assert.AreEqual(10f, root_child0.LayoutY);
            Assert.AreEqual(10f, root_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(60f, root_child0.LayoutX);
            Assert.AreEqual(10f, root_child0.LayoutY);
            Assert.AreEqual(10f, root_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0.LayoutHeight);

            YogaNode.SetExperimentalFeatureEnabled(YogaExperimentalFeature.Rounding, false);
        }

    }
}
