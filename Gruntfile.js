'use strict';

module.exports = function(grunt) {

  require('load-grunt-tasks')(grunt);

  grunt.initConfig({

    paths: {
      libName: 'css-layout',
      distFolder: 'dist',
      srcFolder: 'src',
      testFolder: 'src/__tests__',
      cTestFiles: 'src/__tests__/Layout-test.c src/Layout.c src/Layout-test-utils.c',
      cTestOutput: 'c_test',
      javaLibFolder: 'src/java/lib',
      javaSource: 'src/java/tests/com/facebook/csslayout/*.java',
      javaTestFiles: 'org.junit.runner.JUnitCore com.facebook.csslayout.LayoutEngineTest com.facebook.csslayout.LayoutCachingTest com.facebook.csslayout.CSSNodeTest'
    },

    clean: {
      dist: ['<%= paths.distFolder %>'],
      cTest: ['<%= paths.cTestOutput %>'],
      javaTest: ['**/*.class']
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
        src: '<%= paths.srcFolder %>/<%= paths.libName %>.js',
        dest: '<%= paths.distFolder %>/<%= paths.libName %>.js'
      }
    },

    uglify: {
      options: {
        sourceMap: true,
        sourceMapIncludeSources: true
      },
      main: {
        files: {
          '<%= paths.distFolder %>/<%= paths.libName %>.min.js':
            ['<%= paths.distFolder %>/<%= paths.libName %>.js']
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
      cCompile: {
        command: 'gcc -std=c99 -Werror -Wno-padded <%= paths.cTestFiles %> -lm -o "./<%= paths.cTestOutput %>"'
      },
      cTestExecute: {
        command: './<%= paths.cTestOutput %>'
      },
      javaCompile: {
        command: 'javac -cp <%= paths.javaLibFolder %>/junit4.jar:<%= paths.javaLibFolder %>/jsr305.jar:<%= paths.javaLibFolder %>/infer-annotations-1.4.jar -sourcepath ./src/java/src:./src/java/tests <%= paths.javaSource %>'
      },
      javaTestExecute: {
        command: 'java -cp ./src/java/src:./src/java/tests:<%= paths.javaLibFolder %>/junit4.jar:<%= paths.javaLibFolder %>/infer-annotations-1.4.jar <%= paths.javaTestFiles %>'
      },
      javaPackage: {
        command: 'jar cf <%= paths.distFolder %>/<%= paths.libName %>.jar <%= paths.javaSource %>'
      }
    }
  });

  grunt.registerTask('test-java', ['shell:javaCompile', 'shell:javaTestExecute', 'clean:javaTest']);

  grunt.registerTask('test-c', ['shell:cCompile', 'shell:cTestExecute', 'clean:cTest']);

  grunt.registerTask('transpile', ['execute:transpile', 'test-c', 'test-java']);

  grunt.registerTask('test-javascript', ['eslint', 'karma']);

  grunt.registerTask('package-javascript', ['includereplace', 'uglify']);

  grunt.registerTask('package-java', ['shell:javaPackage']);

  grunt.registerTask('build', ['test-javascript', 'transpile', 'clean:dist', 'package-javascript', 'package-java']);

  grunt.registerTask('default', ['build']);
};
