#include <SDL2/SDL.h>
#include "engine/displayer.hpp"
#include "game.hpp"
#include "Menu.h"
#include <GL/glut.h>
#include "SDL2/SDL_image.h"
#include <OVR.h>
#include "tools.hpp"

#ifdef	CHEAT
# include "cheat.hpp"
t_cheat		cheat;
#endif

void	setAzerty(t_keys *keys)
{
  keys->forward = KEY_Z;
  keys->backward = KEY_S;
  keys->left = KEY_Q;
  keys->right = KEY_D;
  keys->jump = KEY_SPACE;
  keys->weapon1 = KEY_COMMERCIAL_AND;
  keys->weapon2 = KEY_E_ACCENT;
  keys->weapon3 = KEY_QUOTE;
}

void	setQwerty(t_keys *keys)
{
  keys->forward = KEY_W;
  keys->backward = KEY_S;
  keys->left = KEY_A;
  keys->right = KEY_D;
  keys->jump = KEY_SPACE;
  keys->weapon1 = KEY_1;
  keys->weapon2 = KEY_2;
  keys->weapon3 = KEY_3;
}

void	commonKeys(t_keys *keys)
{
  keys->aim = MOUSE_RIGHT;
  keys->fire = MOUSE_LEFT;
}

void	initWeapons(t_player *player)
{
  static t_bunny_music	*rifle = NULL;
  static t_bunny_music	*knife = NULL;
  static t_bunny_music	*pistol = NULL;

  if (!rifle && !knife)
    {
      if (!(pistol = bunny_load_music(PISTOL_SOUND_PATH)) ||
	  !(rifle = bunny_load_music(RIFLE_SOUND_PATH)) ||
	  !(knife = bunny_load_music(KNIFE_SOUND_PATH)))
	{
	  std::cerr << "Cannot load effect\n";
	  exit(1);
	}
    }

  // Init Knife
  player->weapons[KNIFE_WEAPON].id = 0;
  player->weapons[KNIFE_WEAPON].loaded = KNIFE_LOAD;
  player->weapons[KNIFE_WEAPON].ammo = KNIFE_AMMO;
  player->weapons[KNIFE_WEAPON].shootSound = knife;

  //Init Pistol
  player->weapons[PISTOL_WEAPON].id = 0;
  player->weapons[PISTOL_WEAPON].loaded = PISTOL_AMMO;
  player->weapons[PISTOL_WEAPON].ammo = PISTOL_AMMO;
  player->weapons[PISTOL_WEAPON].shootSound = pistol;

  //Init Rifle
  player->weapons[RIFLE_WEAPON].id = 0;
  player->weapons[RIFLE_WEAPON].loaded = RIFLE_LOAD;
  player->weapons[RIFLE_WEAPON].ammo = RIFLE_AMMO;
  player->weapons[RIFLE_WEAPON].shootSound = rifle;
}

void	initData(t_data *data)
{
  int	i;

  memset(data, 0, sizeof(t_data));
  i = -1;
  if (!(data->menuEffect = bunny_load_music(EFFECT_MENU)))
    {
      std::cerr << "Cannot load effect\n";
      exit(1);
    }
  while (++i < 10)
    {
      data->players[i].events = 0;
      data->players[i].pseudo = new char [21];
      data->players[i].selected_weapon = 0;
      memset(data->players[i].pseudo, 0, 21);
      memset(&data->players[i].position, 0, sizeof(vector3));
      memset(&data->players[i].direction, 0, sizeof(vector3));
      initWeapons(&data->players[i]);
    }
  data->game.running = true;
  data->game.Team1 = Score();
  data->game.Team2 = Score();
  data->config.keyboard = AZERTY_MODE;
  data->config.musicVolume = 50;
  data->config.effectsVolume = 50;
  commonKeys(&data->config.keys);
  setAzerty(&data->config.keys);
#ifdef	CHEAT
  bzero(&cheat, sizeof(t_cheat));
  cheat.keys.ammo = KEY_I;
  cheat.keys.life = KEY_J;
  cheat.keys.fly = KEY_K;
  cheat.keys.collisions = KEY_L;
#endif
}

int	game()
{
  t_data		*data = new t_data;
  Displayer		display(WIN_X, WIN_Y, "ColdCube");
  std::vector<menuItem>	items(14);
  std::string		inputText = "Some text";
  SDL_Rect		pos;
  SDL_Surface		*screen = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, 32, 0, 0, 0, 0);// SDL_GetWindowSurface(display.GetWin());
  SDL_Surface		*surface = NULL;
  Menu			*menu = new Menu(screen, &items);
  ovrHmd		hmd;

  ovr_Initialize(0);
  hmd = ovrHmd_Create(0);
  if (hmd)
    ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0);
  initData(data);
  data->screen = screen;
  loginMenu(items);
  //Macro definie dans game.hpp
  surface = IMG_Load(CURSOR_IMG);
  pos.x = (screen->w / 2) - (surface->w / 2);
  pos.y = (screen->h / 2) - (surface->h / 2);
  pos.w = surface->w / 2;
  pos.h = surface->h / 2;
  SDL_StartTextInput();
  data->config.oculusHmd = hmd;
  data->config.oculus = (hmd != NULL);
  while (data->game.running)
    {
      display.UpdateMenu(menu, items, &pos, screen, surface, data);
    }
  if (hmd)
    ovrHmd_Destroy(hmd);
  if (data->players[0].weapons[0].shootSound)
    bunny_delete_sound(&data->players[0].weapons[0].shootSound->sound);
  if (data->players[0].weapons[1].shootSound)
    bunny_delete_sound(&data->players[0].weapons[1].shootSound->sound);
  if (data->players[0].weapons[2].shootSound)
    bunny_delete_sound(&data->players[0].weapons[2].shootSound->sound);
  bunny_delete_sound(&data->menuEffect->sound);
  return (0);
}

int	main(int ac, char **av, char **env)
{
  (void) ac;
  (void) av;
  if (!*env)
    {
      write(2, "Environment variable are missing\n", 33);
#ifdef DEBUG
      write(2, "[INFOS] Game exited with status error 1\n", 40);
#endif
      return (1);
    }
  if (game())
    {
      write(2, "An error occured.\n", 18);
#ifdef DEBUG
      write(2, "[INFOS] Game exited with status error 1\n", 40);
#endif
      return (1);
    }
#ifdef DEBUG
  write(2, "[INFOS] Game exited correctly\n", 30);
#endif
  return (0);
}
