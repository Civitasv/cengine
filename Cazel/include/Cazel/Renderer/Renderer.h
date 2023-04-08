#pragma once

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"

namespace Cazel {
/// @brief This is platform agnostic.
class Renderer {
 private:
  struct SceneData {
    glm::mat4 ViewProjectMatrix;
  };

  static Scope<SceneData> s_SceneData;

 public:
  static void Init();
  static void Shutdown();

  static void OnWindowResize(uint32_t width, uint32_t height);

  static void BeginScene(OrthographicCamera& camera);
  static void EndScene();

  static void Submit(const Ref<Shader>& shader,
                     const Ref<VertexArray>& vertexArray,
                     const glm::mat4& transform = glm::mat4(1.0f));
  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
};
}  // namespace Cazel