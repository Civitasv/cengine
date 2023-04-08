#include "Cazel/Renderer/VertexArray.h"

#include "Cazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "czpch.h"

namespace Cazel {
Ref<VertexArray> VertexArray::Create() {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      CZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLVertexArray>();
  }

  CZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
}  // namespace Cazel
