
function computeLayout(node) {

  function getMargin(node) {
    if ('margin' in node.style) {
      return node.style.margin;
    }
    return 0;
  }

  function layoutNode(node, parent) {
    var top = 0;
    var children = [];
    (node.children || []).forEach(function(child) {
      children.push(layoutNode(child, {
        top: top,
        left: 0
      }));
      top += child.style.height;
    });

    var result = {
      width: node.style.width,
      height: node.style.height,
      top: getMargin(node) + parent.top + 0,
      left: getMargin(node) + parent.left + 0
    };

    if (children.length > 0) {
      result.children = children;
    }
    return result;
  }

  return layoutNode(node, {top: 0, left: 0});
}

