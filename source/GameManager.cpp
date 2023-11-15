#include <iostream>
#include <SDL2/SDL.h>

#include "../include/GameManager.h"

GameManager::GameManager(int _w, int _h) {
	window = NULL;
	renderer = NULL;

	if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
		std::cout << "ERROR: COULD NOT START SDL" << "\n";
	}

	window = SDL_CreateWindow("SDL2 - Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _w, _h, SDL_WINDOW_SHOWN);
	if(window == NULL) {
		std::cout << "ERROR: " << SDL_GetError() << "\n"; 
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if(renderer == NULL) {
		std::cout << "ERROR: " << SDL_GetError() << "\n";
	}
}
