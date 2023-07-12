/*
 * StaticArray.h
 *
 * This custom static array data structure offers several advantages over c-style arrays such as enhanced functionality, safety, and ease of use.
 * It provides additional methods, automated bounds checking, and abstracts away low-level memory management.
 * 
 * The size of the array is determined at compile time enabling compile time optimization.
 *
 * DISCLAIMER: This implementation is intended for portfolio/education purposes only.
 * For production use, it is recommended to use std::array instead.
 *
 * © Copyright Peter Hoghton. All rights reserved.
 */

#pragma once

#include "Array.h"

template <typename T, size_t N>
class StaticArray : public Array<T>
{
public:
	using Array<T>::Copy;
	using Array<T>::Fill;
	using Array<T>::Move;

	// Default constructor
	StaticArray() = default;

	// Copy constructor
	StaticArray(const StaticArray& other) : StaticArray(other.Data(), N) {}

	// Move constructor
	StaticArray(StaticArray&& other) noexcept : StaticArray(other.Data(), N, true) {}

	// Conversion copy constructor from other Array
	StaticArray(const Array<T>& other) : StaticArray(other.Data(), other.Size()) {}

	// Conversion move constructor from other Array
	StaticArray(Array<T>&& other) : StaticArray(other.Data(), other.Size(), true) {}

	// Conversion copy constructor from initializer list
	StaticArray(const std::initializer_list<T>& list) : StaticArray(list.begin(), list.size()) {}

	// Conversion copy constructor from c-style array
	template <size_t M>
	StaticArray(const T(&other)[M]) : StaticArray(other, M) {}

	// Conversion copy constructor from raw array
	StaticArray(const T* data, const size_t size)
	{
		Copy(data, size);
		Fill(T{}, size); // Fills remaining elements with default values
	}

	// Conversion copy/move constructor from raw array
	StaticArray(T* data, const size_t size, const bool move = false)
	{
		move ? Move(data, size) : Copy(data, size);
		Fill(T{}, size); // Fills remaining elements with default values
	}

	// Default destructor
	~StaticArray() = default;

	// Copy assignment operator
	StaticArray& operator=(const StaticArray& other)
	{
		Copy(other.Data(), N);
		return *this;
	}

	// Move assignment operator
	StaticArray& operator=(StaticArray&& other) noexcept
	{
		Move(other.Data(), N);
		return *this;
	}

	// Conversion copy assignment operator from other Array
	StaticArray& operator=(const Array<T>& other)
	{
		Copy(other.Data(), other.Size());
		Fill(T{}, other.Size()); // Fills remaining elements with default values
		return *this;
	}

	// Conversion move assignment operator from other Array
	StaticArray& operator=(Array<T>&& other)
	{
		Move(other.Data(), other.Size());
		Fill(T{}, other.Size()); // Fills remaining elements with default values
		return *this;
	}

	// Conversion copy assignment operator from initializer list
	StaticArray& operator=(const std::initializer_list<T>& list)
	{
		Copy(list.begin(), list.size());
		Fill(T{}, list.size()); // Fills remaining elements with default values
		return *this;
	}

	// Conversion copy assignment operator from c-style array
	template <size_t M>
	StaticArray& operator=(const T(&other)[M])
	{
		Copy(other, M);
		Fill(T{}, M); // Fills remaining elements with default values
		return *this;
	}

	// Addition operator - concatenates two Static Arrays
	template <size_t M>
	StaticArray<T, N + M> operator+(const StaticArray<T, M>& other) const
	{
		return Concatenate<T, N, M>(m_data, other.Data());
	}

	// Addition operator - concatenates a Static Array and a c-style array
	template <size_t M>
	StaticArray<T, N + M> operator+(const T(&other)[M]) const
	{
		return Concatenate<T, N, M>(m_data, other);
	}

