// proj2.cpp

#include "proj2.hpp"
#include "LLQueue.hpp"

#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::map<int, int> assignBusSeats(std::istream & in)
{
	std::string line;
	int numSeats = 0;
	int k = 0;															// Mark for Window preference seperation.
	int l = 0;															// Mark for Aisle preference seperation.
	int p;
	std::stringstream ss;
	LLQueue<int> windowQueue;
	LLQueue<int> windowPreference;
	LLQueue<int> aislePreference;
	std::map<int,int> seatingArrangment;
	std::vector<int> assignedA;							// To know if A has been assigned or no.

	getline(in, line);
	numSeats = atoi(line.c_str());

	getline(in, line);
	ss << line;

	// Queueing everyone who wants a window seat
	for(int i = 1; i <= numSeats; i++)
		windowQueue.enqueue(i);

	// Queueing the window people's preference
	for(int i = 1; i <= numSeats; i++)
	{
		for(int j = 1; j <= numSeats; j++)
		{
			ss >> p;
			windowPreference.enqueue(p);
		}

		// Add -1, -2, ... to indicate the end of one's preference list.
		k--;
		windowPreference.enqueue(k);

		std::stringstream().swap(ss);
		getline(in, line);
		ss << line;
	}

	// Queueing the Aisle people's preference
	for(int i = 1; i <= numSeats; i++)
	{
		for(int j = 1; j <= numSeats; j++)
		{
			ss >> p;
			aislePreference.enqueue(p);
		}

		// Add -1, -2, ... to indicate the end of one's preference list.
		l--;
		aislePreference.enqueue(l);

		std::stringstream().swap(ss);
		getline(in, line);
		ss << line;
	}

	// Keep paring until everyone has a partner
	while(windowQueue.isEmpty() == false)
	{
		// Iterator for searching A's partner
		std::vector<int>::iterator it;
		std::map<int, int>::iterator mapIt;
		int target = 0;

		// To get to the correct Window people's preference
		int windowStartingPoint = windowQueue.front() - (windowQueue.front() * 2) + 1;

		// If it's not the first person on the queue, then keep cycling until
		// it finally gets to the correct starting point.
		if(windowQueue.front() != 1)
		{
			while(windowPreference.front() != windowStartingPoint)
			{
				windowPreference.enqueue(windowPreference.front());
				windowPreference.dequeue();
			}

			// Get rid of the -1, -2, ...  to the back.
			windowPreference.enqueue(windowPreference.front());
			windowPreference.dequeue();
		}

		int aislewindowStartingPoint = windowPreference.front() - (windowPreference.front() * 2) + 1;

		it = find(assignedA.begin(), assignedA.end(), windowPreference.front());

		// If A hasn't been assigned, then match W with A, and take W out of the queue
		// Then, revert the the window preference back to where it first started
		if(it == assignedA.end())
		{
			seatingArrangment.insert({windowQueue.front(), windowPreference.front()});
			assignedA.push_back(windowPreference.front());
			windowQueue.dequeue();
			windowPreference.dequeue();

			while(windowPreference.front() != k)
			{
				windowPreference.enqueue(windowPreference.front());
				windowPreference.dequeue();
			}
			windowPreference.enqueue(windowPreference.front());
			windowPreference.dequeue();
		}

		else
		{
			// Find the W that seats with A
			for(auto mapIt = seatingArrangment.begin(); mapIt != seatingArrangment.end(); mapIt++)
			{
				if(mapIt->second == windowPreference.front())
				{
					target = mapIt->first;
					break;
				}
			}

			// If it's not the first person on the queue, then keep cycling until
			// it finally gets to the correct starting point.
			if(windowPreference.front() != 1)
			{
				while(aislePreference.front() != aislewindowStartingPoint)
				{
					aislePreference.enqueue(aislePreference.front());
					aislePreference.dequeue();
				}

				aislePreference.enqueue(aislePreference.front());
				aislePreference.dequeue();
			}

			// Search through the A's preference list
			while(aislePreference.front() != target && aislePreference.front() != windowQueue.front())
			{
				aislePreference.enqueue(aislePreference.front());
				aislePreference.dequeue();
			}

			// If A prefers with his/her buddy
			if(aislePreference.front() == target)
			{
				windowQueue.enqueue(windowQueue.front());
				windowQueue.dequeue();
				windowPreference.dequeue();
			}

			// If A perfers with W, Pair A with W and remove W from the queue.
			// Put the pervious A seat partner back to the queue.
			if(aislePreference.front() == windowQueue.front())
			{
				assignedA.erase(std::remove(assignedA.begin(), assignedA.end(), target), assignedA.end());
				assignedA.push_back(windowPreference.front());
				seatingArrangment.erase(target);
				seatingArrangment.insert({windowQueue.front(), windowPreference.front()});
				windowQueue.dequeue();
				windowPreference.dequeue();
				windowQueue.enqueue(target);
			}

			// Revert the Aisle Preference Queue back to where it started
			while(aislePreference.front() != l)
			{
				aislePreference.enqueue(aislePreference.front());
				aislePreference.dequeue();
			}

			aislePreference.enqueue(aislePreference.front());
			aislePreference.dequeue();


			// Revert the Window Preference Queue back to where it started
			while(windowPreference.front() != k)
			{
				windowPreference.enqueue(windowPreference.front());
				windowPreference.dequeue();
			}

			windowPreference.enqueue(windowPreference.front());
			windowPreference.dequeue();
		}
	}

	return seatingArrangment;
}
