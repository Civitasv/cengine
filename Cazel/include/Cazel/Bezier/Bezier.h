#pragma once

#include <glm/glm.hpp>

namespace Cazel {
struct Bezier {
  static glm::vec2 Linear(const glm::vec2& p0, const glm::vec2& p1,
                          float delta) {
    float x = p0.x + delta * (p1.x - p0.x);
    float y = p0.y + delta * (p1.y - p0.y);

    return {x, y};
  }

  static glm::vec2 Quadratic(const glm::vec2& p0, const glm::vec2& p1,
                             const glm::vec2& p2, float delta) {
    glm::vec2 v1 = Linear(p0, p1, delta);
    glm::vec2 v2 = Linear(p1, p2, delta);

    return Linear(v1, v2, delta);
  }

  static glm::vec2 Cubic(const glm::vec2& p0, const glm::vec2& p1,
                         const glm::vec2& p2, const glm::vec2& p3,
                         float delta) {
    glm::vec2 v1 = Quadratic(p0, p1, p2, delta);
    glm::vec2 v2 = Quadratic(p1, p2, p3, delta);

    return Linear(v1, v2, delta);
  }
};
}  // namespace Cazel