	// Addition operator - concatenates a c-style array and a Static Array
	template <typename T, size_t M, size_t N>
	friend StaticArray<T, M + N> operator+(const T(&left)[M], const StaticArray<T, N>& right);

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

	// Removes all elements from the array
	bool RemoveAll() override
	{
		return Fill(); // Resets all elements to default values
	}

	// Returns the size of the array
	const size_t Size() const override
	{
		return N;
	}

	// Returns the size of the array (constexpr)
	constexpr size_t StaticSize() const
	{
		return N;
	}

private:
	// Concatenates the two arrays and returns the result
	template <typename T, size_t N, size_t M>
	static StaticArray<T, N + M> Concatenate(const T* left, const T* right)
	{
		StaticArray<T, N + M> result;

		result.Copy(left, N);
		result.Copy(right, M, N);

		return result;
	}

	T m_data[N]; // The array data
};

// Special case for size 0 array
template <typename T>
class StaticArray<T, 0> : public Array<T>
{
public:
	//Default constructor
	StaticArray() = default;

	// Copy constructor
	StaticArray(const StaticArray& other) = delete;

	// Move constructor
	StaticArray(StaticArray&& other) noexcept = delete;

	// Conversion copy constructor from other Array
	StaticArray(const Array<T>& other) = delete;

	// Conversion move constructor from other Array
	StaticArray(Array<T>&& other) = delete;

	// Conversion copy constructor from initializer list
	StaticArray(const std::initializer_list<T>& list) = delete;

	// Conversion copy constructor from c-style array
	template <size_t M>
	StaticArray(const T(&other)[M]) = delete;

	// Conversion copy constructor from const raw array
	StaticArray(const T* data, const size_t size) = delete;

	// Conversion copy/move constructor from raw array
	StaticArray(T* data, const size_t size, const bool move = false) = delete;

	//Default destructor
	~StaticArray() = default;

	// Copy assignment operator
	StaticArray& operator=(const StaticArray& other) = delete;

	// Move assignment operator
	StaticArray& operator=(StaticArray&& other) noexcept = delete;

	// Conversion copy assignment operator from other Array
	StaticArray& operator=(const Array<T>& other) = delete;

	// Conversion move assignment operator from other Array
	StaticArray& operator=(Array<T>&& other) = delete;

	// Conversion copy assignment operator from initializer list
	StaticArray& operator=(const std::initializer_list<T>& list) = delete;

	// Conversion copy assignment operator from c-style array
	template <size_t M>
	StaticArray& operator=(const T(&other)[M]) = delete;

	// Addition operator - concatenates two Static Arrays
	template <size_t M>
	StaticArray<T, M> operator+(const StaticArray<T, M>& other) const
	{
		return other;
	}

	// Addition operator - concatenates a Static Array and a c-style array
	template <size_t M>
	StaticArray<T, M> operator+(const T(&other)[M]) const
	{
		return other;
	}

	// Returns a pointer to the first element of the array
	T* Data() override
	{
		return nullptr;
	}

	// Returns a pointer to the first element of the array (const version)
	const T* Data() const override
	{
		return nullptr;
	}

	// Removes all elements from the array
	bool RemoveAll() override
	{
		return false;
	}

	// Returns the size of the array
	const size_t Size() const override
	{
		return 0;
	}

	// Returns the size of the array (constexpr)
	constexpr size_t StaticSize() const
	{
		return 0;
	}
};

// Addition operator - concatenates a c-style array and a Static Array
template <typename T, size_t M, size_t N>
StaticArray<T, M + N> operator+(const T(&left)[M], const StaticArray<T, N>& right)
{
	return StaticArray<T, M + N>::template Concatenate<T, M, N>(left, right.m_data);
}

// Addition operator - concatenates a c-style array and a Static Array
template <typename T, size_t M>
StaticArray<T, M> operator+(const T(&left)[M], const StaticArray<T, 0>& right)
{
	return StaticArray<T, M>(left);
}