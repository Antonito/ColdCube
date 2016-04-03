#include "engine/mesh.hpp"
#include "engine/animation_player.hpp"

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

void	DrawPlayerModel(vec3 &pos, vec3 &dir, double speed, Camera &cam, Shader &shader)
{
  mat4	transform;
  vec2	t = normalize(vec2(dir.x, dir.y));
  GLfloat	rotAngle = -atan2(t.x, t.y);
  Mesh	*body = GetBody();
  Mesh	*head = GetHead();
  Mesh	*member = GetMember();
  static int	i = 0;
  if (speed > 1)
    speed = 1;
  // Mesh	leg = GetLeg();

  transform = glm::translate(pos + vec3(0.4, 0.4, 1.1));
  transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
  shader.Update(transform, cam);
  body->Draw();
  transform = glm::translate(pos + vec3(0.4, 0.4, 1.6));
  transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
  shader.Update(transform, cam);
  head->Draw();
  transform = glm::translate(pos + vec3(0.4, 0.4, 1.4));
  transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
  transform *= glm::translate(vec3(0.25, 0, 0));
  transform *= glm::rotate((GLfloat)(cos(i / 50.0) / 5 * speed), vec3(1, 0, 0));
  transform *= glm::rotate(-(GLfloat)0.1, vec3(0, 1, 0));
  shader.Update(transform, cam);
  member->Draw();
  transform = glm::translate(pos + vec3(0.4, 0.4, 1.4));
  transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
  transform *= glm::translate(vec3(-0.25, 0, 0));
  transform *= glm::rotate(-(GLfloat)(cos(i / 50.0) / 5 * speed), vec3(1, 0, 0));
  transform *= glm::rotate((GLfloat)0.1, vec3(0, 1, 0));
  shader.Update(transform, cam);
  member->Draw();
  transform = glm::translate(pos + vec3(0.4, 0.4, 0.8));
  transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
  transform *= glm::translate(vec3(-0.1, 0, 0));
  transform *= glm::rotate((GLfloat)(cos(i / 50.0) / 2 * speed), vec3(1, 0, 0));
  shader.Update(transform, cam);
  member->Draw();
  transform = glm::translate(pos + vec3(0.4, 0.4, 0.8));
  transform *= glm::rotate(rotAngle, vec3(0, 0, 1));
  transform *= glm::translate(vec3(0.1, 0, 0));
  transform *= glm::rotate(-(GLfloat)(cos(i / 50.0) / 2 * speed), vec3(1, 0, 0));
  shader.Update(transform, cam);
  member->Draw();
  i++;
}
