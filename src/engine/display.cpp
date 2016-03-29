#include <GL/glew.h>
#include <GL/gl.h>
#include "engine/display.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include "common_structs.hpp"
#include "game.hpp"
#include "tools.hpp"

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
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_SetRelativeMouseMode(SDL_TRUE);
  m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
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

void	Display::Update(Camera &cam, Map &map)
{
  SDL_GL_SwapWindow(m_window);
  // static	int cur(0), old(0), tot(0), nb(0);
  // cur = SDL_GetTicks();
  // int		t = cur - old + 1;
  // float		dTime = t / 1000.0f;
  // old = cur;
  SDL_Event	e;

  // tot += 1000 / t;
  // nb++;
  // if (nb == 1)
  //   tot = 0;
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
	      cam.GetPos() += cam.GetFor() * 50.0f;
	      break ;
	    case (SDLK_s):
	      cam.GetPos() -= cam.GetFor() * 50.0f;
	      break ;
	    case (SDLK_q):
	      cam.GetPos() += normalize(vec3((cross(cam.GetFor(), vec3(0, 1, 0))).x, (cross(cam.GetFor(), vec3(0, 1, 0))).y, 0));
	      break ;
	    case (SDLK_d):
	      cam.GetPos() -= normalize(vec3((cross(cam.GetFor(), vec3(0, 1, 0))).x, (cross(cam.GetFor(), vec3(0, 1, 0))).y, 0));
	      break ;
	    case (SDLK_a):
	      cam.GetPos() += vec3(0, 1, 0);
	      break ;
	    case (SDLK_e):
	      cam.GetPos() -= vec3(0, 1, 0);
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
	  cam.GetRot().y -= e.motion.xrel / 20.0f;
	  cam.GetRot().x -= e.motion.yrel / 20.0f;
	  if (cam.GetRot().x > 89.99f)
	    cam.GetRot().x = 89.99f;
	  if (cam.GetRot().x < -89.99f)
	    cam.GetRot().x = -89.99f;
	  cam.UpdateFor();
	  break ;
	}
    }
}

void	Display::UpdateMenu(Menu *menu, std::vector<menuItem> &items,
			    SDL_Rect *pos, SDL_Surface *screen,
			    SDL_Surface *surface, t_data *data)
{
  SDL_Event	event;

  while (SDL_PollEvent(&event))
    {
      switch(event.type)
	{
	case SDL_QUIT:
	  data->game.running = false;
	  break;
	case SDL_KEYDOWN:
	  if (event.key.keysym.sym == SDLK_ESCAPE)
	    {
	      data->game.running = false;
	      break;
	    }
	  if (event.key.keysym.sym == SDLK_DOWN)
	    menu->moveDown();
	  if (event.key.keysym.sym == SDLK_UP)
	    menu->moveUp();
	  if (event.key.keysym.sym == SDLK_BACKSPACE &&
	      items[menu->currentItem].text.length())
	    items[menu->currentItem].text.erase(items[menu->currentItem].text.length() - 1);
	  if (event.key.keysym.sym == SDLK_RETURN)
	    {
	      //Initilisation
	      data->net.port = atoi(items[3].text.c_str());
	      data->net.ip = (char *)items[4].text.c_str();
	      data->net.pseudo = (char *)items[5].text.c_str();
	      this->setClosed(false);

	      // Penser a checker IP + Pseudo + Port

	      printf("Port = %d\n", data->net.port);
	      printf("Ip = %s\n", data->net.ip);
	      printf("Pseudo = %s\n", data->net.pseudo);
	      if (!clientLaunchTcpc(data) && !clientLaunchUdpc(data)) //TCP Start
		{
		  engineMain(*this);
		}
	    }
	  break;
	case SDL_MOUSEMOTION:
	  pos->x = event.motion.x - 20;
	  pos->y = event.motion.y - 20;
	  menu->hover(event.motion.x, event.motion.y);
	  break;
	case SDL_TEXTINPUT:
	  printf("readed \"%s\"\n", event.text.text);
	  items[menu->currentItem].text += event.text.text;
	  break;
	}
      SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
      menu->draw();
      SDL_BlitSurface(surface, NULL, screen, pos);
      SDL_UpdateWindowSurface(m_window);
    }
}
