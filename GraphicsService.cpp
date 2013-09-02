#include "GraphicsService.hpp"
#include "Log.hpp"

GraphicsService::GraphicsService(android_app* application)
	: application_(application), display_(EGL_NO_DISPLAY), surface_(EGL_NO_CONTEXT),
	  context_(EGL_NO_SURFACE), width_(0), height_(0)
{
	shaders_ = new Shaders();
}

GraphicsService::~GraphicsService()
{
	delete shaders_;
	shaders_ = 0;
}

int GraphicsService::start()
{
	if(create() != 0)
	{
		Log::error("error creating egl setup");
	}
	if(shaders_->init() != 0)
	{
		Log::error("error in shader setup");
	}
	return 0;
}

int GraphicsService::update()
{
	shaders_->draw();

	//Render
	if (eglSwapBuffers(display_, surface_) != EGL_TRUE)
	{
		Log::error("Fail swap buffer");
		return -1;
	}
	return 0;
}

void GraphicsService::stop()
{
	if (display_ != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (context_ != EGL_NO_CONTEXT)
		{
			eglDestroyContext(display_, context_);
			context_ = EGL_NO_CONTEXT;
		}
		if (surface_ != EGL_NO_SURFACE)
		{
			eglDestroySurface(display_, surface_);
			surface_ = EGL_NO_SURFACE;
		}
		eglTerminate(display_);
		display_ = EGL_NO_DISPLAY;
	}
}

int GraphicsService::create()
{
	EGLint format, numConfigs, errorResult;
	EGLConfig config;

	const EGLint configAttr[] = { EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
								  EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8,
								  EGL_RED_SIZE, 8, EGL_DEPTH_SIZE, 16,
								  EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
								  EGL_NONE };

	display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (display_ == EGL_NO_DISPLAY)
	{
		Log::error("Fail to get default Display");
		stop();
		return -1;
	}
	if (!eglInitialize(display_, 0, 0))
	{
		Log::error("Fail initialize display");
		stop();
		return -1;
	}
	if (!eglChooseConfig(display_, configAttr, &config, 1, &numConfigs) ||
	   (numConfigs <= 0))
	{
		Log::error("Fail to choose a config");
		stop();
		return -1;
	}
	if (!eglGetConfigAttrib(display_, config, EGL_NATIVE_VISUAL_ID, &format))
	{
		Log::error("Fail to config android display with EGL");
		stop();
		return -1;
	}
	//change window buffers
	ANativeWindow_setBuffersGeometry(application_->window, 0, 0, format);

	// Create display surface.
	surface_ = eglCreateWindowSurface(display_, config, application_->window, 0);
	if (surface_ == EGL_NO_SURFACE)
	{
		Log::error("Fail create surface");
		stop();
		return -1;
	}
	const EGLint contextAttr[] = { EGL_CONTEXT_CLIENT_VERSION, 2,
								   EGL_NONE, EGL_NONE};

	context_ = eglCreateContext(display_, config, EGL_NO_CONTEXT, contextAttr);
	if (context_ == EGL_NO_CONTEXT)
	{
		Log::error("failed to create context");
		stop();
		return -1;
	}
	// Activate display surface.
	if (!eglMakeCurrent(display_, surface_, surface_, context_)	||
		!eglQuerySurface(display_, surface_, EGL_WIDTH, &width_) ||
		!eglQuerySurface(display_, surface_, EGL_HEIGHT, &height_) ||
		(width_ <= 0) || (height_ <= 0))
	{
		Log::error("Fail to make current surface");
		stop();
		return -1;
	}
	glViewport(0, 0, width_, height_);
	return 0;
}
