#include <sys/time.h>
#include <unistd.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <sys/time.h>
#include "engine/display.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include "common_structs.hpp"
#include "game.hpp"
#include "tools.hpp"
#include "Menu.h"

Display::Display(int width, int height, const std::string& title)
{
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

  SDL_SetRelativeMouseMode(SDL_TRUE);
  m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
  m_glContext = SDL_GL_CreateContext(m_window);

  GLenum status = glewInit();
  if (status != GLEW_OK)
    {
      std::cerr << "Glew failed to init!" << std::endl;
      exit(1);
    }
  m_isClosed = false;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  // glEnable(LIGHTING);
  // glEnable(LIGHT0);
  glCullFace(GL_BACK);
}

Display::~Display()
{
  SDL_GL_DeleteContext(m_glContext);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void	Display::Clear(float r, float g, float b, float a)
{
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool	Display::IsClosed()
{
  return (m_isClosed);
}

void	Display::Update(Camera &cam, Map &map, Player &player,
			t_data *data)
{
  SDL_GL_SwapWindow(m_window);
  static		int cur(0), old(0), tot(0), nb(0);
  cur = SDL_GetTicks();
  int			t = cur - old + 1;
  float			dTime = t / 1000.0f;
  old = cur;
  SDL_Event	e;
  struct timeval	t1;

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
	case (SDL_KEYDOWN):
	  switch (e.key.keysym.sym)
	    {
	    case (SDLK_z):
	      player.Move(vec2(cam.GetFor().x, cam.GetFor().y));
	      break ;
	    case (SDLK_s):
	      player.Move(-vec2(cam.GetFor().x, cam.GetFor().y));
	      break ;
	    case (SDLK_SPACE):
	      player.Jump();
	      break ;
	    // case (SDLK_q):
	    //   player.GetPos() += normalize(vec3((cross(cam.GetFor(), vec3(0, 1, 0))).x, (cross(cam.GetFor(), vec3(0, 1, 0))).y, 0));
	    //   break ;
	    // case (SDLK_d):
	    //   player.GetPos() -= normalize(vec3((cross(cam.GetFor(), vec3(0, 1, 0))).x, (cross(cam.GetFor(), vec3(0, 1, 0))).y, 0));
	    //   break ;
	      break ;
	    case (SDLK_ESCAPE):
	      m_isClosed = true;
	      break ;
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
	    }
	  break ;
	case (SDL_MOUSEMOTION):
	  player.GetRot().y -= e.motion.xrel / 20.0f;
	  player.GetRot().x -= e.motion.yrel / 20.0f;
	  if (player.GetRot().x > 89.99f)
	    player.GetRot().x = 89.99f;
	  if (player.GetRot().x < -89.99f)
	    player.GetRot().x = -89.99f;
	  cam.UpdateFor();
	  break ;
	}
    }
  gettimeofday(&t1, NULL);
  if (t1.tv_usec % 3000)
    {
      createUdpPacket(data, &data->players[data->net.playerIndexUdp]);
    }
  player.Update(dTime);
  player.SetCam(cam);
}

