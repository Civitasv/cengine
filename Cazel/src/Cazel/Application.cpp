#include "Cazel/Application.h"

#include "Cazel/Events/ApplicationEvent.h"
#include "Cazel/Input.h"
#include "Cazel/Log.h"
#include "czpch.h"

namespace Cazel {
/// It should be Single Instance
Application *Application::s_Instance = nullptr;

Application::Application() {
  CZ_CORE_ASSERT(!s_Instance, "Application already exists!");
  s_Instance = this;

  m_Window = std::unique_ptr<Window>(Window::Create());
  // see https://en.cppreference.com/w/cpp/utility/functional/bind
  m_Window->SetEventCallback(CZ_BIND_EVENT_FN(Application::OnEvent));

  m_ImGuiLayer = new ImGuiLayer();
  PushOverlay(m_ImGuiLayer);
}

Application::~Application() {}

void Application::Run() {
  while (m_Running) {
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Layer *layer : m_LayerStack) {
      layer->OnUpdate();  // 更新的时候，是从第一个到最后一个
    }

    m_ImGuiLayer->Begin();
    for (Layer *layer : m_LayerStack) {
      layer->OnImGuiRender();  // 更新的时候，是从第一个到最后一个
    }
    m_ImGuiLayer->End();

    m_Window->OnUpdate();
  }
}

/// @brief Higher layer of callback.
/// @param e event to be handled.
void Application::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  // 检查是否是 WindowCloseEvent，如果是的话，e.handled will be true
  dispatcher.Dispatch<WindowCloseEvent>(
      CZ_BIND_EVENT_FN(Application::OnWindowClose));

  // 否则，对每一个图层执行该事件
  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    if (e.Handled) {
      break;
    }
    (*--it)->OnEvent(e);  // 处理事件的时候，是从最后一个到第一个
  }
}

void Application::PushLayer(Layer *layer) {
  m_LayerStack.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer *overlay) {
  m_LayerStack.PushOverlay(overlay);
  overlay->OnAttach();
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}

Application &Application::Get() { return *s_Instance; }

Window &Application::GetWindow() { return *m_Window.get(); }
}  // namespace Cazel
