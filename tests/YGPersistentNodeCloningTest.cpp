/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <yoga/config/Config.h>
#include <yoga/node/Node.h>

#include <functional>
#include <memory>
#include <vector>

namespace facebook::yoga {

struct YGPersistentNodeCloningTest : public ::testing::Test {
  struct NodeWrapper {
    explicit NodeWrapper(
        YGConfigRef config,
        std::vector<std::shared_ptr<NodeWrapper>> children = {})
        : node{YGNodeNewWithConfig(config)}, children{std::move(children)} {
      YGNodeSetContext(node, this);

      auto privateNode = resolveRef(node);
      for (const auto& child : this->children) {
        auto privateChild = resolveRef(child->node);
        // Claim first ownership of not yet owned nodes, to avoid immediately
        // cloning them
        if (YGNodeGetOwner(child->node) == nullptr) {
          privateChild->setOwner(privateNode);
        }
        privateNode->insertChild(privateChild, privateNode->getChildCount());
      }
    }

    // Clone, with current children, for mutation
    NodeWrapper(const NodeWrapper& other)
        : node{YGNodeClone(other.node)}, children{other.children} {
      YGNodeSetContext(node, this);

      auto privateNode = resolveRef(node);
      privateNode->setOwner(nullptr);
    }

    // Clone, with new children
    NodeWrapper(
        const NodeWrapper& other,
        std::vector<std::shared_ptr<NodeWrapper>> children)
        : node{YGNodeClone(other.node)}, children{std::move(children)} {
      YGNodeSetContext(node, this);

      auto privateNode = resolveRef(node);
      privateNode->setOwner(nullptr);
      privateNode->setChildren({});
      privateNode->setDirty(true);

      for (const auto& child : this->children) {
        auto privateChild = resolveRef(child->node);
        // Claim first ownership of not yet owned nodes, to avoid immediately
        // cloning them
        if (YGNodeGetOwner(child->node) == nullptr) {
          privateChild->setOwner(privateNode);
        }
        privateNode->insertChild(privateChild, privateNode->getChildCount());
      }
    }

    NodeWrapper(NodeWrapper&&) = delete;

    ~NodeWrapper() {
      YGNodeFree(node);
    }

    NodeWrapper& operator=(const NodeWrapper& other) = delete;
    NodeWrapper& operator=(NodeWrapper&& other) = delete;

    YGNodeRef node;
    std::vector<std::shared_ptr<NodeWrapper>> children;
  };

  struct ConfigWrapper {
    ConfigWrapper() {
      YGConfigSetCloneNodeFunc(
          config,
          [](YGNodeConstRef oldNode, YGNodeConstRef owner, size_t childIndex) {
            onClone(oldNode, owner, childIndex);
            auto wrapper = static_cast<NodeWrapper*>(YGNodeGetContext(owner));
            auto old = static_cast<NodeWrapper*>(YGNodeGetContext(oldNode));

            wrapper->children[childIndex] = std::make_shared<NodeWrapper>(*old);
            return wrapper->children[childIndex]->node;
          });
    }

    ConfigWrapper(const ConfigWrapper&) = delete;
    ConfigWrapper(ConfigWrapper&&) = delete;

    ~ConfigWrapper() {
      YGConfigFree(config);
    }

    ConfigWrapper& operator=(const ConfigWrapper&) = delete;
    ConfigWrapper& operator=(ConfigWrapper&&) = delete;

    YGConfigRef config{YGConfigNew()};
  };

  ConfigWrapper configWrapper;
  YGConfigRef config{configWrapper.config};

  void SetUp() override {
    onClone = [](...) {};
  }

  // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
  static inline std::function<void(YGNodeConstRef, YGNodeConstRef, size_t)>
      onClone;
};

TEST_F(
    YGPersistentNodeCloningTest,
    changing_sibling_height_does_not_clone_neighbors) {
  // <ScrollView>
  //   <View id="Sibling" style={{ height: 1 }} />
  //   <View id="A" style={{ height: 1 }}>
  //     <View id="B">
  //       <View id="C">
  //         <View id="D"/>
  //       </View>
  //     </View>
  //   </View>
  // </ScrollView>

  auto sibling = std::make_shared<NodeWrapper>(config);
  YGNodeStyleSetHeight(sibling->node, 1);

  auto d = std::make_shared<NodeWrapper>(config);
  auto c = std::make_shared<NodeWrapper>(config, std::vector{d});
  auto b = std::make_shared<NodeWrapper>(config, std::vector{c});
  auto a = std::make_shared<NodeWrapper>(config, std::vector{b});
  YGNodeStyleSetHeight(a->node, 1);

  auto scrollContentView =
      std::make_shared<NodeWrapper>(config, std::vector{sibling, a});
  YGNodeStyleSetPositionType(scrollContentView->node, YGPositionTypeAbsolute);

  auto scrollView =
      std::make_shared<NodeWrapper>(config, std::vector{scrollContentView});
  YGNodeStyleSetWidth(scrollView->node, 100);
  YGNodeStyleSetHeight(scrollView->node, 100);

  // We don't expect any cloning during the first layout
  onClone = [](...) { FAIL(); };

  YGNodeCalculateLayout(
      scrollView->node, YGUndefined, YGUndefined, YGDirectionLTR);

  auto siblingPrime = std::make_shared<NodeWrapper>(config);
  YGNodeStyleSetHeight(siblingPrime->node, 2);

  auto scrollContentViewPrime = std::make_shared<NodeWrapper>(
      *scrollContentView, std::vector{siblingPrime, a});
  auto scrollViewPrime = std::make_shared<NodeWrapper>(
      *scrollView, std::vector{scrollContentViewPrime});

  std::vector<NodeWrapper*> nodesCloned;
  // We should only need to clone "A"
  onClone = [&](YGNodeConstRef oldNode,
                YGNodeConstRef /*owner*/,
                size_t /*childIndex*/) {
    nodesCloned.push_back(static_cast<NodeWrapper*>(YGNodeGetContext(oldNode)));
  };

  YGNodeCalculateLayout(
      scrollViewPrime->node, YGUndefined, YGUndefined, YGDirectionLTR);

  EXPECT_EQ(nodesCloned.size(), 1);
  EXPECT_EQ(nodesCloned[0], a.get());
}

TEST_F(YGPersistentNodeCloningTest, clone_leaf_display_contents_node) {
  // <View id="A">
  //   <View id="B" style={{ display: 'contents' }} />
  // </View>

  auto b = std::make_shared<NodeWrapper>(config);
  auto a = std::make_shared<NodeWrapper>(config, std::vector{b});
  YGNodeStyleSetDisplay(b->node, YGDisplayContents);

  // We don't expect any cloning during the first layout
  onClone = [](...) { FAIL(); };

  YGNodeCalculateLayout(a->node, YGUndefined, YGUndefined, YGDirectionLTR);

  auto aPrime = std::make_shared<NodeWrapper>(config, std::vector{b});

  std::vector<NodeWrapper*> nodesCloned;
  // We should clone "C"
  onClone = [&](YGNodeConstRef oldNode,
                YGNodeConstRef /*owner*/,
                size_t /*childIndex*/) {
    nodesCloned.push_back(static_cast<NodeWrapper*>(YGNodeGetContext(oldNode)));
  };

  YGNodeCalculateLayout(aPrime->node, 100, 100, YGDirectionLTR);

  EXPECT_EQ(nodesCloned.size(), 1);
  EXPECT_EQ(nodesCloned[0], b.get());
}

} // namespace facebook::yoga
