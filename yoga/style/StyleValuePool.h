/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <cassert>
#include <cstdint>

#include <yoga/numeric/FloatOptional.h>
#include <yoga/style/SmallValueBuffer.h>
#include <yoga/style/StyleCalcLength.h>
#include <yoga/style/StyleLength.h>
#include <yoga/style/StyleSizeLength.h>
#include <yoga/style/StyleValueHandle.h>

namespace facebook::yoga {

/**
 * StyleValuePool allows compact storage for a sparse collection of assigned
 * lengths and numbers. Values are referred to using StyleValueHandle. In most
 * cases StyleValueHandle can embed the value directly, but if not, the value is
 * stored within a buffer provided by the pool. The pool contains a fixed number
 * of inline slots before falling back to heap allocating additional slots.
 */
class StyleValuePool {
 public:
  void store(StyleValueHandle& handle, StyleLength length) {
    if (length.isUndefined()) {
      handle.setType(StyleValueHandle::Type::Undefined);
    } else if (length.isAuto()) {
      handle.setType(StyleValueHandle::Type::Auto);
    } else if (length.isCalc()) {
      storeCalc(handle, length.calcValue());
    } else {
      auto type = length.isPoints() ? StyleValueHandle::Type::Point
                                    : StyleValueHandle::Type::Percent;
      storeValue(handle, length.value().unwrap(), type);
    }
  }

  void store(StyleValueHandle& handle, StyleSizeLength sizeValue) {
    if (sizeValue.isUndefined()) {
      handle.setType(StyleValueHandle::Type::Undefined);
    } else if (sizeValue.isAuto()) {
      handle.setType(StyleValueHandle::Type::Auto);
    } else if (sizeValue.isMaxContent()) {
      storeKeyword(handle, StyleValueHandle::Keyword::MaxContent);
    } else if (sizeValue.isStretch()) {
      storeKeyword(handle, StyleValueHandle::Keyword::Stretch);
    } else if (sizeValue.isFitContent()) {
      storeKeyword(handle, StyleValueHandle::Keyword::FitContent);
    } else if (sizeValue.isCalc()) {
      storeCalc(handle, sizeValue.calcValue());
    } else {
      auto type = sizeValue.isPoints() ? StyleValueHandle::Type::Point
                                       : StyleValueHandle::Type::Percent;
      storeValue(handle, sizeValue.value().unwrap(), type);
    }
  }

  void store(StyleValueHandle& handle, FloatOptional number) {
    if (number.isUndefined()) {
      handle.setType(StyleValueHandle::Type::Undefined);
    } else {
      storeValue(handle, number.unwrap(), StyleValueHandle::Type::Number);
    }
  }

  StyleLength getLength(StyleValueHandle handle) const {
    if (handle.isUndefined()) {
      return StyleLength::undefined();
    } else if (handle.isAuto()) {
      return StyleLength::ofAuto();
    } else if (handle.isCalc()) {
      return StyleLength::calc(getCalc(handle));
    } else {
      assert(
          handle.type() == StyleValueHandle::Type::Point ||
          handle.type() == StyleValueHandle::Type::Percent);
      float value = (handle.isValueIndexed())
          ? std::bit_cast<float>(buffer_.get32(handle.value()))
          : unpackInlineInteger(handle.value());

      return handle.type() == StyleValueHandle::Type::Point
          ? StyleLength::points(value)
          : StyleLength::percent(value);
    }
  }

  StyleSizeLength getSize(StyleValueHandle handle) const {
    if (handle.isUndefined()) {
      return StyleSizeLength::undefined();
    } else if (handle.isAuto()) {
      return StyleSizeLength::ofAuto();
    } else if (handle.isKeyword(StyleValueHandle::Keyword::MaxContent)) {
      return StyleSizeLength::ofMaxContent();
    } else if (handle.isKeyword(StyleValueHandle::Keyword::FitContent)) {
      return StyleSizeLength::ofFitContent();
    } else if (handle.isKeyword(StyleValueHandle::Keyword::Stretch)) {
      return StyleSizeLength::ofStretch();
    } else if (handle.isCalc()) {
      return StyleSizeLength::calc(getCalc(handle));
    } else {
      assert(
          handle.type() == StyleValueHandle::Type::Point ||
          handle.type() == StyleValueHandle::Type::Percent);
      float value = (handle.isValueIndexed())
          ? std::bit_cast<float>(buffer_.get32(handle.value()))
          : unpackInlineInteger(handle.value());

      return handle.type() == StyleValueHandle::Type::Point
          ? StyleSizeLength::points(value)
          : StyleSizeLength::percent(value);
    }
  }

  FloatOptional getNumber(StyleValueHandle handle) const {
    if (handle.isUndefined()) {
      return FloatOptional{};
    } else {
      assert(handle.type() == StyleValueHandle::Type::Number);
      float value = (handle.isValueIndexed())
          ? std::bit_cast<float>(buffer_.get32(handle.value()))
          : unpackInlineInteger(handle.value());
      return FloatOptional{value};
    }
  }

