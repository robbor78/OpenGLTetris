


/*
 * FontWriter.cpp
 *
 *  Created on: 16 Dec 2013
 *      Author: bert
 */

#include "FontWriter.h"

FontWriter::FontWriter(std::string& fontFilename) {
	std::string line;
	std::ifstream fontFile(fontFilename.c_str());
	if (fontFile.is_open()) {
		while (getline(fontFile, line)) {
			std::cout << line << '\n';

			if (line.substr(0, 2).compare("//") == 0)
				continue;

			std::istringstream f(line);
			std::string s;
			FontMeta fm;

			getline(f, s, ' ');
			std::cout << s << std::endl;
			fm.ascii = atoi(s.c_str());

			getline(f, s, ' ');
			std::cout << s << std::endl;
			fm.s = atof(s.c_str());

			getline(f, s, ' ');
			std::cout << s << std::endl;
			fm.width = atof(s.c_str());

			getline(f, s, ' ');
			std::cout << s << std::endl;
			fm.t = atof(s.c_str());

			getline(f, s, ' ');
			std::cout << s << std::endl;
			fm.height = atof(s.c_str());

			getline(f, s, ' ');
			std::cout << s << std::endl;
			fm.yoffset = atof(s.c_str());

			fontMetaData[fm.ascii] = fm;

		}
		fontFile.close();
	}

	else
		std::cout << "Unable to open file";

}

FontWriter::~FontWriter() {
	// TODO Auto-generated destructor stub
}

/**
 * Source: http://antongerdelan.net/opengl/bitmapfonts.html
 */
void FontWriter::Write(std::string text, int maxLineLength, float xOffset, float yOffset, std::vector<OnePoint>& dest) {
	// Get size or length of string.
	int length = text.size();
	// 'cursor' position
	float current_x_pos = xOffset;
	float current_y_pos = yOffset;

	float glyph_resolution = (float) GLYPH_RESOLUTION / (float) ATLAS_RESOLUTION; // 0.0625f;
	float glyph_width = glyph_resolution;

	int charCount = 0;
	for (int i = 0; i < length; i++) {
//	    // get ascii code as integer
		int ascii_code = text[i];
		FontMeta fm = fontMetaData[ascii_code];
//
//	    // work out row and column in atlas
		//int atlas_col = (ascii_code - ' ') % ATLAS_COLS;
		//int atlas_row = (ascii_code - ' ') / ATLAS_COLS;
//	    // work out texture coordinates in atlas
		float s = fm.s;		// (float) atlas_col * glyph_resolution;
		float t = 1.0f - fm.t;		// 1.0f - (float) atlas_row * glyph_resolution;
		float scale = 1.0f;
		glyph_width = scale * fm.width;
		float glyph_height = scale * fm.height;
//
//	    // work out position of glyph
		float x_pos = current_x_pos;
		float y_pos = current_y_pos + scale * fm.yoffset;		// glyph_y_offset;
		current_x_pos += glyph_width;
		if ((i > 0 && charCount == maxLineLength) || text[i] == '\n') {
			current_x_pos = xOffset;
			current_y_pos -= scale * glyph_resolution;
			charCount = 0;
		}
		charCount++;
//
//	    add point and texture coordinates to buffers
		OnePoint result;
		result.coord[0] = x_pos;
		result.coord[1] = y_pos;
		result.tex_coord[0] = s;
		result.tex_coord[1] = t - fm.height;		//glyph_resolution;
		dest.push_back(result);

		result.coord[0] = x_pos + glyph_width;
		result.coord[1] = y_pos + glyph_height;
		result.tex_coord[0] = s + fm.width;		//glyph_resolution;
		result.tex_coord[1] = t;
		dest.push_back(result);

		result.coord[0] = x_pos;
		result.coord[1] = y_pos + glyph_height;
		result.tex_coord[0] = s;
		result.tex_coord[1] = t;
		dest.push_back(result);

		result.coord[0] = x_pos;
		result.coord[1] = y_pos;
		result.tex_coord[0] = s;
		result.tex_coord[1] = t - fm.height;		//glyph_resolution;
		dest.push_back(result);

		result.coord[0] = x_pos + glyph_width;
		result.coord[1] = y_pos;
		result.tex_coord[0] = s + fm.width;		//glyph_resolution;
		result.tex_coord[1] = t - fm.height;		//glyph_resolution;
		dest.push_back(result);

		result.coord[0] = x_pos + glyph_width;
		result.coord[1] = y_pos + glyph_height;
		result.tex_coord[0] = s + fm.width;		//glyph_resolution;
		result.tex_coord[1] = t;
		dest.push_back(result);
	}
}
