#include <iostream>

#include "Library.h"

std::string Library::s_binaryPath("Library.bin");

std::map<int, Customer> Library::s_customerMap;
std::map<int, Book> Library::s_bookMap;

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

auto Library::lookupBook(const std::string& title, const std::string& author, Book* bookPtr) -> bool
{
	for (const std::pair<int, Book>& entry : s_bookMap)
	{
		const Book& book = entry.second;
		if ((book.author() == author) && (book.title() == title))
		{
			if (bookPtr != nullptr)
			{
				*bookPtr = book;
			}
			return true;
		}
	}
	return false;
}


auto Library::lookupCustomer(const std::string& name, const std::string& address, Customer* customerPtr) -> bool
{
	for (const std::pair<int, Customer>& entry : s_customerMap)
	{
		const Customer& customer = entry.second;
		if ((customer.name() == name) && (customer.address() == address))
		{
			if (customerPtr != nullptr)
			{
				*customerPtr = customer;
			}
			return true;
		}
	}
	return false;
}

void Library::addBook(void)
{
	std::string author;
	std::string title;

	std::cout << "Title: ";
	std::getline(std::cin >> std::ws, title);
	

	std::cout << "Author: ";
	std::getline(std::cin >> std::ws, author);

	Book book(title, author);
	if (lookupBook(title, author, &book))
	{
		std::cout << std::endl << "Book" << book << " already exists." << std::endl;
		return;
	}
	s_bookMap[book.bookID()] = book;
	std::cout << std::endl << "Added: " << book << std::endl;
}

void Library::deleteBook(void)
{
	std::string author;
	std::string title;

	std::cout << "Title: ";
	std::getline(std::cin >> std::ws, title);

	std::cout << "Author: ";
	std::getline(std::cin >> std::ws, author);
	
	Book book;
	if (!lookupBook(title, author, &book))
	{
		std::cout << std::endl << "Book " << book << std::endl;
		return;
	}

	for (auto entry : s_customerMap)
	{
		Customer& customer = entry.second;
		customer.returnBook(book.bookID());
		customer.unreserveBook(book.bookID());
		s_customerMap[customer.id()] = customer;
	}

	s_bookMap.erase(book.bookID());
	std::cout << std::endl << "Deleted " << book << std::endl;
}

