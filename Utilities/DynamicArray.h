/*
 * DynamicArray.h
 *
 * This custom dynamic array data structure offers several advantages over c-style arrays such as enhanced functionality, safety, and ease of use.
 * It provides additional methods, automated bounds checking, and abstracts away low-level memory management.
 * 
 * The size of the array can be changed during runtime enabling greater runtime flexibility.
 *
 * DISCLAIMER: This implementation is intended for portfolio/education purposes only.
 * For production use, it is recommended to use std::vector instead.
 *
 * © Copyright Peter Hoghton. All rights reserved.
 */

#pragma once

#include "Array.h"

template <typename T>
class DynamicArray : public Array<T>
{
public:
	using Array<T>::Contains;
	using Array<T>::s_maxSize;

	// Default constructor
	DynamicArray() : DynamicArray(0) {}

	// Constructor with capacity argument
	DynamicArray(const size_t capacity) 
	{
		Init(nullptr, 0, capacity);
	}

	// Copy constructor
	DynamicArray(const DynamicArray& other) : DynamicArray(other.m_data, other.m_size) {}

	// Move constructor
	DynamicArray(DynamicArray&& other) noexcept : DynamicArray(other.m_data, other.m_size, true) 
	{
		other.Resize(0);
	}

	// Conversion copy constructor from other Array
	DynamicArray(const Array<T>& other) : DynamicArray(other.Data(), other.Size()) {}

	// Conversion move constructor from other Array
	DynamicArray(Array<T>&& other) : DynamicArray(other.Data(), other.Size(), true) {}
	
	// Conversion copy constructor from initializer list
	DynamicArray(const std::initializer_list<T>& list) : DynamicArray(list.begin(), list.size()) {}

	// Conversion copy constructor from c-style array
	template <size_t N>
	DynamicArray(const T(&other)[N]) : DynamicArray(other, N) {}

	// Conversion copy constructor from raw array
	DynamicArray(const T* data, const size_t size)
	{
		Init(size);
		Copy(data, size);
	}

	// Conversion copy/move constructor from raw array
	DynamicArray(T* data, const size_t size, const bool move = false)
	{
		Init(size);
		move ? Move(data, size) : Copy(data, size);
	}

	// Default destructor
	~DynamicArray()
	{
		delete[] m_data;
	}

	// Copy assignment operator
	DynamicArray& operator=(const DynamicArray& other)
	{	
		Init(other.m_size);
		Copy(other.Data(), other.m_size);	
		return *this;
	}

	// Move assignment operator
	DynamicArray& operator=(DynamicArray&& other) noexcept
	{
		Init(other.m_size);
		Move(other.Data(), other.m_size);
		other.Resize(0);
		return *this;
	}

	// Conversion copy assignment operator from other Array
	DynamicArray& operator=(const Array<T>& other)
	{
		Init(other.Size());
		Copy(other.Data(), other.Size());
		return *this;
	}

	// Conversion move assignment operator from other Array
	DynamicArray& operator=(Array<T>&& other)
	{
		Init(other.Size());
		Move(other.Data(), other.Size());
		return *this;
	}

	// Conversion copy assignment operator from initializer list
	DynamicArray& operator=(const std::initializer_list<T>& list)
	{
		Init(list.size());
		Copy(list.begin(), list.size());
		return *this;
	}

	// Conversion copy assignment operator from c-style array
	template <size_t N>
	DynamicArray& operator=(const T(&other)[N])
	{
		Init(N);
		Copy(other, N);
		return *this;
	}

	// Addition assignment operator - concatenates the Dynamic Array and another Array
	DynamicArray<T>& operator+=(const Array<T>& other)
	{
		Add(other);
		return *this;
	}

	// Addition assignment operator - concatenates the Dynamic Array and an initializer list
	DynamicArray<T>& operator+=(const std::initializer_list<T>& list)
	{
		Add(list.begin(), list.size());
		return *this;
	}

	// Addition assignment operator - concatenates the Dynamic Array and a c-style array
	template <size_t N>
	DynamicArray<T>& operator+=(const T(&other)[N])
	{
		Add(other);
		return *this;
	}

	// Addition operator - concatenates two Arrays
	template <typename T>
	friend DynamicArray<T> operator+(const Array<T>& left, const Array<T>& right);

