#pragma once

#include "Cazel/Core/Core.h"
#include "Cazel/Events/Event.h"
#include "Cazel/Renderer/Camera.h"
#include "czpch.h"

namespace Cazel {
/// @brief 窗口相关属性，包括名称、高度、宽度
struct WindowProps {
  std::string Title;
  unsigned int Width;
  unsigned int Height;

  WindowProps(const std::string title = "Cazel Engine",
              unsigned int width = 800, unsigned int height = 600)
      : Title(title), Width(width), Height(height) {}
};

/// @brief 窗口类
class CAZEL_API Window {
 public:
  using EventCallbackFn = std::function<void(Event&)>;

  virtual ~Window() {}
  virtual void OnUpdate() = 0;
  virtual unsigned int GetWidth() const = 0;
  virtual unsigned int GetHeight() const = 0;

  virtual float GetAspectRatio() const = 0;

  // 获取底层实现的不同平台的具体的 Window
  virtual void* GetNativeWindow() const = 0;

  // Window attr
  virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
  virtual void SetVSync(bool enabled) = 0;
  virtual bool IsVSync() const = 0;

  static Window* Create(const WindowProps& props = WindowProps());
};
}  // namespace Cazel