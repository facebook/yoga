/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

using NUnit.Framework;
using System;

/**
 * Tests for {@link YogaNode}.
 */
namespace Facebook.Yoga
{
    [TestFixture]
    public class YogaNodeSpacingTest
    {
        [Test]
        public void TestObjectInitializer()
        {
            YogaNode node = new YogaNode
            {
                Top = 1,
                Bottom = 2,
                Left = 3,
                Right = 4,

                MarginTop = 5,
                MarginBottom = 6,
                MarginLeft = 7,
                MarginRight = 8,

                PaddingTop = 9,
                PaddingBottom = 10,
                PaddingLeft = 11,
                PaddingRight = 12,

                BorderTopWidth = 13,
                BorderBottomWidth = 14,
                BorderLeftWidth = 15,
                BorderRightWidth = 16,
            };

            Assert.AreEqual(1.Pt(), node.Top);
            Assert.AreEqual(2.Pt(), node.Bottom);
            Assert.AreEqual(3.Pt(), node.Left);
            Assert.AreEqual(4.Pt(), node.Right);

            Assert.AreEqual(5.Pt(), node.MarginTop);
            Assert.AreEqual(6.Pt(), node.MarginBottom);
            Assert.AreEqual(7.Pt(), node.MarginLeft);
            Assert.AreEqual(8.Pt(), node.MarginRight);

            Assert.AreEqual(9.Pt(), node.PaddingTop);
            Assert.AreEqual(10.Pt(), node.PaddingBottom);
            Assert.AreEqual(11.Pt(), node.PaddingLeft);
            Assert.AreEqual(12.Pt(), node.PaddingRight);

            Assert.AreEqual(13, node.BorderTopWidth);
            Assert.AreEqual(14, node.BorderBottomWidth);
            Assert.AreEqual(15, node.BorderLeftWidth);
            Assert.AreEqual(16, node.BorderRightWidth);
        }

        [Test]
        public void TestWriteRead()
        {
            YogaNode node = new YogaNode();

            node.Top = 1;
            node.Bottom = 2;
            node.Left = 3;
            node.Right = 4;

            node.MarginTop = 5;
            node.MarginBottom = 6;
            node.MarginLeft = 7;
            node.MarginRight = 8;

            node.PaddingTop = 9;
            node.PaddingBottom = 10;
            node.PaddingLeft = 11;
            node.PaddingRight = 12;

            node.BorderTopWidth = 13;
            node.BorderBottomWidth = 14;
            node.BorderLeftWidth = 15;
            node.BorderRightWidth = 16;

            Assert.AreEqual(1.Pt(), node.Top);
            Assert.AreEqual(2.Pt(), node.Bottom);
            Assert.AreEqual(3.Pt(), node.Left);
            Assert.AreEqual(4.Pt(), node.Right);

            Assert.AreEqual(5.Pt(), node.MarginTop);
            Assert.AreEqual(6.Pt(), node.MarginBottom);
            Assert.AreEqual(7.Pt(), node.MarginLeft);
            Assert.AreEqual(8.Pt(), node.MarginRight);

            Assert.AreEqual(9.Pt(), node.PaddingTop);
            Assert.AreEqual(10.Pt(), node.PaddingBottom);
            Assert.AreEqual(11.Pt(), node.PaddingLeft);
            Assert.AreEqual(12.Pt(), node.PaddingRight);

            Assert.AreEqual(13, node.BorderTopWidth);
            Assert.AreEqual(14, node.BorderBottomWidth);
            Assert.AreEqual(15, node.BorderLeftWidth);
            Assert.AreEqual(16, node.BorderRightWidth);
        }
    }
}
