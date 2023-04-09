#pragma once

#include "Cazel/Core/Core.h"
#include "glm/glm.hpp"

namespace Cazel {
class Camera {
 public:
  enum class Type { Two_D = 0, Three_D };

 public:
  Camera() = default;
  Camera(const glm::mat4& projection, const glm::mat4& view)
      : m_ProjectionMatrix(projection), m_ViewMatrix(view) {}

  virtual ~Camera() = default;

  const glm::vec3& GetPosition() const { return m_Position; }
  const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
  const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
  const glm::mat4& GetViewProjectionMatrix() const {
    return m_ViewProjectionMatrix;
  }

  static Scope<Camera> Create(float a1, float a2, float a3, float a4);

 protected:
  glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
  glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
  glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
  glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);

 private:
  static Type s_Type;
};
}  // namespace Cazel