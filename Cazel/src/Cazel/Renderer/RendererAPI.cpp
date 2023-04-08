#include "Cazel/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "czpch.h"

namespace Cazel {
RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

Scope<RendererAPI> RendererAPI::Create() {
  switch (s_API) {
    case RendererAPI::API::None:
      CZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateScope<OpenGLRendererAPI>();
  }

  CZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
}  // namespace Cazel