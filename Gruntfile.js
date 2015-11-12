'use strict';

module.exports = function(grunt) {
  var path = require('path');
  var isWindows = (/^win/).test(process.platform);

  require('load-grunt-tasks')(grunt);

  // config
  var config = {
    delimiter: path.delimiter,
    libName: 'css-layout',
    distFolder: 'dist',
    srcFolder: 'src',
    testFolder: 'src/__tests__',
    javaLibFolder: 'src/java/lib',
    javaSource: 'src/java/tests/com/facebook/csslayout/*.java',
    javaTestFiles: 'org.junit.runner.JUnitCore com.facebook.csslayout.LayoutEngineTest com.facebook.csslayout.LayoutCachingTest com.facebook.csslayout.CSSNodeTest'
  };

  // C compilation configuration
  if (isWindows) {
    // Windows build, assumes cl is in the path (see https://msdn.microsoft.com/en-us/library/f2ccy3wt.aspx).
    config.cTestOutput = 'c_test.exe';
    config.cTestCompile = 'cl -nologo -Zi -Tpsrc/__tests__/Layout-test.c -Tpsrc/Layout.c -Tpsrc/Layout-test-utils.c -link -incremental:no -out:"<%= config.cTestOutput %>"';
    config.cTestExecute = '<%= config.cTestOutput %>';
    config.cTestClean = ['<%= config.cTestOutput %>', '*.obj', '*.pdb'];
  } else {
    // GCC build (OSX, Linux, ...), assumes gcc is in the path.
    config.cTestOutput = 'c_test';
    config.cTestCompile = 'gcc -std=c99 -Werror -Wno-padded src/__tests__/Layout-test.c src/Layout.c src/Layout-test-utils.c -lm -o "./<%= config.cTestOutput %>"';
    config.cTestExecute = './<%= config.cTestOutput %>';
    config.cTestClean = ['<%= config.cTestOutput %>'];
  }

  grunt.initConfig({
    config: config,

    mkdir: {
      dist: {
        options: {
          create: ['<%= config.distFolder %>']
        }
      }
    },

    clean: {
      dist: ['<%= config.distFolder %>/css-layout.*'],
      cTest: config.cTestClean,
      javaTest: ['**/*.class']
    },

    eslint: {
      options: {
        configFile: '.eslintrc'
      },
      target: ['<%= config.srcFolder %>/**/*.js', './Gruntfile.js']
    },

    includereplace: {
      options: {
        prefix: '// @@'
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

    concat: {
      options: {
        separator: '\n',
        // Replace all 'use strict' statements in the code with a single one at the top
        banner: [
          '/*',
          ' * #define CSS_LAYOUT_IMPLEMENTATION',
          ' * before you include this file in *one* C or C++ file to create the implementation.',
          ' */\n'
        ].join('\n'),
        process: function(src, filepath) {
          if (path.extname(filepath) === '.c') {
            return [
              '#ifdef CSS_LAYOUT_IMPLEMENTATION',
              src,
              '#endif // CSS_LAYOUT_IMPLEMENTATION'
            ].join('\n');
          } else {
            return src;
          }
        }
      },
      dist: {
        src: ['<%= config.srcFolder %>/Layout.h', '<%= config.srcFolder %>/Layout.c'],
        dest: '<%= config.distFolder %>/css-layout.h'
      }
    },

    shell: {
      cCompile: {
        command: config.cTestCompile
      },
      cTestExecute: {
        command: config.cTestExecute
      },
      javaCompile: {
        command: 'javac -cp <%= config.javaLibFolder %>/junit4.jar<%= config.delimiter %><%= config.javaLibFolder %>/jsr305.jar<%= config.delimiter %><%= config.javaLibFolder %>/infer-annotations-1.4.jar' + ' -sourcepath ./src/java/src<%= config.delimiter %>./src/java/tests' + ' <%= config.javaSource %>'
      },
      javaTestExecute: {
        command: 'java -cp ./src/java/src<%= config.delimiter %>./src/java/tests<%= config.delimiter %><%= config.javaLibFolder %>/junit4.jar<%= config.delimiter %><%= config.javaLibFolder %>/infer-annotations-1.4.jar <%= config.javaTestFiles %>'
      },
      javaPackage: {
        command: 'jar cf <%= config.distFolder %>/<%= config.libName %>.jar <%= config.javaSource %>'
      }
    },

    watch: {
      files: ['src/Layout.js'],
      tasks: ['ci']
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

  // Packages the C code as a single header
  grunt.registerTask('package-c', ['concat']);

  // package all languages
  grunt.registerTask('package-all', ['package-javascript', 'package-java', 'package-c']);

  // Default build, performs the full works!
  grunt.registerTask('build', ['test-javascript', 'transpile', 'clean:dist', 'mkdir:dist', 'package-all']);

  // The JavaScript unit tests require Chrome (they need a faithful flexbox implementation
  // to test against), so under CI this step is skipped.
  grunt.registerTask('ci', ['eslint', 'transpile', 'clean:dist', 'mkdir:dist', 'package-all']);

  grunt.registerTask('default', ['build']);
};
