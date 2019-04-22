#pragma once

#include <string>
#include <list>
#include <fstream>

#include "Customer.h"

class Book
{
public:
	Book(void);
	Book(const std::string& title, const std::string& author);

	auto title() const -> const std::string& { return m_title; }
	auto author() const -> const std::string& { return m_author; }
	auto bookID() const -> int { return m_bookID; }
	auto borrowed() const -> const bool { return m_isBorrowed; }
	auto customerID() const -> int { return m_customerId; }

	auto reservationList(void)->std::list<int>& { return m_reservationList; }

	void read(std::ifstream& inStream);
	void write(std::ofstream& outStream) const;

	void borrowBook(int customerId);
	void returnBook(void);

	void reserveBook(int customerId);
	void unreserveBook(int customerId);

	friend auto operator<<(std::ostream& outStream, const Book& book)->std::ostream&;
private:
	int m_bookID, m_customerId;
	std::string m_title, m_author;
	bool m_isBorrowed;
	std::list<int> m_reservationList;

	static int ID_MAX;
};