#ifndef RENDERER_HPP_
# define RENDERER_HPP_

#include "engine/misc.hpp"

Class Renderer
{
 public:
  Renderer(int w, int h);
  ~Renderer();
 private:
  GLuint m_frameBuffer;
  GLuint m_depthBuffer;
};

#endif // !RENDERER_HPP_
