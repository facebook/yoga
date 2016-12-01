/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

 // @Generated by gentest/gentest.rb from gentest/fixtures/CSSLayoutPaddingTest.html

using System;
using NUnit.Framework;

namespace Facebook.CSSLayout
{
    [TestFixture]
    public class CSSLayoutPaddingTest
    {
        [Test]
        public void Test_padding_no_size()
        {
            CSSNode root = new CSSNode();
            root.SetPadding(CSSEdge.Left, 10f);
            root.SetPadding(CSSEdge.Top, 10f);
            root.SetPadding(CSSEdge.Right, 10f);
            root.SetPadding(CSSEdge.Bottom, 10f);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(20f, root.LayoutWidth);
            Assert.AreEqual(20f, root.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(20f, root.LayoutWidth);
            Assert.AreEqual(20f, root.LayoutHeight);
        }

        [Test]
        public void Test_padding_container_match_child()
        {
            CSSNode root = new CSSNode();
            root.SetPadding(CSSEdge.Left, 10f);
            root.SetPadding(CSSEdge.Top, 10f);
            root.SetPadding(CSSEdge.Right, 10f);
            root.SetPadding(CSSEdge.Bottom, 10f);

            CSSNode root_child0 = new CSSNode();
            root_child0.StyleWidth = 10f;
            root_child0.StyleHeight = 10f;
            root.Insert(0, root_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(30f, root.LayoutWidth);
            Assert.AreEqual(30f, root.LayoutHeight);

            Assert.AreEqual(10f, root_child0.LayoutX);
            Assert.AreEqual(10f, root_child0.LayoutY);
            Assert.AreEqual(10f, root_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(30f, root.LayoutWidth);
            Assert.AreEqual(30f, root.LayoutHeight);

            Assert.AreEqual(10f, root_child0.LayoutX);
            Assert.AreEqual(10f, root_child0.LayoutY);
            Assert.AreEqual(10f, root_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0.LayoutHeight);
        }

        [Test]
        public void Test_padding_flex_child()
        {
            CSSNode root = new CSSNode();
            root.SetPadding(CSSEdge.Left, 10f);
            root.SetPadding(CSSEdge.Top, 10f);
            root.SetPadding(CSSEdge.Right, 10f);
            root.SetPadding(CSSEdge.Bottom, 10f);
            root.StyleWidth = 100f;
            root.StyleHeight = 100f;

            CSSNode root_child0 = new CSSNode();
            root_child0.FlexGrow = 1f;
            root_child0.StyleWidth = 10f;
            root.Insert(0, root_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(100f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(10f, root_child0.LayoutX);
            Assert.AreEqual(10f, root_child0.LayoutY);
            Assert.AreEqual(10f, root_child0.LayoutWidth);
            Assert.AreEqual(80f, root_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(100f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(80f, root_child0.LayoutX);
            Assert.AreEqual(10f, root_child0.LayoutY);
            Assert.AreEqual(10f, root_child0.LayoutWidth);
            Assert.AreEqual(80f, root_child0.LayoutHeight);
        }

        [Test]
        public void Test_padding_stretch_child()
        {
            CSSNode root = new CSSNode();
            root.SetPadding(CSSEdge.Left, 10f);
            root.SetPadding(CSSEdge.Top, 10f);
            root.SetPadding(CSSEdge.Right, 10f);
            root.SetPadding(CSSEdge.Bottom, 10f);
            root.StyleWidth = 100f;
            root.StyleHeight = 100f;

            CSSNode root_child0 = new CSSNode();
            root_child0.StyleHeight = 10f;
            root.Insert(0, root_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(100f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(10f, root_child0.LayoutX);
            Assert.AreEqual(10f, root_child0.LayoutY);
            Assert.AreEqual(80f, root_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(100f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(10f, root_child0.LayoutX);
            Assert.AreEqual(10f, root_child0.LayoutY);
            Assert.AreEqual(80f, root_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0.LayoutHeight);
        }

        [Test]
        public void Test_padding_center_child()
        {
            CSSNode root = new CSSNode();
            root.JustifyContent = CSSJustify.Center;
            root.AlignItems = CSSAlign.Center;
            root.SetPadding(CSSEdge.Start, 10f);
            root.SetPadding(CSSEdge.End, 20f);
            root.SetPadding(CSSEdge.Bottom, 20f);
            root.StyleWidth = 100f;
            root.StyleHeight = 100f;

            CSSNode root_child0 = new CSSNode();
            root_child0.StyleWidth = 10f;
            root_child0.StyleHeight = 10f;
            root.Insert(0, root_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(100f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(40f, root_child0.LayoutX);
            Assert.AreEqual(35f, root_child0.LayoutY);
            Assert.AreEqual(10f, root_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(100f, root.LayoutWidth);
            Assert.AreEqual(100f, root.LayoutHeight);

            Assert.AreEqual(50f, root_child0.LayoutX);
            Assert.AreEqual(35f, root_child0.LayoutY);
            Assert.AreEqual(10f, root_child0.LayoutWidth);
            Assert.AreEqual(10f, root_child0.LayoutHeight);
        }

        [Test]
        public void Test_child_with_padding_align_end()
        {
            CSSNode root = new CSSNode();
            root.JustifyContent = CSSJustify.FlexEnd;
            root.AlignItems = CSSAlign.FlexEnd;
            root.StyleWidth = 200f;
            root.StyleHeight = 200f;

            CSSNode root_child0 = new CSSNode();
            root_child0.SetPadding(CSSEdge.Left, 20f);
            root_child0.SetPadding(CSSEdge.Top, 20f);
            root_child0.SetPadding(CSSEdge.Right, 20f);
            root_child0.SetPadding(CSSEdge.Bottom, 20f);
            root_child0.StyleWidth = 100f;
            root_child0.StyleHeight = 100f;
            root.Insert(0, root_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(100f, root_child0.LayoutX);
            Assert.AreEqual(100f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(100f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);
        }

        [Test]
        public void Test_child_with_padding_align_end1()
        {
            CSSNode root = new CSSNode();
            root.JustifyContent = CSSJustify.FlexEnd;
            root.AlignItems = CSSAlign.FlexEnd;
            root.StyleWidth = 200f;
            root.StyleHeight = 200f;

            CSSNode root_child0 = new CSSNode();
            root_child0.SetPadding(CSSEdge.Left, 20f);
            root_child0.SetPadding(CSSEdge.Top, 20f);
            root_child0.SetPadding(CSSEdge.Right, 20f);
            root_child0.SetPadding(CSSEdge.Bottom, 20f);
            root_child0.StyleWidth = 100f;
            root_child0.StyleHeight = 100f;
            root.Insert(0, root_child0);

            CSSNode root_child0_child0 = new CSSNode();
            root_child0_child0.StyleWidth = 100f;
            root_child0_child0.StyleHeight = 100f;
            root_child0.Insert(0, root_child0_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(100f, root_child0.LayoutX);
            Assert.AreEqual(100f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(100f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(-20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);
        }

        [Test]
        public void Test_child_with_padding_align_end2()
        {
            CSSNode root = new CSSNode();
            root.AlignItems = CSSAlign.FlexEnd;
            root.StyleWidth = 200f;
            root.StyleHeight = 200f;

            CSSNode root_child0 = new CSSNode();
            root_child0.SetPadding(CSSEdge.Left, 20f);
            root_child0.SetPadding(CSSEdge.Top, 20f);
            root_child0.SetPadding(CSSEdge.Right, 20f);
            root_child0.SetPadding(CSSEdge.Bottom, 20f);
            root_child0.StyleWidth = 100f;
            root_child0.StyleHeight = 100f;
            root.Insert(0, root_child0);

            CSSNode root_child0_child0 = new CSSNode();
            root_child0_child0.StyleWidth = 100f;
            root_child0_child0.StyleHeight = 100f;
            root_child0.Insert(0, root_child0_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(100f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(-20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);
        }

        [Test]
        public void Test_child_with_padding_align_end3()
        {
            CSSNode root = new CSSNode();
            root.JustifyContent = CSSJustify.FlexEnd;
            root.StyleWidth = 200f;
            root.StyleHeight = 200f;

            CSSNode root_child0 = new CSSNode();
            root_child0.SetPadding(CSSEdge.Left, 20f);
            root_child0.SetPadding(CSSEdge.Top, 20f);
            root_child0.SetPadding(CSSEdge.Right, 20f);
            root_child0.SetPadding(CSSEdge.Bottom, 20f);
            root_child0.StyleWidth = 100f;
            root_child0.StyleHeight = 100f;
            root.Insert(0, root_child0);

            CSSNode root_child0_child0 = new CSSNode();
            root_child0_child0.StyleWidth = 100f;
            root_child0_child0.StyleHeight = 100f;
            root_child0.Insert(0, root_child0_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(100f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(100f, root_child0.LayoutX);
            Assert.AreEqual(100f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(-20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);
        }

        [Test]
        public void Test_child_with_padding_align_end4()
        {
            CSSNode root = new CSSNode();
            root.JustifyContent = CSSJustify.FlexEnd;
            root.AlignItems = CSSAlign.FlexStart;
            root.StyleWidth = 200f;
            root.StyleHeight = 200f;

            CSSNode root_child0 = new CSSNode();
            root_child0.SetPadding(CSSEdge.Left, 20f);
            root_child0.SetPadding(CSSEdge.Top, 20f);
            root_child0.SetPadding(CSSEdge.Right, 20f);
            root_child0.SetPadding(CSSEdge.Bottom, 20f);
            root_child0.StyleWidth = 100f;
            root_child0.StyleHeight = 100f;
            root.Insert(0, root_child0);

            CSSNode root_child0_child0 = new CSSNode();
            root_child0_child0.StyleWidth = 100f;
            root_child0_child0.StyleHeight = 100f;
            root_child0.Insert(0, root_child0_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(100f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(100f, root_child0.LayoutX);
            Assert.AreEqual(100f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(-20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);
        }

        [Test]
        public void Test_child_with_padding_align_end5()
        {
            CSSNode root = new CSSNode();
            root.JustifyContent = CSSJustify.FlexEnd;
            root.AlignItems = CSSAlign.FlexEnd;
            root.StyleWidth = 200f;
            root.StyleHeight = 200f;

            CSSNode root_child0 = new CSSNode();
            root_child0.SetPadding(CSSEdge.Left, 20f);
            root_child0.SetPadding(CSSEdge.Top, 20f);
            root_child0.SetPadding(CSSEdge.Right, 20f);
            root_child0.SetPadding(CSSEdge.Bottom, 20f);
            root_child0.StyleWidth = 100f;
            root_child0.StyleHeight = 100f;
            root.Insert(0, root_child0);

            CSSNode root_child0_child0 = new CSSNode();
            root_child0_child0.StyleWidth = 100f;
            root_child0_child0.StyleHeight = 100f;
            root_child0.Insert(0, root_child0_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(100f, root_child0.LayoutX);
            Assert.AreEqual(100f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(100f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(-20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);
        }

        [Test]
        public void Test_child_with_padding_align_end6()
        {
            CSSNode root = new CSSNode();
            root.JustifyContent = CSSJustify.SpaceAround;
            root.AlignItems = CSSAlign.FlexEnd;
            root.StyleWidth = 200f;
            root.StyleHeight = 200f;

            CSSNode root_child0 = new CSSNode();
            root_child0.SetPadding(CSSEdge.Left, 20f);
            root_child0.SetPadding(CSSEdge.Top, 20f);
            root_child0.SetPadding(CSSEdge.Right, 20f);
            root_child0.SetPadding(CSSEdge.Bottom, 20f);
            root_child0.StyleWidth = 100f;
            root_child0.StyleHeight = 100f;
            root.Insert(0, root_child0);

            CSSNode root_child0_child0 = new CSSNode();
            root_child0_child0.StyleWidth = 100f;
            root_child0_child0.StyleHeight = 100f;
            root_child0.Insert(0, root_child0_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(100f, root_child0.LayoutX);
            Assert.AreEqual(50f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(50f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(-20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);
        }

        [Test]
        public void Test_child_with_padding_align_end7()
        {
            CSSNode root = new CSSNode();
            root.JustifyContent = CSSJustify.SpaceBetween;
            root.AlignItems = CSSAlign.FlexEnd;
            root.StyleWidth = 200f;
            root.StyleHeight = 200f;

            CSSNode root_child0 = new CSSNode();
            root_child0.SetPadding(CSSEdge.Left, 20f);
            root_child0.SetPadding(CSSEdge.Top, 20f);
            root_child0.SetPadding(CSSEdge.Right, 20f);
            root_child0.SetPadding(CSSEdge.Bottom, 20f);
            root_child0.StyleWidth = 100f;
            root_child0.StyleHeight = 100f;
            root.Insert(0, root_child0);

            CSSNode root_child0_child0 = new CSSNode();
            root_child0_child0.StyleWidth = 100f;
            root_child0_child0.StyleHeight = 100f;
            root_child0.Insert(0, root_child0_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(100f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(0f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(-20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);
        }

        [Test]
        public void Test_child_with_padding_align_end8()
        {
            CSSNode root = new CSSNode();
            root.JustifyContent = CSSJustify.Center;
            root.AlignItems = CSSAlign.FlexEnd;
            root.StyleWidth = 200f;
            root.StyleHeight = 200f;

            CSSNode root_child0 = new CSSNode();
            root_child0.SetPadding(CSSEdge.Left, 20f);
            root_child0.SetPadding(CSSEdge.Top, 20f);
            root_child0.SetPadding(CSSEdge.Right, 20f);
            root_child0.SetPadding(CSSEdge.Bottom, 20f);
            root_child0.StyleWidth = 100f;
            root_child0.StyleHeight = 100f;
            root.Insert(0, root_child0);

            CSSNode root_child0_child0 = new CSSNode();
            root_child0_child0.StyleWidth = 100f;
            root_child0_child0.StyleHeight = 100f;
            root_child0.Insert(0, root_child0_child0);
            root.StyleDirection = CSSDirection.LTR;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(100f, root_child0.LayoutX);
            Assert.AreEqual(50f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);

            root.StyleDirection = CSSDirection.RTL;
            root.CalculateLayout();

            Assert.AreEqual(0f, root.LayoutX);
            Assert.AreEqual(0f, root.LayoutY);
            Assert.AreEqual(200f, root.LayoutWidth);
            Assert.AreEqual(200f, root.LayoutHeight);

            Assert.AreEqual(0f, root_child0.LayoutX);
            Assert.AreEqual(50f, root_child0.LayoutY);
            Assert.AreEqual(100f, root_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0.LayoutHeight);

            Assert.AreEqual(-20f, root_child0_child0.LayoutX);
            Assert.AreEqual(20f, root_child0_child0.LayoutY);
            Assert.AreEqual(100f, root_child0_child0.LayoutWidth);
            Assert.AreEqual(100f, root_child0_child0.LayoutHeight);
        }

    }
}
