#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <random>
#include <iterator>
#include <array>

std::vector <int> V;

template <class T>
void Heap_Sort(T Iter_begin, T Iter_end)
{
	std::make_heap(Iter_begin,Iter_end);
	auto Itmoveend = Iter_end;
	for(int i = 0; i < Iter_end-Iter_begin; i++)
		std::pop_heap(Iter_begin, Itmoveend--);
}

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1,50);
	for(int i = 0; i < 8; i++)
		V.push_back(dist(gen));
	for(auto it = V.begin(); it != V.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
	auto it1 = V.begin();
	auto it2 = V.end();
	std::make_heap(V.begin(),V.end());
	Heap_Sort(it1,it2);
	for(auto it = V.begin(); it != V.end(); it++)
		std::cout << *it << " ";
	system("pause");
	return 0;
}