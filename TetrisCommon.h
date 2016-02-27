/*
 * TetrisCommon.h
 *
 *  Created on: 15 Dec 2013
 *      Author: bert
 */

#ifndef TETRISCOMMON_H_
#define TETRISCOMMON_H_

#include <vector>

#define TETRIS_SIDE_LENGTH 2

typedef std::vector<bool> PieceRowArray;
typedef std::vector<PieceRowArray> PieceArray;

struct PC {
	float x;
	float y;
	float z;
	float normal[3];
	float colour[3];
};


#endif /* TETRISCOMMON_H_ */
