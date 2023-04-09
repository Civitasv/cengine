#pragma once

#include "Camera.h"
#include "glm/glm.hpp"

namespace Cazel {
class OrthographicCamera : public Camera {
 public:
  OrthographicCamera(float left, float right, float bottom, float top);

  void SetProjection(float left, float right, float bottom, float top);

  void SetPosition(const glm::vec3& position) override {
    m_Position = position;
    RecalculateViewMatrix();
  }

  float GetRotation() const { return m_Rotation; }
  void SetRotation(float rotation) override {
    m_Rotation = rotation;
    RecalculateViewMatrix();
  }

 private:
  void RecalculateViewMatrix();

 private:
  float m_Rotation = 0.0f;
};
}  // namespace Cazel