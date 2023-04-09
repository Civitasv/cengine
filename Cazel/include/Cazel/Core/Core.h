#pragma once

#include <memory>

#define CZ_DEBUG

#ifdef CZ_DEBUG
#define CZ_ENABLE_ASSERTS
#endif

#if defined(_MSC_VER)
//  Microsoft
#define CAZEL_API __declspec(dllexport)
#elif defined(__GNUC__)
//  GCC
#define CAZEL_API __attribute__((visibility("default")))
#else
//  do nothing and hope for the best?
#define CAZEL_API
#pragma warning Unknown dynamic link import / export semantics.
#endif

#ifdef CZ_ENABLE_ASSERTS
#define CZ_ASSERT(x, ...)                             \
  {                                                   \
    if (!(x)) {                                       \
      CZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      __debugbreak();                                 \
    }                                                 \
  }
#define CZ_CORE_ASSERT(x, ...)                             \
  {                                                        \
    if (!(x)) {                                            \
      CZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      __debugbreak();                                      \
    }                                                      \
  }
#else
#define CZ_ASSERT(x, ...)
#define CZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

/// @breif 类似于 [this](auto a) -> void { fn(a); };
/// for std::bind, see https://en.cppreference.com/w/cpp/utility/functional/bind
#define CZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define CAZEL_DIMENSION TWO_D
#define CAZEL_RENDERER_PLATFORM OPENGL

namespace Cazel {
template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}
}  // namespace Cazel