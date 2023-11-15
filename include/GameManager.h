#include <SDL2/SDL.h>
#pragma once

class GameManager {
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	GameManager(int _w, int _h);
};
