#pragma once

#include "Cazel.h"
#include "Cazel/Renderer/PerspectiveCamera.h"

namespace Cazel {
class EditorLayer : public Layer {
 public:
  EditorLayer();
  virtual ~EditorLayer() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;

  void OnUpdate(Timestep ts) override;
  virtual void OnImGuiRender() override;
  void OnEvent(Event& e) override;

 private:
  bool OnKeyPressed(KeyPressedEvent& e);
  bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

  void OnOverlayRender();

 private:
  // Temp
  Ref<VertexArray> m_SquareVA;
  Ref<Shader> m_FlatColorShader;

  bool m_PrimaryCamera = true;
  PerspectiveCamera m_EditorCamera;

  Ref<Texture2D> m_CheckerboardTexture;

  bool m_ViewportFocused = false, m_ViewportHovered = false;
  glm::vec2 m_ViewportSize = {0.0f, 0.0f};
  glm::vec2 m_ViewportBounds[2];

  glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};

  bool m_ShowPhysicsColliders = false;

  enum class SceneState { Edit = 0, Play = 1, Simulate = 2 };
  SceneState m_SceneState = SceneState::Edit;
};

}  // namespace Cazel
