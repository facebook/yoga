
function computeLayout(node) {

  function getMargin(node) {
    if ('margin' in node.style) {
      return node.style.margin;
    }
    return 0;
  }

  var pos = {
    row: 'left',
    column: 'top'
  };
  var dim = {
    row: 'width',
    column: 'height'
  };

  function layoutNode(node, parent) {
    var mainAxis = node.style.flexDirection === 'row' ? 'row' : 'column';
    var crossAxis = mainAxis === 'row' ? 'column' : 'row';

    var mainPos = 0;
    var children = [];
    (node.children || []).forEach(function(child) {
      var offset = {};
      offset[pos[mainAxis]] = mainPos;
      offset[pos[crossAxis]] = 0;
      children.push(layoutNode(child, offset));

      mainPos += child.style[dim[mainAxis]] + 2 * getMargin(child);
    });

    var result = {
      width: node.style.width,
      height: node.style.height,
      top: getMargin(node) + parent.top,
      left: getMargin(node) + parent.left
    };

    if (children.length > 0) {
      result.children = children;
    }
    return result;
  }

  return layoutNode(node, {top: 0, left: 0});
}

