MSB=msbuild.exe /m /verbosity:m /nologo
NUGET=nuget.exe
NUNITC=nunit-console.exe

VER=1.0.0
NAME=Facebook.CSSLayout

.PHONY: all
all: test

.PHONY: distribute
distribute: package release-package

.PHONY: package
package: conf=Release
package: build
	cd ${NAME} && ${NUGET} pack ${NAME}.csproj -Version ${VER} -Prop Configuration=${conf}

.PHONY: release-package
release-package:
	cd ${NAME} && nuget push ${NAME}.${VER}.nupkg

.PHONY: test
test: build-debug
	cd ${NAME}.Tests/bin/Debug && ${NUNITC} Facebook.CSSLayout.Tests.dll

.PHONY: build-debug
build-debug: conf=Debug
build-debug: build

.PHONY: build-release
build-release: conf=Release
build-release: build

.PHONY: build
build:
	${MSB} ${NAME}.sln /p:Configuration=${conf} /t:"Facebook_CSSLayout:Rebuild;Facebook_CSSLayout_Tests:Rebuild"

