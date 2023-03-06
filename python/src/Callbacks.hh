#pragma once
#include "./Size.hh"

class MeasureCallback {
public:
  virtual ~MeasureCallback() {}
  virtual Size measure(
      float width,
      int widthMode,
      float height,
      int heightMode) = 0;
};

class DirtiedCallback {
public:
  virtual ~DirtiedCallback() {}
  virtual void dirtied() = 0;
};
