'use strict';

module.exports = function (config) {
  config.set({

    // base path, that will be used to resolve files and exclude
    basePath: 'src',

    // frameworks to use
    frameworks: ['jasmine'],

    // list of files / patterns to load in the browser
    files: [
      'Layout.js',
      'Layout-test-utils.js',
      '__tests__/Layout-test.js',
      '__tests__/Layout-consts-test.js'
    ],

    plugins: [
      'karma-chrome-launcher',
      'karma-jasmine'
    ],

    // web server port
    port: 9876,

    // enable / disable colors in the output (reporters and logs)
    colors: true,

    // level of logging
    // possible values: config.LOG_DISABLE || config.LOG_ERROR || config.LOG_WARN || config.LOG_INFO || config.LOG_DEBUG
    logLevel: config.LOG_INFO,

    browsers: ['Chrome'],

    // If browser does not capture in given timeout [ms], kill it
    captureTimeout: 60000,

    singleRun: false
  });
};
