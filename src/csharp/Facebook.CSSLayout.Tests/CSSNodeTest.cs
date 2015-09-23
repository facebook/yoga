/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using System;
using NUnit.Framework;

namespace Facebook.CSSLayout.Tests
{
    /**
     * Tests for {@link CSSNode}.
     */
    public class CSSNodeTest
    {

        [Test]
        public void testAddChildGetParent()
        {
            CSSNode parent = new CSSNode();
            CSSNode child = new CSSNode();

            Assert.Null(child.getParent());
            Assert.AreEqual(0, parent.getChildCount());

            parent.addChildAt(child, 0);

            Assert.AreEqual(1, parent.getChildCount());
            Assert.AreEqual(child, parent.getChildAt(0));
            Assert.AreEqual(parent, child.getParent());

            parent.removeChildAt(0);

            Assert.Null(child.getParent());
            Assert.AreEqual(0, parent.getChildCount());
        }

        [Test, ExpectedException(typeof(InvalidOperationException))]
        public void testCannotAddChildToMultipleParents()
        {
            CSSNode parent1 = new CSSNode();
            CSSNode parent2 = new CSSNode();
            CSSNode child = new CSSNode();

            parent1.addChildAt(child, 0);
            parent2.addChildAt(child, 0);
        }
    }
}
