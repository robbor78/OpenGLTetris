/*
 * CurrentPiece.cpp
 *
 *  Created on: 10 Dec 2013
 *      Author: bert
 */

#include "Piece.h"

Piece::Piece(int size, float x, float y, float z) :
		AbstractPiece(x, y, z) {

	this->size = size;

	CreateContainer();

}

Piece::~Piece() {

}

void Piece::Reset(float x, float y, float z) {
	AbstractPiece::Reset(x,y,z);
	incX = 0.0;
	incY = -0.2;
	incZ = 0.0;
}

void Piece::CreateContainer() {
	container = PieceArray(size);

	for (int c = 0; c < size; c++) {
		container[c] = PieceRowArray(size);
		for (int r = 0; r < size; r++) {
			container[c][r] = false;
		}
	}
}

void Piece::Set(int col, int row, bool flag) {
	if (col < 0 || col >= this->size)
		return;
	if (row < 0 || row >= this->size)
		return;

	container[col][row] = flag;
}

void Piece::Increment(bool isIncX, bool isIncY, bool isIncZ) {
	x += (isIncX ? incX : 0.0);
	y += (isIncY ? incY : 0.0);
	z += (isIncZ ? incZ : 0.0);
}

void Piece::Move(int incCol, int incRow, bool isAdjustXandY, bool isAdjustAbsolute) {
	top += incRow;
	left += incCol;

	if (isAdjustXandY) {
		if (isAdjustAbsolute) {
			x = (float) (left * sideLength);
			y = (float) (-top * sideLength);
		} else {
			x += (float) (incCol * sideLength);
			y += (float) (-incRow * sideLength);
		}
	}
}

void Piece::RotateLeft() {
	int n = size;
	int f = floor((float) n / 2.0);
	int c = ceil((float) n / 2.0);

	for (int x = 0; x < f; x++)
		for (int y = 0; y < c; y++) {

			bool temp = container[x][y];
			container[x][y] = container[n - 1 - y][x];
			container[n - 1 - y][x] = container[n - 1 - x][n - 1 - y];
			container[n - 1 - x][n - 1 - y] = container[y][n - 1 - x];
			container[y][n - 1 - x] = temp;
		}
}

void Piece::RotateRight() {
	int n = size;
	int f = floor((float) n / 2.0);
	int c = ceil((float) n / 2.0);

	for (int x = 0; x < f; x++)
		for (int y = 0; y < c; y++) {

			bool temp = container[x][y];
			container[x][y] = container[y][n - 1 - x];

			container[y][n - 1 - x] = container[n - 1 - x][n - 1 - y];
			container[n - 1 - x][n - 1 - y] = container[n - 1 - y][x];
			container[n - 1 - y][x] = temp;
		}

	RemoveGaps();
}

void Piece::RemoveGaps() {
	int emptyRows = 0;
	int emptyCols = size;
	bool isRowEmpty = true;
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (container[col][row]) {
				isRowEmpty = false;
				if (col < emptyCols) {
					emptyCols = col;
				}
				break;
			}
		}
		if (isRowEmpty) {
			emptyRows++;
		}
	}

	if (emptyRows > 0 || (emptyCols > 0 && emptyCols < size)) {
		for (int row = emptyRows; row < size; row++) {
			for (int col = emptyCols; col < size; col++) {
				container[col - emptyCols][row - emptyRows] = container[col][row];
				container[col][row] = false;
			}

		}
	}
}

int Piece::GetBottomRow() {
	for (int row = size - 1; row >= 0; row--) {
		for (int col = size - 1; col >= 0; col--) {
			if (container[col][row])
				return row;
		}
	}
	return 0;
}

bool Piece::MustMove() {
	float upperBound = -(float) (top * sideLength) - incY / 2.0;

	return y <= upperBound;
}
