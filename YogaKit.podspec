# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

podspec = Pod::Spec.new do |spec|
  spec.name = 'YogaKit'
  spec.version = '2.0.1'
  spec.license =  { :type => 'MIT', :file => "LICENSE" }
  spec.homepage = 'https://yogalayout.com/'
  spec.documentation_url = 'https://yogalayout.com/docs'
  spec.deprecated = true

  spec.summary = 'YogaKit allows using the Yoga layout engine in combination with UIKit'

  spec.authors = {'Meta Open Source' => 'opensource@meta.com'}
  spec.source = {
    :git => 'https://github.com/facebook/yoga.git',
    :tag => "v#{spec.version.to_s}",
  }

  spec.platforms = { :ios => "13.4" }
  spec.ios.frameworks = 'UIKit'
  spec.module_name = 'YogaKit'
  spec.dependency 'Yoga', "~> #{spec.version.to_s}"
  spec.source_files = 'YogaKit/Source/*.{h,m,swift}'
  spec.public_header_files = 'YogaKit/Source/{YGLayout,UIView+Yoga}.h'
  spec.private_header_files = 'YogaKit/Source/YGLayout+Private.h'
  spec.swift_version = '5.1'
end

# See https://github.com/facebook/yoga/pull/366
podspec.attributes_hash["readme"] = "YogaKit/README.md"
podspec
