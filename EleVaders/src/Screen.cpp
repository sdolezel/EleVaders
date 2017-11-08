/*
 * Screen.cpp
 *
 *  Created on: Mar 15, 2015
 *      Author: doli
 */

#include "Screen.h"

namespace ev {

Screen* Screen::_instance = 0;

void Screen::draw(char* file, const int x, const int y) const {
	static SDL_Surface* image;
	static SDL_Rect dest;
	image = SDL_LoadBMP(file);
	if (image == NULL) {
		printf("Can't load image\n");
	}
	dest.w = image->w;
	dest.h = image->h;
	dest.x = image->w * x;
	dest.y = image->h * y;

	//Use this function to perform a fast surface copy to a destination surface.
	SDL_BlitSurface(image, NULL, _screen, &dest); // kopiere das Bild-Surface auf das _screen-surface

	//Makes sure the given list of rectangles is updated on the given screen.
	//SDL_UpdateRects(_screen, 1, &dest);

	// Use this function to free an RGB surface.
	SDL_FreeSurface(image); // Das Bitmap-Surface löschen
}

void Screen::update() const {
	SDL_Flip(_screen); //swaps screen buffers
}

void Screen::speed(int delay) const {
	SDL_Delay(delay);
}

Screen::~Screen() {
	SDL_Delay(2000);
	SDL_Quit();
	delete _instance;
	_instance = 0;
}

Screen* Screen::instance(void) {
	return (_instance);
}

void Screen::create(const int x, const int y) {
	if (!_instance) {
		_instance = new Screen(x, y);
	}
}

Screen::Screen(void) {
}

Screen::Screen(const int x, const int y) {
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		printf("Can't init SDL:  %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	_screen = SDL_SetVideoMode(x, y, 24, SDL_HWSURFACE);

	if (_screen == NULL) {
		printf("Can't set video mode: %s\n", SDL_GetError());
		exit(1);
	}
}

} /* namespace ev */
