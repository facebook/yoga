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
        public void TestRemoveAtFromEmpty()
        {
            YogaNode parent = new YogaNode();
            Assert.Throws<NullReferenceException>(() => parent.RemoveAt(0));
        }

        [Test]
        public void TestRemoveAtOutOfRange()
        {
            YogaNode parent = new YogaNode();
            YogaNode child = new YogaNode();
            parent.Insert(0, child);
            Assert.Throws<ArgumentOutOfRangeException>(() => parent.RemoveAt(1));
        }

        [Test]
        public void TestCannotAddChildToMultipleParents()
        {
            YogaNode parent1 = new YogaNode();
            YogaNode parent2 = new YogaNode();
            YogaNode child = new YogaNode();

            parent1.Insert(0, child);
            Assert.Throws<InvalidOperationException>(() => parent2.Insert(0, child));
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
        public void TestResetParent()
        {
            YogaNode parent = new YogaNode();
            YogaNode child = new YogaNode();
            parent.Insert(0, child);
            Assert.Throws<InvalidOperationException>(() => parent.Reset());
        }

        [Test]
        public void TestResetChild()
        {
            YogaNode parent = new YogaNode();
            YogaNode child = new YogaNode();
            parent.Insert(0, child);
            Assert.Throws<InvalidOperationException>(() => child.Reset());
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
            Assert.AreEqual(124.0f, node.LayoutWidth);
            Assert.AreEqual(82.0f, node.LayoutHeight);

            node = new YogaNode(new YogaConfig{PointScaleFactor = 0});
            node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(123.4f, 81.7f);
            });
            node.CalculateLayout();
            Assert.AreEqual(123.4f, node.LayoutWidth);
            Assert.AreEqual(81.7f, node.LayoutHeight);
        }

        [Test]
        public void TestChildWithMeasureFunc()
        {
            YogaNode node = new YogaNode();
            node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                return MeasureOutput.Make(100, 150);
            });
            YogaNode child = new YogaNode();
            Assert.Throws<InvalidOperationException>(() => node.Insert(0, child));
        }

        [Test]
        public void TestMeasureFuncWithChild()
        {
            YogaNode node = new YogaNode();
            YogaNode child = new YogaNode();
            node.Insert(0, child);
            Assert.Throws<InvalidOperationException>(() =>
                node.SetMeasureFunction((_, width, widthMode, height, heightMode) => {
                    return MeasureOutput.Make(100, 150);
                })
            );
        }

        [Test]
        public void TestBaselineFunc()
        {
            YogaNode node = new YogaNode();
            node.Height = 200;
            node.FlexDirection = YogaFlexDirection.Row;
            node.AlignItems = YogaAlign.Baseline;

            YogaNode child0 = new YogaNode();
            child0.Width = 100;
            child0.Height = 110;
            child0.SetBaselineFunction((_, width, height) => {
                Assert.AreEqual(100, width);
                Assert.AreEqual(110, height);
                return 65;
            });
            node.Insert(0, child0);

            YogaNode child1 = new YogaNode();
            child1.Width = 100;
            child1.Height = 110;
            child1.SetBaselineFunction((_, width, height) => {
                Assert.AreEqual(100, width);
                Assert.AreEqual(110, height);
                return 80;
            });
            node.Insert(1, child1);

            YogaNode child2 = new YogaNode();
            child2.Width = 100;
            child2.Height = 110;
            child2.SetBaselineFunction((_, width, height) => {
                Assert.AreEqual(100, width);
                Assert.AreEqual(110, height);
                return 88;
            });
            node.Insert(2, child2);

            node.CalculateLayout();

            Assert.AreEqual(0, child0.LayoutX);
            Assert.AreEqual(23, child0.LayoutY);
            Assert.AreEqual(100, child1.LayoutX);
            Assert.AreEqual(8, child1.LayoutY);
            Assert.AreEqual(200, child2.LayoutX);
            Assert.AreEqual(0, child2.LayoutY);
        }

        [Test]
        public void TestPrintOneNode()
        {
            YogaNode node = new YogaNode();
            node.Width = 100;
            node.Height = 120;
            node.CalculateLayout();
            Assert.AreEqual("<div layout=\"width: 100; height: 120; top: 0; left: 0;\" style=\"width: 100px; height: 120px; \" ></div>", node.Print());
        }

        [Test]
        public void TestPrintWithLogger()
        {
            YogaNode node = new YogaNode();
            node.Width = 110;
            node.Height = 105;
            node.CalculateLayout();
            Assert.AreEqual("<div layout=\"width: 110; height: 105; top: 0; left: 0;\" style=\"width: 110px; height: 105px; \" ></div>", node.Print());
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
            Assert.AreEqual("<div layout=\"width: 100; height: 120; top: 0; left: 0;\" style=\"width: 100px; height: 120px; \" >\n  <div layout=\"width: 35; height: 45; top: 0; left: 0;\" style=\"width: 35px; height: 45px; \" ></div>\n  <div layout=\"width: 30; height: 40; top: 45; left: 0;\" style=\"width: 30px; height: 40px; \" ></div>\n</div>", parent.Print());
        }

        [Test]
        public void TestCopyStyle()
        {
            YogaNode node0 = new YogaNode();
            Assert.IsTrue(YogaConstants.IsUndefined(node0.MaxHeight));

            YogaNode node1 = new YogaNode();
            node1.MaxHeight = 100;

            node0.CopyStyle(node1);
            Assert.AreEqual(100.Pt(), node0.MaxHeight);
        }

        [Test]
        public void TestCopyConstructor()
        {
            YogaNode node0 = new YogaNode();
            node0.MaxWidth = 80;

            YogaNode node1 = new YogaNode(node0);
            Assert.AreEqual(80.Pt(), node1.MaxWidth);

            YogaNode node2 = new YogaNode(node1)
            {
                MaxHeight = 90,
            };
            Assert.AreEqual(80.Pt(), node2.MaxWidth);
            Assert.AreEqual(90.Pt(), node2.MaxHeight);

            YogaNode node3 = new YogaNode(node0)
            {
                MaxWidth = 100,
            };
            Assert.AreEqual(100.Pt(), node3.MaxWidth);

            YogaNode node4 = new YogaNode(node2)
            {
                MaxWidth = 100,
            };
            Assert.AreEqual(100.Pt(), node4.MaxWidth);
            Assert.AreEqual(90.Pt(), node4.MaxHeight);
        }

