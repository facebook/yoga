Releases can be found on [npm](https://www.npmjs.com/package/dss-layout).

#Release Process

```bash
# Ensure that the local codebase is up to date
git fetch upstream master && git checkout FETCH_HEAD

npm version [<newversion> | major | minor | patch | premajor | preminor | prepatch | prerelease]
```

This will take care of getting the latest version of `upstream/master`, updating the package.json, committing, tagging and pushing back to `upstream/master`. Travis will then take care of building the packages and pushing to npm.
