#include <map>
#include <string>
#include <iostream>
#include <cmath>
#include "proj0.hpp"

unsigned string1 = 0;
unsigned string2 = 0;
unsigned string3 = 0;
unsigned expo = 0;

bool verifySolution(std::string s1, std::string s2, std::string s3, const std::map<char, unsigned> & mapping)
{
    while(expo < s1.size())
    {
        string1 += mapping.at(s1[s1.size() - 1 - expo]) * (pow(10,expo));
        expo++;
    }

    expo = 0;

    while(expo < s2.size())
    {
        string2 += mapping.at(s2[s2.size()- 1 - expo]) * (pow(10,expo));
        expo++;
    }

    expo = 0;

    while(expo < s3.size())
    {
        string3 += mapping.at(s3[s3.size()- 1 - expo]) * (pow(10,expo));
        expo++;
    }

    expo = 0;

    return string1 + string2 == string3;
}
