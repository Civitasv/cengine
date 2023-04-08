#include "czpch.h"
#include "Cazel/Renderer/RenderCommand.h"

namespace Cazel {
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}