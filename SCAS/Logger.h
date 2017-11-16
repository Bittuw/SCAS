#pragma once

// TODO סהוכאעü כמדדונ
class Logger
{
public:

	enum MODES {
		TRACE,
		DEBUG,
		WARNING,
		FAILURE
	};

	enum LEVEL {
		DEBUG_LEVEL_DISABLED = 0,
		DEBUG_LEVEL_WARNING = 1,
		DEBUF_LEVEL_FAILURE = 2
	};

	~Logger();

	static Logger* getInstance();
	
private:
	static std::string Indent;
	
	Logger() {};
	Logger(const char* fileName, const char* funcName, int lineMumber, MODES, LEVEL);
	Logger(Logger const&) = delete;
	Logger& operator=(Logger const&) = delete;
	static Logger* instance;
};
