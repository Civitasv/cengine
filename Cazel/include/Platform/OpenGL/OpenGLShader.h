#pragma once

#include <glm/glm.hpp>

#include "Cazel/Renderer/Shader.h"

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Cazel {
class OpenGLShader : public Shader {
 public:
  OpenGLShader(const std::string& filepath);

  /// string representation of vertex shader, fragment shader and geom shader.
  OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc,
               const std::string& geomSrc = nullptr);

  virtual ~OpenGLShader();

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual void SetInt(const std::string& name, int value) override;
  virtual void SetIntArray(const std::string& name, int* values,
                           uint32_t count) override;
  virtual void SetFloat(const std::string& name, float value) override;
  virtual void SetFloat2(const std::string& name,
                         const glm::vec2& value) override;
  virtual void SetFloat3(const std::string& name,
                         const glm::vec3& value) override;
  virtual void SetFloat4(const std::string& name,
                         const glm::vec4& value) override;
  virtual void SetMat4(const std::string& name,
                       const glm::mat4& value) override;

  void UploadUniformInt(const std::string& name, int value);
  void UploadUniformIntArray(const std::string& name, int* values,
                             uint32_t count);

  void UploadUniformFloat(const std::string& name, float value);
  void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
  void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
  void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

  void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
  void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

 private:
  std::string ReadFile(const std::string& filepath);
  std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

  void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

 private:
  uint32_t m_RendererID;
};
}  // namespace Cazel