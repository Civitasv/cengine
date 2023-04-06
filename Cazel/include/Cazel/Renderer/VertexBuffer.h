#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "Log.h"
#include "glad/gl.h"

class VertexBuffer {
 private:
  unsigned int m_RendererID;

 public:
  VertexBuffer(const void* data, unsigned int size);

  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;
};