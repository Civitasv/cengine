#include "Cazel/Renderer/Texture.h"

#include "stb_image.h"

Texture::Texture(const std::string& path)
    : m_RendererID(0),
      m_FilePath(path),
      m_LocalBuffer(nullptr),
      m_Width(0),
      m_Height(0),
      m_BPP(0) {
  GLCall(glGenTextures(1, &m_RendererID));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                         GL_LINEAR_MIPMAP_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  stbi_set_flip_vertically_on_load(1);
  m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

  if (m_LocalBuffer) {
    GLenum format;
    if (m_BPP == 1)
      format = GL_RED;
    else if (m_BPP == 3)
      format = GL_RGB;
    else if (m_BPP == 4)
      format = GL_RGBA;

    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format,
                        GL_UNSIGNED_BYTE, m_LocalBuffer));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    stbi_image_free(m_LocalBuffer);
  } else {
    CZ_CORE_ERROR("Failed to load texture");
  }
}

Texture::~Texture() { GLCall(glDeleteTextures(1, &m_RendererID)); }

void Texture::Bind(unsigned int slot) const {
  GLCall(glActiveTexture(GL_TEXTURE0 + slot));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() { GLCall(glBindTexture(GL_TEXTURE_2D, 0)); }