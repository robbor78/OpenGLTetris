

/*
 * FontWriter.h
 *
 *  Created on: 16 Dec 2013
 *      Author: bert
 */

#ifndef FONTWRITER_H_
#define FONTWRITER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <string>
#include <vector>

#define ATLAS_RESOLUTION 1024
#define ATLAS_COLS 16
#define GLYPH_RESOLUTION 64

struct OnePoint {
	float coord[2];
	float tex_coord[2];
};

struct FontMeta {
	//The ASCII value of each glyph
	char ascii;
	//The atlas texture coordinate at the left side of its cell
	float s;
	//The relative width of the glyph
	float width;
	//The atlas texture coordinate at the top of its cell
	float t;
	//The relative height of the glyph
	float height;
	//The "y offset", or relative amount to move the glyph downwards, to make it sit on a common base-line
	float yoffset;
};

class FontWriter {
public:
	FontWriter(std::string& fontFile);
	virtual ~FontWriter();

	void Write(std::string str, int maxLineLength, float xOffset, float yOffset, std::vector<OnePoint>& dest);

private:
	std::map<char, FontMeta> fontMetaData;
};

#endif /* FONTWRITER_H_ */



