#pragma once

#include "Cazel/Core/Layer.h"
#include "Cazel/Events/ApplicationEvent.h"
#include "Cazel/Events/KeyEvent.h"
#include "Cazel/Events/MouseEvent.h"

namespace Cazel {
/// @brief 主要用于 Debug
class ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  virtual ~ImGuiLayer();

  virtual void OnAttach() override;
  virtual void OnImGuiRender() override;
  virtual void OnDetach() override;
  virtual void OnEvent(Event& e) override;

  void Begin();
  void End();

  void BlockEvents(bool block) { m_BlockEvents = block; }
  void SetDarkThemeColors();
  uint32_t GetActiveWidgetID() const;

 private:
  bool m_BlockEvents = true;
};
}  // namespace Cazel