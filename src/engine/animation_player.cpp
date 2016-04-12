#include <SDL2/SDL.h>
#include "engine/mesh.hpp"
#include "engine/animation_player.hpp"
#include "engine/texture.hpp"

static Mesh* GetBody()
{
  static Mesh* body = NULL;

  if (!body)
    {
      Vertex	v[] = {Vertex(vec3(-0.18, 0.1, -0.3), vec2(0, 0)),
		       Vertex(vec3(-0.18, -0.1, -0.3), vec2(0, 1)),
		       Vertex(vec3(0.18, -0.1, -0.3), vec2(1, 1)),
		       Vertex(vec3(0.18, 0.1, -0.3), vec2(1, 0)),
		       // BOT FACE

		       Vertex(vec3(-0.18, -0.1, 0.3), vec2(0, 0)),
		       Vertex(vec3(-0.18, 0.1, 0.3), vec2(0, 1)),
		       Vertex(vec3(0.18, 0.1, 0.3), vec2(1, 1)),
		       Vertex(vec3(0.18, -0.1, 0.3), vec2(1, 0)),
		       // TOP FACE

		       Vertex(vec3(-0.18, -0.1, -0.3), vec2(0, 0)),
		       Vertex(vec3(-0.18, -0.1, 0.3), vec2(0, 1)),
		       Vertex(vec3(0.18, -0.1, 0.3), vec2(1, 1)),
		       Vertex(vec3(0.18, -0.1, -0.3), vec2(1, 0)),
		       // FRONT FACE

		       Vertex(vec3(-0.18, 0.1, 0.3), vec2(0, 0)),
		       Vertex(vec3(-0.18, 0.1, -0.3), vec2(0, 1)),
		       Vertex(vec3(0.18, 0.1, -0.3), vec2(1, 1)),
		       Vertex(vec3(0.18, 0.1, 0.3), vec2(1, 0)),
		       // BACK FACE

		       Vertex(vec3(-0.18, -0.1, -0.3), vec2(0, 0)),
		       Vertex(vec3(-0.18, 0.1, -0.3), vec2(0, 1)),
		       Vertex(vec3(-0.18, 0.1, 0.3), vec2(1, 1)),
		       Vertex(vec3(-0.18, -0.1, 0.3), vec2(1, 0)),
		       // RIGHT FACE

		       Vertex(vec3(0.18, 0.1, -0.3), vec2(0, 0)),
		       Vertex(vec3(0.18, -0.1, -0.3), vec2(0, 1)),
		       Vertex(vec3(0.18, -0.1, 0.3), vec2(1, 1)),
		       Vertex(vec3(0.18, 0.1, 0.3), vec2(1, 0))
		       // LEFT FACE
      };
      unsigned int	i[36];
      int		j = 0;

      while (j < 6)
	{
	  i[6 * j] = 4 * j;
	  i[6 * j + 1] = 4 * j + 2;
	  i[6 * j + 2] = 4 * j + 1;
	  i[6 * j + 3] = 4 * j;
	  i[6 * j + 4] = 4 * j + 3;
	  i[6 * j + 5] = 4 * j + 2;
	  j++;
	}
      body = new Mesh(v, 24, i, 36);
    }
  return (body);
}

static Mesh* GetHead()
{
  static Mesh* head = NULL;

  if (!head)
    {
      Vertex	v[] = {Vertex(vec3(-0.2, 0.2, -0.2), vec2(0, 0)),
		       Vertex(vec3(-0.2, -0.2, -0.2), vec2(0, 1)),
		       Vertex(vec3(0.2, -0.2, -0.2), vec2(1, 1)),
		       Vertex(vec3(0.2, 0.2, -0.2), vec2(1, 0)),
		       // BOT FACE

		       Vertex(vec3(-0.2, -0.2, 0.2), vec2(0, 0)),
		       Vertex(vec3(-0.2, 0.2, 0.2), vec2(0, 1)),
		       Vertex(vec3(0.2, 0.2, 0.2), vec2(1, 1)),
		       Vertex(vec3(0.2, -0.2, 0.2), vec2(1, 0)),
		       // TOP FACE

		       Vertex(vec3(-0.2, -0.2, -0.2), vec2(0, 0)),
		       Vertex(vec3(-0.2, -0.2, 0.2), vec2(0, 1)),
		       Vertex(vec3(0.2, -0.2, 0.2), vec2(1, 1)),
		       Vertex(vec3(0.2, -0.2, -0.2), vec2(1, 0)),
		       // FRONT FACE

		       Vertex(vec3(-0.2, 0.2, 0.2), vec2(0, 0)),
		       Vertex(vec3(-0.2, 0.2, -0.2), vec2(0, 1)),
		       Vertex(vec3(0.2, 0.2, -0.2), vec2(1, 1)),
		       Vertex(vec3(0.2, 0.2, 0.2), vec2(1, 0)),
		       // BACK FACE

		       Vertex(vec3(-0.2, -0.2, -0.2), vec2(0, 0)),
		       Vertex(vec3(-0.2, 0.2, -0.2), vec2(0, 1)),
		       Vertex(vec3(-0.2, 0.2, 0.2), vec2(1, 1)),
		       Vertex(vec3(-0.2, -0.2, 0.2), vec2(1, 0)),
		       // RIGHT FACE

		       Vertex(vec3(0.2, 0.2, -0.2), vec2(0, 0)),
		       Vertex(vec3(0.2, -0.2, -0.2), vec2(0, 1)),
		       Vertex(vec3(0.2, -0.2, 0.2), vec2(1, 1)),
		       Vertex(vec3(0.2, 0.2, 0.2), vec2(1, 0))
		       // LEFT FACE
      };
      unsigned int	i[36];
      int		j = 0;

      while (j < 6)
	{
	  i[6 * j] = 4 * j;
	  i[6 * j + 1] = 4 * j + 2;
	  i[6 * j + 2] = 4 * j + 1;
	  i[6 * j + 3] = 4 * j;
	  i[6 * j + 4] = 4 * j + 3;
	  i[6 * j + 5] = 4 * j + 2;
	  j++;
	}
      head = new Mesh(v, 24, i, 36);
    }
  return (head);
}

