#include "Cazel/Renderer/Buffer.h"

#include "Cazel/Renderer/Renderer.h"
#include "Cazel/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "czpch.h"

namespace Cazel {

Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      CZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLVertexBuffer>(size);
  }

  CZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      CZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLVertexBuffer>(vertices, size);
  }

  CZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      CZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLIndexBuffer>(indices, size);
  }

  CZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}  // namespace Cazel