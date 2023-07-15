/* 
 * Array.h
 * 
 * This custom abstract array interface provides common functionality for array data structures.
 * 
 * For implementations of this interface, see StaticArray.h and DynamicArray.h.
 *   
 * DISCLAIMER: This implementation is intended for portfolio/education purposes only.
 * For production use, it is recommended to use std::array or std::vector instead.
 *   
 * © Copyright Peter Hoghton. All rights reserved.
 */

#pragma once

#include <concepts>
#include <limits>
#include <stdexcept>
#include <type_traits>

// Enum for specifying the sort order (ascending or descending)
enum class SortOrder
{
	Ascending,
	Descending
};

template<typename T>
class Array
{
public:
	// Default constructor
	Array() = default;

	// Default destructor
	virtual ~Array() = default;

	// Index operator
	T& operator[](const size_t index)
	{
		BoundsCheck(index);
		return Data()[index];
	}

	// Index operator (const version)
	const T& operator[](const size_t index) const
	{
		return const_cast<Array<T>*>(this)->operator[](index);
	}

	// Equality operator
	bool operator==(const Array& other) const
	{
		return Equals(other.Data(), other.Size());
	}

	// Equality operator with c-style array
	template <size_t M>
	bool operator==(const T(&other)[M]) const
	{
		return Equals(other, M);
	}

	// Inequality operator
	bool operator!=(const Array& other) const
	{
		return !(*this == other);
	}

	// Inequality operator with c-style array
	template <size_t M>
	bool operator!=(const T(&other)[M]) const
	{
		return !(*this == other);
	}

	// Range-based for loop support
	T* begin()
	{
		return Data();
	}

	T* end()
	{
		return Data() + Size();
	}

	const T* begin() const
	{
		return const_cast<Array<T>*>(this)->begin();
	}

	const T* end() const
	{
		return const_cast<Array<T>*>(this)->end();
	}

	// Returns true if the array contains the given value
	bool Contains(const T& value, const size_t from = 0, const size_t to = s_maxSize) const
	{
		return Find([&](const T& element) { return element == value; }, from, to);
	}

	// Deep copies the elements from the raw array
	// Note: Remaining elements are left uninitialized.
	virtual bool Copy(const T* data, const size_t size, const size_t offset = 0)
	{
		return CopyOrMove(data, size, Data(), Bounds(), offset);
	}

	// Returns the number of occurrences of the given value in the array
	size_t Count(const T& value, const size_t from = 0, const size_t to = s_maxSize) const
	{
		return Count([&](const T& element) { return element == value; }, from, to);
	}

	// Returns the number of occurrences of nullptr in the array
	size_t Count(std::nullptr_t, const size_t from = 0, const size_t to = s_maxSize) const
	{
		return Count([](const T& element) { return element == nullptr; }, from, to);
	}

	// Returns the number of elements in the array that satisfy the predicate
	template<typename Predicate>
	size_t Count(const Predicate& predicate, const size_t from = 0, const size_t to = s_maxSize) const
	{
		if (Size() == 0)
		{
			return 0;
		}

		const size_t size = (to == s_maxSize) ? Size() : to;
		BoundsCheck(size - 1);
		size_t count = 0;
		for (size_t i = from; i < size; ++i)
		{
			if (predicate(Data()[i]))
			{
				++count;
			}
		}
		return count;
	}

	// Returns a pointer to the first element of the array
	virtual T* Data() = 0;

	// Returns a pointer to the first element of the array (const version)
	virtual const T* Data() const = 0;

	// Deletes all elements in the array
	// Note: Non-pointer elements will automatically be removed instead.
	bool DeleteAll()
	{
		bool dirty = false;
		if constexpr (std::is_pointer_v<T>)
		{
			for (T& element : *this)
			{
				delete element;
				element = nullptr;
			}
			dirty = Size() > 0;
		}
		return RemoveAll() || dirty;
	}

	// Equality comparison with raw array
	bool Equals(const T* data, const size_t size) const
	{
		return Equals(Data(), Size(), data, size);
	}

