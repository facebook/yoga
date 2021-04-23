# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

podspec = Pod::Spec.new do |spec|
  spec.name = 'BeagleYogaKit'
  spec.version = '1.19.0'
  spec.license =  { :type => 'MIT', :file => "LICENSE" }
  spec.homepage = 'https://facebook.github.io/yoga/'
  spec.documentation_url = 'https://facebook.github.io/yoga/docs/'

  spec.summary = 'Yoga is a cross-platform layout engine which implements Flexbox.'
  spec.description = 'Yoga is a cross-platform layout engine enabling maximum collaboration within your team by implementing an API many designers are familiar with, and opening it up to developers across different platforms.'

  spec.authors = 'Facebook and ZupIT'
  spec.source = {
    :git => 'https://github.com/ZupIT/yoga.git',
    :tag => spec.version.to_s,
  }

  spec.platform = :ios
  spec.ios.deployment_target = '8.0'
  spec.ios.frameworks = 'UIKit'
  spec.module_name = 'YogaKit'
  spec.dependency 'BeagleYoga', '~> 1.19'
  # Fixes the bug related the xcode 11 not able to find swift related frameworks.
  # https://github.com/Carthage/Carthage/issues/2825
  # https://twitter.com/krzyzanowskim/status/1151549874653081601?s=21
  spec.pod_target_xcconfig = {"LD_VERIFY_BITCODE": "NO"}
  spec.source_files = 'YogaKit/Source/*.{h,m}', 'YogaKit/Source/swift/YGLayoutExtensions.swift'
  spec.public_header_files = 'YogaKit/Source/{YGLayout,UIView+Yoga}.h'
  spec.private_header_files = 'YogaKit/Source/YGLayout+Private.h'
  spec.swift_version = '5.1'
end

# See https://github.com/facebook/yoga/pull/366
podspec.attributes_hash["readme"] = "YogaKit/README.md"
podspec
