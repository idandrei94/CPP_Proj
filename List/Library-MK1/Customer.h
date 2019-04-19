#pragma once

class Customer
{
public:
	std::string m_name;
	Customer() : m_name("customer name") {};
	auto name() const->std::string { return m_name; }
};