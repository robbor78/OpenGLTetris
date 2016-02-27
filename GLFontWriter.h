/*
 * GLFontWriter.h
 *
 *  Created on: 16 Dec 2013
 *      Author: bert
 */

#ifndef GLFONTWRITER_H_
#define GLFONTWRITER_H_

#include <GL/glew.h>

#include <vector>

#include "stb_image.h"
#include "shader_utils.h"
#include "FontWriter.h"

class GLFontWriter {
public:
	GLFontWriter();
	virtual ~GLFontWriter();

	void Write(std::string text, int maxLineLength, float xOffset, float yOffset);
	void Draw();
	void Clear();

private:
	unsigned char* textureData;
	GLuint program, vs, fs;
	GLuint textureId;
	GLint uniform_texturemap;
	GLuint vbo_text;
	FontWriter* fw;
	GLint attribute_vertex_position, attribute_vertex_texcoord;
	std::vector<OnePoint> textVector;

	void InitProgram();
	void InitTexture();
	unsigned char* LoadImage(const char* file_name);
};

#endif /* GLFONTWRITER_H_ */
