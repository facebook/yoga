'use strict';

module.exports = function(grunt) {
  var fs = require('fs');
  var path = require('path');
  var isWindows = /^win/.test(process.platform);

  require('load-grunt-tasks')(grunt);

  // config
  var config = {
    libName: 'css-layout',
    distFolder: 'dist',
    srcFolder: 'src',
    testFolder: 'src/__tests__',
    javaLibFolder: 'src/java/lib',
    javaSource: 'src/java/tests/com/facebook/csslayout/*.java',
    javaTestFiles: 'org.junit.runner.JUnitCore com.facebook.csslayout.LayoutEngineTest com.facebook.csslayout.LayoutCachingTest com.facebook.csslayout.CSSNodeTest'
  };

  // Create the dist folder if it doesn't exist. It is deleted by the 'clean' task.
  if (!fs.existsSync(config.distFolder)){
    fs.mkdirSync(config.distFolder);
  }

  // C compilation configuration
  var cTestClean, cTestCompile, cTestExecute;
  if (isWindows) {
    // Windows build, assumes cl is in the path (see https://msdn.microsoft.com/en-us/library/f2ccy3wt.aspx).
    config.cTestOutput = 'c_test.exe';
    cTestCompile = 'cl -nologo -Zi -Tpsrc/__tests__/Layout-test.c -Tpsrc/Layout.c -Tpsrc/Layout-test-utils.c -link -incremental:no -out:"<%= config.cTestOutput %>"';
    cTestExecute = '<%= config.cTestOutput %>';
    cTestClean = ['<%= config.cTestOutput %>','*.obj','*.pdb'];
  }
  else {
    // GCC build (OSX, Linux, ...), assumes gcc is in the path.
    config.cTestOutput = 'c_test';
    cTestCompile = 'gcc -std=c99 -Werror -Wno-padded src/__tests__/Layout-test.c src/Layout.c src/Layout-test-utils.c -lm -o "./<%= config.cTestOutput %>"';
    cTestExecute = './<%= config.cTestOutput %>';
    cTestClean = ['<%= config.cTestOutput %>'];
  }

  grunt.initConfig({

    config: config,

    clean: {
      dist: ['<%= config.distFolder %>'],
      cTest: cTestClean,
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
        command: cTestCompile
      },
      cTestExecute: {
        command: cTestExecute
      },
      javaCompile: {
        command: 'javac -cp <%= config.javaLibFolder %>/junit4.jar' +
          path.delimiter + '<%= config.javaLibFolder %>/jsr305.jar' +
          path.delimiter + '<%= config.javaLibFolder %>/infer-annotations-1.4.jar' +
          ' -sourcepath ./src/java/src' +
          path.delimiter + './src/java/tests' +
          ' <%= config.javaSource %>'
      },
      javaTestExecute: {
        command: 'java -cp ./src/java/src' +
          path.delimiter + './src/java/tests' +
          path.delimiter + '<%= config.javaLibFolder %>/junit4.jar' +
          path.delimiter + '<%= config.javaLibFolder %>/infer-annotations-1.4.jar' +
          ' <%= config.javaTestFiles %>'
      },
      javaPackage: {
        command: 'jar cf <%= config.distFolder %>/<%= config.libName %>.jar <%= config.javaSource %>'
      }
    }
  });

  // Compiles and runs the Java tests
  grunt.registerTask('test-java', ['shell:javaCompile', 'shell:javaTestExecute', 'clean:javaTest']);

  // Compiles and runs the C tests
  grunt.registerTask('test-c', ['shell:cCompile', 'shell:cTestExecute', 'clean:cTest']);

  // Transpiles the JavaScript to C and Java, running tests
  grunt.registerTask('transpile', ['execute:transpile', 'test-c', 'test-java']);

  // Lints and tests the JavaScritp using Chrome
  grunt.registerTask('test-javascript', ['eslint', 'karma']);

  // Packages the JavaScript as a single UMD module and minifies
  grunt.registerTask('package-javascript', ['includereplace', 'uglify']);

  // Packages the Java as a JAR
  grunt.registerTask('package-java', ['shell:javaPackage']);

  // Default build, performs the full works!
  grunt.registerTask('build', ['test-javascript', 'transpile', 'clean:dist', 'package-javascript', 'package-java']);

  // The JavaScript unit tests require Chrome (they need a faithful flexbox implementation
  // to test against), so under CI this step is skipped.
  grunt.registerTask('ci', ['eslint', 'transpile', 'clean:dist', 'package-javascript', 'package-java']);

  grunt.registerTask('default', ['build']);
};
