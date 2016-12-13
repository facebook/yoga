$solutionRoot = Resolve-Path ..\

# Delete any existing output.
Remove-Item *.nupkg

# Create new packages for any nuspec files that exist in this directory.
Foreach ($nuspec in $(Get-Item *.nuspec))
{
	.\Tools\NuGet.exe pack "$nuspec"
}