#pragma once

namespace Cazel {
class GraphicsContext {
 public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
};
}  // namespace Cazel