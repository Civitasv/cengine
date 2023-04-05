#include "Cazel/imgui/ImGuiLayer.h"

#include <iostream>

#include "Cazel/Application.h"
#include "Platform/GLFW/ImGuiGLFW.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "czpch.h"
#include "imgui.h"

namespace Cazel {
ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGuiIO& io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  // TEMPORARY: should eventually use Cazel key codes
  io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
  io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
  io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
  io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
  io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
  io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
  io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
  io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
  io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
  io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
  io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
  io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
  io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
  io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
  io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
  io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
  io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

  // auto window = static_cast<GLFWwindow*>(
  //     Application::Get().GetWindow().GetNativeWindow());

  // ImGui_ImplGlfw_InitForOpenGL(window, false);
  ImGui_ImplOpenGL3_Init("#version 410 core");
}

void ImGuiLayer::OnDetach() {
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  // ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer::OnUpdate() {
  ImGuiIO& io = ImGui::GetIO();
  Application& app = Application::Get();

  io.DisplaySize =
      ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

  float time = (float)glfwGetTime();
  io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
  m_Time = time;

  // ImGui_ImplGlfw_NewFrame();
  ImGui_ImplOpenGL3_NewFrame();

  ImGui::NewFrame();

  static bool show = true;
  ImGui::ShowDemoWindow(&show);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event& event) {
  // Implement Windowing, Event input on our platform
  // (我们封装了 glfw，但是自己处理事件、窗口、键盘输入输出等)
  EventDispatcher dispatcher(event);

  // [this](auto e) -> void { fn(e); }
  dispatcher.Dispatch<MouseButtonPressedEvent>(
      CZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
  dispatcher.Dispatch<MouseButtonReleasedEvent>(
      CZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
  dispatcher.Dispatch<MouseMovedEvent>(
      CZ_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
  dispatcher.Dispatch<MouseScrolledEvent>(
      CZ_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
  dispatcher.Dispatch<KeyPressedEvent>(
      CZ_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
  dispatcher.Dispatch<KeyReleasedEvent>(
      CZ_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
  dispatcher.Dispatch<KeyTypedEvent>(
      CZ_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
  dispatcher.Dispatch<WindowResizeEvent>(
      CZ_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
  ImGuiIO& io = ImGui::GetIO();
  io.MouseDown[e.GetMouseButton()] = true;

  return false;  // we want other layers handle this
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
  ImGuiIO& io = ImGui::GetIO();
  io.MouseDown[e.GetMouseButton()] = false;

  return false;  // we want other layers handle this
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e) {
  ImGuiIO& io = ImGui::GetIO();
  io.MousePos = ImVec2(e.GetX(), e.GetY());

  return false;  // we want other layers handle this
}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e) {
  ImGuiIO& io = ImGui::GetIO();
  io.MouseWheelH += e.GetXOffset();
  io.MouseWheel += e.GetYOffset();

  return false;  // we want other layers handle this
}

bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e) {
  ImGuiIO& io = ImGui::GetIO();
  io.KeysDown[e.GetKeyCode()] = true;

  io.KeyCtrl =
      io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
  io.KeyShift =
      io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
  io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
  io.KeySuper =
      io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

  return false;  // we want other layers handle this
}

bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) {
  ImGuiIO& io = ImGui::GetIO();
  io.KeysDown[e.GetKeyCode()] = false;

  return false;  // we want other layers handle this
}

bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
  ImGuiIO& io = ImGui::GetIO();
  io.AddInputCharacter(e.GetKeyCode());

  return false;  // we want other layers handle this
}

bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e) {
  ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
  io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

  // glViewport(0, 0, e.GetWidth(), e.GetHeight());
  return false;  // we want other layers handle this
}
}  // namespace Cazel