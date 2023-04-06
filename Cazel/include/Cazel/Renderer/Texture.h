#pragma once

#include "Log.h"
#include "czpch.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

class Texture {
 private:
  unsigned int m_RendererID;
  std::string m_FilePath;

  unsigned char* m_LocalBuffer;
  int m_Width, m_Height, m_BPP;  // bytes per pixel, rgba -> 4byte

 public:
  Texture(const std::string& path);
  ~Texture();

  void Bind(unsigned int slot = 0) const;
  void Unbind();

  inline int GetWidth() const { return m_Width; }
  inline int GetHeight() const { return m_Height; }
};