//
// Created by Vlad Boroday on 2023-12-04.
//

#include "Logger.h"

void SEngine::Logger::Log(Logger::Level level, const SEngine::String& message)
{
	Log(level, message.c_str());
}
void SEngine::Logger::Log(Logger::Level level, const char* message)
{
	TraceLog(static_cast<int>(level), message);
}
