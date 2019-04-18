#pragma once
#include <iostream>


template <class T>
class LinkedList {
private:
	class Cell {
	private:
		Cell(const T& value, Cell *previous, Cell *next) : m_value(value), m_previous(previous), m_next(next) { }

	public:
		auto value() const -> const T { return m_value; }
		auto value() -> T& { return m_value; }

		auto next() const -> const  Cell*& { return m_next; }
		auto next() -> Cell*& { return m_next; }

		auto previous() const -> const Cell*& { return m_previous; }
		auto previous() -> Cell*& { return m_previous; }

		friend class LinkedList;

	private:
		T m_value;
		Cell *m_previous, *m_next;
	};

public:
	class Iterator {
	public:
		Iterator() : m_cellPtr(nullptr) { }

	private:
		Iterator(Cell *cellPtr) : m_cellPtr(cellPtr) { }

	public:
		Iterator(const Iterator& iterator) : m_cellPtr(iterator.m_cellPtr) { }

		auto operator=(const Iterator& iterator) -> Iterator&;
		auto operator==(const Iterator& iterator) -> bool { return m_cellPtr == iterator.m_cellPtr; }
		auto operator!=(const Iterator& iterator) -> bool { return m_cellPtr != iterator.m_cellPtr; }
		
		auto operator++() -> bool;                               // prefix: ++i
		auto operator++(int) -> bool;                            // postfix: i++
		auto operator--() -> bool;                               // prefix: --i
		auto operator--(int) -> bool;                            // postfix: i--

		auto operator*() const -> T { return m_cellPtr->value(); }
		auto operator*() -> T& { return m_cellPtr->value(); }

		friend class LinkedList<T>;

	private:
		Cell *m_cellPtr;
	};

	class ReverseIterator {
	public:
		ReverseIterator() : m_cellPtr(nullptr) { }

	private:
		ReverseIterator(Cell *cellPtr) : m_cellPtr(cellPtr) { }

	public:
		ReverseIterator(const ReverseIterator& iterator) : m_cellPtr(iterator.m_cellPtr) { }

		auto operator=(const ReverseIterator& iterator) -> const ReverseIterator&;
		auto operator==(const ReverseIterator& iterator) -> bool { return m_cellPtr == iterator.m_cellPtr; }
		auto operator!=(const ReverseIterator& iterator) -> bool { return m_cellPtr != iterator.m_cellPtr; }
		auto operator++() -> bool;                               // prefix: ++i
		auto operator++(int) -> bool;                            // postfix: i++
		auto operator--() -> bool;                               // prefix: --i
		auto operator--(int) -> bool;                            // postfix: i--

		auto operator*() const -> T { return m_cellPtr->value(); }
		auto operator*() -> T& { return m_cellPtr->value(); }

		friend class LinkedList<T>;

	private:
		Cell *m_cellPtr;
	};

public:
	LinkedList() : m_firstCellPtr(nullptr), m_lastCellPtr(nullptr), m_size(0) { }
	LinkedList(const LinkedList& list) { clear(); add(list); }
	auto operator=(const LinkedList& list) -> LinkedList<T>&;
	~LinkedList() { clear(); }
	void clear();

	auto size() const -> int { return m_size; }
	auto empty() const -> bool { return m_size == 0; }

	auto operator==(const LinkedList& list) const -> bool;
	auto operator!=(const LinkedList& list) const -> bool { return *this == list; }

	void add(const T& value);
	void add(const LinkedList& list);

	void insert(const Iterator& insertPosition, const T& value);
	void insert(const Iterator& insertPosition, const LinkedList<T>& list);

	void erase(const Iterator& erasePosition) { remove(erasePosition, erasePosition); }
	void remove(const Iterator& firstPosition, const Iterator& lastPosition = Iterator(nullptr));

	auto begin() const -> Iterator { return Iterator(m_firstCellPtr); }
	auto end() const -> Iterator { return Iterator(nullptr); }
	auto rbegin() const -> ReverseIterator { return ReverseIterator(m_lastCellPtr); }
	auto rend() const -> ReverseIterator { return ReverseIterator(nullptr); }

	template <class U>
	friend auto operator>>(std::istream& outStream, LinkedList<U>& list) -> std::istream&;

	template <class U>
	friend auto operator<<(std::ostream& outStream, LinkedList<U>& list) -> std::ostream&;

private:
	int m_size;
	Cell *m_firstCellPtr, *m_lastCellPtr;
};

template <class T>
auto LinkedList<T>::Iterator::operator=(const Iterator& iterator) -> typename LinkedList<T>::Iterator&
{
	this->m_cellPtr = iterator.m_cellPtr;
	return *this;
}

template <class T>
auto  LinkedList<T>::Iterator::operator++()-> bool
{
	if (m_cellPtr != nullptr)
	{
		m_cellPtr = m_cellPtr->next();
		return true;
	}
	return false;
}

template <class T>
auto  LinkedList<T>::Iterator::operator++(int)-> bool
{
	if (m_cellPtr != nullptr)
	{
		m_cellPtr = m_cellPtr->next();
		return true;
	}
	return false;
}

template <class T>
auto  LinkedList<T>::Iterator::operator--()-> bool
{
	if (m_cellPtr != nullptr)
	{
		m_cellPtr = m_cellPtr->previous();
		return true;
	}
	return false;
}

