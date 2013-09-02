#include "EventLoop.hpp"

EventLoop::EventLoop(android_app* application)
	: enabled_(false), quit_(false), application_(application),
	  activity_(0), input_(0), sensorPollSource_(),
	  sensorManager_(0), sensorEventQueue_(0)
{
	application_->userData = this;
	application_->onAppCmd = callback_event;
	application_->onInputEvent = callback_input;
}

void EventLoop::run(Activity* activity, InputService* input)
{
	// Make sure native glue is not stripped by the linker.
	app_dummy();

	int result;
	int events;
	android_poll_source* source;

	activity_ = activity;
	input_ = input;

	// Global step loop.
	while (true)
	{
		// Event processing loop.
		while ((result = ALooper_pollAll(enabled_ ? 0 : -1, 0, &events,
				reinterpret_cast<void**>(&source))) >= 0)
		{
			if (source != 0)
			{
				source->process(application_, source);
			}
			if (application_->destroyRequested)
			{
				return;
			}
		}
		if ((enabled_) && (!quit_))
		{
			if (activity_->onStep() != 0)
			{
				quit_ = true;
				ANativeActivity_finish(application_->activity);
			}
		}
	}
}

//	ASensorManager_getSensorList //TODO: check this
//	ASENSOR_TYPE_ACCELEROMETER
//	ASENSOR_TYPE_MAGNETIC_FIELD
//	ASENSOR_TYPE_GYROSCOPE
//	ASENSOR_TYPE_LIGHT
//	ASENSOR_TYPE_PROXIMITY

void EventLoop::activate()
{
	if ((!enabled_) && (application_->window != 0))
	{
		sensorPollSource_.id = LOOPER_ID_USER;
		sensorPollSource_.app = application_;
		sensorPollSource_.process = callback_sensor;
		sensorManager_ = ASensorManager_getInstance();
		if (sensorManager_ != 0)
		{
			sensorEventQueue_ =
					ASensorManager_createEventQueue(sensorManager_,
													application_->looper,
													LOOPER_ID_USER,
													0,
													&sensorPollSource_);
			if (sensorEventQueue_ == 0) return;
		}

		quit_ = false;
		enabled_ = true;
		if (activity_->onActivate() != 0)
		{
			quit_ = true;
			deactivate();
			ANativeActivity_finish(application_->activity);
		}
	}
	return;
}

void EventLoop::deactivate()
{
	if (enabled_)
	{
		activity_->onDeactivate();
		enabled_ = false;

		if (sensorEventQueue_ != 0)
		{
			ASensorManager_destroyEventQueue(sensorManager_,
											 sensorEventQueue_);
			sensorEventQueue_ = 0;
		}
		sensorManager_ = 0;
	}
}

void EventLoop::processAppEvent(int command)
{
	switch (command)
	{
		case APP_CMD_CONFIG_CHANGED:
			activity_->onConfigurationChanged();
			break;
		case APP_CMD_INIT_WINDOW:
			activity_->onCreateWindow();
			break;
		case APP_CMD_DESTROY:
			activity_->onDestroy();
			break;
		case APP_CMD_GAINED_FOCUS:
			activate();
			activity_->onGainFocus();
			break;
		case APP_CMD_LOST_FOCUS:
			activity_->onLostFocus();
			deactivate();
			break;
		case APP_CMD_LOW_MEMORY:
			activity_->onLowMemory();
			break;
		case APP_CMD_PAUSE:
			activity_->onPause();
			deactivate();
			break;
		case APP_CMD_RESUME:
			activity_->onResume();
			break;
		case APP_CMD_SAVE_STATE:
			activity_->onSaveState(&application_->savedState,
								   &application_->savedStateSize);
			break;
		case APP_CMD_START:
			activity_->onStart();
			break;
		case APP_CMD_STOP:
			activity_->onStop();
			break;
		case APP_CMD_TERM_WINDOW:
			activity_->onDestroyWindow();
			deactivate();
			break;
		default:
			break;
	}
}

int EventLoop::processInputEvent(AInputEvent* event)
{
	return 0;
}

void EventLoop::processSensorEvent()
{
}

//main call back event loop(makes stuff happen)
void EventLoop::callback_event(android_app* application, int command)
{
	EventLoop& eventLoop = *(static_cast<EventLoop*>(application->userData));
	eventLoop.processAppEvent(command);
}

int EventLoop::callback_input(android_app* application,
							  AInputEvent* event)
{
	EventLoop& eventLoop = *(static_cast<EventLoop*>(application->userData));
	return eventLoop.processInputEvent(event);
}

void EventLoop::callback_sensor(android_app* application,
								android_poll_source* source)
{
	EventLoop& eventLoop = *(static_cast<EventLoop*>(application->userData));
	eventLoop.processSensorEvent();
}
