#include <iostream>

#include <cassert>
#include <list>

#include "Library.h"

std::string Library::s_binaryPath("Library.bin");

Library::Library(void)
{
	load();

	bool quit = false;
	while (!quit)
	{
		std::cout 
			<< "1. Add Book" << std::endl
			<< "2. Delete Book" << std::endl
			<< "3. List Books" << std::endl
			<< "4. Add Customer" << std::endl
			<< "5. Delete Customer" << std::endl
			<< "6. List Customers" << std::endl
			<< "7. Borrow Book" << std::endl
			<< "8. Reserve Book" << std::endl
			<< "9. Return Book" << std::endl
			<< "0. Quit" << std::endl
			<< ": ";
		int choice;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			addBook();
			break;
		case 2:
			deleteBook();
			break;
		case 3:
			listBooks();
			break;
		case 4:
			addCustomer();
			break;
		case 5:
			deleteCustomer();
			break;
		case 6:
			listCustomers();
			break;
		case 7:
			borrowBook();
			break;
		case 8:
			reserveBook();
			break;
		case 9:
			returnBook();
			break;
		case 0:
			quit = true;
			break;
		default:
			std::cout << "Invalid input!" << std::endl;
			break;
		}
	}
	save();
}

auto Library::lookupBook(const std::string& title, const std::string& author) -> Book*
{
	for (Book* book : m_bookList)
	{
		if ((book->author() == author) && (book->title() == title))
		{
			return book;
		}
	}
	return nullptr;
}


auto Library::lookupCustomer(const std::string& name, const std::string& address) -> Customer*
{
	for (Customer* customer : m_customerList)
	{
		if ((customer->name() == name) && (customer->address() == address))
		{
			return customer;
		}
	}
	return nullptr;
}

void Library::addBook(void)
{
	std::string author;
	std::string title;

	std::cout << "Title: ";
	std::getline(std::cin >> std::ws, title);
	

	std::cout << "Author: ";
	std::getline(std::cin >> std::ws, author);

	Book *book = lookupBook(title, author);
	if (book)
	{
		std::cout << std::endl << "Book" << *book << " already exists." << std::endl;
		return;
	}

	book = new Book(title, author);
	assert(book);
	m_bookList.push_back(book);

	std::cout << std::endl << "Added: " << *book << std::endl;
}

void Library::deleteBook(void)
{
	std::string author;
	std::string title;

	std::cout << "Title: ";
	std::getline(std::cin >> std::ws, title);

	std::cout << "Author: ";
	std::getline(std::cin >> std::ws, author);
	
	Book *book = lookupBook(title, author);
	if (!book)
	{
		std::cout << std::endl << "Book \"" << title << "\" by " << title << " does not exist. " << std::endl;
		return;
	}

	for (auto customer : m_customerList)
	{
		customer->returnBook(book);
		customer->unreserveBook(book);
	}

	m_bookList.remove(book);
	std::cout << std::endl << "Deleted " << *book << std::endl;

	delete book;
}

void Library::listBooks(void)
{
	if (m_bookList.size() == 0)
	{
		std::cout << "No books." << std::endl;
		return;
	}

	for (auto book : m_bookList)
	{
		std::cout << (*book) << std::endl;
	}
	std::cout << std::endl;
}

void Library::addCustomer(void)
{
	std::string name;
	std::string address;

	std::cout << "Name: ";
	std::getline(std::cin >> std::ws, name);

	std::cout << "Address: ";
	std::getline(std::cin >> std::ws, address);

	Customer *customer = lookupCustomer(name, address);
	if (customer)
	{
		std::cout << std::endl << "Customer " << *customer << " already exists." << std::endl;
		return;
	}
	customer = new Customer(name, address);
	assert(customer);
	m_customerList.push_back(customer);

	std::cout << std::endl << "Added: " << (*customer) << std::endl;
}

void Library::deleteCustomer(void)
{
	std::string name;
	std::string address;

	std::cout << "Name: ";
	std::getline(std::cin >> std::ws, name);

	std::cout << "Address: ";
	std::getline(std::cin >> std::ws, address);

	Customer *customer = lookupCustomer(name, address);
	if (!customer)
	{
		std::cout << std::endl << "Customer " << name << " with address " << address << " doesn't exist." << std::endl;
		return;
	}

	if (customer->hasBorrowed())
	{
		std::cout << std::endl << "Customer " << *customer << " has pending loans." << std::endl;
		return;
	}

	for (auto book : m_bookList)
	{
		book->unreserveBook(customer);
	}

	std::cout << std::endl << "Deleted " << *customer << std::endl;
	delete customer;
}