	// Fills the array with the given value
	// Note: Remaining elements are left uninitialized.
	virtual bool Fill(const T& value = T{}, const size_t from = 0, const size_t to = s_maxSize)
	{
		if (Bounds() == 0)
		{
			return false;
		}

		const size_t size = (to == s_maxSize) ? Bounds() : to;
		BoundsCheck(size - 1);
		for (size_t i = from; i < size; ++i)
		{
			Data()[i] = value;
		}
		return (size - from) > 0;
	}

	// Returns a pointer to the first element in the array that satisfies the predicate, or nullptr if not found
	template<typename Predicate>
	const T* Find(const Predicate& predicate, const size_t from = 0, const size_t to = s_maxSize) const
	{
		if (Size() == 0)
		{
			return nullptr;
		}

		const size_t size = (to == s_maxSize) ? Size() : to;
		BoundsCheck(size - 1);
		for (size_t i = from; i < size; ++i)
		{
			if (predicate(Data()[i]))
			{
				return &Data()[i];
			}
		}
		return nullptr;
	}

	// Returns the index of the first occurrence of the given value in the array, or the array size if not found
	size_t IndexOf(const T& value, const size_t from = 0, const size_t to = s_maxSize) const
	{
		return IndexOf([&](const T& element) { return element == value; }, from, to);
	}

	// Returns the index of the first occurrence of nullptr in the array, or the array size if not found
	size_t IndexOf(std::nullptr_t, const size_t from = 0, const size_t to = s_maxSize) const
	{
		return IndexOf([](const T& element) { return element == nullptr; }, from, to);
	}

	// Returns the index of the first element in the array that satisfies the predicate, or the array size if not found
	template<typename Predicate>
	size_t IndexOf(const Predicate& predicate, const size_t from = 0, const size_t to = s_maxSize) const
	{
		if (Size() == 0)
		{
			return Size();
		}

		const size_t size = (to == s_maxSize) ? Size() : to;
		BoundsCheck(size - 1);
		for (size_t i = from; i < size; ++i)
		{
			if (predicate(Data()[i]))
			{
				return i;
			}
		}
		return Size();
	}

	// Moves the elements from the raw array
	// Note: Remaining elements are left uninitialized.
	virtual bool Move(T* data, const size_t size, const size_t offset = 0)
	{
		return CopyOrMove(data, size, Data(), Bounds(), offset, true);
	}

	// Removes all elements from the array
	virtual bool RemoveAll() = 0;

	// Replaces all occurrences of the old value in the array with the new value
	bool Replace(const T& oldValue, const T& newValue, const size_t from = 0, const size_t to = s_maxSize)
	{
		if (oldValue == newValue)
		{
			return false;
		}

		return Replace([&](const T& element) { return element == oldValue; }, newValue, from, to);
	}

	// Replaces all occurrences of nullptr in the array with the new value
	bool Replace(std::nullptr_t, const T& newValue, const size_t from = 0, const size_t to = s_maxSize)
	{
		if (newValue == nullptr)
		{
			return false;
		}

		return Replace([](const T& element) { return element == nullptr; }, newValue, from, to);
	}

	// Replaces all elements in the array that satisfy the predicate with the new value
	template<typename Predicate>
	bool Replace(const Predicate& predicate, const T& newValue, const size_t from = 0, const size_t to = s_maxSize)
	{
		if (Size() == 0)
		{
			return false;
		}

		const size_t size = (to == s_maxSize) ? Size() : to;
		BoundsCheck(size - 1);
		bool dirty = false;
		for (size_t i = from; i < size; ++i)
		{
			if (predicate(Data()[i]))
			{
				Data()[i] = newValue;
				dirty = true;
			}
		}
		return dirty;
	}

	// Reverses the order of elements in the array
	bool Reverse() 
	{
		size_t first = 0;
		size_t last = Size() - 1;
		while (first < last)
		{
			Swap(first, last);
			++first;
			--last;
		}
		return Size() > 0;
	}

	// Returns a pointer to the last element in the array that satisfies the predicate, or nullptr if not found
	template<typename Predicate>
	const T* ReverseFind(const Predicate& predicate, const size_t from = 0, const size_t to = s_maxSize) const
	{
		if (Size() == 0)
		{
			return nullptr;
		}

		const size_t size = (to == s_maxSize) ? Size() : to;
		BoundsCheck(size - 1);
		for (size_t i = size - 1; i > from; --i)
		{
			if (predicate(Data()[i]))
			{
				return &Data()[i];
			}
		}
		return nullptr;
	}

