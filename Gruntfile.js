'use strict';

module.exports = function(grunt) {

  grunt.initConfig({

    paths: {
      distFolder: 'dist',
      srcFolder: 'src',
      testFolder: 'src/__tests__',
    },

    clean: ['<%= paths.distFolder %>'],

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

  grunt.loadNpmTasks('grunt-contrib-clean');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-karma');

  grunt.registerTask('build', ['clean', 'karma' ,'copy', 'uglify']);

  grunt.registerTask('default', ['build']);

};
