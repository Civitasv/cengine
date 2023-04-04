#include "Platform/Windows/WindowsWindow.h"

#include "Cazel/Events/ApplicationEvent.h"
#include "Cazel/Events/KeyEvent.h"
#include "Cazel/Events/MouseEvent.h"
#include "Cazel/Log.h"
#include "czpch.h"

namespace Cazel {
static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char *description) {
  CZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window *Window::Create(const WindowProps &props) {
  return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps &props) { Init(props); }

WindowsWindow::~WindowsWindow() { Shutdown(); }

void WindowsWindow::OnUpdate() {
  glfwPollEvents();
  // This function swaps the front and back buffers
  // of the specified window. If the swap interval
  // is greater than zero, the GPU driver waits the
  // specified number of screen updates before swapping the buffers.
  glfwSwapBuffers(m_Window);
}

void WindowsWindow::Init(const WindowProps &props) {
  m_Data.Title = props.Title;
  m_Data.Width = props.Width;
  m_Data.Height = props.Height;

  CZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
               props.Height);

  if (!s_GLFWInitialized) {
    int success = glfwInit();
    CZ_CORE_ASSERT(success, "Could not intialize GLFW!");

    glfwSetErrorCallback(GLFWErrorCallback);
    s_GLFWInitialized = true;
  }

  m_Window = glfwCreateWindow(props.Width, props.Height, m_Data.Title.c_str(),
                              nullptr, nullptr);

  glfwMakeContextCurrent(m_Window);

  // Initialize Glad
  int status = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
  CZ_CORE_ASSERT(status, "Failed to initialize OpenGL context");
  CZ_CORE_INFO("Loaded OpenGL, VERSION: {0}.{1}", GLAD_VERSION_MAJOR(status),
               GLAD_VERSION_MINOR(status));

  glfwSetWindowUserPointer(m_Window, &m_Data);

  SetVSync(true);

  // Set GLFW callbacks
  glfwSetWindowSizeCallback(
      m_Window, [](GLFWwindow *window, int width, int height) {
        WindowData &data =
            *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        // lower layer of callback.
        data.EventCallback(event);
      });

  glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
    WindowData &data =
        *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
    WindowCloseEvent event;
    data.EventCallback(event);
  });

  glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode,
                                  int action, int mods) {
    WindowData &data =
        *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
    switch (action) {
      case GLFW_PRESS: {
        KeyPressedEvent event(key, 0);
        data.EventCallback(event);
        break;
      }
      case GLFW_RELEASE: {
        KeyReleasedEvent event(key);
        data.EventCallback(event);
        break;
      }
      case GLFW_REPEAT: {
        KeyPressedEvent event(key, 1);
        data.EventCallback(event);
        break;
      }
    }
  });

  glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    KeyTypedEvent event(keycode);
    data.EventCallback(event);
  });

  glfwSetMouseButtonCallback(
      m_Window, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data =
            *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
        switch (action) {
          case GLFW_PRESS: {
            MouseButtonPressedEvent event(button);
            data.EventCallback(event);
            break;
          }
          case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(button);
            data.EventCallback(event);
            break;
          }
        }
      });

  glfwSetScrollCallback(
      m_Window, [](GLFWwindow *window, double xoffset, double yoffset) {
        WindowData &data =
            *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        MouseScrolledEvent event((float)xoffset, (float)yoffset);
        data.EventCallback(event);
      });

  glfwSetCursorPosCallback(
      m_Window, [](GLFWwindow *window, double xpos, double ypos) {
        WindowData &data =
            *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
        MouseMovedEvent event((float)xpos, (float)ypos);
        data.EventCallback(event);
      });
}

void WindowsWindow::Shutdown() { glfwDestroyWindow(m_Window); }

void WindowsWindow::SetVSync(bool enabled) {
  if (enabled) {
    // set the number of screen updates to wait
    // before swapping the buffers and returning
    // (when glfwSwapBuffers was called)
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  m_Data.VSync = enabled;
}

bool WindowsWindow::IsVSync() const { return m_Data.VSync; }
}  // namespace Cazel