#include "proj1.hpp"

bool puzzleSolver(std::string s1, std::string s2, std::string s3, std::map<char, unsigned> & mapping)
{
  // Keeping track of the mapped value
  std::vector<unsigned> mappedNum;

  // Carry number purposes
  unsigned carry = 0;
  unsigned carryFuture = 0;

  return findSolution(s1, s2, s3, mapping, mappedNum, carry, carryFuture);
}

//Recursive Function
bool findSolution(std::string s1, std::string s2, std::string s3, std::map<char, unsigned> & mapping, std::vector<unsigned> &mappedNum, unsigned carry, unsigned carryFuture)
{
  // Assigned value of each letter.
  // The only purpose of this is to check for carry.
  int value1 = 0;
  int value2 = 0;
  int value3 = 0;
  int sumOfs1s2 = 0;

  // Indicate that there exist the same pair of character and number.
  bool duplicate1 = false;
  bool duplicate2 = false;
  bool duplicate3 = false;

  // If Every characters has been mapped to a distinct numbers.
  if(s1.size() == 0 && s2.size() == 0 && s3.size() == 0)
    return true;

  // Going through all the possible permutation of the last letter of each strings.
  for(int num1 = 0; num1 < 10; num1++)
  {
    for(int num2 = 0; num2 < 10; num2++)
    {
      for(int num3 = 0; num3 < 10; num3++)
      {
        if(s1[s1.size() - 1] == (char)0)
          value1 = 0;
        else
          value1 = num1;

        if(s2[s2.size() - 1] == (char)0)
          value2 = 0;
        else
          value2= num2;

        if(s3[s3.size() - 1] == (char)0)
          value3 = 0;
        else
          value3 = num3;

        // Checks to see if this is the first letter of the third string.
        // Allow carrying ones if it's not the first letter of the third string
        // else, it does not allow carrying ones.
        if(s3.size() == 1)
          sumOfs1s2 = value1 + value2 + carry;
        else
          sumOfs1s2 = (value1 + value2 + carry) % 10;

        // Going through all possible permutations such that the assigned value
        // of thefirst string and second string is equal to the thrid string.
        if(sumOfs1s2 == value3)
        {
          // Only map when there isn't exist the same letter inside the mapping
          // and if the string is not a null string.
          // Cheecks for the first letter.
          if(mapping.count(s1[s1.size() - 1]))
            duplicate1 = true;
          if(isSafe(s1[s1.size() - 1], num1, mappedNum, mapping))
          {
            if(s1[s1.size() - 1] != (char)0)
            {
              mapping.insert({s1[s1.size() - 1], num1});
              mappedNum.push_back(num1);
            }

            //Checks for the second letter.
            if(mapping.count(s2[s2.size() - 1]))
              duplicate2 = true;
            if(isSafe(s2[s2.size() - 1], num2, mappedNum, mapping))
            {
              if(s2[s2.size() - 1] != (char)0)
              {
                mapping.insert({s2[s2.size() - 1], num2});
                mappedNum.push_back(num2);
              }

              // Checks for the third letter.
              if(mapping.count(s3[s3.size() - 1]))
                duplicate3 = true;
              if(isSafe(s3[s3.size() - 1], num3, mappedNum, mapping))
              {
                if(s3[s3.size() - 1] != (char)0)
                {
                  mapping.insert({s3[s3.size() - 1], num3});
                  mappedNum.push_back(num3);
                }

                // Determine there is a carry for the next letter.
                if(value1 + value2 + carry >= 10)
                  carryFuture = 1;
                else
                  carryFuture = 0;

                // Repeat for the next letters.
                if(findSolution(s1.substr(0, s1.size() - 1), s2.substr(0, s2.size() - 1), s3.substr(0, s3.size() - 1), mapping, mappedNum, carryFuture, 0))
                  return true;

                // Backtracking.
                if(s3[s3.size() - 1] != (char)0)
                {
                  if(duplicate3 == false)
                    mapping.erase(s3[s3.size() - 1]);
                  mappedNum.pop_back();
                }
              }

              // Backtracking.
              if(s2[s2.size() - 1] != (char)0)
              {
                if(duplicate2 == false)
                  mapping.erase(s2[s2.size() - 1]);
                mappedNum.pop_back();
              }
            }

            //Backtracking.
            if(s1[s1.size() - 1] != (char)0)
            {
              if(duplicate1 == false)
                mapping.erase(s1[s1.size() - 1]);
              mappedNum.pop_back();
            }
          }
        }
      }
    }
  }
  return false;
}

// Each letter must pass this test before mapped.
bool isSafe(char c, unsigned num, std::vector<unsigned> & mappedNum, std::map<char, unsigned> & mapping)
{
  // Defining iterator.
  typedef std::vector<unsigned> IntContainer;
  typedef IntContainer::iterator it;

  // Search the letter through the map. If it exist and have the same value,
  // then it passes the test.
  if(mapping.count(c))
  {
    if(mapping.find(c)->second == num)
      return true;

    return false;
  }

  it it1 = find(mappedNum.begin(), mappedNum.end(), num);

  // Making sure that there is no duplicate value.
  if(it1 != mappedNum.end() && c != (char) 0)
    return false;
  return true;
}
