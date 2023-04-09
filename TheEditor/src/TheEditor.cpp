#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

#include "Cazel.h"
#include "Cazel/Core/EntryPoint.h"
#include "EditorLayer.h"

namespace Cazel {
/// @brief Define Application.
class TheEditorApp : public Application {
 public:
  TheEditorApp() { PushLayer(new EditorLayer()); }
  ~TheEditorApp() {}
};

/// @brief Create Application.
/// @return Application which will run.
Cazel::Application* Cazel::CreateApplication() { return new TheEditorApp(); }
}  // namespace Cazel