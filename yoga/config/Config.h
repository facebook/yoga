/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <yoga/Yoga.h>
#include <yoga/bits/EnumBitset.h>

// Tag struct used to form the opaque YGConfigRef for the public C API
struct YGConfig {};

namespace facebook::yoga {

class Config;
class Node;

// Whether moving a node from an old to new config should dirty previously
// calculated layout results.
bool configUpdateInvalidatesLayout(
    const Config& oldConfig,
    const Config& newConfig);

// Internal variants of log functions, currently used only by JNI bindings.
// TODO: Reconcile this with the public API
using LogWithContextFn = int (*)(
    YGConfigConstRef config,
    YGNodeConstRef node,
    YGLogLevel level,
    void* context,
    const char* format,
    va_list args);
using CloneWithContextFn = YGNodeRef (*)(
    YGNodeConstRef node,
    YGNodeConstRef owner,
    size_t childIndex,
    void* cloneContext);

#pragma pack(push)
#pragma pack(1)
// Packed structure of <32-bit options to miminize size per node.
struct ConfigFlags {
  bool useWebDefaults : 1;
  bool printTree : 1;
  bool cloneNodeUsesContext : 1;
  bool loggerUsesContext : 1;
};
#pragma pack(pop)

class YG_EXPORT Config : public ::YGConfig {
public:
  Config(YGLogger logger);

  void setUseWebDefaults(bool useWebDefaults);
  bool useWebDefaults() const;

  void setShouldPrintTree(bool printTree);
  bool shouldPrintTree() const;

  void setExperimentalFeatureEnabled(
      YGExperimentalFeature feature,
      bool enabled);
  bool isExperimentalFeatureEnabled(YGExperimentalFeature feature) const;
  EnumBitset<YGExperimentalFeature> getEnabledExperiments() const;

  void setErrata(YGErrata errata);
  void addErrata(YGErrata errata);
  void removeErrata(YGErrata errata);
  YGErrata getErrata() const;
  bool hasErrata(YGErrata errata) const;

  void setPointScaleFactor(float pointScaleFactor);
  float getPointScaleFactor() const;

  void setContext(void* context);
  void* getContext() const;

  void setLogger(YGLogger logger);
  void setLogger(LogWithContextFn logger);
  void setLogger(std::nullptr_t);
  void log(
      const yoga::Node* node,
      YGLogLevel logLevel,
      void* logContext,
      const char* format,
      va_list args) const;

  void setCloneNodeCallback(YGCloneNodeFunc cloneNode);
  void setCloneNodeCallback(CloneWithContextFn cloneNode);
  void setCloneNodeCallback(std::nullptr_t);
  YGNodeRef cloneNode(
      YGNodeConstRef node,
      YGNodeConstRef owner,
      size_t childIndex,
      void* cloneContext) const;

  static const Config& getDefault();

private:
  union {
    CloneWithContextFn withContext;
    YGCloneNodeFunc noContext;
  } cloneNodeCallback_;
  union {
    LogWithContextFn withContext;
    YGLogger noContext;
  } logger_;

  ConfigFlags flags_{};
  EnumBitset<YGExperimentalFeature> experimentalFeatures_{};
  YGErrata errata_ = YGErrataNone;
  float pointScaleFactor_ = 1.0f;
  void* context_ = nullptr;
};

inline Config* resolveRef(const YGConfigRef ref) {
  return static_cast<Config*>(ref);
}

inline const Config* resolveRef(const YGConfigConstRef ref) {
  return static_cast<const Config*>(ref);
}

} // namespace facebook::yoga
