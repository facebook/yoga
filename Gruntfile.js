'use strict';

module.exports = function(grunt) {

  require('load-grunt-tasks')(grunt);

  grunt.initConfig({

    paths: {
      distFolder: 'dist',
      srcFolder: 'src',
      testFolder: 'src/__tests__',
      cTestFiles: 'src/__tests__/Layout-test.c src/Layout.c src/Layout-test-utils.c',
      cTestOutput: 'c_test'
    },

    clean: {
      dist: ['<%= paths.distFolder %>'],
      ctest: ['<%= paths.cTestOutput %>']
    },

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
    },

    execute: {
      transpile: {
        src: ['<%= paths.srcFolder %>/transpile.js']
      }
    },

    shell: {
      ccompile: {
        command: 'gcc -std=c99 -Werror -Wno-padded <%= paths.cTestFiles %> -lm -o "./<%= paths.cTestOutput %>"'
      },
      ctestExecute: {
        command: './<%= paths.cTestOutput %>'
      }
    }
  });

  
  grunt.registerTask('ctest', ['shell:ccompile', 'shell:ctestExecute', 'clean:ctest']);

  grunt.registerTask('transpile', ['execute:transpile', 'ctest']);

  grunt.registerTask('test-javascript', ['eslint', 'karma']);

  grunt.registerTask('package-javascript', ['clean:dist', 'includereplace', 'uglify']);

  grunt.registerTask('build', ['test-javascript', 'transpile', 'package-javascript']);

  grunt.registerTask('default', ['build']);
};
