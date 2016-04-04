#ifndef MISC_HPP_
# define MISC_HPP_

# include <ctime>
# include <GL/glew.h>
# include <GL/gl.h>
# include <glm/glm.hpp>
//# include <glm/gtx/transform.hpp>


# define OFFSET(TYPE, MEMBER) (((TYPE)NULL).MEMBER)
# define FALL_SPEED 1.0f
# define JUMP_SPEED 2.0f

int    launch_app();

// int	g_WinWidth = 1280;
// int	g_WinHeight = 720;
// int	g_WinHandle = 0;
// int	g_Z, g_Q, g_S, g_D, g_A, g_E;
// bool	g_Shift = false;

// GLuint	g_VAO = 0;
// GLint	g_uniformMVP = -1;

// glm::ivec2 g_MousePos;
// glm::quat g_Rotation;

// std::clock_t	g_PreviousTick;
// std::clock_t	g_CurrentTick;

// Camera		g_Camera;
// glm::vec3	g_InitialCameraPosition;
// glm::quat	g_InitialCameraRotation;

#endif // !MISC_HPP_
