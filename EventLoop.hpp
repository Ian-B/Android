#ifndef _EVENTLOOP_HPP_
#define _EVENTLOOP_HPP_

#include "Activity.hpp"
#include <android_native_app_glue.h>

class EventLoop
{
public:
	explicit EventLoop(android_app* application);

	void run(Activity* activity, InputService* input);

protected:
	void activate();
	void deactivate();
	void processAppEvent(int command);
	int processInputEvent(AInputEvent* event);
	void processSensorEvent();

private:
	friend class Sensor;

	static void callback_event(android_app* application, int command);

	static int callback_input(android_app* application, AInputEvent* event);

	static void callback_sensor(android_app* application,
								android_poll_source* source);

private:
	bool enabled_;
	bool quit_;
	android_app* application_;
	Activity* activity_;
	InputService* input_;
	ASensorManager* sensorManager_;
	ASensorEventQueue* sensorEventQueue_;
	android_poll_source sensorPollSource_;
};

#endif
