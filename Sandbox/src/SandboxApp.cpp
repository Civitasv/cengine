#include <iostream>

#include "Cazel.h"
#include "Cazel/Core/EntryPoint.h"

#include "Sandbox2D.h"

using namespace Cazel;

/// @brief Define Application.
class Sandbox : public Application {
 public:
  Sandbox() { PushLayer(new Sandbox2D()); }
  ~Sandbox() {}
};

/// @brief Create Application.
/// @return Application which will run.
Cazel::Application* Cazel::CreateApplication() { return new Sandbox(); }
