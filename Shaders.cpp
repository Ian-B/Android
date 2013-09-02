/*
 * Shaders.cpp
 *
 *  Created on: 18/01/2013
 *      Author: ian
 */

#include "Shaders.hpp"
#include "Log.hpp"
#include "malloc.h"

GLuint Shaders::loadShader(GLenum type, const GLchar* shaderSrc)
{
	GLboolean supported;
	glGetBooleanv(GL_SHADER_COMPILER, &supported);
	if (!supported)
	{
		Log::error("no compile support");
		//TODO: binary shaders
	}

	GLuint shader = glCreateShader(type);
	if (shader == 0) return -1;

	glShaderSource(shader, 1, &shaderSrc, 0);
	glCompileShader(shader);

	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if(!compiled)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 0)
		{
		 void* infoLog = malloc(sizeof(char) * infoLen);
		 glGetShaderInfoLog(shader, infoLen, NULL, static_cast<char*>(infoLog));
		 free (infoLog);
		}
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

int Shaders::init()
{
	const GLchar vShaderStr[] = "attribute vec4 vPosition;   \n"
								"void main()                 \n"
								"{                           \n"
								"   gl_Position = vPosition; \n"
								"}                           \n";

	const GLchar fShaderStr[] = "precision mediump float;                   \n"
								"void main()                                \n"
								"{                                          \n"
								"  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
								"}                                          \n";

	programObject_ = glCreateProgram();
	if (programObject_ == 0) return -1;

	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vShaderStr);
	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fShaderStr);

	glAttachShader(programObject_, vertexShader);
	glAttachShader(programObject_, fragmentShader);

	// Bind vPosition to attribute 0
	glBindAttribLocation(programObject_, 0, "vPosition");

	glLinkProgram(programObject_);

	GLint linked;
	glGetProgramiv(programObject_, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;
		glGetProgramiv(programObject_, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 0)
		{
		 void* infoLog = malloc(sizeof(char) * infoLen);
		 glGetProgramInfoLog(programObject_, infoLen, 0, static_cast<char*>(infoLog));
		 free(infoLog);
		}
		glDeleteProgram(programObject_);
		return -1;
	}
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	return 0;
}

void Shaders::draw()
{
	const GLfloat vertices[] = {0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f};

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(programObject_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

