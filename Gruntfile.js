'use strict';

module.exports = function(grunt) {

  require('load-grunt-tasks')(grunt);

  var config = {
    libName: 'css-layout',
    distFolder: 'dist',
    srcFolder: 'src',
    testFolder: 'src/__tests__',
    cTestFiles: 'src/__tests__/Layout-test.c src/Layout.c src/Layout-test-utils.c',
    cTestOutput: 'c_test',
    javaLibFolder: 'src/java/lib',
    javaSource: 'src/java/tests/com/facebook/csslayout/*.java',
    javaTestFiles: 'org.junit.runner.JUnitCore com.facebook.csslayout.LayoutEngineTest com.facebook.csslayout.LayoutCachingTest com.facebook.csslayout.CSSNodeTest'
  };

  grunt.initConfig({

    config: config,

    clean: {
      dist: ['<%= config.distFolder %>'],
      cTest: ['<%= config.cTestOutput %>'],
      javaTest: ['**/*.class']
    },

    eslint: {
      options: {
        configFile: '.eslintrc'
      },
      target: ['<%= config.srcFolder %>/Layout.js']
    },

    includereplace: {
      options: {
        prefix: '// @@',
      },
      main: {
        src: '<%= config.srcFolder %>/<%= config.libName %>.js',
        dest: '<%= config.distFolder %>/<%= config.libName %>.js'
      }
    },

    uglify: {
      options: {
        sourceMap: true,
        sourceMapIncludeSources: true
      },
      main: {
        files: {
          '<%= config.distFolder %>/<%= config.libName %>.min.js':
            ['<%= config.distFolder %>/<%= config.libName %>.js']
        }
      }
    },

    karma: {
      main: {
        options: {
          files: [
            '<%= config.srcFolder %>/Layout.js',
            '<%= config.srcFolder %>/Layout-test-utils.js',
            '<%= config.testFolder %>/Layout-test.js',
            '<%= config.testFolder %>/Layout-consts-test.js'
          ],
          browsers: ['Chrome'],
          frameworks: ['jasmine'],
          singleRun: true
        }
      }
    },

    execute: {
      transpile: {
        src: ['<%= config.srcFolder %>/transpile.js']
      }
    },

    shell: {
      cCompile: {
        command: 'gcc -std=c99 -Werror -Wno-padded <%= config.cTestFiles %> -lm -o "./<%= config.cTestOutput %>"'
      },
      cTestExecute: {
        command: './<%= config.cTestOutput %>'
      },
      javaCompile: {
        command: 'javac -cp <%= config.javaLibFolder %>/junit4.jar:<%= config.javaLibFolder %>/jsr305.jar:<%= config.javaLibFolder %>/infer-annotations-1.4.jar -sourcepath ./src/java/src:./src/java/tests <%= config.javaSource %>'
      },
      javaTestExecute: {
        command: 'java -cp ./src/java/src:./src/java/tests:<%= config.javaLibFolder %>/junit4.jar:<%= config.javaLibFolder %>/infer-annotations-1.4.jar <%= config.javaTestFiles %>'
      },
      javaPackage: {
        command: 'jar cf <%= config.distFolder %>/<%= config.libName %>.jar <%= config.javaSource %>'
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

  grunt.registerTask('ci', ['eslint', 'transpile', 'clean:dist', 'package-javascript', 'package-java']);

  grunt.registerTask('default', ['build']);
};
