'use strict';

module.exports = function(grunt) {

  grunt.initConfig({

    paths: {
      distFolder: 'dist',
      srcFolder: 'src'
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
    }
  });

  grunt.loadNpmTasks('grunt-contrib-clean');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-contrib-uglify');

  grunt.registerTask('build', ['clean', 'copy', 'uglify']);

  grunt.registerTask('default', ['build']);

};
