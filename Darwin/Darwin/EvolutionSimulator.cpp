#include "EvolutionSimulator.h"

/**
@param _argParser wskaznik na ArgumentParser, w ktorym przechowywane sa parametry uruchomieniowe programu
*/
EvolutionSimulator::EvolutionSimulator(ArgumentParser*& _argParser)
{
	argParser = _argParser;
	strongestSubjectChromosomeSum = 0;
}
/**
@param lista osobnikow, ktore maja zostac dodane do listy subjects\n
dodaje osobniki z podanej w parametrze listy do listy subjects
*/
void EvolutionSimulator::addSubjectsToPopulation(List<Subject>& _subjects)
{
	ListIterator<Subject> it(_subjects);
	for(unsigned int i = 0; i<_subjects.getSize(); i++)
	{ 
		subjects.addAtEnd(it.getCurrent()->value);
		++it;
	}
}

/**
Krzyzuje losowo wybrane pary osobnikow  poprzez polaczenie poczatkowej czesci chromosomu jednego z koncowa czescia drugiego osobnika (ilosc par zalezna od parametru -k podanego przez uzytkownika).\n
@return lista osobnikow powstalych po skrzyzowaniu sie wybranych osobnikow z populacji
*/
List<Subject> EvolutionSimulator::getChildren()
{
	List<Subject> newSubjects;
	if (subjects.getSize() <= 1) return newSubjects;
	std::default_random_engine silnik;
	int tmp = 0;
	if (subjects.getSize() != 0) tmp = 1;
	std::uniform_int_distribution<unsigned int> zakres(0, subjects.getSize()-tmp);
	silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
	int firstSubjectNumber, secondSubjectNumber;
	ListIterator<Subject> it(subjects);
	List<unsigned int> firstChromosomePart;
	List<unsigned int> secondChromosomePart;
	for (int i = 0; i < argParser->getCommandLineArguments().crossingPairsAmount; i++)
	{
		firstSubjectNumber = zakres(silnik);
		do
		{
			secondSubjectNumber = zakres(silnik);
		} while (secondSubjectNumber == firstSubjectNumber);

		if (firstSubjectNumber > secondSubjectNumber)
		{
			int tmp2 = firstSubjectNumber;
			firstSubjectNumber = secondSubjectNumber;
			secondSubjectNumber = tmp2;

		}
		for (unsigned int j = 0; j < subjects.getSize(); j++)
		{
			if (j == firstSubjectNumber)
			{
				firstChromosomePart = it.getCurrent()->value.split().first;
			}
			if (j == secondSubjectNumber)
			{
				secondChromosomePart = it.getCurrent()->value.split().second;
				break;
			}
			++it;
		}
		it.reset();
		Subject newSubject(firstChromosomePart, secondChromosomePart);
		newSubjects.addAtBeginning(newSubject);
	}
	return newSubjects;
}
/**
Wczytuje wszystkie osobniki z pliku podanego przez uzytkownika przy uruchamianiu programu po parametrze -i i zapisuje je do listy subjects.
@return true, jesli wczytanie sie powiodlo, false jestli plik nie istnieje lub w pliku sa nieprawidlowe dane
*/
bool EvolutionSimulator::loadSubjects()
{
	std::string fileName = argParser->getCommandLineArguments().inputFile;
	std::ifstream inputFile(fileName);
	if (!inputFile)
	{
		std::cout << "File " << fileName << " does not exist" << std::endl;
		return false;
	}
	
	std::string line;
	while (std::getline(inputFile, line))
	{		
		std::stringstream ss;
		ss << line;
		List<unsigned int> chromosome;
		while (ss)
		{
			unsigned int x;
			std::string s;
			ss >> s;
			if (!ss) break;
			if (!isNumber(s))
			{
				std::cout << "Data is not correct" << std::endl;
				return false;
			}
			x = stoi(s);
			
			
			chromosome.addAtEnd(x);
		}
		Subject subject(chromosome);
		subjects.addAtEnd(subject);
	}	
	inputFile.close();
	return true;
}
/**
Zapisuje wszystkie osobniki do pliku podanego przez uzytkownika przy uruchamianiu programu po parametrze -o.
@return true, jesli zapisanie sie powiodlo, false jesli plik nie istnieje 
*/
bool EvolutionSimulator::saveSubjectsToFile()
{
	std::string fileName = argParser->getCommandLineArguments().outputFile;
	std::ofstream outputFile(fileName);
	if (!outputFile)
	{
		std::cout << "File " << fileName << " does not exist" << std::endl;
		return false;
	}
	ListIterator<Subject> it(subjects);
	for (unsigned int i = 0; i < subjects.getSize(); i++)
	{
		List<unsigned int> chromosome = it.getCurrent()->value.getChromosome();
		ListIterator<unsigned int> it2(chromosome);
		for (unsigned int i = 0; i < chromosome.getSize(); i++)
		{
			outputFile << it2.getCurrent()->value << " ";
			++it2;
		}
		outputFile << std::endl;
		++it;
	}
	outputFile.close();
	return true;
}
/**
@param _subjects lista osobnikow, ktorych przystosowanie chcemy przetestowac. \n
Oblicza przystosowanie osobnikow z podanej listy i w zaleznosci od niego usuwa, klonuje lub nic nie robi z danym osobnikiem.  
*/
void EvolutionSimulator::checkSubjectsAdaptation(List<Subject>& _subjects)
{
	ListIterator<Subject> it(_subjects);	
	Element<Subject>* pTmp = nullptr;
	unsigned int size = _subjects.getSize();
	for (unsigned int i = 0; i < size; i++)
	{
		if (it.getCurrent())
		{
			Subject currentSubject(it.getCurrent()->value.getChromosome());
			int chromosomeSum = currentSubject.getSumOfChromosomeNumbers();
			if (strongestSubjectChromosomeSum < chromosomeSum)
			{
				strongestSubjectChromosomeSum = chromosomeSum;
			}
			
			if (currentSubject.getAdaptation(strongestSubjectChromosomeSum) < argParser->getCommandLineArguments().extinctionFactor)
			{
				pTmp = it.getCurrent()->pNext;
				_subjects.deleteElement(it.getCurrent());
				it.reset(pTmp);

			}
			else if (currentSubject.getAdaptation(strongestSubjectChromosomeSum) >= argParser->getCommandLineArguments().multiplicationFactor)
			{
				++it;
				_subjects.addAtEnd(currentSubject);
			}
			else
			{
				++it;
			}
		}
	}

}
/**
Glowna funkcja symulujaca ewolucje. Wczytuje osobniki z pliku. Po czym, w pêtli, krzyzuje osobniki, testuje ich przystosowanie i dodaje je do populacji. Petla wykonuje sie tyle razy, ile wynosi parametr -p podany przez uzytkowika.  
*/
void EvolutionSimulator::simulateEvolution()
{
	if (!loadSubjects())
	{
		return;
	}
	for (int i = 0; i < argParser->getCommandLineArguments().generationsNumber; i++)
	{
		children = getChildren();
		checkSubjectsAdaptation(children);
		addSubjectsToPopulation(children);		
	}	
	saveSubjectsToFile();
}