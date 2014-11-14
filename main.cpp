#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <random>
#include <iterator>
#include <array>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1,50);

std::vector <int> V;

template <class Iterator>
void Quick_Sort(Iterator Iter_begin, Iterator Iter_end)
{
	std::uniform_int_distribution<> dist(0,size_t(Iter_end-Iter_begin)-1);
	auto PartElement = *(Iter_begin + dist(gen));
	Iterator Left = Iter_begin;
	Iterator Right = Iter_end-1;
	while(Left < Right)
	{
		while(*Left < PartElement)
			Left++;
		while(PartElement < *Right)
			Right--;
		if((Left < Right) || !((Left < Right) || (Right < Left)))
		{
			std::iter_swap(Left,Right);
			Left++;
			Right--;
		}
	}
	if(Left < Iter_end-1)
		Quick_Sort(Left, Iter_end);
	if(Iter_begin < Right)
		Quick_Sort(Iter_begin, Right+1);
}

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
	Quick_Sort(it1,it2);
	for(auto it = V.begin(); it != V.end(); it++)
		std::cout << *it << " ";
	std::cout << '\n' << it1 - it2 << '\n';
	system("pause");
	return 0;
}
