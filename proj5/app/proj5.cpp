//proj5.cpp

#include <iostream>
#include <sstream>
#include <string>
#include "proj5.hpp"

// Function that returns true if and only if the strings is min heap.
// If it's a mean heap, then all the children must have greater value
// then its parent. Since we start with with index 0 as the root,
// then the parent of a node i is floor((i-1)/2). Since int division
// by default is using the floor function, then we can leave it as is.
bool isMinHeap(std::string s)
{
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i] < s[(i-1)/2])
			return false;
	}
	return true;
}

// Bubble sort.
// Start from the first element, if the next element is bigger, then swap.
// Keep swaping until the last element. There is no need to check the last
// element, since if strings prior to the last one is sorted, then the last
// element must be sorted too.
void doSomeSort(std::vector<std::string> & vec)
{
	for(int i = 0; i < vec.size() - 1; i++)
	{
		for(int j = 0; j < vec.size() - 1; j++)
		{
			if(vec[j] > vec[j+1])
			{
				std::string tmp = vec[j];
				vec[j] = vec[j+1];
				vec[j+1] = tmp;
			}
		}
	}
}

// Function that will sort a set of strings if the strings are MinHeap.
// Return the sorted vector.
std::vector<std::string> findHeaps(std::istream & in)
{
	std::vector <std::string> vec;
	std::string line, word;
	std::stringstream ss;
	while(getline(in, line))
	{
		ss.clear();
		ss << line;
		while(ss >> word)
		{
			if(isMinHeap(word))
				vec.push_back(word);
		}
	}

	doSomeSort(vec);

	return vec;
}
