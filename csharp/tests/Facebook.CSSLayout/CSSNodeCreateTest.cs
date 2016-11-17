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
 * Tests for {@link CSSNode}.
 */
namespace Facebook.CSSLayout
{
    [TestFixture]
    public class CSSNodeCreateTest
    {
        [Test]
        public void TestSimple()
        {
            CSSNode nodeDefault = new CSSNode();
            CSSNode nodeCreated = CSSNode.Create(flexDirection: CSSFlexDirection.Row);
            Assert.AreEqual(CSSFlexDirection.Row, nodeCreated.FlexDirection);
            Assert.IsFalse(nodeDefault.IsDirty);
            nodeDefault.CopyStyle(nodeCreated);
            Assert.IsTrue(nodeDefault.IsDirty);
        }

        [Test]
        public void TestSame()
        {
            CSSNode nodeDefault = new CSSNode();
            CSSNode nodeCreated = CSSNode.Create();
            Assert.IsFalse(nodeDefault.IsDirty);
            nodeDefault.CopyStyle(nodeCreated);
            Assert.IsFalse(nodeDefault.IsDirty);
        }

        [Test]
        public void TestMultiple()
        {
            CSSNode node = CSSNode.Create(
                positionType: CSSPositionType.Absolute,
                wrap: CSSWrap.Wrap,
                position: new Spacing(top:6, right:4),
                margin: new Spacing(bottom:5, left:3));

            Assert.AreEqual(CSSFlexDirection.Column, node.FlexDirection);
            Assert.AreEqual(CSSPositionType.Absolute, node.PositionType);
            Assert.AreEqual(CSSWrap.Wrap, node.Wrap);
            Assert.AreEqual(6, node.GetPosition(CSSEdge.Top));
            Assert.IsTrue(CSSConstants.IsUndefined(node.GetPosition(CSSEdge.Bottom)));
            Assert.AreEqual(4, node.GetPosition(CSSEdge.Right));
            Assert.IsTrue(CSSConstants.IsUndefined(node.GetPosition(CSSEdge.Left)));
            Assert.AreEqual(0, node.GetMargin(CSSEdge.Top));
            Assert.AreEqual(5, node.GetMargin(CSSEdge.Bottom));
            Assert.AreEqual(3, node.GetMargin(CSSEdge.Left));
            Assert.AreEqual(0, node.GetMargin(CSSEdge.Right));
        }

        [Test]
        public void TestFull()
        {
            CSSNode node = CSSNode.Create(
                styleDirection: CSSDirection.RTL,
                flexDirection: CSSFlexDirection.RowReverse,

                justifyContent: CSSJustify.SpaceAround,
                alignContent: CSSAlign.Center,
                alignItems: CSSAlign.FlexEnd,
                alignSelf: CSSAlign.Stretch,

                positionType: CSSPositionType.Absolute,
                wrap: CSSWrap.Wrap,
                overflow: CSSOverflow.Scroll,

                flex: 1,
                flexGrow: 2,
                flexShrink: 3,
                flexBasis: 4,

                position: new Spacing(top: 5, bottom: 6, left: 7, right: 8),
                margin: new Spacing(top: 9, bottom: 10, left: 11, right: 12),
                padding: new Spacing(top: 13, bottom: 14, left: 15, right: 16),
                border: new Spacing(top: 17, bottom: 18, left: 19, right: 20),

                styleWidth: 21,
                styleHeight: 22,
                styleMinWidth: 23,
                styleMinHeight: 24,
                styleMaxWidth: 25,
                styleMaxHeight: 26);

            Assert.AreEqual(CSSDirection.RTL, node.StyleDirection);
            Assert.AreEqual(CSSFlexDirection.RowReverse, node.FlexDirection);

            Assert.AreEqual(CSSJustify.SpaceAround, node.JustifyContent);
            Assert.AreEqual(CSSAlign.Center, node.AlignContent);
            Assert.AreEqual(CSSAlign.FlexEnd, node.AlignItems);
            Assert.AreEqual(CSSAlign.Stretch, node.AlignSelf);

            Assert.AreEqual(CSSPositionType.Absolute, node.PositionType);
            Assert.AreEqual(CSSWrap.Wrap, node.Wrap);
            Assert.AreEqual(CSSOverflow.Scroll, node.Overflow);

            Assert.AreEqual(2, node.FlexGrow);
            Assert.AreEqual(3, node.FlexShrink);
            Assert.AreEqual(4, node.FlexBasis);
            node.FlexGrow = CSSConstants.Undefined;
            Assert.AreEqual(1, node.FlexGrow);

            Assert.AreEqual(5, node.GetPosition(CSSEdge.Top));
            Assert.AreEqual(6, node.GetPosition(CSSEdge.Bottom));
            Assert.AreEqual(7, node.GetPosition(CSSEdge.Left));
            Assert.AreEqual(8, node.GetPosition(CSSEdge.Right));

            Assert.AreEqual(9, node.GetMargin(CSSEdge.Top));
            Assert.AreEqual(10, node.GetMargin(CSSEdge.Bottom));
            Assert.AreEqual(11, node.GetMargin(CSSEdge.Left));
            Assert.AreEqual(12, node.GetMargin(CSSEdge.Right));

            Assert.AreEqual(13, node.GetPadding(CSSEdge.Top));
            Assert.AreEqual(14, node.GetPadding(CSSEdge.Bottom));
            Assert.AreEqual(15, node.GetPadding(CSSEdge.Left));
            Assert.AreEqual(16, node.GetPadding(CSSEdge.Right));

            Assert.AreEqual(17, node.GetBorder(CSSEdge.Top));
            Assert.AreEqual(18, node.GetBorder(CSSEdge.Bottom));
            Assert.AreEqual(19, node.GetBorder(CSSEdge.Left));
            Assert.AreEqual(20, node.GetBorder(CSSEdge.Right));

            Assert.AreEqual(21, node.StyleWidth);
            Assert.AreEqual(22, node.StyleHeight);
            Assert.AreEqual(23, node.StyleMinWidth);
            Assert.AreEqual(24, node.StyleMinHeight);
            Assert.AreEqual(25, node.StyleMaxWidth);
            Assert.AreEqual(26, node.StyleMaxHeight);
        }
    }
}
