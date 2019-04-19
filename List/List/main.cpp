#include <iostream>
#include <cstdlib>

#include "List.h"

using namespace std;

int main(void)
{
	LinkedList<double> list;
	list.add(8);
	LinkedList<double> list2 = list;
	for (int i = 1; i <= 10; ++i)
	{
		list.add(i);
	}

	for (const double val : list)
	{
		cout << val << " ";
	}
	cout << endl;

	cout << list << endl;
	cout << list2 << endl;

	list.erase(list.begin());
	LinkedList<double>::Iterator it1 = list.begin();
	for (int i = 0; i < list.size()/2; ++i)
	{
		++it1;
	}
	LinkedList<double>::Iterator it2 = it1;
	for (int i = 0; i < list.size() / 4; ++i)
	{
		++it2;
	}
	cout << list << endl;
	list.remove(it1, it2);
	cout << list << endl;

	cout << "### FINISHED ###" << endl;
	return EXIT_SUCCESS;
}