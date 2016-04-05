#include "engine/renderer.hpp"

Renderer::Renderer(int w, int h)
{
  glGenFrameBuffers(1, &m_frameBuffer);
  glBindFrameBuffer(GL_FRAMEBUFFER, m_frameBuffer);

  glGenRenderBuffers(1, &m_depthBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, GAME_X, GAME_Y);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
}

Renderer::~Renderer()
{

}
