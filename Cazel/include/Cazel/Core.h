#pragma once

#ifdef CZ_PLATFORM_WINDOWS
#ifdef CZ_BUILD_DLL
/// __declspec(dllexport) means exporting this in dll.
#define CAZEL_API __declspec(dllexport)
#else
/// __declspec(dllimport) means importing this in dll.
#define CAZEL_API __declspec(dllimport)
#endif
#else
#error CAZEL ONLY SUPPORT WINDOWS!
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