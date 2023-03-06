/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include <sstream>

#include "./Node.hh"
#include "./Layout.hh"
#include "./Size.hh"
#include "./Value.hh"
#include "./Config.hh"
#include "./CallbackTrampolines.hh"


#include <yoga/Yoga.h>
#include <pybind11/pybind11.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;


PYBIND11_MODULE(yoga, m) {
  py::class_<MeasureCallback, PyMeasureCallback>(m, "MeasureCallback")
      .def(py::init<>())
      .def("measure", &MeasureCallback::measure);
  py::class_<DirtiedCallback, PyDirtiedCallback>(m, "DirtiedCallback")
      .def(py::init<>())
      .def("dirtied", &DirtiedCallback::dirtied);

  py::class_<Config, std::shared_ptr<Config>>(m, "Config")
      .def(py::init<>())
      .def(
          "set_experimental_feature_enabled",
          &Config::setExperimentalFeatureEnabled)
      .def("set_point_scale_factor", &Config::setPointScaleFactor)
      .def(
          "set_use_legacy_stretch_behaviour", &Config::setUseLegacyStretchBehaviour)
      .def("set_use_web_defaults", &Config::setUseWebDefaults)
      .def(
          "is_experimental_feature_enabled", &Config::isExperimentalFeatureEnabled)
      .def("use_legacy_stretch_behaviour", &Config::useLegacyStretchBehaviour)
      .def("use_web_defaults", &Config::useWebDefaults);

  py::class_<Layout>(m, "Layout")
      .def(py::init<>())
      .def_readwrite("left", &Layout::left)
      .def_readwrite("right", &Layout::right)
      .def_readwrite("top", &Layout::top)
      .def_readwrite("bottom", &Layout::bottom)
      .def_readwrite("width", &Layout::width)
      .def_readwrite("height", &Layout::height)
      .def("__repr__",
        [](const Layout &a) {
            std::stringstream rep;
            rep << "Layout(";
            rep << "left=" << a.left;
            rep << ", right=" << a.right;
            rep << ", top=" << a.top;
            rep << ", bottom=" << a.bottom;
            rep << ", width=" << a.width;
            rep << ", height=" << a.height;
            rep << ")";
            return rep.str();
        }
      );

  py::class_<Size>(m, "Size")
      .def(
        py::init<double, double>(),
        py::arg("width") = 0.0,
        py::arg("height") = 0.0)
      .def_readwrite("width", &Size::width)
      .def_readwrite("height", &Size::height)
      .def("__repr__",
        [](const Size &a) {
            std::stringstream rep;
            rep << "Size(";
            rep << "width=" << a.width;
            rep << ", height=" << a.height;
            rep << ")";
            return rep.str();
        }
      );

  py::class_<Value>(m, "Value")
      .def(
        py::init<int, double>(),
        py::arg("unit") = static_cast<int>(YGUnitUndefined),
        py::arg("value") = 0.0)
      .def_readwrite("value", &Value::value)
      .def_readwrite("unit", &Value::unit)
      .def("__repr__",
        [](const Value &a) {
            std::stringstream rep;
            rep << "Value(";
            rep << "value=" << a.value;
            rep << ", unit=" << a.unit;
            rep << ")";
            return rep.str();
        }
      );

  py::class_<Node, std::shared_ptr<Node>>(m, "Node")
      .def(
        py::init<Config*>(),
        py::arg("config") = static_cast<Config*>(nullptr),
        py::keep_alive<1,2>())

      .def("reset", &Node::reset)

      .def("copy_style", &Node::copyStyle)

      .def("set_position_type", &Node::setPositionType)
      .def("set_position", &Node::setPosition)
      .def("set_position_percent", &Node::setPositionPercent)

      .def("set_align_content", &Node::setAlignContent)
      .def("set_align_items", &Node::setAlignItems)
      .def("set_align_self", &Node::setAlignSelf)
      .def("set_flex_direction", &Node::setFlexDirection)
      .def("set_flex_wrap", &Node::setFlexWrap)
      .def("set_justify_content", &Node::setJustifyContent)

      .def("set_margin", &Node::setMargin)
      .def("set_margin_percent", &Node::setMarginPercent)
      .def("set_margin_auto", &Node::setMarginAuto)

      .def("set_overflow", &Node::setOverflow)
      .def("set_display", &Node::setDisplay)

      .def("set_flex", &Node::setFlex)
      .def("set_flex_basis", &Node::setFlexBasis)
      .def("set_flex_basis_percent", &Node::setFlexBasisPercent)
      .def("set_flex_basis_auto", &Node::setFlexBasisAuto)
      .def("set_flex_grow", &Node::setFlexGrow)
      .def("set_flex_shrink", &Node::setFlexShrink)

      .def("set_width", &Node::setWidth)
      .def("set_width_percent", &Node::setWidthPercent)
      .def("set_width_auto", &Node::setWidthAuto)
      .def("set_height", &Node::setHeight)
      .def("set_height_percent", &Node::setHeightPercent)
      .def("set_height_auto", &Node::setHeightAuto)

      .def("set_min_width", &Node::setMinWidth)
      .def("set_min_width_percent", &Node::setMinWidthPercent)
      .def("set_min_height", &Node::setMinHeight)
      .def("set_min_height_percent", &Node::setMinHeightPercent)

      .def("set_max_width", &Node::setMaxWidth)
      .def("set_max_width_percent", &Node::setMaxWidthPercent)
      .def("set_max_height", &Node::setMaxHeight)
      .def("set_max_height_percent", &Node::setMaxHeightPercent)

      .def("set_aspect_ratio", &Node::setAspectRatio)

      .def("set_border", &Node::setBorder)

      .def("set_padding", &Node::setPadding)
      .def("set_padding_percent", &Node::setPaddingPercent)
      .def("set_gap", &Node::setGap)

      .def("get_position_type", &Node::getPositionType)
      .def("get_position", &Node::getPosition)

      .def("get_align_content", &Node::getAlignContent)
      .def("get_align_items", &Node::getAlignItems)
      .def("get_align_self", &Node::getAlignSelf)
      .def("get_flex_direction", &Node::getFlexDirection)
      .def("get_flex_wrap", &Node::getFlexWrap)
      .def("get_justify_content", &Node::getJustifyContent)

      .def("get_margin", &Node::getMargin)

      .def("get_flex_basis", &Node::getFlexBasis)
      .def("get_flex_grow", &Node::getFlexGrow)
      .def("get_flex_shrink", &Node::getFlexShrink)

      .def("get_width", &Node::getWidth)
      .def("get_height", &Node::getHeight)

      .def("get_min_width", &Node::getMinWidth)
      .def("get_min_height", &Node::getMinHeight)

      .def("get_max_width", &Node::getMaxWidth)
      .def("get_max_height", &Node::getMaxHeight)

      .def("get_aspect_ratio", &Node::getAspectRatio)

      .def("get_border", &Node::getBorder)

      .def("get_overflow", &Node::getOverflow)
      .def("get_display", &Node::getDisplay)

      .def("get_padding", &Node::getPadding)
      .def("get_gap", &Node::getGap)

      .def("insert_child", &Node::insertChild)
      .def("remove_child", &Node::removeChild)

      .def("get_child_count", &Node::getChildCount)

      .def("get_parent", &Node::getParent)
      .def("get_child", &Node::getChild)

      .def("is_reference_baseline", &Node::isReferenceBaseline)
      .def("set_is_reference_baseline", &Node::setIsReferenceBaseline)

      .def("set_measure_func", &Node::setMeasureFunc, py::keep_alive<1,2>())
      .def("unset_measure_func", &Node::unsetMeasureFunc)

      .def("set_dirtied_func", &Node::setDirtiedFunc, py::keep_alive<1,2>())
      .def("unset_dirtied_func", &Node::unsetDirtiedFunc)

      .def("mark_dirty", &Node::markDirty)
      .def("is_dirty", &Node::isDirty)

      .def("calculate_layout", &Node::calculateLayout)

      .def("get_computed_left", &Node::getComputedLeft)
      .def("get_computed_right", &Node::getComputedRight)

      .def("get_computed_top", &Node::getComputedTop)
      .def("get_computed_bottom", &Node::getComputedBottom)

      .def("get_computed_width", &Node::getComputedWidth)
      .def("get_computed_height", &Node::getComputedHeight)

      .def("get_computed_layout", &Node::getComputedLayout)

      .def("get_computed_margin", &Node::getComputedMargin)
      .def("get_computed_border", &Node::getComputedBorder)
      .def("get_computed_padding", &Node::getComputedPadding);

      #include "./YGEnums.h"

#ifdef VERSION_INFO
      m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
      m.attr("__version__") = "dev";
#endif
}
