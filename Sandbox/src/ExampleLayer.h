#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Cazel.h"
#include "imgui.h"

class ExampleLayer : public Cazel::Layer {
 private:
  Cazel::Ref<Cazel::Camera> camera;
  Cazel::Ref<Cazel::VertexArray> vao;
  Cazel::Ref<Cazel::VertexBuffer> vbo;
  Cazel::Ref<Cazel::IndexBuffer> ibo;
  Cazel::Ref<Cazel::Shader> shader;

  glm::vec3 camera_position;
  float camera_speed = 1.0f;  // 1m/s

 public:
  ExampleLayer() : Cazel::Layer("Example"), camera_position(0.0f) {
    float vertices[] = {
        -0.5f, -0.5f,  // 1
        0.5f,  -0.5f,  // 2
        0.5f,  0.5f,   // 3
        -0.5f, 0.5f    // 4
    };

    uint32_t indices[] = {0, 1, 3, 1, 2, 3};

    Cazel::BufferLayout layout = {{Cazel::ShaderDataType::Float2, "Position"}};
    vbo = Cazel::VertexBuffer::Create(vertices, sizeof(vertices));
    ibo = Cazel::IndexBuffer::Create(indices, 6);
    vbo->SetLayout(layout);

    vao = Cazel::VertexArray::Create();
    vao->AddVertexBuffer(vbo);
    vao->SetIndexBuffer(ibo);

    shader = Cazel::Shader::Create("res/shaders/basic.shader");
    camera = Cazel::Camera::Create(-1.0f, 1.0f, -1.0f, 1.0f);
  }

  virtual void OnUpdate(Cazel::Timestep ts) override {
    // 这个会在每一帧执行，所以很丝滑，需要使用 deltaTime 机制
    // 从而保证，每秒移动的距离是一致的
    Cazel::RenderCommand::Clear();
    Cazel::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

    if (Cazel::Input::IsKeyPressed(Cazel::Key::W)) {
      camera_position.y -= camera_speed * ts;
    } else if (Cazel::Input::IsKeyPressed(Cazel::Key::A)) {
      camera_position.x += camera_speed * ts;
    } else if (Cazel::Input::IsKeyPressed(Cazel::Key::S)) {
      camera_position.y += camera_speed * ts;
    } else if (Cazel::Input::IsKeyPressed(Cazel::Key::D)) {
      camera_position.x -= camera_speed * ts;
    }
    camera->SetPosition(camera_position);

    // Translate, Rotate, Scale
    Cazel::Renderer::BeginScene(*camera);
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f),
                           glm::vec3(i * 0.11f, j * 0.11f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
        Cazel::Renderer::Submit(shader, vao, transform);
      }
    }
    Cazel::Renderer::EndScene();
  }

  virtual void OnEvent(Cazel::Event& event) override {
    // 这个只会在事件发生时执行，所以没那么丝滑
  }

  virtual void OnImGuiRender() override {}
};