template<typename Iterator,
         typename Comparator=std::less<typename
             std::iterator_traits<Iterator>::value_type>>
void Sort(Iterator begin,
          Iterator end,
          Comparator comparator = Comparator());

template <typename Iterator> 
void Selection_Sort(Iterator Iter_begin, Iterator Iter_end)
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
			if(*it_move < *it_min)
				it_min = it_move;
			it_move++;
		}
		iter_swap(it,it_min);
		it++;
	}
}


template <class Iterator>
void Insertion_Sort_Copy_For(Iterator Iter_begin, Iterator Iter_end)
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
			if(!(*Iter_move < *(Iter_value-1)))
				Doit = false;
			else
				Iter_value--;
		}
		Tmp = *(Iter_move);
		if(Iter_value != Iter_move)
		{
			for(T ittmp = Iter_value; ittmp >= Iter_move; ittmp--)
				std::iter_swap(ittmp,(ittmp+1));
			*(Iter_value) = Tmp;
		}
		Iter_move++;
	}
}


template <class Iterator>
void Insertion_Sort_Copy_Backward(Iterator Iter_begin, Iterator Iter_end)
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


template <class Iterator>
void Insertion_Sort_Copy(Iterator Iter_begin, Iterator Iter_end)
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
			if(!(*Iter_move < *(Iter_value-1)))
				Doit = false;
			else
				Iter_value--;
		}
		Tmp = *(Iter_move);
		if(Iter_value != Iter_move)
		{
			std::copy(Iter_value, Iter_move, Iter_value+1);
			*(Iter_value) = Tmp;
		}
		Iter_move++;
	}
}


template <class T>
void Heap_Sort(T Iter_begin, T Iter_end)
{
	std::make_heap(Iter_begin,Iter_end);
	auto Itmoveend = Iter_end;
	for(int i = 0; i < Iter_end-Iter_begin; i++)
		std::pop_heap(Iter_begin, Itmoveend--);
}



template <class Iterator>
void Quick_Sort(Iterator Iter_begin, Iterator Iter_end)
{
	if((Iter_begin - Iter_end) < 25)
		Insertion_Sort(Iter_begin,Iter_end);
	else
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
}



template <typename FSourceIterator, typename SSourceIterator,
typename TargetIterator >
TargetIterator Merge(FSourceIterator first_begin, FSourceIterator first_end,
                     SSourceIterator second_begin, SSourceIterator second_end,
                     TargetIterator target) {
    while (first_begin != first_end &&
           second_begin != second_end) {
        if(*first_begin <= *second_begin) {
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
 
 
template <typename Iterator ,typename OutputIterator>
void MergeSubarrays(Iterator begin, Iterator end, OutputIterator target, ptrdiff_t chunk_size) {
        for(Iterator first_begin = begin;
            first_begin < end;
            first_begin += std::min<size_t>(2 * chunk_size, end - first_begin)) {
            Iterator second_begin = first_begin + std::min<size_t>(chunk_size, end - first_begin);
            Iterator second_end = second_begin + std::min<size_t>(chunk_size, end - second_begin);
            target = Merge(first_begin, second_begin, second_begin, second_end, target);
        }
    }
 
template <typename Iterator>
void MergeSort(Iterator begin, Iterator end) {
    std::vector<typename std::iterator_traits<Iterator>::value_type> buffer(end - begin);
    ptrdiff_t chunk_size = 1;
    while (chunk_size < end - begin) {
        MergeSubarrays(begin, end, buffer.begin(), chunk_size);
        chunk_size *= 2;
        if(chunk_size < end - begin)
            MergeSubarrays(buffer.begin(), buffer.end(), begin, chunk_size);
        else
            std::copy(buffer.begin(), buffer.end(), begin);
        chunk_size *= 2;
    }
}


template <class Iterator>
void MergeSort(Iterator Iter_begin, Iterator Iter_end)
{
	std::vector <typename std::iterator_traits<Iterator>::value_type> buffer(Iter_end - Iter_begin);
	Iterator BuffBegin = buffer.begin();
	Iterator ReallyEnd = Iter_end-1;
	Merge(Iter_begin, ReallyEnd, BuffBegin);
}

template <class Iterator> 
void Merge(Iterator Iter_begin, Iterator Iter_end, Iterator buffer)
{
	if((Iter_end - Iter_begin) == 0)
		return;
	if((Iter_end - Iter_begin) == 1)
	{
		if(*Iter_end < *Iter_begin)
			std::iter_swap(Iter_begin,Iter_end);
		return;
	}
	Iterator IterMiddle = Iter_begin + (Iter_end - Iter_begin)/2;
	Iterator IterMiddle1 = IterMiddle + 1;
	Merge(Iter_begin, IterMiddle, buffer);
	Merge(IterMiddle1, Iter_end, buffer);
	MergeSubarrays(Iter_begin, IterMiddle, IterMiddle1, Iter_end, buffer);
	std::copy(buffer,buffer+(Iter_end-Iter_begin)+1,Iter_begin);
}

template <class Iterator>
void MergeSubarrays(Iterator Left1, Iterator Right1, Iterator Left2, Iterator Right2, Iterator buffer)
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
				if(*(IterFirstPart) < *(IterSecondPart))
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
