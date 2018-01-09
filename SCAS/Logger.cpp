#include "stdafx.h"
#include <process.h>
#include <Windows.h>
#include "DbgHelp.h"
#pragma comment(lib, "dbghelp.lib")
#include "Logger.h"

//#define TRACE_MAX_STACK_FRAMES 1024
//#define TRACE_MAX_FUNCTION_NAME_LENGTH 1024

std::ostream& operator<<(std::ostream& stream, const CurrentTime& time) {
	stream << time.tCurrentTime;
	return stream;
}
std::ostream& operator<<(std::ostream& stream, const LoggerMessage& message) {
	stream << TypeMessageString[message.Type] << "  " << message.message;
	return stream;
}
Logger& Log = Logger::createInstance();

Logger::Logger() :
_queue(std::make_shared<MessageQueue>()),
_mutex(std::make_shared<std::mutex>()),
_wakeUp(std::make_shared<std::condition_variable>())
{ // TODO создание директории, всех файлов, первичное сообщение 
	LoggingThread::startThread(_queue, _mutex, _wakeUp);
	//_wakeUp->notify_one();
}

Logger& Logger::operator()(MessageTypes&& type) {
	_mutex->lock();
	typeMessage = type;
	return *this; 
}

void Logger::operator<<(const char& str) { // TODO ¬ запихнуть в очередь и сделать поток
	Command command = { STANDART_MESSAGE ,{ std::to_string(str), CurrentTime(), typeMessage } };
	_queue->push(command);
	/*if (destination[typeMessage].mode == 2)  std::cout << TypeMessageString[typeMessage] << " || " << time << " || " << str << std::endl;
	destination[typeMessage].out_dist << TypeMessageString[typeMessage] << " || " << time << " || " << str << std::endl;*/
	_mutex->unlock();
	_wakeUp->notify_one();
	//printStackTrace();
}

void Logger::operator<<(const std::string& str) { // TODO ¬ запихнуть в очередь и сделать поток
	Command command = { STANDART_MESSAGE , { str, CurrentTime(), typeMessage } };
	_queue->push(command);
	/*if (destination[typeMessage].mode == 2)  std::cout << TypeMessageString[typeMessage] << " || "<< time << " || " << str << std::endl;
	destination[typeMessage].out_dist << TypeMessageString[typeMessage] << " || " << time << " || " << str << std::endl;*/
	_mutex->unlock();
	_wakeUp->notify_one();
	//printStackTrace();
}


Logger::~Logger() {
	/*out_error.close();*/
} 

bool Logger::created = false;
std::mutex mutex;

Logger Logger::createInstance() {
	if (!created) {
		created = true;
		return Logger();
	}
	else {
		
	}
}

bool LoggingThread::created = false;

LoggingThread::LoggingThread(std::shared_ptr<MessageQueue>& queue, std::shared_ptr<std::mutex>& mutex, std::shared_ptr<std::condition_variable>& wakeUp) :
_queue(queue),
_mutex(mutex),
_wakeUp(wakeUp)
{	

	wchar_t buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, sizeof(buffer));
	std::wstring buffer_w(buffer);
	auto pos = buffer_w.find_last_of(L"\\");
	buffer_w = buffer_w.substr(0, pos) + L"\\Log";
	path = std::string(buffer_w.begin(), buffer_w.end());

	_tmkdir(buffer_w.c_str());

	out_debug = std::ofstream(path + std::string("\\DLog.log"), std::ofstream::ate | std::ofstream::app);
	out_debug << std::endl;

	out_error = std::ofstream(path + std::string("\\ERLog.log"), std::ofstream::ate | std::ofstream::app);
	out_error << std::endl;

	out_event = std::ofstream(path + std::string("\\EVLog.log"), std::ofstream::ate | std::ofstream::app);
	out_event << std::endl;

	destination = {
		{ TypeMessageString[TRACE], std::cout, WriteConsoleOnly },
		{ TypeMessageString[DEBUG], this->out_debug, WriteDestinationAndConsole },
		{ TypeMessageString[WARNING], this->out_debug, WriteDestinationAndConsole },
		{ TypeMessageString[ERR], this->out_error, WriteDestinationAndConsole },
		{ TypeMessageString[FAILURE], this->out_error, WriteDestinationAndConsole },
		{ TypeMessageString[EVENT], this->out_event, WriteDestinationAndConsole }
	};

	std::ios_base::sync_with_stdio(false);
}

void LoggingThread::startThread(std::shared_ptr<MessageQueue>& queue, std::shared_ptr<std::mutex>& mutex, std::shared_ptr<std::condition_variable>& wakeUp) {
	if (!created) {
		std::thread LoggingThread(&RunningInThread, new LoggingThread(queue, mutex, wakeUp));
		LoggingThread.detach();
		created = true;
	}
	else {
		Log(ERR) << std::string("Second attempt to create a class \"Logger\"!");
	}
}

void* LoggingThread::operator new(size_t size) {
	return malloc(size);
}

void LoggingThread::operator delete(void* pointer) {
	delete pointer;
}

void LoggingThread::RunningInThread() {
	while (true) {
		std::unique_lock<std::mutex> lock(*_mutex);
		_wakeUp->wait(lock);
		auto command = _queue->front();
		_queue->pop();
		lock.unlock();
		if (destination[command.data.Type].mode == 2)  std::cout << TypeMessageString[command.data.Type] << " || " << command.data.time << " || " << command.data.message << std::endl;
		destination[command.data.Type].out_dist << TypeMessageString[command.data.Type] << " || " << command.data.time << " || " << command.data.message << std::endl;
	}
}
//int printStackTrace() // TODO изучить
//{
//	void *stack[TRACE_MAX_STACK_FRAMES];
//	HANDLE process = GetCurrentProcess();
//	SymInitialize(process, NULL, TRUE);
//	WORD numberOfFrames = CaptureStackBackTrace(0, TRACE_MAX_STACK_FRAMES, stack, NULL);
//	SYMBOL_INFO *symbol = (SYMBOL_INFO *)malloc(sizeof(SYMBOL_INFO) + (TRACE_MAX_FUNCTION_NAME_LENGTH - 1) * sizeof(TCHAR));
//	symbol->MaxNameLen = TRACE_MAX_FUNCTION_NAME_LENGTH;
//	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
//	DWORD displacement;
//	IMAGEHLP_LINE64 *line = (IMAGEHLP_LINE64 *)malloc(sizeof(IMAGEHLP_LINE64));
//	line->SizeOfStruct = sizeof(IMAGEHLP_LINE64);
//	for (int i = 0; i < numberOfFrames; i++)
//	{
//		DWORD64 address = (DWORD64)(stack[i]);
//		SymFromAddr(process, address, NULL, symbol);
//		if (SymGetLineFromAddr64(process, address, &displacement, line))
//		{
//			printf("\tat %s in %s: line: %lu: address: 0x%0X\n", symbol->Name, line->FileName, line->LineNumber, symbol->Address);
//		}
//		else
//		{
//			printf("\tSymGetLineFromAddr64 returned error code %lu.\n", GetLastError());
//			printf("\tat %s, address 0x%0X.\n", symbol->Name, symbol->Address);
//		}
//	}
//	return 0;
//}