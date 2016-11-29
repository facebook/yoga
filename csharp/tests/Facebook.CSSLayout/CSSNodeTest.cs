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
            CSSNode child = new CSSNode();

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
        public void TestChildren()
        {
            CSSNode parent = new CSSNode();
            foreach (CSSNode node in parent) {
                Assert.Fail(node.ToString());
            }

            CSSNode child0 = new CSSNode();
            Assert.AreEqual(-1, parent.IndexOf(child0));
            parent.Insert(0, child0);
            foreach (CSSNode node in parent) {
                Assert.AreEqual(0, parent.IndexOf(node));
            }

            CSSNode child1 = new CSSNode();
            parent.Insert(1, child1);
            int index = 0;
            foreach (CSSNode node in parent) {
                Assert.AreEqual(index++, parent.IndexOf(node));
            }

            parent.RemoveAt(0);
            Assert.AreEqual(-1, parent.IndexOf(child0));
            Assert.AreEqual(0, parent.IndexOf(child1));

            parent.Clear();
            Assert.AreEqual(0, parent.Count);

            parent.Clear();
            Assert.AreEqual(0, parent.Count);
        }

        [Test]
        [ExpectedException("System.NullReferenceException")]
        public void TestRemoveAtFromEmpty()
        {
            CSSNode parent = new CSSNode();
            parent.RemoveAt(0);
        }

        [Test]
        [ExpectedException("System.ArgumentOutOfRangeException")]
        public void TestRemoveAtOutOfRange()
        {
            CSSNode parent = new CSSNode();
            CSSNode child = new CSSNode();
            parent.Insert(0, child);
            parent.RemoveAt(1);
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestCannotAddChildToMultipleParents()
        {
            CSSNode parent1 = new CSSNode();
            CSSNode parent2 = new CSSNode();
            CSSNode child = new CSSNode();

            parent1.Insert(0, child);
            parent2.Insert(0, child);
        }

        [Test]
        public void TestReset()
        {
            int instanceCount = CSSNode.GetInstanceCount();
            CSSNode node = new CSSNode();
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());
            node.Reset();
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestResetParent()
        {
            CSSNode parent = new CSSNode();
            CSSNode child = new CSSNode();
            parent.Insert(0, child);
            parent.Reset();
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestResetChild()
        {
            CSSNode parent = new CSSNode();
            CSSNode child = new CSSNode();
            parent.Insert(0, child);
            child.Reset();
        }

        [Test]
        public void TestClear()
        {
            int instanceCount = CSSNode.GetInstanceCount();
            CSSNode parent = new CSSNode();
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());
            CSSNode child = new CSSNode();
            Assert.AreEqual(instanceCount + 2, CSSNode.GetInstanceCount());
            parent.Insert(0, child);
            Assert.AreEqual(1, parent.Count);
            Assert.AreEqual(parent, child.Parent);
            parent.Clear();
            Assert.AreEqual(0, parent.Count);
            Assert.IsNull(child.Parent);
            Assert.AreEqual(instanceCount + 2, CSSNode.GetInstanceCount());
        }

        [Test]
        public void TestMeasureFunc()
        {
            CSSNode node = new CSSNode();
            node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(100, 150);
            });
            node.CalculateLayout();
            Assert.AreEqual(100, node.LayoutWidth);
            Assert.AreEqual(150, node.LayoutHeight);
        }

        [Test]
        public void TestMeasureFuncWithFloat()
        {
            CSSNode node = new CSSNode();
            node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(123.4f, 81.7f);
            });
            node.CalculateLayout();
            Assert.AreEqual(123, node.LayoutWidth);
            Assert.AreEqual(81, node.LayoutHeight);
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestChildWithMeasureFunc()
        {
            CSSNode node = new CSSNode();
            node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(100, 150);
            });
            CSSNode child = new CSSNode();
            node.Insert(0, child);
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestMeasureFuncWithChild()
        {
            CSSNode node = new CSSNode();
            CSSNode child = new CSSNode();
            node.Insert(0, child);
            node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(100, 150);
            });
        }

        [Test]
        public void TestPrint()
        {
            CSSNode parent = new CSSNode();
            parent.Width = 100;
            parent.Height = 120;
            CSSNode child0 = new CSSNode();
            child0.Width = 30;
            child0.Height = 40;
            CSSNode child1 = new CSSNode();
            child1.Width = 35;
            child1.Height = 45;
            parent.Insert(0, child0);
            parent.Insert(0, child1);
            parent.CalculateLayout();
            Assert.AreEqual(parent.Print(), "{layout: {width: 100, height: 120, top: 0, left: 0}, flexDirection: 'column', alignItems: 'stretch', flexGrow: 0, flexShrink: 0, overflow: 'visible', width: 100, height: 120, children: [\n  {layout: {width: 35, height: 45, top: 0, left: 0}, flexDirection: 'column', alignItems: 'stretch', flexGrow: 0, flexShrink: 0, overflow: 'visible', width: 35, height: 45, },\n  {layout: {width: 30, height: 40, top: 45, left: 0}, flexDirection: 'column', alignItems: 'stretch', flexGrow: 0, flexShrink: 0, overflow: 'visible', width: 30, height: 40, },\n]},\n");
        }

        [Test]
        public void TestCopyStyle()
        {
            CSSNode node0 = new CSSNode();
            Assert.IsTrue(CSSConstants.IsUndefined(node0.MaxHeight));

            CSSNode node1 = new CSSNode();
            node1.MaxHeight = 100;

            node0.CopyStyle(node1);
            Assert.AreEqual(100, node0.MaxHeight);
        }

