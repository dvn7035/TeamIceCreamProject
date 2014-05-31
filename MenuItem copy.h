// Menu Item (Data Record) class
// by Sean Ashe and David Nguyen

#ifndef _MENUITEM_H
#define _MENUITEM_H

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class MenuItem
{
private:
	string name;
	string nuts;
	int calories;
	double price;

public:
	// Default Constructor
	MenuItem()
	{
		name = "";
		nuts = "";
		calories = 0;
		price = 0.0;
	}

	// Constructor with parameters
	MenuItem(string input_name, string input_nuts, int input_calories, double input_price)
	{
		name = input_name;
		nuts = input_nuts;
		calories = input_calories;
		price = input_price;
	}

	// Accessors

	string getName() const
	{
		return name;
	}

	string getNuts() const
	{
		return nuts;
	}
	
	int getCalories() const
	{
		return calories;
	}

	double getPrice() const
	{
		return price;
	}

	// Operator Overloads

	friend ostream& operator<<(ostream &os, const MenuItem &obj)
	{
		return os << obj.name;
	}

	bool operator<(const MenuItem &right)
	{
		if (name < right.name)
			return true;
		return false;
	}

	bool operator>(const MenuItem &right)
	{
		if (name > right.name)
			return true;
		return false;
	}

	bool operator==(const MenuItem &right)
	{
		if (name == right.name)
			return true;
		return false;
	}

	bool operator!=(const MenuItem &right)
	{
		if (name == right.name)
			return false;
		return true;
	}

	const MenuItem operator=(const MenuItem &right)
	{
		name = right.name;
		nuts = right.nuts;
		calories = right.calories;
		price = right.price;
		return *this;
	}
};

// non-member function
void display(MenuItem & anItem)
{
	cout << left << setw(30) << anItem.getName() << setw(10) << anItem.getNuts() << setw(10) 
		 << anItem.getCalories() << setw(10) << anItem.getPrice() << endl;
}

#endif
