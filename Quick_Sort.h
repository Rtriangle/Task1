template <typename Iterator, typename Comparator>
void Quick_Sort(Iterator Iter_begin, Iterator Iter_end, Comparator comparator)
{
	if((Iter_begin - Iter_end) < 25)
		Insertion_Sort_Copy_Backward(Iter_begin, Iter_end, comparator);
	else
	{
		std::uniform_int_distribution<> dist(0, size_t(Iter_end - Iter_begin) - 1);
		typename std::iterator_traits<Iterator>::value_type PartElement = *(Iter_begin + dist(gen));
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