#include "Cazel/Renderer/VertexArray.h"
#include "Cazel/Renderer/IndexBuffer.h"

VertexArray::VertexArray() { GLCall(glGenVertexArrays(1, &m_RendererID)); }

VertexArray::~VertexArray() { GLCall(glDeleteVertexArrays(1, &m_RendererID)); }

void VertexArray::AddBuffer(const VertexBuffer& vb, const IndexBuffer& ib,
                            const VertexBufferLayout& layout) {
  Bind();
  vb.Bind();
  ib.Bind();

  const auto& elements = layout.GetElements();
  unsigned int offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++) {
    GLCall(glEnableVertexAttribArray(i));
    // index: index of this attribute
    // size: the number of components of this attribute
    // stride: byte offset between two attributes
    // pointer: first location of this attribute
    GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type,
                                 elements[i].normalized, layout.GetStride(),
                                 (const void*)offset));
    offset += elements[i].count *
              VertexBufferElement::GetSizeOfType(elements[i].type);
  }
}

void VertexArray::Bind() const { GLCall(glBindVertexArray(m_RendererID)); }

void VertexArray::Unbind() const { GLCall(glBindVertexArray(0)); }
