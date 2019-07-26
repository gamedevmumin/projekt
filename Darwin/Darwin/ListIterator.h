#pragma once

#include "List.h"


template<class Type>
class ListIterator
{

private:
	List<Type>* list;
	Element<Type>* pHead;
	Element<Type>* current;
	Element<Type>* pTail;
public:
	ListIterator(List<Type>& _list);
	void reset();
	void reset(Element<Type>*& _current);
	Element<Type>* begin();
	Element<Type>* getCurrent();
	Element<Type>* end();
	ListIterator<Type>& operator++();
	ListIterator<Type>& operator--();

};
/**
@param _list lista, ktorej obiekt bedzie iteratorem.\n
przypisuje podana liste do pola list, glowe listy do pola pHead, ogon listy do pola pTail i ustawia pole current na pHead.
*/
template<class Type> ListIterator<Type>::ListIterator(List<Type>& _list)
{
	list = &_list;
	pHead = list->head();
	pTail = list->tail();
	current = pHead;
}

/**
resetuje iterator, poprzez ponowne ustawienie pHead i pTail na, kolejno, glowe i ogon listy, oraz pola current na pHead.
*/
template<class Type> void ListIterator<Type>::reset()
{
	pHead = list->head();
	pTail = list->tail();
	current = pHead;
}
/**
@param _current wskaznik na pozadany element, na ktory ma wskazywac iterator
resetuje iterator, poprzez ponowne ustawienie pHead i pTail na, kolejno, glowe i ogon listy, ale ustawia pole current na podane przez uzytkownika w parametrze.
*/
template<class Type> void ListIterator<Type>::reset(Element<Type>*& _current)
{
	pHead = list->head();
	pTail = list->tail();
	current = _current;
}

/**
@return pHead
*/
template<class Type> Element<Type>* ListIterator<Type>::begin()
{
	return pHead;
}
/**
@return current
*/
template<class Type> Element<Type>* ListIterator<Type>::getCurrent()
{
	return current;
}
/**
@return pTail
*/
template<class Type> Element<Type>* ListIterator<Type>::end()
{
	return pTail;
}
/**
przeciazenie operatora inkrementacji, ustawia current na current->pNext
*/
template<class Type>
ListIterator<Type>& ListIterator<Type>::operator++()
{
	current = current->pNext;
	return *this;
}

/**
przeciazenie operatora dekrementacji, ustawia current na current->pPrev
*/
template<class Type>
ListIterator<Type>& ListIterator<Type>::operator--()
{
	current = current->pPrev;
	return *this;
}


