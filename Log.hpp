#ifndef _LOG_HPP_
#define _LOG_HPP_

class Log
{
public:
	static void error(const char* msg, ...);
	static void warn(const char* msg, ...);
	static void info(const char* msg, ...);
	static void debug(const char* msg, ...);
};

#ifndef NDEBUG
#define app_Log_debug(...) app::Log::debug(__VA_ARGS__)
#else
#define app_Log_debug(...)
#endif

#endif
