#include "proj4.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>

// Insert all words in the txt to the Hash Table.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{

			//std::cout << word << std::endl;
			words.insert( word );
		}
	}
}


// Convoerting a word to another using the shortest path.
std::string convert(std::string s1, std::string s2, const WordSet & words)
{
	std::queue <std::string> qu;
	std::map <std::string, std::string> mapping;
	std::vector <char> alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	std::string tmp = s1;
	std::string before = " ";
	std::string after;
	std::stack <std::string> result;
	std::string convert = s1 + " --> ";
	std::map<std::string, std::string>::iterator itr;

	// enqueue the initial word to the queue.
	qu.push(s1);

	// While queue is not empty, if there is a word in the dictonary that is only
	// 1 letter away from the word in the top of queue, then map it.
	while(!qu.empty())
	{

		// If the queue contains the word s2, then backtrack the path using map
		// to get the word before s2. Then backtrack that word to get the previous
		// word, so on and so fort until it reaches s1.
		if(qu.front() == s2)
		{
			itr = mapping.find(s2);

			while(true)
			{
				if(itr->second == s1)
					break;
				result.push(itr->second);
				itr = mapping.find(itr->second);
			}

			while(!result.empty())
			{
				convert += result.top() + " --> ";
				result.pop();
			}

			convert += s2;
			//std::cout << convert;
			return convert;
		}
		else
		{

			// Start by enqueue, if the queue is not empty, then set the temporary
			// string to the queue front. Then, find any word in the dictionary that
			// is one letter away from the queue front. If there is such word,
			// then map using the key = the new word, and value = the pervious word
			// Should there be a double key, map will only keep the first key and not
			// the second one. This cause the map to only keep the shortest path from
			// a word to another.
			qu.pop();

			if(!qu.empty())
				before = qu.front();

			for(int s1Length = 0; s1Length < s1.size(); s1Length++)
			{
				if(!qu.empty())
					tmp = before;
				else
					before = s1;

				for(int letter = 0; letter < 26; letter++)
				{
					tmp[s1Length] = alphabet[letter];
					if(words.contains(tmp))
					{
						itr = mapping.find(tmp);
						if(itr == mapping.end())
						{
							after = tmp;
							qu.push(after);
							mapping.insert({after, before});
						}
					}
				}
			}
		}
	}

	return "foo";  // stub obviously

}
