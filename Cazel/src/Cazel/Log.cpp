#include "Cazel/Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Cazel {
std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::Init() {
  // %v: actual text
  // %n: Logger's name
  // %T: ISO 8601 time format(HH:MM:SS)
  // %^: start color range
  // %$: end color range
  spdlog::set_pattern("%^[%T] %n: %v%$");

  s_CoreLogger = spdlog::stdout_color_mt("CAZEL");
  s_CoreLogger->set_level(spdlog::level::trace);

  s_ClientLogger = spdlog::stdout_color_mt("APP");
  s_ClientLogger->set_level(spdlog::level::trace);
}
}  // namespace Cazel