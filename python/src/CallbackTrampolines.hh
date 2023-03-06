#pragma once
#include <memory>
#include <pybind11/pybind11.h>

#include "./Callbacks.hh"




class PyMeasureCallback : public MeasureCallback {
public:
    /* Inherit the constructors */
    using MeasureCallback::MeasureCallback;

    /* Trampoline (need one for each virtual function) */
    Size measure(
      float width, int widthMode,
      float height, int heightMode) override {
        PYBIND11_OVERRIDE_PURE(
            Size,
            MeasureCallback,
            measure,
            width,
            widthMode,
            height,
            heightMode
        );
    }
};

class PyDirtiedCallback : public DirtiedCallback {
public:
    /* Inherit the constructors */
    using DirtiedCallback::DirtiedCallback;

    /* Trampoline (need one for each virtual function) */
    void dirtied() override {
        PYBIND11_OVERRIDE_PURE(
            void,
            DirtiedCallback,
            dirtied
        );
    }
};
