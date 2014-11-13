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
void Insertion_Sort_Copy_Backward(T Iter_begin, T Iter_end)
{
	T Iter_move;
	if(Iter_begin != Iter_end)
		Iter_move = Iter_begin + 1;
	T Iter_value;
	T Iter_fix;
	bool Doit = true;
	auto Tmp = *(Iter_begin);
	while(Iter_move != Iter_end)
	{
		Iter_value = Iter_move;
		Doit = true;
		while(Iter_value > Iter_begin && Doit)
		{
			if(!(*Iter_move < *(Iter_value-1)))
				Doit = false;
			else
				Iter_value--;
		}
		Tmp = *(Iter_move);
		if(Iter_value != Iter_move)
		{

			std::copy_backward(Iter_value, Iter_move, Iter_value+1);
			*(Iter_value) = Tmp;
		}
		Iter_move++;
	}
}


int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1,50);
	for(int i = 0; i < 5; i++)
		V.push_back(dist(gen));
	for(auto it = V.begin(); it != V.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
	auto it1 = V.begin();
	auto it2 = V.end();
	Insertion_Sort_Copy_Backward(it1,it2);
	for(auto it = V.begin(); it != V.end(); it++)
		std::cout << *it << " ";
	system("pause");
	return 0;
}