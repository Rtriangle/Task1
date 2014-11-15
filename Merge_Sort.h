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
