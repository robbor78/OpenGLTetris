/*
 * AbstractPiece.cpp
 *
 *  Created on: 15 Dec 2013
 *      Author: bert
 */

#include "AbstractPiece.h"

AbstractPiece::AbstractPiece(float x, float y, float z) {

	Reset(0.0, 0.0, 0.0);

}

AbstractPiece::~AbstractPiece() {
}

void AbstractPiece::Reset(float x, float y, float z) {
	top = 0;
	left = 0;
	sideLength = TETRIS_SIDE_LENGTH;
	this->x = x;
	this->y = y;
	this->z = z;
	red = 1.0f;
	blue = 1.0f;
	green = 1.0f;
}

void AbstractPiece::ConvertToCubes(std::vector<float> &cs, std::vector<unsigned short> &el) {

	cs.clear();
	el.clear();

	int numElements = 24;
	int cubeNum = 0;

	int col = 0;
	for (PieceArray::iterator c = container.begin(); c != container.end(); ++c) {

		int row = -1;
		for (PieceRowArray::iterator r = (*c).begin(); r != (*c).end(); ++r) {
			row++;
			if (!(*r))
				continue;

			PC f_bl = { (float) (col * sideLength), (float) (-(row + 1) * sideLength), -1.0 };
			PC f_br = { f_bl.x + sideLength, f_bl.y, -1.0 };
			PC f_tl = { f_bl.x, f_bl.y + sideLength, -1.0 };
			PC f_tr = { f_br.x, f_tl.y, -1.0 };
			PC b_tl = { f_tl.x, f_tl.y, 1.0 };
			PC b_tr = { f_tr.x, f_tr.y, 1.0 };
			PC b_bl = { f_bl.x, f_bl.y, 1.0 };
			PC b_br = { f_tr.x, f_bl.y, 1.0 };

			//front
			PushIntoVector(cs, f_bl, new float[3] { 0.0, 0.0, -1.0 }, new float[3] { 1.0, 0.0, 0.0 });
			PushIntoVector(cs, f_br, new float[3] { 0.0, 0.0, -1.0 }, new float[3] { 1.0, 0.0, 0.0 });
			PushIntoVector(cs, f_tr, new float[3] { 0.0, 0.0, -1.0 }, new float[3] { 1.0, 0.0, 0.0 });
			PushIntoVector(cs, f_tl, new float[3] { 0.0, 0.0, -1.0 }, new float[3] { 1.0, 0.0, 0.0 });

			//top
			PushIntoVector(cs, f_tl, new float[3] { 0.0, 1.0, 0.0 }, new float[3] { 0.1, 0.8, 0.0 });
			PushIntoVector(cs, f_tr, new float[3] { 0.0, 1.0, 0.0 }, new float[3] { 0.1, 0.8, 0.0 });
			PushIntoVector(cs, b_tr, new float[3] { 0.0, 1.0, 0.0 }, new float[3] { 0.1, 0.8, 0.0 });
			PushIntoVector(cs, b_tl, new float[3] { 0.0, 1.0, 0.0 }, new float[3] { 0.1, 0.8, 0.0 });

			//back
			PushIntoVector(cs, b_br, new float[3] { 0.0, 0.0, 1.0 }, new float[3] { red, green, blue });
			PushIntoVector(cs, b_bl, new float[3] { 0.0, 0.0, 1.0 }, new float[3] { red, green, blue });
			PushIntoVector(cs, b_tl, new float[3] { 0.0, 0.0, 1.0 }, new float[3] { red, green, blue });
			PushIntoVector(cs, b_tr, new float[3] { 0.0, 0.0, 1.0 }, new float[3] { red, green, blue });

			//bottom
			PushIntoVector(cs, b_bl, new float[3] { 0.0, -1.0, 0.0 }, new float[3] { 0.0, 0.5, 0.5 });
			PushIntoVector(cs, b_br, new float[3] { 0.0, -1.0, 0.0 }, new float[3] { 0.0, 0.5, 0.5 });
			PushIntoVector(cs, f_br, new float[3] { 0.0, -1.0, 0.0 }, new float[3] { 0.0, 0.5, 0.5 });
			PushIntoVector(cs, f_bl, new float[3] { 0.0, -1.0, 0.0 }, new float[3] { 0.0, 0.5, 0.5 });

			//left
			PushIntoVector(cs, b_bl, new float[3] { -1.0, 0.0, 0.0 }, new float[3] { 0.5, 0.5, 0.0 });
			PushIntoVector(cs, f_bl, new float[3] { -1.0, 0.0, 0.0 }, new float[3] { 0.5, 0.5, 0.0 });
			PushIntoVector(cs, f_tl, new float[3] { -1.0, 0.0, 0.0 }, new float[3] { 0.5, 0.5, 0.0 });
			PushIntoVector(cs, b_tl, new float[3] { -1.0, 0.0, 0.0 }, new float[3] { 0.5, 0.5, 0.0 });

			//right
			PushIntoVector(cs, f_br, new float[3] { 1.0, 0.0, 0.0 }, new float[3] { 1.0, 0.2, 0.4 });
			PushIntoVector(cs, b_br, new float[3] { 1.0, 0.0, 0.0 }, new float[3] { 1.0, 0.2, 0.4 });
			PushIntoVector(cs, b_tr, new float[3] { 1.0, 0.0, 0.0 }, new float[3] { 1.0, 0.2, 0.4 });
			PushIntoVector(cs, f_tr, new float[3] { 1.0, 0.0, 0.0 }, new float[3] { 1.0, 0.2, 0.4 });

			MakeElements(el, numElements, cubeNum);

			cubeNum++; //increment the cube counter;

		}
		col++;

	}

}

