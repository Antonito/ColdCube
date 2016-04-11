#include "engine/texture.hpp"
#include <cassert>
#include <iostream>

Texture::Texture()
{
  m_texture = 0;
  m_temp = true;
}

Texture::Texture(const unsigned char *imgData, int width, int height, bool temp)
{
  if (imgData == NULL)
    {
      std::cerr << "Invalid image data: aborting" << std::endl;
      exit(1);
    }
  m_temp = temp;
  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
  glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
}

Texture::Texture(SDL_Surface *surface)
{
  if (surface == NULL)
    {
      std::cerr << "Invalid SDL_Surface: aborting" << std::endl;
      exit(1);
    }
  m_temp = false;
  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
  glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

  int	mode = GL_RGB;

  if (surface->format->BytesPerPixel == 4)
    mode = GL_RGBA;

  glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
}

Texture::~Texture()
{
  if (m_texture && !m_temp)
    glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit)
{
  assert(unit <= 31);

  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, m_texture);
}