void Library::listBooks(void)
{
	if (s_bookMap.size() == 0)
	{
		std::cout << "No books." << std::endl;
		return;
	}

	for (auto bookPair : s_bookMap)
	{
		const Book& book = bookPair.second;
		std::cout << book << std::endl;
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

	Customer customer(name, address);
	if (lookupCustomer(name, address, &customer))
	{
		std::cout << std::endl << "Customer " << customer << " already exists." << std::endl;
		return;
	}
	s_customerMap[customer.id()] = customer;
	std::cout << std::endl << "Added: " << customer << std::endl;
}

void Library::deleteCustomer(void)
{
	std::string name;
	std::string address;

	std::cout << "Name: ";
	std::getline(std::cin >> std::ws, name);

	std::cout << "Address: ";
	std::getline(std::cin >> std::ws, address);

	Customer customer;
	if (!lookupCustomer(name, address, &customer))
	{
		std::cout << std::endl << "Customer " << name << " with address " << address << " doesn't exist." << std::endl;
		return;
	}

	if (customer.hasBorrowed())
	{
		std::cout << std::endl << "Customer " << customer << " has pending loans." << std::endl;
		return;
	}

	for (auto bookPair : s_bookMap)
	{
		Book& book = bookPair.second;
		book.unreserveBook(customer.id());
		s_bookMap[book.bookID()] = book;
	}

	std::cout << std::endl << "Deleted " << customer;
	s_customerMap.erase(customer.id());
}

void Library::listCustomers(void)
{
	if (s_customerMap.size() == 0)
	{
		std::cout << "No customers." << std::endl;
		return;
	}

	for (auto custPair : s_customerMap)
	{
		const Customer& customer = custPair.second;
		std::cout << customer << std::endl;
	}
}

void Library::borrowBook(void)
{
	std::string title, author, name, address;

	std::cout << "Title: ";
	std::getline(std::cin >> std::ws, title);

	std::cout << "Author: ";
	std::getline(std::cin >> std::ws, author);

	Book book;
	if (!lookupBook(title, author, &book))
	{
		std::cout << std::endl << "Book \"" << title << "\" by " << author << " does not exist." << std::endl;
		return;
	}

	if (book.borrowed())
	{
		std::cout << std::endl << "Book " << book << " is not available." << std::endl;
		return;
	}

	std::cout << "Name: ";
	std::getline(std::cin >> std::ws, name);
	
	std::cout << "Address: ";
	std::getline(std::cin >> std::ws, address);
	
	Customer customer;
	if (!lookupCustomer(name, address, &customer))
	{
		std::cout << std::endl << "Customer " << customer << " does not exist." << std::endl;
		return;
	}

	book.borrowBook(customer.id());
	customer.borrowBook(book.bookID());

	s_bookMap[book.bookID()] = book;
	s_customerMap[customer.id()] = customer;

	std::cout << std::endl << "Book " << book << std::endl <<" successfully lent to " << customer << std::endl;
}

void Library::reserveBook(void)
{
	std::string title, author, name, address;

	std::cout << "Title: ";
	std::getline(std::cin >> std::ws, title);

	std::cout << "Author: ";
	std::getline(std::cin >> std::ws, author);
	
	Book book;
	if (!lookupBook(title, author, &book))
	{
		std::cout << std::endl << "Book " << book << " does not exist." << std::endl;
		return;
	}

	if (!book.borrowed())
	{
		std::cout << std::endl << "Book " << book << std::endl << " is available, lend it instead." << std::endl;
		return;
	}

	std::cout << "Name: ";
	std::getline(std::cin >> std::ws, name);

	std::cout << "Address: ";
	std::getline(std::cin >> std::ws, address);

	Customer customer;
	if (!lookupCustomer(name, address, &customer))
	{
		std::cout << std::endl << "Customer " << customer << " does not exist." << std::endl;
		return;
	}

	book.reserveBook(customer.id());
	customer.reserveBook(book.bookID());

	s_bookMap[book.bookID()] = book;
	s_customerMap[customer.id()] = customer;

	std::cout << std::endl << "Book " << book << " lent successfully to " << customer << std::endl;
}

void Library::returnBook(void)
{
	std::string title, author;

	std::cout << "Title: ";
	std::getline(std::cin >> std::ws, title);
	
	std::cout << "Author: ";
	std::getline(std::cin >> std::ws, author);

	Book book;
	if (!lookupBook(title, author, &book))
	{
		std::cout << std::endl << "Book " << book << " does not exist." << std::endl;
		return;
	}

	if (!book.borrowed())
	{
		std::cout << std::endl << "Book " << book << " is available." << std::endl;
		return;
	}

	Customer& customer = s_customerMap[book.customerID()];
	customer.returnBook(book.bookID());
	s_customerMap[customer.id()] = customer;

	book.returnBook();

	std::cout << std::endl << "Book " << book << " has been returned." << std::endl;

	std::list<int>& reservationList = book.reservationList();
	if (!reservationList.empty())
	{
		int nextCustomerId = reservationList.front();
		reservationList.pop_front();
		book.borrowBook(nextCustomerId);

		Customer& customer = s_customerMap[nextCustomerId];
		customer.unreserveBook(book.bookID());
		customer.borrowBook(book.bookID());

		s_customerMap[nextCustomerId] = customer;

		std::cout << std::endl << "Book " << book << std::endl << " has been lent to " << customer << "." << std::endl;
	}

	s_bookMap[book.bookID()] = book;
}

void Library::save()
{
	std::ofstream outStream(s_binaryPath);

	auto bookCount = s_bookMap.size();
	auto customerCount = s_customerMap.size();

	outStream.write((char*)& bookCount, sizeof bookCount);
	outStream.write((char*)& customerCount, sizeof customerCount);

	for (auto pair : s_bookMap)
	{
		const Book &book = pair.second;
		book.write(outStream);
	}

	for (auto pair : s_customerMap)
	{
		const Customer &customer = pair.second;
		customer.write(outStream);
	}
}

void Library::load()
{
	std::ifstream instream(s_binaryPath);
	size_t bookCount     = 0, 
		   customerCount = 0;

	instream.read((char*)&bookCount, sizeof bookCount);
	instream.read((char*)&customerCount, sizeof customerCount);

	for (int i = 0; i < bookCount; ++i)
	{
		Book newBook;
		newBook.read(instream);
		s_bookMap[newBook.bookID()] = newBook;
	}

	for (int i = 0; i < customerCount; ++i)
	{
		Customer newCust;
		newCust.read(instream);
		s_customerMap[newCust.id()] = newCust;
	}
}
