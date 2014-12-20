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
#pragma once

template <typename Iterator, typename Comparator>
void Heap_Sort(Iterator Iter_begin, Iterator Iter_end, Comparator comparator)
{
	if(Iter_end - Iter_begin == 0) 
		return;
	std::make_heap(Iter_begin,Iter_end, comparator);
	for(Iterator i = Iter_end; i != Iter_begin; --i)
		std::pop_heap(Iter_begin, i, comparator);
}

template <typename Iterator>
void Heap_Sort(Iterator Iter_begin, Iterator Iter_end)
{
	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	Heap_Sort(Iter_begin, Iter_end, cmp);
}

//Insertion Sort with std::copy_backward
template <typename Iterator, typename Comparator>
void Insertion_Sort_Copy_Backward(Iterator Iter_begin, Iterator Iter_end, Comparator comparator)
{
	if(Iter_begin == Iter_end)
		return;
	for(auto Iter_move = Iter_begin+1; Iter_move != Iter_end; ++Iter_move)
	{
		Iterator Iter_value = Iter_move;
		while(Iter_value > Iter_begin)
		{
			if(!comparator(*Iter_move,*(Iter_value-1)))
				break; // Changed last
			else
				--Iter_value;
		}
		if(Iter_value != Iter_move)
		{
			auto Tmp = *(Iter_move);
			std::copy_backward(Iter_value, Iter_move, Iter_move+1);
			*(Iter_value) = Tmp;
		}
	}
}

template <typename Iterator>
void Insertion_Sort_Copy_Backward(Iterator Iter_begin, Iterator Iter_end)
{
	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	Insertion_Sort_Copy_Backward(Iter_begin, Iter_end, cmp);
}

//Insertion Sort with For
template <typename Iterator, typename Comparator>
void Insertion_Sort_Copy_For(Iterator Iter_begin, Iterator Iter_end, Comparator comparator)
{
	if(Iter_begin == Iter_end)
		return;
	for(auto Iter_move = Iter_begin+1; Iter_move != Iter_end; ++Iter_move)
	{
		Iterator Iter_value = Iter_move;
		while(Iter_value > Iter_begin)
		{
			if(!comparator(*Iter_move, *(Iter_value-1)))
				break;
			else
				--Iter_value;
		}
		if(Iter_value != Iter_move)
		{
			auto Tmp = *(Iter_move);
			for(Iterator ittmp = Iter_move; ittmp > Iter_value; --ittmp)
				std::iter_swap(ittmp,(ittmp-1));
			*(Iter_value) = Tmp;
		}
	}
}

template <typename Iterator>
void Insertion_Sort_Copy_For(Iterator Iter_begin, Iterator Iter_end)
{
	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	Insertion_Sort_Copy_For(Iter_begin, Iter_end, cmp);
}

//Merge Sort Iteration
template <typename FSourceIterator, typename SSourceIterator,
typename TargetIterator, typename Comparator>
 
TargetIterator MergeI(FSourceIterator first_begin, FSourceIterator first_end,
                     SSourceIterator second_begin, SSourceIterator second_end,
                     TargetIterator target, Comparator comparator) 
{
    while (first_begin != first_end && second_begin != second_end) 
	{
        if(comparator(*first_begin, *second_begin)) 
		{
            *target = *first_begin;
            ++target;
            ++first_begin;
        }
        else 
		{
            *target = *second_begin;
            ++target;
            ++second_begin;
        }
    }
    target = std::copy(first_begin, first_end, target);
    target = std::copy(second_begin, second_end, target);
    return target;
}
 
template <typename Iterator, typename OutputIterator, typename Comparator>

void MergeSubarraysI(Iterator begin, Iterator end, OutputIterator target, ptrdiff_t chunk_size, Comparator comparator) 
{
        for(Iterator first_begin = begin;
            first_begin < end;
            first_begin += std::min<size_t>(2 * chunk_size, end - first_begin)) 
		{
            Iterator second_begin = first_begin + std::min<size_t>(chunk_size, end - first_begin);
            Iterator second_end = second_begin + std::min<size_t>(chunk_size, end - second_begin);
            target = MergeI(first_begin, second_begin, second_begin, second_end, target, comparator);
        }
}
 
template <typename Iterator, typename Comparator>
 
void Merge_Sort(Iterator begin, Iterator end, Comparator comparator) 
{
    std::vector<typename std::iterator_traits<Iterator>::value_type> buffer(end - begin);
    ptrdiff_t chunk_size = 1;
    while (chunk_size < end - begin) 
	{
        MergeSubarraysI(begin, end, buffer.begin(), chunk_size, comparator);
        chunk_size *= 2;
        if(chunk_size < end - begin)
            MergeSubarraysI(buffer.begin(), buffer.end(), begin, chunk_size, comparator);
        else
            std::copy(buffer.begin(), buffer.end(), begin);
        chunk_size *= 2;
    }
}

template <typename Iterator>
void Merge_Sort(Iterator begin, Iterator end)
{
	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	Merge_Sort(begin, end, cmp);
}


//Quick Sort
template <typename Iterator, typename Comparator>
void Quick_Sort(Iterator Iter_begin, Iterator Iter_end, const Comparator &comparator)
{
	if(Iter_end-Iter_begin <= 1)
		return;
	if((Iter_end - Iter_begin) < 25)
		Insertion_Sort_Copy_Backward(Iter_begin, Iter_end, comparator);
	else
	{
		std::uniform_int_distribution<> dist(0, size_t(Iter_end - Iter_begin) - 1);
		long long Move = dist(gen);
		typename std::iterator_traits<Iterator>::value_type PartElement = *(Iter_begin + Move);
		Iterator Left = Iter_begin;
		Iterator Right = Iter_end-1;
		while(Left < Right)
		{
			while(comparator(*Left, PartElement))
				++Left;
			while(comparator(PartElement, *Right))
				--Right;
			if(Left <= Right)
			{
				std::iter_swap(Left,Right);
				++Left;
				--Right;
			}
		}
		if(Left < Iter_end-1)
			Quick_Sort(Left, Iter_end, comparator);
		if(Iter_begin < Right)
			Quick_Sort(Iter_begin, Right+1, comparator);
	}
}

template <typename Iterator>
void Quick_Sort(Iterator Iter_begin, Iterator Iter_end)
{
	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	Quick_Sort(Iter_begin, Iter_end, cmp);
}


//Selection Sort
template<typename Iterator, typename Comparator>
void Selection_Sort(Iterator Iter_begin, Iterator Iter_end, Comparator comparator)
{
	Iterator it = Iter_begin;
	Iterator it_move = it;
	Iterator it_min = it;
	for(int i = 1; i < (Iter_end-Iter_begin); ++i)
	{
		it_move = it;
		it_min = it;
		while(it_move != Iter_end)
		{
			if(comparator(*it_move,*it_min))
				it_min = it_move;
			it_move++;
		}
		iter_swap(it,it_min);
		++it;
	}
}

template<typename Iterator>
void Selection_Sort(Iterator Iter_begin, Iterator Iter_end)
{
	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	Selection_Sort(Iter_begin, Iter_end, cmp);
}