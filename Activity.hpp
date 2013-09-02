#ifndef _ACTIVITY_HPP_
#define _ACTIVITY_HPP_

#include "Context.hpp"
#include "GraphicsService.hpp"
#include "InputService.hpp"

class Activity
{
public:
	explicit Activity(Context* context);

	int onActivate();
	void onDeactivate();
	int onStep();

	void onStart();
	void onResume();
	void onPause();
	void onStop();
	void onDestroy();

	void onSaveState(void** data, size_t* size);
	void onConfigurationChanged();
	void onLowMemory();

	void onCreateWindow();
	void onDestroyWindow();
	void onGainFocus();
	void onLostFocus();

private:
	GraphicsService* graphicsService_;
	InputService* inputService_;
};

#endif
