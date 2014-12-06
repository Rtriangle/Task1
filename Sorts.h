// Heap Sort
template <typename Iterator, typename Comparator>
void Heap_Sort(Iterator Iter_begin, Iterator Iter_end, Comparator comparator)
{
	std::make_heap(Iter_begin,Iter_end);
	auto Itmoveend = Iter_end;
	for(int i = 0; i < Iter_end-Iter_begin; i++)
		std::pop_heap(Iter_begin, Itmoveend--);
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
	Iterator Iter_move;
	if(Iter_begin != Iter_end)
		Iter_move = Iter_begin + 1;
	Iterator Iter_value;
	bool Doit = true;
	auto Tmp = *(Iter_begin);
	while(Iter_move != Iter_end)
	{
		Iter_value = Iter_move;
		Doit = true;
		while(Iter_value > Iter_begin && Doit)
		{
			if(!comparator(*Iter_move,*(Iter_value-1)))
				Doit = false;
			else
				Iter_value--;
		}
		Tmp = *(Iter_move);
		if(Iter_value != Iter_move)
		{
			std::copy_backward(Iter_value, Iter_move, Iter_move+1);
			*(Iter_value) = Tmp;
		}
		Iter_move++;
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
	Iterator Iter_move;
	if(Iter_begin != Iter_end)
		Iter_move = Iter_begin + 1;
	Iterator Iter_value;
	Iterator Iter_fix;
	bool Doit = true;
	auto Tmp = *(Iter_begin);
	while(Iter_move != Iter_end)
	{
		Iter_value = Iter_move;
		Doit = true;
		while(Iter_value > Iter_begin && Doit)
		{
			if(!comparator(*Iter_move, *(Iter_value-1)))
				Doit = false;
			else
				Iter_value--;
		}
		Tmp = *(Iter_move);
		if(Iter_value != Iter_move)
		{
			for(Iterator ittmp = Iter_move; ittmp > Iter_value; ittmp--)
				std::iter_swap(ittmp,(ittmp-1));
			*(Iter_value) = Tmp;
		}
		Iter_move++;
	}
}

template <typename Iterator>
void Insertion_Sort_Copy_For(Iterator Iter_begin, Iterator Iter_end)
{
	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	Insertion_Sort_Copy_For(Iter_begin, Iter_end, cmp);
}


//Merge Sort
template <typename Iterator, typename Comparator>
void MergeSubarrays(Iterator Left1, Iterator Right1, Iterator Left2, Iterator Right2, Iterator buffer, Comparator comparator)
{
	Iterator IterFirstPart = Left1;
	Iterator IterSecondPart = Left2;
	while((IterFirstPart <= Right1) || (IterSecondPart <= Right2))
	{
		if(Right1 < IterFirstPart)
			while(IterSecondPart <= Right2)
			{
				*buffer = *IterSecondPart;
				++buffer;
				++IterSecondPart;
			}
		else
			if(Right2 < IterSecondPart)
				while(IterFirstPart <= Right1)
				{
					*buffer = *IterFirstPart;
					++buffer;
					++IterFirstPart;
				}
			else
				if(comparator(*(IterFirstPart), *(IterSecondPart)))
				{
					*buffer = *(IterFirstPart);
					++buffer;
					++IterFirstPart;
				}
				else
				{
					*buffer = *(IterSecondPart);
					++buffer;
					++IterSecondPart;
				}
	}
}

template <typename Iterator> 
void MergeSubarrays(Iterator Left1, Iterator Right1, Iterator Left2, Iterator Right2, Iterator buffer)
{
	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	MergeSubarrays(Left1, Right1, Left2, Right2, buffer, cmp);
}

template <typename Iterator, typename IteratorBuffer, typename Comparator> 
void Merge(Iterator Iter_begin, Iterator Iter_end, IteratorBuffer buffer, Comparator comparator)
{
	if((Iter_end - Iter_begin) == 0)
		return;
	if((Iter_end - Iter_begin) == 1)
	{
		if(comparator(*Iter_end, *Iter_begin))
			std::iter_swap(Iter_begin,Iter_end);
		return;
	}
	Iterator IterMiddle = Iter_begin + (Iter_end - Iter_begin)/2;
	Iterator IterMiddle1 = IterMiddle + 1;
	Merge(Iter_begin, IterMiddle, buffer, comparator);
	Merge(IterMiddle1, Iter_end, buffer, comparator);
	MergeSubarrays(Iter_begin, IterMiddle, IterMiddle1, Iter_end, buffer);
	std::copy(buffer,buffer+(Iter_end-Iter_begin)+1,Iter_begin);
}

template <typename Iterator, typename IteratorBuffer, typename Comparator>
void Merge_Sort_Recurse(Iterator Iter_begin, Iterator Iter_end, Comparator comparator)
{
	std::vector <typename std::iterator_traits<IteratorBuffer>::value_type> buffer(Iter_end - Iter_begin);
	Iter_end--;
	IteratorBuffer It buffer.begin();
	Merge(Iter_begin, Iter_end, It, comparator);
}

template <typename Iterator>
void  Merge_Sort_Recurse(Iterator Iter_begin, Iterator Iter_end)
{
	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	Merge_Sort_Recurse(Iter_begin, Iter_end, cmp);
}

//Merge Sort Iteration
template <typename FSourceIterator, typename SSourceIterator,
typename TargetIterator, typename Comparator>
 
TargetIterator MergeI(FSourceIterator first_begin, FSourceIterator first_end,
                     SSourceIterator second_begin, SSourceIterator second_end,
                     TargetIterator target, Comparator comparator) 
{
    while (first_begin != first_end &&
           second_begin != second_end) {
        if(comparator(*first_begin, *second_begin)) {
            *target = *first_begin;
            ++target;
            ++first_begin;
        }
        else {
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
void Quick_Sort(Iterator Iter_begin, Iterator Iter_end, Comparator comparator)
{
	if((Iter_begin - Iter_end) < 25)
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
				Left++;
			while(comparator(PartElement, *Right))
				Right--;
			if(Left <= Right)
			{
				std::iter_swap(Left,Right);
				Left++;
				Right--;
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
	for(int i = 1; i < (Iter_end-Iter_begin); i++)
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
		it++;
	}
}

template<typename Iterator>
void Selection_Sort(Iterator Iter_begin, Iterator Iter_end)
{
	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	Selection_Sort(Iter_begin, Iter_end, cmp);
}
