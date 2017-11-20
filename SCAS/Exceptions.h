#pragma once
#include <exception>

class ConnectionError : public std::exception {

public:
	virtual const char* what() const throw() {
		return "Connection Exception";
	}
};

class InitializationSearchError : public ConnectionError {
private:
	std::string _message;

public :
	InitializationSearchError(const std::string& message) :
	_message(std::string("Error to initial search: ") + message){}
	virtual const char* what() const throw() override {
		return _message.c_str();
	}
};

class SearchError : public ConnectionError {
private :
	std::string _message;

public:
	SearchError(const std::string& message) : _message(std::string("Search ended with an error: ") + message) {}
	virtual const char* what() const throw() override {
		return _message.c_str();
	}
};

class OpenFailed : public ConnectionError {
private:
	std::string _message;

public:
	OpenFailed(const std::string& message, const std::string& device) :
		_message(std::string("Connection failed with : ") + device + std::string(";\n your message: ") + message) {}

	virtual const char* what() const throw() override {
		return _message.c_str();
	}

};

