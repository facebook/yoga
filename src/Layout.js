
function computeLayout(node) {
  var top = 0;
  var children = [];
  (node.children || []).forEach(function(child) {
    console.log(child);
    children.push({
      top: top,
      left: 0,
      width: child.style.width,
      height: child.style.height
    });
    top += child.style.height;
  });

  var result = {
    top: 0,
    left: 0,
    width: node.style.width,
    height: node.style.height
  };

  if (children.length > 0) {
    result.children = children;
  }
  return result;
}

