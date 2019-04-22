#include <iostream>

#include "Book.h"
#include "Library.h"

int Book::ID_MAX = 0;

Book::Book(void) { };

Book::Book(const std::string& title, const std::string& author) : m_title(title), m_author(author), m_bookID(++ID_MAX) { }

void Book::borrowBook(int customerID)
{
	if (!m_isBorrowed)
	{
		m_isBorrowed = true;
		m_customerId = customerID;
	}
}

void Book::returnBook(void)
{
	m_isBorrowed = false;
}

void Book::reserveBook(int customerID)
{
	m_reservationList.push_back(customerID);
}

void Book::unreserveBook(int customerID)
{
	m_reservationList.remove(customerID);
}

auto operator<<(std::ostream& outStream, const Book& book)->std::ostream&
{
	outStream << "Title: \"" << book.title() << "\" by " << book.author() << std::endl;
	outStream << "   Status: " << (book.borrowed() ? "Borrowed by " : "Available") << (book.borrowed() ? Library::s_customerMap[book.m_customerId].name() : "");
	return outStream;
}

void Book::write(std::ofstream& outStream) const
{
	outStream.write((char*)& m_bookID, sizeof m_bookID);
	outStream << m_title << std::endl;
	outStream << m_author << std::endl;

	outStream.write((char*)& m_isBorrowed, sizeof m_isBorrowed);
	if (m_isBorrowed)
	{
		outStream.write((char*)&m_customerId, sizeof m_customerId);
	}
	auto reserveSize = m_reservationList.size();
	outStream.write((char*)& reserveSize, sizeof reserveSize);
	for (int res : m_reservationList)
	{
		outStream.write((char*)& res, sizeof res);
	}
}

void Book::read(std::ifstream& inStream) 
{
	inStream.read((char*)& m_bookID, sizeof m_bookID);
	std::getline(inStream, m_title);
	std::getline(inStream, m_author);

	inStream.read((char*)& m_isBorrowed, sizeof m_isBorrowed); 
	if (m_isBorrowed)
	{
		inStream.read((char*)&m_customerId, sizeof m_customerId);
	}
	size_t reserveSize;
	inStream.read((char*)& reserveSize, sizeof reserveSize);
	for (int i = 0; i < reserveSize; ++i)
	{
		int customerId; 
		inStream.read((char*)& customerId, sizeof customerId);
		m_reservationList.push_back(customerId);
	}
	if (m_bookID >= Book::ID_MAX)
	{
		Book::ID_MAX = m_bookID + 1;
	}
}