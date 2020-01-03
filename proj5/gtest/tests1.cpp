#include "gtest/gtest.h"
#include "proj5.hpp"
#include <string>
#include <fstream>

namespace{


// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.

TEST(HeapTests, Bedpost)
{
	EXPECT_TRUE(isMinHeap("bedpost"));
}

TEST(HeapTests, Pinhead)
{
	EXPECT_TRUE(! isMinHeap("pinhead")); // it's actually a max heap.
}



// test the sorting function.

TEST(Sorting, Sort1)
{
	std::vector<std::string> vec = {"bedpost", "adjusts", "adjourns", "despot"};
	doSomeSort(vec);

	std::vector<std::string> expected = {"adjourns", "adjusts", "bedpost", "despot"};

	EXPECT_TRUE( vec == expected );
}


// test the collection of heaps

TEST(Collection, SetOfHeaps)
{
	std::string someWords = "bedpost despot pinhead\nadjourns adjusts\n";

	std::istringstream stream( someWords );

	std::vector<std::string> vec = findHeaps(stream);


	std::vector<std::string> expected = {"adjourns", "adjusts", "bedpost", "despot"};

	EXPECT_TRUE( vec == expected );
}
}
