Releases can be found on [npm](https://www.npmjs.com/package/css-layout).

#Release Process

```bash
# Ensure that the local codebase is up to date
git fetch upstream master && git checkout FETCH_HEAD

# build the latest version of the library
grunt

# increment the version number and tag the release
npm version [<newversion> | major | minor | patch | premajor | preminor | prepatch | prerelease]

# push the the commit and tag back to upstream
git push --tags upstream HEAD:master

# publish this new version to npm
npm publish
```
