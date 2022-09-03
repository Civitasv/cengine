#pragma once
#include "Core.h"

namespace Cazel {

/// we want our user to extend this class
/// then use it Run to run app.
class CAZEL_API Application {
 public:
  Application();
  virtual ~Application();

  void Run();
};

/// To be defined in CLIENT.
Application* CreateApplication();

}  // namespace Cazel