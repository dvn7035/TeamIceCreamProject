// Hashed Table class
// Huy Nguyen
// 06/03/2014


#include<string>
#include<iostream>
#include<vector>
#include "HashedTable.h"
#include<iomanip>
#include<cmath>

using namespace std;

// check whether a number is a prime number
bool IsPrime(int number)
{	// Given:   num an integer > 1
	// Returns: true if num is prime
	// 			false otherwise.
	
	int i;
	
	for (i=2; i<number; i++)
	{
		if (number % i == 0)
		{
			return false;
		}
	}
	
	return true;	
}

// allocation for the prime number size of the hash array based on the number user give
void HashedTable::AllocateMemory(int count)
{
	size = count * 2 + 1;
	while ( !IsPrime(size)) size ++; 
	data = new IceCreamFlavor*[size];
	for (int i=0; i<size; i++)
	{
		data[i] = 0;
	}
	number = 0;
	this->size = size;
	maxProbe = log((float) count) / log( (float)2);  //maxProbe should always be <= the efficiency of the binary tree log_2(n) 
}

/*Hashing function: receive name of IceCreamFlavor as a key, cube the ASCII value of each character then add them up
Finally modulus for size of the array
if we square, for example, the last digits are always 1, 4 , 6 ,9
In another hand, cube the ascii value: add more random and range so we easily fill all the indexes of the arrray*/
int HashedTable:: HashingFunction(string food)
{
	
	int index = 0;
	int cube;
	for (size_t i = 0; i < food.length(); i++)
	{
		cube = pow(food[i],3.0);
		index += cube;
	}
	if (index >= size)
	{
		index = index % size;
	}
	return index;
}


bool HashedTable :: add(IceCreamFlavor* address)
{

	int probe=0;
	bool inserted = false;
	string food = address->getName();
	int index = HashingFunction(food);

	while (inserted == false)
	{
		
		if (data[index] == 0)
		{
			data[index] = address;
			number++;
			data[index]->setProbes(probe);
			inserted = true;
		}
		else
		{
			probe ++;
			index = ColRes(index,probe);
			
		}
	}

	return inserted;
}

//quadratic
int HashedTable::ColRes (int index, int probe)
{
	int result=0;
	result = index + probe*probe;
	if (result >= size-1)
			{
				result = result % size;
			}
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

bool HashedTable::getEntry(const IceCreamFlavor* target , IceCreamFlavor* & returned)
{
	bool found = false;
	string food = target->getName();
	int index = HashingFunction(food);
	for(int probes = 0; found == false  && probes <= maxProbe; probes ++)
	{

		if (data[index] != 0 && food == data[index]->getName())
		{
			found = true;
			returned = data[index];
		}
		else
			index = ColRes(index,probes);
	}
	return found;
}

// private function to access the index
bool HashedTable::search(int & index, string food)
{
	bool found = false;
	index = HashingFunction(food);
	for(int probes = 0; found == false  && probes <= maxProbe; probes ++)
	{
		if (data[index] != 0 && food == data[index]->getName())
			found = true;
		else
			index = ColRes(index,probes);
	}
	return found;

}

bool HashedTable::remove(IceCreamFlavor* target, IceCreamFlavor* &returned)
{
	int index= 0;
	string food = target->getName();
	if (search(index,food))	//this line
	{
		returned = data[index];
		data[index] = 0;
		number--;
		return true;
	}
	else
		return false;
}

void HashedTable::printTable()
{
	for( int i=0; i<size; i++)
	{

		if(data[i]!= 0 && data[i]->getProbes() >= 0)
			cout <<*data[i];//  << endl;
	}
}

void HashedTable::DeallocateMemory()
{
	delete[] data;
}