	// Returns the index of the last occurrence of the given value in the array, or the array size if not found
	size_t ReverseIndexOf(const T& value, const size_t from = 0, const size_t to = s_maxSize) const
	{
		return ReverseIndexOf([&](const T& element) { return element == value; }, from, to);
	}

	// Returns the index of the last occurrence of nullptr in the array, or the array size if not found
	size_t ReverseIndexOf(std::nullptr_t, const size_t from = 0, const size_t to = s_maxSize) const
	{
		return ReverseIndexOf([](const T& element) { return element == nullptr; }, from, to);
	}

	// Returns the index of the last element in the array that satisfies the predicate, or the array size if not found
	template<typename Predicate>
	size_t ReverseIndexOf(const Predicate& predicate, const size_t from = 0, const size_t to = s_maxSize) const
	{
		if (Size() == 0)
		{
			return Size();
		}

		const size_t size = (to == s_maxSize) ? Size() : to;
		BoundsCheck(size - 1);
		for (size_t i = size - 1; i > from; --i)
		{
			if (predicate(Data()[i]))
			{
				return i;
			}
		}
		return Size();
	}


	// Randomly shuffles the array using a Fisher-Yates algorithm 
	// Note: Make sure to seed the random number generator (e.g. using srand) before calling this method to ensure proper randomness.
	bool Shuffle()
	{
		for (size_t i = 0; i < Size() - 1; ++i)
		{
			size_t j = i + rand() % (Size() - i);
			Swap(i, j);
		}
		return Size() > 0;
	}

	// Returns the size of the array
	virtual const size_t Size() const = 0;

	// Sorts the elements of the array using a quick sort algorithm in either ascending (default) or descending order
	// Note: An insertion sort will be used instead for small arrays.
	bool Sort(const SortOrder order = SortOrder::Ascending, const size_t from = 0, const size_t to = s_maxSize, const size_t insertionSortThreshold = s_defaultInsertionSortThreshold)
	{
		return Sort([order](const T& a, const T& b) { return order == SortOrder::Ascending ? a < b : a > b; }, from, to, insertionSortThreshold);
	}

	// Sorts the elements of the array using a quick sort algorithm based on the given predicate
	// Note: An insertion sort will be used instead for small arrays.
	template<typename Predicate>
	bool Sort(const Predicate& predicate, const size_t from = 0, const size_t to = s_maxSize, const size_t insertionSortThreshold = s_defaultInsertionSortThreshold)
	{
		if (Size() == 0)
		{
			return false;
		}

		const size_t size = (to == s_maxSize) ? Size() - 1 : to;
		BoundsCheck(size);
		return QuickSort(predicate, from, size, insertionSortThreshold);
	}

	// Swaps the elements at the given indices
	bool Swap(const size_t index1, const size_t index2)
	{
		if (index1 == index2)
		{
			return false;
		}
		BoundsCheck(index1);
		BoundsCheck(index2);

		const T temp = std::move(Data()[index1]);
		Data()[index1] = std::move(Data()[index2]);
		Data()[index2] = std::move(temp);

		return true;
	}

protected:
	// Returns the maximum size of the array
	static const size_t MaxSize()
	{
		return s_maxSize;
	}

private:
	// Copies or moves the elements from the source array into the destination array
	static bool CopyOrMove(T* source, const size_t sourceSize, T* destination, const size_t destinationSize, const size_t offset = 0, bool move = false)
	{
		if (!Equals(source, sourceSize, destination, destinationSize)) // Check for self-assignment
		{
			if (destinationSize < sourceSize + offset)
			{
				throw std::length_error("Destination array cannot be smaller than source array");
			}

			for (size_t i = 0; i < sourceSize; ++i)
			{
				destination[i + offset] = move ? std::move(source[i]) : source[i];
			}
			return sourceSize > 0;
		}
		return false;
	}

	// Copies or moves the elements from the source array into the destination array
	static bool CopyOrMove(const T* source, const size_t sourceSize, T* destination, const size_t destinationSize, const size_t offset = 0)
	{
		return CopyOrMove(const_cast<T*>(source), sourceSize, destination, destinationSize, offset);
	}

