//
// Created by Vlad Boroday on 2023-12-04.
//

#ifndef UNTITLED1_ENGINE_UTILITIES_LOGGER_H_
#define UNTITLED1_ENGINE_UTILITIES_LOGGER_H_

#include "Engine/Types.h"

namespace SEngine
{
	class Logger
	{
	 public:
		enum Level
		{
			LOG_ALL = 0,
			// Display all logs
			LOG_TRACE,
			// Trace logging, intended for internal use only
			LOG_DEBUG,
			// Debug logging, used for internal debugging, it should be disabled on release builds
			LOG_INFO,
			// Info logging, used for program execution info
			LOG_WARNING,
			// Warning logging, used on recoverable failures
			LOG_ERROR,
			// Error logging, used on unrecoverable failures
			LOG_FATAL,
			// Fatal logging, used to abort program: exit(EXIT_FAILURE)
			LOG_NONE // Disable logging
		};

		static void Log(Level level, const String& message);
		static void Log(Level level, const char* message);
	};
}

#endif //UNTITLED1_ENGINE_UTILITIES_LOGGER_H_
