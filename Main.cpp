#include "Context.hpp"
#include "Activity.hpp"
#include "EventLoop.hpp"
#include "GraphicsService.hpp"
#include "InputService.hpp"
#include "Sensor.hpp"

void android_main(android_app* application)
{
	GraphicsService graphicsService(application);
	EventLoop eventLoop(application);
	Sensor accelerometer(&eventLoop, ASENSOR_TYPE_ACCELEROMETER);
	InputService inputService(application, &accelerometer);

	Context context = { &graphicsService,
					    &inputService };

	Activity activity(&context);
	eventLoop.run(&activity, &inputService);
}

//TODO: asset storage et al.
//<android/configuration.h>
//<android/asset_manager.h>
//<android/storage_manager.h>
//<android/obb.h>
