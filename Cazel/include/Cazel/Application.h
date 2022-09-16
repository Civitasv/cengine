#pragma once
#include "Cazel/Core.h"
#include "Cazel/Events/ApplicationEvent.h"
#include "Cazel/Events/Event.h"
#include "Cazel/LayerStack.h"
#include "Cazel/Window.h"

namespace Cazel {

/// we want our user to extend this class
/// then use its `Run method` to run app.
class CAZEL_API Application {
 public:
  Application();
  virtual ~Application();

  void Run();

  /// @brief All events will be handled by this function.
  /// @param e event, see Events directory.
  void OnEvent(Event& e);

  void PushLayer(Layer* layer);
  void PushOverlay(Layer* overlay);

 private:
  bool OnWindowClose(WindowCloseEvent& e);

  std::unique_ptr<Window> m_Window;
  bool m_Running = true;

  LayerStack m_LayerStack;
};

/// To be defined in CLIENT.
Application* CreateApplication();

}  // namespace Cazel