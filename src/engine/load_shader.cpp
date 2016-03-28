#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <string.h>

int LoadShader(const char *fileName, char **src, int *len)
{
  std::ifstream file;
  file.open(fileName);

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
    return (1);
  *src = strdup(output.c_str());
  *len = output.length();
  return (0);
}

void UnloadShader(GLchar** ShaderSource)
{
  if (*ShaderSource != NULL)
    delete[] *ShaderSource;
  *ShaderSource = NULL;
}
