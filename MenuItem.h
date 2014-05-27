#ifndef MENUITEM_H
#define MENUITEM_H


class MenuItem
{
private:
    string name;
    double price;
    int calories;
    bool vegetarian;
public:
    //Constructor
    MenuItem(string input_name, double input_price, int input_calories, bool input_vegetarian)
    {
        name = input_name;
        price = input_price;
        calories = input_calories;
        vegetarian = input_vegetarian;
    }
    //Display the Item
    friend ostream& operator<<(ostream & os)
    {
        return os << name;
    }
};
#endif
