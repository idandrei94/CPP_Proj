#include "LinkedList.h"
#include <cassert>

LinkedList::LinkedList()
	: m_size(0), m_firstCellPtr(nullptr), m_lastCellPtr(nullptr)
{
}

LinkedList::LinkedList(const LinkedList& list)
{
	assign(list);
}

void LinkedList::assign(const LinkedList& list)
{
	clear();
	add(list);
}

LinkedList::~LinkedList()
{
	clear();
}

void LinkedList::clear()
{
	while (m_firstCellPtr != nullptr)
	{
		Cell *deleteCellPtr = m_firstCellPtr;
		m_firstCellPtr = m_firstCellPtr->getNext();
		delete deleteCellPtr;
	}
	m_firstCellPtr = m_lastCellPtr = nullptr;
	m_size = 0;
}

bool LinkedList::find(double value, Iterator& findIterator)
{
	Iterator iterator = first();

	while (iterator.hasNext())
	{
		if (value == iterator.getValue())
		{
			findIterator = iterator;
			return true;
		}
		iterator.next();
	}
	return false;
}

bool LinkedList::equal(const LinkedList& list) const
{
	if (list.m_size != m_size)
	{
		return false;
	}
	Iterator myIterator = first(), otherIterator = list.first();
	while (myIterator.hasNext())
	{
		if (myIterator.getValue() != otherIterator.getValue())
		{
			return false;
		}
		myIterator.next();
		otherIterator.next();
	}
	return true;
}

void LinkedList::add(const LinkedList& list)
{
	Iterator iterator = list.first();
	while (iterator.hasNext())
	{
		add(iterator.getValue());
		iterator.next();
	}
}
void LinkedList::add(double value)
{
	Cell *newCell = new Cell(value, m_lastCellPtr, nullptr);
	if (m_firstCellPtr == nullptr)
	{
		m_firstCellPtr = newCell;
	}
	else
	{
		m_lastCellPtr->setNext(newCell);
	}
	m_lastCellPtr = newCell;
	++m_size;
}

void LinkedList::insert(const Iterator& insertPosition, double value)
{
	if (!insertPosition.hasNext())
	{
		add(value);
	}
	else
	{
		Cell *newCell = new Cell(value, insertPosition.m_cellPtr->getPrevious(), insertPosition.m_cellPtr);
		insertPosition.m_cellPtr->setPrevious(newCell);
		++m_size;
	}
}

void LinkedList::insert(const Iterator& insertPosition, const LinkedList& list)
{
	if (!insertPosition.hasNext())
	{
		add(list);
	}
	else
	{
		Iterator iterator = list.first();
		while (iterator.hasNext())
		{
			insert(insertPosition, iterator.getValue());
			iterator.next();
		}
	}
}

void LinkedList::erase(const Iterator& erasePosition)
{
	remove(erasePosition, erasePosition);
}

void LinkedList::remove(const Iterator& firstPosition, const Iterator& lastPosition)
{
	if (m_firstCellPtr == nullptr)
	{
		return;
	}
	Cell *startCellPtr = m_firstCellPtr;
	Cell *endCellPtr = m_lastCellPtr;
	Cell *firstCellPtr = firstPosition.m_cellPtr;
	Cell *lastCellPtr = lastPosition.m_cellPtr;
	lastCellPtr = (lastCellPtr == nullptr ? endCellPtr : lastCellPtr);

	Cell *prev = firstCellPtr->getPrevious();
	Cell *next = lastCellPtr->getNext();
	if (prev == nullptr)
	{
		m_firstCellPtr = next;
	}
	else
	{
		prev->setNext(next);
	}
	if (next == nullptr)
	{
		m_lastCellPtr = prev;
	}
	else
	{
		next->setPrevious(prev);
	}

	while (firstCellPtr != lastCellPtr && firstCellPtr != nullptr)
	{
		Cell *deleteCellPtr = firstCellPtr;
		firstCellPtr = firstCellPtr->getNext();
		delete deleteCellPtr;
		--m_size;
	}
}

void LinkedList::read(std::istream& inStream)
{
	int size;
	inStream >> size;
	int count = 0;
	for (count = 0; count < size; ++count)
	{
		double value;
		inStream >> value;
		add(value);
	}
}

void LinkedList::write(std::ostream& outStream)
{
	outStream << "[";
	bool firstVal = true;
	Iterator iterator = first();
	while (iterator.hasNext())
	{
		outStream << (firstVal ? "" : ", ") << iterator.getValue();
		firstVal = false;
		iterator.next();
	}
	outStream << "]";
}