	// Returns whether two raw arrays are equal
	static bool Equals(const T* left, const size_t leftSize, const T* right, const size_t rightSize)
	{
		if (leftSize != rightSize)
		{
			return false;
		}

		if constexpr (std::equality_comparable<T>)
		{
			for (size_t i = 0; i < leftSize; ++i)
			{
				if (left[i] != right[i])
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			return std::memcmp(left, right, leftSize * sizeof(T)) == 0;
		}
	}

	// The index used for bounds checks
	virtual size_t Bounds() const
	{
		return Size();
	}

	// Throws an exception if the index is out of bounds
	void BoundsCheck(const size_t index) const
	{
		if (index >= Bounds())
		{
			throw std::out_of_range("Array index out of bounds");
		}
	}

	// Sort helper method - sorts the array using an insertion sort algorithm
	template<typename Predicate>
	bool InsertionSort(const Predicate& predicate, const size_t from, const size_t to)
	{
		bool dirty = false;
		// Iterates through the array from left to right
		for (size_t i = from + 1; i <= to; ++i)
		{
			const T element = Data()[i];

			size_t j = i;

			// Shift lower elements to the right until the correct position for the current element is found
			while (j > from && predicate(element, Data()[j - 1]))
			{
				Data()[j] = Data()[j - 1];
				--j;
				dirty = true;
			}

			// Insert the element in the correct position
			Data()[j] = element;
		}
		return dirty;
	}

	// Sort helper method - performs a single iteration of a quick sort algorithm and returns the pivot index
	template<typename Predicate>
	size_t Partition(const Predicate& predicate, const size_t from, const size_t to)
	{
		// Sorts the left, middle, and right elements of the array (median of three method)
		const size_t mid = (from + to) / 2;
		if (predicate(Data()[mid], Data()[from]))
		{
			Swap(from, mid);
		}
		if (predicate(Data()[to], Data()[from]))
		{
			Swap(from, to);
		}
		if (predicate(Data()[to], Data()[mid]))
		{
			Swap(mid, to);
		}

		// Selects the middle element as the pivot element and moves it next to the end of the array
		const T& pivotElement = Data()[mid];
		Swap(mid, to - 1);

		// Sorts the array so that elements smaller than the pivot element are on the left, and elements larger than the pivot element are on the right
		size_t pivotIndex = from;
		for (size_t i = from + 1; i < to - 1; ++i)
		{
			if (predicate(Data()[i], pivotElement))
			{
				++pivotIndex;
				Swap(i, pivotIndex);
			}
		}

		// Places the pivot element in the correct position in the sorted array
		++pivotIndex;
		Swap(pivotIndex, to - 1);

		return pivotIndex;
	}

	// Sort helper method - recursively performs a quick sort algorithm until the array is sorted
	template<typename Predicate>
	bool QuickSort(const Predicate& predicate, const size_t from, const size_t to, const size_t insertionSortThreshold = s_defaultInsertionSortThreshold)
	{
		// Checks if the indices to be sorted are valid and that there is more than 1 element in the array
		if (to <= from || to >= Size())
		{
			return false;
		}

		// If there are only two elements, just compare and swap
		if (to - from == 1)
		{
			if (predicate(Data()[to], Data()[from]))
			{
				Swap(from, to);
				return true;
			}
			return false;
		}

		// If the number of elements is less than the threshold, performs an insertion sort instead to save on recursion overhead
		if (to - from < insertionSortThreshold)
		{
			return InsertionSort(predicate, from, to);
		}

		// Partitions the array into two sub-arrays on either side of a pivot index
		const size_t pivot = Partition(predicate, from, to);

		// Recursively sorts each sub-array
		QuickSort(predicate, from, pivot - 1);
		QuickSort(predicate, pivot + 1, to);

		return true;
	}

	static const size_t s_defaultInsertionSortThreshold = 10; // By default, an insertion sort will be performed if the array size is less than this threshold
	static const size_t s_maxSize = std::numeric_limits<size_t>::max(); // The maximum size of the array
};

// Equality operator with c-style array
template <typename T, size_t N>
bool operator==(const T(&left)[N], const Array<T>& right)
{
	return right == left;
}

// Inequality operator with c-style array
template <typename T, size_t N>
bool operator!=(const T(&left)[N], const Array<T>& right)
{
	return !(right == left);
}