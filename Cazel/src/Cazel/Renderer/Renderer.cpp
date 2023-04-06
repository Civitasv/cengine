#include "Cazel/Renderer/Renderer.h"

#include "czpch.h"

namespace Cazel {
void Renderer::Clear() const {
  GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1));
  GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const Shader& shader,
                    int count) const {
  shader.Bind();
  // I can just bind VAO, it will bind VBO and vertex layout and IBO for us.
  va.Bind();

  GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
}
}  // namespace Cazel