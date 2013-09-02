#ifndef _GRAPHICSSERVICE_HPP_
#define _GRAPHICSSERVICE_HPP_

#include <android_native_app_glue.h>
#include "Shaders.hpp"

#include <EGL/egl.h>
#include <GLES2/gl2.h>

class GraphicsService
{
public:
	GraphicsService(android_app* application);
	~GraphicsService();

	int start();
	int update();
	void stop();

	//TODO: gets can only be called after start
	inline EGLint getHeight() const { return height_; }
	inline EGLint getWidth() const { return width_; }

private:
	int create();
	android_app* application_;
	EGLint width_, height_;
	EGLDisplay display_;
	EGLSurface surface_;
	EGLContext context_;
	Shaders* shaders_;
};

#endif
