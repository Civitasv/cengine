#pragma once

#include "Cazel/Core.h"
#include "Cazel/Layer.h"

namespace Cazel {
/// @brief 图层组
class CAZEL_API LayerStack {
 public:
  LayerStack();

  ~LayerStack();

  /// @brief 添加图层
  /// @param layer 图层，@see {Layer}
  void PushLayer(Layer* layer);

  /// @brief 添加遮罩
  /// @param overlay 遮罩，@see {Layer}
  void PushOverlay(Layer* overlay);

  /// @brief 删除图层
  /// @param layer 图层，@see {Layer}
  void PopLayer(Layer* layer);

  /// @brief 删除遮罩
  /// @param overlay 遮罩，@see {Layer}
  void PopOverlay(Layer* overlay);

  std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
  std::vector<Layer*>::iterator end() { return m_Layers.end(); }

 private:
  std::vector<Layer*> m_Layers;
  std::vector<Layer*>::iterator m_LayerInsert;
};
}  // namespace Cazel