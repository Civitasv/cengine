#include <iostream>

#include "Cazel.h"

class ExampleLayer : public Cazel::Layer {
 public:
  ExampleLayer() : Layer("Example") {}

  void OnUpdate() override { CZ_INFO("ExampleLayer::Update"); }

  void OnEvent(Cazel::Event& event) override {
    CZ_TRACE("{0}", event);
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
