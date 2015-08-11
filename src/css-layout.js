// UMD (Universal Module Definition)
// See https://github.com/umdjs/umd for reference
(function (root, factory) {
  if (typeof define === 'function' && define.amd) {
    // AMD. Register as an anonymous module.
    define([], factory);
  } else if (typeof exports === 'object') {
    // Node. Does not work with strict CommonJS, but
    // only CommonJS-like environments that support module.exports,
    // like Node.
    module.exports = factory();
  } else {
    // Browser globals (root is window)
    root.computeLayout = factory();
  }
}(this, function () {
    // @@include('./Layout.js')

    return function(node) {
      node = computeLayout.fillNodes(node);
      computeLayout.computeLayout(node);
      node = computeLayout.extractNodes(node);
      return node;
  };
}));
