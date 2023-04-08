#pragma once

#include "Cazel/Renderer/GraphicsContext.h"
#include "Cazel/Core/Window.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

namespace Cazel {
class WindowsWindow : public Window {
 public:
  WindowsWindow(const WindowProps &props);
  virtual ~WindowsWindow();

  virtual void OnUpdate() override;

  virtual inline unsigned int GetWidth() const override { return m_Data.Width; }
  virtual inline unsigned int GetHeight() const override {
    return m_Data.Height;
  }

  // Window attributes
  virtual inline void SetEventCallback(
      const EventCallbackFn &callback) override {
    m_Data.EventCallback = callback;
  }
  virtual void SetVSync(bool enabled) override;
  virtual bool IsVSync() const override;
  virtual void *GetNativeWindow() const override { return m_Window; }

 private:
  virtual void Init(const WindowProps &props);
  virtual void Shutdown();

 private:
  GLFWwindow *m_Window;
  GraphicsContext *m_Context;  ///< render context

  struct WindowData {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;
    float DeltaTime;
    EventCallbackFn EventCallback;
  };

  WindowData m_Data;
};
};  // namespace Cazel
