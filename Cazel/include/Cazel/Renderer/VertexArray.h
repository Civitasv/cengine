#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "Log.h"
#include "glad/gl.h"

class VertexArray {
 private:
  unsigned int m_RendererID;

 public:
  VertexArray();
  ~VertexArray();

  void AddBuffer(const VertexBuffer& vb, const IndexBuffer& ib,
                 const VertexBufferLayout& layout);

  void Bind() const;
  void Unbind() const;
};