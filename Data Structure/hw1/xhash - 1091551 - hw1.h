// xhash internal header

#ifndef XHASH
#define XHASH

#include <list>
using std::list;

// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
	using value_type = ValueType;
	using pointer = value_type*;

	VectorVal()
		: myFirst(),
		myLast(),
		myEnd()
	{
	}

	pointer myFirst; // pointer to beginning of array
	pointer myLast;  // pointer to current end of sequence
	pointer myEnd;   // pointer to end of array
};

template< typename Iter >
struct HashVec
{
	using value_type = Iter;
	using size_type = size_t;

	HashVec()
		: myData()
	{
	}

	// set the elements stored here to cells copies of val
	void assignGrow(const size_type cells, const value_type val)
	{
		const size_type oldSize = static_cast<size_type>(myData.myLast - myData.myFirst);
		if (cells > oldSize) { //要擴大
			delete[] myData.myFirst;

			myData.myFirst = new value_type[cells]();
			myData.myEnd = myData.myLast = myData.myFirst + cells;

			for (auto it = myData.myFirst; it != myData.myEnd; it++)
				*it = val;
		}
		else { //不用擴大直接放
			myData.myEnd = myData.myLast = myData.myFirst + cells;

			for (auto it = myData.myFirst; it != myData.myEnd; it++)
				*it = val;
		}
	}

	~HashVec()
	{
		if (myData.myFirst != nullptr)
			delete[] myData.myFirst;
	}

	VectorVal< value_type > myData;
};

// CLASS TEMPLATE Hash
template< typename Traits >
class Hash // hash table -- list with vector of iterators for quick access
{
protected:
	using MyList = list< typename Traits::value_type >;
	using KeyCompare = typename Traits::key_compare;

public:
	using key_type = typename Traits::key_type;
	using value_type = typename MyList::value_type;
	using size_type = typename MyList::size_type;

	using iterator = typename MyList::const_iterator;
	using const_iterator = typename MyList::const_iterator;

	static const size_type MinBuckets = 8; // must be a positive power of 2

protected:
	Hash(const KeyCompare& parg) // construct empty hash table
		: traitsObj(parg),
		myList(),
		myVec(),
		mask(MinBuckets - 1),
		maxidx(MinBuckets)
	{
		myVec.assignGrow(MinBuckets * 2, myList.end());
	}

public:
	// Returns the number of elements in the unordered_set container.
	size_type size() const
	{
		return myList.size();
	}

	// Returns the number of buckets in the unordered_set container.
	size_type bucket_count() const
	{
		return maxidx;
	}

	// Returns the bucket number where the element with value keyVal is located.
	size_type bucket(const key_type& keyVal) const
	{
		return traitsObj(keyVal) & mask;
		//    return traitsObj.operator()( keyVal ) & mask;
		//    return traitsObj( keyVal ) % maxidx;
	}

	// Returns the number of elements in bucket n.
	size_type bucket_size(size_type n) const
	{
		auto it = myVec.myData.myFirst[n * 2];
		int count = 0;

		for (; it != myVec.myData.myFirst[n * 2 + 1]; it++)
			count++;

		if (it == myList.end())
			return 0;

		else
			return count + 1;

	}

	// Inserts a new element in the unordered_set.
	// The element is inserted only if it is not equivalent to any other element
	// already in the container ( elements in an unordered_set have unique values ).
	// This effectively increases the container size by one.
	void insert(const value_type& val)
	{
		if (find(val) != myList.end())
			return;

		if (myList.size() + 1 > maxidx) {
			if (maxidx == 8 || maxidx == 64)
				maxidx *= 8;
			else
				maxidx *= 2;
			mask = maxidx - 1;

			auto temp = myList;
			myList.clear();
			myVec.assignGrow(maxidx * 2, myList.end());
			for (iterator it = temp.begin(); it != temp.end(); it++)
				putIn(*it);
		}

		putIn(val);
	}

	// Removes from the unordered_set a single element.
	// This effectively reduces the container size by one.
	void erase(const key_type& keyVal)
	{
		auto place_front = &myVec.myData.myFirst[bucket(keyVal) * 2];
		auto place_back = place_front + 1;
		auto it = find(keyVal);
		if (it == myList.end())
			return;

		if (*place_front == *place_back)
			*place_front = *place_back = myList.end();
		else {
			if (*place_front == find(keyVal))
				(*place_front)++;
			else if (*place_back == find(keyVal))
				(*place_back)--;
		}

		myList.erase(it);
	}

	// Searches the unordered_set for an element with keyVal as value and
	// returns an iterator to it if found, otherwise it returns myList.end()
	iterator find(const key_type& keyVal)
	{
		for (iterator it = myList.begin(); it != myList.end(); it++) {
			if (*it == keyVal)
				return it;
		}

		return myList.end();
	}

private:
	// put a new element in the unordered_set when myVec is large enough
	void putIn(const value_type& val)
	{
		auto place_front = &myVec.myData.myFirst[bucket(val) * 2];
		auto place_back = place_front + 1;

		myList.insert(*place_front, val);
		if (*place_front == myList.end())
			(*place_back)--;
		(*place_front)--;
	}

protected:
	Traits traitsObj;          // traits to customize behavior
	MyList myList;             // list of elements, must initialize before myVec
	HashVec< iterator > myVec; // "vector" of list iterators for buckets:
							   // each bucket is 2 iterators denoting
							   // the closed range of elements in the bucket,
							   // or both iterators set to end() if the bucket is empty.
	size_type mask;            // the key mask, equals maxidx - 1
	size_type maxidx;          // current maximum key value, must be a power of 2
};

#endif // XHASH