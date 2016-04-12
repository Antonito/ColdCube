#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include "engine/misc.hpp"
# include <math.h>
# include <stdio.h>
# include <OVR.h>
# include <iostream>

using namespace glm;

class Camera
{
 public:
  Camera(const vec3& pos, float fov, float aspect, float zNear, float zFar, ovrHmd oculusHmd, bool oculus)
    {
      fov *= M_PI / 180.0f;
      if (oculus)
	m_perspective = perspective(fov * 1.5f, 1.0f, zNear, zFar);
      else
	m_perspective = perspective(fov, aspect, zNear, zFar);
      m_aspect = aspect;
      m_zNear = zNear;
      m_zFar = zFar;
      m_position = pos;
      m_rotation = vec2(0, 0);
      m_up = vec3(0, 0, 1);
      m_hmd = oculusHmd;
      m_oculus = oculus;
    }
  ~Camera()
    {
    }

  inline mat4 GetViewProjection() const
  {
    return m_perspective * lookAt(m_position, m_position + m_forward, m_up);
  }
  inline mat4 GetPerspective() const
  {
    return m_perspective;
  }
  bool isOculus() {return m_hmd ? true : false;}
  void SetFov(float fov)
  {
      fov *= M_PI / 180.0f;
      if (m_oculus)
	m_perspective = perspective(fov * 1.5f, 1.0f, m_zNear, m_zFar);
      else
	m_perspective = perspective(fov, m_aspect, m_zNear, m_zFar);
  }

  vec3 &GetPos() {return m_position;}
  void UpdateFor()
  {
    vec4	forward(0, 1, 0, 0);
    mat4	rz = rotate((GLfloat)(m_rotation.y * M_PI / 180), vec3(0, 0, 1));
    vec3	axis(rz * vec4(1, 0, 0, 0));
    mat4	rx = rotate((GLfloat)(m_rotation.x * M_PI / 180), axis);
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
  float m_aspect;
  float m_zNear;
  float m_zFar;
  ovrHmd m_hmd;
  bool m_oculus;
};

#endif // !CAMERA_HPP_
