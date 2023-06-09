#include "UnitTests.h"

#include <cassert>
#include <ctime>
#include <iostream>

#include "Array.h"

// Unit tests for the Array class in Array.h
void TestArray()
{
	// Test constructor with size argument
	Array<int> a(3);
	assert(a.Size() == 3);

	// Test constructor with initializer list
	Array<int> b = { 1, 2, 3 };
	assert(b.Size() == 3);
	assert(b[0] == 1);
	assert(b[1] == 2);
	assert(b[2] == 3);

	// Test copy constructor
	Array<int> c = b;
	assert(c.Size() == 3);
	assert(c[0] == 1);
	assert(c[1] == 2);
	assert(c[2] == 3);

	// Test move constructor
	Array<int> d = std::move(c);
	assert(c.Size() == 0);
	assert(d.Size() == 3);
	assert(d[0] == 1);
	assert(d[1] == 2);
	assert(d[2] == 3);

	// Test copy assignment operator
	Array<int> e(0);
	e = d;
	assert(e.Size() == 3);
	assert(e[0] == 1);
	assert(e[1] == 2);
	assert(e[2] == 3);

	// Test move assignment operator
	Array<int> f(0);
	f = std::move(e);
	assert(e.Size() == 0);
	assert(f.Size() == 3);
	assert(f[0] == 1);
	assert(f[1] == 2);
	assert(f[2] == 3);

	// Test index operator
	f[1] = 5;
	assert(f[1] == 5);

	// Test const index operator
	const Array<int> g = f;
	assert(g[1] == 5);

	// Test equality operator
	assert(g == f);

	// Test inequality operator
	assert(g != d);

	// Test addition (concatenation) operator
	Array<int> h = g + d;
	assert(h[0] == 1);
	assert(h[1] == 5);
	assert(h[2] == 3);
	assert(h[3] == 1);
	assert(h[4] == 2);
	assert(h[5] == 3);

	// Test range-based for loop
	for (int& i : h)
	{
		i *= 2;
	}
	assert(h[0] == 2);
	assert(h[1] == 10);
	assert(h[2] == 6);
	assert(h[3] == 2);
	assert(h[4] == 4);
	assert(h[5] == 6);

	// Test Contains method
	assert(h.Contains(2));
	assert(!h.Contains(0));

	// Test Count method
	assert(h.Count(2) == 2);

	// Test Fill method
	h.Fill(0);
	assert(h[0] == 0);
	assert(h[1] == 0);
	assert(h[2] == 0);
	assert(h[3] == 0);
	assert(h[4] == 0);
	assert(h[5] == 0);

	// Test Find method
	int* ptr = h.Find([](const int& element) { return element == 0; });
	assert(ptr != nullptr && *ptr == 0);
	ptr = h.Find([](const int& element) { return element == 1; });
	assert(ptr == nullptr);

	// Test IndexOf method
	assert(h.IndexOf(0) == 0);
	assert(h.IndexOf(1) == h.Size());

	// Test Replace method
	h.Replace(0, 1);
	assert(h[0] == 1);
	assert(h[1] == 1);
	assert(h[2] == 1);
	assert(h[3] == 1);
	assert(h[4] == 1);
	assert(h[5] == 1);

	// Test Shuffle method
	Array<int> i = { 1, 2, 3, 4, 5 };
	i.Shuffle();
	Array<int> j = { 1, 2, 3, 4, 5 };
	assert(i != j);

	// Test Sort method
	i.Sort();
	assert(i[0] == 1);
	assert(i[1] == 2);
	assert(i[2] == 3);
	assert(i[3] == 4);
	assert(i[4] == 5);

	// Test Swap method
	i.Swap(0, 2);
	assert(i[0] == 3);
	assert(i[1] == 2);
	assert(i[2] == 1);
	assert(i[3] == 4);
	assert(i[4] == 5);
}

