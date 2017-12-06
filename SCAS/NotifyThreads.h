#pragma once

class NotifyThreads // in thread
{
public:
	NotifyThreads();
	~NotifyThreads();

	void beginListning();
	void createNotifiedThreads();

	std::shared_ptr<HANDLE> _e_clearing;
	std::shared_ptr<HANDLE> _e_newlist;
	std::shared_ptr<HANDLE> _e_at;

private:
	std::vector<std::shared_ptr<Connection>> _localConverterList;
	std::vector<std::unique_ptr<std::thread>> _notifiedThreadsList;
	//std::vector<std::string> _localPortsList;
	std::shared_ptr<HANDLE> _e_localExitThread;

	void createThreads(const int);
};

