#include "Customer.h"

Customer::Customer(void) { }

Customer::Customer(const std::string& name, const std::string& address) : m_name(name), m_address(address) { }

void Customer::borrowBook(Book *book)
{
	m_loanList.push_back(book);
}

void Customer::returnBook(Book *book)
{
	m_loanList.remove(book);
}

void Customer::reserveBook(Book *book)
{
	m_reservationList.push_back(book);
}

void Customer::unreserveBook(Book *book)
{
	m_reservationList.remove(book);
}

auto operator<<(std::ostream& outStream, const Customer& customer)->std::ostream&
{
	outStream << "Name: " << customer.m_name << ", Address: " << customer.m_address << std::endl;
	if (!customer.m_loanList.empty())
	{
		outStream << "     Borrow list: " << "[ ";
		bool first = true;
		for (auto book : customer.m_loanList)
		{
			outStream << (*book) << (first ? "" : ", ");
			first = false;
		}
		outStream << " ]" << std::endl;
	}
	if (!customer.m_reservationList.empty())
	{
		outStream << "     Reservation list: " << "[ ";
		bool first = true;
		for (auto book : customer.m_reservationList)
		{
			outStream << (*book) << (first ? "" : ", ");
			first = false;
		}
		outStream << " ]";
	}

	return outStream;
}

void Customer::write(std::ofstream& outStream) const
{
	outStream << m_name << std::endl;
	outStream << m_address << std::endl;
}

void Customer::read(std::ifstream& inStream)
{
	std::getline(inStream, m_name);
	std::getline(inStream, m_address);
}