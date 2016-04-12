#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <sys/time.h>
#include <unistd.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <sys/time.h>
#include "engine/displayer.hpp"
#include <iostream>
#include "game.hpp"
#include "tools.hpp"
#include "Menu.h"
#include <algorithm>

#ifdef	CHEAT
# include "cheat.hpp"
#endif

void	SetSDL_Rect(SDL_Rect *r, int x, int y, int w, int h)
{
  r->x = x;
  r->y = y;
  r->w = w;
  r->h = h;
}

Displayer::Displayer(int width, int height, const std::string& title)
{
  TTF_Init();
  name_font = TTF_OpenFont(TCHAT_FONT_TEXT, (int)(30 / WIN_RATIO));
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
      std::cerr << "Failed to init SDL: " << SDL_GetError() << std::endl;
      exit(1);
    }
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
  m_glContext = SDL_GL_CreateContext(m_window);
  SDL_SetRelativeMouseMode(SDL_TRUE);

  GLenum status = glewInit();
  if (status != GLEW_OK)
    {
      std::cerr << "Glew failed to init!" << std::endl;
      exit(1);
    }
  m_isClosed = false;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glCullFace(GL_BACK);
  m_windowSurface = SDL_GetWindowSurface(m_window);
}

Displayer::~Displayer()
{
  SDL_GL_DeleteContext(m_glContext);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void	Displayer::Clear(float r, float g, float b, float a)
{
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool	Displayer::IsClosed()
{
  return (m_isClosed);
}

void	Displayer::Update(Camera &cam, Map &map, Player &player,
			  t_data *data, User &user)
{
  SDL_GL_SwapWindow(m_window);
  usleep(5800);
  ovrPosef pose[2];
  static		int cur(0), old(0), tot(0), nb(0);
  cur = SDL_GetTicks();
  int			t = cur - old + 1;
  float			dTime = t / 1000.0f;
  old = cur;
  SDL_Event		e;
  static bool		eventKey[NB_KEY_EVENT] = {0};

  tot += 1000 / t;
  nb++;
  if (nb == 1)
    tot = 0;
  // printf("\r%d  %d  ", tot / nb, 1000 / t);
  // fflush(stdout);
  while (SDL_PollEvent(&e))
    {
      switch (e.type)
	{
	case (SDL_QUIT):
	  m_isClosed = true;
	  break ;
	case SDL_MOUSEBUTTONDOWN:
	  switch (e.button.button)
	    {
	    case (SDL_BUTTON_LEFT):
	      eventKey[MOUSE_LEFT] = true;
	      break ;
	    case (SDL_BUTTON_RIGHT):
	      eventKey[MOUSE_RIGHT] = true;
	      break ;
	    }
	  break;
	case(SDL_MOUSEWHEEL):
	  if (e.wheel.y < 0)
	    {
	      user.changeWeaponWheel(DOWN);
	      break;
	    }
	  else if (e.wheel.y > 0)
	    {
	      user.changeWeaponWheel(UP);
	      break;
	    }
	  break ;
	case SDL_MOUSEBUTTONUP:
	  switch (e.button.button)
	    {
	    case (SDL_BUTTON_LEFT):
	      eventKey[MOUSE_LEFT] = false;
	      break ;
	    case (SDL_BUTTON_RIGHT):
	      eventKey[MOUSE_RIGHT] = false;
	      break ;
	    }
	case (SDL_TEXTINPUT):
	  if (data->tchat.isFocus())
	    data->tchat.write_text(e.text.text);
	  break;
	case (SDL_KEYDOWN):
	  if (data->tchat.isFocus())
	    switch (e.key.keysym.sym)
	      {
	      case (SDLK_RETURN):
		data->tchat.send(data);
		break;
	      case (SDLK_ESCAPE):
		data->tchat.focus(false);
		break;
	      case (SDLK_BACKSPACE):
		data->tchat.backspace();
		break;
	      case (SDLK_LEFT):
		data->tchat.moveLeft();
		break;
	      case (SDLK_RIGHT):
		data->tchat.moveRight();
		break;
	      }
	  else
	    {
	      if (e.key.keysym.scancode == SDL_SCANCODE_2)
		{
		  eventKey[KEY_E_ACCENT] = true;
		}
	      switch (e.key.keysym.sym)
		{
		case (SDLK_RETURN):
		  data->tchat.focus(true);
		  break ;
		case (SDLK_z):
		  eventKey[KEY_Z] = true;
		  break ;
		case (SDLK_s):
		  eventKey[KEY_S] = true;
		  break ;
		case (SDLK_q):
		  eventKey[KEY_Q] = true;
		  break ;
		case (SDLK_d):
		  eventKey[KEY_D] = true;
		  break ;
		case (SDLK_a):
		  eventKey[KEY_A] = true;
		  break ;
		case (SDLK_w):
		  eventKey[KEY_W] = true;
		  break ;
		case (SDLK_1):
		  eventKey[KEY_1] = true;
		  break ;
		case (SDLK_2):
		  eventKey[KEY_2] = true;
		  break ;
		case (SDLK_3):
		  eventKey[KEY_3] = true;
		  break ;
		case(SDLK_AMPERSAND):
		  eventKey[KEY_COMMERCIAL_AND] = true;
		  break;
		case (SDLK_QUOTEDBL):
		  eventKey[KEY_QUOTE] = true;
		  break ;
		case (SDLK_SPACE):
		  eventKey[KEY_SPACE] = true;
		  break ;
		  // case (SDLK_q):
		  //   player.GetPos() += normalize(vec3((cross(cam.GetFor(), vec3(0, 1, 0))).x, (cross(cam.GetFor(), vec3(0, 1, 0))).y, 0));
		  //   break ;
		  // case (SDLK_d):
		  //   player.GetPos() -= normalize(vec3((cross(cam.GetFor(), vec3(0, 1, 0))).x, (cross(cam.GetFor(), vec3(0, 1, 0))).y, 0));
		  //   break ;
		case (SDLK_ESCAPE):
		  m_isClosed = true;
		  break ;
		case (SDLK_p):
		  player.Jump();
		  break ;
#ifdef	DEBUG
		case (SDLK_F1):
		  map.PutCube(1, ivec3(cam.GetPos() + cam.GetFor() * 2.0f));
		  break ;
		case (SDLK_F2):
		  map.PutCube(2, ivec3(cam.GetPos() + cam.GetFor() * 2.0f));
		  break ;
		case (SDLK_F3):
		  map.PutCube(3, ivec3(cam.GetPos() + cam.GetFor() * 2.0f));
		  break ;
		case (SDLK_F4):
		  map.PutCube(4, ivec3(cam.GetPos() + cam.GetFor() * 2.0f));
		  break ;
		case (SDLK_F5):
		  map.PutCube(5, ivec3(cam.GetPos() + cam.GetFor() * 2.0f));
		  break ;
		case (SDLK_F6):
		  map.PutCube(6, ivec3(cam.GetPos() + cam.GetFor() * 2.0f));
		  break ;
		case (SDLK_F10):
		  map.PutCube(0, ivec3(cam.GetPos() + cam.GetFor() * 2.0f));
		  break ;
		case (SDLK_v):
		  map.Save();
		  break ;
		case (SDLK_t):
		  player.GetThird() = !player.GetThird();
		  break ;
#endif
#ifdef	CHEAT
		case (SDLK_EQUALS):
		  if (data->players[data->net.playerIndexUdp].life < 100)
		    ++data->players[data->net.playerIndexUdp].life;
		  break ;
		case (SDLK_MINUS):
		  if (data->players[data->net.playerIndexUdp].life)
		    --data->players[data->net.playerIndexUdp].life;
		  break ;
		case(SDLK_i):
		  cheat.selected.ammo = (cheat.selected.ammo) ?  false : true;
		  break ;
		case(SDLK_j):
		  cheat.selected.life = (cheat.selected.life) ?  false : true;
		  break ;
		case(SDLK_k):
		  cheat.selected.fly = (cheat.selected.fly) ?  false : true;
		  cheat.selected.collisions = cheat.selected.fly;
		  break ;
		case(SDLK_l):
		  cheat.selected.collisions =
		    (cheat.selected.collisions) ?  false : true;
		  break ;
#endif
		}
	    }
	  break ;
	case (SDL_KEYUP):
	  {
	    if (e.key.keysym.scancode == SDL_SCANCODE_2)
	      {
		eventKey[KEY_E_ACCENT] = false;
	      }
	    switch (e.key.keysym.sym)
	      {
	      case (SDLK_z):
		eventKey[KEY_Z] = false;
		break ;
	      case (SDLK_s):
		eventKey[KEY_S] = false;
		break ;
	      case (SDLK_q):
		eventKey[KEY_Q] = false;
		break ;
	      case (SDLK_d):
		eventKey[KEY_D] = false;
		break ;
	      case (SDLK_a):
		eventKey[KEY_A] = false;
		break ;
	      case (SDLK_w):
		eventKey[KEY_W] = false;
		break ;
	      case (SDLK_SPACE):
		eventKey[KEY_SPACE] = false;
		break ;
	      case (SDLK_1):
		eventKey[KEY_1] = false;
		break ;
	      case (SDLK_2):
		eventKey[KEY_2] = false;
		break ;
	      case (SDLK_3):
		eventKey[KEY_3] = false;
		break ;
	      case(SDLK_AMPERSAND):
		eventKey[KEY_COMMERCIAL_AND] = false;
		break;
	      case (SDLK_QUOTEDBL):
		eventKey[KEY_QUOTE] = false;
		break ;
	      }
	    break;
	  case (SDL_MOUSEMOTION):
	    player.GetMouseRot().y -= e.motion.xrel / 20.0f / (player.IsAiming() ? FOV_NORMAL / FOV_ZOOM : 1);
	    player.GetMouseRot().x -= e.motion.yrel / 20.0f / (player.IsAiming() ? FOV_NORMAL / FOV_ZOOM : 1);
	    break ;
	  }
	}
    }

  // // Oculus
  // if (cam.isOculus())
  //   cam.UpdateFor();
  player.GetRot() = player.GetMouseRot();
  if (data->config.oculusHmd && data->config.oculus)
    {
      pose[0] = ovrHmd_GetHmdPosePerEye(data->config.oculusHmd,
					data->config.oculusHmd->EyeRenderOrder[0]);
      pose[1] = ovrHmd_GetHmdPosePerEye(data->config.oculusHmd,
					data->config.oculusHmd->EyeRenderOrder[1]);
      // if (pose[0].Orientation.x >= 0.5)
      // 	pose[0].Orientation.x = 0.499;
      player.GetRot().x = pose[0].Orientation.x * 90.0 * 1.3;
      player.GetRot().y += pose[0].Orientation.y * 90.0 * 1.3;
    }
  if (player.GetRot().x > 89.99f)
    player.GetRot().x = 89.99f;
  if (player.GetRot().x < -89.99f)
    player.GetRot().x = -89.99f;
  cam.UpdateFor();

  // Movement
  if (eventKey[data->config.keys.forward])
    player.Move(vec2(cam.GetFor().x, cam.GetFor().y));
  else if (eventKey[data->config.keys.backward])
    player.Move(-vec2(cam.GetFor().x, cam.GetFor().y));
  if (eventKey[data->config.keys.left])
    player.Move(-vec2(normalize(cross(cam.GetFor(), vec3(0, 0, 1))).x, cross(cam.GetFor(), vec3(0, 0, 1)).y));
  else if (eventKey[data->config.keys.right])
    player.Move(vec2(normalize(cross(cam.GetFor(), vec3(0, 0, 1))).x, cross(cam.GetFor(), vec3(0, 0, 1)).y));

  // Jump and Shoot
  if (eventKey[data->config.keys.jump])
    player.Jump();
  if (eventKey[data->config.keys.fire])
    user.shoot(true, data->lock);
  else
    user.shoot(false, data->lock);
  if (eventKey[data->config.keys.aim])
    player.IsAiming() = true;
  else
    player.IsAiming() = false;

  // Switch weapon
  if (eventKey[data->config.keys.weapon1])
    user.changeWeapon(RIFLE_WEAPON);
  else if (eventKey[data->config.keys.weapon2])
    user.changeWeapon(PISTOL_WEAPON);
  else if (eventKey[data->config.keys.weapon3])
    user.changeWeapon(KNIFE_WEAPON);

#ifdef CHEAT
  if (cheat.selected.fly && eventKey[data->config.keys.forward])
    player.MoveCheat(cam.GetFor());
  else if (cheat.selected.fly && eventKey[data->config.keys.backward])
    player.MoveCheat(-cam.GetFor());
  else
    player.Update(map, dTime);
#else
  player.Update(map, dTime);
#endif

  player.SetCam(cam, player.GetThird(), data->players + player.GetId());
}

int	startGame(t_data *data, std::vector<menuItem> &items, Displayer &disp)
{
  //Initilisation
#ifdef	CHEAT
  cheat.selected.ammo = false;
  cheat.selected.life = false;
  cheat.selected.fly = false;
  cheat.selected.collisions = false;
#endif

  if (data->config.keyboard == QWERTY_MODE)
    setQwerty(&data->config.keys);
  else if (data->config.keyboard == AZERTY_MODE)
    setAzerty(&data->config.keys);

  data->config.musicVolume = items[8].value;
  data->config.effectsVolume = items[9].value;
  data->config.brightness = items[10].value;
  bunny_sound_volume(&data->menuMusic->sound, (double)data->config.musicVolume);
  bunny_sound_volume(&data->menuEffect->sound, (double)data->config.effectsVolume);

  if (data->players[0].weapons[0].shootSound)
    bunny_sound_volume(&data->players[0].weapons[0].shootSound->sound, (double)data->config.effectsVolume);
  if (data->players[0].weapons[1].shootSound)
    bunny_sound_volume(&data->players[0].weapons[1].shootSound->sound, (double)data->config.effectsVolume);
  if (data->players[0].weapons[2].shootSound)
    bunny_sound_volume(&data->players[0].weapons[2].shootSound->sound, (double)data->config.effectsVolume);

  data->net.port = atoi(items[3].text.c_str());
  data->net.ip = (char *)items[2].text.c_str();
  data->net.pseudo = (char *)items[1].text.c_str();
  disp.setClosed(false);

  // Penser a checker IP + Pseudo + Port
  if (data->net.port < 0)
    {
      std::cerr << "Incorrect port\n";
      return (1);
    }
  if (strlen(data->net.pseudo) > 20)
    {
      std::cerr << "Pseudo is too long\n";
      return (1);
    }

#ifdef	DEBUG
  std::clog << "[Infos] Port = " << data->net.port << "\n";
  std::clog << "[Infos] Ip = " << data->net.ip << "\n";
  std::clog << "[Infos] Pseudo = " << data->net.pseudo << "\n";
#endif

  data->room = true;
  data->tchat.constructor();
  while (data->room)
    {
  if (!clientLaunchTcpc(data)) //TCP Start
    {
#ifdef	DEBUG
      std::clog << "TCP OK\n";
#endif
	  if (!room(disp, data))
	    {
#ifdef	DEBUG
	      fprintf(stdout, "tcp fd closed\n");
#endif
	      write(data->net.tcp.sock, "/r", 2);
#ifdef _WIN32
	      closesocket(data->net.tcp.sock);
#else
	      close(data->net.tcp.sock);
#endif
	      data->net.tcp.run = 0;
	      data->net.udp.run_send = 0;
	      data->net.udp.run = 0;
	      data->tchat.constructor();
	      data->room = false;
	      disp.setClosed(true);
	      return (0);
	    }
	  if (!clientLaunchUdpc(data))
	    {
#ifdef	DEBUG
	      std::clog << "UDP OK\n";
#endif
	      data->game.Team1.setScore(0);
	      data->game.Team2.setScore(0);
	      selectGameMusic(data, false);
	      data->net.tcp.buff[0] = 0;
	      bunny_sound_volume(&data->gameMusic->sound, (double)data->config.musicVolume);
	      bunny_sound_stop(&data->menuMusic->sound);
	      bunny_sound_play(&data->gameMusic->sound);
	      setEvent(&data->players[data->net.playerIndexUdp].events, IS_CONNECTED, true);
	      engineMain(disp, data);
#ifdef _WIN32
	      closesocket(data->net.udp.sock);
#else
	      close(data->net.udp.sock);
#endif
	      write(data->net.tcp.sock, "/r", 2);
#ifdef	DEBUG
	      fprintf(stdout, "tcp fd closed\n");
#endif
#ifdef	_WIN32
	      closesocket(data->net.tcp.sock);
#else
	      close(data->net.tcp.sock);
#endif
	      setEvent(&data->players[data->net.playerIndexUdp].events, IS_CONNECTED, false);
	      bunny_sound_stop(&data->gameMusic->sound);
	      bunny_sound_play(&data->menuMusic->sound);
	    }
	  data->room = true;
	  data->game.running = true;
	  disp.setClosed(false);
    }
  write(data->net.tcp.sock, "/r", 2);
#ifdef	DEBUG
  fprintf(stdout, "tcp fd closed\n");
#endif
#ifdef	_WIN32
  closesocket(data->net.tcp.sock);
#else
  close(data->net.tcp.sock);
#endif
    }
  data->room = false;
  data->net.tcp.run = 0;
  data->net.udp.run_send = 0;
  data->net.udp.run = 0;
  return (0);
}

int			minUdpID(t_data *data)
{
  for (int i = 0 ; i < 10 ; ++i)
    if (*(data->players[i].pseudo))
      return (i);
  return (-1);
}

void			display_name(t_player *players, int pos,
				     SDL_Surface *to, TTF_Font *font)
{
  SDL_Rect		positions[] = {{1356, 61, 200, 200},
				       {1531, 157, 200, 200},
				       {1063, 198, 200, 200},
				       {1650, 330, 200, 200},
				       {933, 373, 200, 200},
				       {1656, 676, 200, 200},
				       {933, 634, 200, 200},
				       {1533, 796, 200, 200},
				       {1066, 809, 200, 200},
				       {1215, 865, 200, 200}};
  SDL_Rect		point = positions[pos];
  char			path[64];
  SDL_Surface		*link;
  SDL_Color		black = {0, 0, 0, 0};

  sprintf(path, "./assets/imgs/room/players/%d.png", pos);
  link = IMG_Load(path);
  SDL_BlitSurface(link, NULL, to, &point);
  if (((pos % 2) || !pos) && pos != 9)
    point.x += link->w + 10;
  if (pos > 4)
    point.y += link->h;
  SDL_FreeSurface(link);
  link = TTF_RenderUTF8_Blended(font, players[pos].pseudo, black);
  point.y -= link->h / 2;
  if ((!(pos % 2) || pos == 9) && pos)
    point.x -= link->w + 20;
  SDL_BlitSurface(link, NULL, to, &point);
  SDL_FreeSurface(link);
}

void			Displayer::UpdateRoom(t_data *room, SDL_Rect *pos,
					      SDL_Surface *bg, SDL_Surface *surface)
{
  SDL_Event		event;
  SDL_Rect		dest = {0, 0, WIN_X, WIN_Y};
  SDL_Rect		bg_pos = {946, 138, 819, 800};
  SDL_Rect		players[] = {{1320, 215, 76, 76},
				     {1485, 270, 76, 76},
				     {1155, 270, 76, 76},
				     {1585, 410, 76, 76},
				     {1060, 410, 76, 76},
				     {1585, 578, 76, 76},
				     {1060, 578, 76, 76},
				     {1485, 718, 76, 76},
				     {1155, 718, 76, 76},
				     {1320, 773, 76, 76}};
  static SDL_Surface		*icon_connected = IMG_Load(ROOM_ICON_PLAYER),
				*icon_ia = IMG_Load(ROOM_ICON_IA),
				*start_button = IMG_Load(ROOM_START_BUTTON),
				*start_hold = IMG_Load(ROOM_START_HOLD),
				*logo = IMG_Load(ROOM_LOGO);
  static int			height = 0;
  static int			clicked = 0;

  while (SDL_PollEvent(&event))
    {
      switch(event.type)
	{
	  case SDL_KEYUP:
	    if (!room->tchat.isFocus() && event.key.keysym.sym == SDLK_RETURN)
	      {
		room->tchat.focus(true);
		break;
	      }
	    if (event.key.keysym.sym == SDLK_ESCAPE)
	      room->tchat.focus(false);
	    break;
	  case SDL_KEYDOWN:
	    if (!room->tchat.isFocus() && event.key.keysym.sym == SDLK_ESCAPE)
	      {
      		room->game.running = false;
		room->room = false;
		break;
	      }
	    if (!room->tchat.isFocus())
	      break;
	    switch (event.key.keysym.sym)
	      {
		case SDLK_BACKSPACE:
		  room->tchat.backspace();
		  break;
		case SDLK_LEFT:
		  room->tchat.moveLeft();
		  break;
		case SDLK_RIGHT:
		  room->tchat.moveRight();
		  break;
		case SDLK_RETURN:
		  room->tchat.send(room);
		  break;
	      }
	    break;
	  case SDL_QUIT:
	    room->game.running = false;
	    room->room = false;
	    break;
	  case SDL_MOUSEBUTTONUP:
	    if (event.button.button != SDL_BUTTON_LEFT)
	      break;
	    clicked = 0;
	    if (pos->x > 1655 && pos->y > 858
		&& pos->x < 1855 && pos->y < 1058)
	      write(room->net.tcp.sock, "/k", 2);
	    break;
	  case SDL_MOUSEBUTTONDOWN:
	    if (event.button.button != SDL_BUTTON_LEFT)
	      break;
	    if (pos->x > 1705 && pos->y > 858
		&& pos->x < 1905 && pos->y < 1058)
	      clicked = 1;
	    else if (pos->x < 854 && !room->tchat.isFocus())
	      room->tchat.focus(true);
	    else
	      room->tchat.focus(false);
	    break;
	  case SDL_MOUSEMOTION:
	    if (event.motion.x)
	      event.motion.x -= (event.motion.xrel / 3) / WIN_RATIO;
	    if (event.motion.y)
	      event.motion.y -= (event.motion.yrel / 3) / WIN_RATIO;
	    pos->x += (event.motion.xrel / 2) / WIN_RATIO;
	    pos->y += (event.motion.yrel / 2) / WIN_RATIO;
	    if (pos->x > WIN_X)
	      pos->x = WIN_X;
	    else if (pos->x < 0)
	      pos->x = 0;
	    if (pos->y > WIN_Y)
	      pos->y = WIN_Y;
	    else if (pos->y < 0)
	      pos->y = 0;
	    if (!room->tchat.isFocus())
	      break;
	    break;
	  case SDL_TEXTINPUT:
	    if (!room->tchat.isFocus())
	      break;
	    room->tchat.write_text(event.text.text);
	    break;
	}
    }
  SDL_FillRect(m_windowSurface, NULL, SDL_MapRGB(m_windowSurface->format, 243, 237, 211));
  if (room->config.oculus)
    {
      SDL_Surface *eyes = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, 32, 0, 0, 0, 0);
      SDL_FillRect(eyes, NULL, SDL_MapRGB(eyes->format, 243, 237, 211));
      room->tchat.display(dest, eyes);
      SDL_BlitSurface(bg, NULL, eyes, &bg_pos);
      SetSDL_Rect(&bg_pos, 1245, 425 + sin((float)++height / 10.0) * 8.0, 200, 200);
      if ((height / 20.0) == 2 * M_PI)
	height = 0;
      SDL_BlitSurface(logo, NULL, eyes, &bg_pos);
      SetSDL_Rect(&bg_pos, 1705, 858, 200, 200);
      if (room->net.playerIndexUdp == minUdpID(room))
	SDL_BlitSurface(clicked ? start_hold : start_button, NULL, eyes, &bg_pos);

      for (int i = 0 ; i < 10 ; ++i)
	{
	  if (*(room->players[i].pseudo))
	    {
	      SDL_BlitSurface(icon_connected, NULL, eyes, &(players[i]));
	      display_name(room->players, i, eyes, this->name_font);
	    }
	  else
	    SDL_BlitSurface(icon_ia, NULL, eyes, &(players[i]));
	}

      SDL_Surface	*final = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
      this->Clear(0.0, 0.0, 0.0, 1);
      SDL_BlitScaled(eyes, NULL, final, NULL);
      SetSDL_Rect(&dest, pos->x + 10, pos->y, surface->w, surface->h);
      SDL_BlitSurface(surface, NULL, final, &dest);
      Texture left(final);
      glViewport(0, 0, WIN_X / 2, WIN_Y);

      glDisable(GL_DEPTH_TEST);
      glDisable(GL_CULL_FACE);
      glDisable(GL_LIGHTING);
      glEnable(GL_TEXTURE_2D);
      left.Bind(0);

      glBegin(GL_QUADS);
      glTexCoord2i(0, 0);
      glVertex3f(-0.8, 0.5, 0);
      glTexCoord2i(0, 1);
      glVertex3f(-0.8, -0.5, 0);
      glTexCoord2i(1, 1);
      glVertex3f(0.8, -0.5, 0);
      glTexCoord2i(1, 0);
      glVertex3f(0.8, 0.5, 0);
      glEnd();

      SDL_BlitScaled(eyes, NULL, final, NULL);
      SetSDL_Rect(&dest, pos->x - 10, pos->y, surface->w, surface->h);
      SDL_BlitSurface(surface, NULL, final, &dest);

      Texture right(final);
      glViewport(WIN_X / 2, 0, WIN_X / 2, WIN_Y);

      left.Bind(0);

      glBegin(GL_QUADS);
      glTexCoord2i(0, 0);
      glVertex3f(-0.8, 0.5, 0);
      glTexCoord2i(0, 1);
      glVertex3f(-0.8, -0.5, 0);
      glTexCoord2i(1, 1);
      glVertex3f(0.8, -0.5, 0);
      glTexCoord2i(1, 0);
      glVertex3f(0.8, 0.5, 0);
      glEnd();

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_CULL_FACE);
      glEnable(GL_LIGHTING);
      glCullFace(GL_BACK);
      SDL_FreeSurface(final);

      SDL_GL_SwapWindow(m_window);
      SDL_FreeSurface(eyes);
    }
  else
    {
      SDL_BlitSurface(bg, NULL, m_windowSurface, &bg_pos);	// 11ms
      room->tchat.display(dest, m_windowSurface);		// 25ms
      SetSDL_Rect(&bg_pos, 1245, 425 + sin((float)++height / 10.0) * 8.0, 200, 200);
      if ((height / 20.0) == 2 * M_PI)
	height = 0;
      SDL_BlitSurface(logo, NULL, m_windowSurface, &bg_pos);
      SetSDL_Rect(&bg_pos, 1655, 858, 200, 200);
      if (room->net.playerIndexUdp == minUdpID(room))
	SDL_BlitSurface(clicked ? start_hold : start_button, NULL, m_windowSurface, &bg_pos);
      for (int i = 0 ; i < 10 ; ++i)
	{
	  if (*(room->players[i].pseudo))
	    {
	      SDL_BlitSurface(icon_connected, NULL, m_windowSurface, &(players[i]));
	      display_name(room->players, i, m_windowSurface, this->name_font);
	    }
	  else
	    SDL_BlitSurface(icon_ia, NULL, m_windowSurface, &(players[i]));
	}
								// 2ms
      SDL_BlitSurface(surface, NULL, m_windowSurface, pos);	// 3ms
      SDL_UpdateWindowSurface(m_window);
    }
}

