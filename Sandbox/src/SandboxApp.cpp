#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

#include "Cazel.h"
#include "Cazel/Core/EntryPoint.h"
#include "imgui.h"

using namespace Cazel;

class ExampleLayer : public Layer {
 private:
  Ref<Camera> camera;
  Ref<VertexArray> vao;
  Ref<VertexBuffer> vbo;
  Ref<IndexBuffer> ibo;
  Ref<Shader> shader;

  glm::vec3 camera_position;
  float camera_speed = 1.0f;  // 1m/s

 public:
  ExampleLayer() : Layer("Example"), camera_position(0.0f) {
    float vertices[] = {
        -0.5f, -0.5f,  // 1
        0.5f,  -0.5f,  // 2
        0.5f,  0.5f,   // 3
        -0.5f, 0.5f    // 4
    };

    uint32_t indices[] = {0, 1, 3, 1, 2, 3};

    BufferLayout layout = {{ShaderDataType::Float2, "Position"}};
    vbo = VertexBuffer::Create(vertices, sizeof(vertices));
    ibo = IndexBuffer::Create(indices, 6);
    vbo->SetLayout(layout);

    vao = VertexArray::Create();
    vao->AddVertexBuffer(vbo);
    vao->SetIndexBuffer(ibo);

    shader = Shader::Create("res/shaders/basic.shader");
    camera = Camera::Create(-1.0f, 1.0f, -1.0f, 1.0f);
  }

  virtual void OnUpdate(Timestep ts) override {
    // 这个会在每一帧执行，所以很丝滑，需要使用 deltaTime 机制
    // 从而保证，每秒移动的距离是一致的
    RenderCommand::Clear();
    RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

    if (Input::IsKeyPressed(CZ_KEY_W)) {
      camera_position.y -= camera_speed * ts;
    } else if (Input::IsKeyPressed(CZ_KEY_A)) {
      camera_position.x += camera_speed * ts;
    } else if (Input::IsKeyPressed(CZ_KEY_S)) {
      camera_position.y += camera_speed * ts;
    } else if (Input::IsKeyPressed(CZ_KEY_D)) {
      camera_position.x -= camera_speed * ts;
    }
    camera->SetPosition(camera_position);

    // Translate, Rotate, Scale
    Renderer::BeginScene(*camera);
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f),
                           glm::vec3(i * 0.11f, j * 0.11f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
        Renderer::Submit(shader, vao, transform);
      }
    }
    Renderer::EndScene();
  }

  virtual void OnEvent(Event& event) override {
    // 这个只会在事件发生时执行，所以没那么丝滑
  }

  virtual void OnImGuiRender() override {}
};

/// @brief Define Application.
class Sandbox : public Application {
 public:
  Sandbox() { PushLayer(new ExampleLayer()); }
  ~Sandbox() {}
};

/// @brief Create Application.
/// @return Application which will run.
Cazel::Application* Cazel::CreateApplication() { return new Sandbox(); }
