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
#include <deque>
#include <typeinfo>
#include <algorithm>
#include "i-sort.h"
#include "gtest/gtest.h"
#include "Sorts.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1,256);

struct X
{
	std::string key;
	int value;
};

struct comparator
{
	bool operator()(const X &a, const X &b) const
	{
		return a.key < b.key;
	}
};

std::vector <X> VX;
std::vector <int> V;
std::deque <int> D1;
std::deque <X> DX;

int main(int argc,char** argv)
{
	std::ios_base::sync_with_stdio(false);
	::testing::InitGoogleTest(&argc,argv);
	
    RUN_ALL_TESTS();
	system("pause");
	std::getchar();
}
