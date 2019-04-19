#pragma once

#include <map>

#include "Customer.h"

class Library
{
public:
	Library(void) {}
	static std::map<int, Customer> s_customerMap;
};