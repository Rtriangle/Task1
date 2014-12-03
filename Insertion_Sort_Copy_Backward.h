template <typename Iterator, typename Comparator>
void Insertion_Sort_Copy_Backward(Iterator Iter_begin, Iterator Iter_end, Comparator = comparator)
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
			if(!(comparator(*Iter_move, *(Iter_value-1))))
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

template <typename Iterator>
void Insertion_Sort_Copy_Backward(Iterator Iter_begin, Iterator Iter_end)
{
	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	void Insertion_Sort_Copy_Backward(Iterator Iter_begin, Iterator Iter_end, cmp);
}