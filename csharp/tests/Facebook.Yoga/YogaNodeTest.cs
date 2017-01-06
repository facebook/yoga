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
    public class YogaNodeTest
    {
        [Test]
        public void TestAddChildGetParent()
        {
            YogaNode parent = new YogaNode();
            YogaNode child = new YogaNode();

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
            YogaNode parent = new YogaNode();
            foreach (YogaNode node in parent) {
                Assert.Fail(node.ToString());
            }

            YogaNode child0 = new YogaNode();
            Assert.AreEqual(-1, parent.IndexOf(child0));
            parent.Insert(0, child0);
            foreach (YogaNode node in parent) {
                Assert.AreEqual(0, parent.IndexOf(node));
            }

            YogaNode child1 = new YogaNode();
            parent.Insert(1, child1);
            int index = 0;
            foreach (YogaNode node in parent) {
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
            YogaNode parent = new YogaNode();
            parent.RemoveAt(0);
        }

        [Test]
        [ExpectedException("System.ArgumentOutOfRangeException")]
        public void TestRemoveAtOutOfRange()
        {
            YogaNode parent = new YogaNode();
            YogaNode child = new YogaNode();
            parent.Insert(0, child);
            parent.RemoveAt(1);
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestCannotAddChildToMultipleParents()
        {
            YogaNode parent1 = new YogaNode();
            YogaNode parent2 = new YogaNode();
            YogaNode child = new YogaNode();

            parent1.Insert(0, child);
            parent2.Insert(0, child);
        }

        [Test]
        public void TestReset()
        {
            int instanceCount = YogaNode.GetInstanceCount();
            YogaNode node = new YogaNode();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());
            node.Reset();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestResetParent()
        {
            YogaNode parent = new YogaNode();
            YogaNode child = new YogaNode();
            parent.Insert(0, child);
            parent.Reset();
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestResetChild()
        {
            YogaNode parent = new YogaNode();
            YogaNode child = new YogaNode();
            parent.Insert(0, child);
            child.Reset();
        }

        [Test]
        public void TestClear()
        {
            int instanceCount = YogaNode.GetInstanceCount();
            YogaNode parent = new YogaNode();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());
            YogaNode child = new YogaNode();
            Assert.AreEqual(instanceCount + 2, YogaNode.GetInstanceCount());
            parent.Insert(0, child);
            Assert.AreEqual(1, parent.Count);
            Assert.AreEqual(parent, child.Parent);
            parent.Clear();
            Assert.AreEqual(0, parent.Count);
            Assert.IsNull(child.Parent);
            Assert.AreEqual(instanceCount + 2, YogaNode.GetInstanceCount());
        }

        [Test]
        public void TestMeasureFunc()
        {
            YogaNode node = new YogaNode();
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
            YogaNode node = new YogaNode();
            node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(123.4f, 81.7f);
            });
            node.CalculateLayout();
            Assert.AreEqual(123.4f, node.LayoutWidth);
            Assert.AreEqual(81.7f, node.LayoutHeight);
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestChildWithMeasureFunc()
        {
            YogaNode node = new YogaNode();
            node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(100, 150);
            });
            YogaNode child = new YogaNode();
            node.Insert(0, child);
        }

        [Test]
        [ExpectedException("System.InvalidOperationException")]
        public void TestMeasureFuncWithChild()
        {
            YogaNode node = new YogaNode();
            YogaNode child = new YogaNode();
            node.Insert(0, child);
            node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(100, 150);
            });
        }

        [Test]
        public void TestPrint()
        {
            YogaNode parent = new YogaNode();
            parent.Width = 100;
            parent.Height = 120;
            YogaNode child0 = new YogaNode();
            child0.Width = 30;
            child0.Height = 40;
            YogaNode child1 = new YogaNode();
            child1.Width = 35;
            child1.Height = 45;
            parent.Insert(0, child0);
            parent.Insert(0, child1);
            parent.CalculateLayout();
            Assert.AreEqual("{layout: {width: 100, height: 120, top: 0, left: 0}, flexDirection: 'column', alignItems: 'stretch', flexGrow: 0, flexShrink: 0, overflow: 'visible', width: 100px, height: 120px, children: [\n  {layout: {width: 35, height: 45, top: 0, left: 0}, flexDirection: 'column', alignItems: 'stretch', flexGrow: 0, flexShrink: 0, overflow: 'visible', width: 35px, height: 45px, },\n  {layout: {width: 30, height: 40, top: 45, left: 0}, flexDirection: 'column', alignItems: 'stretch', flexGrow: 0, flexShrink: 0, overflow: 'visible', width: 30px, height: 40px, },\n]},\n", parent.Print());
        }

        [Test]
        public void TestCopyStyle()
        {
            YogaNode node0 = new YogaNode();
            Assert.IsTrue(YogaConstants.IsUndefined(node0.MaxHeight));

            YogaNode node1 = new YogaNode();
            node1.MaxHeight = 100;

            node0.CopyStyle(node1);
            Assert.AreEqual(100.Px(), node0.MaxHeight);
        }

        private void ForceGC()
        {
            GC.Collect(GC.MaxGeneration);
            GC.WaitForPendingFinalizers();
        }

        [Test]
        public void TestDestructor()
        {
            ForceGC();
            int instanceCount = YogaNode.GetInstanceCount();
            TestDestructorForGC(instanceCount);
            ForceGC();
            Assert.AreEqual(instanceCount, YogaNode.GetInstanceCount());
        }

        private void TestDestructorForGC(int instanceCount)
        {
            YogaNode node = new YogaNode();
            Assert.IsNotNull(node);
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());
            node = null;
        }

        [Test]
        public void TestDestructorWithChildren()
        {
            ForceGC();
            int instanceCount = YogaNode.GetInstanceCount();
            TestDestructorWithChildrenForGC1(instanceCount);
            ForceGC();
            Assert.AreEqual(instanceCount, YogaNode.GetInstanceCount());
        }

        private void TestDestructorWithChildrenForGC1(int instanceCount)
        {
            YogaNode node = new YogaNode();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());

            TestDestructorWithChildrenForGC2(node, instanceCount + 1);
            ForceGC();
            Assert.AreEqual(instanceCount + 2, YogaNode.GetInstanceCount());

            TestDestructorWithChildrenForGC2(node, instanceCount + 2);
            ForceGC();
            Assert.AreEqual(instanceCount + 3, YogaNode.GetInstanceCount());

            node = null;
        }

        private void TestDestructorWithChildrenForGC2(YogaNode parent, int instanceCount)
        {
            YogaNode child = new YogaNode();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());

            parent.Insert(0, child);
            child = null;
        }

        [Test]
        public void TestParentDestructor()
        {
            ForceGC();
            int instanceCount = YogaNode.GetInstanceCount();
            YogaNode child = new YogaNode();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());

            TestParentDestructorForGC(child, instanceCount + 1);
            ForceGC();

            Assert.IsNull(child.Parent);
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());
        }

        private void TestParentDestructorForGC(YogaNode child, int instanceCount)
        {
            YogaNode parent = new YogaNode();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());
            parent.Insert(0, child);
        }

        [Test]
        public void TestClearWithChildDestructor()
        {
            ForceGC();
            int instanceCount = YogaNode.GetInstanceCount();
            YogaNode node = new YogaNode();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());
            TestClearWithChildDestructorForGC(node, instanceCount + 1);
            ForceGC();
            Assert.AreEqual(instanceCount + 2, YogaNode.GetInstanceCount());
            node.Clear();
            Assert.AreEqual(0, node.Count);
            ForceGC();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());
        }

        private void TestClearWithChildDestructorForGC(YogaNode parent, int instanceCount)
        {
            YogaNode child = new YogaNode();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());
            parent.Insert(0, child);
        }

        [Test]
        public void TestMeasureFuncWithDestructor()
        {
            ForceGC();
            int instanceCount = YogaNode.GetInstanceCount();
            YogaNode parent = new YogaNode();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());
            TestMeasureFuncWithDestructorForGC(parent);
            ForceGC();
            Assert.AreEqual(instanceCount + 2, YogaNode.GetInstanceCount());
            parent.CalculateLayout();
            Assert.AreEqual(120, (int)parent.LayoutWidth);
            Assert.AreEqual(130, (int)parent.LayoutHeight);
        }

        private void TestMeasureFuncWithDestructorForGC(YogaNode parent)
        {
            YogaNode child = new YogaNode();
            parent.Insert(0, child);
            child.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(120, 130);
            });
        }

        [Test]
        public void TestLayoutPadding() {
          YogaNode node = new YogaNode();
          node.Width = 100;
          node.Height = 100;
          node.SetPadding(YogaEdge.Start, 1);
          node.SetPadding(YogaEdge.End, 2);
          node.SetPadding(YogaEdge.Top, 3);
          node.SetPadding(YogaEdge.Bottom, 4);
          node.CalculateLayout();

          Assert.AreEqual(1, node.GetLayoutPadding(YogaEdge.Left));
          Assert.AreEqual(2, node.GetLayoutPadding(YogaEdge.Right));
          Assert.AreEqual(3, node.GetLayoutPadding(YogaEdge.Top));
          Assert.AreEqual(4, node.GetLayoutPadding(YogaEdge.Bottom));
        }
    }
}
