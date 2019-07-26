#include <iostream>
#include <string>
#include "ArgumentParser.h"
#include "List.h"
#include "Subject.h"
#include "ListIterator.h"
#include <vld.h>
#include "EvolutionSimulator.h"



int main(int argc, char* argv[])
{
	ArgumentParser* argParser = new ArgumentParser(argc, argv);
	if (argParser->getIsCorrect())
	{
		EvolutionSimulator	evolutionSimulator(argParser);
		evolutionSimulator.simulateEvolution();
	}
	delete argParser;
	std::cin.ignore();
	return 0;
}