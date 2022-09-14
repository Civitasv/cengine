#pragma once
#include "Cazel/Core.h"
#include "Cazel/Window.h"
#include "Events/Event.h"
#include "Cazel/Events/ApplicationEvent.h"

namespace Cazel {

/// we want our user to extend this class
/// then use it Run to run app.
class CAZEL_API Application {
 public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event& e);

 private:
  bool OnWindowClose(WindowCloseEvent& e);

  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
};

/// To be defined in CLIENT.
Application* CreateApplication();

}  // namespace Cazel