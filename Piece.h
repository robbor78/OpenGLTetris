/*
 * CurrentPiece.h
 *
 *  Created on: 10 Dec 2013
 *      Author: bert
 */

#ifndef PIECE_H_
#define PIECE_H_

#include <stdlib.h>
#include <math.h>

#include "AbstractPiece.h"

class Piece : public AbstractPiece {

public:
	Piece(int size, float x=0.0f, float y=0.0f, float z=0.0f);
	virtual ~Piece();

	void Reset(float x = 0.0, float y = 0.0, float z = 0.0);

	void Set(int col, int row, bool flag);

	bool MustMove();

	void RotateLeft();
	void RotateRight();

	void Increment(bool incX, bool incY, bool incZ);
	void Move(int incCol, int incRow, bool isAdjustXandY = false, bool isAdjustAbsolute = false);

	int GetBottomRow();

	int GetSize() {return size;}

	float getIncX() const {
		return incX;
	}

	float getIncY() const {
		return incY;
	}

	float getIncZ() const {
		return incZ;
	}

protected:
	virtual void CreateContainer();

private:
	int size;
	float incX, incY, incZ;

	void RemoveGaps();
};

#endif /* PIECE_H_ */
