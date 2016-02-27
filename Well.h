/*
 * Well.h
 *
 *  Created on: 10 Dec 2013
 *      Author: bert
 */

#ifndef WELL_H_
#define WELL_H_

#include "AbstractPiece.h"
#include "Piece.h"

class Well : public AbstractPiece {

public:
	Well(int maxCol, int maxRow, float x, float y, float z);

	bool CanAdd(Piece& other);
	void Add(Piece& other);
	bool CanMove(Piece& other, int incCol = 0, int incRow = 1);
	void Drop(Piece& other);
	bool CanRotateLeft(Piece& other);
	bool CanRotateRight(Piece& other);

	void MakeGrid(std::vector<float> &cs);

protected:
	virtual void CreateContainer();

private:

	int maxCol, maxRow;
	bool IsThereSpaceHere(int col, int row);
	void RemoveFullRows();

};

#endif /* WELL_H_ */
