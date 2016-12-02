/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using NUnit.Framework;
using System;

/**
 * Tests for {@link YogaNode}.
 */
namespace Facebook.Yoga
{
    [TestFixture]
    public class YogaNodeCreateTest
    {
        [Test]
        public void TestSimple()
        {
            YogaNode nodeDefault = new YogaNode();
            YogaNode nodeCreated = YogaNode.Create(flexDirection: YogaFlexDirection.Row);
            Assert.AreEqual(YogaFlexDirection.Row, nodeCreated.FlexDirection);
            Assert.IsFalse(nodeDefault.IsDirty);
            nodeDefault.CopyStyle(nodeCreated);
            Assert.IsTrue(nodeDefault.IsDirty);
        }

        [Test]
        public void TestSame()
        {
            YogaNode nodeDefault = new YogaNode();
            YogaNode nodeCreated = YogaNode.Create();
            Assert.IsFalse(nodeDefault.IsDirty);
            nodeDefault.CopyStyle(nodeCreated);
            Assert.IsFalse(nodeDefault.IsDirty);
        }

        [Test]
        public void TestMultiple()
        {
            YogaNode node = YogaNode.Create(
                positionType: YogaPositionType.Absolute,
                wrap: YogaWrap.Wrap,
                position: new Spacing(top:6, right:4),
                margin: new Spacing(bottom:5, left:3));

            Assert.AreEqual(YogaFlexDirection.Column, node.FlexDirection);
            Assert.AreEqual(YogaPositionType.Absolute, node.PositionType);
            Assert.AreEqual(YogaWrap.Wrap, node.Wrap);
            Assert.AreEqual(6, node.GetPosition(YogaEdge.Top));
            Assert.IsTrue(YogaConstants.IsUndefined(node.GetPosition(YogaEdge.Bottom)));
            Assert.AreEqual(4, node.GetPosition(YogaEdge.Right));
            Assert.IsTrue(YogaConstants.IsUndefined(node.GetPosition(YogaEdge.Left)));
            Assert.AreEqual(0, node.GetMargin(YogaEdge.Top));
            Assert.AreEqual(5, node.GetMargin(YogaEdge.Bottom));
            Assert.AreEqual(3, node.GetMargin(YogaEdge.Left));
            Assert.AreEqual(0, node.GetMargin(YogaEdge.Right));
        }

        [Test]
        public void TestFull()
        {
            YogaNode node = YogaNode.Create(
                styleDirection: YogaDirection.RTL,
                flexDirection: YogaFlexDirection.RowReverse,

                justifyContent: YogaJustify.SpaceAround,
                alignContent: YogaAlign.Center,
                alignItems: YogaAlign.FlexEnd,
                alignSelf: YogaAlign.Stretch,

                positionType: YogaPositionType.Absolute,
                wrap: YogaWrap.Wrap,
                overflow: YogaOverflow.Scroll,

                flex: 1,
                flexGrow: 2,
                flexShrink: 3,
                flexBasis: 4,

                position: new Spacing(top: 5, bottom: 6, left: 7, right: 8),
                margin: new Spacing(top: 9, bottom: 10, left: 11, right: 12),
                padding: new Spacing(top: 13, bottom: 14, left: 15, right: 16),
                border: new Spacing(top: 17, bottom: 18, left: 19, right: 20),

                Width: 21,
                Height: 22,
                MinWidth: 23,
                MinHeight: 24,
                MaxWidth: 25,
                MaxHeight: 26);

            Assert.AreEqual(YogaDirection.RTL, node.StyleDirection);
            Assert.AreEqual(YogaFlexDirection.RowReverse, node.FlexDirection);

            Assert.AreEqual(YogaJustify.SpaceAround, node.JustifyContent);
            Assert.AreEqual(YogaAlign.Center, node.AlignContent);
            Assert.AreEqual(YogaAlign.FlexEnd, node.AlignItems);
            Assert.AreEqual(YogaAlign.Stretch, node.AlignSelf);

            Assert.AreEqual(YogaPositionType.Absolute, node.PositionType);
            Assert.AreEqual(YogaWrap.Wrap, node.Wrap);
            Assert.AreEqual(YogaOverflow.Scroll, node.Overflow);

            Assert.AreEqual(2, node.FlexGrow);
            Assert.AreEqual(3, node.FlexShrink);
            Assert.AreEqual(4, node.FlexBasis);
            node.FlexGrow = YogaConstants.Undefined;
            Assert.AreEqual(1, node.FlexGrow);

            Assert.AreEqual(5, node.GetPosition(YogaEdge.Top));
            Assert.AreEqual(6, node.GetPosition(YogaEdge.Bottom));
            Assert.AreEqual(7, node.GetPosition(YogaEdge.Left));
            Assert.AreEqual(8, node.GetPosition(YogaEdge.Right));

            Assert.AreEqual(9, node.GetMargin(YogaEdge.Top));
            Assert.AreEqual(10, node.GetMargin(YogaEdge.Bottom));
            Assert.AreEqual(11, node.GetMargin(YogaEdge.Left));
            Assert.AreEqual(12, node.GetMargin(YogaEdge.Right));

            Assert.AreEqual(13, node.GetPadding(YogaEdge.Top));
            Assert.AreEqual(14, node.GetPadding(YogaEdge.Bottom));
            Assert.AreEqual(15, node.GetPadding(YogaEdge.Left));
            Assert.AreEqual(16, node.GetPadding(YogaEdge.Right));

            Assert.AreEqual(17, node.GetBorder(YogaEdge.Top));
            Assert.AreEqual(18, node.GetBorder(YogaEdge.Bottom));
            Assert.AreEqual(19, node.GetBorder(YogaEdge.Left));
            Assert.AreEqual(20, node.GetBorder(YogaEdge.Right));

            Assert.AreEqual(21, node.Width);
            Assert.AreEqual(22, node.Height);
            Assert.AreEqual(23, node.MinWidth);
            Assert.AreEqual(24, node.MinHeight);
            Assert.AreEqual(25, node.MaxWidth);
            Assert.AreEqual(26, node.MaxHeight);
        }
    }
}
