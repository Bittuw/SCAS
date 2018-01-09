#pragma once
enum Mode {
	WriteConsoleOnly = 0,
	WriteDestinationOnly = 1,
	WriteDestinationAndConsole = 2
};

enum MessageTypes {
	TRACE = 0,
	DEBUG = 1,
	WARNING = 2,
	ERR = 3,
	FAILURE = 4,
	EVENT = 5
};

enum CommandTypes {
	UNDEFINE = 0,
	STANDART_MESSAGE = 1,
	EXCEPTION_MESSAGE = 2,
	EXIT = 3
};

static std::string TypeMessageString[] = {
	"TRACE", // Вывод в консоль 
	"DEBUG", // Вывод в файл out_debug
	"WARNING", // Вывод в файл out_debug
	"ERROR", // Вывод в фалй out_error
	"FAILURE", // Вывод в файл out_error
	"EVENT" // Вывод в файл out_event
};

struct CurrentTime {
private:
	unsigned short tSecond;
	unsigned short tMinute;
	unsigned short tHour;
	unsigned short tDay;
	unsigned short tMonth;
	unsigned short tYear;

	std::string sSecond;
	std::string sMinute;
	std::string sHour;
	std::string sDay;
	std::string sMonth;
	std::string sYear;

public:
	std::string tCurrentTime;

	CurrentTime() {
		SYSTEMTIME currentTime;
		GetLocalTime(&currentTime);

		tSecond = currentTime.wSecond;
		tMinute = currentTime.wMinute;
		tHour = currentTime.wHour;
		tDay = currentTime.wDay;
		tMonth = currentTime.wMonth;
		tYear = currentTime.wYear;
		
		std::stringstream ss;
		ss << std::setfill('0') << std::setw(2) << std::right << tDay << ' ';
		ss << std::setfill('0') << std::setw(2) << std::right << tMonth << ' ';
		ss << std::setfill('0') << std::setw(4) << std::right << tYear << ' ';
		ss << std::setfill('0') << std::setw(2) << std::right << tHour << ' ';
		ss << std::setfill('0') << std::setw(2) << std::right << tMinute << ' ';
		ss << std::setfill('0') << std::setw(2) << std::right << tSecond << ' ';

		ss >> sDay >> sMonth >> sYear >> sHour >> sMinute >> sSecond;

		tCurrentTime = sDay + ":" + sMonth + ":" + sYear + " " + sHour + ":" + sMinute + ":" + sSecond;
	};

	friend std::ostream& operator<<(std::ostream& stream, const CurrentTime&);
};

struct ChannalLine {
	std::string Name;
	std::ostream& out_dist;
	Mode mode;
};

struct LoggerMessage {
	std::string message;
	CurrentTime time;
	MessageTypes Type;
	friend std::ostream& operator<<(std::ostream&, const LoggerMessage&);
};

struct CommandMessage {
	CommandTypes type;
	LoggerMessage data;
};

//struct FunctionMatrix {
//	std::function<void> func;
//};

typedef ChannalLine Channal; // канал записи
typedef LoggerMessage Message; // Сообщения
typedef CommandMessage Command; // Команды
typedef std::queue<Command> MessageQueue; // очередь команд
//typedef FunctionMatrix Action[sizeof(CommandTypes)]; // Массив функций

class Logger
{
public:

	~Logger();

	Logger& operator()(MessageTypes&& = TRACE);
	void* operator new(size_t) = delete;
	void operator<<(const char&);
	void operator<<(const std::string&);
	static Logger createInstance();

private:
	Logger();

	std::shared_ptr<MessageQueue> _queue;
	std::shared_ptr<std::mutex> _mutex; // Мьютекс доступа
	std::shared_ptr<std::condition_variable> _wakeUp;
	MessageTypes typeMessage;

	//CloseLogger& operator=(const CloseLogger&);
	Logger(const Logger&);

	const std::unique_ptr<std::map<std::thread::id, std::string>> thread_list;

	static bool created;
};

extern Logger& Log;

class LoggingThread {
public:
	LoggingThread(std::shared_ptr<MessageQueue>&, std::shared_ptr<std::mutex>&, std::shared_ptr<std::condition_variable>&);
	static void startThread(std::shared_ptr<MessageQueue>&, std::shared_ptr<std::mutex>&, std::shared_ptr<std::condition_variable>&);
	LoggingThread(const LoggingThread&) = delete;
	void* operator new[](size_t) = delete;
	void operator delete[](void*) = delete;
	void operator delete(void* pointer);

private:
	explicit LoggingThread(){};
	void* operator new(size_t);

	std::shared_ptr<MessageQueue> _queue;
	std::shared_ptr<std::mutex> _mutex;
	std::shared_ptr<std::condition_variable> _wakeUp;

	std::ofstream out_debug;
	std::ofstream out_error;
	std::ofstream out_event;

	std::vector<Channal> destination;
	std::string path;

	void RunningInThread();

	

	static bool created;
};