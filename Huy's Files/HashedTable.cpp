// Hashed Table class
// Huy Nguyen
// 06/03/2014


#include<string>
#include<iostream>
#include<vector>
#include "HashedTable.h"
#include<iomanip>

using namespace std;

HashedTable::HashedTable()
{
	size = 53; // default
	data = new IceCreamFlavor*[size];
	probe = new int [size];
	for (int i=0; i<size; i++)
	{
		data[i] = 0;
	}
	number = 0;
}

HashedTable::HashedTable( int size)
{
	data = new IceCreamFlavor*[size];
	probe = new int[size];
	for (int i=0; i<size; i++)
	{
		data[i] = 0;
	}
	number = 0;
	this->size = size;
}

int HashedTable:: HashingFunction(string food)
{
	int index = 0;
	long sum=0;
	const char * temp = food.c_str();
	for(size_t i=0; i < food.length() ; i++)
	{
		sum = sum + (i+13)*temp[i]; // add more random to the number by changing i (loop) and add it with a prime number
	}
	index = (sum) %  size;
	return index;
}

bool HashedTable :: add(IceCreamFlavor* address)
{
	cout << size << endl;
	cout << address << endl;
	int probe=0;
	bool success = false;
	string food = address->getName();
	int index = HashingFunction(food);
	while ( success == false)
	{
		if (data[index] == 0 )
		{
			data[index] = address;
			cout << data[index] << endl;
			this->probe[index] = probe;
			success = true;
		}
		else
		{
			probe++;
			index = ColRes(index,probe);
			if (index > size)
			{
				index = index % size;
			}
		}
	}
	return success;
}

//quadratic
int HashedTable::ColRes (int index, int probe)
{
	int result=0;
	result = index + probe*probe;
	return result;
}


void HashedTable::displayStats()
{
	int max = probe[0];
	vector<IceCreamFlavor*> max_probe;
	int noCollision = 0;
	float factor = static_cast<float>(number) / size;
	cout << "There are " << number <<" dishes in the menu" << endl;
	cout << "The size of the array is " << size << endl;
	cout << "Load factor is " << fixed << setprecision(2) << factor*100 << "%" << endl <<endl;
	cout << "Collisions: " << endl << endl;
	for( int i=0; i<size; i++)
	{
		if(probe[i] > 1)
			cout << "Index:  "<< i << "  probes:  " << probe[i] << endl;
		if(probe[i] >= max)
		{
			max = probe[i];
			max_probe.push_back(data[i]);
		}

		if(probe[i] == 0) noCollision ++;
	}
	cout << "Max number of probes is " << max << " at: " <<endl;
	for (size_t i = 0; i < max_probe.size(); i++)
	{
		cout << max_probe[i];
	}
	
	cout <<endl<< "No collision: " << noCollision << " dishes" << endl;
}