// Unit tests for the Array class in Array.h, where the template is a pointer type
void TestArrayWithPointers()
{
	// Test constructor with size argument
	Array<int*> a(3);
	assert(a.Size() == 3);

	// Test constructor with initializer list
	int* ptr1 = new int(1);
	int* ptr2 = new int(2);
	int* ptr3 = new int(3);
	Array<int*> b = { ptr1, ptr2, ptr3 };
	assert(b.Size() == 3);
	assert(*b[0] == 1);
	assert(*b[1] == 2);
	assert(*b[2] == 3);

	// Test copy constructor
	Array<int*> c = b;
	assert(c.Size() == 3);
	assert(*c[0] == 1);
	assert(*c[1] == 2);
	assert(*c[2] == 3);

	// Test move constructor
	Array<int*> d = std::move(c);
	assert(c.Size() == 0);
	assert(d.Size() == 3);
	assert(*d[0] == 1);
	assert(*d[1] == 2);
	assert(*d[2] == 3);

	// Test copy assignment operator
	Array<int*> e(0);
	e = d;
	assert(e.Size() == 3);
	assert(*e[0] == 1);
	assert(*e[1] == 2);
	assert(*e[2] == 3);

	// Test move assignment operator
	Array<int*> f(0);
	f = std::move(e);
	assert(e.Size() == 0);
	assert(f.Size() == 3);
	assert(*f[0] == 1);
	assert(*f[1] == 2);
	assert(*f[2] == 3);

	// Test index operator
	int* ptr4 = new int(5);
	f[1] = ptr4;
	assert(*f[1] == 5);

	// Test const index operator
	const Array<int*> g = f;
	assert(*g[1] == 5);

	// Test equality operator
	assert(g == f);

	// Test inequality operator
	assert(g != d);

	// Test addition (concatenation) operator
	Array<int*> h = g + d;
	assert(*h[0] == 1);
	assert(*h[1] == 5);
	assert(*h[2] == 3);
	assert(*h[3] == 1);
	assert(*h[4] == 2);
	assert(*h[5] == 3);

	// Test range-based for loop
	for (int* i : h)
	{
		*i *= 2;
	}
	assert(*h[0] == 4); // Note h[0] and h[3] are the same ptr so are doubled twice
	assert(*h[1] == 10);
	assert(*h[2] == 12); // Note h[2] and h[5] are the same ptr so are doubled twice
	assert(*h[3] == 4);
	assert(*h[4] == 4);
	assert(*h[5] == 12);

	// Test Contains method
	assert(h.Contains(ptr2));
	assert(!h.Contains(nullptr));

	// Test Count method
	assert(h.Count(ptr1) == 2);

	// Test Fill method
	int* ptr5 = new int(0);
	h.Fill(ptr5);
	assert(*h[0] == 0);
	assert(*h[1] == 0);
	assert(*h[2] == 0);
	assert(*h[3] == 0);
	assert(*h[4] == 0);
	assert(*h[5] == 0);

	// Test Find method
	int* ptr6 = new int(5);
	h[3] = ptr6;
	assert(*h.Find([](const int* ptr) { return *ptr == 5; }) == ptr6);
	assert(h.Find([](const int* ptr) { return *ptr == 1; }) == nullptr);

	// Test IndexOf method
	assert(h.IndexOf(ptr5) == 0);
	assert(h.IndexOf(ptr4) == h.Size());

	// Test Replace method
	int* ptr7 = new int(1);
	h.Replace(ptr5, ptr7);
	assert(*h[0] == 1);
	assert(*h[1] == 1);
	assert(*h[2] == 1); 
	assert(*h[3] == 5); // Note h[3] is ptr6 so remains the same
	assert(*h[4] == 1);
	assert(*h[5] == 1);

	// Test Shuffle method
	Array<int*> i = { ptr1, ptr2, ptr3, ptr4, ptr5 };
	i.Shuffle();
	Array<int*> j = { ptr1, ptr2, ptr3, ptr4, ptr5 };
	assert(i != j);

	// Test Sort method
	i.Sort([](const int* a, const int* b) { return *a < *b; });
	assert(*i[0] == 0);
	assert(*i[1] == 4);
	assert(*i[2] == 4);
	assert(*i[3] == 10);
	assert(*i[4] == 12);

	// Test Swap method
	i.Swap(0, 2);
	assert(*i[0] == 4);
	assert(*i[1] == 4);
	assert(*i[2] == 0);
	assert(*i[3] == 10);
	assert(*i[4] == 12);

	delete ptr1;
	delete ptr2;
	delete ptr3;
	delete ptr4;
	delete ptr5;
	delete ptr6;
	delete ptr7;
}

// Runs all unit tests - comment out individual tests as needed
void UnitTests::Run()
{
	// Seed random number generator
	srand(static_cast<unsigned int>(time(nullptr)));

	TestArray();
	TestArrayWithPointers();

	std::cout << "All tests passed!\n";
}