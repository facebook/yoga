
#!/bin/sh
if buck --version >/dev/null 2>&1; then true; else
echo "Building Buck!"
mkdir lib
cd lib
git clone https://github.com/facebook/buck.git
cd buck
ant
cd ..
cd ..
fi
#!/bin/bash


buck build //:yoga
buck build //csharp:yoganet-ios
buck build //csharp:yoganet#default,shared
buck build //csharp:yoganet#android-x86,shared
buck build //csharp:yoganet#android-armv7,shared