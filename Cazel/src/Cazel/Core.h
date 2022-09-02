#pragma once

#ifdef CZ_PLATFORM_WINDOWS
#ifdef CZ_BUILD_DLL
#define CAZEL_API __declspec(dllexport)
#else
#define CAZEL_API __declspec(dllimport)
#endif
#else
#error CAZEL ONLY SUPPORT WINDOWS!
#endif
