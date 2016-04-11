#ifndef TEXTURE_HPP_
# define TEXTURE_HPP_

# include <string>
# include "engine/misc.hpp"

class	Texture
{
 public:
  Texture();
  Texture(const unsigned char *imgData, int width, int height, bool temp = false);
  Texture(SDL_Surface *surface);

  void	Bind(unsigned int unit);
  GLuint	GetTexture() {return m_texture;}
  void		Temp(bool t) {m_temp = t;}
  virtual ~Texture();
 protected:
 private:
  GLuint	m_texture;
  bool		m_temp;
};

#endif // !TEXTURE_HPP_
