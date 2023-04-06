#pragma once
#include <vector>

#include "Log.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

struct VertexBufferElement {
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static unsigned int GetSizeOfType(unsigned int type) {
    switch (type) {
      case GL_FLOAT:
        return 4;
        break;
      case GL_UNSIGNED_INT:
        return 4;
        break;
      case GL_UNSIGNED_BYTE:
        return 1;
        break;
    }
    CZ_CORE_ASSERT(false, "Type not allowed!");
    return 0;
  }
};

class VertexBufferLayout {
 private:
  std::vector<VertexBufferElement> m_Elements;
  unsigned int m_Stride;  ///< 步幅

 public:
  VertexBufferLayout() : m_Stride(0) {}

  template <typename T>
  void Push(unsigned int count) {}

  template <>
  void Push<float>(unsigned int count) {
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
  }

  template <>
  void Push<unsigned int>(unsigned int count) {
    m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
  }

  template <>
  void Push<unsigned char>(unsigned int count) {
    m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
  }

  inline std::vector<VertexBufferElement> GetElements() const {
    return m_Elements;
  }

  inline unsigned int GetStride() const { return m_Stride; }
};