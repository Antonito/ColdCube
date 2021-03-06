#ifndef SHADER_H
# define SHADER_H

# include <string>
# include "transform.hpp"
# include "camera.hpp"

# define NB_SHADERS 2

class	Shader
{
 public:
  Shader(const std::string& fileName);

  void Bind();
  void SetBright(float bright);
  void Update(const Transform& transform, Camera& camera);
  void Update(const Transform& transform, Camera& camera, vec3 *light);
  void Update(const glm::mat4& transform, Camera& camera);
  void Update(const glm::mat4& transform, const glm::mat4& persp);

  virtual ~Shader();
 protected:
 private:

enum
{
  TRANSFORM_U,
  SHADOW_MAT_U,
  LIGHT_U,
  MVP_U,

  NB_UNIFORMS
};

  GLuint	m_program;
  GLuint	m_shaders[NB_SHADERS];
  GLuint	m_uniforms[NB_UNIFORMS];
};

#endif // !SHADER_H
