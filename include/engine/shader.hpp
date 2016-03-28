#ifndef SHADER_H
# define SHADER_H

# include <string>
# include <GL/glew.h>
# include "transform.hpp"
# include "camera.hpp"

# define NB_SHADERS 2

class	Shader
{
 public:
  Shader(const std::string& fileName);

  void Bind();
  void Update(const Transform& transform, Camera& camera);

  virtual ~Shader();
 protected:
 private:

enum
{
  TRANSFORM_U,
  //  LIGHT_U,

  NB_UNIFORMS
};

  GLuint	m_program;
  GLuint	m_shaders[NB_SHADERS];
  GLuint	m_uniforms[NB_UNIFORMS];
};

#endif // !SHADER_H
