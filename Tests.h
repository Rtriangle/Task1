struct X
{
	std::string key;
	int value;
};

/*
struct comparator
{
	bool operator()(const X &a, const X &b) const
	{
		return a.key < b.key;
	}
};
*/

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(-1024,1024);
std::uniform_real_distribution<> dist1(-1024.0,1024.0);

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
void RunTest(SortType OneOfSorts, Container &container1, Container &container2, double &SortTime, bool &CorrectSort, Comparator comparator)
{
	auto start = std::chrono::steady_clock::now();
	OneOfSorts(container1);
	auto end = std::chrono::steady_clock::now();
	SortTime = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 0.000001);
	CorrectSort = ScanResult(container1.begin(), container1.end(),container2.begin(),container2.end(), comparator);
}

template <typename SortType, typename Container>
void RunTest(SortType OneOfSorts, Container &container1, Container &container2, double &SortTime, bool &CorrectSort)
{
//	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	std::less<typename Container::value_type> cmp;
	RunTest(OneOfSorts, container1, container2, SortTime, CorrectSort, cmp);
}

void RunAllTests()
{

//	Vector int
//  0,1,2,3 Elements
	std::cout << "Vector <int>\n\n";
	std::cout << std::setw(10) << "n" << std::setw(18) << "InsertionFor" << std::setw(18) << "InsertionCopy" << std::setw(18) << "Selection" 
			  << std::setw(18) << "MergeIteration" << std::setw(18) << "Quick" << std::setw(18) << "Heap" << std::setw(18) << "stable_sort";
{
	std::vector<int> VectorOrigin; 
	std::vector<int> VectorSort;
	std::vector<int> VectorCheck;
	double SortTime = 0, stable_sortTime = 0;
	bool CorrectSort;
	auto TestInsCpyFor = [](std::vector<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
	auto TestInsCpyBack = [](std::vector<int> &v){Insertion_Sort_Copy_Backward(v.begin(), v.end());};
	auto TestHeap = [](std::vector<int> &v){Heap_Sort(v.begin(), v.end());};
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
		auto start = std::chrono::steady_clock::now();
		std::sort(VectorCheck.begin(),VectorCheck.end());
		auto end = std::chrono::steady_clock::now();
		RunTest<decltype (TestInsCpyFor), std::vector<int>> (TestInsCpyFor, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest<decltype (TestInsCpyBack), std::vector<int>> (TestInsCpyBack, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest<decltype (TestSelect), std::vector<int>> (TestSelect, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest<decltype (TestHeap), std::vector<int>> (TestHeap, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect";
		VectorSort = VectorOrigin;
		RunTest<decltype (TestMergeIter), std::vector<int>> (TestMergeIter, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest<decltype (TestQuick), std::vector<int>> (TestQuick, VectorSort, VectorCheck, SortTime, CorrectSort);
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
		auto start = std::chrono::steady_clock::now();
		std::sort(VectorCheck.begin(),VectorCheck.end());
		auto end = std::chrono::steady_clock::now();
		if(i <= 1000)
		{
		RunTest<decltype (TestInsCpyFor), std::vector<int>> (TestInsCpyFor, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestInsCpyBack), std::vector<int>> (TestInsCpyBack, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestSelect), std::vector<int>> (TestSelect, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		RunTest<decltype (TestHeap), std::vector<int>> (TestHeap, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest<decltype (TestMergeIter), std::vector<int>> (TestMergeIter, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest<decltype (TestQuick), std::vector<int>> (TestQuick, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
	}
}

//	Vector double
//  0,1,2,3 Elements
	std::cout << "\n\nVector <double>\n\n";
	std::cout << std::setw(10) << "n" << std::setw(18) << "InsertionFor" << std::setw(18) << "InsertionCopy" << std::setw(18) << "Selection" 
			  << std::setw(18) << "MergeIteration" << std::setw(18) << "Quick" << std::setw(18) << "Heap" << std::setw(18) << "stable_sort";
{
	std::vector<double> VectorOrigin; 
	std::vector<double> VectorSort;
	std::vector<double> VectorCheck;
	double SortTime = 0, stable_sortTime = 0;
	bool CorrectSort;
	auto TestInsCpyFor = [](std::vector<double> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
	auto TestInsCpyBack = [](std::vector<double> &v){Insertion_Sort_Copy_Backward(v.begin(), v.end());};
	auto TestHeap = [](std::vector<double> &v){Heap_Sort(v.begin(), v.end());};
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
		auto start = std::chrono::steady_clock::now();
		std::sort(VectorCheck.begin(),VectorCheck.end());
		auto end = std::chrono::steady_clock::now();
		RunTest<decltype (TestInsCpyFor), std::vector<double>> (TestInsCpyFor, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestInsCpyBack), std::vector<double>> (TestInsCpyBack, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestSelect), std::vector<double>> (TestSelect, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect";
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestHeap), std::vector<double>> (TestHeap, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestMergeIter), std::vector<double>> (TestMergeIter, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestQuick), std::vector<double>> (TestQuick, VectorSort, VectorCheck, SortTime, CorrectSort);
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
		auto start = std::chrono::steady_clock::now();
		std::sort(VectorCheck.begin(),VectorCheck.end());
		auto end = std::chrono::steady_clock::now();
		double SortTime = 0;
		bool CorrectSort;
		if(i <= 1000)
		{
		RunTest<decltype (TestInsCpyFor), std::vector<double>> (TestInsCpyFor, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestInsCpyBack), std::vector<double>> (TestInsCpyBack, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestSelect), std::vector<double>> (TestSelect, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		RunTest<decltype (TestHeap), std::vector<double>> (TestHeap, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		RunTest<decltype (TestMergeIter), std::vector<double>> (TestMergeIter, VectorSort, VectorCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest<decltype (TestQuick), std::vector<double>> (TestQuick, VectorSort, VectorCheck, SortTime, CorrectSort);
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
			  << std::setw(18) << "MergeIteration" << std::setw(18) << "Quick" << std::setw(18) << "Heap" << std::setw(18) << "stable_sort";
{
	std::deque<int> DequeOrigin; 
	std::deque<int> DequeSort;
	std::deque<int> DequeCheck;
	double SortTime = 0, stable_sortTime = 0;
	bool CorrectSort;
	auto TestInsCpyFor = [](std::deque<int> &v){Insertion_Sort_Copy_For(v.begin(), v.end());};
	auto TestInsCpyBack = [](std::deque<int> &v){Insertion_Sort_Copy_Backward(v.begin(), v.end());};
	auto TestHeap = [](std::deque<int> &v){Heap_Sort(v.begin(), v.end());};
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
		auto start = std::chrono::steady_clock::now();
		std::sort(DequeCheck.begin(),DequeCheck.end());
		auto end = std::chrono::steady_clock::now();
		RunTest<decltype (TestInsCpyFor), std::deque<int>> (TestInsCpyFor, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		RunTest<decltype (TestInsCpyBack), std::deque<int>> (TestInsCpyBack, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		RunTest<decltype (TestSelect), std::deque<int>> (TestSelect, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect";
		DequeSort = DequeOrigin;
		RunTest<decltype (TestHeap), std::deque<int>> (TestHeap, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		RunTest<decltype (TestMergeIter), std::deque<int>> (TestMergeIter, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		RunTest<decltype (TestQuick), std::deque<int>> (TestQuick, DequeSort, DequeCheck, SortTime, CorrectSort);
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
			DequeOrigin.push_back(dist(gen));
		DequeSort = DequeOrigin;
		DequeCheck = DequeOrigin;
		auto start = std::chrono::steady_clock::now();
		std::sort(DequeCheck.begin(),DequeCheck.end());
		auto end = std::chrono::steady_clock::now();
		double SortTime = 0;
		bool CorrectSort;
		if(i <= 1000)
		{
		RunTest<decltype (TestInsCpyFor), std::deque<int>> (TestInsCpyFor, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		DequeSort = DequeOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestInsCpyBack), std::deque<int>> (TestInsCpyBack, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		DequeSort = DequeOrigin;
		if(i <= 1000)
		{
		RunTest<decltype (TestSelect), std::deque<int>> (TestSelect, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		DequeSort = DequeOrigin;
		RunTest<decltype (TestHeap), std::deque<int>> (TestHeap, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		RunTest<decltype (TestMergeIter), std::deque<int>> (TestMergeIter, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		DequeSort = DequeOrigin;
		RunTest<decltype (TestQuick), std::deque<int>> (TestQuick, DequeSort, DequeCheck, SortTime, CorrectSort);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
	}
}

//	Vector X
//  0,1,2,3 Elements
	std::cout << "\n\nVector <X>\n\n";
	std::cout << std::setw(10) << "n" << std::setw(18) << "InsertionFor" << std::setw(18) << "InsertionCopy" << std::setw(18) << "Selection" 
			  << std::setw(18) << "MergeIteration" << std::setw(18) << "Quick" << std::setw(18) << "Heap" << std::setw(18) << "stable_sort";
{
	std::vector<X> VectorOrigin; 
	std::vector<X> VectorSort;
	std::vector<X> VectorCheck;
	double SortTime = 0, stable_sortTime = 0;
	bool CorrectSort;
	auto ComparatorX = [](const X &left, const X &right)->bool{return left.key < right.key; };
	auto TestInsCpyFor = [&](std::vector<X> &v){Insertion_Sort_Copy_For(v.begin(), v.end(), ComparatorX );};
	auto TestInsCpyBack = [&](std::vector<X> &v){Insertion_Sort_Copy_Backward(v.begin(), v.end(), ComparatorX );};
	auto TestHeap = [&](std::vector<X> &v){Heap_Sort(v.begin(), v.end(), ComparatorX );};
	auto TestMergeIter = [&](std::vector<X> &v){Merge_Sort(v.begin(), v.end(), ComparatorX );};
	auto TestQuick = [&](std::vector<X> &v){Quick_Sort(v.begin(), v.end(), ComparatorX );};
	auto TestSelect = [&](std::vector<X> &v){Selection_Sort(v.begin(), v.end(), ComparatorX );};
	for(long long i = 0; i <= 3; ++i)
	{
		std::cout << '\n' << std::setw(10) << i;
		VectorOrigin.reserve(i);
		VectorSort.reserve(i);
		VectorCheck.reserve(i);
		auto start = std::chrono::steady_clock::now();
		std::sort(VectorCheck.begin(),VectorCheck.end(), ComparatorX);
		auto end = std::chrono::steady_clock::now();
		//!
		std::string s = "";
		for(size_t j = 0; j <= i; ++j)
		{
			std::uniform_int_distribution<> StringGenerate(97,122);
			std::string sX = "";
			sX += char(StringGenerate(gen));
			int keyX = dist(gen);
			X Tmp;
			Tmp.value = keyX;
			Tmp.key = sX;
			VectorOrigin.push_back(Tmp);
		}
		VectorSort = VectorOrigin;
		RunTest (TestInsCpyFor, VectorSort, VectorCheck, SortTime, CorrectSort, ComparatorX);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest (TestInsCpyBack, VectorSort, VectorCheck, SortTime, CorrectSort, ComparatorX);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest (TestSelect, VectorSort, VectorCheck, SortTime, CorrectSort, ComparatorX);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest (TestHeap, VectorSort, VectorCheck, SortTime, CorrectSort, ComparatorX);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect";
		VectorSort = VectorOrigin;
		RunTest (TestMergeIter, VectorSort, VectorCheck, SortTime, CorrectSort, ComparatorX);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest (TestQuick, VectorSort, VectorCheck, SortTime, CorrectSort, ComparatorX);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
	}
//	Vector X
//	10,100,1000,10000,100000,1000000,10000000
	for(long long i = 10; i <= 1000; i = i*10)
	{
		std::cout << '\n' << std::setw(10) << i;
		VectorOrigin.reserve(i);
		VectorSort.reserve(i);
		VectorCheck.reserve(i);
		//!
		std::string s = "";
		for(size_t j = 0; j <= i; ++j)
		{
			std::uniform_int_distribution<> StringGenerate(97,122);
			std::string sX = "";
			sX += char(StringGenerate(gen));
			int keyX = dist(gen);
			X Tmp;
			Tmp.value = keyX;
			Tmp.key = sX;
			VectorOrigin.push_back(Tmp);
		}
		VectorSort = VectorOrigin;
		VectorCheck = VectorOrigin;
		auto start = std::chrono::steady_clock::now();
		std::sort(VectorCheck.begin(),VectorCheck.end(), ComparatorX);
		auto end = std::chrono::steady_clock::now();
		if(i <= 1000)
		{
		RunTest (TestInsCpyFor, VectorSort, VectorCheck, SortTime, CorrectSort, ComparatorX);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		if(i <= 1000)
		{
		RunTest (TestInsCpyBack, VectorSort, VectorCheck, SortTime, CorrectSort, ComparatorX);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		if(i <= 1000)
		{
		RunTest (TestSelect, VectorSort, VectorCheck, SortTime, CorrectSort, ComparatorX);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		}
		else
			std::cout << std::setw(18) << '-';
		VectorSort = VectorOrigin;
		RunTest (TestHeap, VectorSort, VectorCheck, SortTime, CorrectSort, ComparatorX);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest (TestMergeIter, VectorSort, VectorCheck, SortTime, CorrectSort, ComparatorX);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
		RunTest (TestQuick, VectorSort, VectorCheck, SortTime, CorrectSort, ComparatorX);
		if(CorrectSort)
			std::cout << std::setw(18) << SortTime;
		else
			std::cout << std::setw(18) << "Incorrect"; 
		VectorSort = VectorOrigin;
	}
}
}