void			Display::UpdateMenu(Menu *menu, std::vector<menuItem> &items,
					    SDL_Rect *pos, SDL_Surface *screen,
					    SDL_Surface *surface, t_data *data)
{
  SDL_Event		event;
  struct timeval	tv;

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
	      if (menu->currentItem == 6 && !items[0].type)
		data->game.running = false;
	      else if (menu->currentItem == 5 && !items[0].type)
		optionMenu(items);
	      else if (items[0].type && menu->currentItem == 6)
		loginMenu(items);
	      else if (items[0].type && menu->currentItem == 4) {
		if (items[4].text == "AZERTY mode")
		  items[4].text = "QWERTY mode";
		else
		  items[4].text = "AZERTY mode";
	      } else if (items[0].type && menu->currentItem == 5) {
		if (items[5].text == " Set Oculus")
		  items[5].text = "Unset Oculus";
		else
		  items[5].text = " Set Oculus";
	      } else if (menu->currentItem == 4 && !items[0].type) {
		//Initilisation
		data->net.port = atoi(items[3].text.c_str());
		data->net.ip = (char *)items[2].text.c_str();
		data->net.pseudo = (char *)items[1].text.c_str();
		this->setClosed(false);

		// Penser a checker IP + Pseudo + Port

		if (data->net.port < 0)
		  {
		    std::cerr << "Incorrect port\n";
		    break;
		  }
		if (strlen(data->net.pseudo) > 20)
		  {
		    std::cerr << "Pseudo is too long\n";
		    break;
		  }

#ifdef	DEBUG
		std::clog << "[Infos] Port = " << data->net.port << "\n";
		std::clog << "[Infos] Ip = " << data->net.ip << "\n";
		std::clog << "[Infos] Pseudo = " << data->net.pseudo << "\n";
#endif

		if (!clientLaunchTcpc(data) && !clientLaunchUdpc(data)) //TCP Start
		  {
		    engineMain(*this, data);
		    write(data->net.tcp.sock, "/r", 2);
		    data->net.tcp.run = 0;
		    data->net.udp.run_send = 0;
		    data->net.udp.run = 0;
		    fprintf(stdout, "tcp fd closed\n");
		  }
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
	      if (menu->currentItem == 6 && !items[0].type)
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
	      if (items[menu->currentItem].type == MENU_TEXTINPUT)
		menu->hold();
	    }
	  if (event.key.keysym.sym == SDLK_RIGHT)
	    {
	      menu->moveRight();
	      if (items[menu->currentItem].type == MENU_TEXTINPUT)
		menu->hold();
	    }
	  if (event.key.keysym.sym == SDLK_UP)
	    {
	      menu->moveUp();
	      if (items[menu->currentItem].type == MENU_TEXTINPUT)
		menu->hold();
	  }
	  if (event.key.keysym.sym == SDLK_BACKSPACE &&
	      items[menu->currentItem].text.length())
	    {
	      if (!isprint(items[menu->currentItem].text[items[menu->currentItem].text.length() - 1]))
		items[menu->currentItem].text.erase(items[menu->currentItem].text.length() - 2);
	      else
		items[menu->currentItem].text.erase(items[menu->currentItem].text.length() - 1);
	    }
	  else if (items[0].type && menu->currentItem == 6 && event.key.keysym.sym == SDLK_RETURN)
	    loginMenu(items);
	  else if (items[0].type && menu->currentItem == 4 && event.key.keysym.sym == SDLK_RETURN) {
	    if (items[4].text == "AZERTY mode")
	      items[4].text = "QWERTY mode";
	    else
	      items[4].text = "AZERTY mode";
	  } else if (items[0].type && menu->currentItem == 5 && event.key.keysym.sym == SDLK_RETURN) {
	    if (items[5].text == " Set Oculus")
	      items[5].text = "Unset Oculus";
	    else
	      items[5].text = " Set Oculus";
	  } else if (event.key.keysym.sym == SDLK_RETURN &&
	      !items[0].type && menu->currentItem == 5)
	    optionMenu(items);
	  else if (event.key.keysym.sym == SDLK_RETURN &&
	      items[menu->currentItem].type == MENU_TEXTINPUT)
	    menu->hold();
	  else if (event.key.keysym.sym == SDLK_RETURN &&
	      (menu->currentItem == 3 || menu->currentItem == 4) &&
	      !items[0].type)
	    {
	      menu->hold();
	      //Initilisation
	      data->net.port = atoi(items[3].text.c_str());
	      data->net.ip = (char *)items[2].text.c_str();
	      data->net.pseudo = (char *)items[1].text.c_str();
	      this->setClosed(false);

	      // Penser a checker IP + Pseudo + Port

	      if (data->net.port < 0)
		{
		  std::cerr << "Incorrect port\n";
		  break;
		}
	      if (strlen(data->net.pseudo) > 20)
		{
		  std::cerr << "Pseudo is too long\n";
		  break;
		}

#ifdef	DEBUG
	      std::clog << "[Infos] Port = " << data->net.port << "\n";
	      std::clog << "[Infos] Ip = " << data->net.ip << "\n";
	      std::clog << "[Infos] Pseudo = " << data->net.pseudo << "\n";
#endif

	      if (!clientLaunchTcpc(data) && !clientLaunchUdpc(data)) //TCP Start
		{
		  engineMain(*this, data);
		  write(data->net.tcp.sock, "/r", 2);
		  data->net.tcp.run = 0;
		  data->net.udp.run_send = 0;
		  data->net.udp.run = 0;
		  fprintf(stdout, "tcp fd closed\n");
		}
	    }
	  if (event.key.keysym.sym == SDLK_RETURN &&
	      items[0].type && menu->currentItem == 6)
	    loginMenu(items);
	  if (event.key.keysym.sym == SDLK_DOWN)
	    {
	      menu->moveDown();
	      if (items[menu->currentItem].type == MENU_TEXTINPUT)
		menu->hold();
	    }
	  if ((event.key.keysym.sym == SDLK_RETURN
	       || event.key.keysym.sym == SDLK_TAB)
	      && (items[menu->currentItem].type == MENU_TEXTINPUT
		  || menu->currentItem == 0))
	    {
	      menu->moveNext();
	      if (items[menu->currentItem].type == MENU_TEXTINPUT)
		menu->hold();
	    }
	  break;
	case SDL_MOUSEMOTION:
	  if (event.motion.x)
	    event.motion.x -= event.motion.xrel / 3;
	  if (event.motion.y)
	    event.motion.y -= event.motion.yrel / 3;
	  if (items[menu->currentItem].type != MENU_SLIDER ||
	      !menu->holded) {
	    pos->x += event.motion.xrel / 2;
	    pos->y += event.motion.yrel / 2;
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
	      items[menu->currentItem].text.length() < 15)
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
  SDL_BlitSurface(surface, NULL, screen, pos);
  SDL_UpdateWindowSurface(m_window);
  if (items[menu->currentItem].type == MENU_TEXTINPUT)
    items[menu->currentItem].text.erase(items[menu->currentItem].text.length() - 1);
}
