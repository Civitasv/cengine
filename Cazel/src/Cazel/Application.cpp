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

    for (Layer *layer : m_LayerStack) {
      layer->OnUpdate(); // 更新的时候，是从第一个到最后一个
    }
    m_Window->OnUpdate();
  }
}

/// @brief Higher layer of callback.
/// @param e event to be handled.
void Application::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    (*--it)->OnEvent(e); // 处理事件的时候，是从最后一个到第一个
    if (e.Handled) {
      break;
    }
  }
}

void Application::PushLayer(Layer *layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer *overlay) {
  m_LayerStack.PushOverlay(overlay);
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}
} // namespace Cazel
