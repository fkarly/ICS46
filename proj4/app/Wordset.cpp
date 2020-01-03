#include "Wordset.hpp"
#include <string>
//Nanti hapus
#include <iostream>

const int BASE_TO_USE = 37;
const double LOAD_LIMIT = 0.25;

// Go through each letter and assign c as the letter in ASCII.
// Since a starts is 97, then subtract the c with 97.
// Multiply that number with base to the power of string length - 1
// and sum all of the numbers and mod it with the given mod.
int hashFunction(std::string s, int base, int mod)
{
	int sum = 0;
	for(int i = 0; i < s.size(); i++)
	{
		char c = s.at(i);
		int multiplicity = base;
		int num = (int)c - 97;
		int j;
		for(j = i+1; j < s.size() - 1; j++)
			multiplicity = (multiplicity * base) % mod;

		// Handler for the last word of the strings.
		// Set the multiplicity to 1 instead of the base.
		if(i == s.size() - 1)
			multiplicity = 1;

		sum = sum + num * multiplicity;
	}
	sum = sum % mod;
	//std::cout << sum << "\n";
	return sum;
}

// Constructor for WordSet function.
WordSet::WordSet()
{
	count = 0;
	index = 0;
	hashTable = new std::string [SIZES[index]];
	size = SIZES[index];
}

// Destructor
WordSet::~WordSet()
{
	delete [] hashTable;
}

// Insert function.
void WordSet::insert(std::string s)
{
	// If a new element insertion will cause a total of element greater than
	// the load limit * the size of the dynamic array, then rehashing.
	// Move all the elements in the array to a new temporary array and use
	// the new size as the mod to get the new hashFunction.
	// If this causes collision, then execute collisionHandling to get the new key.
	if(getCount() + 1 >= LOAD_LIMIT * getCapacity())
	{
		int oldSize = size;
		size = SIZES[++index];
		std::string * tmp = new std::string [size];
		for (int i = 0; i < oldSize; i++)
		{
			if(hashTable[i] != "")
			{
				int j = 0;
				int hashIndex = hashFunction(hashTable[i], BASE_TO_USE, getCapacity());
				while(tmp[hashIndex] != "")
					hashIndex = collisionHandling(hashIndex, ++j);
				tmp[hashIndex] = hashTable[i];
			}
		}
		hashTable = tmp;
	}

	// Insert the new strings according to the hashFunction.
	// If this causes a collision, then execute collisionHandling to get the new key.
	int hashIndex = hashFunction(s, BASE_TO_USE, getCapacity());
	int j = 0;
	while(hashTable[hashIndex] != "")
		hashIndex = collisionHandling(hashIndex, ++j);
	hashTable[hashIndex] = s;
	count++;
}

// Search if the array contains the string s using the hashFunction to get the
// key/index number. If the spot contains another string, then search the
// other possible spots using the quadratic probing.
bool WordSet::contains(std::string s) const
{
	int hashIndex = hashFunction(s, BASE_TO_USE, getCapacity());
	int j = 0;
	while(hashTable[hashIndex] != "")
	{
		if(s == hashTable[hashIndex])
			return true;
		j++;
		hashIndex = (hashIndex + j*j) % getCapacity();
	}

	return false;  // stub, not correct.
}

// return how many distinct strings are in the set
int WordSet::getCount() const
{
	return count;
}

// return how large the underlying array is.
int WordSet::getCapacity() const
{
	return size;
}

// Quadratic probing collision handling
int WordSet::collisionHandling(int hashIndex, int j)
{
	return ((hashIndex + j*j) % getCapacity());
}
