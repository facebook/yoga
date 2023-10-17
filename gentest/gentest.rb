#!/usr/bin/env ruby
# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

require 'watir'
require 'webdrivers'
require 'fileutils'
require 'optparse'

browser = Watir::Browser.new(:chrome, options: {
  "goog:loggingPrefs" => {
    "browser" => "ALL",
    "performance" => "ALL"
  },
  args: ['--force-device-scale-factor=1', '--hide-scrollbars', '--window-position=0,0']
})

Dir.chdir(File.dirname($0))

options = OpenStruct.new
OptionParser.new do |opts|
  opts.on("-s", "--suspend", "Pauses the script after each fixture to allow for debugging on Chrome. Press enter to go to the next fixure.") do
    options.suspend = true
  end
  opts.on("-f", "--fixture [FIXTURE]", String, "Only runs the script on the specific fixture.") do |f|
    fixture = "fixtures/" + f + ".html"
    if !File.file?(fixture)
      puts fixture + " does not exist."
    else
      options.fixture = fixture
    end
  end
end.parse!

files = options.fixture ? options.fixture : "fixtures/*.html"
Dir[files].each do |file|
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
  f.write sprintf(template, name, ltr_fixture, rtl_fixture, fixture)
  f.close
  FileUtils.copy('test.html', "#{name}.html") if $DEBUG

  browser.goto('file://' + Dir.pwd + '/test.html')
  logs = browser.driver.logs.get(:browser)

  f = File.open("../tests/generated/#{name}.cpp", 'w')
  f.write eval(logs[0].message.sub(/^[^"]*/, ''))
  f.close

  f = File.open("../java/tests/com/facebook/yoga/#{name}.java", 'w')
  f.write eval(logs[1].message.sub(/^[^"]*/, '')).sub('YogaTest', name)
  f.close

  print logs[3]

  f = File.open("../javascript/tests/generated/#{name}.test.ts", 'w')
  f.write eval(logs[2].message.sub(/^[^"]*/, '')).sub('YogaTest', name)
  f.close

  if options.suspend
    gets
  end
end
File.delete('test.html')
browser.close
