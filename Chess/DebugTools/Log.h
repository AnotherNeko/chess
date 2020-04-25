/*Log.h*/#pragma once
#include <iostream>
#include <string>

enum LogLevel : char
{
	info, warning, error
};

std::string unsignedchar_toString(unsigned char u);

void Log(LogLevel level, const std::string& message);
void Log(const std::string& message);
void Log(LogLevel level, const std::string& message1, float number, const std::string& message2);

void LogError(const std::string& message);

void LogWarning(const std::string& message);

void LogInfo(const std::string& message);

void Pause();