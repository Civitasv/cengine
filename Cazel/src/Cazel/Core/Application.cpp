#include "Cazel/Core/Application.h"

#include "Cazel/Core/Input.h"
#include "Cazel/Core/Log.h"
#include "Cazel/Events/ApplicationEvent.h"
#include "Cazel/Renderer/EditorCamera.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
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
  static OpenGLRendererAPI renderer;
  renderer.Init();

  float vertices[] = {
      // positions          // normals           // texture coords
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 0.0f,
      0.0f,  -1.0f, 1.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
      1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f,
      0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      0.0f,  1.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,
      -0.5f, -1.0f, 0.0f,  0.0f,  1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f,
      0.0f,  0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
      0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,
      -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,
      0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
      0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
      -1.0f, 0.0f,  1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
      1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,
      -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      1.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f};
  unsigned int indices[36];
  for (int i = 0; i < 36; i++) indices[i] = i;

  // vertex array object
  auto cube_vao = std::make_shared<OpenGLVertexArray>();
  auto light_cube_vao = std::make_shared<OpenGLVertexArray>();
  // vertex buffer object
  auto vb = std::make_shared<OpenGLVertexBuffer>(vertices, sizeof(vertices));
  // index buffer object
  auto ib = std::make_shared<OpenGLIndexBuffer>(indices, 36);

  // specify layout in vertex buffer
  BufferLayout layout({{ShaderDataType::Float3, "position"},
                       {ShaderDataType::Float3, "normal"},
                       {ShaderDataType::Float2, "texture"}});
  vb->SetLayout(layout);

  cube_vao->AddVertexBuffer(vb);
  light_cube_vao->AddVertexBuffer(vb);
  cube_vao->SetIndexBuffer(ib);
  light_cube_vao->SetIndexBuffer(ib);

  OpenGLShader lightingShader("res/shaders/colors.shader");
  OpenGLShader lightCubeShader("res/shaders/lights.shader");
  glm::vec3 lightPos(1.0f, 0.5f, 0.2f);

  EditorCamera camera(30.0f, 1.333f, 0.1f, 1000.0f);
  while (m_Running) {
    renderer.Clear();
    renderer.SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

    // change the light's position values over time (can be done anywhere in
    // the render loop actually, but try to do it at least before using the
    // light source positions)
    lightPos.x = sin(glfwGetTime());
    lightPos.y = cos(glfwGetTime());

    glm::mat4 projection = camera.GetProjection();
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0, 0.0, 1.0));

    lightingShader.Bind();
    lightingShader.SetMat4("projection", projection);
    lightingShader.SetMat4("view", view);
    lightingShader.SetMat4("model", model);

    lightingShader.SetFloat3("light.position", lightPos);
    lightingShader.SetFloat3("viewPos", camera.GetPosition());

    // light properties
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    lightColor.x = sin(glfwGetTime() * 2.0f);
    lightColor.y = sin(glfwGetTime() * 0.7f);
    lightColor.z = sin(glfwGetTime() * 1.3f);
    glm::vec3 diffuseColor = lightColor * glm::vec3(1.0f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
    lightingShader.SetFloat3("light.ambient", ambientColor);
    lightingShader.SetFloat3("light.diffuse", diffuseColor);
    lightingShader.SetFloat3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    // material properties
    lightingShader.SetFloat("material.shininess", 32.0f);

    // light cube object
    lightCubeShader.Bind();
    lightCubeShader.SetMat4("projection", projection);
    lightCubeShader.SetMat4("view", view);
    lightCubeShader.SetFloat3("LightColor", lightColor);
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));  // a smaller cube
    lightCubeShader.SetMat4("model", model);

    lightingShader.Bind();
    lightingShader.SetInt("material.diffuse", 0);
    lightingShader.SetInt("material.specular", 1);
    OpenGLTexture2D tex("res/textures/container_diffuse.png");
    OpenGLTexture2D tex2("res/textures/container_specular.png");

    tex.Bind(0);
    tex2.Bind(1);
    renderer.DrawIndexed(cube_vao);

    lightCubeShader.Bind();
    renderer.DrawIndexed(light_cube_vao);

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
