#pragma once
#include "Cazel/Core.h"
#include "Cazel/Window.h"
#include "Events/Event.h"

namespace Cazel {

/// we want our user to extend this class
/// then use it Run to run app.
class CAZEL_API Application {
 public:
  Application();
  virtual ~Application();

  void Run();

 private:
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
};

/// To be defined in CLIENT.
Application* CreateApplication();

}  // namespace Cazel