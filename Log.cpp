/*Log.cpp*/#include <iostream>
#include "Log.h"

static std::string LevelToString(LogLevel level)
{
	switch (level) {
	case info :
		return("        [INFO] ");
		break;
	case warning :
		return("    [WARN] ");
		break;
	case error :
		return("[ERROR] ");
	}
}

std::string unsignedchar_toString(unsigned char u)
{
	char buffer[3];
	snprintf(buffer, 4, "%u", u);
	return(std::string(buffer));
}

void Log(LogLevel level, const std::string& message)
{
	std::cout << LevelToString(level) << message << std::endl;
}

void Log(LogLevel level, const std::string& message1, float number, const std::string& message2)
{
	std::cout << LevelToString(level) << message1 << number << message2 << std::endl;
}

void LogError(const std::string& message)
{
	std::cout << LevelToString(error) << message << std::endl;
}

void LogWarning(const std::string& message)
{
	std::cout << LevelToString(warning) << message << std::endl;
}

void LogInfo(const std::string& message)
{
	std::cout << LevelToString(info) << message << std::endl;
}

void Log(const std::string& message)
{
	std::cout << LevelToString(info) << message << std::endl;
}


void Pause()
{
	std::cin.get();
}
