/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

 // @Generated by gentest/gentest.rb from gentest/fixtures/YGFlexWrapTest.html

using System;
using NUnit.Framework;

namespace Facebook.Yoga
{
    [TestFixture]
    public class YGFlexWrapTest
    {
        [Test]
        public void Test_wrap_column()
        {
            YogaNode root = new YogaNode();
            root.Wrap = YogaWrap.Wrap;
            root.Height = 100;

            YogaNode root_child0 = new YogaNode();
            root_child0.Width = 30;
            root_child0.Height = 30;
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.Width = 30;
            root_child1.Height = 30;
            root.Insert(1, root_child1);

            YogaNode root_child2 = new YogaNode();
            root_child2.Width = 30;
            root_child2.Height = 30;
            root.Insert(2, root_child2);

            YogaNode root_child3 = new YogaNode();
            root_child3.Width = 30;
            root_child3.Height = 30;
            root.Insert(3, root_child3);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(60f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(30f, root_child0.LayoutWidth);
            Assert.AreEqual(30f, root_child0.LayoutHeight);

            Assert.AreEqual(0f, root_child1.LayoutX);
            Assert.AreEqual(30f, root_child1.LayoutY);
            Assert.AreEqual(30f, root_child1.LayoutWidth);
            Assert.AreEqual(30f, root_child1.LayoutHeight);

            Assert.AreEqual(0f, root_child2.LayoutX);
            Assert.AreEqual(60f, root_child2.LayoutY);
            Assert.AreEqual(30f, root_child2.LayoutWidth);
            Assert.AreEqual(30f, root_child2.LayoutHeight);

            Assert.AreEqual(30f, root_child3.LayoutX);
            Assert.AreEqual(0f, root_child3.LayoutY);
            Assert.AreEqual(30f, root_child3.LayoutWidth);
            Assert.AreEqual(30f, root_child3.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(60f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(30f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(30f, root_child0.LayoutWidth);
            Assert.AreEqual(30f, root_child0.LayoutHeight);

            Assert.AreEqual(30f, root_child1.LayoutX);
            Assert.AreEqual(30f, root_child1.LayoutY);
            Assert.AreEqual(30f, root_child1.LayoutWidth);
            Assert.AreEqual(30f, root_child1.LayoutHeight);

            Assert.AreEqual(30f, root_child2.LayoutX);
            Assert.AreEqual(60f, root_child2.LayoutY);
            Assert.AreEqual(30f, root_child2.LayoutWidth);
            Assert.AreEqual(30f, root_child2.LayoutHeight);

            Assert.AreEqual(0f, root_child3.LayoutX);
            Assert.AreEqual(0f, root_child3.LayoutY);
            Assert.AreEqual(30f, root_child3.LayoutWidth);
            Assert.AreEqual(30f, root_child3.LayoutHeight);
        }

        [Test]
        public void Test_wrap_row()
        {
            YogaNode root = new YogaNode();
            root.FlexDirection = YogaFlexDirection.Row;
            root.Wrap = YogaWrap.Wrap;
            root.Width = 100;

            YogaNode root_child0 = new YogaNode();
            root_child0.Width = 30;
            root_child0.Height = 30;
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.Width = 30;
            root_child1.Height = 30;
            root.Insert(1, root_child1);

            YogaNode root_child2 = new YogaNode();
            root_child2.Width = 30;
            root_child2.Height = 30;
            root.Insert(2, root_child2);

            YogaNode root_child3 = new YogaNode();
            root_child3.Width = 30;
            root_child3.Height = 30;
            root.Insert(3, root_child3);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(100f, root.LayoutWidth);
            Assert.AreEqual(60f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(30f, root_child0.LayoutWidth);
            Assert.AreEqual(30f, root_child0.LayoutHeight);

            Assert.AreEqual(30f, root_child1.LayoutX);
            Assert.AreEqual(0f, root_child1.LayoutY);
            Assert.AreEqual(30f, root_child1.LayoutWidth);
            Assert.AreEqual(30f, root_child1.LayoutHeight);

            Assert.AreEqual(60f, root_child2.LayoutX);
            Assert.AreEqual(0f, root_child2.LayoutY);
            Assert.AreEqual(30f, root_child2.LayoutWidth);
            Assert.AreEqual(30f, root_child2.LayoutHeight);

            Assert.AreEqual(0f, root_child3.LayoutX);
            Assert.AreEqual(30f, root_child3.LayoutY);
            Assert.AreEqual(30f, root_child3.LayoutWidth);
            Assert.AreEqual(30f, root_child3.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(100f, root.LayoutWidth);
            Assert.AreEqual(60f, root.LayoutHeight);

            Assert.AreEqual(70f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(30f, root_child0.LayoutWidth);
            Assert.AreEqual(30f, root_child0.LayoutHeight);

            Assert.AreEqual(40f, root_child1.LayoutX);
            Assert.AreEqual(0f, root_child1.LayoutY);
            Assert.AreEqual(30f, root_child1.LayoutWidth);
            Assert.AreEqual(30f, root_child1.LayoutHeight);

            Assert.AreEqual(10f, root_child2.LayoutX);
            Assert.AreEqual(0f, root_child2.LayoutY);
            Assert.AreEqual(30f, root_child2.LayoutWidth);
            Assert.AreEqual(30f, root_child2.LayoutHeight);

            Assert.AreEqual(70f, root_child3.LayoutX);
            Assert.AreEqual(30f, root_child3.LayoutY);
            Assert.AreEqual(30f, root_child3.LayoutWidth);
            Assert.AreEqual(30f, root_child3.LayoutHeight);
        }

        [Test]
        public void Test_wrap_row_align_items_flex_end()
        {
            YogaNode root = new YogaNode();
            root.FlexDirection = YogaFlexDirection.Row;
            root.AlignItems = YogaAlign.FlexEnd;
            root.Wrap = YogaWrap.Wrap;
            root.Width = 100;

            YogaNode root_child0 = new YogaNode();
            root_child0.Width = 30;
            root_child0.Height = 10;
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.Width = 30;
            root_child1.Height = 20;
            root.Insert(1, root_child1);

            YogaNode root_child2 = new YogaNode();
            root_child2.Width = 30;
            root_child2.Height = 30;
            root.Insert(2, root_child2);

            YogaNode root_child3 = new YogaNode();
            root_child3.Width = 30;
            root_child3.Height = 30;
            root.Insert(3, root_child3);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(100f, root.LayoutWidth);
            Assert.AreEqual(60f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(20f, root_child0.LayoutY);
            Assert.AreEqual(30f, root_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0.LayoutHeight);

            Assert.AreEqual(30f, root_child1.LayoutX);
            Assert.AreEqual(10f, root_child1.LayoutY);
            Assert.AreEqual(30f, root_child1.LayoutWidth);
            Assert.AreEqual(20f, root_child1.LayoutHeight);

            Assert.AreEqual(60f, root_child2.LayoutX);
            Assert.AreEqual(0f, root_child2.LayoutY);
            Assert.AreEqual(30f, root_child2.LayoutWidth);
            Assert.AreEqual(30f, root_child2.LayoutHeight);

            Assert.AreEqual(0f, root_child3.LayoutX);
            Assert.AreEqual(30f, root_child3.LayoutY);
            Assert.AreEqual(30f, root_child3.LayoutWidth);
            Assert.AreEqual(30f, root_child3.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(100f, root.LayoutWidth);
            Assert.AreEqual(60f, root.LayoutHeight);

            Assert.AreEqual(70f, root_child0.LayoutX);
            Assert.AreEqual(20f, root_child0.LayoutY);
            Assert.AreEqual(30f, root_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0.LayoutHeight);

            Assert.AreEqual(40f, root_child1.LayoutX);
            Assert.AreEqual(10f, root_child1.LayoutY);
            Assert.AreEqual(30f, root_child1.LayoutWidth);
            Assert.AreEqual(20f, root_child1.LayoutHeight);

            Assert.AreEqual(10f, root_child2.LayoutX);
            Assert.AreEqual(0f, root_child2.LayoutY);
            Assert.AreEqual(30f, root_child2.LayoutWidth);
            Assert.AreEqual(30f, root_child2.LayoutHeight);

            Assert.AreEqual(70f, root_child3.LayoutX);
            Assert.AreEqual(30f, root_child3.LayoutY);
            Assert.AreEqual(30f, root_child3.LayoutWidth);
            Assert.AreEqual(30f, root_child3.LayoutHeight);
        }

        [Test]
        public void Test_wrap_row_align_items_center()
        {
            YogaNode root = new YogaNode();
            root.FlexDirection = YogaFlexDirection.Row;
            root.AlignItems = YogaAlign.Center;
            root.Wrap = YogaWrap.Wrap;
            root.Width = 100;

            YogaNode root_child0 = new YogaNode();
            root_child0.Width = 30;
            root_child0.Height = 10;
            root.Insert(0, root_child0);

            YogaNode root_child1 = new YogaNode();
            root_child1.Width = 30;
            root_child1.Height = 20;
            root.Insert(1, root_child1);

            YogaNode root_child2 = new YogaNode();
            root_child2.Width = 30;
            root_child2.Height = 30;
            root.Insert(2, root_child2);

            YogaNode root_child3 = new YogaNode();
            root_child3.Width = 30;
            root_child3.Height = 30;
            root.Insert(3, root_child3);
            root.StyleDirection = YogaDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(100f, root.LayoutWidth);
            Assert.AreEqual(60f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(10f, root_child0.LayoutY);
            Assert.AreEqual(30f, root_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0.LayoutHeight);

            Assert.AreEqual(30f, root_child1.LayoutX);
            Assert.AreEqual(5f, root_child1.LayoutY);
            Assert.AreEqual(30f, root_child1.LayoutWidth);
            Assert.AreEqual(20f, root_child1.LayoutHeight);

            Assert.AreEqual(60f, root_child2.LayoutX);
            Assert.AreEqual(0f, root_child2.LayoutY);
            Assert.AreEqual(30f, root_child2.LayoutWidth);
            Assert.AreEqual(30f, root_child2.LayoutHeight);

            Assert.AreEqual(0f, root_child3.LayoutX);
            Assert.AreEqual(30f, root_child3.LayoutY);
            Assert.AreEqual(30f, root_child3.LayoutWidth);
            Assert.AreEqual(30f, root_child3.LayoutHeight);

            root.StyleDirection = YogaDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(100f, root.LayoutWidth);
            Assert.AreEqual(60f, root.LayoutHeight);

            Assert.AreEqual(70f, root_child0.LayoutX);
            Assert.AreEqual(10f, root_child0.LayoutY);
            Assert.AreEqual(30f, root_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0.LayoutHeight);

            Assert.AreEqual(40f, root_child1.LayoutX);
            Assert.AreEqual(5f, root_child1.LayoutY);
            Assert.AreEqual(30f, root_child1.LayoutWidth);
            Assert.AreEqual(20f, root_child1.LayoutHeight);

            Assert.AreEqual(10f, root_child2.LayoutX);
            Assert.AreEqual(0f, root_child2.LayoutY);
            Assert.AreEqual(30f, root_child2.LayoutWidth);
            Assert.AreEqual(30f, root_child2.LayoutHeight);

            Assert.AreEqual(70f, root_child3.LayoutX);
            Assert.AreEqual(30f, root_child3.LayoutY);
            Assert.AreEqual(30f, root_child3.LayoutWidth);
            Assert.AreEqual(30f, root_child3.LayoutHeight);
        }

    }
}
