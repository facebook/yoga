Pod::Spec.new do |s|
  s.name = 'Yoga'
  s.version = '1.0.0'
  s.summary = 'A cross-platform layout engine.'
  s.homepage = 'https://github.com/facebook/yoga'
  s.documentation_url = 'https://facebook.github.io/yoga'
  s.description = 'Yoga is a cross-platform layout engine enabling maximum collaboration within your team by implementing an API many designers are familiar with, and opening it up to developers across different platforms.'

  s.license =  { :type => 'BSD', :file => "LICENSE" }
  s.authors = 'Facebook'
  s.social_media_url = 'https://twitter.com/fbOpenSource'
  s.source = {
    :git => 'https://github.com/facebook/yoga.git',
    :tag => 'v2017.01.23.00',
  }
  s.module_name = 'yoga'
  s.requires_arc = false
  s.compiler_flags = [
      '-fno-omit-frame-pointer',
      '-fexceptions',
      '-Wall',
      '-Werror',
      '-std=c11',
      '-fPIC'
  ]
  s.source_files = 'yoga/**/*.{c,h}'
end
