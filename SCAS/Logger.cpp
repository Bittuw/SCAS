#include "stdafx.h"
#include "Logger.h"

Logger* Logger::instance = nullptr;

Logger::Logger()
{
}


Logger::~Logger()
{
}

Logger* Logger::getInstance() {

	if (instance == nullptr)
		instance = new Logger;

	return instance;
}