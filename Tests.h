#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <random>
#include <iterator>
#include <chrono>
#include <ctime>
#include <deque>
#include <typeinfo>
#include <algorithm>
#include <cmath>
#include "Sorts.h"
#pragma once
const size_t N = 1000;

struct X
{
	std::string key;
	int value;
};

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(-5,5);
std::uniform_real_distribution<> dist1(-1024.0,1024.0);
std::vector <std::vector <double> > TimesSortsVectorInt(10, std::vector <double>(7, -1));
std::vector <std::vector <double> > TimesSortsVectorDouble(10, std::vector <double>(7, -1));
std::vector <std::vector <double> > TimesSortsDequeInt(10, std::vector <double>(7, -1));
std::vector <std::vector <double> > TimesSortsVectorX(10, std::vector <double>(7, -1));
auto ComparatorX = [](const X &left, const X &right)->bool{return left.key < right.key;};
std::vector <int> SortVectorInt;
std::vector <double> SortVectorDouble;
std::vector <X> SortVectorX;
std::deque <int> SortDequeInt;

template <typename Iterator, typename Comparator> 
bool ScanResult(Iterator Left1, Iterator Right1, Iterator Left2, Iterator Right2, Comparator comparator)
{
	bool doit = true;
	std::vector <bool> WasInResult((Right1-Left1),false);
	for(auto It1 = Left2; It1 != Right2 && doit; It1++)
	{
		doit = true;
		for(auto It2 = Left1; It2 != Right1 && doit; It2++)
			if(!comparator(*It2, *It1) && !comparator(*It2, *It1))
			{
				WasInResult[It2-Left1] = true;
				doit = false;
			}
		doit = !doit;
	}
	return doit;
}

template <typename SortType, typename Container, typename Comparator> 
void RunTest(SortType OneOfSorts, Container &ContainerForMySort, Container &ContainerForStdSort, double &SortTime, bool &CorrectSort, Comparator comparator)
{
	auto start = std::chrono::steady_clock::now();
	OneOfSorts(ContainerForMySort);
	auto end = std::chrono::steady_clock::now();
	SortTime = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 0.000001);
	CorrectSort = ScanResult(ContainerForMySort.begin(), ContainerForMySort.end(), ContainerForStdSort.begin(), ContainerForStdSort.end(), comparator);
}

template <typename SortType, typename Container>
void RunTest(SortType OneOfSorts, Container &container1, Container &container2, double &SortTime, bool &CorrectSort)
{
	std::less<typename Container::value_type> cmp;
	RunTest(OneOfSorts, container1, container2, SortTime, CorrectSort, cmp);
}

void GenerateContainers(size_t Size)
{
	SortVectorInt.clear();
	SortVectorDouble.clear();
	SortVectorX.clear();
	SortDequeInt.clear();
	for(size_t i = 0; i < Size; ++i)
	{
		SortVectorInt.push_back(dist(gen));
		SortVectorDouble.push_back(dist1(gen));
		SortDequeInt.push_back(dist(gen));
		std::string S = "";
		std::uniform_int_distribution<> StringDist(97,122);
		for(size_t j = 0; j < 5; ++j)
			S += char(StringDist(gen));
		X TmpPair;
		TmpPair.key = S;
		TmpPair.value = dist(gen);
		SortVectorX.push_back(TmpPair);
	}
}

template <typename Container, typename ContainerWriteTime> 
void CreatingLambdaFunctions(Container &SortContainer, ContainerWriteTime &TimeContainer, size_t Raw)
{
	auto TestInsCpyFor = [&](Container &OurContainer){Insertion_Sort_Copy_For(OurContainer.begin(), OurContainer.end());};
	auto TestInsCpyBack = [&](Container &OurContainer){Insertion_Sort_Copy_Backward(OurContainer.begin(), OurContainer.end());};
	auto TestHeap = [&](Container &OurContainer){Heap_Sort(OurContainer.begin(), OurContainer.end());};
	auto TestMergeIter = [&](Container &OurContainer){Merge_Sort(OurContainer.begin(), OurContainer.end());};
	auto TestQuick = [&](Container &OurContainer){Quick_Sort(OurContainer.begin(), OurContainer.end());};
	auto TestSelect = [&](Container &OurContainer){Selection_Sort(OurContainer.begin(), OurContainer.end());};
	TestAllSortsForSize(SortContainer, TimeContainer, Raw, TestInsCpyFor, TestInsCpyBack, TestHeap, TestMergeIter, TestQuick, TestSelect);
}

