#pragma once
#include <set>
#include <fstream>
#include <string>

class Customer
{
public:
	Customer(void);
	Customer(const std::string& name, const std::string& address);

	void read(std::ifstream& inStream);
	void write(std::ofstream& outStream) const;

	void borrowBook(int bookId);
	void returnBook(int bookId);
	void reserveBook(int bookId);
	void unreserveBook(int bookId);

	auto hasBorrowed(void) const -> bool { return !m_loanSet.empty(); }

	auto name() const -> const std::string& { return m_name; }
	auto address() const -> const std::string& { return m_address; }
	auto id() const -> int { return m_customerId; }

	friend auto operator<<(std::ostream& outStream, const Customer& customer) -> std::ostream&;

private:
	int m_customerId;
	std::string m_name, m_address;
	std::set<int> m_loanSet, m_reservationSet;

	static int MAX_ID;
};