#if !UNITY_5_4_OR_NEWER
        public static void ForceGC()
        {
            GC.Collect();
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

#if YOGA_ENABLE_GC_TEST
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
#endif

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
#endif

        [Test]
        public void TestLayoutMargin() {
          YogaNode node = new YogaNode();
          node.Width = 100;
          node.Height = 100;
          node.MarginStart = 1;
          node.MarginEnd = 2;
          node.MarginTop = 3;
          node.MarginBottom = 4;
          node.CalculateLayout();

          Assert.AreEqual(1, node.LayoutMarginLeft);
          Assert.AreEqual(2, node.LayoutMarginRight);
          Assert.AreEqual(3, node.LayoutMarginTop);
          Assert.AreEqual(4, node.LayoutMarginBottom);
        }

        [Test]
        public void TestLayoutPadding() {
          YogaNode node = new YogaNode();
          node.Width = 100;
          node.Height = 100;
          node.PaddingStart = 1;
          node.PaddingEnd = 2;
          node.PaddingTop = 3;
          node.PaddingBottom = 4;
          node.CalculateLayout();

          Assert.AreEqual(1, node.LayoutPaddingLeft);
          Assert.AreEqual(2, node.LayoutPaddingRight);
          Assert.AreEqual(3, node.LayoutPaddingTop);
          Assert.AreEqual(4, node.LayoutPaddingBottom);
        }
    }
}
