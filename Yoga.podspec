# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.


Pod::Spec.new do |spec|
  spec.name = 'Yoga'
  spec.version = '2.0.1'
  spec.license =  { :type => 'MIT', :file => "LICENSE" }
  spec.homepage = 'https://yogalayout.com/'
  spec.documentation_url = 'https://yogalayout.com/docs'

  spec.summary = 'An embeddable and performant flexbox layout engine with bindings for multiple languages'

  spec.authors = {'Meta Open Source' => 'opensource@meta.com'}
  spec.source = {
    :git => 'https://github.com/facebook/yoga.git',
    :tag => "v#{spec.version.to_s}",
  }

  spec.ios.deployment_target = "13.4"

  spec.module_name = 'yoga'
  spec.requires_arc = false
  spec.pod_target_xcconfig = {
    'DEFINES_MODULE' => 'YES'
  }
  spec.compiler_flags = [
      '-fno-omit-frame-pointer',
      '-fexceptions',
      '-Wall',
      '-Werror',
      '-Wextra',
      '-std=c++14',
      '-fPIC'
  ]
  spec.source_files = 'yoga/**/*.{h,cpp}'
  spec.public_header_files = 'yoga/{Yoga,YGEnums,YGMacros,YGValue}.h'
  spec.swift_version = '5.1'
end
