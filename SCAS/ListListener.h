#pragma once
template <class T>
class GenerateConnetion
{
public:
	GenerateConnetion(T generate);
	~GenerateConnetion();


	GenerateConnection* instance;
	static T generateInstance(MainInfo);
};

