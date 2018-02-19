#pragma once
#include <exception>

class Base_Exceptions : public std::exception {
protected:
	std::string _message;
public:
	Base_Exceptions(const std::string& message) : _message(message) { Log(MessageTypes::ERR) << _message; }
	Base_Exceptions(std::string&& message) : _message(message){ Log(MessageTypes::ERR) << _message; }

	virtual const char* what() const throw() { // Because std::exception asks
		return _message.c_str();
	}
};

class Prefix_Base_Exceptions : public Base_Exceptions {
protected:
	std::string _prefix_name;
public:
	Prefix_Base_Exceptions(const std::string& message, const std::string& prefix_name) : _prefix_name(prefix_name), Base_Exceptions(_prefix_name + message){}
	Prefix_Base_Exceptions(std::string&& message, const std::string& prefix_name) :_prefix_name(prefix_name), Base_Exceptions(_prefix_name + message){};
};

class Zguard_Exceptions : public Prefix_Base_Exceptions {
protected:
	const std::string prefix = "Zguard_Exception (on the side of the converters/controllers): ";
public:
	Zguard_Exceptions(const std::string& message) : Prefix_Base_Exceptions(message, _prefix_name) {}
	Zguard_Exceptions(std::string&& message) : Prefix_Base_Exceptions(std::forward<std::string>(message), _prefix_name) {}
};

class Mysql_Exceptions : public Prefix_Base_Exceptions {
protected:
	const std::string prefix = "Mysql_Exception (on the side of the database): ";
public:
	Mysql_Exceptions(const std::string& message) : Prefix_Base_Exceptions(message, _prefix_name) {}
	Mysql_Exceptions(std::string&& message) : Prefix_Base_Exceptions(std::forward<std::string>(message), _prefix_name) {}
};

class Programm_Exceptions : public Prefix_Base_Exceptions {
protected:
	const std::string prefix = "Programm_Exceptions (on the side of the internal programm): ";
public:
	Programm_Exceptions(const std::string& message) : Prefix_Base_Exceptions(message, _prefix_name) {}
	Programm_Exceptions(std::string&& message) : Prefix_Base_Exceptions(std::forward<std::string>(message), _prefix_name) {}
};



//class ConnectionError : public std::exception {
//protected:
//	std::string _message;
//
//public:
//	ConnectionError(const std::string& message) : _message(message) {}
//
//	virtual const char* what() const throw() {
//		return "Connection Exception: ";
//	}
//};
//
//class ThreadAlradyExists : public std::exception {
//
//
//};
//
//class InitializationSearchError : public ConnectionError {
//public :
//	InitializationSearchError(const std::string& message) :
//		ConnectionError((std::string("Error to initial search: ") + message + "\n")){}
//	virtual const char* what() const throw() {
//		return _message.c_str();
//	}
//};
//
//class SearchError : public ConnectionError {
//public:
//	SearchError(const std::string& message) : ConnectionError(std::string("Search ended with an error: ") + message) {}
//	virtual const char* what() const throw() {
//		return _message.c_str();
//	}
//};
//
//class ConstructError : public std::exception {
//private:
//	std::string _message;
//
//public:
//	ConstructError(const std::string& message) : _message(std::string("Error in construct method: " + message)){}
//	virtual const char* what() const throw() {
//		return _message.c_str();
//	}
//};
//
//class CommandError : public std::exception {
//private:
//	std::string _message;
//
//public:
//	CommandError(const std::string& message) : _message(std::string("Error while performing command: ") + message + "\n"){}
//	virtual const char* what() const throw() {
//		return _message.c_str();
//	}
//};
//
//class OpenFailed : public ConnectionError {
//public:
//	OpenFailed(const std::string& message, const std::string& device) :
//		ConnectionError(std::string("Connection failed with: ") + device + std::string(";\n your description: ") + message + "\n") {}
//
//	virtual const char* what() const throw() {
//		return _message.c_str();
//	}
//};

