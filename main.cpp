#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <random>
#include <iterator>
#include <array>
#include <ctime>
#include <typeinfo>
#include <algorithm>
#include "gtest/gtest.h"
#include "Selection_Sort.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1,50);

std::vector <int> V;



TEST(TestCase, Test1) 
{
	for(int i = 0; i < 10; i++)
		V.push_back(dist(gen));
	std::vector <int> V1;
	std::vector <int> V2;
	V1 = V;
	V2 = V;
	sort(V1.begin(),V1.end());
	Selection_Sort(V2.begin(),V2.end());
	EXPECT_EQ(V1, V2);
	EXPECT_TRUE(2 + 2 == 4);
}

template <typename Iterator, typename Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>

int main(int argc,char** argv)
{
	::testing::InitGoogleTest(&argc,argv);
    RUN_ALL_TESTS();
	std::getchar();
}
