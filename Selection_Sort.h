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