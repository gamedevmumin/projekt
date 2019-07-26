#include "ArgumentParser.h"
/**
@param argumentsAmount liczba argumentow uruchomieniowych podanych przez uzytkownika
@param arguments[] argumenty uruchomieniowe podane przez uzytkownika
parsuje argumenty podane przez uzytkownika i w razie blednego ich podania ustawia flage isCorrect na false
*/
void ArgumentParser::parseArguments(int argumentsAmount, char* arguments[])
{
	for (int i = 1; i < argumentsAmount; i++)
	{

		if (std::string(arguments[i]) == "-i" && commandLineArguments.inputFile == "")
		{
			if (i + 1 < argumentsAmount)
			{
				commandLineArguments.inputFile = arguments[++i];
			}
			else
			{
				isCorrect = false;
				showHelp();
				return;
			}
		}
		else if (std::string(arguments[i]) == "-o" && commandLineArguments.outputFile == "")
		{
			if (i + 1 < argumentsAmount)
			{
				commandLineArguments.outputFile = arguments[++i];
			}
			else
			{
				isCorrect = false;
				showHelp();
				return;
			}
		}
		else if (std::string(arguments[i]) == "-w" && commandLineArguments.extinctionFactor == -1)
		{
			if (i + 1 < argumentsAmount)
			{
				if (isFloatingNumber(arguments[i + 1]) && atof(arguments[1 + i]) >= 0 && atof(arguments[1 + i]) <= 1)
				{
					commandLineArguments.extinctionFactor = atof(arguments[++i]);
					if (commandLineArguments.multiplicationFactor != -1 && commandLineArguments.multiplicationFactor <= commandLineArguments.extinctionFactor)
					{
						isCorrect = false;
						showHelp();
						return;
					}
				}
				else
				{
					isCorrect = false;
					showHelp();
					return;
				}
			}
			else
			{
				isCorrect = false;
				showHelp();
				return;
			}
		}
		else if (std::string(arguments[i]) == "-r" && commandLineArguments.multiplicationFactor == -1)
		{
			if (i + 1 < argumentsAmount)
			{
				if (isFloatingNumber(arguments[i + 1]) && ( atof(arguments[1 + i]) >= 0 && atof(arguments[1 + i]) <= 1))
				{
					commandLineArguments.multiplicationFactor = atof(arguments[++i]);
					if (commandLineArguments.extinctionFactor != -1 && commandLineArguments.multiplicationFactor <= commandLineArguments.extinctionFactor)
					{
						isCorrect = false;
						showHelp();
						return;
					}
				}
				else
				{
					isCorrect = false;
					showHelp();
					return;
				}

			}
			else
			{
				isCorrect = false;
				showHelp();
				return;
			}
		}
		else if (std::string(arguments[i]) == "-p" && commandLineArguments.generationsNumber == -1)
		{
			if (i + 1 < argumentsAmount)
			{
				if (!isNumber(arguments[i + 1]))
				{
					isCorrect = false;
					showHelp();
					return;
				}
				commandLineArguments.generationsNumber = atoi(arguments[++i]);
			}
			else
			{
				isCorrect = false;
				showHelp();
				return;
			}
		}
		else if (std::string(arguments[i]) == "-k" && commandLineArguments.crossingPairsAmount == -1)
		{
			if (i + 1 < argumentsAmount)
			{
				if (!isNumber(arguments[i + 1]))
				{
					isCorrect = false;
					showHelp();
					return;
				}
				commandLineArguments.crossingPairsAmount = atoi(arguments[++i]);
			}
			else
			{
				isCorrect = false;
				showHelp();
				return;
			}
		}
		else
		{
			isCorrect = false;
			showHelp();
		}
	}
}

/**
shows help
*/
void ArgumentParser::showHelp()
{
	std::cerr << " Something went wrong, we'll try to -help you : ) " << std::endl;
	std::cerr << "Every option should have just one argument." << std::endl;
	std::cerr << "You have to give all options: " << std::endl;
	std::cerr << "-k amount of crossing pairs, should be a number" << std::endl;
	std::cerr << "-r multiplication factor, should be a number between 0 and 1, greater than -w" << std::endl;
	std::cerr << "-w exctinction factor should be a number between 0 and 1, smaller than -r" << std::endl;
	std::cerr << "-i input file" << std::endl;
	std::cerr << "-o output file" << std::endl;
	std::cerr << "-p number of generations, should be a number" << std::endl;
	
}

/**
@param argumentsAmount liczba argumentow uruchomieniowych podanych przez uzytkownika
@param arguments[] argumenty uruchomieniowe podane przez uzytkownika
wywoluje funkcje parseArguments w celu zparsowania argumentow
*/
ArgumentParser::ArgumentParser(int argumentsAmount, char* arguments[])
{
	parseArguments(argumentsAmount, arguments);
}
/**
@return commandLineArguments
*/
CommandLineArguments ArgumentParser::getCommandLineArguments()
{
	return commandLineArguments;
}
/**
wypisuje wszystkie pola commandLineArguments na ekran
*/
void ArgumentParser::showArguments()
{
		std::cout << commandLineArguments.inputFile << std::endl;
		std::cout << commandLineArguments.outputFile << std::endl;
		std::cout << commandLineArguments.extinctionFactor << std::endl;
		std::cout << commandLineArguments.multiplicationFactor << std::endl;
		std::cout << commandLineArguments.generationsNumber << std::endl;
		std::cout << commandLineArguments.crossingPairsAmount << std::endl;
}
/**
@returns isCorrect
*/
bool ArgumentParser::getIsCorrect()
{
	return isCorrect;
}