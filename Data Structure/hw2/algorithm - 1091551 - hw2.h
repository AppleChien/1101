// algorithm standard header

#ifndef ALGORITHM
#define ALGORITHM

namespace MyNamespace
{

	template< typename RanIt, typename Ty, typename Pr >
	inline void pushHeapByIndex(RanIt first, ptrdiff_t hole, ptrdiff_t top, Ty& val, Pr pred)
	{
		while (hole != top) {
			if (pred(first[(hole - 1) / 2], val)) {
				first[hole] = first[(hole - 1) / 2];
				hole = (hole - 1) / 2;
			}
			else
				break;
		}
		first[hole] = val;
	}

	// push *(last - 1) onto heap at [first, last - 1), using pred
	template< typename RanIt, typename Pr >
	inline void push_heap(RanIt first, RanIt last, Pr pred)
	{
		ptrdiff_t count = last - first;
		if (count >= 2)
		{
			--last;
			typename RanIt::value_type val = *last;
			--count;
			pushHeapByIndex(first, count, 0, val, pred);
		}
	}

	template< typename RanIt, typename Ty, typename Pr >
	inline void popHeapHoleByIndex(RanIt first, ptrdiff_t hole, ptrdiff_t bottom, Ty& val, Pr pred)
	{
		ptrdiff_t top = hole;
		while (hole * 2 + 1 < bottom) {
			if (hole * 2 + 2 >= bottom) {
				first[hole] = first[hole * 2 + 1];
				hole = hole * 2 + 1;
				break;
			}
			else {
				if (pred(first[hole * 2 + 2], first[hole * 2 + 1])) {
					first[hole] = first[hole * 2 + 1];
					hole = hole * 2 + 1;
				}
				else {
					first[hole] = first[hole * 2 + 2];
					hole = hole * 2 + 2;
				}
			}
		}

		pushHeapByIndex(first, hole, top, val, pred);
		/*ptrdiff_t top = hole;
		while (1) {
			if (hole * 2 + 1 >= bottom)
				break;
			else if (hole * 2 + 2 >= bottom) {
				first[hole] = first[hole * 2 + 1];
				hole = hole * 2 + 1;
				break;
			}
			else {
				if (pred(first[hole * 2 + 2], first[hole * 2 + 1])) {
					first[hole] = first[hole * 2 + 1];
					hole = hole * 2 + 1;
				}
				else {
					first[hole] = first[hole * 2 + 2];
					hole = hole * 2 + 2;
				}
			}
		}

	   pushHeapByIndex( first, hole, top, val, pred );*/

	}

	// pop *first to *(last - 1) and reheap, using pred
	template< typename RanIt, typename Pr >
	inline void pop_heap(RanIt first, RanIt last, Pr pred)
	{
		if (last - first >= 2)
		{
			--last;
			typename RanIt::value_type val = *last;

			// pop *first to *(last - 1) and reheap, using pred
			// precondition: first != last
			*last = *first;
			popHeapHoleByIndex(first, 0, last - first, val, pred);
		}
	}

	// make [first, last) into a heap, using pred
	template< typename RanIt, typename Pr >
	inline void make_heap(RanIt first, RanIt last, Pr pred)
	{
		ptrdiff_t bottom = last - first;
		ptrdiff_t hole = bottom / 2;
		while (hole > 0)
		{
			// reheap top half, bottom to top
			--hole;
			typename RanIt::value_type val = *(first + hole);
			popHeapHoleByIndex(first, hole, bottom, val, pred);
		}
	}
}

#endif // ALGORITHM