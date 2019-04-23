#include <iostream>

#include "Book.h"

Book::Book(void) { };

Book::Book(const std::string& title, const std::string& author) : m_title(title), m_author(author){ }

void Book::borrowBook(Customer* customer)
{
	if (m_customer == nullptr)
	{
		m_customer = customer;
	}
}

void Book::returnBook(void)
{
	m_customer = nullptr;
}

void Book::reserveBook(Customer* customer)
{
	m_reservationList.push_back(customer);
}

void Book::unreserveBook(Customer* customer)
{
	m_reservationList.remove(customer);
}

auto operator<<(std::ostream& outStream, const Book& book)->std::ostream&
{
	outStream << "Title: \"" << book.title() << "\" by " << book.author() << std::endl;
	outStream << "   Status: " << (book.m_customer != nullptr ? "Borrowed by " : "Available") << (book.m_customer != nullptr ? book.m_customer->name() : "");
	return outStream;
}

void Book::write(std::ofstream& outStream) const
{
	outStream << m_title << std::endl;
	outStream << m_author << std::endl;
}

void Book::read(std::ifstream& inStream) 
{
	std::getline(inStream, m_title);
	std::getline(inStream, m_author);
}