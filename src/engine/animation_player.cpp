#include "mesh.hpp"
#include "common_structs.hpp"

static Mesh& GetBody()
{
}

static Mesh& GetHead()
{
}

static Mesh& GetArm()
{
}

static Mesh& GetLeg()
{
}

void	DrawPlayerModel(t_player *player, double speed)
{
  Mesh	body = GetBody();
  Mesh	head = GetHead();
  Mesh	arm = GetArm();
  Mesh	leg = GetLeg();
}
