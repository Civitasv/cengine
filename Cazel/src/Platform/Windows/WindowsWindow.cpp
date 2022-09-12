#include "Platform/Windows/WindowsWindow.h"

#include "czpch.h"

namespace Cazel {
static bool s_GLFWInitialized = false;

Window* Window::Create(const WindowProps& props) {
  return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props) { Init(props); }

WindowsWindow::~WindowsWindow() { Shutdown(); }

void WindowsWindow::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_Window);
}

void WindowsWindow::Init(const WindowProps& props) {
  m_Data.Title = props.Title;
  m_Data.Width = props.Width;
  m_Data.Height = props.Height;

  CZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
               props.Height);

  if (!s_GLFWInitialized) {
    int success = glfwInit();
    CZ_CORE_ASSERT(success, "Could not intialize GLFW!");
    s_GLFWInitialized = true;
  }

  m_Window = glfwCreateWindow(props.Width, props.Height, m_Data.Title.c_str(),
                              nullptr, nullptr);

  glfwMakeContextCurrent(m_Window);
  glfwSetWindowUserPointer(m_Window, &m_Data);

  SetVSync(true);
}

void WindowsWindow::Shutdown() { glfwDestroyWindow(m_Window); }

void WindowsWindow::SetVSync(bool enabled) {
  if (enabled) {
    // the number of screen updates to wait 
    // [from] the time glfwSwapBuffers was called 
    // [to] before swapping the buffers and returning
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  m_Data.VSync = enabled;
}

bool WindowsWindow::IsVSync() const { return m_Data.VSync; }
}  // namespace Cazel