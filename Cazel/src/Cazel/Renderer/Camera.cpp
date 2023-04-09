#include "Cazel/Renderer/Camera.h"

#include "Cazel/Renderer/OrthographicCamera.h"
#include "Cazel/Renderer/PerspectiveCamera.h"
#include "czpch.h"

namespace Cazel {
#if CAZEL_DIMENSION == TWO_D
Camera::Type Camera::s_Type = Camera::Type::Two_D;
#else
Camera::Type Camera::s_Type = Camera::Type::Three_D;
#endif

Scope<Camera> Camera::Create(float a1, float a2, float a3, float a4) {
  switch (s_Type) {
    case Camera::Type::Two_D:
      return CreateScope<OrthographicCamera>(a1, a2, a3, a4);
    case Camera::Type::Three_D:
      return CreateScope<PerspectiveCamera>(a1, a2, a3, a4);
  }

  CZ_CORE_ASSERT(false, "Unknown Camera Type!");
  return nullptr;
}
}  // namespace Cazel