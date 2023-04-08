#include "Platform/Windows/WindowsInput.h"

#include "Cazel/Core/Application.h"
#include "czpch.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

namespace Cazel {
Input* Input::s_Instance = new WindowsInput();

bool WindowsInput::IsKeyPressedImpl(int keycode) {
  auto window = static_cast<GLFWwindow*>(
      Application::Get().GetWindow().GetNativeWindow());
  auto state = glfwGetKey(window, keycode);

  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::IsMouseButtonPressedImpl(int button) {
  auto window = static_cast<GLFWwindow*>(
      Application::Get().GetWindow().GetNativeWindow());
  auto state = glfwGetMouseButton(window, button);

  return state == GLFW_PRESS;
}

float WindowsInput::GetMouseXImpl() {
  auto [x, y] = GetMousePositionImpl();
  return x;
}

float WindowsInput::GetMouseYImpl() {
  auto [x, y] = GetMousePositionImpl();
  return y;
}

std::pair<float, float> WindowsInput::GetMousePositionImpl() {
  auto window = static_cast<GLFWwindow*>(
      Application::Get().GetWindow().GetNativeWindow());

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  return {(float)xpos, (float)ypos};
}
}  // namespace Cazel