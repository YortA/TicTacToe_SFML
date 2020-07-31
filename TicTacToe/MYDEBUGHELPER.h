#pragma once
#include <time.h>
#include <iostream>
#include <ctime>
#include <chrono>
#pragma warning(disable : 4996)

// This is my test debugger. Checking timestamps of the actions in the program
class myDebugger 
{
private:
public:
	void my_debug_timer(std::string str1)
	{
		//time_t debugTimer = time(NULL);

		//tm* ltm = localtime(&debugTimer);

		//cerr << ltm->tm_min << ':' << ltm->tm_sec << ' ' << str1 << endl;

		unsigned __int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		std::cerr << now << ": " << str1 << std::endl;
	}

	void my_debug_timer2()
	{
		unsigned __int64 dtimer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		std::cerr << dtimer << ": ";
	}
};