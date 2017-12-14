#pragma once

class NotifyThreads
{
public:
	~NotifyThreads();

	std::shared_ptr<HANDLE> _e_clearing;
	std::shared_ptr<HANDLE> _e_newlist;
	std::shared_ptr<HANDLE> _e_at;

	static void runListening();

private:

	NotifyThreads();
	static bool isRunning;
	
	std::vector<std::shared_ptr<Connection>> _localConverterList;
	std::vector<std::unique_ptr<std::thread>> _notifiedThreadsList;
	//std::vector<std::string> _localPortsList;
	std::shared_ptr<HANDLE> _e_localExitThread;

	///////////////
	void beginListning();
	void createNotifiedThreads();				 
	void createThreads(const int);
	///////////////
};