	// Addition operator - concatenates a Dynamic Array and a c-style array
	template <size_t N>
	DynamicArray<T> operator+(const T(&other)[N]) const
	{
		return Concatenate(m_data, m_size, other, N);
	}

	// Addition operator - concatenates a c-style array and a Dynamic Array
	template <typename T, size_t N>
	friend DynamicArray<T> operator+(const T(&left)[N], const DynamicArray<T>& right);

	// Adds an element to the end of the array
	void Add(const T& element)
	{
		Insert(m_size, element);
	}

	// Adds another Array to the end of the array
	bool Add(const Array<T>& other)
	{
		return Add(other.Data(), other.Size());
	}

	// Adds a c-style array to the end of the array
	template <size_t N>
	bool Add(const T(&other)[N])
	{
		return Add(other, N);
	}

	// Adds a raw array to the end of the array
	bool Add(const T* data, const size_t size)
	{
		return Insert(m_size, data, size);
	}

	// Adds an element to the end of the array only if it isn't already in the array
	bool AddUnique(const T& element)
	{
		return InsertUnique(m_size, element);
	}

	// Returns the capacity of the array
	size_t Capacity() const
	{
		return m_capacity;
	}

	// Deep copies the elements from the raw array
	// Note: Remaining elements are left uninitialized.
	bool Copy(const T* data, const size_t size, const size_t offset = 0) override
	{
		if (m_data == nullptr)
		{
			Init(m_capacity);
		}
		return Array<T>::Copy(data, size, offset);
	}

	// Returns a pointer to the first element of the array
	T* Data() override
	{
		return m_data;
	}

	// Returns a pointer to the first element of the array (const version)
	const T* Data() const override
	{
		return m_data;
	}

	// Constructs an element at the end of the array
	template<typename... Args>
	void Emplace(Args&&... args)
	{
		EmplaceAt(m_size, std::forward<Args>(args)...);
	}

	// Constructs an element at the specified index
	template<typename... Args>
	void EmplaceAt(const size_t index, Args&&... args)
	{
		Grow(index);
		m_data[index] = T(std::forward<Args>(args)...);
		++m_size;
	}

	// Fills the array with the given value
	// Note: Remaining elements are left uninitialized.
	bool Fill(const T& value = T{}, const size_t from = 0, const size_t to = s_maxSize) override
	{
		if (m_data == nullptr)
		{
			Init(m_capacity);
		}
		return Array<T>::Fill(value, from, to);
	}

	// Inserts an element at the specified index
	void Insert(const size_t index, const T& element)
	{
		Grow(index);
		m_data[index] = element;
		++m_size;
	}

	// Inserts another Array at the specified index
	bool Insert(const size_t index, const Array<T>& other)
	{
		return Insert(index, other.Data(), other.Size());
	}

	// Inserts a c-style array at the specified index
	template <size_t N>
	bool Insert(const size_t index, const T(&other)[N])
	{
		return Insert(index, other, N);
	}

	// Inserts a raw array at the specified index
	bool Insert(const size_t index, const T* data, const size_t size)
	{
		Grow(index, size);

		for (size_t i = 0; i < size; ++i)
		{
			m_data[index + i] = data[i];
		}

		m_size += size;

		return size > 0;
	}

	// Inserts an element at the specified index only if it isn't already in the array
	bool InsertUnique(const size_t index, const T& element)
	{
		if (!Contains(element))
		{
			Insert(index, element);
			return true;
		}
		return false;
	}

	// Moves the elements from the raw array
	// Note: Remaining elements are left uninitialized.
	bool Move(T* data, const size_t size, const size_t offset = 0) override
	{
		if (m_data == nullptr)
		{
			Init(m_capacity);
		}
		return Array<T>::Move(data, size, offset);
	}

	// Removes all occurrences of the given value from the array
	bool Remove(const T& value)
	{
		return Remove([&](const T& element) { return element == value; });
	}

	// Removes all occurrences of nullptr from the array
	bool Remove(std::nullptr_t)
	{
		return Remove([](const T& element) { return element == nullptr; });
	}

	// Removes all elements that satisfy the predicate from the array
	template<typename Predicate>
	bool Remove(const Predicate& predicate)
	{
		size_t count = 0;

		for (size_t i = 0; i < m_size; ++i)
		{
			if (predicate(m_data[i]))
			{
				++count;
			}
		}

		if (count == 0)
		{
			return false;
		}

		T* newData = new T[m_size - count];

		size_t index = 0;

		for (size_t i = 0; i < m_size; ++i)
		{
			if (!predicate(m_data[i]))
			{
				newData[index++] = m_data[i];
			}
		}

		delete[] m_data;
		m_data = newData;
		m_size -= count;

		Shrink();

		return true;
	}

