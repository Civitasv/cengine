#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"),
      m_CameraController(Cazel::Application::Get().GetWindow().GetAspectRatio(),
                         true),
      m_SquareColor({0.2f, 0.3f, 0.8f, 1.0f}) {}

void Sandbox2D::OnAttach() {
  m_CheckerboardTexture =
      Cazel::Texture2D::Create("res/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(Cazel::Timestep ts) {
  // Update
  m_CameraController.OnUpdate(ts);

  // Render
  Cazel::Renderer2D::ResetStats();
  {
    Cazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Cazel::RenderCommand::Clear();
  }

  {
    static float rotation = 0.0f;
    rotation += ts * 50.0f;

    Cazel::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Cazel::Renderer2D::DrawLineBezierCubic(
        {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {2.0f, 0.1f, 0.0f},
        {3.0f, 1.6f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, 3.0f);

    Cazel::Renderer2D::DrawRect({1.5f, 0.8f, 0.0f}, {3.0f, 1.6f},
                                {1.0f, 1.0f, 1.0f, 1.0f});

    Cazel::Renderer2D::EndScene();
  }
}

void Sandbox2D::OnImGuiRender() {
  ImGui::Begin("Settings");

  ImGui::End();
}

void Sandbox2D::OnEvent(Cazel::Event& e) { m_CameraController.OnEvent(e); }
