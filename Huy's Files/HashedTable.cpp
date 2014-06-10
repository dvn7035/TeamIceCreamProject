// Hashed Table class
// Huy Nguyen
// 06/03/2014


#include<string>
#include<iostream>
#include<vector>
#include "HashedTable.h"
#include<iomanip>

using namespace std;

const int maxProbe = 4;

HashedTable::HashedTable()
{
	size = 53; // default
	data = new IceCreamFlavor*[size];
	for (int i=0; i<size; i++)
	{
		data[i] = 0;
	}
	number = 0;
}

void HashedTable::AllocateMemory(int size)
{
	data = new IceCreamFlavor*[size];
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
	bool inserted = false;
	string food = address->getName();
	int index = HashingFunction(food);
	for(probe = 0; probe <= maxProbe && inserted == false; probe++ )
	{
		if (data[index] == 0)
		{
			data[index] = address;
			number++;
			//cout << data[index] << endl;
			data[index]->setProbes(probe);
			inserted = true;
		}
		else
		{
			index = ColRes(index,probe);
			if (index > size)
			{
				index = index % size;
			}
		}
	}
	return inserted;
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
	int max = 0;
	vector<IceCreamFlavor*> max_probe;
	int noCollision = 0;
	float factor = static_cast<float>(number) / size;
	cout << "There are " << number <<" type of ice creams in the menu" << endl;
	cout << "The size of the array is " << size << endl;
	cout << "Load factor is " << fixed << setprecision(2) << factor*100 << "%" << endl <<endl;
	cout << "Collisions: " << endl << endl;
	for( int i=0; i<size; i++)
	{
		if(data[i]!=0  && data[i]->getProbes() >= 1)
			cout << "Index:  "<< i << "  probes:  " << data[i]->getProbes() <<"  "<< *data[i]  << endl;
		if(data[i]!=0 && data[i]->getProbes() >= max)
		{
			max = data[i]->getProbes();
			max_probe.push_back(data[i]);
		}

		if(data[i]!=0 && data[i]->getProbes() == 0) noCollision ++;
	}

	cout << "Max number of probes is " << max << " at: " <<endl;
	for (size_t i = 0; i < max_probe.size(); i++)
	{
		if(max_probe[i]->getProbes() == max )
		cout << *(max_probe[i]) << "   ";
	}
	
	cout <<endl<< "No collision: " << noCollision << " ice creams" << endl;
}

bool HashedTable::search(int & index, string food)
{
	bool found = false;
	index = HashingFunction(food);
	for(int probes = 0; found == false  && probes <= maxProbe; probes ++)
	{
		if (food == data[index]->getName())
			found = true;
		else
			index = ColRes(index,probes);
	}
	return found;
}

bool HashedTable::remove(IceCreamFlavor* address, string food)
{
	int index= 0;
	if (search(index,food))
	{
		address = data[index];
		data[index] = 0;
		return true;
	}
	else return false;
}

void HashedTable::printTable()
{
	for( int i=0; i<size; i++)
	{

		if(data[i]!= 0 && data[i]->getProbes() >= 0)
			cout << "Index:  "<< i << "  probes:  " << data[i]->getProbes() <<"  "<< *data[i]  << endl;
	}
}