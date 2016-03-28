#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <GL/glew.h>

using namespace std;

int	main()
{
  SDL_Window	*win(0);
  SDL_GLContext	context(0);
  SDL_Event	event;
  bool		quit = false;

  if (SDL_Init(SDL_INIT_VIDEO))
    {
      cerr << "Error: Failed to init SDL: " << SDL_GetError() << endl;
      return (1);
    }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  win = SDL_CreateWindow("Cold Cube", SDL_WINDOWPOS_UNDEFINED,
			 SDL_WINDOWPOS_UNDEFINED,
			 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  if (win == NULL)
    {
      cerr << "Error: Failed to start the window: " << SDL_GetError() << endl;
      SDL_Quit();
      return (1);
    }

  context = SDL_GL_CreateContext(win);
  if (!context)
    {
      cerr << "Error: Failed to create the OpenGL context: " << SDL_GetError() << endl;
      SDL_DestroyWindow(win);
      SDL_Quit();
      return (1);
    }

  GLenum	glewInitialisation(glewInit());

  if (glewInitialisation != GLEW_OK)
    {
      cerr << "Error: Failer to init GLEW: " << glewGetErrorString(glewInitialisation) << endl;
      SDL_GL_DeleteContext(context);
      SDL_DestroyWindow(win);
      SDL_Quit();
      return (1);
    }

  while (!quit)
    {
      SDL_WaitEvent(&event);

      if (event.window.event == SDL_WINDOWEVENT_CLOSE)
	quit = true;

      glClear(GL_COLOR_BUFFER_BIT);
      SDL_GL_SwapWindow(win);
    }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return (0);
}