void Library::listCustomers(void)
{
	if (m_customerList.size() == 0)
	{
		std::cout << "No customers." << std::endl;
		return;
	}

	for (auto customer : m_customerList)
	{
		std::cout << *customer << std::endl;
	}
	std::cout << std::endl;
}

void Library::borrowBook(void)
{
	std::string title, author, name, address;

	std::cout << "Title: ";
	std::getline(std::cin >> std::ws, title);

	std::cout << "Author: ";
	std::getline(std::cin >> std::ws, author);

	Book *book = lookupBook(title, author);
	if (!book)
	{
		std::cout << std::endl << "Book \"" << title << "\" by " << author << " does not exist." << std::endl;
		return;
	}

	if (book->borrower() )
	{
		std::cout << std::endl << "Book " << *book << " is not available." << std::endl;
		return;
	}

	std::cout << "Name: ";
	std::getline(std::cin >> std::ws, name);
	
	std::cout << "Address: ";
	std::getline(std::cin >> std::ws, address);
	
	Customer *customer = lookupCustomer(name, address);
	if (!customer)
	{
		std::cout << std::endl << "Customer " << name << " with address " << address << " does not exist." << std::endl;
		return;
	}

	book->borrowBook(customer);
	customer->borrowBook(book);
	customer->unreserveBook(book);

	std::cout << std::endl << "Book " << *book << std::endl <<" successfully lent to " << *customer << std::endl;
}

void Library::reserveBook(void)
{
	std::string title, author, name, address;

	std::cout << "Title: ";
	std::getline(std::cin >> std::ws, title);

	std::cout << "Author: ";
	std::getline(std::cin >> std::ws, author);
	
	Book *book = lookupBook(title, author);
	if (!book)
	{
		std::cout << std::endl << "Book \"" << title << "\" by " << author << " does not exist." << std::endl;
		return;
	}

	if (!book->borrower())
	{
		std::cout << std::endl << "Book " << *book << std::endl << " is available, lend it instead." << std::endl;
		return;
	}

	std::cout << "Name: ";
	std::getline(std::cin >> std::ws, name);

	std::cout << "Address: ";
	std::getline(std::cin >> std::ws, address);

	Customer *customer = lookupCustomer(name, address);
	if (!customer)
	{
		std::cout << std::endl << "Customer " << name << " with address " << address << " does not exist." << std::endl;
		return;
	}

	book->reserveBook(customer);
	customer->reserveBook(book);

	std::cout << std::endl << "Book " << *book << " lent successfully to " << *customer << std::endl;
}

void Library::returnBook(void)
{
	std::string title, author;

	std::cout << "Title: ";
	std::getline(std::cin >> std::ws, title);
	
	std::cout << "Author: ";
	std::getline(std::cin >> std::ws, author);

	Book *book = lookupBook(title, author);
	if (!book)
	{
		std::cout << std::endl << "Book \"" << title << "\" by " << author << " does not exist." << std::endl;
		return;
	}

	if (!book->borrower())
	{
		std::cout << std::endl << "Book " << *book << " is available." << std::endl;
		return;
	}

	(book->borrower())->returnBook(book);

	book->returnBook();

	std::cout << std::endl << "Book " << *book << " has been returned." << std::endl;

	if (book->reservationList().size() > 0)
	{
		Customer *customer = book->reservationList().front();
		book->reservationList().pop_front();

		book->borrowBook(customer);
		customer->borrowBook(book);
		customer->unreserveBook(book);

		std::cout << std::endl << "Book " << *book << std::endl << " has been lent to " << *customer << "." << std::endl;
	}
}

auto Library::lookupBookIndex(const Book *book) const -> int
{
	int index = 0;
	for (auto iter : m_bookList)
	{
		if (iter == book)
		{
			return index;
		}
		++index;
	}
	assert(false);
	return -1;
}

auto Library::lookupCustomerIndex(const Customer *customer) const -> int
{
	int index = 0;
	for (auto cust : m_customerList)
	{
		if (cust == customer)
		{
			return index;
		}
		++index;
		std::cout << index << std::endl;
	}
	assert(false);
	return -1;
}

auto Library::lookupBookPtr(const int index) const->Book*
{
	assert(index >= 0 && index < (int)m_bookList.size());

	auto iter = m_bookList.begin();
	for (int i = 0; i < index; ++i)
	{
		++iter;
	}
	return *iter;
}

