#ifndef RENDERER_HPP_
# define RENDERER_HPP_

#include "engine/misc.hpp"

class Renderer
{
 public:
  Renderer(int w, int h);
  ~Renderer();
  void Bind(float bright);
  void Unbind();
  void Draw();
 private:
  GLuint m_frameBuffer;
  GLuint m_renderedTex;
  GLuint m_depthBuffer;
  GLuint m_drawVertices;
  int	 m_w;
  int	 m_h;
};

#endif // !RENDERER_HPP_
