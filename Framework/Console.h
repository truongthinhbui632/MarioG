#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <string>
#include "Utility.h"

class Console
{
private:
	Console();
	~Console();

public:


	static void Log(const std::string &message);
};

#endif
