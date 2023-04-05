#pragma once

#include "Cazel/Renderer/GraphicsContext.h"
#include "czpch.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

namespace Cazel {
class OpenGLContext : public GraphicsContext {
 public:
  OpenGLContext(GLFWwindow* windowHandle);

  void Init() override;
  void SwapBuffers() override;

 private:
  GLFWwindow* m_WindowHandle;
};
}  // namespace Cazel