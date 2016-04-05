#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include <math.h>
# include <stdio.h>
# include <OVR.h>
# include <iostream>
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

      ovr_Initialize(0);
      hmd = ovrHmd_Create(0);
      if (hmd)
	ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0);
    }
  ~Camera()
    {
      if (hmd)
	ovrHmd_Destroy(hmd);
    }

  inline mat4 GetViewProjection() const
  {
    return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
  }

  int isOculus() {return hmd ? 1 : 0;}

  vec3 &GetPos() {return m_position;}
  void UpdateFor()
  {
    ovrPosef pose[2];
    vec2     finalRot = m_rotation;
    //m_rotation[0] = pose[0].Orientation.x * 90;
    if (hmd) {
      pose[0] = ovrHmd_GetHmdPosePerEye(hmd, hmd->EyeRenderOrder[0]);
      pose[1] = ovrHmd_GetHmdPosePerEye(hmd, hmd->EyeRenderOrder[1]);
      // if (pose[0].Orientation.x >= 0.5)
      // 	pose[0].Orientation.x = 0.499;
      finalRot.x -= pose[0].Orientation.x * 90.0 * 2;
      finalRot.y -= pose[0].Orientation.y * 90.0 * 2;
      if (finalRot.x > 89.99)
	finalRot.x = 89.99;
      if (finalRot.x < -89.99)
	finalRot.x = -89.99;
    }

    vec4	forward(0, 1, 0, 0);
    mat4	rz = glm::rotate((GLfloat)(finalRot.y * M_PI / 180), vec3(0, 0, 1));
    vec3	axis(rz * vec4(1, 0, 0, 0));
    mat4	rx = glm::rotate((GLfloat)(finalRot.x * M_PI / 180), axis);
    vec3	res(rx * rz * forward);
    m_forward = normalize(res);
  }
  vec3 &GetFor() {return m_forward;}

  vec2 &GetRot() {
    return m_rotation;
  }

 protected:
 private:
  mat4 m_perspective;
  vec3 m_forward;
  vec3 m_position;
  vec2 m_rotation;
  vec3 m_up;
  ovrHmd hmd;
};

#endif // !CAMERA_HPP_
