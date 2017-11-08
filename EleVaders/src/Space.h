/*
 * Space.h
 *
 *  Created on: Mar 15, 2015
 *      Author: doli
 */

#ifndef SPACE_H_
#define SPACE_H_

#include "all.h"
#include "Screen.h"

namespace ev {

class Space {
public:
	void printSpace(void) const;
	void step(const int keyvalue);
	bool is_destroyed(void) const;
	void gameover(void);
	void win(void);
	bool isGameover(void) {
		return _gameover;
	}
	void Escape(void) {
		_gameover = true;
	}

	Space(const int X, const int Y);
	Space(void);
	virtual ~Space(void);

private:
	int top(const int y) const;
	int bottom(const int y) const;
	int left(const int x) const;
	int right(const int x) const;

	bool fire(void);

	void addEle(const int x, const int y);
	void setup(void);
	float rand(void);

	int _X; // x size
	int _Y; // y size

	bool _is_ship_destroyed;
	float _pFire; // prob to fire;
	float _pMove; // prob to ele move;

	int _n_eles;
	bool _gameover;

	std::vector<std::vector<int> > _space;
	std::vector<std::vector<int> > _new_space;

	std::random_device _rd;
	std::mt19937_64 _mt;
	std::uniform_real_distribution<float> _rand;
};

} /* namespace ev */

#endif /* SPACE_H_ */
