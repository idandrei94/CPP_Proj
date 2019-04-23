#pragma once

#include <list>

#include "Customer.h"
#include "Book.h"

class Library
{
public:
	Library(void);
	~Library();

private:
	auto lookupBook(const std::string& title, const std::string& author) -> Book*;
	auto lookupCustomer(const std::string& name, const std::string& address) -> Customer*;

	void addBook(void);
	void deleteBook(void);
	void listBooks(void);
	void addCustomer(void);
	void deleteCustomer(void);
	void listCustomers(void);
	void borrowBook(void);
	void reserveBook(void);
	void returnBook(void);

	auto lookupBookIndex(const Book *book) const -> int;
	auto lookupCustomerIndex(const Customer *customer) const -> int;
	auto lookupBookPtr(const int index) const -> Book*;
	auto lookupCustomerPtr(const int index) const -> Customer*;

	void load();
	void save();

private:
	std::list<Customer*> m_customerList;
	std::list<Book*> m_bookList;

private:
	static std::string s_binaryPath;
};