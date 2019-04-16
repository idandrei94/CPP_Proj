#pragma once
#include <iostream>
template <class T>
class LinkedList {
private:
	class Cell {
	private:
		Cell(const T& value, Cell *previous, Cell *next);

	public:
		auto value() const -> const T { return m_value; }
		auto value() -> T { return m_value; }

		auto next() const -> const  Cell*& { return m_next; }
		auto next() -> Cell*& { return m_next; }

		auto previous() const -> const Cell*& { return m_previous; }
		auto previous() -> Cell*& { return m_previous; }

		friend class LinkedList;

	private:
		T m_value;
		Cell *m_previous, m_next;
	};

public:
	class Iterator {
	public: 
		Iterator() : m_cellPtr(nullptr) { }

	private:
		Iterator(Cell *cellPtr) : m_cellPtr(cellptr) { }

	public:
		Iterator(const Iterator& iterator) : m_cellPtr(iterator.m_cellPtr) { }

		auto operator=(const Iterator& iterator) -> Iterator& {  return Iterator(iterator.m_cellPtr); }
		auto operator==(const Iterator& iterator) -> bool { return m_cellPtr == iterator.m_cellPtr; }
		auto operator==(const bool boolean) -> bool { return (m_cellPtr != nullptr) == boolean; }
		auto operator!=(const Iterator& iterator) -> bool { return m_cellPtr != iterator.m_cellPtr; }
		
		auto operator++() -> bool;                               // prefix: ++i
		auto operator++(int) -> bool;                            // postfix: i++
		auto operator--() -> bool;                               // prefix: --i
		auto operator--(int) -> bool;                            // postfix: i--

		auto operator*() const -> T { return m_cellPtr->value(); }
		auto operator*() -> T& { return m_cellPtr->value(); }

	private:
		Cell *m_cellPtr;
	};

	class ReverseIterator {
	public:
		ReverseIterator();

	private:
		ReverseIterator(Cell *cellPtr);

	public:
		ReverseIterator(const Iterator& Iterator);

		auto operator==(const ReverseIterator& iterator) -> Iterator&;
		auto operator==(const ReverseIterator& iterator) -> bool;
		auto operator!=(const ReverseIterator& iterator) -> bool;
		auto operator++() -> bool;                               // prefix: ++i
		auto operator++(int) -> bool;                            // postfix: i++
		auto operator--() -> bool;                               // prefix: --i
		auto operator--(int) -> bool;                            // postfix: i--

		auto operator*() const -> T;
		auto operator*() -> T&;

	private:
		Cell *m_cellPtr;
	};

public:
	LinkedList();
	LinkedList(const LinkedList& list);
	LinkedList& operator=(const LinkedList& list);
	~LinkedList();
	void clear();

	auto size() const -> int { return m_size; }
	auto empty() const -> bool { return m_size == 0; }

	auto operator==(const LinkedList& list) const -> bool;
	auto operator!=(const LinkedList& list) const -> bool;

	void add(const T& value);
	void add(const LinkedList& list);

	void insert(const Iterator& insertPosition, const T& value);
	void insert(const Iterator& insertPosition, const LinkedList& list);

	void erase(const Iterator& erasePosition);
	void remove(const Iterator& firstPosition, const Iterator& lastPosition = Iterator(nullptr));

	auto begin() const -> Iterator { return Iterator(m_firstCellPtr); }
	auto end() const -> Iterator { return Iterator(m_lastCellPtr); }
	auto rbegin() const -> ReverseIterator { return ReverseIterator(m_lastCellPtr); }
	auto rend() const -> ReverseIterator { return ReverseIterator(m_firstCellPtr); }

	template <class U>
	friend std::istream operator>>(std::istream& outStream, LinkedList<U>& list);

	template <class U>
	friend std::ostream operator<<(std::istream& outStream, LinkedList<U>& list);

private:
	int m_size;
	Cell *m_firstCellPtr, *m_lastCellPtr;
};

template <class T>
//typename LinkedList<T>
LinkedList<T>::Cell::Cell(const T& value, Cell *previous, Cell *next)
{
	m_value = value;
	m_previous = previous;
	m_next = next;
}