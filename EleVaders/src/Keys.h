/*
 * Keys.h
 *
 *  Created on: Apr 3, 2015
 *      Author: doli
 */

#ifndef KEYS_H_
#define KEYS_H_

#include "all.h"
#include "Space.h"

namespace ev {

class Keys {
public:
	Keys();
	virtual ~Keys();
	int event(ev::Space& space);
private:
	SDL_Event _keyevent;
};

} /* namespace ev */

#endif /* KEYS_H_ */
