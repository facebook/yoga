'use strict';

module.exports = function(grunt) {

  require('load-grunt-tasks')(grunt);

  grunt.initConfig({

    paths: {
      distFolder: 'dist',
      srcFolder: 'src',
      testFolder: 'src/__tests__',
    },

    clean: ['<%= paths.distFolder %>'],

    eslint: {
      options: {
        configFile: '.eslintrc'
      },
      target: ['<%= paths.srcFolder %>/Layout.js']
    },

    includereplace: {
      options: {
        prefix: '// @@',
      },
      main: {
        src: '<%= paths.srcFolder %>/css-layout.js',
        dest: '<%= paths.distFolder %>/css-layout.js'
      }
    },

    uglify: {
      options: {
        sourceMap: true,
        sourceMapIncludeSources: true
      },
      main: {
        files: {
          '<%= paths.distFolder %>/css-layout.min.js': ['<%= paths.distFolder %>/css-layout.js']
        }
      }
    },

    karma: {
      main: {
        options: {
          files: [
            '<%= paths.srcFolder %>/Layout.js',
            '<%= paths.srcFolder %>/Layout-test-utils.js',
            '<%= paths.testFolder %>/Layout-test.js',
            '<%= paths.testFolder %>/Layout-consts-test.js'
          ],
          browsers: ['Chrome'],
          frameworks: ['jasmine'],
          singleRun: true
        }
      }
    }
  });

  grunt.registerTask('build', ['eslint', 'clean', 'karma' ,'includereplace', 'uglify']);

  grunt.registerTask('default', ['build']);
};
