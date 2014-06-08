#ifndef ICECREAMFLAVOR_H_INCLUDED
#define ICECREAMFLAVOR_H_INCLUDED

#include<string>
using namespace std;

class IceCreamFlavor
{
private:
    string name;
    double price;
    int calories;
    bool nuts;
public:
	//default constructor
	IceCreamFlavor() {name = "";price = 0; calories = 0, nuts = false;}
    //Constructor
    IceCreamFlavor(string input_name, double input_price, int input_calories, bool input_nuts)
    {
        name = input_name;
        price = input_price;
        calories = input_calories;
        nuts = input_nuts;
    }
	void setName(string str) {name = str;}
	void setPrice(double num) {price = num;}
	void setcal(int cal) {calories = cal;}
	void setnuts(bool nut) {nuts = nut;}

    // Accessors (David: I think some of these are unnesseary)

	string getName() const {return name;}
	bool getNuts() const {return nuts;} //getNuts lol
	int getCalories() const {return calories;}
	double getPrice() const {return price;}

	// Operator Overloads

	friend ostream& operator<< (ostream &os, const IceCreamFlavor &obj){return os << obj.name;}
	bool operator> (const IceCreamFlavor &right) {return (name > right.name);}
	bool operator< (const IceCreamFlavor &right) {return (name < right.name);}
	bool operator== (const IceCreamFlavor &right) {return (name == right.name);} 
	bool operator!= (const IceCreamFlavor &right) {return !operator==(right);}
    IceCreamFlavor& operator= (const IceCreamFlavor &right)
	{
		name = right.name;
		nuts = right.nuts;
		calories = right.calories;
		price = right.price;
		return *this;
	}
};
#endif // ICECREAMFLAVOR_H_INCLUDED
