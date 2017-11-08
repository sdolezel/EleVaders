/*
 * Screen.h
 *
 *  Created on: Mar 15, 2015
 *      Author: doli
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "all.h"

namespace ev {

class Screen {
public:
	virtual ~Screen();

	void draw(char* file, const int x, const int y) const;
	void update() const;
	void speed(int delay) const;

	static void create(const int x, const int y);
	static Screen* instance(void);

protected:
	static Screen* _instance;

private:
	SDL_Surface* _screen;

	Screen(void);
	Screen(const int x, const int y);
};

} /* namespace ev */

#endif /* SCREEN_H_ */
