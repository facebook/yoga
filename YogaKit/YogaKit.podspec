Pod::Spec.new do |spec|
  spec.name                 = 'YogaKit'
  spec.version              = 'v2016.12.26.00'
  spec.license              = { :type => 'BSD-3-Clause', :file => '../LICENSE' }
  spec.homepage             = 'https://facebook.github.io/yoga/'
  spec.authors              = {
                              'Emil Sjölander'      => 'sjolander.emil@gmail.com',
                              'Dustin Shahidehpour' => 'email@email.com'
                            }
  spec.summary              = 'Yoga is a cross-platform layout engine which implements Flexbox.'
  spec.description          = <<-DESC
  Yoga is a cross-platform layout engine which implements Flexbox.
  It enables maximum collaboration within your team by implementing an API familiar to
  many designers and opening it up to developers across different platforms.
  DESC
  spec.documentation_url    = 'https://facebook.github.io/yoga/docs/getting-started/'
  spec.source               = { :git => 'https://github.com/facebook/yoga.git', :tag => "v#{spec.version}" }
  spec.platform             = :ios
  spec.source_files         = './UIView+Yoga.m', '../yoga/*.c'
  spec.public_header_files  = './UIView+Yoga.h', '../yoga/*.h'
end
