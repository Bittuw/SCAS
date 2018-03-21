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
	Zguard_Exceptions(const std::string& message) : Prefix_Base_Exceptions(message, prefix) {}
	Zguard_Exceptions(std::string&& message) : Prefix_Base_Exceptions(std::forward<std::string>(message), prefix) {}
};

class Mysql_Exceptions : public Prefix_Base_Exceptions {
protected:
	const std::string prefix = "Mysql_Exception (on the side of the database): ";
public:
	Mysql_Exceptions(const std::string& message) : Prefix_Base_Exceptions(message, prefix) {}
	Mysql_Exceptions(std::string&& message) : Prefix_Base_Exceptions(std::forward<std::string>(message), prefix) {}
};

class Programm_Exceptions : public Prefix_Base_Exceptions {
protected:
	const std::string prefix = "Programm_Exceptions (on the side of the internal programm): ";
public:
	Programm_Exceptions(const std::string& message) : Prefix_Base_Exceptions(message, prefix) {}
	Programm_Exceptions(std::string&& message) : Prefix_Base_Exceptions(std::forward<std::string>(message), prefix) {}
};

class Not_Found_Exception : public Prefix_Base_Exceptions {
protected:
	const std::string prefix = "Not_Found_Exception:";
public:
	Not_Found_Exception(const std::string& message) : Prefix_Base_Exceptions(message, prefix) {}
	Not_Found_Exception(std::string& message) : Prefix_Base_Exceptions(std::forward<std::string>(message), prefix) {}
};