#pragma once
#include <string>
#include "UsefulFunctions.h"
#include "CommandLineArguments.h"

class ArgumentParser
{
private:
	CommandLineArguments commandLineArguments;
	bool isCorrect;
	void parseArguments(int argumentsAmount, char* arguments[]);
public:
	bool getIsCorrect();
	ArgumentParser(int argumentsAmount, char* arguments[]);
	CommandLineArguments getCommandLineArguments();
	void showArguments();
	void showHelp();
};