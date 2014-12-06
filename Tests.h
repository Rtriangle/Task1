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
	std::vector<int> VectorOrigin; 
	std::vector<int> VectorSort;
	std::vector<int> VectorCheck;
	std::cout << std::setw(10) << "n" << std::setw(18) << "InsertionCopy" << std::setw(18) << "InsertionFor" << std::setw(18) << "Selection" 
			  << std::setw(18) << "Merge" << std::setw(18) << "MergeIteration" << std::setw(18) << "Quick" << std::setw(18) << "Heap";
//	Vector int
//  0,1,2,3 Element
	{
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
		double SortTime = 0;
		bool CorrectSort;
		auto TestInsCpyFor = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
		auto TestInsCpyBack = [](std::vector<int> &v){Insertion_Sort_Copy_Backward(v.begin(), v.end());};
		auto TestHeap = [](std::vector<int> &v){Heap_Sort(v.begin(), v.end());};
		auto TestMerge = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
		auto TestMergeIter = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
		auto TestQuick = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
		auto TestSelect = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
		RunTest<decltype (TestInsCpyFor), decltype (VectorSort.begin())> (TestInsCpyFor, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		RunTest<decltype (TestInsCpyBack), decltype (VectorSort.begin())> (TestInsCpyBack, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		RunTest<decltype (TestSelect), decltype (VectorSort.begin())> (TestSelect, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		RunTest<decltype (TestHeap), decltype (VectorSort.begin())> (TestHeap, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		RunTest<decltype (TestMerge), decltype (VectorSort.begin())> (TestMerge, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		RunTest<decltype (TestMergeIter), decltype (VectorSort.begin())> (TestMergeIter, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		RunTest<decltype (TestQuick), decltype (VectorSort.begin())> (TestQuick, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
	}
//	Vector int
//	10,100,1000,10000,100000,1000000,10000000
	for(long long i = 10; i <= 10000; i = i*10)
	{
		std::cout << '\n' << std::setw(10) << i;
		VectorOrigin.reserve(i);
		VectorSort.reserve(i);
		VectorCheck.reserve(i);
		for(size_t j = 0; j <= i; j++)
			VectorOrigin.push_back(dist(gen));
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		double SortTime = 0;
		bool CorrectSort;
		auto TestInsCpyFor = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
		auto TestInsCpyBack = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
		auto TestHeap = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
		auto TestMerge = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
		auto TestMergeIter = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
		auto TestQuick = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
		auto TestSelect = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
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
		RunTest<decltype (TestHeap), decltype (VectorSort.begin())> (TestHeap, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		RunTest<decltype (TestMerge), decltype (VectorSort.begin())> (TestMerge, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		RunTest<decltype (TestMergeIter), decltype (VectorSort.begin())> (TestMergeIter, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		RunTest<decltype (TestQuick), decltype (VectorSort.begin())> (TestQuick, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
	}
	}
}


