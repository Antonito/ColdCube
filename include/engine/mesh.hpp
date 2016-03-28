#ifndef MESH_HPP_
# define MESH_HPP_

# include <glm/glm.hpp>
# include <GL/glew.h>
# include <vector>
# include <string>

using namespace glm;

class IndexedModel
{
public:
  std::vector<vec3> positions;
  std::vector<vec2> texCoords;
  std::vector<vec3> normals;
  std::vector<unsigned int> indices;

  void CalcNormals();
};

class Vertex
{
 public:
  Vertex()
  {
    m_pos = vec3(0, 0, 0);
    m_texCoord = vec2(0, 0);
    m_normal = vec3(0, 0, 0);
  }
  Vertex(const vec3& pos, const vec2& texCoord, const vec3 normal = vec3(0, 0, 0))
    {
      m_pos = pos;
      m_texCoord = texCoord;
      m_normal = normal;
    }

  inline vec3* GetPos() {return &m_pos;}
  inline vec2* GetTexCoord() {return &m_texCoord;}
  inline vec3* GetNormal() {return &m_normal;}
 private:
  vec3 m_pos;
  vec2 m_texCoord;
  vec3 m_normal;
};

class Mesh
{
 public:
  Mesh();
  Mesh(Vertex* vertices, unsigned int nbVertices, unsigned int *indices, unsigned int nbIndices, bool temp = false);

  void Draw();
  bool IsTemp() {return m_temp;}
  void Temp(bool t) {m_temp = t;}
  virtual ~Mesh();
 private:
  void InitMesh(const IndexedModel& model);
  bool	m_temp;

enum
{
  POSITION_VB,
  TEXCOORD_VB,
  NORMAL_VB,

  INDEX_VB,

  NB_BUFFERS
};

  GLuint m_vertexArrayObject;
  GLuint m_vertexArrayBuffers[NB_BUFFERS];
  unsigned int m_drawCount;
};

#endif // !MESH_HPP_
