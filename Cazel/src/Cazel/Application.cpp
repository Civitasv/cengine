#include "Cazel/Application.h"

#include "Cazel/Events/ApplicationEvent.h"
#include "Cazel/Log.h"
#include "GLFW/glfw3.h"
#include "czpch.h"

namespace Cazel {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
Application::Application() {
  m_Window = std::unique_ptr<Window>(Window::Create());
  // see https://en.cppreference.com/w/cpp/utility/functional/bind
  m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
}

Application::~Application() {}

void Application::Run() {
  while (m_Running) {
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    m_Window->OnUpdate();
  }
}

/// @brief Higher layer of callback.
/// @param e event to be handled.
void Application::OnEvent(Event& e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

  CZ_CORE_TRACE("{0}", e);
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
  m_Running = false;
  return true;
}
}  // namespace Cazel
