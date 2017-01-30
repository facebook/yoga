Pod::Spec.new do |spec|
  spec.name = 'YogaKit'
  spec.version = '1.0.1'
  spec.license = { :type => 'BSD-3-Clause', :file => '../LICENSE' }
  spec.homepage = 'https://facebook.github.io/yoga'
  spec.authors = {
    'Emil Sjölander'      => 'sjolander.emil@gmail.com',
    'Dustin Shahidehpour' => 'dshahidehpour@gmail.com'
  }

  spec.summary = 'Yoga is a cross-platform layout engine which implements Flexbox.'
  spec.description = <<-DESC
  Yoga is a cross-platform layout engine which implements Flexbox.
  It enables maximum collaboration within your team by implementing an API familiar to
  many designers and opening it up to developers across different platforms.
  DESC

  spec.documentation_url = 'https://facebook.github.io/yoga/docs/getting-started/'
  spec.source = {
    :git => 'https://github.com/facebook/yoga.git',
    :tag => 'v2017.01.27.00'
  }
  spec.platform = :ios
  spec.ios.deployment_target = '8.0'
  spec.ios.frameworks = 'UIKit'

  spec.dependency 'Yoga', '~> 1.0'
  spec.source_files = 'YogaKit/Source/*.{h,m}',
  spec.public_header_files = 'YogaKit/Source/{YGLayout,UIView+Yoga}.h'
  spec.private_header_files = 'YogaKit/Source/YGLayout+Private.h'

end