	// Removes all elements from the array
	bool RemoveAll() override
	{
		return Resize(0);
	}

	// Removes the element at the specified index
	void RemoveAt(const size_t index)
	{
		RemoveRange(index, index);
	}

	// Removes all duplicate elements from the array
	bool RemoveDuplicates()
	{
		DynamicArray<T> result;

		for (size_t i = 0; i < m_size; ++i)
		{
			result.AddUnique(m_data[i]);
		}

		if (result.m_size < m_size)
		{
			*this = std::move(result);
			return true;
		}

		return false;
	}

	// Remove the elements within the specified range from the array
	bool RemoveRange(const size_t from, const size_t to)
	{
		if (to > m_size || from > to)
		{
			throw std::out_of_range("Array index out of bounds");
		}
		size_t count = to - from + 1;	
		if (count > 0)
		{
			for (size_t i = to + 1; i < m_size; ++i)
			{
				m_data[i - count] = m_data[i];
			}
			m_size -= count;
			Shrink();
			return true;
		}

		return false;
	}

	// Resizes the array to the specified capacity
	bool Resize(const size_t capacity)
	{
		if (capacity == m_capacity)
		{
			return false;
		}

		T* newData = (capacity == 0) ? nullptr : new T[capacity];

		size_t newSize = (m_size < capacity) ? m_size : capacity;
		for (size_t i = 0; i < newSize; ++i)
		{
			newData[i] = m_data[i];
		}

		delete[] m_data;
		Init(newData, newSize, capacity);

		return true;
	}

	// Returns the size of the array
	const size_t Size() const override
	{
		return m_size;
	}

	// Trims the capacity of the array to fit its contents
	bool Trim()
	{
		return Resize(m_size);
	}

private:
	// Concatenates the two arrays and returns the result
	static DynamicArray<T> Concatenate(const T* left, const size_t leftSize, const T* right, const size_t rightSize)
	{
		DynamicArray<T> result;
		result.Init(leftSize + rightSize);

		result.Copy(left, leftSize);
		result.Copy(right, rightSize, leftSize);

		return result;
	}

	// The index used for bounds checks
	size_t Bounds() const override
	{
		return m_capacity;
	}

	// Grows the array from the specified index if necessary
	bool Grow(const size_t index, const size_t amount = 1)
	{
		if (m_data == nullptr)
		{
			Init(new T[m_capacity], m_size, m_capacity);
		}

		if (m_size + amount > m_capacity)
		{
			size_t newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
			Resize(m_size + amount > newCapacity ? m_size + amount : newCapacity);
		}

		for (size_t i = m_capacity - 1; i >= index + amount; --i)
		{
			m_data[i] = std::move(m_data[i - amount]);
		}

		return amount > 0;
	}

	// Initializes the array with default values
	void Init(const size_t capacity = 0)
	{
		Init(capacity == 0 ? nullptr : new T[capacity], capacity, capacity);
	}

	// Initializes the array with default values
	void Init(T* data, const size_t size, const size_t capacity)
	{
		m_data = data;
		m_size = size;
		m_capacity = capacity;
	}

	// Shrinks the array if necessary
	bool Shrink()
	{
		if (m_size < m_capacity / 2)
		{
			size_t newCapacity = (m_capacity == 1) ? 0 : m_capacity / 2;
			return Resize(m_size < newCapacity / 2 ? m_size : newCapacity);
		}
		return false;
	}

	T* m_data; // Pointer to the first element of the array
	size_t m_size; // Size of the array
	size_t m_capacity; // Capacity of the array
};

// Addition operator - concatenates two Arrays
template <typename T>
DynamicArray<T> operator+(const Array<T>& left, const Array<T>& right)
{
	return DynamicArray<T>::Concatenate(left.Data(), left.Size(), right.Data(), right.Size());
}

// Addition operator - concatenates a c-style array and a Dynamic Array
template <typename T, size_t N>
DynamicArray<T> operator+(const T(&left)[N], const DynamicArray<T>& right)
{
	return DynamicArray<T>::Concatenate(left, N, right.m_data, right.m_size);
}