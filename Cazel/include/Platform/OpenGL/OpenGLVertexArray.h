#pragma once

#include "Cazel/Renderer/VertexArray.h"

namespace Cazel {

class OpenGLVertexArray : public VertexArray {
 public:
  OpenGLVertexArray();
  virtual ~OpenGLVertexArray();

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
  virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

  virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const {
    return m_VertexBuffers;
  }
  virtual const Ref<IndexBuffer>& GetIndexBuffer() const {
    return m_IndexBuffer;
  }

 private:
  uint32_t m_RendererID;
  uint32_t m_VertexBufferIndex = 0;
  std::vector<Ref<VertexBuffer>>
      m_VertexBuffers;  ///< One VAO can handle multiple VBO
  Ref<IndexBuffer> m_IndexBuffer;
};

}  // namespace Cazel