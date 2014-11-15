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

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1,50);

std::vector <int> V;

int main()
{
	V.push_back(2);
	V.push_back(5);
	V.push_back(1);
	V.push_back(3);
	V.push_back(4);
	for(auto it = V.begin(); it != V.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
	auto it1 = V.begin();
	auto it2 = V.end();
	for(auto it = V.begin(); it != V.end(); it++)
		std::cout << *it << " ";
	system("pause");
	return 0;
}
