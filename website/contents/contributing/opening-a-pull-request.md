---
path: "/contributing/opening-a-pull-request"
title: "Opening a Pull Request"
hasPlayground: false
---

# Opening a Pull Request

Before opening your first pull request to Yoga you have to know how to get the code,
install build time dependencies, and test the code locally.

### Clone

```
$> git clone https://github.com/facebook/yoga.git
$> cd yoga
```

### Install dependencies

```
$> git submodule init
$> git submodule update
$> brew install buck
```

### Build and Test

```
$> buck build //:yoga
$> buck test //:yoga
```

## Making a Change

Now all you need to do is make your change and test it before submitting a pull request for review.
Below is the general structure of the repo and where you may want to make your change. One you have
made your change see the [testing documentation](/contributing/testing) for more on how to test your change.

``` bash
/yoga
|-- yoga                  # Home to the main Yoga codebase written in C++. Any algorithmic changes should be made here
|-- lib                   # Yoga external dependencies. Be thoughtful adding any new ones
|-- tests                 # Yoga's C++ test suite. Both manaul and generated tests
|-- gentest
|   |-- fixtures          # html fixtures for generated tests
|-- java
|   |-- com/facebook/yoga # Java binding code
|   |-- jni               # JNI binding code
|-- javascript            # emscripten / javascript bindings
```
