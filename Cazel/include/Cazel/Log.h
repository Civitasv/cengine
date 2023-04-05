#pragma once

#include "Cazel/Core.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

namespace Cazel {
class CAZEL_API Log {
 public:
  static void Init();

  static std::shared_ptr<spdlog::logger>& GetCoreLogger();

  static std::shared_ptr<spdlog::logger>& GetClientLogger();

 private:
  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};
}  // namespace Cazel

// Core log macros, __VA_ARGS__ means everything you put into this macro.
#define CZ_CORE_TRACE(...) ::Cazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CZ_CORE_INFO(...) ::Cazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CZ_CORE_WARN(...) ::Cazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CZ_CORE_ERROR(...) ::Cazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CZ_CORE_FATAL(...) ::Cazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define CZ_TRACE(...) ::Cazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CZ_INFO(...) ::Cazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define CZ_WARN(...) ::Cazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CZ_ERROR(...) ::Cazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define CZ_FATAL(...) ::Cazel::Log::GetClientLogger()->fatal(__VA_ARGS__)