void AbstractPiece::PushIntoVector(std::vector<float> &cs, PC &pc, float *normal, float* colour) {
	cs.push_back(pc.x);
	cs.push_back(pc.y);
	cs.push_back(pc.z);

	cs.push_back(normal[0]);
	cs.push_back(normal[1]);
	cs.push_back(normal[2]);

	cs.push_back(colour[0]);
	cs.push_back(colour[1]);
	cs.push_back(colour[2]);
}

void AbstractPiece::MakeElements(std::vector<unsigned short> &el, int numElements, int cubeNum) {

	int offset = numElements * cubeNum;
//front
	el.push_back(0 + offset);
	el.push_back(1 + offset);
	el.push_back(2 + offset);
	el.push_back(2 + offset);
	el.push_back(3 + offset);
	el.push_back(0 + offset);
//top
	el.push_back(4 + offset);
	el.push_back(5 + offset);
	el.push_back(6 + offset);
	el.push_back(6 + offset);
	el.push_back(7 + offset);
	el.push_back(4 + offset);
//back
	el.push_back(8 + offset);
	el.push_back(9 + offset);
	el.push_back(10 + offset);
	el.push_back(10 + offset);
	el.push_back(11 + offset);
	el.push_back(8 + offset);
//bottom
	el.push_back(12 + offset);
	el.push_back(13 + offset);
	el.push_back(14 + offset);
	el.push_back(14 + offset);
	el.push_back(15 + offset);
	el.push_back(12 + offset);
//left
	el.push_back(16 + offset);
	el.push_back(17 + offset);
	el.push_back(18 + offset);
	el.push_back(18 + offset);
	el.push_back(19 + offset);
	el.push_back(16 + offset);
//rightunsigned
	el.push_back(20 + offset);
	el.push_back(21 + offset);
	el.push_back(22 + offset);
	el.push_back(22 + offset);
	el.push_back(23 + offset);
	el.push_back(20 + offset);

}

int AbstractPiece::GetSmallestDistance(int wellRow, int pieceRowInWell, int currentDistance) {
	int newDD = wellRow - pieceRowInWell; //calculate distance
	if (newDD < currentDistance) {
		return newDD;
	} else {
		return currentDistance;
	}
}

