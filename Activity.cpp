#include "Activity.hpp"
#include "Log.hpp"

Activity::Activity(Context* context)
	:
	  graphicsService_(context->graphicsService_),
	  inputService_(context->inputService_)
{
}

int Activity::onActivate()
{
	// Starts services.
	if (graphicsService_->start() != 0)
	{
		Log::error("graphics service start error");
		return -1;
	}
	if (inputService_->start() != 0)
	{
		Log::error("input service start error");
		return -1;
	}
	return 0;
}

void Activity::onDeactivate()
{
	graphicsService_->stop();
	inputService_->stop();
}

int Activity::onStep()
{
	// Updates services.
	if (graphicsService_->update() != 0)
	{
		Log::error("graphics service update error");
		return -1;
	}
	if (inputService_->update() != 0)
	{
		Log::error("input service update error");
		return -1;
	}
	return 0;
}

void Activity::onStart()
{
}

void Activity::onResume()
{
}

void Activity::onPause()
{
}

void Activity::onStop()
{
}

void Activity::onDestroy()
{
}

void Activity::onSaveState(void** data, size_t* size)
{
}

void Activity::onConfigurationChanged()
{
}

void Activity::onLowMemory()
{
}

void Activity::onCreateWindow()
{
}

void Activity::onDestroyWindow()
{
}

void Activity::onGainFocus()
{
}

void Activity::onLostFocus()
{
}
