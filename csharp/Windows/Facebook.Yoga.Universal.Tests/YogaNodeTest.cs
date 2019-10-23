/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

using System;
using Microsoft.VisualStudio.TestPlatform.UnitTestFramework;
using Facebook.Yoga;

namespace Facebook.Yoga.Universal.Tests
{
    [TestClass]
    public class YogaNodeTest
    {
        [TestMethod]
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

        [TestMethod]
        public void TestChildren()
        {
            YogaNode parent = new YogaNode();
            foreach (YogaNode node in parent)
            {
                Assert.Fail(node.ToString());
            }

            YogaNode child0 = new YogaNode();
            Assert.AreEqual(-1, parent.IndexOf(child0));
            parent.Insert(0, child0);
            foreach (YogaNode node in parent)
            {
                Assert.AreEqual(0, parent.IndexOf(node));
            }

            YogaNode child1 = new YogaNode();
            parent.Insert(1, child1);
            int index = 0;
            foreach (YogaNode node in parent)
            {
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

        [TestMethod]
        public void TestRemoveAtFromEmpty()
        {
            YogaNode parent = new YogaNode();

            try
            {
                parent.RemoveAt(0);
            }
            catch (System.NullReferenceException)
            {
                return;
            }

            Assert.Fail("Excepted exception of type 'System.NullReferenceException'.");
        }

        [TestMethod]
        public void TestRemoveAtOutOfRange()
        {
            YogaNode parent = new YogaNode();
            YogaNode child = new YogaNode();
            parent.Insert(0, child);

            try
            {
                parent.RemoveAt(1);
            }
            catch (System.ArgumentOutOfRangeException)
            {
                return;
            }

            Assert.Fail("Excepted exception of type 'System.ArgumentOutOfRangeException'.");
        }

        [TestMethod]
        public void TestCannotAddChildToMultipleParents()
        {
            YogaNode parent1 = new YogaNode();
            YogaNode parent2 = new YogaNode();
            YogaNode child = new YogaNode();

            parent1.Insert(0, child);

            try
            {
                parent2.Insert(0, child);
            }
            catch (System.InvalidOperationException)
            {
                return;
            }

            Assert.Fail("Excepted exception of type 'System.InvalidOperationException'.");
        }

        [TestMethod]
        public void TestReset()
        {
            int instanceCount = YogaNode.GetInstanceCount();
            YogaNode node = new YogaNode();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());
            node.Reset();
            Assert.AreEqual(instanceCount + 1, YogaNode.GetInstanceCount());
        }

        [TestMethod]
        public void TestResetParent()
        {
            YogaNode parent = new YogaNode();
            YogaNode child = new YogaNode();
            parent.Insert(0, child);

            try
            {
                parent.Reset();
            }
            catch (System.InvalidOperationException)
            {
                return;
            }

            Assert.Fail("Excepted exception of type 'System.InvalidOperationException'.");
        }

        [TestMethod]
        public void TestResetChild()
        {
            YogaNode parent = new YogaNode();
            YogaNode child = new YogaNode();
            parent.Insert(0, child);

            try
            {
                child.Reset();
            }
            catch (System.InvalidOperationException)
            {
                return;
            }

            Assert.Fail("Excepted exception of type 'System.InvalidOperationException'.");
        }

        [TestMethod]
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

        [TestMethod]
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

        [TestMethod]
        public void TestMeasureFuncWithFloat()
        {
            YogaNode node = new YogaNode();
            node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(123.4f, 81.7f);
            });
            node.CalculateLayout();
            Assert.AreEqual(124, node.LayoutWidth);
            Assert.AreEqual(82, node.LayoutHeight);
        }

        [TestMethod]
        public void TestChildWithMeasureFunc()
        {
            YogaNode node = new YogaNode();

            node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(100, 150);
            });
            YogaNode child = new YogaNode();

            try
            {
                node.Insert(0, child);
            }
            catch (System.InvalidOperationException)
            {
                return;
            }

            Assert.Fail("Excepted exception of type 'System.InvalidOperationException'.");
        }

        [TestMethod]
        public void TestMeasureFuncWithChild()
        {
            YogaNode node = new YogaNode();
            YogaNode child = new YogaNode();
            node.Insert(0, child);

            try
            {
                node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(100, 150);
                });
            }
            catch (System.InvalidOperationException)
            {
                return;
            }

            Assert.Fail("Excepted exception of type 'System.InvalidOperationException'.");
        }

        [TestMethod]
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
            Assert.AreEqual(parent.Print(),
              "<div layout=\"width: 100; height: 120; top: 0; left: 0;\" style=\"width: 100px; height: 120px; \" >\n" +
              "  <div layout=\"width: 35; height: 45; top: 0; left: 0;\" style=\"width: 35px; height: 45px; \" ></div>\n" +
              "  <div layout=\"width: 30; height: 40; top: 45; left: 0;\" style=\"width: 30px; height: 40px; \" ></div>\n" +
              "</div>"
            );
        }

        [TestMethod]
        public void TestCopyStyle()
        {
            YogaNode node0 = new YogaNode();
            Assert.IsTrue(YogaConstants.IsUndefined(node0.MaxHeight));

            YogaNode node1 = new YogaNode();
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

        [TestMethod]
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

        [TestMethod]
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

        [TestMethod]
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

        [TestMethod]
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

        [TestMethod]
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
#endif
    }
}
