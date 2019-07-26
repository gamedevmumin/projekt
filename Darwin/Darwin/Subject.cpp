#include "Subject.h"


/**
@param _chromosome lista intow reprezentujaca chromosom osobnika \n
przypisuje _chromosome do pola chromosome
*/
Subject::Subject(const List<unsigned int>& _chromosome)
{
	chromosome = _chromosome;
}

/**
@param firstChromosomePart lista intow reprezentujaca pierwsza czesc chromosomu osobnika \n
@param secondChromosomePart lista intow reprezentujaca druga czesc chromosomu osobnika \n
tworzy osobnika, ktorego pole chromosome to polaczone listy firstChromosomePart i secondChromosomePart
*/
Subject::Subject(List<unsigned int>& firstChromosomePart, List<unsigned int>& secondChromosomePart)
{
	ListIterator<unsigned int> it(firstChromosomePart);
	for ( unsigned int i = 0; i < firstChromosomePart.getSize(); i++)
	{ 
		chromosome.addAtEnd(it.getCurrent()->value);
		++it;
	}
	ListIterator<unsigned int> it2(secondChromosomePart);
	for (unsigned int i = 0; i < secondChromosomePart.getSize(); i++)
	{
		chromosome.addAtEnd(it2.getCurrent()->value);
		++it2;
	}
}
/**
@return chromosome
*/
List<unsigned int> Subject::getChromosome()
{
	return chromosome;
}
/**
sumuje wszystkie elementy listy chromosome
@return suma wszystkich elementow listy reprezentujacej chromosom (pole chromosome)
*/
int Subject::getSumOfChromosomeNumbers()
{
	ListIterator<unsigned int> it(chromosome);
	int sum = 0;
	for (unsigned int i = 0; i < chromosome.getSize(); i++)
	{
		
		sum += it.getCurrent()->value;
		++it;
	}
	return sum;
}
/**
dzieli liste chromosome w losowym miejscu, tworzac w ten sposob dwie nowe listy
@return para list unsigned int, reprezentujaca dwie czesci chromosomu
*/
std::pair<List<unsigned int>, List<unsigned int>> Subject::split()
{
	ListIterator<unsigned int> it(chromosome);
	List<unsigned int> firstPart, secondPart;
	if (chromosome.getSize()==2)
	{				
		firstPart.addAtEnd(it.getCurrent()->value);
		++it;
		secondPart.addAtEnd(it.getCurrent()->value);
		std::pair<List<unsigned int>, List<unsigned int>> parts(firstPart, secondPart);
		return parts;
	}
	else if (chromosome.getSize() == 1)
	{
		firstPart.addAtEnd(it.getCurrent()->value);
		std::pair<List<unsigned int>, List<unsigned int>> parts(firstPart, secondPart);
		return parts;
	}
	std::default_random_engine silnik;
	std::uniform_int_distribution<unsigned int> zakres(1, chromosome.getSize() - 2);
	silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
	int randomNumber = zakres(silnik);
	for (unsigned int i = 0; i < chromosome.getSize(); i++)
	{		
		if (i < randomNumber) firstPart.addAtEnd(it.getCurrent()->value);
		else secondPart.addAtEnd(it.getCurrent()->value);
		++it;
	}

	std::pair<List<unsigned int>, List<unsigned int>> parts(firstPart, secondPart);
	return parts;
}
/**
@param strongestSum najwieksza suma elementow chromosomu w calej populacji
oblicza przystosowania osobnika dzielac sume elementow jego chromosomu przez strongestSum
@return przystosowanie osobnika
*/
double Subject::getAdaptation(int strongestSum)
{
	f = (double)getSumOfChromosomeNumbers() / (double)strongestSum;
	return f;
}
