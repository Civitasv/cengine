#include "Cazel/Renderer/Log.h"

#include <iostream>

void GLClearError() {
  while (glGetError())
    ;
}

bool GLLogCall(const char* function, const char* file, int line) {
  while (GLenum error = glGetError()) {
    CZ_CORE_ERROR("[OpenGL Error] ( {0} ): {1} {2}: {3}", error, function, file,
                  line);
    return false;
  }

  return true;
}