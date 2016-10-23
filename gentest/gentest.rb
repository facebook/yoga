#!/usr/bin/env ruby
require 'watir-webdriver'
require 'fileutils'
caps = Selenium::WebDriver::Remote::Capabilities.chrome(
  "loggingPrefs"=>{"browser"=>"ALL", "performance"=>"ALL"})
browser = Watir::Browser.new(:chrome, :desired_capabilities => caps)
Dir.chdir(File.dirname($0))
Dir['fixtures/*.html'].each do |file|
  fixture = File.read(file)
  name = File.basename(file, '.*')
  puts "Generate #{name}"

  ltr_fixture = fixture.gsub('start', 'left')
                       .gsub('end', 'right')
                       .gsub('flex-left', 'flex-start')
                       .gsub('flex-right', 'flex-end')

  rtl_fixture = fixture.gsub('start', 'right')
                       .gsub('end', 'left')
                       .gsub('flex-right', 'flex-start')
                       .gsub('flex-left', 'flex-end')

  template = File.open('test-template.html').read
  f = File.open('test.html', 'w')
  f.write sprintf(template, ltr_fixture, rtl_fixture, fixture)
  f.close
  FileUtils.copy('test.html', "#{name}.html") if $DEBUG

  browser.goto('file://' + Dir.pwd + '/test.html')
  logs = browser.driver.manage.logs.get(:browser)

  f = File.open("../tests/#{name}.cpp", 'w')
  f.write eval(logs[0].message.sub(/^[^"]*/, ''))
  f.close

  f = File.open("../java/tests/com/facebook/csslayout/#{name}.java", 'w')
  f.write eval(logs[1].message.sub(/^[^"]*/, '')).sub('CSSNodeLayoutTest', name)
  f.close

  f = File.open("../csharp/tests/Facebook.CSSLayout/#{name}.cs", 'w')
  f.write eval(logs[2].message.sub(/^[^"]*/, '')).sub('CSSNodeLayoutTest', name)
  f.close
end
File.delete('test.html')
browser.close
