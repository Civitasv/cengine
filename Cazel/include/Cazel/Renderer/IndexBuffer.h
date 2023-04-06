#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include "Log.h"

class IndexBuffer {
 private:
  unsigned int m_RendererID;
  unsigned int m_Count;

 public:
  IndexBuffer(const unsigned int* data, unsigned int count);

  ~IndexBuffer();

  void Bind() const;
  void Unbind() const;

  inline unsigned int GetCount() { return m_Count; }
};