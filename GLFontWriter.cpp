/*
 * GLFontWriter.cpp
 *
 *  Created on: 16 Dec 2013
 *      Author: bert
 */

#include "GLFontWriter.h"

GLFontWriter::GLFontWriter() {
	textureData = LoadImage("texgyreheros-bold.png");

	std::string filename = "texgyreheros-bold.meta";
	fw = new FontWriter(filename);

	InitProgram();
	InitTexture();
}

GLFontWriter::~GLFontWriter() {
	glUseProgram(0);

	glDetachShader(program, vs);
	glDetachShader(program, fs);

	glDeleteShader(fs);
	glDeleteShader(vs);

	glDeleteProgram(program);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo_text);

	delete fw;

}

void GLFontWriter::Write(std::string text, int maxLineLength, float xOffset, float yOffset) {
	fw->Write(text, maxLineLength, xOffset, yOffset, textVector);

	glUseProgram(program);
	glDeleteBuffers(1,&vbo_text);
	glGenBuffers(1, &vbo_text);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_text);
	glBufferData(GL_ARRAY_BUFFER, textVector.size() * 4 * 4, &(textVector[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	attribute_vertex_position = get_attrib(program, "vertex_position");
	attribute_vertex_texcoord = get_attrib(program, "vertex_texcoord");
}

void GLFontWriter::Draw() {
	glUseProgram(program);

	glEnableVertexAttribArray(attribute_vertex_position);
	glEnableVertexAttribArray(attribute_vertex_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_text);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glUniform1i(uniform_texturemap, /*GL_TEXTURE*/0);

	glVertexAttribPointer(attribute_vertex_position, 2,
	GL_FLOAT,
	GL_FALSE, sizeof(struct OnePoint),  // stride
	0);  // offset

	glVertexAttribPointer(attribute_vertex_texcoord, 2,
	GL_FLOAT,
	GL_FALSE, sizeof(struct OnePoint),  // stride
	(GLvoid*) offsetof(struct OnePoint, tex_coord));

	int size;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawArrays(GL_TRIANGLES, 0, size / sizeof(OnePoint));

	glDisableVertexAttribArray(attribute_vertex_position);
	glDisableVertexAttribArray(attribute_vertex_texcoord);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLFontWriter::Clear()
{
	textVector.clear();
}

void GLFontWriter::InitProgram() {
	program = create_program("textshader.v.glsl", "textshader.f.glsl", vs, fs);
	if (program == 0)
		return;

}

void GLFontWriter::InitTexture() {

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, // target
	0,  // level, 0 = base, no minimap,
	GL_RGBA, // internalformat
	1024,  // width
	1024,  // height
	0,  // border, always 0 in OpenGL ES
	GL_RGBA,  // format
	GL_UNSIGNED_BYTE, // type
	textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	// work out maximum an-isotropy
	GLfloat max_aniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);
	// set the maximum!
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);

	uniform_texturemap = get_uniform(program, "f_texturemap");
}

unsigned char* GLFontWriter::LoadImage(const char* file_name) {
	int x, y, n;
	int force_channels = 4;
	//const char* file_name = "altas.png";
	unsigned char* image_data = stbi_load(file_name, &x, &y, &n, force_channels);
	if (!image_data) {
		fprintf(stderr, "ERROR: could not load %s\n", file_name);
	}

	// NPOT check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf(
		stderr, "WARNING: texture %s is not power-of-2 dimensions\n", file_name);
	}

	int width_in_bytes = x * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = y / 2;

	for (int row = 0; row < half_height; row++) {
		top = image_data + row * width_in_bytes;
		bottom = image_data + (y - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}

	return image_data;

}
