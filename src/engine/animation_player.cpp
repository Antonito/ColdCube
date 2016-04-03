#include "mesh.hpp"
#include "common_structs.hpp"

static Mesh& GetBody()
{
  static isSet = false;
  static Mesh* body;

  if (!isSet)
    {
      isSet = true;
    }
  return (*body);
}

static Mesh& GetHead()
{
  static isSet = false;
  static Mesh* head;

  if (!isSet)
    {
      isSet = true;
    }
  return (*head);
}

static Mesh& GetArm()
{
  static isSet = false;
  static Mesh* arm;

  if (!isSet)
    {
      isSet = true;
    }
  return (*arm);
}

static Mesh& GetLeg()
{
  static isSet = false;
  static Mesh* leg;

  if (!isSet)
    {
      isSet = true;
    }
  return (*leg);
}

void	DrawPlayerModel(t_player *player, double speed)
{
  Mesh	body = GetBody();
  Mesh	head = GetHead();
  Mesh	arm = GetArm();
  Mesh	leg = GetLeg();
}
