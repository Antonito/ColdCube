#ifndef ANIMATION_PLAYER_HPP_
# define ANIMATION_PLAYER_HPP_

# include "engine/misc.hpp"
# include "engine/transform.hpp"
# include "engine/camera.hpp"
# include "engine/shader.hpp"

void	DrawPlayerModel(vec3 &pos, vec3 &dir, double speed, Camera &cam, Shader &shader, int current, int id, bool third, vec3 decal);

#endif //ANIMATION_PLAYER_HPP_
