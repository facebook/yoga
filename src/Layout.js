  /**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var computeLayout = (function() {

  var POSITIVE_FLEX_IS_AUTO = false;

  var gCurrentGenerationCount = 0;

  var CSS_UNDEFINED;

  var CSS_LEFT = 'left';
  var CSS_TOP = 'top';
  var CSS_RIGHT = 'right';
  var CSS_BOTTOM = 'bottom';

  var CSS_DIRECTION_INHERIT = 'inherit';
  var CSS_DIRECTION_LTR = 'ltr';
  var CSS_DIRECTION_RTL = 'rtl';

  var CSS_FLEX_DIRECTION_ROW = 'row';
  var CSS_FLEX_DIRECTION_ROW_REVERSE = 'row-reverse';
  var CSS_FLEX_DIRECTION_COLUMN = 'column';
  var CSS_FLEX_DIRECTION_COLUMN_REVERSE = 'column-reverse';

  var CSS_JUSTIFY_FLEX_START = 'flex-start';
  var CSS_JUSTIFY_CENTER = 'center';
  var CSS_JUSTIFY_FLEX_END = 'flex-end';
  var CSS_JUSTIFY_SPACE_BETWEEN = 'space-between';
  var CSS_JUSTIFY_SPACE_AROUND = 'space-around';

  var CSS_ALIGN_FLEX_START = 'flex-start';
  var CSS_ALIGN_CENTER = 'center';
  var CSS_ALIGN_FLEX_END = 'flex-end';
  var CSS_ALIGN_STRETCH = 'stretch';

  var CSS_POSITION_RELATIVE = 'relative';
  var CSS_POSITION_ABSOLUTE = 'absolute';

  var CSS_OVERFLOW_VISIBLE = 'visible';
  var CSS_OVERFLOW_HIDDEN = 'hidden';

  var CSS_MEASURE_MODE_UNDEFINED = 'undefined';
  var CSS_MEASURE_MODE_EXACTLY = 'exactly';
  var CSS_MEASURE_MODE_AT_MOST = 'at-most';

  var leading = {
    'row': 'left',
    'row-reverse': 'right',
    'column': 'top',
    'column-reverse': 'bottom'
  };
  var trailing = {
    'row': 'right',
    'row-reverse': 'left',
    'column': 'bottom',
    'column-reverse': 'top'
  };
  var pos = {
    'row': 'left',
    'row-reverse': 'right',
    'column': 'top',
    'column-reverse': 'bottom'
  };
  var dim = {
    'row': 'width',
    'row-reverse': 'width',
    'column': 'height',
    'column-reverse': 'height'
  };
  var measuredDim = {
    'row': 'measuredWidth',
    'row-reverse': 'measuredWidth',
    'column': 'measuredHeight',
    'column-reverse': 'measuredHeight'
  };

  // When transpiled to Java / C the node type has layout, children and style
  // properties. For the JavaScript version this function adds these properties
  // if they don't already exist.
  function fillNodes(node) {
    if (!node.layout || node.isDirty) {
      node.layout = {
        width: undefined,
        height: undefined,
        top: 0,
        left: 0,
        right: 0,
        bottom: 0
      };
    }

    if (!node.style) {
      node.style = {};
    }

    if (!node.children) {
      node.children = [];
    }

    if (node.style.measure && node.children && node.children.length) {
      throw new Error('Using custom measure function is supported only for leaf nodes.');
    }

    node.children.forEach(fillNodes);
    return node;
  }

  function isUndefined(value) {
    return value === undefined || Number.isNaN(value);
  }

  function isRowDirection(flexDirection) {
    return flexDirection === CSS_FLEX_DIRECTION_ROW ||
           flexDirection === CSS_FLEX_DIRECTION_ROW_REVERSE;
  }

  function isColumnDirection(flexDirection) {
    return flexDirection === CSS_FLEX_DIRECTION_COLUMN ||
           flexDirection === CSS_FLEX_DIRECTION_COLUMN_REVERSE;
  }

  function getFlex(node) {
    if (node.style.flex === undefined) {
      return 0;
    }
    return node.style.flex;
  }

  function isFlexBasisAuto(node) {
    if (POSITIVE_FLEX_IS_AUTO) {
      // All flex values are auto.
      return true;
    } else {
      // A flex value > 0 implies a basis of zero.
      return getFlex(node) <= 0;
    }
  }

  function getFlexGrowFactor(node) {
    // Flex grow is implied by positive values for flex.
    if (getFlex(node) > 0) {
      return getFlex(node);
    }
    return 0;
  }

  function getFlexShrinkFactor(node) {
    if (POSITIVE_FLEX_IS_AUTO) {
      // A flex shrink factor of 1 is implied by non-zero values for flex.
      if (getFlex(node) !== 0) {
        return 1;
      }
    } else {
      // A flex shrink factor of 1 is implied by negative values for flex.
      if (getFlex(node) < 0) {
        return 1;
      }
    }
    return 0;
  }

  function getLeadingMargin(node, axis) {
    if (node.style.marginStart !== undefined && isRowDirection(axis)) {
      return node.style.marginStart;
    }

    var value = null;
    switch (axis) {
      case 'row':            value = node.style.marginLeft;   break;
      case 'row-reverse':    value = node.style.marginRight;  break;
      case 'column':         value = node.style.marginTop;    break;
      case 'column-reverse': value = node.style.marginBottom; break;
    }

    if (value !== undefined) {
      return value;
    }

    if (node.style.margin !== undefined) {
      return node.style.margin;
    }

    return 0;
  }

  function getTrailingMargin(node, axis) {
    if (node.style.marginEnd !== undefined && isRowDirection(axis)) {
      return node.style.marginEnd;
    }

    var value = null;
    switch (axis) {
      case 'row':            value = node.style.marginRight;  break;
      case 'row-reverse':    value = node.style.marginLeft;   break;
      case 'column':         value = node.style.marginBottom; break;
      case 'column-reverse': value = node.style.marginTop;    break;
    }

    if (value != null) {
      return value;
    }

    if (node.style.margin !== undefined) {
      return node.style.margin;
    }

    return 0;
  }

  function getLeadingPadding(node, axis) {
    if (node.style.paddingStart !== undefined && node.style.paddingStart >= 0
        && isRowDirection(axis)) {
      return node.style.paddingStart;
    }

    var value = null;
    switch (axis) {
      case 'row':            value = node.style.paddingLeft;   break;
      case 'row-reverse':    value = node.style.paddingRight;  break;
      case 'column':         value = node.style.paddingTop;    break;
      case 'column-reverse': value = node.style.paddingBottom; break;
    }

    if (value != null && value >= 0) {
      return value;
    }

    if (node.style.padding !== undefined && node.style.padding >= 0) {
      return node.style.padding;
    }

    return 0;
  }

  function getTrailingPadding(node, axis) {
    if (node.style.paddingEnd !== undefined && node.style.paddingEnd >= 0
        && isRowDirection(axis)) {
      return node.style.paddingEnd;
    }

    var value = null;
    switch (axis) {
      case 'row':            value = node.style.paddingRight;  break;
      case 'row-reverse':    value = node.style.paddingLeft;   break;
      case 'column':         value = node.style.paddingBottom; break;
      case 'column-reverse': value = node.style.paddingTop;    break;
    }

    if (value != null && value >= 0) {
      return value;
    }

    if (node.style.padding !== undefined && node.style.padding >= 0) {
      return node.style.padding;
    }

    return 0;
  }

  function getLeadingBorder(node, axis) {
    if (node.style.borderStartWidth !== undefined && node.style.borderStartWidth >= 0
        && isRowDirection(axis)) {
      return node.style.borderStartWidth;
    }

    var value = null;
    switch (axis) {
      case 'row':            value = node.style.borderLeftWidth;   break;
      case 'row-reverse':    value = node.style.borderRightWidth;  break;
      case 'column':         value = node.style.borderTopWidth;    break;
      case 'column-reverse': value = node.style.borderBottomWidth; break;
    }

    if (value != null && value >= 0) {
      return value;
    }

    if (node.style.borderWidth !== undefined && node.style.borderWidth >= 0) {
      return node.style.borderWidth;
    }

    return 0;
  }

  function getTrailingBorder(node, axis) {
    if (node.style.borderEndWidth !== undefined && node.style.borderEndWidth >= 0
        && isRowDirection(axis)) {
      return node.style.borderEndWidth;
    }

    var value = null;
    switch (axis) {
      case 'row':            value = node.style.borderRightWidth;  break;
      case 'row-reverse':    value = node.style.borderLeftWidth;   break;
      case 'column':         value = node.style.borderBottomWidth; break;
      case 'column-reverse': value = node.style.borderTopWidth;    break;
    }

    if (value != null && value >= 0) {
      return value;
    }

    if (node.style.borderWidth !== undefined && node.style.borderWidth >= 0) {
      return node.style.borderWidth;
    }

    return 0;
  }

  function getLeadingPaddingAndBorder(node, axis) {
    return getLeadingPadding(node, axis) + getLeadingBorder(node, axis);
  }

  function getTrailingPaddingAndBorder(node, axis) {
    return getTrailingPadding(node, axis) + getTrailingBorder(node, axis);
  }

  function getMarginAxis(node, axis) {
    return getLeadingMargin(node, axis) + getTrailingMargin(node, axis);
  }

  function getPaddingAndBorderAxis(node, axis) {
    return getLeadingPaddingAndBorder(node, axis) +
        getTrailingPaddingAndBorder(node, axis);
  }

  function getJustifyContent(node) {
    if (node.style.justifyContent) {
      return node.style.justifyContent;
    }
    return 'flex-start';
  }

  function getAlignContent(node) {
    if (node.style.alignContent) {
      return node.style.alignContent;
    }
    return 'flex-start';
  }

  function getAlignItem(node, child) {
    if (child.style.alignSelf) {
      return child.style.alignSelf;
    }
    if (node.style.alignItems) {
      return node.style.alignItems;
    }
    return 'stretch';
  }

  function resolveAxis(axis, direction) {
    if (direction === CSS_DIRECTION_RTL) {
      if (axis === CSS_FLEX_DIRECTION_ROW) {
        return CSS_FLEX_DIRECTION_ROW_REVERSE;
      } else if (axis === CSS_FLEX_DIRECTION_ROW_REVERSE) {
        return CSS_FLEX_DIRECTION_ROW;
      }
    }

    return axis;
  }

  function resolveDirection(node, parentDirection) {
    var direction;
    if (node.style.direction) {
      direction = node.style.direction;
    } else {
      direction = CSS_DIRECTION_INHERIT;
    }

    if (direction === CSS_DIRECTION_INHERIT) {
      direction = (parentDirection === undefined ? CSS_DIRECTION_LTR : parentDirection);
    }

    return direction;
  }

  function getFlexDirection(node) {
    if (node.style.flexDirection) {
      return node.style.flexDirection;
    }
    return CSS_FLEX_DIRECTION_COLUMN;
  }

  function getCrossFlexDirection(flexDirection, direction) {
    if (isColumnDirection(flexDirection)) {
      return resolveAxis(CSS_FLEX_DIRECTION_ROW, direction);
    } else {
      return CSS_FLEX_DIRECTION_COLUMN;
    }
  }

  function getPositionType(node) {
    if (node.style.position) {
      return node.style.position;
    }
    return CSS_POSITION_RELATIVE;
  }

  function getOverflow(node) {
    if (node.style.overflow) {
      return node.style.overflow;
    }
    return CSS_OVERFLOW_VISIBLE;
  }

  function isFlex(node) {
    return (
      getPositionType(node) === CSS_POSITION_RELATIVE &&
      node.style.flex !== undefined && node.style.flex !== 0
    );
  }

  function isFlexWrap(node) {
    return node.style.flexWrap === 'wrap';
  }

  function getDimWithMargin(node, axis) {
    return node.layout[measuredDim[axis]] + getMarginAxis(node, axis);
  }

  function isStyleDimDefined(node, axis) {
    return node.style[dim[axis]] !== undefined && node.style[dim[axis]] >= 0;
  }

  function isLayoutDimDefined(node, axis) {
    return node.layout[measuredDim[axis]] !== undefined && node.layout[measuredDim[axis]] >= 0;
  }

  function isPosDefined(node, pos) {
    return node.style[pos] !== undefined;
  }

  function isMeasureDefined(node) {
    return node.style.measure !== undefined;
  }

  function getPosition(node, pos) {
    if (node.style[pos] !== undefined) {
      return node.style[pos];
    }
    return 0;
  }

  function boundAxisWithinMinAndMax(node, axis, value) {
    var min = {
      'row': node.style.minWidth,
      'row-reverse': node.style.minWidth,
      'column': node.style.minHeight,
      'column-reverse': node.style.minHeight
    }[axis];

    var max = {
      'row': node.style.maxWidth,
      'row-reverse': node.style.maxWidth,
      'column': node.style.maxHeight,
      'column-reverse': node.style.maxHeight
    }[axis];

    var boundValue = value;
    if (max !== undefined && max >= 0 && boundValue > max) {
      boundValue = max;
    }
    if (min !== undefined && min >= 0 && boundValue < min) {
      boundValue = min;
    }
    return boundValue;
  }

  function fminf(a, b) {
    if (a < b) {
      return a;
    }
    return b;
  }

  function fmaxf(a, b) {
    if (a > b) {
      return a;
    }
    return b;
  }

  // Like boundAxisWithinMinAndMax but also ensures that the value doesn't go below the
  // padding and border amount.
  function boundAxis(node, axis, value) {
    return fmaxf(boundAxisWithinMinAndMax(node, axis, value), getPaddingAndBorderAxis(node, axis));
  }

  function setTrailingPosition(node, child, axis) {
    var size = (getPositionType(child) === CSS_POSITION_ABSOLUTE) ?
      0 :
      child.layout[measuredDim[axis]];
    child.layout[trailing[axis]] = node.layout[measuredDim[axis]] - size - child.layout[pos[axis]];
  }

  // If both left and right are defined, then use left. Otherwise return
  // +left or -right depending on which is defined.
  function getRelativePosition(node, axis) {
    if (node.style[leading[axis]] !== undefined) {
      return getPosition(node, leading[axis]);
    }
    return -getPosition(node, trailing[axis]);
  }

  function setPosition(node, direction) {
    var mainAxis = resolveAxis(getFlexDirection(node), direction);
    var crossAxis = getCrossFlexDirection(mainAxis, direction);

    node.layout[leading[mainAxis]] = getLeadingMargin(node, mainAxis) +
      getRelativePosition(node, mainAxis);
    node.layout[trailing[mainAxis]] = getTrailingMargin(node, mainAxis) +
      getRelativePosition(node, mainAxis);
    node.layout[leading[crossAxis]] = getLeadingMargin(node, crossAxis) +
      getRelativePosition(node, crossAxis);
    node.layout[trailing[crossAxis]] = getTrailingMargin(node, crossAxis) +
      getRelativePosition(node, crossAxis);
  }

  function assert(condition, message) {
    if (!condition) {
      throw new Error(message);
    }
  }

  //
  // This is the main routine that implements a subset of the flexbox layout algorithm
  // described in the W3C CSS documentation: https://www.w3.org/TR/css3-flexbox/.
  //
  // Limitations of this algorithm, compared to the full standard:
  //  * Display property is always assumed to be 'flex' except for Text nodes, which
  //    are assumed to be 'inline-flex'.
  //  * The 'zIndex' property (or any form of z ordering) is not supported. Nodes are
  //    stacked in document order.
  //  * The 'order' property is not supported. The order of flex items is always defined
  //    by document order.
  //  * The 'visibility' property is always assumed to be 'visible'. Values of 'collapse'
  //    and 'hidden' are not supported.
  //  * The 'wrap' property supports only 'nowrap' (which is the default) or 'wrap'. The
  //    rarely-used 'wrap-reverse' is not supported.
  //  * Rather than allowing arbitrary combinations of flexGrow, flexShrink and
  //    flexBasis, this algorithm supports only the three most common combinations:
  //      flex: 0 is equiavlent to flex: 0 0 auto
  //      flex: n (where n is a positive value) is equivalent to flex: n 1 auto
  //          If POSITIVE_FLEX_IS_AUTO is 0, then it is equivalent to flex: n 0 0
  //          This is faster because the content doesn't need to be measured, but it's
  //          less flexible because the basis is always 0 and can't be overriden with
  //          the width/height attributes.
  //      flex: -1 (or any negative value) is equivalent to flex: 0 1 auto
  //  * Margins cannot be specified as 'auto'. They must be specified in terms of pixel
  //    values, and the default value is 0.
  //  * The 'baseline' value is not supported for alignItems and alignSelf properties.
  //  * Values of width, maxWidth, minWidth, height, maxHeight and minHeight must be
  //    specified as pixel values, not as percentages.
  //  * There is no support for calculation of dimensions based on intrinsic aspect ratios
  //     (e.g. images).
  //  * There is no support for forced breaks.
  //  * It does not support vertical inline directions (top-to-bottom or bottom-to-top text).
  //
  // Deviations from standard:
  //  * Section 4.5 of the spec indicates that all flex items have a default minimum
  //    main size. For text blocks, for example, this is the width of the widest word.
  //    Calculating the minimum width is expensive, so we forego it and assume a default
  //    minimum main size of 0.
  //  * Min/Max sizes in the main axis are not honored when resolving flexible lengths.
  //  * The spec indicates that the default value for 'flexDirection' is 'row', but
  //    the algorithm below assumes a default of 'column'.
  //
  // Input parameters:
  //    - node: current node to be sized and layed out
  //    - availableWidth & availableHeight: available size to be used for sizing the node
  //      or CSS_UNDEFINED if the size is not available; interpretation depends on layout
  //      flags
  //    - parentDirection: the inline (text) direction within the parent (left-to-right or
  //      right-to-left)
  //    - widthMeasureMode: indicates the sizing rules for the width (see below for explanation)
  //    - heightMeasureMode: indicates the sizing rules for the height (see below for explanation)
  //    - performLayout: specifies whether the caller is interested in just the dimensions
  //      of the node or it requires the entire node and its subtree to be layed out
  //      (with final positions)
  //
  // Details:
  //    This routine is called recursively to lay out subtrees of flexbox elements. It uses the
  //    information in node.style, which is treated as a read-only input. It is responsible for
  //    setting the layout.direction and layout.measured_dimensions fields for the input node as well
  //    as the layout.position and layout.line_index fields for its child nodes. The
  //    layout.measured_dimensions field includes any border or padding for the node but does
  //    not include margins.
  //
  //    The spec describes four different layout modes: "fill available", "max content", "min content",
  //    and "fit content". Of these, we don't use "min content" because we don't support default
  //    minimum main sizes (see above for details). Each of our measure modes maps to a layout mode
  //    from the spec (https://www.w3.org/TR/css3-sizing/#terms):
  //      - CSS_MEASURE_MODE_UNDEFINED: max content
  //      - CSS_MEASURE_MODE_EXACTLY: fill available
  //      - CSS_MEASURE_MODE_AT_MOST: fit content
  //
  //    When calling layoutNodeImpl and layoutNodeInternal, if the caller passes an available size of
  //    undefined then it must also pass a measure mode of CSS_MEASURE_MODE_UNDEFINED in that dimension.
  //
  function layoutNodeImpl(node, availableWidth, availableHeight, /*css_direction_t*/parentDirection, widthMeasureMode, heightMeasureMode, performLayout) {
    assert(isUndefined(availableWidth) ? widthMeasureMode === CSS_MEASURE_MODE_UNDEFINED : true, 'availableWidth is indefinite so widthMeasureMode must be CSS_MEASURE_MODE_UNDEFINED');
    assert(isUndefined(availableHeight) ? heightMeasureMode === CSS_MEASURE_MODE_UNDEFINED : true, 'availableHeight is indefinite so heightMeasureMode must be CSS_MEASURE_MODE_UNDEFINED');

    var/*float*/ paddingAndBorderAxisRow = getPaddingAndBorderAxis(node, CSS_FLEX_DIRECTION_ROW);
    var/*float*/ paddingAndBorderAxisColumn = getPaddingAndBorderAxis(node, CSS_FLEX_DIRECTION_COLUMN);
    var/*float*/ marginAxisRow = getMarginAxis(node, CSS_FLEX_DIRECTION_ROW);
    var/*float*/ marginAxisColumn = getMarginAxis(node, CSS_FLEX_DIRECTION_COLUMN);

    // Set the resolved resolution in the node's layout.
    var/*css_direction_t*/ direction = resolveDirection(node, parentDirection);
    node.layout.direction = direction;

    // For content (text) nodes, determine the dimensions based on the text contents.
    if (isMeasureDefined(node)) {
      var/*float*/ innerWidth = availableWidth - marginAxisRow - paddingAndBorderAxisRow;
      var/*float*/ innerHeight = availableHeight - marginAxisColumn - paddingAndBorderAxisColumn;

      if (widthMeasureMode === CSS_MEASURE_MODE_EXACTLY && heightMeasureMode === CSS_MEASURE_MODE_EXACTLY) {

        // Don't bother sizing the text if both dimensions are already defined.
        node.layout.measuredWidth = boundAxis(node, CSS_FLEX_DIRECTION_ROW, availableWidth - marginAxisRow);
        node.layout.measuredHeight = boundAxis(node, CSS_FLEX_DIRECTION_COLUMN, availableHeight - marginAxisColumn);
      } else if (innerWidth <= 0 || innerHeight <= 0) {

        // Don't bother sizing the text if there's no horizontal or vertical space.
        node.layout.measuredWidth = boundAxis(node, CSS_FLEX_DIRECTION_ROW, 0);
        node.layout.measuredHeight = boundAxis(node, CSS_FLEX_DIRECTION_COLUMN, 0);
      } else {

        // Measure the text under the current constraints.
        var/*css_dim_t*/ measureDim = node.style.measure(
          /*(c)!node->context,*/
          /*(java)!layoutContext.measureOutput,*/
          innerWidth,
          widthMeasureMode,
          innerHeight,
          heightMeasureMode
        );

        node.layout.measuredWidth = boundAxis(node, CSS_FLEX_DIRECTION_ROW,
          (widthMeasureMode === CSS_MEASURE_MODE_UNDEFINED || widthMeasureMode === CSS_MEASURE_MODE_AT_MOST) ?
            measureDim.width + paddingAndBorderAxisRow :
            availableWidth - marginAxisRow);
        node.layout.measuredHeight = boundAxis(node, CSS_FLEX_DIRECTION_COLUMN,
          (heightMeasureMode === CSS_MEASURE_MODE_UNDEFINED || heightMeasureMode === CSS_MEASURE_MODE_AT_MOST) ?
            measureDim.height + paddingAndBorderAxisColumn :
            availableHeight - marginAxisColumn);
      }

      return;
    }

    // For nodes with no children, use the available values if they were provided, or
    // the minimum size as indicated by the padding and border sizes.
    var/*int*/ childCount = node.children.length;
    if (childCount === 0) {
      node.layout.measuredWidth = boundAxis(node, CSS_FLEX_DIRECTION_ROW,
        (widthMeasureMode === CSS_MEASURE_MODE_UNDEFINED || widthMeasureMode === CSS_MEASURE_MODE_AT_MOST) ?
          paddingAndBorderAxisRow :
          availableWidth - marginAxisRow);
      node.layout.measuredHeight = boundAxis(node, CSS_FLEX_DIRECTION_COLUMN,
        (heightMeasureMode === CSS_MEASURE_MODE_UNDEFINED || heightMeasureMode === CSS_MEASURE_MODE_AT_MOST) ?
          paddingAndBorderAxisColumn :
          availableHeight - marginAxisColumn);
      return;
    }

    // If we're not being asked to perform a full layout, we can handle a number of common
    // cases here without incurring the cost of the remaining function.
    if (!performLayout) {
      // If we're being asked to size the content with an at most constraint but there is no available width,
      // the measurement will always be zero.
      if (widthMeasureMode === CSS_MEASURE_MODE_AT_MOST && availableWidth <= 0 &&
          heightMeasureMode === CSS_MEASURE_MODE_AT_MOST && availableHeight <= 0) {
        node.layout.measuredWidth = boundAxis(node, CSS_FLEX_DIRECTION_ROW, 0);
        node.layout.measuredHeight = boundAxis(node, CSS_FLEX_DIRECTION_COLUMN, 0);
        return;
      }

      if (widthMeasureMode === CSS_MEASURE_MODE_AT_MOST && availableWidth <= 0) {
        node.layout.measuredWidth = boundAxis(node, CSS_FLEX_DIRECTION_ROW, 0);
        node.layout.measuredHeight = boundAxis(node, CSS_FLEX_DIRECTION_COLUMN, isUndefined(availableHeight) ? 0 : (availableHeight - marginAxisColumn));
        return;
      }

      if (heightMeasureMode === CSS_MEASURE_MODE_AT_MOST && availableHeight <= 0) {
        node.layout.measuredWidth = boundAxis(node, CSS_FLEX_DIRECTION_ROW, isUndefined(availableWidth) ? 0 : (availableWidth - marginAxisRow));
        node.layout.measuredHeight = boundAxis(node, CSS_FLEX_DIRECTION_COLUMN, 0);
        return;
      }

      // If we're being asked to use an exact width/height, there's no need to measure the children.
      if (widthMeasureMode === CSS_MEASURE_MODE_EXACTLY && heightMeasureMode === CSS_MEASURE_MODE_EXACTLY) {
        node.layout.measuredWidth = boundAxis(node, CSS_FLEX_DIRECTION_ROW, availableWidth - marginAxisRow);
        node.layout.measuredHeight = boundAxis(node, CSS_FLEX_DIRECTION_COLUMN, availableHeight - marginAxisColumn);
        return;
      }
    }

    // STEP 1: CALCULATE VALUES FOR REMAINDER OF ALGORITHM
    var/*(c)!css_flex_direction_t*//*(java)!int*/ mainAxis = resolveAxis(getFlexDirection(node), direction);
    var/*(c)!css_flex_direction_t*//*(java)!int*/ crossAxis = getCrossFlexDirection(mainAxis, direction);
    var/*bool*/ isMainAxisRow = isRowDirection(mainAxis);
    var/*css_justify_t*/ justifyContent = getJustifyContent(node);
    var/*bool*/ isNodeFlexWrap = isFlexWrap(node);

    var/*css_node_t**/ firstAbsoluteChild = undefined;
    var/*css_node_t**/ currentAbsoluteChild = undefined;

    var/*float*/ leadingPaddingAndBorderMain = getLeadingPaddingAndBorder(node, mainAxis);
    var/*float*/ trailingPaddingAndBorderMain = getTrailingPaddingAndBorder(node, mainAxis);
    var/*float*/ leadingPaddingAndBorderCross = getLeadingPaddingAndBorder(node, crossAxis);
    var/*float*/ paddingAndBorderAxisMain = getPaddingAndBorderAxis(node, mainAxis);
    var/*float*/ paddingAndBorderAxisCross = getPaddingAndBorderAxis(node, crossAxis);

    var/*css_measure_mode_t*/ measureModeMainDim = isMainAxisRow ? widthMeasureMode : heightMeasureMode;
    var/*css_measure_mode_t*/ measureModeCrossDim = isMainAxisRow ? heightMeasureMode : widthMeasureMode;

    // STEP 2: DETERMINE AVAILABLE SIZE IN MAIN AND CROSS DIRECTIONS
    var/*float*/ availableInnerWidth = availableWidth - marginAxisRow - paddingAndBorderAxisRow;
    var/*float*/ availableInnerHeight = availableHeight - marginAxisColumn - paddingAndBorderAxisColumn;
    var/*float*/ availableInnerMainDim = isMainAxisRow ? availableInnerWidth : availableInnerHeight;
    var/*float*/ availableInnerCrossDim = isMainAxisRow ? availableInnerHeight : availableInnerWidth;

    // STEP 3: DETERMINE FLEX BASIS FOR EACH ITEM
    var/*css_node_t**/ child;
    var/*int*/ i;
    var/*float*/ childWidth;
    var/*float*/ childHeight;
    var/*css_measure_mode_t*/ childWidthMeasureMode;
    var/*css_measure_mode_t*/ childHeightMeasureMode;
    for (i = 0; i < childCount; i++) {
      child = node.children[i];

      if (performLayout) {
        // Set the initial position (relative to the parent).
        var/*css_direction_t*/ childDirection = resolveDirection(child, direction);
        setPosition(child, childDirection);
      }

      // Absolute-positioned children don't participate in flex layout. Add them
      // to a list that we can process later.
      if (getPositionType(child) === CSS_POSITION_ABSOLUTE) {

        // Store a private linked list of absolutely positioned children
        // so that we can efficiently traverse them later.
        if (firstAbsoluteChild === undefined) {
          firstAbsoluteChild = child;
        }
        if (currentAbsoluteChild !== undefined) {
          currentAbsoluteChild.nextChild = child;
        }
        currentAbsoluteChild = child;
        child.nextChild = undefined;
      } else {

        if (isMainAxisRow && isStyleDimDefined(child, CSS_FLEX_DIRECTION_ROW)) {

          // The width is definite, so use that as the flex basis.
          child.layout.flexBasis = fmaxf(child.style.width, getPaddingAndBorderAxis(child, CSS_FLEX_DIRECTION_ROW));
        } else if (!isMainAxisRow && isStyleDimDefined(child, CSS_FLEX_DIRECTION_COLUMN)) {

          // The height is definite, so use that as the flex basis.
          child.layout.flexBasis = fmaxf(child.style.height, getPaddingAndBorderAxis(child, CSS_FLEX_DIRECTION_COLUMN));
        } else if (!isFlexBasisAuto(child) && !isUndefined(availableInnerMainDim)) {

          // If the basis isn't 'auto', it is assumed to be zero.
          child.layout.flexBasis = fmaxf(0, getPaddingAndBorderAxis(child, mainAxis));
        } else {

          // Compute the flex basis and hypothetical main size (i.e. the clamped flex basis).
          childWidth = CSS_UNDEFINED;
          childHeight = CSS_UNDEFINED;
          childWidthMeasureMode = CSS_MEASURE_MODE_UNDEFINED;
          childHeightMeasureMode = CSS_MEASURE_MODE_UNDEFINED;

          if (isStyleDimDefined(child, CSS_FLEX_DIRECTION_ROW)) {
            childWidth = child.style.width + getMarginAxis(child, CSS_FLEX_DIRECTION_ROW);
            childWidthMeasureMode = CSS_MEASURE_MODE_EXACTLY;
          }
          if (isStyleDimDefined(child, CSS_FLEX_DIRECTION_COLUMN)) {
            childHeight = child.style.height + getMarginAxis(child, CSS_FLEX_DIRECTION_COLUMN);
            childHeightMeasureMode = CSS_MEASURE_MODE_EXACTLY;
          }

          // According to the spec, if the main size is not definite and the
          // child's inline axis is parallel to the main axis (i.e. it's
          // horizontal), the child should be sized using "UNDEFINED" in
          // the main size. Otherwise use "AT_MOST" in the cross axis.
          if (!isMainAxisRow && isUndefined(childWidth) && !isUndefined(availableInnerWidth)) {
            childWidth = availableInnerWidth;
            childWidthMeasureMode = CSS_MEASURE_MODE_AT_MOST;
          }

          // The W3C spec doesn't say anything about the 'overflow' property,
          // but all major browsers appear to implement the following logic.
          if (getOverflow(node) === CSS_OVERFLOW_HIDDEN) {
            if (isMainAxisRow && isUndefined(childHeight) && !isUndefined(availableInnerHeight)) {
              childHeight = availableInnerHeight;
              childHeightMeasureMode = CSS_MEASURE_MODE_AT_MOST;
            }
          }

          // Measure the child
          layoutNodeInternal(child, childWidth, childHeight, direction, childWidthMeasureMode, childHeightMeasureMode, false, 'measure');

          child.layout.flexBasis = fmaxf(isMainAxisRow ? child.layout.measuredWidth : child.layout.measuredHeight, getPaddingAndBorderAxis(child, mainAxis));
        }
      }
    }

    // STEP 4: COLLECT FLEX ITEMS INTO FLEX LINES

    // Indexes of children that represent the first and last items in the line.
    var/*int*/ startOfLineIndex = 0;
    var/*int*/ endOfLineIndex = 0;

    // Number of lines.
    var/*int*/ lineCount = 0;

    // Accumulated cross dimensions of all lines so far.
    var/*float*/ totalLineCrossDim = 0;

    // Max main dimension of all the lines.
    var/*float*/ maxLineMainDim = 0;

    while (endOfLineIndex < childCount) {

      // Number of items on the currently line. May be different than the difference
      // between start and end indicates because we skip over absolute-positioned items.
      var/*int*/ itemsOnLine = 0;

      // sizeConsumedOnCurrentLine is accumulation of the dimensions and margin
      // of all the children on the current line. This will be used in order to
      // either set the dimensions of the node if none already exist or to compute
      // the remaining space left for the flexible children.
      var/*float*/ sizeConsumedOnCurrentLine = 0;

      var/*float*/ totalFlexGrowFactors = 0;
      var/*float*/ totalFlexShrinkScaledFactors = 0;

      i = startOfLineIndex;

      // Maintain a linked list of the child nodes that can shrink and/or grow.
      var/*css_node_t**/ firstRelativeChild = undefined;
      var/*css_node_t**/ currentRelativeChild = undefined;

      // Add items to the current line until it's full or we run out of items.
      while (i < childCount) {
        child = node.children[i];
        child.lineIndex = lineCount;

        if (getPositionType(child) !== CSS_POSITION_ABSOLUTE) {
          var/*float*/ outerFlexBasis = child.layout.flexBasis + getMarginAxis(child, mainAxis);

          // If this is a multi-line flow and this item pushes us over the available size, we've
          // hit the end of the current line. Break out of the loop and lay out the current line.
          if (sizeConsumedOnCurrentLine + outerFlexBasis > availableInnerMainDim && isNodeFlexWrap && itemsOnLine > 0) {
            break;
          }

          sizeConsumedOnCurrentLine += outerFlexBasis;
          itemsOnLine++;

          if (isFlex(child)) {
            totalFlexGrowFactors += getFlexGrowFactor(child);

            // Unlike the grow factor, the shrink factor is scaled relative to the child
            // dimension.
            totalFlexShrinkScaledFactors += getFlexShrinkFactor(child) * child.layout.flexBasis;
          }

          // Store a private linked list of children that need to be layed out.
          if (firstRelativeChild === undefined) {
            firstRelativeChild = child;
          }
          if (currentRelativeChild !== undefined) {
            currentRelativeChild.nextChild = child;
          }
          currentRelativeChild = child;
          child.nextChild = undefined;
        }

        i++;
        endOfLineIndex++;
      }

      // If we don't need to measure the cross axis, we can skip the entire flex step.
      var/*bool*/ canSkipFlex = !performLayout && measureModeCrossDim === CSS_MEASURE_MODE_EXACTLY;

      // In order to position the elements in the main axis, we have two
      // controls. The space between the beginning and the first element
      // and the space between each two elements.
      var/*float*/ leadingMainDim = 0;
      var/*float*/ betweenMainDim = 0;

      // STEP 5: RESOLVING FLEXIBLE LENGTHS ON MAIN AXIS
      // Calculate the remaining available space that needs to be allocated.
      // If the main dimension size isn't known, it is computed based on
      // the line length, so there's no more space left to distribute.
      var/*float*/ remainingFreeSpace = 0;
      if (!isUndefined(availableInnerMainDim)) {
        remainingFreeSpace = availableInnerMainDim - sizeConsumedOnCurrentLine;
      } else if (sizeConsumedOnCurrentLine < 0) {
        // availableInnerMainDim is indefinite which means the node is being sized based on its content.
        // sizeConsumedOnCurrentLine is negative which means the node will allocate 0 pixels for
        // its content. Consequently, remainingFreeSpace is 0 - sizeConsumedOnCurrentLine.
        remainingFreeSpace = -sizeConsumedOnCurrentLine;
      }

      var/*float*/ originalRemainingFreeSpace = remainingFreeSpace;
      var/*float*/ deltaFreeSpace = 0;

      if (!canSkipFlex) {
        var/*float*/ childFlexBasis;
        var/*float*/ flexShrinkScaledFactor;
        var/*float*/ flexGrowFactor;
        var/*float*/ baseMainSize;
        var/*float*/ boundMainSize;

        // Do two passes over the flex items to figure out how to distribute the remaining space.
        // The first pass finds the items whose min/max constraints trigger, freezes them at those
        // sizes, and excludes those sizes from the remaining space. The second pass sets the size
        // of each flexible item. It distributes the remaining space amongst the items whose min/max
        // constraints didn't trigger in pass 1. For the other items, it sets their sizes by forcing
        // their min/max constraints to trigger again.
        //
        // This two pass approach for resolving min/max constraints deviates from the spec. The
        // spec (https://www.w3.org/TR/css-flexbox-1/#resolve-flexible-lengths) describes a process
        // that needs to be repeated a variable number of times. The algorithm implemented here
        // won't handle all cases but it was simpler to implement and it mitigates performance
        // concerns because we know exactly how many passes it'll do.

        // First pass: detect the flex items whose min/max constraints trigger
        var/*float*/ deltaFlexShrinkScaledFactors = 0;
        var/*float*/ deltaFlexGrowFactors = 0;
        currentRelativeChild = firstRelativeChild;
        while (currentRelativeChild !== undefined) {
          childFlexBasis = currentRelativeChild.layout.flexBasis;

          if (remainingFreeSpace < 0) {
            flexShrinkScaledFactor = getFlexShrinkFactor(currentRelativeChild) * childFlexBasis;

            // Is this child able to shrink?
            if (flexShrinkScaledFactor !== 0) {
              baseMainSize = childFlexBasis +
                remainingFreeSpace / totalFlexShrinkScaledFactors * flexShrinkScaledFactor;
              boundMainSize = boundAxis(currentRelativeChild, mainAxis, baseMainSize);
              if (baseMainSize !== boundMainSize) {
                // By excluding this item's size and flex factor from remaining, this item's
                // min/max constraints should also trigger in the second pass resulting in the
                // item's size calculation being identical in the first and second passes.
                deltaFreeSpace -= boundMainSize - childFlexBasis;
                deltaFlexShrinkScaledFactors -= flexShrinkScaledFactor;
              }
            }
          } else if (remainingFreeSpace > 0) {
            flexGrowFactor = getFlexGrowFactor(currentRelativeChild);

            // Is this child able to grow?
            if (flexGrowFactor !== 0) {
              baseMainSize = childFlexBasis +
                remainingFreeSpace / totalFlexGrowFactors * flexGrowFactor;
              boundMainSize = boundAxis(currentRelativeChild, mainAxis, baseMainSize);
              if (baseMainSize !== boundMainSize) {
                // By excluding this item's size and flex factor from remaining, this item's
                // min/max constraints should also trigger in the second pass resulting in the
                // item's size calculation being identical in the first and second passes.
                deltaFreeSpace -= boundMainSize - childFlexBasis;
                deltaFlexGrowFactors -= flexGrowFactor;
              }
            }
          }

          currentRelativeChild = currentRelativeChild.nextChild;
        }

        totalFlexShrinkScaledFactors += deltaFlexShrinkScaledFactors;
        totalFlexGrowFactors += deltaFlexGrowFactors;
        remainingFreeSpace += deltaFreeSpace;

        // Second pass: resolve the sizes of the flexible items
        deltaFreeSpace = 0;
        currentRelativeChild = firstRelativeChild;
        while (currentRelativeChild !== undefined) {
          childFlexBasis = currentRelativeChild.layout.flexBasis;
          var/*float*/ updatedMainSize = childFlexBasis;

          if (remainingFreeSpace < 0) {
            flexShrinkScaledFactor = getFlexShrinkFactor(currentRelativeChild) * childFlexBasis;

            // Is this child able to shrink?
            if (flexShrinkScaledFactor !== 0) {
              updatedMainSize = boundAxis(currentRelativeChild, mainAxis, childFlexBasis +
                remainingFreeSpace / totalFlexShrinkScaledFactors * flexShrinkScaledFactor);
            }
          } else if (remainingFreeSpace > 0) {
            flexGrowFactor = getFlexGrowFactor(currentRelativeChild);

            // Is this child able to grow?
            if (flexGrowFactor !== 0) {
              updatedMainSize = boundAxis(currentRelativeChild, mainAxis, childFlexBasis +
                remainingFreeSpace / totalFlexGrowFactors * flexGrowFactor);
            }
          }

          deltaFreeSpace -= updatedMainSize - childFlexBasis;

          if (isMainAxisRow) {
            childWidth = updatedMainSize + getMarginAxis(currentRelativeChild, CSS_FLEX_DIRECTION_ROW);
            childWidthMeasureMode = CSS_MEASURE_MODE_EXACTLY;

            if (!isStyleDimDefined(currentRelativeChild, CSS_FLEX_DIRECTION_COLUMN)) {
              childHeight = availableInnerCrossDim;
              childHeightMeasureMode = isUndefined(childHeight) ? CSS_MEASURE_MODE_UNDEFINED : CSS_MEASURE_MODE_AT_MOST;
            } else {
              childHeight = currentRelativeChild.style.height + getMarginAxis(currentRelativeChild, CSS_FLEX_DIRECTION_COLUMN);
              childHeightMeasureMode = CSS_MEASURE_MODE_EXACTLY;
            }
          } else {
            childHeight = updatedMainSize + getMarginAxis(currentRelativeChild, CSS_FLEX_DIRECTION_COLUMN);
            childHeightMeasureMode = CSS_MEASURE_MODE_EXACTLY;

            if (!isStyleDimDefined(currentRelativeChild, CSS_FLEX_DIRECTION_ROW)) {
              childWidth = availableInnerCrossDim;
              childWidthMeasureMode = isUndefined(childWidth) ? CSS_MEASURE_MODE_UNDEFINED : CSS_MEASURE_MODE_AT_MOST;
            } else {
              childWidth = currentRelativeChild.style.width + getMarginAxis(currentRelativeChild, CSS_FLEX_DIRECTION_ROW);
              childWidthMeasureMode = CSS_MEASURE_MODE_EXACTLY;
            }
          }

          var/*bool*/ requiresStretchLayout = !isStyleDimDefined(currentRelativeChild, crossAxis) &&
            getAlignItem(node, currentRelativeChild) === CSS_ALIGN_STRETCH;

          // Recursively call the layout algorithm for this child with the updated main size.
          layoutNodeInternal(currentRelativeChild, childWidth, childHeight, direction, childWidthMeasureMode, childHeightMeasureMode, performLayout && !requiresStretchLayout, 'flex');

          currentRelativeChild = currentRelativeChild.nextChild;
        }
      }

      remainingFreeSpace = originalRemainingFreeSpace + deltaFreeSpace;

      // STEP 6: MAIN-AXIS JUSTIFICATION & CROSS-AXIS SIZE DETERMINATION

      // At this point, all the children have their dimensions set in the main axis.
      // Their dimensions are also set in the cross axis with the exception of items
      // that are aligned 'stretch'. We need to compute these stretch values and
      // set the final positions.

      // If we are using "at most" rules in the main axis, we won't distribute
      // any remaining space at this point.
      if (measureModeMainDim === CSS_MEASURE_MODE_AT_MOST) {
        remainingFreeSpace = 0;
      }

      // Use justifyContent to figure out how to allocate the remaining space
      // available in the main axis.
      if (justifyContent !== CSS_JUSTIFY_FLEX_START) {
        if (justifyContent === CSS_JUSTIFY_CENTER) {
          leadingMainDim = remainingFreeSpace / 2;
        } else if (justifyContent === CSS_JUSTIFY_FLEX_END) {
          leadingMainDim = remainingFreeSpace;
        } else if (justifyContent === CSS_JUSTIFY_SPACE_BETWEEN) {
          remainingFreeSpace = fmaxf(remainingFreeSpace, 0);
          if (itemsOnLine > 1) {
            betweenMainDim = remainingFreeSpace / (itemsOnLine - 1);
          } else {
            betweenMainDim = 0;
          }
        } else if (justifyContent === CSS_JUSTIFY_SPACE_AROUND) {
          // Space on the edges is half of the space between elements
          betweenMainDim = remainingFreeSpace / itemsOnLine;
          leadingMainDim = betweenMainDim / 2;
        }
      }

      var/*float*/ mainDim = leadingPaddingAndBorderMain + leadingMainDim;
      var/*float*/ crossDim = 0;

      for (i = startOfLineIndex; i < endOfLineIndex; ++i) {
        child = node.children[i];

        if (getPositionType(child) === CSS_POSITION_ABSOLUTE &&
            isPosDefined(child, leading[mainAxis])) {
          if (performLayout) {
            // In case the child is position absolute and has left/top being
            // defined, we override the position to whatever the user said
            // (and margin/border).
            child.layout[pos[mainAxis]] = getPosition(child, leading[mainAxis]) +
              getLeadingBorder(node, mainAxis) +
              getLeadingMargin(child, mainAxis);
          }
        } else {
          if (performLayout) {
            // If the child is position absolute (without top/left) or relative,
            // we put it at the current accumulated offset.
            child.layout[pos[mainAxis]] += mainDim;
          }

          // Now that we placed the element, we need to update the variables.
          // We need to do that only for relative elements. Absolute elements
          // do not take part in that phase.
          if (getPositionType(child) === CSS_POSITION_RELATIVE) {
            if (canSkipFlex) {
              // If we skipped the flex step, then we can't rely on the measuredDims because
              // they weren't computed. This means we can't call getDimWithMargin.
              mainDim += betweenMainDim + getMarginAxis(child, mainAxis) + child.layout.flexBasis;
              crossDim = availableInnerCrossDim;
            } else {
              // The main dimension is the sum of all the elements dimension plus
              // the spacing.
              mainDim += betweenMainDim + getDimWithMargin(child, mainAxis);

              // The cross dimension is the max of the elements dimension since there
              // can only be one element in that cross dimension.
              crossDim = fmaxf(crossDim, getDimWithMargin(child, crossAxis));
            }
          }
        }
      }

      mainDim += trailingPaddingAndBorderMain;

      var/*float*/ containerCrossAxis = availableInnerCrossDim;
      if (measureModeCrossDim === CSS_MEASURE_MODE_UNDEFINED || measureModeCrossDim === CSS_MEASURE_MODE_AT_MOST) {
        // Compute the cross axis from the max cross dimension of the children.
        containerCrossAxis = boundAxis(node, crossAxis, crossDim + paddingAndBorderAxisCross) - paddingAndBorderAxisCross;

        if (measureModeCrossDim === CSS_MEASURE_MODE_AT_MOST) {
          containerCrossAxis = fminf(containerCrossAxis, availableInnerCrossDim);
        }
      }

      // If there's no flex wrap, the cross dimension is defined by the container.
      if (!isNodeFlexWrap && measureModeCrossDim === CSS_MEASURE_MODE_EXACTLY) {
        crossDim = availableInnerCrossDim;
      }

      // Clamp to the min/max size specified on the container.
      crossDim = boundAxis(node, crossAxis, crossDim + paddingAndBorderAxisCross) - paddingAndBorderAxisCross;

      // STEP 7: CROSS-AXIS ALIGNMENT
      // We can skip child alignment if we're just measuring the container.
      if (performLayout) {
        for (i = startOfLineIndex; i < endOfLineIndex; ++i) {
          child = node.children[i];

          if (getPositionType(child) === CSS_POSITION_ABSOLUTE) {
            // If the child is absolutely positioned and has a top/left/bottom/right
            // set, override all the previously computed positions to set it correctly.
            if (isPosDefined(child, leading[crossAxis])) {
              child.layout[pos[crossAxis]] = getPosition(child, leading[crossAxis]) +
                getLeadingBorder(node, crossAxis) +
                getLeadingMargin(child, crossAxis);
            } else {
              child.layout[pos[crossAxis]] = leadingPaddingAndBorderCross +
                getLeadingMargin(child, crossAxis);
            }
          } else {
            var/*float*/ leadingCrossDim = leadingPaddingAndBorderCross;

            // For a relative children, we're either using alignItems (parent) or
            // alignSelf (child) in order to determine the position in the cross axis
            var/*css_align_t*/ alignItem = getAlignItem(node, child);

            // If the child uses align stretch, we need to lay it out one more time, this time
            // forcing the cross-axis size to be the computed cross size for the current line.
            if (alignItem === CSS_ALIGN_STRETCH) {
              childWidth = child.layout.measuredWidth + getMarginAxis(child, CSS_FLEX_DIRECTION_ROW);
              childHeight = child.layout.measuredHeight + getMarginAxis(child, CSS_FLEX_DIRECTION_COLUMN);
              var/*bool*/ isCrossSizeDefinite = false;

              if (isMainAxisRow) {
                isCrossSizeDefinite = isStyleDimDefined(child, CSS_FLEX_DIRECTION_COLUMN);
                childHeight = crossDim;
              } else {
                isCrossSizeDefinite = isStyleDimDefined(child, CSS_FLEX_DIRECTION_ROW);
                childWidth = crossDim;
              }

              // If the child defines a definite size for its cross axis, there's no need to stretch.
              if (!isCrossSizeDefinite) {
                childWidthMeasureMode = isUndefined(childWidth) ? CSS_MEASURE_MODE_UNDEFINED : CSS_MEASURE_MODE_EXACTLY;
                childHeightMeasureMode = isUndefined(childHeight) ? CSS_MEASURE_MODE_UNDEFINED : CSS_MEASURE_MODE_EXACTLY;
                layoutNodeInternal(child, childWidth, childHeight, direction, childWidthMeasureMode, childHeightMeasureMode, true, 'stretch');
              }
            } else if (alignItem !== CSS_ALIGN_FLEX_START) {
              var/*float*/ remainingCrossDim = containerCrossAxis - getDimWithMargin(child, crossAxis);

              if (alignItem === CSS_ALIGN_CENTER) {
                leadingCrossDim += remainingCrossDim / 2;
              } else { // CSS_ALIGN_FLEX_END
                leadingCrossDim += remainingCrossDim;
              }
            }

            // And we apply the position
            child.layout[pos[crossAxis]] += totalLineCrossDim + leadingCrossDim;
          }
        }
      }

      totalLineCrossDim += crossDim;
      maxLineMainDim = fmaxf(maxLineMainDim, mainDim);

      // Reset variables for new line.
      lineCount++;
      startOfLineIndex = endOfLineIndex;
      endOfLineIndex = startOfLineIndex;
    }

    // STEP 8: MULTI-LINE CONTENT ALIGNMENT
    if (lineCount > 1 && performLayout && !isUndefined(availableInnerCrossDim)) {
      var/*float*/ remainingAlignContentDim = availableInnerCrossDim - totalLineCrossDim;

      var/*float*/ crossDimLead = 0;
      var/*float*/ currentLead = leadingPaddingAndBorderCross;

      var/*css_align_t*/ alignContent = getAlignContent(node);
      if (alignContent === CSS_ALIGN_FLEX_END) {
        currentLead += remainingAlignContentDim;
      } else if (alignContent === CSS_ALIGN_CENTER) {
        currentLead += remainingAlignContentDim / 2;
      } else if (alignContent === CSS_ALIGN_STRETCH) {
        if (availableInnerCrossDim > totalLineCrossDim) {
          crossDimLead = (remainingAlignContentDim / lineCount);
        }
      }

      var/*int*/ endIndex = 0;
      for (i = 0; i < lineCount; ++i) {
        var/*int*/ startIndex = endIndex;
        var/*int*/ j;

        // compute the line's height and find the endIndex
        var/*float*/ lineHeight = 0;
        for (j = startIndex; j < childCount; ++j) {
          child = node.children[j];
          if (getPositionType(child) !== CSS_POSITION_RELATIVE) {
            continue;
          }
          if (child.lineIndex !== i) {
            break;
          }
          if (isLayoutDimDefined(child, crossAxis)) {
            lineHeight = fmaxf(lineHeight,
              child.layout[measuredDim[crossAxis]] + getMarginAxis(child, crossAxis));
          }
        }
        endIndex = j;
        lineHeight += crossDimLead;

        if (performLayout) {
          for (j = startIndex; j < endIndex; ++j) {
            child = node.children[j];
            if (getPositionType(child) !== CSS_POSITION_RELATIVE) {
              continue;
            }

            var/*css_align_t*/ alignContentAlignItem = getAlignItem(node, child);
            if (alignContentAlignItem === CSS_ALIGN_FLEX_START) {
              child.layout[pos[crossAxis]] = currentLead + getLeadingMargin(child, crossAxis);
            } else if (alignContentAlignItem === CSS_ALIGN_FLEX_END) {
              child.layout[pos[crossAxis]] = currentLead + lineHeight - getTrailingMargin(child, crossAxis) - child.layout[measuredDim[crossAxis]];
            } else if (alignContentAlignItem === CSS_ALIGN_CENTER) {
              childHeight = child.layout[measuredDim[crossAxis]];
              child.layout[pos[crossAxis]] = currentLead + (lineHeight - childHeight) / 2;
            } else if (alignContentAlignItem === CSS_ALIGN_STRETCH) {
              child.layout[pos[crossAxis]] = currentLead + getLeadingMargin(child, crossAxis);
              // TODO(prenaux): Correctly set the height of items with indefinite
              //                (auto) crossAxis dimension.
            }
          }
        }

        currentLead += lineHeight;
      }
    }

    // STEP 9: COMPUTING FINAL DIMENSIONS
    node.layout.measuredWidth = boundAxis(node, CSS_FLEX_DIRECTION_ROW, availableWidth - marginAxisRow);
    node.layout.measuredHeight = boundAxis(node, CSS_FLEX_DIRECTION_COLUMN, availableHeight - marginAxisColumn);

    // If the user didn't specify a width or height for the node, set the
    // dimensions based on the children.
    if (measureModeMainDim === CSS_MEASURE_MODE_UNDEFINED) {
      // Clamp the size to the min/max size, if specified, and make sure it
      // doesn't go below the padding and border amount.
      node.layout[measuredDim[mainAxis]] = boundAxis(node, mainAxis, maxLineMainDim);
    } else if (measureModeMainDim === CSS_MEASURE_MODE_AT_MOST) {
      node.layout[measuredDim[mainAxis]] = fmaxf(
        fminf(availableInnerMainDim + paddingAndBorderAxisMain,
          boundAxisWithinMinAndMax(node, mainAxis, maxLineMainDim)),
        paddingAndBorderAxisMain);
    }

    if (measureModeCrossDim === CSS_MEASURE_MODE_UNDEFINED) {
      // Clamp the size to the min/max size, if specified, and make sure it
      // doesn't go below the padding and border amount.
      node.layout[measuredDim[crossAxis]] = boundAxis(node, crossAxis, totalLineCrossDim + paddingAndBorderAxisCross);
    } else if (measureModeCrossDim === CSS_MEASURE_MODE_AT_MOST) {
      node.layout[measuredDim[crossAxis]] = fmaxf(
        fminf(availableInnerCrossDim + paddingAndBorderAxisCross,
          boundAxisWithinMinAndMax(node, crossAxis, totalLineCrossDim + paddingAndBorderAxisCross)),
        paddingAndBorderAxisCross);
    }

    // STEP 10: SETTING TRAILING POSITIONS FOR CHILDREN
    if (performLayout) {
      var/*bool*/ needsMainTrailingPos = false;
      var/*bool*/ needsCrossTrailingPos = false;

      if (mainAxis === CSS_FLEX_DIRECTION_ROW_REVERSE ||
          mainAxis === CSS_FLEX_DIRECTION_COLUMN_REVERSE) {
        needsMainTrailingPos = true;
      }

      if (crossAxis === CSS_FLEX_DIRECTION_ROW_REVERSE ||
          crossAxis === CSS_FLEX_DIRECTION_COLUMN_REVERSE) {
        needsCrossTrailingPos = true;
      }

      // Set trailing position if necessary.
      if (needsMainTrailingPos || needsCrossTrailingPos) {
        for (i = 0; i < childCount; ++i) {
          child = node.children[i];

          if (needsMainTrailingPos) {
            setTrailingPosition(node, child, mainAxis);
          }

          if (needsCrossTrailingPos) {
            setTrailingPosition(node, child, crossAxis);
          }
        }
      }
    }

    // STEP 11: SIZING AND POSITIONING ABSOLUTE CHILDREN
    currentAbsoluteChild = firstAbsoluteChild;
    while (currentAbsoluteChild !== undefined) {
      // Now that we know the bounds of the container, perform layout again on the
      // absolutely-positioned children.
      if (performLayout) {

        childWidth = CSS_UNDEFINED;
        childHeight = CSS_UNDEFINED;

        if (isStyleDimDefined(currentAbsoluteChild, CSS_FLEX_DIRECTION_ROW)) {
          childWidth = currentAbsoluteChild.style.width + getMarginAxis(currentAbsoluteChild, CSS_FLEX_DIRECTION_ROW);
        } else {
          // If the child doesn't have a specified width, compute the width based on the left/right offsets if they're defined.
          if (isPosDefined(currentAbsoluteChild, CSS_LEFT) && isPosDefined(currentAbsoluteChild, CSS_RIGHT)) {
            childWidth = node.layout.measuredWidth -
              (getLeadingBorder(node, CSS_FLEX_DIRECTION_ROW) + getTrailingBorder(node, CSS_FLEX_DIRECTION_ROW)) -
              (currentAbsoluteChild.style[CSS_LEFT] + currentAbsoluteChild.style[CSS_RIGHT]);
            childWidth = boundAxis(currentAbsoluteChild, CSS_FLEX_DIRECTION_ROW, childWidth);
          }
        }

        if (isStyleDimDefined(currentAbsoluteChild, CSS_FLEX_DIRECTION_COLUMN)) {
          childHeight = currentAbsoluteChild.style.height + getMarginAxis(currentAbsoluteChild, CSS_FLEX_DIRECTION_COLUMN);
        } else {
          // If the child doesn't have a specified height, compute the height based on the top/bottom offsets if they're defined.
          if (isPosDefined(currentAbsoluteChild, CSS_TOP) && isPosDefined(currentAbsoluteChild, CSS_BOTTOM)) {
            childHeight = node.layout.measuredHeight -
              (getLeadingBorder(node, CSS_FLEX_DIRECTION_COLUMN) + getTrailingBorder(node, CSS_FLEX_DIRECTION_COLUMN)) -
              (currentAbsoluteChild.style[CSS_TOP] + currentAbsoluteChild.style[CSS_BOTTOM]);
            childHeight = boundAxis(currentAbsoluteChild, CSS_FLEX_DIRECTION_COLUMN, childHeight);
          }
        }

        // If we're still missing one or the other dimension, measure the content.
        if (isUndefined(childWidth) || isUndefined(childHeight)) {
          childWidthMeasureMode = isUndefined(childWidth) ? CSS_MEASURE_MODE_UNDEFINED : CSS_MEASURE_MODE_EXACTLY;
          childHeightMeasureMode = isUndefined(childHeight) ? CSS_MEASURE_MODE_UNDEFINED : CSS_MEASURE_MODE_EXACTLY;

          // According to the spec, if the main size is not definite and the
          // child's inline axis is parallel to the main axis (i.e. it's
          // horizontal), the child should be sized using "UNDEFINED" in
          // the main size. Otherwise use "AT_MOST" in the cross axis.
          if (!isMainAxisRow && isUndefined(childWidth) && !isUndefined(availableInnerWidth)) {
            childWidth = availableInnerWidth;
            childWidthMeasureMode = CSS_MEASURE_MODE_AT_MOST;
          }

          // The W3C spec doesn't say anything about the 'overflow' property,
          // but all major browsers appear to implement the following logic.
          if (getOverflow(node) === CSS_OVERFLOW_HIDDEN) {
            if (isMainAxisRow && isUndefined(childHeight) && !isUndefined(availableInnerHeight)) {
              childHeight = availableInnerHeight;
              childHeightMeasureMode = CSS_MEASURE_MODE_AT_MOST;
            }
          }

          layoutNodeInternal(currentAbsoluteChild, childWidth, childHeight, direction, childWidthMeasureMode, childHeightMeasureMode, false, 'abs-measure');
          childWidth = currentAbsoluteChild.layout.measuredWidth + getMarginAxis(currentAbsoluteChild, CSS_FLEX_DIRECTION_ROW);
          childHeight = currentAbsoluteChild.layout.measuredHeight + getMarginAxis(currentAbsoluteChild, CSS_FLEX_DIRECTION_COLUMN);
        }

        layoutNodeInternal(currentAbsoluteChild, childWidth, childHeight, direction, CSS_MEASURE_MODE_EXACTLY, CSS_MEASURE_MODE_EXACTLY, true, 'abs-layout');

        if (isPosDefined(currentAbsoluteChild, trailing[CSS_FLEX_DIRECTION_ROW]) &&
            !isPosDefined(currentAbsoluteChild, leading[CSS_FLEX_DIRECTION_ROW])) {
          currentAbsoluteChild.layout[leading[CSS_FLEX_DIRECTION_ROW]] =
            node.layout[measuredDim[CSS_FLEX_DIRECTION_ROW]] -
            currentAbsoluteChild.layout[measuredDim[CSS_FLEX_DIRECTION_ROW]] -
            getPosition(currentAbsoluteChild, trailing[CSS_FLEX_DIRECTION_ROW]);
        }

        if (isPosDefined(currentAbsoluteChild, trailing[CSS_FLEX_DIRECTION_COLUMN]) &&
            !isPosDefined(currentAbsoluteChild, leading[CSS_FLEX_DIRECTION_COLUMN])) {
          currentAbsoluteChild.layout[leading[CSS_FLEX_DIRECTION_COLUMN]] =
            node.layout[measuredDim[CSS_FLEX_DIRECTION_COLUMN]] -
            currentAbsoluteChild.layout[measuredDim[CSS_FLEX_DIRECTION_COLUMN]] -
            getPosition(currentAbsoluteChild, trailing[CSS_FLEX_DIRECTION_COLUMN]);
        }
      }

      currentAbsoluteChild = currentAbsoluteChild.nextChild;
    }
  }

  function canUseCachedMeasurement(availableWidth, availableHeight,
    marginRow, marginColumn,
    widthMeasureMode, heightMeasureMode,
    cachedLayout) {

    // Is it an exact match?
    if (cachedLayout.availableWidth === availableWidth &&
        cachedLayout.availableHeight === availableHeight &&
        cachedLayout.widthMeasureMode === widthMeasureMode &&
        cachedLayout.heightMeasureMode === heightMeasureMode) {
      return true;
    }

    // If the width is an exact match, try a fuzzy match on the height.
    if (cachedLayout.availableWidth === availableWidth &&
        cachedLayout.widthMeasureMode === widthMeasureMode &&
        heightMeasureMode === CSS_MEASURE_MODE_EXACTLY &&
        availableHeight - marginColumn === cachedLayout.computedHeight) {
      return true;
    }

    // If the height is an exact match, try a fuzzy match on the width.
    if (cachedLayout.availableHeight === availableHeight &&
        cachedLayout.heightMeasureMode === heightMeasureMode &&
        widthMeasureMode === CSS_MEASURE_MODE_EXACTLY &&
        availableWidth - marginRow === cachedLayout.computedWidth) {
      return true;
    }

    return false;
  }

  //
  // This is a wrapper around the layoutNodeImpl function. It determines
  // whether the layout request is redundant and can be skipped.
  //
  // Parameters:
  //  Input parameters are the same as layoutNodeImpl (see above)
  //  Return parameter is true if layout was performed, false if skipped
  //
  function layoutNodeInternal(node, availableWidth, availableHeight, parentDirection,
      widthMeasureMode, heightMeasureMode, performLayout, reason) {
    var layout = node.layout;

    var needToVisitNode = (node.isDirty && layout.generationCount !== gCurrentGenerationCount) ||
      layout.lastParentDirection !== parentDirection;

    if (needToVisitNode) {
      // Invalidate the cached results.
      if (layout.cachedMeasurements !== undefined) {
        layout.cachedMeasurements = [];
      }
      if (layout.cachedLayout !== undefined) {
        layout.cachedLayout.widthMeasureMode = undefined;
        layout.cachedLayout.heightMeasureMode = undefined;
      }
    }

    var i;
    var len;
    var cachedResults;

    // Determine whether the results are already cached. We maintain a separate
    // cache for layouts and measurements. A layout operation modifies the positions
    // and dimensions for nodes in the subtree. The algorithm assumes that each node
    // gets layed out a maximum of one time per tree layout, but multiple measurements
    // may be required to resolve all of the flex dimensions.
    // We handle nodes with measure functions specially here because they are the most
    // expensive to measure, so it's worth avoiding redundant measurements if at all possible.
    if (isMeasureDefined(node)) {
      var marginAxisRow = getMarginAxis(node, CSS_FLEX_DIRECTION_ROW);
      var marginAxisColumn = getMarginAxis(node, CSS_FLEX_DIRECTION_COLUMN);

      // First, try to use the layout cache.
      if (layout.cachedLayout &&
          canUseCachedMeasurement(availableWidth, availableHeight, marginAxisRow, marginAxisColumn,
            widthMeasureMode, heightMeasureMode, layout.cachedLayout)) {
        cachedResults = layout.cachedLayout;
      } else if (layout.cachedMeasurements) {
        // Try to use the measurement cache.
        for (i = 0, len = layout.cachedMeasurements.length; i < len; i++) {
          if (canUseCachedMeasurement(availableWidth, availableHeight, marginAxisRow, marginAxisColumn,
              widthMeasureMode, heightMeasureMode, layout.cachedMeasurements[i])) {
            cachedResults = layout.cachedMeasurements[i];
            break;
          }
        }
      }
    } else if (performLayout) {
      if (layout.cachedLayout &&
          layout.cachedLayout.availableWidth === availableWidth &&
          layout.cachedLayout.availableHeight === availableHeight &&
          layout.cachedLayout.widthMeasureMode === widthMeasureMode &&
          layout.cachedLayout.heightMeasureMode === heightMeasureMode) {
        cachedResults = layout.cachedLayout;
      }
    } else if (layout.cachedMeasurements) {
      for (i = 0, len = layout.cachedMeasurements.length; i < len; i++) {
        if (layout.cachedMeasurements[i].availableWidth === availableWidth &&
            layout.cachedMeasurements[i].availableHeight === availableHeight &&
            layout.cachedMeasurements[i].widthMeasureMode === widthMeasureMode &&
            layout.cachedMeasurements[i].heightMeasureMode === heightMeasureMode) {
          cachedResults = layout.cachedMeasurements[i];
          break;
        }
      }
    }

    if (!needToVisitNode && cachedResults !== undefined) {
      layout.measureWidth = cachedResults.computedWidth;
      layout.measureHeight = cachedResults.computedHeight;
    } else {
      layoutNodeImpl(node, availableWidth, availableHeight, parentDirection, widthMeasureMode, heightMeasureMode, performLayout);
      layout.lastParentDirection = parentDirection;

      if (cachedResults === undefined) {
        var newCacheEntry;
        if (performLayout) {
          // Use the single layout cache entry.
          if (layout.cachedLayout === undefined) {
            layout.cachedLayout = {};
          }
          newCacheEntry = layout.cachedLayout;
        } else {
          // Allocate a new measurement cache entry.
          if (layout.cachedMeasurements === undefined) {
            layout.cachedMeasurements = [];
          }
          newCacheEntry = {};
          layout.cachedMeasurements.push(newCacheEntry);
        }

        newCacheEntry.availableWidth = availableWidth;
        newCacheEntry.availableHeight = availableHeight;
        newCacheEntry.widthMeasureMode = widthMeasureMode;
        newCacheEntry.heightMeasureMode = heightMeasureMode;
        newCacheEntry.computedWidth = layout.measuredWidth;
        newCacheEntry.computedHeight = layout.measuredHeight;
      }
    }

    if (performLayout) {
      node.layout.width = node.layout.measuredWidth;
      node.layout.height = node.layout.measuredHeight;
      layout.shouldUpdate = true;
    }

    layout.generationCount = gCurrentGenerationCount;
    return (needToVisitNode || cachedResults === undefined);
  }

  function layoutNode(node, availableWidth, availableHeight, parentDirection) {
    // Increment the generation count. This will force the recursive routine to visit
    // all dirty nodes at least once. Subsequent visits will be skipped if the input
    // parameters don't change.
    gCurrentGenerationCount++;

    // If the caller didn't specify a height/width, use the dimensions
    // specified in the style.
    if (isUndefined(availableWidth) && isStyleDimDefined(node, CSS_FLEX_DIRECTION_ROW)) {
      availableWidth = node.style.width + getMarginAxis(node, CSS_FLEX_DIRECTION_ROW);
    }
    if (isUndefined(availableHeight) && isStyleDimDefined(node, CSS_FLEX_DIRECTION_COLUMN)) {
      availableHeight = node.style.height + getMarginAxis(node, CSS_FLEX_DIRECTION_COLUMN);
    }

    var widthMeasureMode = isUndefined(availableWidth) ? CSS_MEASURE_MODE_UNDEFINED : CSS_MEASURE_MODE_EXACTLY;
    var heightMeasureMode = isUndefined(availableHeight) ? CSS_MEASURE_MODE_UNDEFINED : CSS_MEASURE_MODE_EXACTLY;

    if (layoutNodeInternal(node, availableWidth, availableHeight, parentDirection, widthMeasureMode, heightMeasureMode, true, 'initial')) {
      setPosition(node, node.layout.direction);
    }
  }

  return {
    layoutNodeImpl: layoutNodeImpl,
    computeLayout: layoutNode,
    fillNodes: fillNodes,
    canUseCachedMeasurement: canUseCachedMeasurement
  };
})();

// This module export is only used for the purposes of unit testing this file. When
// the library is packaged this file is included within css-layout.js which forms
// the public API.
if (typeof exports === 'object') {
  module.exports = computeLayout;
}
