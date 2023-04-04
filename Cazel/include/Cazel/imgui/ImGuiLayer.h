#pragma once

#include "Cazel/Events/ApplicationEvent.h"
#include "Cazel/Events/KeyEvent.h"
#include "Cazel/Events/MouseEvent.h"
#include "Cazel/Layer.h"

namespace Cazel {
/// @brief 主要用于 Debug
class CAZEL_API ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  virtual ~ImGuiLayer();

  virtual void OnAttach() override;

  virtual void OnDetach() override;

  virtual void OnUpdate() override;

  virtual void OnEvent(Event& event) override;

 private:
  bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
  bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
  bool OnMouseMovedEvent(MouseMovedEvent& e);
  bool OnMouseScrolledEvent(MouseScrolledEvent& e);

  bool OnKeyPressedEvent(KeyPressedEvent& e);
  bool OnKeyReleasedEvent(KeyReleasedEvent& e);
  bool OnKeyTypedEvent(KeyTypedEvent& e);

  bool OnWindowResizeEvent(WindowResizeEvent& e);

 private:
  float m_Time = 0.0f;
};
}  // namespace Cazel