/*
 * Space.cpp
 *
 *  Created on: Mar 15, 2015
 *      Author: doli
 */

#include "Space.h"

namespace ev {

void Space::printSpace(void) const {

	const Screen* screen = Screen::instance();

	static char empty_image[] = "images/empty30.bmp"; // case 0
	static char ship_image[] = "images/ship30.bmp"; // case 1
	static char laser_image[] = "images/laser30.bmp"; // case 2
	static char ele_image[] = "images/ele30.bmp"; // case 3
	static char water_image[] = "images/water30.bmp"; // case 4
	static char expl_image[] = "images/expl30.bmp"; // case 5

	for (int x = 0; x < _X; ++x) {
		for (int y = 0; y < _Y; ++y) {
			switch (_space[x][y]) {
			case EMPTY:
				screen->draw(empty_image, x, y);
				break;
			case SHIP:
				screen->draw(ship_image, x, y);
				break;
			case LASER:
				screen->draw(laser_image, x, y);
				break;
			case ELE:
				screen->draw(ele_image, x, y);
				break;
			case WATER:
				screen->draw(water_image, x, y);
				break;
			case EXPL:
				screen->draw(expl_image, x, y);
				break;
			default: // empty as default
				screen->draw(empty_image, x, y);
				break;
			}
		}
	}
	screen->update();
}

void Space::step(const int keyvalue) {
//keyvalue 1=left 2=right 3=shoot 4=nothing 0=nothing

	// clear new space
	for (int x = 0; x < _X; ++x) {
		for (int y = 0; y < _Y; ++y) {
			_new_space[x][y] = EMPTY;
		}
	}

	// Move Ship and shoot
	int y = _Y - 1;
	for (int x = 0; x < _X; ++x) {
		switch (_space[x][y]) {
		case SHIP:
			if (_space[x][top(y)] == WATER) {
				_new_space[x][y] = EXPL;
				_is_ship_destroyed = true;
				_gameover = true;
				return;
			}
			if (keyvalue == 1) {
				if ((x > 0) && (_space[left(x)][y] == EMPTY)
						&& (_space[left(x)][y - 1] == EMPTY)) {
					_new_space[left(x)][y] = SHIP;
					break;
				}
			}
			if (keyvalue == 2) {
				if ((x < (_X - 1)) && (_space[right(x)][y] == EMPTY)
						&& (_space[right(x)][y - 1] == EMPTY)) {
					_new_space[right(x)][y] = SHIP;
					break;
				}
			}
			if (keyvalue == 3) {
				if (_space[x][top(y)] == EMPTY) {
					_new_space[x][y] = SHIP;
					_new_space[x][top(y)] = LASER;
					break;
				}
			}
			_new_space[x][y] = SHIP;
			break;
		default:
			break;
		}
	}

	// check laser
	for (int x = 0; x < _X; ++x) {
		for (int y = 0; y < _Y; ++y) {
			switch (_space[x][y]) {
			case LASER:
				if (_space[x][top(y)] == WATER) {
					_new_space[x][top(y)] = EXPL;
					_space[x][top(y)] = EMPTY;
					break;
				}
				if (_space[x][top(top(y))] == WATER) {
					_new_space[x][top(top(y))] = EXPL;
					_space[x][top(top(y))] = EMPTY;
					break;
				}
				if (_space[x][top(y)] == ELE) {
					_new_space[x][top(y)] = EXPL;
					_space[x][top(y)] = EMPTY;
					--_n_eles;
					if (_n_eles == 0) {
						win();
						exit(1);
						return;
					}
					break;
				}

				if (_space[x][top(y)] == EMPTY) {
					_new_space[x][top(y)] = LASER;
					break;
				}
				break;

			default:
				break;
			}
		}
	}

	// check water
	for (int x = 0; x < _X; ++x) {
		for (int y = 0; y < _Y; ++y) {
			switch (_space[x][y]) {

			case WATER:
				if (_space[x][bottom(y)] == EMPTY) {
					_new_space[x][bottom(y)] = WATER;
					break;
				}
				break;

			default:
				break;
			}
		}
	}

	// check ele
	for (int x = 0; x < _X; ++x) {
		for (int y = 0; y < _Y; ++y) {
			switch (_space[x][y]) {

			case ELE:
				_new_space[x][y] = ELE;
				if (_space[x][bottom(y)] == EMPTY) {
					if (fire()) {
						_new_space[x][bottom(y)] = WATER;
					}
				}
				break;

			default:
				break;
			}
		}
	}

// Ele move
	if (rand() < _pMove) {
		int smallestX = 1000000;
		int biggestX = 0;

		for (int x = 0; x < _X; ++x) {
			for (int y = 0; y < _Y; ++y) {
				switch (_space[x][y]) {
				case ELE:
					if (x < smallestX) {
						smallestX = x;
					}
					if (x > biggestX) {
						biggestX = x;
					}
					break;
				default:
					break;
				}
			}
		}

		if (rand() < 0.5) { //left
			if (smallestX > 1) {
				for (int x = 0; x < _X; ++x) {
					for (int y = 0; y < _Y; ++y) {
						switch (_space[x][y]) {
						case ELE:
							_new_space[left(x)][y] = ELE;
							_new_space[x][y] = EMPTY;
							break;
						default:
							break;
						}
					}
				}
			}
		} else { //right
			if (biggestX < (_X - 1)) {
				for (int x = _X - 1; x > 0; --x) {
					for (int y = 0; y < _Y; ++y) {
						switch (_space[x][y]) {
						case ELE:
							_new_space[right(x)][y] = ELE;
							_new_space[x][y] = EMPTY;
							break;
						default:
							break;
						}
					}
				}
			}
		}
	}

	_space = _new_space;
}

bool Space::is_destroyed(void) const {
	return (_is_ship_destroyed);
}

void Space::gameover(void) {
	const Screen* screen = Screen::instance();
	for (int x = 0; x < _X; ++x) {
		for (int y = 0; y < _Y; ++y) {
			_space[x][y] = EMPTY;
		}
	}
	printSpace();
	static char gameover_image[] = "images/gameover30.bmp";
	screen->draw(gameover_image, _X / 2, _Y / 2);
	screen->update();
	screen->speed(1000);
	screen->update();
	_is_ship_destroyed = true;
	_gameover = true;
}

void Space::win(void) {
	const Screen* screen = Screen::instance();
	for (int x = 0; x < _X; ++x) {
		for (int y = 0; y < _Y; ++y) {
			_space[x][y] = EMPTY;
		}
	}
	printSpace();
	static char win_image[] = "images/win30.bmp";
	screen->draw(win_image, _X / 2, _Y / 2);
	screen->update();
	screen->speed(1000);
	screen->update();
}

Space::Space(const int X, const int Y) :
		_X(X), _Y(Y), _pFire(0.03), _pMove(0.10), _n_eles(0), _gameover(false), _is_ship_destroyed(
				false), _rd(), _mt(_rd()), _rand(0.0, 1.0) {
	setup();
}

Space::Space(void) {
	exit(1);
}

Space::~Space(void) {
}

// ##################
// #	PRIVATE		#
// ##################

int Space::left(const int x) const {
	return (x - 1);
}

int Space::right(const int x) const {
	return (x + 1);
}

int Space::top(const int y) const {
	return (y - 1);
}

int Space::bottom(const int y) const {
	return (y + 1);
}

bool Space::fire(void) {
	if (rand() < _pFire) {
		return (true);
	} else {
		return (false);
	}
}

float Space::rand(void) {
	return (_rand(_mt));
}

void Space::addEle(const int x, const int y) {
	_space[x][y] = ELE;
	++_n_eles;
}

void Space::setup(void) {
// Resize
	_space.resize(_X);
	_new_space.resize(_X);
	for (int x = 0; x < _X; ++x) {
		_space[x].resize(_Y);
		_new_space[x].resize(_Y);
	}

//set all empty
	for (int x = 0; x < _X; ++x) {
		for (int y = 0; y < _Y; ++y) {
			_space[x][y] = EMPTY;
		}
	}

// Set ship
	_space[_X / 2][_Y - 1] = SHIP;

// Set ele
	addEle((_X / 2) - 1, 1);
	addEle((_X / 2) + 1, 1);
	addEle((_X / 2) - 2, 1);
	addEle((_X / 2) + 2, 1);
	addEle((_X / 2) - 3, 1);
	addEle((_X / 2) + 3, 1);

	addEle((_X / 2) - 6, 1);
	addEle((_X / 2) + 6, 1);
	addEle((_X / 2) - 7, 1);
	addEle((_X / 2) + 7, 1);
	addEle((_X / 2) - 8, 1);
	addEle((_X / 2) + 8, 1);

	addEle((_X / 2) - 10, 1);
	addEle((_X / 2) + 10, 1);
	addEle((_X / 2) - 11, 1);
	addEle((_X / 2) + 11, 1);
	addEle((_X / 2) - 12, 1);
	addEle((_X / 2) + 12, 1);

	addEle((_X / 2) - 1, 2);
	addEle((_X / 2) + 1, 2);
	addEle((_X / 2) - 2, 2);
	addEle((_X / 2) + 2, 2);
	addEle((_X / 2) - 3, 2);
	addEle((_X / 2) + 3, 2);

	addEle((_X / 2) - 6, 2);
	addEle((_X / 2) + 6, 2);
	addEle((_X / 2) - 7, 2);
	addEle((_X / 2) + 7, 2);
	addEle((_X / 2) - 8, 2);
	addEle((_X / 2) + 8, 2);

	addEle((_X / 2) - 10, 2);
	addEle((_X / 2) + 10, 2);
	addEle((_X / 2) - 11, 2);
	addEle((_X / 2) + 11, 2);
	addEle((_X / 2) - 12, 2);
	addEle((_X / 2) + 12, 2);

	addEle((_X / 2) - 1, 3);
	addEle((_X / 2) + 1, 3);
	addEle((_X / 2) - 2, 3);
	addEle((_X / 2) + 2, 3);
	addEle((_X / 2) - 3, 3);
	addEle((_X / 2) + 3, 3);

	addEle((_X / 2) - 6, 3);
	addEle((_X / 2) + 6, 3);
	addEle((_X / 2) - 7, 3);
	addEle((_X / 2) + 7, 3);
	addEle((_X / 2) - 8, 3);
	addEle((_X / 2) + 8, 3);

	addEle((_X / 2) - 10, 3);
	addEle((_X / 2) + 10, 3);
	addEle((_X / 2) - 11, 3);
	addEle((_X / 2) + 11, 3);
	addEle((_X / 2) - 12, 3);
	addEle((_X / 2) + 12, 3);

}

} /* namespace ev */
