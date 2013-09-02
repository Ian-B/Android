#ifndef _INPUTSERVICE_HPP_
#define _INPUTSERVICE_HPP_

#include "Sensor.hpp"
#include "Location.hpp"
#include <android_native_app_glue.h>

class InputService
{
public:
	InputService(android_app* application, Sensor* accelerometer);

	int start();
	int update();
	void stop();

	inline float getHorizontal() const
	{
		return posX_;
	}

	inline float getVertical() const
	{
		return posY_;
	}

	inline void setRefPoint(Location* touchReference)
	{
		refPoint_ = touchReference;
	}

public:
	bool onTouchEvent(AInputEvent* event);
	bool onKeyboardEvent(AInputEvent* event);
	bool onTrackballEvent(AInputEvent* event);
	bool onAccelerometerEvent(ASensorEvent* event);

private:
	android_app* application_;
	float posX_, posY_;
	Location* refPoint_;
	int width_, height_;
	bool menuKey_;
	Sensor* accelerometer_;
};

#endif
