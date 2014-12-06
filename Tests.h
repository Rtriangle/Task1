template <typename Iterator> 
bool ScanResult(Iterator Left1, Iterator Right1, Iterator Left2, Iterator Right2)
{
	bool doit = true;
	std::vector <bool> WasInResult((Right1-Left1),false);
	for(auto It1 = Left2; It1 != Right2 && doit; It1++)
	{
		doit = true;
		for(auto It2 = Left1; It2 != Right1 && doit; It2++)
			if(*It2 == *It1)
			{
				WasInResult[It2-Left1] = true;
				doit = false;
			}
		doit = !doit;
	}
	return doit;
}

template <typename SortType, typename Iterator, typename Container> 
void RunTest(SortType OneOfSorts, Container container1, Container container2, double &SortTime, bool &CorrectSort)
{
	auto start = std::chrono::steady_clock::now();
	OneOfSorts(container1);
	auto end = std::chrono::steady_clock::now();
	SortTime = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 0.000001);
	std::sort(container2.begin(),container2.end());
	CorrectSort = ScanResult(container1.begin(), container1.end(),container2.begin(),container2.end());
}

template <typename Comparator>
void RunAllTests(Comparator comparator)
{

//	Vector int
//  0,1,2,3 Elements
	std::cout << "Vector <int>\n\n";
	std::cout << std::setw(10) << "n" << std::setw(18) << "InsertionFor" << std::setw(18) << "InsertionCopy" << std::setw(18) << "Selection" 
			  << std::setw(18) << "Merge" << std::setw(18) << "MergeIteration" << std::setw(18) << "Quick" << std::setw(18) << "Heap";
{
	std::vector<int> VectorOrigin; 
	std::vector<int> VectorSort;
	std::vector<int> VectorCheck;
	double SortTime = 0;
	bool CorrectSort;
	auto TestInsCpyFor = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
	auto TestInsCpyBack = [](std::vector<int> &v){Insertion_Sort_Copy_Backward(v.begin(), v.end());};
	auto TestHeap = [](std::vector<int> &v){Heap_Sort(v.begin(), v.end());};
	auto TestMerge = [](std::vector<int> &v){Merge_Sort_Recurse(v.begin(), v.end());};
	auto TestMergeIter = [](std::vector<int> &v){Merge_Sort(v.begin(), v.end());};
	auto TestQuick = [](std::vector<int> &v){Quick_Sort(v.begin(), v.end());};
	auto TestSelect = [](std::vector<int> &v){Selection_Sort(v.begin(), v.end());};
	for(long long i = 0; i <= 3; ++i)
	{
		std::cout << '\n' << std::setw(10) << i;
		VectorOrigin.reserve(i);
		VectorSort.reserve(i);
		VectorCheck.reserve(i);
		for(size_t j = 0; j <= i; ++j)
			VectorOrigin.push_back(dist(gen));
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestInsCpyFor), decltype (VectorSort.begin())> (TestInsCpyFor, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestInsCpyBack), decltype (VectorSort.begin())> (TestInsCpyBack, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestSelect), decltype (VectorSort.begin())> (TestSelect, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestHeap), decltype (VectorSort.begin())> (TestHeap, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect";
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestMerge), decltype (VectorSort.begin())> (TestMerge, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestMergeIter), decltype (VectorSort.begin())> (TestMergeIter, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestQuick), decltype (VectorSort.begin())> (TestQuick, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
	}
//	Vector int
//	10,100,1000,10000,100000,1000000,10000000
	for(long long i = 10; i <= 1000; i = i*10)
	{
		std::cout << '\n' << std::setw(10) << i;
		VectorOrigin.reserve(i);
		VectorSort.reserve(i);
		VectorCheck.reserve(i);
		for(long long j = 0; j <= i; j++)
			VectorOrigin.push_back(dist(gen));
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestInsCpyFor), decltype (VectorSort.begin())> (TestInsCpyFor, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestInsCpyBack), decltype (VectorSort.begin())> (TestInsCpyBack, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestSelect), decltype (VectorSort.begin())> (TestSelect, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestHeap), decltype (VectorSort.begin())> (TestHeap, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestMerge), decltype (VectorSort.begin())> (TestMerge, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestMergeIter), decltype (VectorSort.begin())> (TestMergeIter, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestQuick), decltype (VectorSort.begin())> (TestQuick, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
	}
}

//	Vector double
//  0,1,2,3 Elements
	std::cout << "\n\nVector <double>\n\n";
	std::cout << std::setw(10) << "n" << std::setw(18) << "InsertionFor" << std::setw(18) << "InsertionCopy" << std::setw(18) << "Selection" 
			  << std::setw(18) << "Merge" << std::setw(18) << "MergeIteration" << std::setw(18) << "Quick" << std::setw(18) << "Heap";
{
	std::vector<double> VectorOrigin; 
	std::vector<double> VectorSort;
	std::vector<double> VectorCheck;
	double SortTime = 0;
	bool CorrectSort;
	auto TestInsCpyFor = [](std::vector<double> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
	auto TestInsCpyBack = [](std::vector<double> &v){Insertion_Sort_Copy_Backward(v.begin(), v.end());};
	auto TestHeap = [](std::vector<double> &v){Heap_Sort(v.begin(), v.end());};
	auto TestMerge = [](std::vector<double> &v){Merge_Sort_Recurse(v.begin(), v.end());};
	auto TestMergeIter = [](std::vector<double> &v){Merge_Sort(v.begin(), v.end());};
	auto TestQuick = [](std::vector<double> &v){Quick_Sort(v.begin(), v.end());};
	auto TestSelect = [](std::vector<double> &v){Selection_Sort(v.begin(), v.end());};
	for(long long i = 0; i <= 3; ++i)
	{
		std::cout << '\n' << std::setw(10) << i;
		VectorOrigin.reserve(i);
		VectorSort.reserve(i);
		VectorCheck.reserve(i);
		for(long long j = 0; j <= i; ++j)
			VectorOrigin.push_back(dist1(gen));
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestInsCpyFor), decltype (VectorSort.begin())> (TestInsCpyFor, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestInsCpyBack), decltype (VectorSort.begin())> (TestInsCpyBack, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestSelect), decltype (VectorSort.begin())> (TestSelect, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect";
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestHeap), decltype (VectorSort.begin())> (TestHeap, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestMerge), decltype (VectorSort.begin())> (TestMerge, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestMergeIter), decltype (VectorSort.begin())> (TestMergeIter, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestQuick), decltype (VectorSort.begin())> (TestQuick, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
	}

//	Vector double
//	10,100,1000,10000,100000,1000000,10000000
	for(long long i = 10; i <= 1000; i = i*10)
	{
		std::cout << '\n' << std::setw(10) << i;
		VectorOrigin.reserve(i);
		VectorSort.reserve(i);
		VectorCheck.reserve(i);
		for(long long j = 0; j <= i; j++)
			VectorOrigin.push_back(dist1(gen));
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		double SortTime = 0;
		bool CorrectSort;
		if(i <= 1000)
		{
		RunTest<decltype (TestInsCpyFor), decltype (VectorSort.begin())> (TestInsCpyFor, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestInsCpyBack), decltype (VectorSort.begin())> (TestInsCpyBack, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestSelect), decltype (VectorSort.begin())> (TestSelect, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestHeap), decltype (VectorSort.begin())> (TestHeap, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestMerge), decltype (VectorSort.begin())> (TestMerge, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect";
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestMergeIter), decltype (VectorSort.begin())> (TestMergeIter, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestQuick), decltype (VectorSort.begin())> (TestQuick, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
	}
}

//	Deque int
//  0,1,2,3 Elements
	std::cout << "\n\nDeque <int>\n\n";
	std::cout << std::setw(10) << "n" << std::setw(18) << "InsertionFor" << std::setw(18) << "InsertionCopy" << std::setw(18) << "Selection" 
			  << std::setw(18) << "Merge" << std::setw(18) << "MergeIteration" << std::setw(18) << "Quick" << std::setw(18) << "Heap";
{
	std::deque<int> DequeOrigin; 
	std::deque<int> DequeSort;
	std::deque<int> DequeCheck;
	double SortTime = 0;
	bool CorrectSort;
	auto TestInsCpyFor = [](std::deque<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
	auto TestInsCpyBack = [](std::deque<int> &v){Insertion_Sort_Copy_Backward(v.begin(), v.end());};
	auto TestHeap = [](std::deque<int> &v){Heap_Sort(v.begin(), v.end());};
	auto TestMerge = [](std::deque<int> &v){Merge_Sort_Recurse(v.begin(), v.end());};
	auto TestMergeIter = [](std::deque<int> &v){Merge_Sort(v.begin(), v.end());};
	auto TestQuick = [](std::deque<int> &v){Quick_Sort(v.begin(), v.end());};
	auto TestSelect = [](std::deque<int> &v){Selection_Sort(v.begin(), v.end());};
	for(long long i = 0; i <= 3; ++i)
	{
		std::cout << '\n' << std::setw(10) << i;
		for(long long j = 0; j <= i; ++j)
			DequeOrigin.push_back(dist1(gen));
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		RunTest<decltype (TestInsCpyFor), decltype (DequeSort.begin())> (TestInsCpyFor, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		RunTest<decltype (TestInsCpyBack), decltype (DequeSort.begin())> (TestInsCpyBack, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		RunTest<decltype (TestSelect), decltype (DequeSort.begin())> (TestSelect, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect";
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		RunTest<decltype (TestHeap), decltype (DequeSort.begin())> (TestHeap, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		RunTest<decltype (TestMerge), decltype (DequeSort.begin())> (TestMerge, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		RunTest<decltype (TestMergeIter), decltype (DequeSort.begin())> (TestMergeIter, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		RunTest<decltype (TestQuick), decltype (DequeSort.begin())> (TestQuick, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
	}

//	Deque int
//	10,100,1000,10000,100000,1000000,10000000
	for(long long i = 10; i <= 1000; i = i*10)
	{
		std::cout << '\n' << std::setw(10) << i;
		for(long long j = 0; j <= i; ++j)
			DequeOrigin.push_back(dist1(gen));
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		double SortTime = 0;
		bool CorrectSort;
		if(i <= 1000)
		{
		RunTest<decltype (TestInsCpyFor), decltype (DequeSort.begin())> (TestInsCpyFor, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestInsCpyBack), decltype (DequeSort.begin())> (TestInsCpyBack, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestSelect), decltype (DequeSort.begin())> (TestSelect, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		RunTest<decltype (TestHeap), decltype (DequeSort.begin())> (TestHeap, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		RunTest<decltype (TestMerge), decltype (DequeSort.begin())> (TestMerge, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect";
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		RunTest<decltype (TestMergeIter), decltype (DequeSort.begin())> (TestMergeIter, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		RunTest<decltype (TestQuick), decltype (DequeSort.begin())> (TestQuick, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
	}
}

}


