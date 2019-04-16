#pragma once
class Cell {
private:
	friend class LinkedList;
	Cell(double value, Cell* previous, Cell* next);

public:
	auto value() -> double& { return m_value; }
	auto value() const -> const double& { return m_value; }

	double getValue() const { return m_value; }
	void setValue(double value) { m_value = value; }

	Cell* getPrevious() const { return m_previous; }
	void setPrevious(Cell* previous) { m_previous = previous; }

	Cell* getNext() const { return m_next; }
	void setNext(Cell* next) { m_next = next; }

private:
	double m_value;
	Cell* m_previous, *m_next;
};