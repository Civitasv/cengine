#pragma once

namespace Cazel {
/// @brief This is platform agnostic.
class GraphicsContext {
 public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
};
}  // namespace Cazel