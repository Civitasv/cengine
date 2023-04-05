#include "Platform/OpenGL/OpenGLContext.h"

#include "czpch.h"

namespace Cazel {
OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : m_WindowHandle(windowHandle) {
  CZ_CORE_ASSERT(windowHandle, "Window handle is null!");
}

void OpenGLContext::Init() {
  glfwMakeContextCurrent(m_WindowHandle);

  // Initialize Glad
  int status = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
  CZ_CORE_ASSERT(status, "Failed to initialize OpenGL context");
  CZ_CORE_INFO("Loaded OpenGL, VERSION: {0}.{1}", GLAD_VERSION_MAJOR(status),
               GLAD_VERSION_MINOR(status));
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }
}  // namespace Cazel