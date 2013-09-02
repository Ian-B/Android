/*
 * Shaders.hpp
 *
 *  Created on: 18/01/2013
 *      Author: ian
 */

#ifndef _SHADERS_HPP_
#define _SHADERS_HPP_

#include <GlES2/gl2.h>

class Shaders
{
public:
	int init();
	void draw();

private:
	GLuint loadShader(GLenum type, const GLchar* shaderSrc);
	GLuint programObject_;
};

#endif /* SHADERS_HPP_ */
