#pragma once

#include "Log.h"
#include "czpch.h"
#include "glm/glm.hpp"

struct ShaderProgramSource {
  std::string VertexSource;    ///< operate on each vertex
  std::string FragmentSource;  /// < operare on each pixel
};

class Shader {
 private:
  std::string m_Filepath;
  unsigned int m_RendererID;
  // caching for uniforms
  std::unordered_map<std::string, int> m_UniformLocationCache;

 public:
  Shader(const std::string& filepath);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  // Set uniforms
  void SetUniform3f(const std::string& name, float v0, float v1, float v2);
  void SetUniform4f(const std::string& name, float v0, float v1, float v2,
                    float v3);
  void SetUniform1i(const std::string& name, int value);
  void SetUniform1f(const std::string& name, float value);
  void SetUniformVec3f(const std::string& name, const glm::vec3& vec);
  void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

 private:
  int GetUniformLocation(const std::string& name);
  unsigned int CompileShader(unsigned int type, const std::string& source);
  unsigned int CreateShader(const std::string& vertexShader,
                            const std::string& fragmentShader);
  ShaderProgramSource ParseShader(const std::string& filepath);
};