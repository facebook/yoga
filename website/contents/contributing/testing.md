---
path: "/contributing/testing"
title: "Testing"
hasPlayground: false
---

# Testing

Yoga tries to be as close as possible to chrome in its flexbox behaviour.
To ensure this most of Yoga's test suite is automatically generateded from
running the corresponding layout in chrome using a webdriver which then generates
C++ test which asserts that Yoga will produce matching outputs for that layout.

## Running the Test Suite

1. Yoga builds with [buck](https://buckbuild.com). Follow their documentation to get up and running.
2. For testing Yoga relies on [gtest](https://github.com/google/googletest) as a submodule. After cloning Yoga run `git submodule init` followed by `git submodule update`.
3. In a terminal from the root of your Yoga checkout run `buck test //:yoga`.

## Adding a Test

Instead of manually writing a test which ensures parity with web implementations
of Flexbox we make use of a generated test suite. We use `gentest/gentest.rb` to
generate this test suite. Write the html which you want to verify in Yoga and put
it in the `gentest/fixtures` folder, such as the following.

```html
<div id="my_test" style="width: 100px; height: 100px; align-items: center;">
  <div style="width: 50px; height: 50px;"></div>
</div>
```

Run `gentest/gentest.rb` to generate test code and re-run `buck test //:yoga`
to validate the behavior. One test case will be generated for every root `div`
in the input html with the string in the `id` corresponding to the test name.

You should run `bundle install` in the `gentest` directory to install dependencies for the `gentest/gentest.rb` Ruby script.

## Manual test

For some aspects of Yoga we cannot generate a test using the test generation
infrastructure described earlier. For these cases we manually write a test in
the `/tests` directory.
