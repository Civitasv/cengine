#include "Cazel/Renderer/Shader.h"

#include "Cazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "czpch.h"

namespace Cazel {
Ref<Shader> Shader::Create(const std::string& filepath) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      CZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLShader>(filepath);
  }

  CZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

Ref<Shader> Shader::Create(const std::string& vertexSrc,
                           const std::string& fragmentSrc) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      CZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);
  }

  CZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
}  // namespace Cazel