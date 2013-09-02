#include "Log.hpp"

#include <stdarg.h>
#include <android/log.h>

void Log::info(const char* msg, ...)
{
	va_list varArgs;
	va_start(varArgs, msg);
	__android_log_vprint(ANDROID_LOG_INFO, "APP", msg, varArgs);
	__android_log_print(ANDROID_LOG_INFO, "APP", "\n");
	va_end(varArgs);
}

void Log::error(const char* msg, ...)
{
	va_list varArgs;
	va_start(varArgs, msg);
	__android_log_vprint(ANDROID_LOG_ERROR, "APP", msg, varArgs);
	__android_log_print(ANDROID_LOG_ERROR, "APP", "\n");
	va_end(varArgs);
}

void Log::warn(const char* msg, ...)
{
	va_list varArgs;
	va_start(varArgs, msg);
	__android_log_vprint(ANDROID_LOG_WARN, "APP", msg, varArgs);
	__android_log_print(ANDROID_LOG_WARN, "APP", "\n");
	va_end(varArgs);
}

void Log::debug(const char* msg, ...)
{
	va_list varArgs;
	va_start(varArgs, msg);
	__android_log_vprint(ANDROID_LOG_DEBUG, "APP", msg, varArgs);
	__android_log_print(ANDROID_LOG_DEBUG, "APP", "\n");
	va_end(varArgs);
}