auto Library::lookupCustomerPtr(const int index) const->Customer*
{
	assert(index >= 0 && index < (int)m_customerList.size());

	auto iter = m_customerList.begin();
	for (int i = 0; i < index; ++i)
	{
		++iter;
	}
	return *iter;
}

void Library::save()
{
	std::ofstream outStream(s_binaryPath);

	int bookCount = (int)m_bookList.size();
	int customerCount = (int)m_customerList.size();

	outStream.write((char*)& bookCount, sizeof bookCount);
	outStream.write((char*)& customerCount, sizeof customerCount);

	for (auto book : m_bookList)
	{
		book->write(outStream);
	}

	for (auto customer : m_customerList)
	{
		customer->write(outStream);
	}
	std::cout << "Saved basic data." << std::endl;
	for (auto book : m_bookList)
	{
		std::cout << "Saving book " << *book << std::endl;
		bool borrowed = (book->borrower() != nullptr);
		outStream.write((char*)& borrowed, sizeof borrowed);
		if (borrowed)
		{
			int customerIdx = lookupCustomerIndex(book->borrower());
			outStream.write((char*)& customerIdx, sizeof customerIdx);
		}
		int reservationCount = (int)book->reservationList().size();
		outStream.write((char*)& reservationCount, sizeof reservationCount);
		for (auto customer : book->reservationList())
		{
			int customerIdx = lookupCustomerIndex(customer);
			outStream.write((char*)& customerIdx, sizeof customerIdx);
		}
	}

	for (auto customer : m_customerList)
	{
		int borrowCount = (int)customer->loans().size();
		outStream.write((char*)& borrowCount, sizeof borrowCount);
		for (auto book : customer->loans())
		{
			int bookIdx = lookupBookIndex(book);
			outStream.write((char*)& bookIdx, sizeof bookIdx);
		}
		int reservationCount = (int)customer->reservations().size();
		outStream.write((char*)& reservationCount, sizeof reservationCount);
		for (auto book : customer->reservations())
		{
			int bookIdx = lookupBookIndex(book);
			outStream.write((char*)& bookIdx, sizeof bookIdx);
		}
	}
}

void Library::load()
{
	std::ifstream inStream(s_binaryPath);
	int bookCount = 0;
	int customerCount = 0;
	inStream.read((char*)& bookCount, sizeof bookCount);
	inStream.read((char*)& customerCount, sizeof customerCount);
	std::cout << "reading " << bookCount << " books and " << customerCount << " customers" << std::endl;

	for (int i = 0; i < bookCount; ++i)
	{
		Book *book = new Book();
		book->read(inStream);
		m_bookList.push_back(book);
	}

	for (int i = 0; i < customerCount; ++i)
	{
		Customer *customer = new Customer();
		customer->read(inStream);
		m_customerList.push_back(customer);
	}

	for (auto book : m_bookList)
	{
		bool borrowed = false;
		inStream.read((char*)& borrowed, sizeof borrowed);
		if (borrowed)
		{
			int customerIdx = -1;
			inStream.read((char*)& customerIdx, sizeof customerIdx);
			book->borrower() = lookupCustomerPtr(customerIdx);
		}

		int reservationCount = 0;
		inStream.read((char*)& reservationCount, sizeof reservationCount);
		for (int i = 0; i < reservationCount; ++i)
		{
			int customerIdx = -1;
			inStream.read((char*)& customerIdx, sizeof customerIdx);
			book->reservationList().push_back(lookupCustomerPtr(customerIdx));
		}
	}

	for (auto customer : m_customerList)
	{
		int borrowCount = 0;
		inStream.read((char*)& borrowCount, sizeof borrowCount);
		for (int i = 0; i < borrowCount; ++i)
		{
			int bookIdx = -1;
			inStream.read((char*)& bookIdx, sizeof bookIdx);
			customer->loans().push_back(lookupBookPtr(bookIdx));
		}
		int reservationCount = 0;
		inStream.read((char*)& reservationCount, sizeof reservationCount);
		for (int i = 0; i < reservationCount; ++i)
		{
			int bookIdx = -1;
			inStream.read((char*)& bookIdx, sizeof bookIdx);
			customer->reservations().push_back(lookupBookPtr(bookIdx));
		}
	}
}

Library::~Library()
{
	for (auto book : m_bookList)
	{
		delete book;
	}
	for (auto customer : m_customerList)
	{
		delete customer;
	}
}
