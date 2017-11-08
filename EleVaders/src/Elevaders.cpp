//============================================================================
// Name        : Elevaders.cpp
// Author      : Stefan Dolezel
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include "all.h"

#include "Screen.h"
#include "Space.h"
#include "Keys.h"

void game_loop(ev::Space& space, ev::Keys& keys) {
	space.step(keys.event(space));
	space.printSpace();
}

int main(void) {

	// Variables
	static const int PIXELSIZE = 30;
	static const int X = 900 / PIXELSIZE;
	static const int Y = 900 / PIXELSIZE;
	int step = 0;

	int delay = 50;

	ev::Keys keys;

	ev::Screen::create(X * PIXELSIZE, Y * PIXELSIZE);
	ev::Screen* screen = ev::Screen::instance();

	ev::Space space(X, Y);
	space.printSpace();

	// Main loop
	while (!space.isGameover()) {
		++step;
#if DEBUG > 0
		std::cout << "Step " << step << std::endl;
#endif
		game_loop(space, keys);
		screen->speed(delay);

	}

	space.gameover();
	space.~Space();
	return EXIT_SUCCESS;
}
