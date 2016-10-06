/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using NUnit.Framework;

/**
 * Tests for {@link CSSNode}.
 */
namespace Facebook.CSSLayout
{
    [TestFixture]
    public class CSSNodeTest
    {
        [Test]
        public void TestAddChildGetParent()
        {
            CSSNode parent = new CSSNode();
            parent.Initialize();
            CSSNode child = new CSSNode();
            child.Initialize();
    
            Assert.IsNull(child.Parent);
            Assert.AreEqual(0, parent.Count);
    
            parent.Insert(0, child);
    
            Assert.AreEqual(1, parent.Count);
            Assert.AreEqual(child, parent[0]);
            Assert.AreEqual(parent, child.Parent);
    
            parent.RemoveAt(0);
    
            Assert.IsNull(child.Parent);
            Assert.AreEqual(0, parent.Count);
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestAlreadyInitialize()
        {
            CSSNode node = new CSSNode();
            node.Initialize();
            node.Initialize();
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestNullNativePointer()
        {
            CSSNode node = new CSSNode();
            node.CalculateLayout();
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestNullNativePointerWithReset()
        {
            CSSNode node = new CSSNode();
            node.Reset();
        }

        [Test]
        [ExpectedException("System.ObjectDisposedException")]
        public void TestDisposed()
        {
            CSSNode node = new CSSNode();
            node.Initialize();
            node.Dispose();
            node.CalculateLayout();
        }

        [Test]
        public void TestReset()
        {
            CSSNode node = new CSSNode();
            node.Initialize();
            node.Reset();
            node.Initialize();
        }

        [Test]
        public void TestDispose()
        {
            CSSNode node = new CSSNode();
            node.Initialize();
            node.Dispose();
        }

        [Test]
        public void TestDestructor()
        {
            CSSNode node = new CSSNode();
            node.Initialize();
        }
    }
}
