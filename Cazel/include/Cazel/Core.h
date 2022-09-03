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
