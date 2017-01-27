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

            Assert.AreEqual(1.Px(), node.Top);
            Assert.AreEqual(2.Px(), node.Bottom);
            Assert.AreEqual(3.Px(), node.Left);
            Assert.AreEqual(4.Px(), node.Right);

            Assert.AreEqual(5.Px(), node.MarginTop);
            Assert.AreEqual(6.Px(), node.MarginBottom);
            Assert.AreEqual(7.Px(), node.MarginLeft);
            Assert.AreEqual(8.Px(), node.MarginRight);

            Assert.AreEqual(9.Px(), node.PaddingTop);
            Assert.AreEqual(10.Px(), node.PaddingBottom);
            Assert.AreEqual(11.Px(), node.PaddingLeft);
            Assert.AreEqual(12.Px(), node.PaddingRight);

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

            Assert.AreEqual(1.Px(), node.Top);
            Assert.AreEqual(2.Px(), node.Bottom);
            Assert.AreEqual(3.Px(), node.Left);
            Assert.AreEqual(4.Px(), node.Right);

            Assert.AreEqual(5.Px(), node.MarginTop);
            Assert.AreEqual(6.Px(), node.MarginBottom);
            Assert.AreEqual(7.Px(), node.MarginLeft);
            Assert.AreEqual(8.Px(), node.MarginRight);

            Assert.AreEqual(9.Px(), node.PaddingTop);
            Assert.AreEqual(10.Px(), node.PaddingBottom);
            Assert.AreEqual(11.Px(), node.PaddingLeft);
            Assert.AreEqual(12.Px(), node.PaddingRight);

            Assert.AreEqual(13, node.BorderTopWidth);
            Assert.AreEqual(14, node.BorderBottomWidth);
            Assert.AreEqual(15, node.BorderLeftWidth);
            Assert.AreEqual(16, node.BorderRightWidth);
        }
    }
}