void			Displayer::UpdateMenu(Menu *menu, std::vector<menuItem> &items,
					      SDL_Rect *pos, SDL_Surface *screen,
					      SDL_Surface *surface, t_data *data)
{
  SDL_Event		event;
  struct timeval	tv;
  SDL_Rect		dest = {0, 0, WIN_X, WIN_Y};

  while (SDL_PollEvent(&event))
    {
      switch(event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
	  menu->hover(pos->x, pos->y);
	  menu->hold();
	  break;
	case SDL_MOUSEBUTTONUP:
	  if (menu->holded)
	    {
	      if (menu->currentItem == LEFT_BOTTOM && !items[0].type)
		data->game.running = false;
	      else if (menu->currentItem == LEFT_MIDDLE && !items[0].type)
		optionMenu(items);
	      else if (items[0].type && menu->currentItem == LEFT_BOTTOM)
		loginMenu(items);
	      else if (items[0].type && menu->currentItem == RIGHT_MIDDLE) {
		if (items[4].text == "AZERTY mode")
		  {
		    items[4].text = "QWERTY mode";
		    data->config.keyboard = QWERTY_MODE;
		  }
		else
		  {
		    items[4].text = "AZERTY mode";
		    data->config.keyboard = AZERTY_MODE;
		  }
	      } else if (items[0].type && menu->currentItem == LEFT_MIDDLE) {
		if (items[5].text == " Set Oculus")
		  {
		    items[5].text = "Unset Oculus";
		    data->config.oculus = true;
		  }
		else
		  {
		    items[5].text = " Set Oculus";
		    data->config.oculus = false;
		  }
	      } else if (menu->currentItem == RIGHT_MIDDLE && !items[0].type) {
		if (startGame(data, items, *this))
		  break;
	      }
	      menu->unhold();
	    }
	  break;
	case SDL_QUIT:
	  data->game.running = false;
	  break;
	case SDL_KEYUP:
	  if (menu->holded)
	    {
	      if (menu->currentItem == LEFT_BOTTOM && !items[0].type)
		data->game.running = false;
	      menu->unhold();
	    }
	  break;
	case SDL_KEYDOWN:
	  if (event.key.keysym.sym == SDLK_ESCAPE)
	    {
	      data->game.running = false;
	      break;
	    }
	  if (event.key.keysym.sym == SDLK_LEFT)
	    {
	      menu->moveLeft();
	      bunny_sound_play(&data->menuEffect->sound);
	      if (items[menu->currentItem].type == MENU_TEXTINPUT)
		menu->hold();
	    }
	  if (event.key.keysym.sym == SDLK_RIGHT)
	    {
	      menu->moveRight();
	      bunny_sound_play(&data->menuEffect->sound);
	      if (items[menu->currentItem].type == MENU_TEXTINPUT)
		menu->hold();
	    }
	  if (event.key.keysym.sym == SDLK_UP)
	    {
	      menu->moveUp();
	      bunny_sound_play(&data->menuEffect->sound);
	      if (items[menu->currentItem].type == MENU_TEXTINPUT)
		menu->hold();
	    }
	  if (event.key.keysym.sym == SDLK_BACKSPACE &&
	      items[menu->currentItem].text.length() &&
	      items[menu->currentItem].type == MENU_TEXTINPUT)
	    {
	      if (!isprint(items[menu->currentItem].text[items[menu->currentItem].text.length() - 1]))
		items[menu->currentItem].text.erase(items[menu->currentItem].text.length() - 2);
	      else
		items[menu->currentItem].text.erase(items[menu->currentItem].text.length() - 1);
	    }
	  else if (items[0].type && menu->currentItem == LEFT_BOTTOM && event.key.keysym.sym == SDLK_RETURN)
	    {
	      loginMenu(items);
	    }
	  else if (!items[0].type && menu->currentItem == LEFT_BOTTOM && event.key.keysym.sym == SDLK_RETURN)
	    {
	      data->game.running = false;
	    }
	  else if (items[0].type && menu->currentItem == RIGHT_MIDDLE && event.key.keysym.sym == SDLK_RETURN) {
	    if (items[4].text == "AZERTY mode")
	      {
		items[4].text = "QWERTY mode";
		data->config.keyboard = QWERTY_MODE;
	      }
	    else
	      {
		items[4].text = "AZERTY mode";
		data->config.keyboard = AZERTY_MODE;
	      }
	  } else if (items[0].type && menu->currentItem == LEFT_MIDDLE && event.key.keysym.sym == SDLK_RETURN) {
	    if (items[5].text == " Set Oculus")
	      {
		items[5].text = "Unset Oculus";
		data->config.oculus = false;
	      }
	    else
	      {
		items[5].text = " Set Oculus";
		data->config.oculus = true;
	      }
	  } else if (event.key.keysym.sym == SDLK_RETURN &&
		     !items[0].type && menu->currentItem == LEFT_MIDDLE)
	    optionMenu(items);
	  else if (event.key.keysym.sym == SDLK_RETURN &&
		   items[menu->currentItem].type == MENU_TEXTINPUT)
	    menu->hold();
	  else if (event.key.keysym.sym == SDLK_RETURN &&
		   (menu->currentItem == 3 || menu->currentItem == RIGHT_MIDDLE) &&
		   !items[0].type)
	    {
	      menu->hold();
	      //Initilisation
	      if (startGame(data, items, *this))
		break;
	    }
	  if (event.key.keysym.sym == SDLK_RETURN &&
	      items[0].type && menu->currentItem == LEFT_BOTTOM)
	    {
	      loginMenu(items);
	    }
	  if (event.key.keysym.sym == SDLK_DOWN)
	    {
	      menu->moveDown();
	      bunny_sound_play(&data->menuEffect->sound);
	      if (items[menu->currentItem].type == MENU_TEXTINPUT)
		menu->hold();
	    }
	  if ((event.key.keysym.sym == SDLK_RETURN
	       || event.key.keysym.sym == SDLK_TAB)
	      && (items[menu->currentItem].type == MENU_TEXTINPUT
		  || menu->currentItem == 0))
	    {
	      menu->moveNext();
	      bunny_sound_play(&data->menuEffect->sound);
	      if (items[menu->currentItem].type == MENU_TEXTINPUT)
		menu->hold();
	    }
	  break;
	case SDL_MOUSEMOTION:
	  if (event.motion.x)
	    event.motion.x -= (event.motion.xrel / 3) / WIN_RATIO;
	  if (event.motion.y)
	    event.motion.y -= (event.motion.yrel / 3) / WIN_RATIO;
	  if (items[menu->currentItem].type != MENU_SLIDER ||
	      !menu->holded) {
	    pos->x += (event.motion.xrel / 2) / WIN_RATIO;
	    pos->y += (event.motion.yrel / 2) / WIN_RATIO;
	    if (pos->x > WIN_X)
	      pos->x = WIN_X;
	    else if (pos->x < 0)
	      pos->x = 0;
	    if (pos->y > WIN_Y)
	      pos->y = WIN_Y;
	    else if (pos->y < 0)
	      pos->y = 0;
	  }
	  if (menu->holded)
	    menu->hover(pos->x, pos->y);
	  if (items[menu->currentItem].type == MENU_SLIDER && menu->holded) {
	    items[menu->currentItem].value += event.motion.xrel / 20 + ((event.motion.xrel > 0) * 2 - 1);
	    if (items[menu->currentItem].value < 0)
	      items[menu->currentItem].value = 0;
	    else if (items[menu->currentItem].value > 100)
	      items[menu->currentItem].value = 100;
	  }
	  break;
	case SDL_TEXTINPUT:
	  if (items[menu->currentItem].type == MENU_TEXTINPUT &&
	      ((menu->currentItem != 1 && items[menu->currentItem].text.length() < 16)
	       || (menu->currentItem == 1 && items[menu->currentItem].text.length() < 10)))
	    {
	      if (items[menu->currentItem].text == " ")
		items[menu->currentItem].text = "";
	      items[menu->currentItem].text += event.text.text;
	    }
	  break;
	}
      SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    }
  if (items[menu->currentItem].type == MENU_TEXTINPUT)
    {
      gettimeofday(&tv, NULL);
      if (tv.tv_usec / 500000 % 2)
	items[menu->currentItem].text += " ";
      else
	items[menu->currentItem].text += "|";
    }

  menu->draw();
  SDL_FillRect(m_windowSurface, NULL, SDL_MapRGB(screen->format, 143, 45, 42));
  if (data->config.oculus)
    {
      SDL_Surface	*final = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
      this->Clear(0.0, 0.0, 0.0, 1);
      SDL_BlitScaled(screen, NULL, final, NULL);
      SDL_BlitScaled(surface, NULL, final, pos);
      Texture left(final);
      glViewport(0, 0, WIN_X / 2, WIN_Y);

      glDisable(GL_DEPTH_TEST);
      glDisable(GL_CULL_FACE);
      glDisable(GL_LIGHTING);
      glEnable(GL_TEXTURE_2D);
      left.Bind(0);

      glBegin(GL_QUADS);
      glTexCoord2i(0, 0);
      glVertex3f(-0.8, 0.5, 0);
      glTexCoord2i(0, 1);
      glVertex3f(-0.8, -0.5, 0);
      glTexCoord2i(1, 1);
      glVertex3f(0.8, -0.5, 0);
      glTexCoord2i(1, 0);
      glVertex3f(0.8, 0.5, 0);
      glEnd();

      SDL_BlitScaled(screen, NULL, final, NULL);
      SDL_BlitScaled(surface, NULL, final, pos);

      Texture right(final);
      glViewport(WIN_X / 2, 0, WIN_X / 2, WIN_Y);

      left.Bind(0);

      glBegin(GL_QUADS);
      glTexCoord2i(0, 0);
      glVertex3f(-0.8, 0.5, 0);
      glTexCoord2i(0, 1);
      glVertex3f(-0.8, -0.5, 0);
      glTexCoord2i(1, 1);
      glVertex3f(0.8, -0.5, 0);
      glTexCoord2i(1, 0);
      glVertex3f(0.8, 0.5, 0);
      glEnd();

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_CULL_FACE);
      glEnable(GL_LIGHTING);
      glCullFace(GL_BACK);
      SDL_FreeSurface(final);
      SDL_GL_SwapWindow(m_window);
    }
  else
    {
      SDL_BlitSurface(surface, NULL, screen, pos);
      SDL_BlitSurface(screen, NULL, m_windowSurface, &dest);
      SDL_UpdateWindowSurface(m_window);
    }
  if (items[menu->currentItem].type == MENU_TEXTINPUT)
    items[menu->currentItem].text.erase(items[menu->currentItem].text.length() - 1);
  usleep(12000);
}
