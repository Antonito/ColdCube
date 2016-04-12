#include "engine/misc.hpp"
#include "engine/renderer.hpp"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>

#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9

#include <stdio.h>
using namespace std;
Renderer::Renderer(int w, int h)
{
  m_w = w;
  m_h = h;


	/* Texture */
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_renderedTex);
	glBindTexture(GL_TEXTURE_2D, m_renderedTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	/* Depth buffer */
	glGenRenderbuffers(1, &m_depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, w, h);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	/* Framebuffer to link everything together */
	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_renderedTex, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
	GLenum status;
	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) {
		cerr << "glCheckFramebufferStatus: error 0x" << hex << status << endl;
		switch (status) {
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			cerr << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
			cerr << "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS" << endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			cerr << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << endl;
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			cerr << "GL_FRAMEBUFFER_UNSUPPORTED" << endl;
			break;
		}
		return ;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLfloat fbo_vertices[] = {
	  -1, -1, 1,
	  1, -1, 1,
	  -1,  1, 1,
	  1,  1, 1,
	};
	glGenBuffers(1, &m_drawVertices);
	glBindBuffer(GL_ARRAY_BUFFER, m_drawVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_vertices), fbo_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Renderer::~Renderer()
{
  glDeleteRenderbuffers(1, &m_depthBuffer);
  glDeleteTextures(1, &m_renderedTex);
  glDeleteFramebuffers(1, &m_frameBuffer);
}

void	Renderer::Bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
  glClearColor(0.0f, 0.3f, 0.8f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	Renderer::Unbind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void	Renderer::Draw()
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, m_renderedTex);

  glBegin(GL_QUADS);
  glTexCoord2i(0, 0);
  glVertex3f(-1, -1, 0);
  glTexCoord2i(0, 1);
  glVertex3f(-1, 1, 0);
  glTexCoord2i(1, 1);
  glVertex3f(1, 1, 0);
  glTexCoord2i(1, 0);
  glVertex3f(1, -1, 0);
  glEnd();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glCullFace(GL_BACK);
}