static Mesh* GetMember()
{
  static Mesh* member = NULL;

  if (!member)
    {
      Vertex	v[] = {Vertex(vec3(-0.1, 0.1, -0.8), vec2(0, 0)),
		       Vertex(vec3(-0.1, -0.1, -0.8), vec2(0, 1)),
		       Vertex(vec3(0.1, -0.1, -0.8), vec2(1, 1)),
		       Vertex(vec3(0.1, 0.1, -0.8), vec2(1, 0)),
		       // BOT FACE

		       Vertex(vec3(-0.1, -0.1, 0.0), vec2(0, 0)),
		       Vertex(vec3(-0.1, 0.1, 0.0), vec2(0, 1)),
		       Vertex(vec3(0.1, 0.1, 0.0), vec2(1, 1)),
		       Vertex(vec3(0.1, -0.1, 0.0), vec2(1, 0)),
		       // TOP FACE

		       Vertex(vec3(-0.1, -0.1, -0.8), vec2(0, 0)),
		       Vertex(vec3(-0.1, -0.1, 0.0), vec2(0, 1)),
		       Vertex(vec3(0.1, -0.1, 0.0), vec2(1, 1)),
		       Vertex(vec3(0.1, -0.1, -0.8), vec2(1, 0)),
		       // FRONT FACE

		       Vertex(vec3(-0.1, 0.1, 0.0), vec2(0, 0)),
		       Vertex(vec3(-0.1, 0.1, -0.8), vec2(0, 1)),
		       Vertex(vec3(0.1, 0.1, -0.8), vec2(1, 1)),
		       Vertex(vec3(0.1, 0.1, 0.0), vec2(1, 0)),
		       // BACK FACE

		       Vertex(vec3(-0.1, -0.1, -0.8), vec2(0, 0)),
		       Vertex(vec3(-0.1, 0.1, -0.8), vec2(0, 1)),
		       Vertex(vec3(-0.1, 0.1, 0.0), vec2(1, 1)),
		       Vertex(vec3(-0.1, -0.1, 0.0), vec2(1, 0)),
		       // RIGHT FACE

		       Vertex(vec3(0.1, 0.1, -0.8), vec2(0, 0)),
		       Vertex(vec3(0.1, -0.1, -0.8), vec2(0, 1)),
		       Vertex(vec3(0.1, -0.1, 0.0), vec2(1, 1)),
		       Vertex(vec3(0.1, 0.1, 0.0), vec2(1, 0))
		       // LEFT FACE
      };
      unsigned int	i[36];
      int		j = 0;

      while (j < 6)
	{
	  i[6 * j] = 4 * j;
	  i[6 * j + 1] = 4 * j + 2;
	  i[6 * j + 2] = 4 * j + 1;
	  i[6 * j + 3] = 4 * j;
	  i[6 * j + 4] = 4 * j + 3;
	  i[6 * j + 5] = 4 * j + 2;
	  j++;
	}
      member = new Mesh(v, 24, i, 36);
    }
  return (member);
}

