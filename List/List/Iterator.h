#pragma once
#include "Cell.h"
#include <cassert>

class Iterator {
private:
	Iterator(Cell* cellPtr);
	friend class LinkedList;
public:
	Iterator();
	Iterator(const Iterator& iterator);

	double getValue() const { return m_cellPtr->getValue(); }
	void setValue(double value) { m_cellPtr->setValue(value); }

	bool hasNext() const { return m_cellPtr != nullptr; }
	void next() { assert(hasNext()); m_cellPtr = m_cellPtr->getNext(); }

	bool hasPrevious() const { return m_cellPtr != nullptr; }
	void previous() { assert(hasPrevious()); m_cellPtr = m_cellPtr->getPrevious(); }

private:
	Cell* m_cellPtr;
};