/*
 * AbstractPiece.h
 *
 *  Created on: 15 Dec 2013
 *      Author: bert
 */

#ifndef ABSTRACTPIECE_H_
#define ABSTRACTPIECE_H_

#include "TetrisCommon.h"

class AbstractPiece {
public:
	AbstractPiece(float x, float y, float z);
	virtual ~AbstractPiece();
	virtual void Reset(float x = 0.0, float y = 0.0, float z = 0.0);
	virtual void ConvertToCubes(std::vector<float> &cs, std::vector<unsigned short> &el);

	PieceArray getContainer() {
		return container;
	}

	int getLeft() const {
		return left;
	}

	int getSideLength() const {
		return sideLength;
	}

	int getTop() const {
		return top;
	}

	float getX() const {
		return x;
	}

	float getY() const {
		return y;
	}

	float getZ() const {
		return z;
	}

	void setBlue(float blue) {
		this->blue = blue;
	}

	void setGreen(float green) {
		this->green = green;
	}

	void setRed(float red) {
		this->red = red;
	}

protected:
	float x, y, z;
	int left;
	int top;
	int sideLength;
	PieceArray container;
	float red, green, blue;

	virtual void CreateContainer()=0;
	int GetSmallestDistance(int wellRow, int pieceRowInWell, int currentDistanc);
	void PushIntoVector(std::vector<float> &vector, PC &pc, float *normal, float* colour);

private:

	void MakeElements(std::vector<unsigned short> &el, int numElements, int cubeNum);

};

#endif /* ABSTRACTPIECE_H_ */
