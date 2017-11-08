/*
 * Keys.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: doli
 */

#include "Keys.h"

namespace ev {

Keys::Keys() {

}

Keys::~Keys() {
}

int Keys::event(ev::Space& space) {
	while (SDL_PollEvent(&_keyevent)) {
		switch (_keyevent.type) {
		/* Look for a keypress */
		case SDL_KEYDOWN:
			switch (_keyevent.key.keysym.sym) {
			case SDLK_LEFT:
#if DEBUG > 0
				std::cout << "Left" << std::endl;
#endif
				return 1;
				break;
			case SDLK_RIGHT:
#if DEBUG > 0
				std::cout << "Right" << std::endl;
#endif
				return 2;
				break;
			case SDLK_UP:
#if DEBUG > 0
				std::cout << "Up" << std::endl;
#endif
				return 3;
				break;
			case SDLK_DOWN:
#if DEBUG > 0
				std::cout << "Down" << std::endl;
#endif
				return 4;
				break;
			case SDLK_ESCAPE:
#if DEBUG > 0
				std::cout << "ESC" << std::endl;
#endif
				space.Escape();
				break;
			default:
				return 0;
				break;
			}
		default:
			return 0;
			break;
		}
	}
	return 0;
}

} /* namespace ev */
