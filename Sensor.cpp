#include "Sensor.hpp"
#include "EventLoop.hpp"
#include "Log.hpp"

Sensor::Sensor(EventLoop* eventLoop, int sensorType)
	: eventLoop_(eventLoop), sensor_(0), sensorType_(sensorType)
{
}

int Sensor::toggle()
{
	return (sensor_ != 0) ? disable() : enable();
}

int Sensor::enable()
{
	if (eventLoop_->enabled_)
	{
		sensor_ = ASensorManager_getDefaultSensor(eventLoop_->sensorManager_,
												  sensorType_);
		if (sensor_ != 0)
		{
			if (ASensorEventQueue_enableSensor(eventLoop_->sensorEventQueue_,
											   sensor_) < 0)
			{
				disable();
				return -1;
			}
			const char* name = ASensor_getName(sensor_);
			const char* vendor = ASensor_getVendor(sensor_);
			float resolution = ASensor_getResolution(sensor_);

			int minDelay = ASensor_getMinDelay(sensor_);
			if (ASensorEventQueue_setEventRate(eventLoop_->sensorEventQueue_,
											   sensor_, minDelay) < 0)
			{
				disable();
				return -1;
			}
		}
		else
		{
			Log::error("No sensor type %d", sensorType_);
		}
	}
	return 0;
}

int Sensor::disable()
{
	if ((eventLoop_->enabled_) && (sensor_ != 0))
	{
		if (ASensorEventQueue_disableSensor(eventLoop_->sensorEventQueue_, sensor_) < 0)
		{
			return -1;
		}
		sensor_ = 0;
	}
	return 0;
}

