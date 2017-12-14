#pragma once
#include <exception>

class ConnectionError : public std::exception {
protected:
	std::string _message;

public:
	ConnectionError(const std::string& message) : _message(message) {}

	virtual const char* what() const throw() {
		return "Connection Exception: ";
	}
};

class ThreadAlradyExists : public std::exception {


};

class InitializationSearchError : public ConnectionError {
public :
	InitializationSearchError(const std::string& message) :
		ConnectionError((std::string("Error to initial search: ") + message + "\n")){}
	virtual const char* what() const throw() {
		return _message.c_str();
	}
};

class SearchError : public ConnectionError {
public:
	SearchError(const std::string& message) : ConnectionError(std::string("Search ended with an error: ") + message) {}
	virtual const char* what() const throw() {
		return _message.c_str();
	}
};

class ConstructError : public std::exception {
private:
	std::string _message;

public:
	ConstructError(const std::string& message) : _message(std::string("Error in construct method: " + message)){}
	virtual const char* what() const throw() {
		return _message.c_str();
	}
};

class CommandError : public std::exception {
private:
	std::string _message;

public:
	CommandError(const std::string& message) : _message(std::string("Error while performing command: ") + message + "\n"){}
	virtual const char* what() const throw() {
		return _message.c_str();
	}
};

class OpenFailed : public ConnectionError {
public:
	OpenFailed(const std::string& message, const std::string& device) :
		ConnectionError(std::string("Connection failed with: ") + device + std::string(";\n your description: ") + message + "\n") {}

	virtual const char* what() const throw() {
		return _message.c_str();
	}
};

