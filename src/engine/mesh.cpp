#include "engine/mesh.hpp"
#include <vector>

#include <stdio.h>

Mesh::Mesh()
{
  m_vertexArrayObject = 0;
  m_temp = false;
}

Mesh::Mesh(Vertex* vertices, unsigned int nbVertices, unsigned int *indices, unsigned int nbIndices, bool temp)
{
  IndexedModel model;

  for (unsigned int i = 0; i < nbVertices; i++)
    {
      model.positions.push_back(*vertices[i].GetPos());
      model.texCoords.push_back(*vertices[i].GetTexCoord());
      model.normals.push_back(*vertices[i].GetNormal());
    }

  for (unsigned int i = 0; i < nbIndices; i++)
    model.indices.push_back(indices[i]);

  model.CalcNormals();
  InitMesh(model);
  m_temp = temp;
}

Mesh::~Mesh()
{
  if (!m_temp)
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::InitMesh(const IndexedModel& model)
{
  m_drawCount = model.indices.size();

  glGenVertexArrays(1, &m_vertexArrayObject);
  glBindVertexArray(m_vertexArrayObject);

  glGenBuffers(NB_BUFFERS, m_vertexArrayBuffers);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.positions.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
}

void Mesh::Draw()
{
  glBindVertexArray(m_vertexArrayObject);

  glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
  //  glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

  glBindVertexArray(0);
}

void IndexedModel::CalcNormals()
{
  for(unsigned int i = 0; i < indices.size(); i += 3)
    {
      int i0 = indices[i];
      int i1 = indices[i + 1];
      int i2 = indices[i + 2];

      glm::vec3 v1 = positions[i1] - positions[i0];
      glm::vec3 v2 = positions[i2] - positions[i0];

      glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

      normals[i0] += normal;
      normals[i1] += normal;
      normals[i2] += normal;
    }

  for(unsigned int i = 0; i < positions.size(); i++)
    normals[i] = glm::normalize(normals[i]);
}
