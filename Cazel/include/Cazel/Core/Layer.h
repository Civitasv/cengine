#pragma once

#include "Cazel/Core/Core.h"
#include "Cazel/Events/Event.h"

namespace Cazel {
/// @brief 图层类
class CAZEL_API Layer {
 public:
  Layer(const std::string& name = "Layer");
  virtual ~Layer();

  /// @brief 图层添加事件
  virtual void OnAttach() {}

  /// @brief 图层删除事件
  virtual void OnDetach() {}

  /// @brief 图层更新事件
  virtual void OnUpdate() {}

  /// @brief 图层相关事件
  /// @param event 事件处理
  virtual void OnEvent(Event& event) {}

  /// @brief 该图层要对 ImGui 图层做什么事情，比如在 ImGui 图层展示东西
  virtual void OnImGuiRender(){};

  /// @brief 获取图层名，用于 debug
  /// @return 图层名称
  inline const std::string& GetName() const { return m_DebugName; }

 private:
  std::string m_DebugName;
};
}  // namespace Cazel