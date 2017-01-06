"C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe" ..\Yoga\Yoga.vcxproj /p:configuration=Release /property:Platform=x64
xcopy "..\Yoga\bin\x64\Release\yoga.dll" %~dp0 /s /d /y
