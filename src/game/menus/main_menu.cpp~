#include "SDL2/SDL.h"
#include "SDL2/SDL_video.h"
#include "Menu.h"

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *zozor = NULL;
    SDL_Rect positionZozor;
    SDL_Event event;
    int continuer = 1;
    std::vector<menuItem> items(5);

    items[0].text = "Start";
    items[1].text = "Options";
    items[2].text = "Quit";
    items[3].text = "server port";
    items[4].text = "server IP";

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window*	m_window = SDL_CreateWindow("toto", 0, 0, 500, 500, 0);

    ecran = SDL_GetWindowSurface(m_window);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    Menu *menu = new Menu(ecran, &items);

    zozor = SDL_LoadBMP("assets/imgs/cursor.bmp");
    SDL_SetColorKey(zozor, 0, SDL_MapRGB(zozor->format, 0, 0, 0));
    //SDL_SetColorKey(zozor, SDL_TRUE, 0);

    positionZozor.x = ecran->w / 2 - zozor->w / 2;
    positionZozor.y = ecran->h / 2 - zozor->h / 2;

    SDL_ShowCursor(SDL_DISABLE);
            std::string inputText = "Some Text";
            //gInputTextTexture.loadFromRenderedText( inputText.c_str(), {0, 0, 0, 0xFF});

            //Enable text input
            SDL_StartTextInput();
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
	    case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_DOWN)
		  menu->moveDown();
		if (event.key.keysym.sym == SDLK_UP)
		  menu->moveUp();
		if (event.key.keysym.sym == SDLK_BACKSPACE)
		  items[menu->currentItem].text.erase(items[menu->currentItem].text.length() - 1);
		break;
	    case SDL_MOUSEMOTION:
		positionZozor.x = event.motion.x - 20;
		positionZozor.y = event.motion.y - 20;
		menu->hover(event.motion.x, event.motion.y);
                break;
	    case SDL_TEXTINPUT:
		printf("readed \"%s\"\n", event.text.text);
		items[menu->currentItem].text += event.text.text;
		break;
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	menu->draw();
        SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
	SDL_UpdateWindowSurface(m_window);
    }

    SDL_FreeSurface(zozor);
    SDL_Quit();

    return EXIT_SUCCESS;
}
