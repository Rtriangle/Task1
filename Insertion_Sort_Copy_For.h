/*
template <class T>
void Insertion_Sort_Copy_For(T Iter_begin, T Iter_end)
{
	T Iter_move;
	if(Iter_begin != Iter_end)
		Iter_move = Iter_begin + 1;
	T Iter_value;
	T Iter_fix;
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
*/