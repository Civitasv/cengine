#include "Cazel/Renderer/Renderer.h"

#include "Cazel/Renderer/RenderCommand.h"
#include "Cazel/Renderer/Renderer2D.h"
#include "czpch.h"

namespace Cazel {
Scope<Renderer::SceneData> Renderer::s_SceneData =
    CreateScope<Renderer::SceneData>();

void Renderer::Init() {
  RenderCommand::Init();
  Renderer2D::Init();
}

void Renderer::Shutdown() {}

void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
  RenderCommand::SetViewport(0, 0, width, height);
}

void Renderer::BeginScene(Camera& camera) {
  s_SceneData->ViewProjectMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const Ref<Shader>& shader,
                      const Ref<VertexArray>& vertexArray,
                      const glm::mat4& transform) {
  shader->Bind();
  // View and Projection matrix
  shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectMatrix);
  // Model matrix
  shader->SetMat4("u_Transform", transform);

  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace Cazel