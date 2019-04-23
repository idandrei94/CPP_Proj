#pragma once
#include <fstream>
#include <string>
#include <list>

#include "Book.h"

class Book;

class Customer
{
public:
	Customer(void);
	Customer(const std::string& name, const std::string& address);

	auto name() const -> const std::string& { return m_name; }
	auto address() const -> const std::string& { return m_address; }

	auto loans() const -> const std::list<Book*> { return m_loanList; }
	auto loans() ->  std::list<Book*>& { return m_loanList; }

	auto reservations() const -> const std::list<Book*> { return m_reservationList; }
	auto reservations() ->  std::list<Book*>& { return m_reservationList; }

	void read(std::ifstream& inStream);
	void write(std::ofstream& outStream) const;

	void borrowBook(Book *book);
	void returnBook(Book *book);
	void reserveBook(Book *book);
	void unreserveBook(Book *book);

	auto hasBorrowed(void) const -> bool { return !m_loanList.empty(); }

	friend auto operator<<(std::ostream& outStream, const Customer& customer) -> std::ostream&;

private:
	std::string m_name, m_address;
	std::list<Book*> m_loanList, m_reservationList;
};