#include "Cazel/Renderer/Texture.h"

#include "Cazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "czpch.h"

namespace Cazel {
Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      CZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLTexture2D>(width, height);
  }

  CZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

Ref<Texture2D> Texture2D::Create(const std::string& path) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      CZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLTexture2D>(path);
  }

  CZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
}  // namespace Cazel