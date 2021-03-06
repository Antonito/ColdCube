#include "engine/shader.hpp"
#include <fstream>
#include <iostream>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);


Shader::Shader(const std::string& fileName)
{
  m_program = glCreateProgram();
  m_shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
  m_shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

  for (unsigned int i = 0; i < NB_SHADERS; i++)
    glAttachShader(m_program, m_shaders[i]);

  glBindAttribLocation(m_program, 0, "position");
  glBindAttribLocation(m_program, 1, "texCoord");
  glBindAttribLocation(m_program, 2, "normal");

  glLinkProgram(m_program);
  CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

  glValidateProgram(m_program);
  CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

  m_uniforms[0] = glGetUniformLocation(m_program, "transform");
  m_uniforms[1] = glGetUniformLocation(m_program, "shadow_mat");
  m_uniforms[2] = glGetUniformLocation(m_program, "light");
  m_uniforms[3] = glGetUniformLocation(m_program, "mvp");
}

Shader::~Shader()
{
  for (unsigned int i = 0; i < NB_SHADERS; i++)
    {
      glDetachShader(m_program, m_shaders[i]);
      glDeleteShader(m_shaders[i]);
    }

  glDeleteProgram(m_program);
}

void	Shader::Bind()
{
  glUseProgram(m_program);
}

void	Shader::Update(const Transform& transform, Camera& camera)
{
  glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
  glUniformMatrix4fv(m_uniforms[SHADOW_MAT_U], 1, GL_FALSE, &transform.GetModel()[0][0]);
  glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
  //  glUniform4fv(m_uniforms[1], 120, lights);
}

void	Shader::Update(const Transform& transform, Camera& camera, vec3 *light)
{
  glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

  glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
  glUniformMatrix4fv(m_uniforms[SHADOW_MAT_U], 1, GL_FALSE, &transform.GetModel()[0][0]);
  glUniform4f(m_uniforms[LIGHT_U], light->x, light->y, light->z, 1.0);
  glUniformMatrix4fv(m_uniforms[MVP_U], 1, GL_FALSE, &camera.GetViewProjection()[0][0]);
  //  glUniform4fv(m_uniforms[1], 120, lights);
}

void	Shader::Update(const glm::mat4& transform, Camera& camera)
{
  glm::mat4 model = camera.GetViewProjection() * transform;

  glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
  glUniformMatrix4fv(m_uniforms[SHADOW_MAT_U], 1, GL_FALSE, &transform[0][0]);
  //  glUniform4fv(m_uniforms[1], 120, lights);
}

void	Shader::Update(const glm::mat4& transform, const glm::mat4& persp)
{
  glm::mat4 model = persp * transform;

  glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
  glUniformMatrix4fv(m_uniforms[SHADOW_MAT_U], 1, GL_FALSE, &transform[0][0]);
  //  glUniform4fv(m_uniforms[1], 120, lights);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
  GLuint shader = glCreateShader(shaderType);

  if (shader == 0)
    {
      std::cerr << "Error: shader creation failed!" << std::endl;
      exit(1);
    }

  const GLchar* shaderSourceStrings[1];
  GLint		len[1];
  shaderSourceStrings[0] = text.c_str();
  len[0] = text.length();

  glShaderSource(shader, 1, shaderSourceStrings, len);
  glCompileShader(shader);
  CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

  return (shader);
}

static std::string LoadShader(const std::string& fileName)
{
  std::ifstream	file;
  file.open((fileName).c_str());

  std::string output;
  std::string line;

  if (file.is_open())
    {
      while (file.good())
	{
	  getline(file, line);
	  output.append(line + "\n");
	}
    }
  else
    {
      std::cerr << "Unable to load shader" << std::endl;
      exit(1);
    }

  return (output);
}

static		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
  GLint		success = 0;
  GLchar	error[1024] = {0};

  if (isProgram)
    glGetProgramiv(shader, flag, &success);
  else
    glGetShaderiv(shader, flag, &success);

  if (success == GL_FALSE)
    {
      if (isProgram)
	glGetProgramInfoLog(shader, sizeof(error), NULL, error);
      else
	glGetShaderInfoLog(shader, sizeof(error), NULL, error);

      std::cerr << errorMessage << ": '" << error << "'" << std::endl;
      exit(1);
    }
}
