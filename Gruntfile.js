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

    copy: {
      main: {
        expand: true,
        src: ['<%= paths.srcFolder %>/Layout.js'],
        dest: '<%= paths.distFolder %>',
        rename: function(dest, src) {
          return dest + '/css-layout.js';
        }
      }
    },

    uglify: {
      options: {
        sourceMap: true,
        sourceMapIncludeSources: true
      },
      main: {
        files: {
          '<%= paths.distFolder %>/css-layout.min.js': ['<%= paths.srcFolder %>/Layout.js']
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

  grunt.registerTask('build', ['eslint', 'clean', 'karma' ,'copy', 'uglify']);

  grunt.registerTask('default', ['build']);
};
