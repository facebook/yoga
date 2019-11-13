# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

podspec = Pod::Spec.new do |spec|
  spec.name = 'YogaKit'
  spec.version = '1.18.1'
  spec.license =  { :type => 'MIT', :file => "LICENSE" }
  spec.homepage = 'https://facebook.github.io/yoga/'
  spec.documentation_url = 'https://facebook.github.io/yoga/docs/'

  spec.summary = 'Yoga is a cross-platform layout engine which implements Flexbox.'
  spec.description = 'Yoga is a cross-platform layout engine enabling maximum collaboration within your team by implementing an API many designers are familiar with, and opening it up to developers across different platforms.'

  spec.authors = 'Facebook'
  spec.source = {
    :git => 'https://github.com/facebook/yoga.git',
    :tag => spec.version.to_s,
  }

  spec.platform = { :ios => "8.0", :osx => "10.9", :tvos => "9.0" }
  spec.module_name = 'YogaKit'
  spec.pod_target_xcconfig = {
    'DEFINES_MODULE' => 'YES'
  }
  spec.ios.deployment_target = '8.0'
  spec.osx.deployment_target = '10.9'
  spec.tvos.deployment_target = '9.0'
  spec.pod_target_xcconfig = { 'HEADER_SEARCH_PATHS' => '"${SRCROOT}/YogaKit"' }
  spec.source_files = 'YogaKit/Source/*.{h,m,swift}', 'yoga/**/*.{c,h,cpp}'
  spec.public_header_files = 'YogaKit/Source/{YGLayout,UIView+Yoga}.h', 'yoga/{Yoga,YGEnums,YGMacros,YGValue}.h'
  spec.private_header_files = 'YogaKit/Source/YGLayout+Private.h'
  spec.swift_version = '5.1'
  spec.static_framework = true
end

# See https://github.com/facebook/yoga/pull/366
podspec.attributes_hash["readme"] = "YogaKit/README.md"
podspec
