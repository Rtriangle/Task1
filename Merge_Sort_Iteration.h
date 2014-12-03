template <typename FSourceIterator, typename SSourceIterator,
typename TargetIterator, typename Comparator>
 
TargetIterator Merge(FSourceIterator first_begin, FSourceIterator first_end,
                     SSourceIterator second_begin, SSourceIterator second_end,
                     TargetIterator target, Comparator comparator) {
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
 

template <typename FSourceIterator, typename SSourceIterator, typename TargetIterator>
TargetIterator Merge(FSourceIterator first_begin, FSourceIterator first_end,
                     SSourceIterator second_begin, SSourceIterator second_end,
                     TargetIterator target)
{
	std::less<typename std::iterator_traits<Iterator>::value_type> cmp;
	TargetIterator Merge(FSourceIterator first_begin, FSourceIterator first_end,
						 SSourceIterator second_begin, SSourceIterator second_end,
						 TargetIterator target, cmp);
}
 
template <typename Iterator, typename OutputIterator>

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