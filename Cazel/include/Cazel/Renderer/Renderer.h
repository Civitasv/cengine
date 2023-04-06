#pragma once

#include "Shader.h"
#include "VertexArray.h"

namespace Cazel {
/// @brief This is platform agnostic.
class Renderer {
 private:
 public:
  void Clear() const;
  void Draw(const VertexArray& va, const Shader& shader, int count) const;
};
}  // namespace Cazel