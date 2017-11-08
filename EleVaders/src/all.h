/*
 * all.h
 *
 *  Created on: Mar 15, 2015
 *      Author: doli
 */

#ifndef ALL_H_
#define ALL_H_

#define EMPTY 0
#define SHIP 1
#define LASER 2
#define ELE 3
#define WATER 4
#define EXPL 5

#define _GXX_EXPERIMENTAL_CXX0X__ 1

#include <cstdlib>
#include <random>
#include <vector>

#include <unistd.h> // sleep

#if DEBUG > 0
#include <iostream>
#endif

#include "SDL/SDL.h"

#endif /* ALL_H_ */
