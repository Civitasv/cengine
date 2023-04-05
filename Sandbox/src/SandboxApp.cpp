#include <iostream>

#include "Cazel.h"
#include "imgui.h"

class ExampleLayer : public Cazel::Layer {
 public:
  ExampleLayer() : Layer("Example") {}

  virtual void OnUpdate() override {
    CZ_INFO("ExampleLayer::Update");
  }

  virtual void OnEvent(Cazel::Event& event) override { CZ_TRACE("{0}", event); }

  virtual void OnImGuiRender() override {
    ImGui::Begin("Test");
    ImGui::Text("Hello World");
    ImGui::End();
  }
};

/// @brief Define Application.
class Sandbox : public Cazel::Application {
 public:
  Sandbox() { PushLayer(new ExampleLayer()); }
  ~Sandbox() {}
};

/// @brief Create Application.
/// @return Application which will run.
Cazel::Application* Cazel::CreateApplication() { return new Sandbox(); }
