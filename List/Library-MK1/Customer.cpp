#include "Customer.h"
#include "Library.h"

int Customer::MAX_ID = 0;

Customer::Customer(void) { }

Customer::Customer(const std::string& name, const std::string& address) : m_customerId(MAX_ID++), m_name(name), m_address(address) { }

void Customer::borrowBook(int bookId)
{
	m_loanSet.insert(bookId);
}

void Customer::returnBook(int bookId)
{
	m_loanSet.erase(bookId);
}

void Customer::reserveBook(int bookId)
{
	m_reservationSet.insert(bookId);
}

void Customer::unreserveBook(int bookId)
{
	m_reservationSet.erase(bookId);
}

auto operator<<(std::ostream& outStream, const Customer& customer)->std::ostream&
{
	outStream << "Customer ID: " << customer.m_customerId << " Name: " << customer.m_name << ", Address: " << customer.m_address << std::endl;
	if (!customer.m_loanSet.empty())
	{
		outStream << "     Borrow list: " << "[ ";
		bool first = true;
		for (auto book : customer.m_loanSet)
		{
			outStream << Library::s_bookMap[book] << (first ? "" : ", ");
			first = false;
		}
		outStream << " ]" << std::endl;
	}
	if (!customer.m_reservationSet.empty())
	{
		outStream << "     Reservation list: " << "[ ";
		bool first = true;
		for (auto book : customer.m_reservationSet)
		{
			outStream << Library::s_bookMap[book] << (first ? "" : ", ");
			first = false;
		}
		outStream << " ]";
	}

	return outStream;
}

void Customer::write(std::ofstream& outStream) const
{
	outStream.write((char*)& m_customerId, sizeof m_customerId);
	outStream << m_name << std::endl;
	outStream << m_address << std::endl;

	auto loanCount = m_loanSet.size();
	outStream.write((char*)& loanCount, sizeof loanCount);
	for (auto bookId : m_loanSet)
	{
		outStream.write((char*)& bookId, sizeof bookId);
	}

	auto reserveCount = m_reservationSet.size();
	outStream.write((char*)& reserveCount, sizeof reserveCount);
	for (auto bookId : m_reservationSet)
	{
		outStream.write((char*)& bookId, sizeof bookId);
	}
}

void Customer::read(std::ifstream& inStream)
{
	inStream.read((char*)& m_customerId, sizeof m_customerId);
	std::getline(inStream, m_name);
	std::getline(inStream, m_address);

	size_t loanCout = 0;
	inStream.read((char*)& loanCout, sizeof loanCout);
	for (int i = 0; i < loanCout; ++i)
	{
		int bookId = -1;
		inStream.read((char*)& bookId, sizeof bookId);
		m_loanSet.insert(bookId);
	}

	size_t reserveCount = 0;
	inStream.read((char*)& reserveCount, sizeof reserveCount);
	for (int i = 0; i < reserveCount; ++i)
	{
		int bookId = -1;
		inStream.read((char*)& bookId, sizeof bookId);
		m_reservationSet.insert(bookId);
	}

	if (m_customerId >= Customer::MAX_ID)
	{
		Customer::MAX_ID = m_customerId + 1;
	}
}