#include "Cazel/Application.h"

#include "Cazel/Events/ApplicationEvent.h"
#include "Cazel/Log.h"
#include "czpch.h"

namespace Cazel {

Application::Application() {}

Application::~Application() {}

void Application::Run() {
  WindowResizeEvent e(1280, 720);
  if (e.IsInCategory(EventCategoryApplication)) {
    CZ_TRACE(e);
  }
  if (e.IsInCategory(EventCategoryInput)) {
    CZ_TRACE(e);
  }

  while (true)
    ;
}

}  // namespace Cazel