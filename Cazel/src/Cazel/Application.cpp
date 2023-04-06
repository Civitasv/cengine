#include "Cazel/Application.h"

#include "Cazel/Events/ApplicationEvent.h"
#include "Cazel/Input.h"
#include "Cazel/Log.h"
#include "czpch.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

namespace Cazel {
/// It should be Single Instance
Application *Application::s_Instance = nullptr;

Application::Application() {
  CZ_CORE_ASSERT(!s_Instance, "Application already exists!");
  s_Instance = this;

  m_Window = std::unique_ptr<Window>(Window::Create());
  // event handler
  m_Window->SetEventCallback(CZ_BIND_EVENT_FN(Application::OnEvent));

  m_ImGuiLayer = new ImGuiLayer();
  PushOverlay(m_ImGuiLayer);
}

Application::~Application() {}

void Application::Run() {
  static Renderer renderer;
  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.5f,  -0.5f, -0.5f,
      0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
      0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, -0.5f, 0.5f,  -0.5f,
      0.0f,  0.0f,  -1.0f, -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,

      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,
      0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,
      0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,

      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f,
      -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,
      -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
      1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
      0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,
      1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, -0.5f,
      0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
      0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, 0.5f,
      0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
      0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,
      0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f};
  unsigned int indices[36];
  for (int i = 0; i < 36; i++) indices[i] = i;

  // GLCall(glEnable(GL_BLEND));
  GLCall(glEnable(GL_DEPTH_TEST));

  // R = r_src * sfactor + r_dest * dfactor
  // G = g_src * sfactor + g_dest * dfactor
  // B = b_src * sfactor + b_dest * dfactor
  // A = a_src * sfactor + a_dest * dfactor
  // GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  // vertex array object
  VertexArray cube_vao, light_cube_vao;
  // vertex buffer object
  VertexBuffer vb(vertices, sizeof(vertices));
  // specify layout in vertex buffer
  VertexBufferLayout layout;
  layout.Push<float>(3);
  layout.Push<float>(3);

  // index buffer object, specify how I want to draw this layout.
  IndexBuffer ib(indices, 36);

  cube_vao.AddBuffer(vb, ib, layout);
  light_cube_vao.AddBuffer(vb, ib, layout);

  Shader lightingShader("res/shaders/colors.shader");
  Shader lightCubeShader("res/shaders/lights.shader");
  glm::vec3 lightPos(1.0f, 0.5f, 0.2f);

  while (m_Running) {
    renderer.Clear();

    // change the light's position values over time (can be done anywhere in the
    // render loop actually, but try to do it at least before using the light
    // source positions)
     lightPos.x =sin(glfwGetTime());
     lightPos.y =  cos(glfwGetTime());

    // 4 * 3，正射投影，left, right, bottom, top 表示 x 和 y 的边界，zNear 和
    // zFar
    // 表示 z 的边界
    // glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 projection = glm::perspective(
        glm::radians(m_Window->GetCamera().zoom),
        (float)m_Window->GetWidth() / (float)m_Window->GetHeight(), 0.1f,
        100.0f);
    glm::mat4 view = m_Window->GetCamera().GetViewMatrix();
    glm::mat4 model = glm::mat4(0.5f);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0, 0.0, 1.0));

    lightingShader.Bind();
    lightingShader.SetUniformMat4f("projection", projection);
    lightingShader.SetUniformMat4f("view", view);
    lightingShader.SetUniformMat4f("model", model);
    lightingShader.SetUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
    lightingShader.SetUniform3f("lightColor", 0.0f, 1.0f, 0.0f);
    lightingShader.SetUniformVec3f("lightPos", lightPos);
    lightingShader.SetUniformVec3f("viewPos", m_Window->GetCamera().position);

    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));  // a smaller cube

    lightCubeShader.Bind();
    lightCubeShader.SetUniformMat4f("projection", projection);
    lightCubeShader.SetUniformMat4f("view", view);
    lightCubeShader.SetUniformMat4f("model", model);

    renderer.Draw(cube_vao, lightingShader, ib.GetCount());
    renderer.Draw(light_cube_vao, lightCubeShader, ib.GetCount());

    for (Layer *layer : m_LayerStack) {
      layer->OnUpdate();  // 更新的时候，是从第一个到最后一个
    }

    m_ImGuiLayer->Begin();
    for (Layer *layer : m_LayerStack) {
      layer->OnImGuiRender();  // 更新的时候，是从第一个到最后一个
    }
    m_ImGuiLayer->End();

    m_Window->OnUpdate();
  }
}

/// @brief Higher layer of callback.
/// @param e event to be handled.
void Application::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  // 检查是否是 WindowCloseEvent，如果是的话，e.handled will be true
  dispatcher.Dispatch<WindowCloseEvent>(
      CZ_BIND_EVENT_FN(Application::OnWindowClose));

  // 否则，对每一个图层执行该事件
  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    if (e.Handled) {
      break;
    }
    (*--it)->OnEvent(e);  // 处理事件的时候，是从最后一个到第一个
  }
}

void Application::PushLayer(Layer *layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer *overlay) {
  m_LayerStack.PushOverlay(overlay);
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}

inline Application &Application::Get() { return *s_Instance; }

inline Window &Application::GetWindow() { return *m_Window; }
}  // namespace Cazel
