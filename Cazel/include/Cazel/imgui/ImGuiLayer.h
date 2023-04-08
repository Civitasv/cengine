#pragma once

#include "Cazel/Events/ApplicationEvent.h"
#include "Cazel/Events/KeyEvent.h"
#include "Cazel/Events/MouseEvent.h"
#include "Cazel/Core/Layer.h"

namespace Cazel {
/// @brief 主要用于 Debug
class CAZEL_API ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  virtual ~ImGuiLayer();

  virtual void OnAttach() override;

  virtual void OnDetach() override;

  virtual void OnImGuiRender() override;

  void Begin();

  void End();

 private:
  float m_Time = 0.0f;
};
}  // namespace Cazel