template <typename ContainerWriteTime> 
void CreatingLambdaFunctions(std::vector <X> v, ContainerWriteTime &TimeContainer, size_t Raw)
{
	auto ComparatorX = [](const X &left, const X &right)->bool{return left.key < right.key; };
	auto TestInsCpyFor = [&](std::vector<X> &v){Insertion_Sort_Copy_For(v.begin(), v.end(), ComparatorX );};
	auto TestInsCpyBack = [&](std::vector<X> &v){Insertion_Sort_Copy_Backward(v.begin(), v.end(), ComparatorX );};
	auto TestHeap = [&](std::vector<X> &v){Heap_Sort(v.begin(), v.end(), ComparatorX );};
	auto TestMergeIter = [&](std::vector<X> &v){Merge_Sort(v.begin(), v.end(), ComparatorX );};
	auto TestQuick = [&](std::vector<X> &v){Quick_Sort(v.begin(), v.end(), ComparatorX );};
	auto TestSelect = [&](std::vector<X> &v){Selection_Sort(v.begin(), v.end(), ComparatorX );};
	TestAllSortsForSize(v, TimeContainer, Raw, TestInsCpyFor, TestInsCpyBack, TestHeap, TestMergeIter, TestQuick, TestSelect, ComparatorX);
}

template <typename Container, typename ContainerWriteTime, typename Lambda1, typename Lambda2, typename Lambda3, typename Lambda4, 
		  typename Lambda5, typename Lambda6, typename Comparator>
void TestAllSortsForSize(Container &SortContainer, ContainerWriteTime &TimeContainer, size_t Raw, 
Lambda1 TestInsCpyFor, Lambda2 TestInsCpyBack, Lambda3 TestHeap, Lambda4 TestMergeIter, Lambda5 TestQuick, Lambda6 TestSelect, Comparator cmp)
{
	bool CorrectSort;
	double SortTime;
	Container ContainerOrigin = SortContainer;
	Container ContainerSort = ContainerOrigin;
	Container CheckContainer = ContainerOrigin;
	auto start = std::chrono::steady_clock::now();
	std::stable_sort(CheckContainer.begin(), CheckContainer.end(), cmp);
	auto end = std::chrono::steady_clock::now();
	double StableSortTime = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 0.000001);
	TimeContainer[Raw][6] = StableSortTime;

	RunTest<decltype (TestInsCpyFor), Container> (TestInsCpyFor, ContainerSort, CheckContainer, SortTime, CorrectSort);
	if(CorrectSort)
		TimeContainer[Raw][0] = SortTime;
	else
		TimeContainer[Raw][0] = -1;
	ContainerSort = ContainerOrigin;

	RunTest<decltype (TestInsCpyBack), Container> (TestInsCpyBack, ContainerSort, CheckContainer, SortTime, CorrectSort);
	if(CorrectSort)
		TimeContainer[Raw][1] = SortTime;
	else
		TimeContainer[Raw][1] = -1;
	ContainerSort = ContainerOrigin;

	RunTest<decltype (TestSelect), Container> (TestSelect, ContainerSort, CheckContainer, SortTime, CorrectSort);
	if(CorrectSort)
		TimeContainer[Raw][2] = SortTime;
	else
		TimeContainer[Raw][2] = -1;
	ContainerSort = ContainerOrigin;

	RunTest<decltype (TestHeap), Container> (TestHeap, ContainerSort, CheckContainer, SortTime, CorrectSort);
	if(CorrectSort)
		TimeContainer[Raw][3] = SortTime;
	else
		TimeContainer[Raw][3] = -1;
	ContainerSort = ContainerOrigin;

	RunTest<decltype (TestMergeIter), Container> (TestMergeIter, ContainerSort, CheckContainer, SortTime, CorrectSort);
	if(CorrectSort)
		TimeContainer[Raw][4] = SortTime;
	else
		TimeContainer[Raw][4] = -1;
	ContainerSort = ContainerOrigin;

	RunTest<decltype (TestQuick), Container> (TestQuick, ContainerSort, CheckContainer, SortTime, CorrectSort);
	if(CorrectSort)
		TimeContainer[Raw][5] = SortTime;
	else
		TimeContainer[Raw][5] = -1;
}

template <typename Container, typename ContainerWriteTime, typename Lambda1, typename Lambda2, typename Lambda3, typename Lambda4, 
		  typename Lambda5, typename Lambda6>
