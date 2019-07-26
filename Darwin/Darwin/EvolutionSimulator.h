#pragma once

#include "List.h"
#include "ArgumentParser.h"
#include "UsefulFunctions.h"
#include "Subject.h"
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>

class EvolutionSimulator
{
private:
	ArgumentParser* argParser;
	List<Subject> subjects;
	List<Subject> children;
	int strongestSubjectChromosomeSum;
public:
	EvolutionSimulator(ArgumentParser*& _argParser);
	void checkSubjectsAdaptation(List<Subject>& _subjects);
	List<Subject> getChildren();
	void addSubjectsToPopulation(List<Subject>& _subjects);
	bool loadSubjects();
	bool saveSubjectsToFile();
	void simulateEvolution();
};
