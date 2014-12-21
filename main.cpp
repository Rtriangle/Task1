#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <random>
#include <iterator>
#include <array>
#include <chrono>
#include <ctime>
#include <deque>
#include <typeinfo>
#include <algorithm>
#include "Sorts.h"
#include "Tests.h"
#pragma warning(disable : 4996)

int main()
{
	std::ios_base::sync_with_stdio(false);
	freopen("output.txt","w",stdout);
	RunAllTests();
	fclose(stdout);
}