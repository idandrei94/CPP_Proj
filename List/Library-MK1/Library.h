#pragma once

#include <map>

#include "Customer.h"
#include "Book.h"

class Library
{
public:
	Library(void);

private:
	auto lookupBook(const std::string& title, const std::string& author, Book* bookPtr = nullptr) -> bool;
	auto lookupCustomer(const std::string& name, const std::string& address, Customer* customerPtr = nullptr) -> bool;

	void addBook(void);
	void deleteBook(void);
	void listBooks(void);
	void addCustomer(void);
	void deleteCustomer(void);
	void listCustomers(void);
	void borrowBook(void);
	void reserveBook(void);
	void returnBook(void);

	void load();
	void save();

private:
	static std::string s_binaryPath;

public:
	static std::map<int, Customer> s_customerMap;
	static std::map<int, Book> s_bookMap;
};