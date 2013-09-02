#ifndef _SENSOR_HPP_
#define _SENSOR_HPP_

#include <android/sensor.h>

class EventLoop;

class Sensor
{
public:
	Sensor(EventLoop* eventLoop, int sensorType);

	int toggle();
	int enable();
	int disable();

private:
	EventLoop* eventLoop_;
	const ASensor* sensor_;
	int sensorType_;
};

#endif
