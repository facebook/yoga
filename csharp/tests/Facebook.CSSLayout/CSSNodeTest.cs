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
        public void TestCannotAddChildToMultipleParents()
        {
            CSSNode parent1 = new CSSNode();
            parent1.Initialize();
            CSSNode parent2 = new CSSNode();
            parent2.Initialize();
            CSSNode child = new CSSNode();
            child.Initialize();

            parent1.Insert(0, child);
            parent2.Insert(0, child);
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
            ForceGC();
            Assert.AreEqual(0, CSSNode.GetInstanceCount());
            CSSNode node = new CSSNode();
            Assert.AreEqual(0, CSSNode.GetInstanceCount());
            node.Initialize();
            Assert.AreEqual(1, CSSNode.GetInstanceCount());
            node.Dispose();
            Assert.AreEqual(0, CSSNode.GetInstanceCount());
        }

        [Test]
        public void TestDisposeWithUsing()
        {
            ForceGC();
            Assert.AreEqual(0, CSSNode.GetInstanceCount());
            using (CSSNode node = new CSSNode())
            {
                Assert.AreEqual(0, CSSNode.GetInstanceCount());
                node.Initialize();
                Assert.AreEqual(1, CSSNode.GetInstanceCount());
            }
            Assert.AreEqual(0, CSSNode.GetInstanceCount());
        }

        [Test]
        public void TestDestructor()
        {
            ForceGC();
            Assert.AreEqual(0, CSSNode.GetInstanceCount());
            TestDestructorForGC();
            ForceGC();
            Assert.AreEqual(0, CSSNode.GetInstanceCount());
        }

        private void TestDestructorForGC()
        {
            CSSNode node = new CSSNode();
            Assert.AreEqual(0, CSSNode.GetInstanceCount());
            node.Initialize();
            Assert.AreEqual(1, CSSNode.GetInstanceCount());
            node = null;
        }

        [Test]
        public void TestDestructorWithChildren()
        {
            ForceGC();
            Assert.AreEqual(0, CSSNode.GetInstanceCount());
            TestDestructorWithChildrenForGC1();
            ForceGC();
            Assert.AreEqual(0, CSSNode.GetInstanceCount());
        }

        private void TestDestructorWithChildrenForGC1()
        {
            CSSNode node = new CSSNode();
            Assert.AreEqual(0, CSSNode.GetInstanceCount());
            node.Initialize();
            Assert.AreEqual(1, CSSNode.GetInstanceCount());

            TestDestructorWithChildrenForGC2(node, 1);
            ForceGC();
            Assert.AreEqual(2, CSSNode.GetInstanceCount());

            TestDestructorWithChildrenForGC2(node, 2);
            ForceGC();
            Assert.AreEqual(3, CSSNode.GetInstanceCount());

            node = null;
        }

        private void TestDestructorWithChildrenForGC2(CSSNode parent, int count)
        {
            CSSNode child = new CSSNode();
            Assert.AreEqual(count, CSSNode.GetInstanceCount());
            child.Initialize();
            Assert.AreEqual(count + 1, CSSNode.GetInstanceCount());

            parent.Insert(0, child);
            child = null;
        }

        private void ForceGC()
        {
            GC.Collect(GC.MaxGeneration);
            GC.WaitForPendingFinalizers();
        }
    }
}
