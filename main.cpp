#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

#include "./include/GameManager.h"
#include "./include/Imaginary.h"

const int WIDTH = 1200;
const int HEIGHT = 800;
bool quit = false;

bool ProcessInput();
void Render();

Uint8 buffer[WIDTH][HEIGHT];
const int MANDELBROT_DEPTH = 100;
double X_MIN = -2.25;
double X_MAX = 0.5;
double Y_MIN = -1;
double Y_MAX = 1;
double lerp(double min, double max, double a);
bool mouseDrag = false;
bool definedSelection = false;
struct MousePos { int x, y; };
MousePos firstMousePos;
MousePos secondMousePos;

int BrotTest(Imaginary i);
void CalculateSet();
void RecalcBounds();

GameManager gm(WIDTH, HEIGHT);

int main() {
	CalculateSet();

	while(ProcessInput() == true) {
		Render();
	}

	SDL_DestroyWindow(gm.window);
	SDL_Quit();

	return 0;
}

bool ProcessInput() {
	while(SDL_PollEvent(&gm.event)) {
		switch(gm.event.type) {
			case SDL_QUIT:
				return false;
				break;
			case SDL_KEYDOWN:
				if(gm.event.key.keysym.sym == SDLK_w && gm.event.key.keysym.mod == 4160) {
					return false;	
				} else if(gm.event.key.keysym.sym == SDLK_c) {
					definedSelection = false;
					RecalcBounds();
					CalculateSet();
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseDrag = true;
				SDL_GetMouseState(&firstMousePos.x, &firstMousePos.y);
				break;
			case SDL_MOUSEMOTION:
				if(mouseDrag) SDL_GetMouseState(&secondMousePos.x, &secondMousePos.y);
				break;
			case SDL_MOUSEBUTTONUP:
				mouseDrag = false;
				definedSelection = true;
				SDL_GetMouseState(&secondMousePos.x, &secondMousePos.y);
				break;
		}
	}
	return true;
}

void Render() {
	SDL_SetRenderDrawColor(gm.renderer, 255, 255, 255, 255);
	SDL_RenderClear(gm.renderer);

	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			switch(buffer[x][y]) {
				case 0:
					SDL_SetRenderDrawColor(gm.renderer, 0, 0, 0, 255);
					break;
				case 1:
					SDL_SetRenderDrawColor(gm.renderer, 255, 255, 255, 255);
					break;
			}
			SDL_RenderDrawPoint(gm.renderer, x, y);
		}
	}

	if(mouseDrag || definedSelection) {
		SDL_SetRenderDrawColor(gm.renderer, 155, 0, 0, 50);
		SDL_Rect rect;
		rect.x = firstMousePos.x;
		rect.y = firstMousePos.y;
		rect.w = secondMousePos.x - firstMousePos.x;
		rect.h = secondMousePos.y - firstMousePos.y;
		SDL_RenderFillRect(gm.renderer, &rect);
	}

	SDL_RenderPresent(gm.renderer);
}

void CalculateSet() {
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			Imaginary c(
				lerp(X_MIN, X_MAX, ((double)x / WIDTH)),
				lerp(Y_MIN, Y_MAX, ((double)y / HEIGHT))
			);
			buffer[x][y] = BrotTest(c);
		}
	}
}

void RecalcBounds() {
	double xmint = lerp(X_MIN, X_MAX, (double)firstMousePos.x / WIDTH);
	double xmaxt = lerp(X_MIN, X_MAX, (double)secondMousePos.x / WIDTH);
	double ymint = lerp(Y_MIN, Y_MAX, (double)firstMousePos.y / HEIGHT);
	double ymaxt = lerp(Y_MIN, Y_MAX, (double)secondMousePos.y / HEIGHT);
	X_MIN = xmint;
	X_MAX = xmaxt;
	Y_MIN = ymint;
	Y_MAX = ymaxt;
}

int BrotTest(Imaginary c) {
	Imaginary z(0.0, 0.0);
	for(int i = 0; i < MANDELBROT_DEPTH; i++) {
		z.square();
		z.add(c);
		if((z.imaginary * z.imaginary) + (z.real * z.real) > 225) return 0;
	}
	return 1;
}

double lerp(double min, double max, double a) {
	return a * (max - min) + min; 
}
