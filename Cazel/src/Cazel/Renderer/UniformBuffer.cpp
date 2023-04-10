#include "Cazel/Renderer/UniformBuffer.h"

#include "Cazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"
#include "czpch.h"

namespace Cazel {
Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      CZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLUniformBuffer>(size, binding);
  }

  CZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
}  // namespace Cazel
