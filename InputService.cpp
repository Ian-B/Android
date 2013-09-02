#include "InputService.hpp"
#include "Log.hpp"

#include <android_native_app_glue.h>
#include <cmath>

InputService::InputService(android_app* application, Sensor* accelerometer)
	: application_(application), posX_(0.0f), posY_(0.0f),
	  refPoint_(0), width_(0), height_(0), menuKey_(false),
	  accelerometer_(accelerometer)
{
}

int InputService::start()
{
	posX_ = 0.0f;
	posY_ = 0.0f;
	menuKey_ = false;

//	if ((width_ == 0) || (height_ == 0))
//	{
//		Log::error("error width n height");
//		return -1;
//	}
	return 0;
}

int InputService::update()
{
	// sensors if search button is pressed.
	if (menuKey_)
	{
		if (!accelerometer_->toggle())
		{
			return -1;
		}
	}
	menuKey_ = false;
	return 0;
}

void InputService::stop()
{
	accelerometer_->disable();
}

bool InputService::onTouchEvent(AInputEvent* event)
{
	return true;
}

bool InputService::onKeyboardEvent(AInputEvent* event)
{
	return true;
}

bool InputService::onTrackballEvent(AInputEvent* event)
{
	return true;
}

bool InputService::onAccelerometerEvent(ASensorEvent* event)
{
	return true;
}
