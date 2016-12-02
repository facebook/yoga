#!/bin/sh
if clang --version >/dev/null 2>&1; then true; else
  echo "ERROR: Can't execute clang. You need to install Xcode and command line tools."
  exit 1
fi

if mcs --version >/dev/null 2>&1; then true; else
  echo "ERROR: Can't execute mcs. You need to install Mono from http://www.mono-project.com/download/ and re-login to apply PATH environment."
  exit 1
fi

if mono --version >/dev/null 2>&1; then true; else
  echo "ERROR: Can't execute mono64. You need to install Mono from http://www.mono-project.com/download/ and re-login to apply PATH environment."
  exit 1
fi

cd "$( dirname "$0" )"

NUNIT=NUnit-2.6.4/bin
if [ -d $NUNIT \
    -a -f $NUNIT/nunit-console.exe \
    -a -f $NUNIT/lib/nunit-console-runner.dll \
    -a -f $NUNIT/lib/nunit.core.dll \
    -a -f $NUNIT/lib/nunit.core.interfaces.dll \
    -a -f $NUNIT/lib/nunit.util.dll ]; then true; else
  curl -L -O https://github.com/nunit/nunitv2/releases/download/2.6.4/NUnit-2.6.4.zip
  unzip -qq NUnit-2.6.4.zip
  rm NUnit-2.6.4.zip
fi

clang -g -Wall -Wextra -dynamiclib -o libyoga.dylib -I../../.. ../../../CSSLayout/*.c ../../Yoga/YGInterop.cpp
mcs -debug -t:library -r:$NUNIT/nunit.framework.dll -out:YogaTest.dll *.cs ../../../csharp/Facebook.Yoga/*cs
MONO_PATH=$NUNIT mono --arch=64 --debug $NUNIT/nunit-console.exe YogaTest.dll
