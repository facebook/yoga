/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <forward_list>
#include <memory>
#include <mutex>
#include <stack>
#include <type_traits>
#include <utility>

#ifndef YOGA_EXPORT
#ifdef _MSC_VER
#define YOGA_EXPORT
#else
#define YOGA_EXPORT __attribute__((visibility("default")))
#endif
#endif

namespace facebook {
namespace yoga {

namespace detail {

class YOGA_EXPORT FreeList {
  std::stack<void*> free_;
  void* getRaw();

public:
  FreeList();
  ~FreeList();

  void put(std::mutex&, void*);

  template <typename T>
  T* get() {
    return static_cast<T*>(getRaw());
  }
};

} // namespace detail

/// SingleWriterValueList is a data structure that holds a list of values. Each
/// value can be borrowed for exclusive writing, and will not be exposed to
/// another borrower until returned.
/// Additionaly, the whole list of values can be accessed for reading via const
/// iterators. Read consistency depends on CPU internals, i.e. whether values
/// are written to memory atomically.
///
/// A typical usage scenario would be a set of threads, where each thread
/// borrows a value for lock free writing, e.g. as a thread local variable. This
/// avoids the usage of atomics, or locking of shared memory, which both can
/// lead to increased latency due to CPU cache flushes and waits.
///
/// Values are heap allocated (via forward_list), which typically will avoid
/// multiple values being allocated in the same CPU cache line, which would also
/// lead to cache flushing.
///
/// SingleWriterValueList never deallocates, to guarantee the validity of
/// references and iterators. However, memory returned by a borrower can be
/// borrowed again.
///
/// SingleWriterValueList supports return policies as second template parameter,
/// i.e. an optional mutation of values after a borrower returns them. The
/// default policy is to do nothing. SingleWriterValueList::resetPolicy is a
/// convenience method that will move assign the default value of a type.
///
/// Example:
///
///   static SingleWriterValueList<int> counters;
///   thread_local auto localCounter = counters.borrow();
///
///    /* per thread */
///    localCounter =+ n;
///
///    /* anywhere */
///    std::accumulate(counters.begin(), counters.end(), 0);
///
template <typename T, void (*ReturnPolicy)(T&) = nullptr>
class YOGA_EXPORT SingleWriterValueList {
  std::forward_list<T> values_{};
  std::mutex acquireMutex_{};
  detail::FreeList freeValuesList_{};

  T* allocValue() {
    values_.emplace_front();
    return &values_.front();
  }

  void returnRef(T* value) {
    if (ReturnPolicy != nullptr) {
      ReturnPolicy(*value);
    }
    freeValuesList_.put(acquireMutex_, value);
  }

public:
  using const_iterator = decltype(values_.cbegin());

  /// RAII representation of a single value, borrowed for exclusive writing.
  /// Instances cannot be copied, and will return the borrowed value to the
  /// owner upon destruction.
  class Borrowed {
    T* value_;
    SingleWriterValueList* owner_;

  public:
    Borrowed(T* value, SingleWriterValueList* owner)
        : value_{value}, owner_{owner} {}
    ~Borrowed() {
      if (owner_ != nullptr && value_ != nullptr) {
        owner_->returnRef(value_);
      }
    }

    Borrowed(Borrowed&& other) = default;
    Borrowed& operator=(Borrowed&& other) = default;

    // no copies allowed
    Borrowed(const Borrowed&) = delete;
    Borrowed& operator=(const Borrowed&) = delete;

    T& get() { return *value_; }
    T& operator*() { return get(); }
  };

  Borrowed borrow() {
    std::lock_guard<std::mutex> lock{acquireMutex_};
    T* value = freeValuesList_.get<T>();
    return {value != nullptr ? value : allocValue(), this};
  }

  const_iterator cbegin() const { return values_.cbegin(); };
  const_iterator cend() const { return values_.cend(); };
  const_iterator begin() const { return cbegin(); };
  const_iterator end() const { return cend(); };

  static void resetPolicy(T& value) { value = std::move(T{}); }
};

} // namespace yoga
} // namespace facebook
