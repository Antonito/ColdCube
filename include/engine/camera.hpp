#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include <math.h>
# include <stdio.h>
# include "engine/misc.hpp"

using namespace glm;

class Camera
{
 public:
  Camera(const vec3& pos, float fov, float aspect, float zNear, float zFar)
    {
      m_perspective = glm::perspective(fov, aspect, zNear, zFar);
      m_position = pos;
      m_rotation = vec2(0, 0);
      m_up = vec3(0, 0, 1);
    }

  inline mat4 GetViewProjection() const
  {
    return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
  }

  vec3 &GetPos() {return m_position;}
  void UpdateFor()
  {
    vec4	forward(0, 1, 0, 0);
    mat4	rz = glm::rotate((typeof(m_rotation.y))(m_rotation.y * M_PI / 180), vec3(0, 0, 1));
    vec3	axis(rz * vec4(1, 0, 0, 0));
    mat4	rx = glm::rotate((typeof(m_rotation.x))(m_rotation.x * M_PI / 180), axis);

    vec3	res(rx * rz * forward);
    m_forward = normalize(res);
  }
  vec3 &GetFor() {return m_forward;}
  vec2 &GetRot() {return m_rotation;}

 protected:
 private:
  mat4 m_perspective;
  vec3 m_forward;
  vec3 m_position;
  vec2 m_rotation;
  vec3 m_up;
};

#endif // !CAMERA_HPP_
