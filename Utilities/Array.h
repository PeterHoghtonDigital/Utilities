/* 
 * Array.h
 * 
 * This custom static array data structure offers several advantages over c-style arrays such as enhanced functionality, safety, and ease of use. 
 * It provides additional methods, automated bounds checking, and abstracts away low-level memory management.
 * 
 * DISCLAIMER: This implementation is intended for portfolio/education purposes only. 
 * For production use, it is recommended to use std::array instead.
 *
 * © Copyright Peter Hoghton. All rights reserved.
 */

#pragma once

#include <stdexcept>

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
	// Constructor with size argument
	Array(const size_t size) : m_data(new T[size]), m_size(size) {}

	// Constructor with initializer list
	Array(std::initializer_list<T> list) : m_data(new T[list.size()]), m_size(list.size())
	{
		size_t index = 0;
		for(const T& element : list)
		{
			m_data[index++] = element;
		}
	}

	// Copy constructor
	Array(const Array& other) : m_data(new T[other.m_size]), m_size(other.m_size)
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			m_data[i] = other.m_data[i];
		}
	}

	// Move constructor
	Array(Array&& other) noexcept : m_data(other.m_data), m_size(other.m_size)
	{
		other.m_data = nullptr;
		other.m_size = 0;
	}

	// Destructor
	~Array()
	{
		delete[] m_data;
	}

	// Copy assignment operator
	Array& operator=(const Array& other)
	{
		if (this != &other) // Check for self-assignment
		{
			delete[] m_data;
			m_data = new T[other.m_size];
			m_size = other.m_size;
			for (size_t i = 0; i < m_size; ++i)
			{
				m_data[i] = other.m_data[i];
			}	
		}
		return *this;
	}

	// Move assignment operator
	Array& operator=(Array&& other) noexcept
	{
		if (this != &other) // Check for self-assignment
		{
			delete[] m_data;
			m_data = other.m_data;
			m_size = other.m_size;
			other.m_data = nullptr;
			other.m_size = 0;
		}
		return *this;
	}

	// Index operator
	T& operator[](const size_t index)
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Array index out of bounds");
		}
		return m_data[index];
	}

	// Const version of index operator
	const T& operator[](const size_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Array index out of bounds");
		}
		return m_data[index];
	}

	// Equality operator
	bool operator==(const Array& other) const
	{
		if (m_size != other.m_size)
		{
			return false;
		}

		for (size_t i = 0; i < m_size; ++i)
		{
			if (m_data[i] != other.m_data[i])
			{
				return false;
			}
		}

		return true;
	}

	// Inequality operator
	bool operator!=(const Array& other) const
	{
		return !(*this == other);
	}

	// Addition operator - concatenates the two arrays
	Array<T> operator+(const Array<T>& other) const
	{
		Array<T> result(m_size + other.m_size);

		for (size_t i = 0; i < m_size; ++i)
		{
			result[i] = m_data[i];
		}

		for (size_t i = 0; i < other.m_size; ++i)
		{
			result[m_size + i] = other.m_data[i];
		}

		return result;
	}

	// Range-based for loop support
	T* begin()
	{
		return m_data;
	}

	T* end()
	{
		return m_data + m_size;
	}

	const T* begin() const
	{
		return m_data;
	}

	const T* end() const
	{
		return m_data + m_size;
	}

	// Returns true if the array contains the given value
	bool Contains(const T& value, const size_t offset = 0) const
	{
		return Contains([&](const T& element) { return element == value; }, offset);
	}

	// Returns true if the array contains nullptr
	bool Contains(std::nullptr_t, const size_t offset = 0) const
	{
		return Contains([](const T& element) { return element == nullptr; }, offset);
	}

	// Returns true if the given predicate returns true for any element in the array
	template<typename Predicate>
	bool Contains(const Predicate& predicate, const size_t offset = 0) const
	{
		return Find(predicate, offset);
	}

	// Returns the number of occurrences of the given value in the array
	size_t Count(const T& value, const size_t offset = 0) const
	{
		return Count([&](const T& element) { return element == value; }, offset);
	}

	// Returns the number of occurrences of nullptr in the array
	size_t Count(std::nullptr_t, const size_t offset = 0) const
	{
		return Count([&](const T& element) { return element == nullptr; }, offset);
	}

	// Returns the number of elements in the array that satisfy the given predicate
	template<typename Predicate>
	size_t Count(const Predicate& predicate, const size_t offset = 0) const
	{
		size_t count = 0;
		for (size_t i = offset; i < m_size; ++i)
		{
			if (predicate(m_data[i]))
			{
				++count;
			}
		}
		return count;
	}

	// Fills the array with the given value
	void Fill(const T& value, const size_t offset = 0)
	{
		for (size_t i = offset; i < m_size; ++i)
		{
			m_data[i] = value;
		}
	}

	// Returns a pointer to the first element in the array that satisfies the predicate, or nullptr if not found
	template<typename Predicate>
	T* Find(const Predicate& predicate, const size_t offset = 0) const
	{
		for (size_t i = offset; i < m_size; ++i)
		{
			if (predicate(m_data[i]))
			{
				return &m_data[i];
			}
		}
		return nullptr;
	}

	// Returns the index of the first occurrence of the given value in the array, or the array size if not found
	size_t IndexOf(const T& value, const size_t offset = 0) const
	{
		return IndexOf([&](const T& element) { return element == value; }, offset);
	}

	// Returns the index of the first occurrence of nullptr in the array, or the array size if not found
	size_t IndexOf(std::nullptr_t, const size_t offset = 0) const
	{
		return IndexOf([](const T& element) { return element == nullptr; }, offset);
	}

	// Returns the index of the first element in the array that satisfies the predicate, or the array size if not found
	template<typename Predicate>
	size_t IndexOf(const Predicate& predicate, const size_t offset = 0) const
	{
		for (size_t i = offset; i < m_size; ++i)
		{
			if (predicate(m_data[i]))
			{
				return i;
			}
		}
		return m_size;
	}

	// Replaces all occurrences of the old value in the array with the new value
	void Replace(const T& oldValue, const T& newValue, const size_t offset = 0)
	{
		if (oldValue == newValue)
		{
			return;
		}

		Replace([&](const T& element) { return element == oldValue; }, newValue, offset);
	}

	// Replaces all elements in the array that satisfy the predicate with the new value
	template<typename Predicate>
	void Replace(const Predicate& predicate, const T& newValue, const size_t offset = 0)
	{
		for (size_t i = offset; i < m_size; ++i)
		{
			if (predicate(m_data[i]))
			{
				m_data[i] = newValue;
			}
		}
	}

	// Randomly shuffles the array using a Fisher-Yates algorithm 
	// Note: Make sure to seed the random number generator (e.g. using srand) before calling this method to ensure proper randomness.
	void Shuffle(const size_t offset = 0) 
	{
		for (size_t i = m_size - 1; i > offset; --i)
		{
			size_t j = offset + rand() % (i - offset + 1);
			Swap(i, j);
		}
	}

	// Size of the array
	size_t Size() const
	{
		return m_size;
	}

	// Sorts the elements of the array using a quick sort algorithm in either ascending (default) or descending order
	void Sort(const SortOrder order = SortOrder::Ascending, const size_t offset = 0, const size_t insertionSortThreshold = 10)
	{
		Sort([order](const T& a, const T& b) { return order == SortOrder::Ascending ? a < b : a > b; }, offset, insertionSortThreshold);
	}

	// Sorts the elements of the array using a quick sort algorithm based on the given predicate
	template<typename Predicate>
	void Sort(const Predicate& predicate, const size_t offset = 0, const size_t insertionSortThreshold = 10)
	{
		QuickSort(offset, m_size - 1, predicate, insertionSortThreshold);
	}

	// Swaps the elements at the given indices
	void Swap(const size_t index1, const size_t index2)
	{
		if (index1 == index2)
		{
			return;
		}
		if (index1 >= m_size || index2 >= m_size)
		{
			throw std::out_of_range("Array index out of bounds");
		}
		
		const T temp = m_data[index1];
		m_data[index1] = m_data[index2];
		m_data[index2] = temp;
	}

