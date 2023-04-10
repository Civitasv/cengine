#pragma once
#include "Cazel/Core/Core.h"
#include "Cazel/Core/LayerStack.h"
#include "Cazel/Core/Timestep.h"
#include "Cazel/Core/Window.h"
#include "Cazel/Events/ApplicationEvent.h"
#include "Cazel/Events/Event.h"
#include "Cazel/Renderer/Renderer.h"
#include "Cazel/Renderer/Texture.h"
#include "Cazel/imgui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Cazel {
/// we want our user to extend this class
/// then use its `Run method` to run app.
class CAZEL_API Application {
 public:
  Application();
  virtual ~Application();

  void Run();
  void ShutDown();

  /// @brief All events will be handled by this function.
  /// @param e event, see Events directory.
  void OnEvent(Event& e);

  void PushLayer(Layer* layer);
  void PushOverlay(Layer* overlay);

  static Application& Get();
  Window& GetWindow();

 private:
  bool OnWindowClose(WindowCloseEvent& e);
  Scope<Window> m_Window;
  // For debug issues
  ImGuiLayer* m_ImGuiLayer;  ///< handled by layerstack, so I don't need to
                             ///< release this memory
  bool m_Running = true;
  LayerStack m_LayerStack;
  float m_LastFrameTime = 0.0f;

 private:
  static Application* s_Instance;
  friend int ::main(int argc, char** argv);
};

/// To be defined in CLIENT.
Application* CreateApplication();
}  // namespace Cazel