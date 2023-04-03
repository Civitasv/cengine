#pragma once

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
#define CZ_ASSERT(x, ...)                                                      \
  {                                                                            \
    if (!(x)) {                                                                \
      CZ_ERROR("Assertion Failed: {0}", __VA_ARGS__);                          \
      __debugbreak();                                                          \
    }                                                                          \
  }
#define CZ_CORE_ASSERT(x, ...)                                                 \
  {                                                                            \
    if (!(x)) {                                                                \
      CZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                     \
      __debugbreak();                                                          \
    }                                                                          \
  }
#else
#define CZ_ASSERT(x, ...)
#define CZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)