#include <iostream>

#include "Cazel.h"

/// @brief Define Application.
class Sandbox : public Cazel::Application {
 public:
  Sandbox() {}
  ~Sandbox() {}
};

/// @brief Create Application.
/// @return Application which will run.
Cazel::Application* Cazel::CreateApplication() {
  return new Sandbox();
}
