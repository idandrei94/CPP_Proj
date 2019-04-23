#pragma once

#include <string>
#include <fstream>

#include "Customer.h"

class Customer;

class Book
{
public:
	Book(void);
	Book(const std::string& title, const std::string& author);

	auto title() const -> const std::string& { return m_title; }
	auto author() const -> const std::string& { return m_author; }

	auto borrower() const -> const Customer* { return m_customer; }
	auto borrower() -> Customer*& { return m_customer; }

	auto reservationList() -> std::list<Customer*>& { return m_reservationList; }
	auto reservationList() const -> const std::list<Customer*> { return m_reservationList; }

	void read(std::ifstream& inStream);
	void write(std::ofstream& outStream) const;

	void borrowBook(Customer* customer);
	void returnBook(void);

	void reserveBook(Customer* customer);
	void unreserveBook(Customer* customer);

	friend auto operator<<(std::ostream& outStream, const Book& book) -> std::ostream&;

private:
	std::string m_title, m_author;
	Customer *m_customer = nullptr;
	std::list<Customer*> m_reservationList;
};