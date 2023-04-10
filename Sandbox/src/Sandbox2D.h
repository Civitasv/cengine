#pragma once

#include "Cazel.h"
#include "Cazel/Renderer/Renderer2D.h"

class Sandbox2D : public Cazel::Layer {
 public:
  Sandbox2D();
  virtual ~Sandbox2D() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;

  void OnUpdate(Cazel::Timestep ts) override;
  virtual void OnImGuiRender() override;
  void OnEvent(Cazel::Event& e) override;

 private:
  Cazel::OrthographicCameraController m_CameraController;

  // Temp
  Cazel::Ref<Cazel::VertexArray> m_SquareVA;
  Cazel::Ref<Cazel::Shader> m_FlatColorShader;

  Cazel::Ref<Cazel::Texture2D> m_CheckerboardTexture;

  glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};