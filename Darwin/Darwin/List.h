#pragma once


template <class Type>
struct Element
{
	Type value;
	Element * pNext;
	Element * pPrev;
};

template <class Type>
class List 
{
private:
	Element<Type>* pHead;
	Element<Type>* pTail;
	unsigned int size;
public:
	/**
	sets size to 0, pHead and pTail to nullptr 
	*/
	List<Type>() { 
	size = 0; 
	pHead = nullptr;
	pTail = nullptr;
	}
	List<Type>(const List<Type>& other);

	/**
	deletes list iteratively
	*/
	~List<Type>() {
		deleteIteratively();
	}
	Element<Type>* head();
	Element<Type>* tail();
	void addAtBeginning(Type value);
	void addAtEnd(Type value);
	void deleteElement(Element<Type>* pElement);
	void writeIteratively();
	void writeFromTheEndIteratively();
	void deleteIteratively();
	unsigned int const getSize();
	List<Type>& operator=(const List<Type>& other);
};

template <class Type>
List<Type>::List(const List<Type>& other)
{
	pHead = nullptr;
	pTail = nullptr;
	size = 0;
	Element<Type>* otherHead = other.pHead;
	while (otherHead)
	{
		addAtEnd(otherHead->value);
		otherHead = otherHead->pNext;
	}
}

/**
@return pHead
*/
template <class Type>
Element<Type>* List<Type>::head()
{
	return pHead;
}
/**
@return pTail
*/
template <class Type>
Element<Type>* List<Type>::tail()
{
	return pTail;
}
/**
@param value wartosc, ktora ma zostac dodana do listy\n
dodaje element na poczatek listy
*/
template <class Type>
void List<Type>::addAtBeginning(Type value)
{
	if (not pHead)
	{
		pHead = new Element<Type>{ value, nullptr, nullptr };
		pTail = pHead;
	}
	else
	{
		Element<Type>* pPrevHead = pHead;
		pHead = new Element<Type>{ value, pHead, nullptr };
		pPrevHead->pPrev = pHead;
	}
	size++;
}
/**
@param value wartosc, ktora ma zostac dodana do listy\n
dodaje element na koniec listy
*/
template<class Type>
void List<Type>::addAtEnd(Type value)
{
	if (not pHead)
	{
		pHead = new Element<Type>{ value, nullptr };
		pTail = pHead;
	}
	else
	{
		Element<Type>* pPrevTail = pTail;
		pTail = new Element<Type>{ value, nullptr, pPrevTail };
		pPrevTail->pNext = pTail;
	}
	size++;
}
/**
@param pElement wskaznik na element, ktory ma zostac usuniety z listy\n
usuwa podany element z listy
*/
template<class Type>
void List<Type>::deleteElement(Element<Type>* pElement)
{
	if (pElement == pHead && pElement == pTail)
	{
		delete pHead;
		pHead = nullptr;
		pTail = nullptr;
	}
	else if (pElement == pHead)
	{
		Element<Type>* pNewHead = nullptr;
		pNewHead = pHead->pNext;
		delete pHead;
		pHead = pNewHead;
		pHead->pPrev = nullptr;
	}
	else if(pElement == pTail)
	{
		
		Element<Type>* pNewTail = pTail->pPrev;
		delete pTail;
		pTail = pNewTail;
		pTail->pNext = nullptr;
	}
	else
	{
		pElement->pPrev->pNext = pElement->pNext;
		pElement->pNext->pPrev = pElement->pPrev;
		delete pElement;
	}
	size--;
	
}
/**
wypisuje liste od poczatku iteracyjnie
*/
template <class Type>
void List<Type>::writeIteratively()
{
	Element<Type>* pTmp = pHead;

	while (pTmp)
	{
		pTmp = pTmp->pNext;
	}
}
/**
wypisuje liste od konca iteracyjnie
*/
template <class Type>
void List<Type>::writeFromTheEndIteratively()
{
	Element<Type>* pTmp = pTail;

	while (pTmp)
	{
		pTmp = pTmp->pPrev;
	}
}
/**
usuwa liste iteracyjnie
*/
template<class Type>
void List<Type>::deleteIteratively()
{
	while (pHead)
	{
		Element<Type>* pNext = pHead->pNext;
		delete pHead;
		pHead = pNext;
		size--;
	}
}
/**
@return size
*/
template<class Type>
unsigned int const List<Type>::getSize()
{
	return size;
}
/**
przeciazony operator przypisania, usuwa liste, po czym  dodaje do niej elementy z listy podanej jako prawy argument
*/
template<class Type>
List<Type>& List<Type>::operator=(const List<Type>& other)
{
	deleteIteratively();
	Element<Type>* otherHead = other.pHead;
	while (otherHead)
	{
		addAtEnd(otherHead->value);
		otherHead = otherHead->pNext;
	}
	return *this;
}