/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

using NUnit.Framework;
using System;

/**
 * Tests for {@link YogaConfig}.
 */
namespace Facebook.Yoga
{
    [TestFixture]
    public class YogaConfigTest
    {
        [Test]
        public void TestUseWebDefaults()
        {
            YogaNode node0 = new YogaNode(new YogaConfig{UseWebDefaults = true});
            Assert.AreEqual(YogaFlexDirection.Row, node0.FlexDirection);

            node0.Reset();
            Assert.AreEqual(YogaFlexDirection.Row, node0.FlexDirection);

            YogaConfig config = new YogaConfig();
            config.UseWebDefaults = true;
            YogaNode node1 = new YogaNode(config);
            Assert.AreEqual(YogaFlexDirection.Row, node1.FlexDirection);

            node1.Reset();
            Assert.AreEqual(YogaFlexDirection.Row, node1.FlexDirection);
        }

        [Test]
        public void TestDefaultConfig()
        {
            YogaNode node0 = new YogaNode();
            Assert.AreEqual(YogaFlexDirection.Column, node0.FlexDirection);

            YogaNode node1 = new YogaNode(new YogaConfig());
            Assert.AreEqual(YogaFlexDirection.Column, node1.FlexDirection);
        }

        [Test]
        public void TestCopyConstructor()
        {
            YogaNode srcNode = new YogaNode(new YogaConfig{UseWebDefaults = true});
            YogaNode node0 = new YogaNode(srcNode);
            Assert.AreEqual(YogaFlexDirection.Row, node0.FlexDirection);

            node0.FlexDirection = YogaFlexDirection.Column;
            Assert.AreEqual(YogaFlexDirection.Column, node0.FlexDirection);

            node0.Reset();
            Assert.AreEqual(YogaFlexDirection.Row, node0.FlexDirection);

            YogaNode node1 = new YogaNode(srcNode)
            {
                FlexDirection = YogaFlexDirection.Column
            };
            Assert.AreEqual(YogaFlexDirection.Column, node1.FlexDirection);

            node1.Reset();
            Assert.AreEqual(YogaFlexDirection.Row, node1.FlexDirection);
        }

#if !UNITY_5_4_OR_NEWER
        public static void ForceGC()
        {
            YogaNodeTest.ForceGC();
        }

        [Test]
        public void TestDestructor()
        {
            ForceGC();
            int instanceCount = YogaConfig.GetInstanceCount();
            TestDestructorForGC(instanceCount);
            ForceGC();
            Assert.AreEqual(instanceCount, YogaConfig.GetInstanceCount());
        }

        private void TestDestructorForGC(int instanceCount)
        {
            YogaConfig config = new YogaConfig();
            Assert.IsNotNull(config);
            Assert.AreEqual(instanceCount + 1, YogaConfig.GetInstanceCount());
            config = null;
        }

        [Test]
        public void TestRetainConfig()
        {
            ForceGC();
            int nodeInstanceCount = YogaNode.GetInstanceCount();
            int configInstanceCount = YogaConfig.GetInstanceCount();
            TestRetainConfigForGC(nodeInstanceCount, configInstanceCount);
            ForceGC();

            Assert.AreEqual(nodeInstanceCount, YogaNode.GetInstanceCount());
            Assert.AreEqual(configInstanceCount, YogaConfig.GetInstanceCount());
        }

        private void TestRetainConfigForGC(int nodeInstanceCount, int configInstanceCount)
        {
            ForceGC();
            Assert.AreEqual(nodeInstanceCount, YogaNode.GetInstanceCount());
            Assert.AreEqual(configInstanceCount, YogaConfig.GetInstanceCount());
            YogaNode node = TestRetainConfigForGC2(nodeInstanceCount, configInstanceCount);
            ForceGC();
            Assert.IsNotNull(node);
            Assert.AreEqual(configInstanceCount + 1, YogaConfig.GetInstanceCount());
            Assert.AreEqual(nodeInstanceCount + 1, YogaNode.GetInstanceCount());
            node = null;
        }

        private YogaNode TestRetainConfigForGC2(int nodeInstanceCount, int configInstanceCount)
        {
            YogaConfig config = new YogaConfig();
            Assert.IsNotNull(config);
            Assert.AreEqual(configInstanceCount + 1, YogaConfig.GetInstanceCount());

            YogaNode node = new YogaNode(config);
            Assert.IsNotNull(node);
            Assert.AreEqual(nodeInstanceCount + 1, YogaNode.GetInstanceCount());

            config = null;

            return node;
        }
#endif
    }
}