#if !UNITY_EDITOR
        private void ForceGC()
        {
            GC.Collect(GC.MaxGeneration);
            GC.WaitForPendingFinalizers();
        }

        [Test]
        public void TestDestructor()
        {
            ForceGC();
            int instanceCount = CSSNode.GetInstanceCount();
            TestDestructorForGC(instanceCount);
            ForceGC();
            Assert.AreEqual(instanceCount, CSSNode.GetInstanceCount());
        }

        private void TestDestructorForGC(int instanceCount)
        {
            CSSNode node = new CSSNode();
            Assert.IsNotNull(node);
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());
            node = null;
        }

        [Test]
        public void TestDestructorWithChildren()
        {
            ForceGC();
            int instanceCount = CSSNode.GetInstanceCount();
            TestDestructorWithChildrenForGC1(instanceCount);
            ForceGC();
            Assert.AreEqual(instanceCount, CSSNode.GetInstanceCount());
        }

        private void TestDestructorWithChildrenForGC1(int instanceCount)
        {
            CSSNode node = new CSSNode();
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());

            TestDestructorWithChildrenForGC2(node, instanceCount + 1);
            ForceGC();
            Assert.AreEqual(instanceCount + 2, CSSNode.GetInstanceCount());

            TestDestructorWithChildrenForGC2(node, instanceCount + 2);
            ForceGC();
            Assert.AreEqual(instanceCount + 3, CSSNode.GetInstanceCount());

            node = null;
        }

        private void TestDestructorWithChildrenForGC2(CSSNode parent, int instanceCount)
        {
            CSSNode child = new CSSNode();
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());

            parent.Insert(0, child);
            child = null;
        }

        [Test]
        public void TestParentDestructor()
        {
            ForceGC();
            int instanceCount = CSSNode.GetInstanceCount();
            CSSNode child = new CSSNode();
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());

            TestParentDestructorForGC(child, instanceCount + 1);
            ForceGC();

            Assert.IsNull(child.Parent);
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());
        }

        private void TestParentDestructorForGC(CSSNode child, int instanceCount)
        {
            CSSNode parent = new CSSNode();
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());
            parent.Insert(0, child);
        }

        [Test]
        public void TestClearWithChildDestructor()
        {
            ForceGC();
            int instanceCount = CSSNode.GetInstanceCount();
            CSSNode node = new CSSNode();
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());
            TestClearWithChildDestructorForGC(node, instanceCount + 1);
            ForceGC();
            Assert.AreEqual(instanceCount + 2, CSSNode.GetInstanceCount());
            node.Clear();
            Assert.AreEqual(0, node.Count);
            ForceGC();
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());
        }

        private void TestClearWithChildDestructorForGC(CSSNode parent, int instanceCount)
        {
            CSSNode child = new CSSNode();
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());
            parent.Insert(0, child);
        }

        [Test]
        public void TestMeasureFuncWithDestructor()
        {
            ForceGC();
            int instanceCount = CSSNode.GetInstanceCount();
            CSSNode parent = new CSSNode();
            Assert.AreEqual(instanceCount + 1, CSSNode.GetInstanceCount());
            TestMeasureFuncWithDestructorForGC(parent);
            ForceGC();
            Assert.AreEqual(instanceCount + 2, CSSNode.GetInstanceCount());
            parent.CalculateLayout();
            Assert.AreEqual(120, (int)parent.LayoutWidth);
            Assert.AreEqual(130, (int)parent.LayoutHeight);
        }

        private void TestMeasureFuncWithDestructorForGC(CSSNode parent)
        {
            CSSNode child = new CSSNode();
            parent.Insert(0, child);
            child.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(120, 130);
            });
        }
#endif
    }
}
