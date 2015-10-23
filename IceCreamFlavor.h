#ifndef ICECREAMFLAVOR_H_INCLUDED
#define ICECREAMFLAVOR_H_INCLUDED

#include<string>
#include<iomanip>
#include<iostream>

using namespace std;

class IceCreamFlavor
{
private:
    string name;
    double price;
    int calories;
    int probes;
    bool nuts;
public:
	//default constructor
	IceCreamFlavor() {name = "";price = 0; calories = 0; probes =0; nuts = false;}
    //Constructor
    IceCreamFlavor(string input_name, double input_price, int input_calories, bool input_nuts)
    {
        name = input_name;
        price = input_price;
        calories = input_calories;
        nuts = input_nuts;
        probes = 0;
    }
	void setName(string str) {name = str;}
	void setPrice(double num) {price = num;}
	void setcal(int cal) {calories = cal;}
	void setnuts(bool nut) {nuts = nut;}
	void setProbes(int num) {probes = num;}

    // Accessors 
	string getName() const {return name;}
	bool getNuts() const {return nuts;} 
	int getCalories() const {return calories;}
	double getPrice() const {return price;}
	int getProbes() const {return probes;}

	// Operator Overloads
	friend ostream& operator<< (ostream &os, const IceCreamFlavor &obj)
	{
		string nut;
		if (obj.nuts ==  true)
			nut = "nut";
		else 
			nut = "no nut";
		return os << obj.name <<", "<<nut<<", "<<obj.calories<<", "<<obj.price<<endl;
	}
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