template <class T>
auto  LinkedList<T>::Iterator::operator--(int)-> bool
{
	if (m_cellPtr != nullptr)
	{
		m_cellPtr = m_cellPtr->previous();
		return true;
	}
	return false;
}

template <class T>
auto LinkedList<T>::ReverseIterator::operator=(const ReverseIterator& iterator) -> typename const LinkedList<T>::ReverseIterator&
{
	this->m_cellPtr = iterator.m_cellPtr;
	return *this;
}

template <class T>
auto  LinkedList<T>::ReverseIterator::operator++()-> bool
{
	if (m_cellPtr != nullptr)
	{
		m_cellPtr = m_cellPtr->previous();
		return true;
	}
	return false;
}
template <class T>
auto  LinkedList<T>::ReverseIterator::operator++(int x)-> bool
{
	if (m_cellPtr != nullptr)
	{
		m_cellPtr = m_cellPtr->previous();
		return true;
	}
	return false;
}

template <class T>
auto  LinkedList<T>::ReverseIterator::operator--()-> bool
{
	if (m_cellPtr != nullptr)
	{
		m_cellPtr = m_cellPtr->next();
		return true;
	}
	return false;
}

template <class T>
auto  LinkedList<T>::ReverseIterator::operator--(int x)-> bool
{
	if (m_cellPtr != nullptr)
	{
		m_cellPtr = m_cellPtr->next();
		return true;
	}
	return false;
}

template <class T>
void LinkedList<T>::clear()
{
	while (m_firstCellPtr != nullptr)
	{
		Cell *deleteCell = m_firstCellPtr;
		m_firstCellPtr = m_firstCellPtr->next();
		delete deleteCell;
	}
	m_lastCellPtr = nullptr;
	m_size = 0;
}

template <class T>
auto LinkedList<T>::operator=(const LinkedList& list) -> LinkedList<T>&
{
	clear();
	add(list);
	return *this;
}

template <class T>
auto LinkedList<T>::operator==(const LinkedList& list) const -> bool
{
	if (m_size != list.size())
	{
		return false;
	}
	for (Iterator myIterator = begin(), listIterator = list.begin(); myIterator != end(); ++myIterator, ++listIterator)
	{
		if (myIterator != listIterator)
		{
			return false;
		}
	}
	return true;
}

template <class T>
void LinkedList<T>::add(const T& value)
{
	Cell *cell = new Cell(value, nullptr, nullptr);
	if (m_firstCellPtr == nullptr) // empty list
	{
		m_firstCellPtr = m_lastCellPtr = cell;
	}
	else
	{
		if (m_lastCellPtr == nullptr)
		{
			m_lastCellPtr = cell;
			cell->previous() = m_firstCellPtr;
			m_firstCellPtr->next() = cell;
		}
		else
		{
			m_lastCellPtr->next() = cell;
			cell->previous() = m_lastCellPtr;
			m_lastCellPtr = cell;
		}
	}
	++m_size;
}


template <class T>
void LinkedList<T>::add(const LinkedList<T>& list)
{
	for (const T& val : list)
	{
		add(val);
	}
}

template <class T>
void LinkedList<T>::insert(const Iterator& insertPosition, const T& value)
{
	if (insertPosition.m_cellPointer == nullptr)
	{
		add(value);
	}
	else
	{
		Cell *insertCell = insertPosition.m_cellPointer;
		Cell *newCell = new Cell(value, insertCell, insertCell->next());
		if (insertCell->next() != nullptr)
		{
			insertCell->next()->previous() = insertCell;
		}
		++m_size;
	}
}

template <class T>
void LinkedList<T>::insert(const Iterator& insertPosition, const LinkedList<T>& list)
{
	if (insertPosition.m_cellPointer == nullptr)
	{
		add(list);
	}
	else
	{
		for (const T& value : list)
		{
			insert(insertPosition++, value);
		}
	}
}

template <class T>
void LinkedList<T>::remove(const Iterator& firstPosition, const Iterator& lastPosition)
{
	Cell *beginCell = firstPosition.m_cellPtr;
	Cell *endCell = lastPosition.m_cellPtr;
	Cell *firstCell = m_firstCellPtr;
	Cell *lastCell = m_lastCellPtr;

	endCell = endCell == nullptr ? lastCell : endCell;

	if (beginCell == nullptr)
	{
		return;
	}
	
	if (beginCell == firstCell) // remove from start
	{
		m_firstCellPtr = endCell->next();
	}
	else
	{
		beginCell->previous()->next() = endCell->next();
	}

	if (endCell->next() == nullptr)
	{
		m_lastCellPtr = beginCell->previous();
	}
	else
	{
		endCell->next()->previous() = beginCell->previous();
	}
	while (beginCell != endCell)
	{
		Cell *deleteCell = beginCell;
		beginCell = beginCell->next();
		delete deleteCell;
		--m_size;
	}
}

template <class T>
auto operator>>(std::istream& outStream, LinkedList<T>& list) -> std::istream&
{
	int size;
	outStream >> size;
	for (int i = 0; i < size; ++i)
	{
		T value;
		outStream >> value;
		list.add(value);
	}
	return outStream;
}

template <class T>
auto operator<<(std::ostream& outStream, LinkedList<T>& list) -> std::ostream&
{
	outStream << "[";
	bool first = true;
	for (const T& value : list)
	{
		outStream << (first ? "" : ",") << value;
		first = false;
	}
	outStream << "]";
	return outStream;
}