  // Used in frequently executed layout code.
  // It resolves directly from the handle and avoids creating temporary
  // StyleLength objects (getLength + resolve).
  FloatOptional resolveLength(
      StyleValueHandle handle,
      float referenceLength,
      float viewportWidth,
      float viewportHeight) const {
    if (handle.isUndefined() || handle.isAuto()) {
      return FloatOptional{};
    }

    const auto handleType = handle.type();
    if (handleType == StyleValueHandle::Type::Point ||
        handleType == StyleValueHandle::Type::Percent) {
      float value = handle.isValueIndexed()
          ? std::bit_cast<float>(buffer_.get32(handle.value()))
          : unpackInlineInteger(handle.value());
      return handle.type() == StyleValueHandle::Type::Point
          ? FloatOptional{value}
          : FloatOptional{referenceLength * value * 0.01f};
    }

    if (handle.isKeyword(StyleValueHandle::Keyword::MaxContent) ||
        handle.isKeyword(StyleValueHandle::Keyword::FitContent) ||
        handle.isKeyword(StyleValueHandle::Keyword::Stretch)) {
      return FloatOptional{};
    }

    if (handleType == StyleValueHandle::Type::Calc) {
      return resolveCalc(
          handle, referenceLength, viewportWidth, viewportHeight);
    }

    return FloatOptional{};
  }

 private:
  void storeValue(
      StyleValueHandle& handle,
      float value,
      StyleValueHandle::Type type) {
    handle.setType(type);

    if (handle.isValueIndexed()) {
      auto newIndex =
          buffer_.replace(handle.value(), std::bit_cast<uint32_t>(value));
      handle.setValue(newIndex);
    } else if (isIntegerPackable(value)) {
      handle.setValue(packInlineInteger(value));
    } else {
      auto newIndex = buffer_.push(std::bit_cast<uint32_t>(value));
      handle.setValue(newIndex);
      handle.setValueIsIndexed();
    }
  }

  void storeKeyword(
      StyleValueHandle& handle,
      StyleValueHandle::Keyword keyword) {
    handle.setType(StyleValueHandle::Type::Keyword);

    if (handle.isValueIndexed()) {
      auto newIndex =
          buffer_.replace(handle.value(), static_cast<uint32_t>(keyword));
      handle.setValue(newIndex);
    } else {
      handle.setValue(static_cast<uint16_t>(keyword));
    }
  }

  void storeCalc(StyleValueHandle& handle, StyleCalcLength calc) {
    handle.setType(StyleValueHandle::Type::Calc);
    uint64_t first = (static_cast<uint64_t>(std::bit_cast<uint32_t>(
                         calc.px().unwrapOrDefault(0.f)))) |
        (static_cast<uint64_t>(
             std::bit_cast<uint32_t>(calc.percent().unwrapOrDefault(0.f)))
         << 32);
    uint64_t second = (static_cast<uint64_t>(std::bit_cast<uint32_t>(
                          calc.vw().unwrapOrDefault(0.f)))) |
        (static_cast<uint64_t>(
             std::bit_cast<uint32_t>(calc.vh().unwrapOrDefault(0.f)))
         << 32);

    if (handle.isValueIndexed()) {
      auto newIndex = buffer_.replace(handle.value(), first);
      if (newIndex != handle.value()) {
        (void)buffer_.push(second);
      } else {
        (void)buffer_.replace(newIndex + 2, second);
      }
      handle.setValue(newIndex);
    } else {
      auto newIndex = buffer_.push(first);
      (void)buffer_.push(second);
      handle.setValue(newIndex);
      handle.setValueIsIndexed();
    }
  }

  StyleCalcLength getCalc(StyleValueHandle handle) const {
    if (handle.isUndefined()) {
      return StyleCalcLength{};
    }
    assert(handle.type() == StyleValueHandle::Type::Calc);
    assert(handle.isValueIndexed());

    uint64_t first = buffer_.get64(handle.value());
    uint64_t second = buffer_.get64(handle.value() + 2);

    return StyleCalcLength{
        FloatOptional{
            std::bit_cast<float>(static_cast<uint32_t>(first & 0xFFFFFFFF))},
        FloatOptional{std::bit_cast<float>(static_cast<uint32_t>(first >> 32))},
        FloatOptional{
            std::bit_cast<float>(static_cast<uint32_t>(second & 0xFFFFFFFF))},
        FloatOptional{
            std::bit_cast<float>(static_cast<uint32_t>(second >> 32))}};
  }

  FloatOptional resolveCalc(
      StyleValueHandle handle,
      float referenceLength,
      float viewportWidth,
      float viewportHeight) const;

  static constexpr bool isIntegerPackable(float f) {
    constexpr uint16_t kMaxInlineAbsValue = (1 << 11) - 1;

    auto i = static_cast<int32_t>(f);
    return static_cast<float>(i) == f && i >= -kMaxInlineAbsValue &&
        i <= +kMaxInlineAbsValue;
  }

  static constexpr uint16_t packInlineInteger(float value) {
    uint16_t isNegative = value < 0 ? 1 : 0;
    return static_cast<uint16_t>(
        (isNegative << 11) |
        (static_cast<int32_t>(value) * (isNegative != 0u ? -1 : 1)));
  }

  static constexpr float unpackInlineInteger(uint16_t value) {
    constexpr uint16_t kValueSignMask = 0b0000'1000'0000'0000;
    constexpr uint16_t kValueMagnitudeMask = 0b0000'0111'1111'1111;
    const bool isNegative = (value & kValueSignMask) != 0;
    return static_cast<float>(
        (value & kValueMagnitudeMask) * (isNegative ? -1 : 1));
  }

  SmallValueBuffer<4> buffer_;
};

} // namespace facebook::yoga