void	DrawPlayerModel(vec3 &pos, vec3 &dir, double speed, Camera &cam, Shader &shader, int current, int id, bool third, vec3 decal)
{
  mat4	transform;
  vec2	t = normalize(vec2(dir.x, dir.y));
  GLfloat	rotAngle = -atan2(t.x, t.y);
  Mesh	*body = GetBody();
  Mesh	*head = GetHead();
  Mesh	*member = GetMember();
  unsigned char	w[] = {255, 255, 255, 255};
  Texture	white(w, 1, 1);
  unsigned char r[] = {255, 0, 0, 255};
  Texture	red(r, 1, 1);
  unsigned char b[] = {0, 0, 255, 255};
  Texture	blue(b, 1, 1);
  int	i = SDL_GetTicks() / 2.0;
  if (speed > 1)
    speed = 1;
  // Mesh	leg = GetLeg();

  if (id != current || third)
    {
      if (current % 2 == id % 2)
	blue.Bind(0);
      else
	red.Bind(0);
      // Body
      transform = glm::translate(pos + vec3(0.4, 0.4, 1.1));
      transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
      shader.Update(transform, cam);
      body->Draw();

      white.Bind(0);
      // Head
      transform = glm::translate(pos + vec3(0.4, 0.4, 1.6));
      transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
      shader.Update(transform, cam);
      head->Draw();

      // Right arm
      transform = glm::translate(pos + vec3(0.4, 0.4, 1.3));
      transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
      transform *= glm::translate(vec3(0.25, 0, 0));
      transform *= glm::rotate((GLfloat)(cos(i / 50.0) / 5 * speed + M_PI / 2), vec3(1, 0, 0));
      transform *= glm::rotate((GLfloat)0.1, vec3(0, 1, 0));
      shader.Update(transform, cam);
      member->Draw();

      // Left arm
      transform = glm::translate(pos + vec3(0.4, 0.4, 1.4));
      transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
      transform *= glm::translate(vec3(-0.25, 0, 0));
      transform *= glm::rotate(-(GLfloat)(cos(i / 50.0) / 5 * speed), vec3(1, 0, 0));
      transform *= glm::rotate((GLfloat)0.1, vec3(0, 1, 0));
      shader.Update(transform, cam);
      member->Draw();

      // Right leg
      transform = glm::translate(pos + vec3(0.4, 0.4, 0.8));
      transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
      transform *= glm::translate(vec3(-0.1, 0, 0));
      transform *= glm::rotate((GLfloat)(cos(i / 50.0) / 2 * speed), vec3(1, 0, 0));
      shader.Update(transform, cam);
      member->Draw();

      // Left leg
      transform = glm::translate(pos + vec3(0.4, 0.4, 0.8));
      transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
      transform *= glm::translate(vec3(0.1, 0, 0));
      transform *= glm::rotate(-(GLfloat)(cos(i / 50.0) / 2 * speed), vec3(1, 0, 0));
      shader.Update(transform, cam);
      member->Draw();
    }
  else
    {
      white.Bind(0);
      // Right arm
      transform = glm::translate(cam.GetPos() - decal);
      transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
      transform *= glm::translate(vec3(0.25, -0.1, -0.2));
      transform *= glm::rotate((GLfloat)((cos(i / 200.0) / 20.0) + M_PI / 2 + cam.GetRot().x * M_PI / 180), vec3(1, 0, 0));
      //      transform *= glm::rotate((GLfloat)0.1, vec3(0, 1, 0));
      transform *= glm::scale(vec3(0.6, 0.6, 1));
      shader.Update(transform, cam);
      member->Draw();

      blue.Bind(0);
      // Body
      transform = glm::translate(cam.GetPos() - decal);
      transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
      transform *= glm::translate(-vec3(0, 0.15, 0.4));
      shader.Update(transform, cam);
      body->Draw();

      white.Bind(0);
      // Left arm
      transform = glm::translate(cam.GetPos() - decal);
      transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
      transform *= glm::translate(vec3(-0.25, -0.1, -0.2));
      transform *= glm::rotate(-(GLfloat)(cos(i / 50.0) / 5 * speed), vec3(1, 0, 0));
      transform *= glm::rotate((GLfloat)0.1, vec3(0, 1, 0));
      transform *= glm::scale(vec3(0.6, 0.6, 1));
      shader.Update(transform, cam);
      member->Draw();

      // Right leg
      transform = glm::translate(cam.GetPos() - decal);
      transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
      transform *= glm::translate(-vec3(0.1, 0.15, 0.8));
      transform *= glm::rotate((GLfloat)(cos(i / 50.0) / 2 * speed), vec3(1, 0, 0));
      shader.Update(transform, cam);
      member->Draw();

      // Left leg
      transform = glm::translate(cam.GetPos() - decal);
      transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
      transform *= glm::translate(-vec3(-0.1, 0.15, 0.8));
      transform *= glm::rotate(-(GLfloat)(cos(i / 50.0) / 2 * speed), vec3(1, 0, 0));
      shader.Update(transform, cam);
      member->Draw();
    }
}
