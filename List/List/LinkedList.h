#pragma once
#include "Cell.h"
#include "Iterator.h"
#include <iostream>

class LinkedList
{
public:
	LinkedList();
	LinkedList(const LinkedList& list);

	void assign(const LinkedList& list);
	~LinkedList();

	int size() const { return m_size; }
	bool empty() const { return m_size == 0; }
	void clear();
	bool find(double value, Iterator& findIterator);
	bool equal(const LinkedList& list) const;
	void add(double value);
	void add(const LinkedList& list);
	void insert(const Iterator& insertPosition, double value);
	void insert(const Iterator& insertPosition, const LinkedList &list);
	void erase(const Iterator& erasePosition);
	void remove(const Iterator& firstPosition, const Iterator& lastPosition = Iterator(nullptr));
	Iterator first() const { return Iterator(m_firstCellPtr); }
	Iterator last () const { return Iterator(m_lastCellPtr); }

	void read(std::istream& inStream);
	void write(std::ostream& outStream);

private:
	int m_size;
	Cell *m_firstCellPtr, *m_lastCellPtr;
};