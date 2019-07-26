#pragma once
#include <iostream>

struct CommandLineArguments;

struct CommandLineArguments
{
	std::string inputFile="";
	std::string outputFile="";
	double extinctionFactor=-1;
	double multiplicationFactor=-1;
	int generationsNumber=-1;
	int crossingPairsAmount=-1;
};