private:
	// Sort helper method - sorts the array using an insertion sort algorithm
	template<typename Predicate>
	void InsertionSort(const size_t left, const size_t right, const Predicate& predicate)
	{
		// Iterates through the array from left to right
		for (size_t i = left + 1; i <= right; ++i)
		{
			const T element = m_data[i];

			size_t j = i;

			// Shift lower elements to the right until the correct position for the current element is found
			while (j > left && predicate(element, m_data[j - 1]))
			{
				m_data[j] = m_data[j - 1];
				--j;
			}

			// Insert the element in the correct position
			m_data[j] = element;
		}
	}

	// Sort helper method - performs a single iteration of a quick sort algorithm and returns the pivot index
	template<typename Predicate>
	size_t Partition(const size_t left, const size_t right, const Predicate& predicate)
	{
		// Sorts the left, middle, and right elements of the array (median of three method)
		const size_t mid = (left + right) / 2;
		if (predicate(m_data[mid], m_data[left]))
		{
			Swap(left, mid);
		}
		if (predicate(m_data[right], m_data[left]))
		{
			Swap(left, right);
		}
		if (predicate(m_data[right], m_data[mid]))
		{
			Swap(mid, right);
		}

		// Selects the middle element as the pivot element and moves it next to the end of the array
		const T& pivotElement = m_data[mid];
		Swap(mid, right - 1);

		// Sorts the array so that elements smaller than the pivot element are on the left, and elements larger than the pivot element are on the right
		size_t pivotIndex = left;
		for (size_t i = left + 1; i < right - 1; ++i)
		{
			if (predicate(m_data[i], pivotElement))
			{
				++pivotIndex;
				Swap(i, pivotIndex);
			}
		}

		// Places the pivot element in the correct position in the sorted array
		++pivotIndex;
		Swap(pivotIndex, right - 1);

		return pivotIndex;
	}

	// Sort helper method - recursively performs a quick sort algorithm until the array is sorted
	template<typename Predicate>
	void QuickSort(const size_t left, const size_t right, const Predicate& predicate, const size_t insertionSortThreshold = 10)
	{
		// Checks if the indices to be sorted are valid and that there is more than 1 element in the array
		if (right <= left || right >= m_size)
		{
			return;
		}

		// If there are only two elements, just compare and swap
		if (right - left == 1)
		{
			if (predicate(m_data[right], m_data[left]))
			{
				Swap(left, right);
			}
			return;
		}

		// If the number of elements is less than the threshold, performs an insertion sort instead to save on recursion overhead
		if (right - left < insertionSortThreshold)
		{
			InsertionSort(left, right, predicate);
			return;
		}

		// Partitions the array into two sub-arrays on either side of a pivot index
		const size_t pivot = Partition(left, right, predicate);

		// Recursively sorts each sub-array
		QuickSort(left, pivot - 1, predicate);
		QuickSort(pivot + 1, right, predicate);
	}

	T* m_data; // Pointer to the first element of the array
	size_t m_size; // Size of the array
};