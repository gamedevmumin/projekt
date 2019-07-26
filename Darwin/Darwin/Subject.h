#pragma once

#include "List.h"
#include "ListIterator.h"
#include <iostream>
#include <utility>
#include <random>
#include <chrono>

class Subject
{
private:
	List<unsigned int> chromosome;
	double f;
public:
	Subject(const List<unsigned int>& _chromosome);
	Subject(List<unsigned int>& firstChromosomePart, List<unsigned int>& secondChromosomePart);
	List<unsigned int> getChromosome();
	int getSumOfChromosomeNumbers();
	std::pair<List<unsigned int>, List<unsigned int>> split();
	double getAdaptation(int strongestSum);
};
