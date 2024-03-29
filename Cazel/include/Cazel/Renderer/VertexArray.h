#pragma once

#include <memory>

#include "Buffer.h"

namespace Cazel {
/// @brief The VertexArray contains the reference to VertexBuffer
/// and IndexBuffer, the actual data is stored in VertexBuffer
/// and IndexBuffer.
class VertexArray {
 private:
  unsigned int m_RendererID;

 public:
  virtual ~VertexArray() = default;

  virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
  virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

  virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
  virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

  static Ref<VertexArray> Create();

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
};
}  // namespace Cazel