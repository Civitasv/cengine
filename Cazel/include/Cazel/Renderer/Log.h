#pragma once

#include "Cazel/Log.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

#ifndef CZ_DEBUG
#define GLCall(x) x
#else
#define GLCall(x) \
  GLClearError(); \
  x;              \
  CZ_CORE_ASSERT(GLLogCall(#x, __FILE__, __LINE__), "OpenGL ERROR");
#endif

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);