void TestAllSortsForSize(Container &SortContainer, ContainerWriteTime &TimeContainer, size_t Raw, 
Lambda1 TestInsCpyFor, Lambda2 TestInsCpyBack, Lambda3 TestHeap, Lambda4 TestMergeIter, Lambda5 TestQuick, Lambda6 TestSelect)
{
	std::less<typename Container::value_type> cmp;
	TestAllSortsForSize(SortContainer, TimeContainer, Raw, TestInsCpyFor, TestInsCpyBack, 
						TestHeap, TestMergeIter, TestQuick, TestSelect, cmp);
}

void PrintAllTimes()
{
	//Done
	std::cout << "vector <int>\n\n";
	std::cout << std::setw(10) << "n" << std::setw(18) << "InsertionFor" << std::setw(18) << "InsertionCopy" << std::setw(18) << "Selection" 
			  << std::setw(18) << "Heap" << std::setw(18) << "MergeIteration" << std::setw(18) << "Quick" << std::setw(18) << "stable_sort";
	for(size_t i = 0; i <= log10(static_cast<size_t>(N)); ++i)
	{
		std::cout << std::setw(18) << pow(10,log10(static_cast<size_t>(N)));
		for(size_t j = 0; j <= 6; ++j)
			std::cout << std::setw(18) << TimesSortsVectorInt[i][j];
		std::cout << '\n';
	}
	//Done
	std::cout << "\n\nvector <double>\n\n";
	std::cout << std::setw(10) << "n" << std::setw(18) << "InsertionFor" << std::setw(18) << "InsertionCopy" << std::setw(18) << "Selection" 
			  << std::setw(18) << "Heap" << std::setw(18) << "MergeIteration" << std::setw(18) << "Quick" << std::setw(18) << "stable_sort";
	for(size_t i = 0; i <= log10(static_cast<size_t>(N)); ++i)
	{
		std::cout << std::setw(18) << pow(10,log10(static_cast<size_t>(N)));
		for(size_t j = 0; j <= 6; ++j)
			std::cout << std::setw(18) << TimesSortsVectorDouble[i][j];
		std::cout << '\n';
	}
	//Done
	std::cout << "\n\ndeque <int>\n\n";
	std::cout << std::setw(10) << "n" << std::setw(18) << "InsertionFor" << std::setw(18) << "InsertionCopy" << std::setw(18) << "Selection" 
			  << std::setw(18) << "Heap" << std::setw(18) << "MergeIteration" << std::setw(18) << "Quick" << std::setw(18) << "stable_sort";
	for(size_t i = 0; i <= log10(static_cast<size_t>(N)); ++i)
	{
		std::cout << std::setw(18) << pow(10,log10(static_cast<size_t>(N)));
		for(size_t j = 0; j <= 6; ++j)
			std::cout << std::setw(18) << TimesSortsDequeInt[i][j];
		std::cout << '\n';
	}
	//Done
	std::cout << "\n\nvector <X>\n\n";
	std::cout << std::setw(10) << "n" << std::setw(18) << "InsertionFor" << std::setw(18) << "InsertionCopy" << std::setw(18) << "Selection" 
			  << std::setw(18) << "Heap" << std::setw(18) << "MergeIteration" << std::setw(18) << "Quick" << std::setw(18) << "stable_sort";
	for(size_t i = 0; i <= log10(static_cast<size_t>(N)); ++i)
	{
		std::cout << std::setw(18) << pow(10,log10(static_cast<size_t>(N)));
		for(size_t j = 0; j <= 6; ++j)
			std::cout << std::setw(18) << TimesSortsVectorX[i][j];
		std::cout << '\n';
	}
}

void RunAllTests()
{
	for(size_t sizeofcontainer = 1; sizeofcontainer <= N; sizeofcontainer = sizeofcontainer * 10)
	{
		GenerateContainers(sizeofcontainer);
		CreatingLambdaFunctions(SortVectorInt,TimesSortsVectorInt, log10(sizeofcontainer));
		CreatingLambdaFunctions(SortVectorDouble,TimesSortsVectorDouble, log10(sizeofcontainer));
		CreatingLambdaFunctions(SortVectorX,TimesSortsVectorX, log10(sizeofcontainer)); //Error
		CreatingLambdaFunctions(SortDequeInt,TimesSortsDequeInt, log10(sizeofcontainer));
	}
	PrintAllTimes();
}