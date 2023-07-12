#include "UnitTestStaticArray.h"

#include <array>
#include <cassert>
#include <ctime>

#include "DynamicArray.h"
#include "StaticArray.h"

namespace UnitTests
{
	void UnitTestStaticArrayConstructors();
	void UnitTestStaticArrayAssignment();
	void UnitTestStaticArrayOperators();
	void UnitTestStaticArrayMethods();
	void UnitTestStaticArrayZero();

	void UnitTestStaticArray()
	{
		UnitTestStaticArrayConstructors();
		UnitTestStaticArrayAssignment();
		UnitTestStaticArrayOperators();
		UnitTestStaticArrayMethods();
		UnitTestStaticArrayZero();
	}

	void UnitTestStaticArrayConstructors()
	{
		// Default constructor
		StaticArray<int, 3> a{}; // Value initialization, can omit braces to leave elements uninitialized
		assert(a.Size() == 3);
		assert(a[0] == 0);
		assert(a[1] == 0);
		assert(a[2] == 0);

		// Copy constructor
		StaticArray<int, 3> b = { 1, 2, 3 };
		StaticArray<int, 3> c = b;
		assert(c.Size() == 3);
		assert(c[0] == 1);
		assert(c[1] == 2);
		assert(c[2] == 3);

		// Move constructor
		StaticArray<int, 3> d = { 1, 2, 3 };
		StaticArray<int, 3> e = std::move(d);
		assert(e.Size() == 3);
		assert(e[0] == 1);
		assert(e[1] == 2);
		assert(e[2] == 3);

		// Conversion copy constructor from other Array (Static Array with different size)
		StaticArray<int, 3> f = { 1, 2, 3 };

		bool success = false;
		try
		{
			StaticArray<int, 1> g = f; // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> g = f;
		assert(g.Size() == 5);
		assert(g[0] == 1);
		assert(g[1] == 2);
		assert(g[2] == 3);
		assert(g[3] == 0);
		assert(g[4] == 0);

		// Conversion copy constructor from other Array (Dynamic Array)
		DynamicArray<int> h = { 1, 2, 3 };

		success = false;
		try
		{
			StaticArray<int, 1> i = h; // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> i = h;
		assert(i.Size() == 5);
		assert(i[0] == 1);
		assert(i[1] == 2);
		assert(i[2] == 3);
		assert(i[3] == 0);
		assert(i[4] == 0);

		// Conversion move constructor from other Array (Static Array with different size)
		StaticArray<int, 3> j = { 1, 2, 3 };

		success = false;
		try
		{
			StaticArray<int, 1> k = std::move(j); // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> k = std::move(j);
		assert(k.Size() == 5);
		assert(k[0] == 1);
		assert(k[1] == 2);
		assert(k[2] == 3);
		assert(k[3] == 0);
		assert(k[4] == 0);

		// Conversion move constructor from other Array (Dynamic Array)
		DynamicArray<int> l = { 1, 2, 3 };

		success = false;
		try
		{
			StaticArray<int, 1> m = std::move(l); // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> m = std::move(l);
		assert(m.Size() == 5);
		assert(m[0] == 1);
		assert(m[1] == 2);
		assert(m[2] == 3);
		assert(m[3] == 0);
		assert(m[4] == 0);

		// Conversion copy constructor from initializer list
		StaticArray<int, 3> n = { 1, 2, 3 };
		assert(n.Size() == 3);
		assert(n[0] == 1);
		assert(n[1] == 2);
		assert(n[2] == 3);

		success = false;
		try
		{
			StaticArray<int, 3> o = { 1, 2, 3, 4, 5 }; // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> o = { 1, 2, 3 };
		assert(o.Size() == 5);
		assert(o[0] == 1);
		assert(o[1] == 2);
		assert(o[2] == 3);
		assert(o[3] == 0);
		assert(o[4] == 0);

		// Conversion copy constructor from c-style array
		int p[] = { 1, 2, 3 };
		StaticArray<int, 3> q = p;
		assert(q.Size() == 3);
		assert(q[0] == 1);
		assert(q[1] == 2);
		assert(q[2] == 3);

		success = false;
		try
		{
			StaticArray<int, 1> r = p; // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> r = p;
		assert(r.Size() == 5);
		assert(r[0] == 1);
		assert(r[1] == 2);
		assert(r[2] == 3);
		assert(r[3] == 0);
		assert(r[4] == 0);

		// Conversion copy constructor from raw array
		std::array<int, 3> s = { 1, 2, 3 }; // Using std::array as an example, but can be used to convert any array structure

		success = false;
		try
		{
			StaticArray<int, 1> t(s.data(), s.size()); // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> t(s.data(), s.size());
		assert(t.Size() == 5);
		assert(t[0] == 1);
		assert(t[1] == 2);
		assert(t[2] == 3);
		assert(t[3] == 0);
		assert(t[4] == 0);

		// Conversion move constructor from raw array
		std::array<int, 3> u = { 1, 2, 3 }; // Using std::array as an example, but can be used to convert any array structure
		success = false;
		try
		{
			StaticArray<int, 1> v(u.data(), u.size(), true); // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> v(u.data(), u.size(), true);
		assert(v.Size() == 5);
		assert(v[0] == 1);
		assert(v[1] == 2);
		assert(v[2] == 3);
		assert(v[3] == 0);
		assert(v[4] == 0);
	}

	void UnitTestStaticArrayAssignment()
	{
		// Copy assignment operator
		StaticArray<int, 3> a = { 1, 2, 3 };
		StaticArray<int, 3> b;
		b = a;
		assert(b.Size() == 3);
		assert(b[0] == 1);
		assert(b[1] == 2);
		assert(b[2] == 3);

		// Move assignment operator
		StaticArray<int, 3> c = { 1, 2, 3 };
		StaticArray<int, 3> d;
		d = std::move(c);
		assert(d.Size() == 3);
		assert(d[0] == 1);
		assert(d[1] == 2);
		assert(d[2] == 3);

		// Conversion copy assignment operator from other Array (Static Array with different size)
		StaticArray<int, 3> e = { 1, 2, 3 };

		bool success = false;
		try
		{
			StaticArray<int, 1> f;
			f = e; // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> f;
		f = e;
		assert(f.Size() == 5);
		assert(f[0] == 1);
		assert(f[1] == 2);
		assert(f[2] == 3);
		assert(f[3] == 0);
		assert(f[4] == 0);

		// Conversion copy assignment operator from other Array (Dynamic Array)
		DynamicArray<int> g = { 1, 2, 3 };

		success = false;
		try
		{
			StaticArray<int, 1> h;
			h = g; // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> h;
		h = g;
		assert(h.Size() == 5);
		assert(h[0] == 1);
		assert(h[1] == 2);
		assert(h[2] == 3);
		assert(h[3] == 0);
		assert(h[4] == 0);

		// Conversion move assignment operator from other Array (Static Array with different size)
		StaticArray<int, 3> i = { 1, 2, 3 };

		success = false;
		try
		{
			StaticArray<int, 1> j;
			j = std::move(i); // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> j;
		j = std::move(i);
		assert(j.Size() == 5);
		assert(j[0] == 1);
		assert(j[1] == 2);
		assert(j[2] == 3);
		assert(j[3] == 0);
		assert(j[4] == 0);

		// Conversion move assignment operator from other Array (Dynamic Array)
		DynamicArray<int> k = { 1, 2, 3 };

		success = false;
		try
		{
			StaticArray<int, 1> l;
			l = std::move(k); // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> l;
		l = std::move(k);
		assert(l.Size() == 5);
		assert(l[0] == 1);
		assert(l[1] == 2);
		assert(l[2] == 3);
		assert(l[3] == 0);
		assert(l[4] == 0);

		// Conversion copy assignment operator from initializer list
		success = false;
		try
		{
			StaticArray<int, 1> m;
			m = { 1, 2, 3 }; // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> m;
		m = { 1, 2, 3 };
		assert(m.Size() == 5);
		assert(m[0] == 1);
		assert(m[1] == 2);
		assert(m[2] == 3);
		assert(m[3] == 0);
		assert(m[4] == 0);

		// Conversion copy assignment operator from c-style array
		int n[] = { 1, 2, 3 };
		StaticArray<int, 3> o;
		o = n;
		assert(o.Size() == 3);
		assert(o[0] == 1);
		assert(o[1] == 2);
		assert(o[2] == 3);

		success = false;
		try
		{
			StaticArray<int, 1> p;
			p = n; // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 5> p;
		p = n;
		assert(p.Size() == 5);
		assert(p[0] == 1);
		assert(p[1] == 2);
		assert(p[2] == 3);
		assert(p[3] == 0);
		assert(p[4] == 0);
	}

	void UnitTestStaticArrayOperators()
	{
		// Addition operator - concatenates two Static Arrays
		StaticArray<int, 3> a = { 1, 2, 3 };
		StaticArray<int, 3> b = { 4, 5, 6 };
		StaticArray<int, 6> c = a + b;
		assert(c.Size() == 6);
		assert(c[0] == 1);
		assert(c[1] == 2);
		assert(c[2] == 3);
		assert(c[3] == 4);
		assert(c[4] == 5);
		assert(c[5] == 6);

		StaticArray<int, 2> d = { 4, 5 };
		StaticArray<int, 5> e = a + d;
		assert(e.Size() == 5);
		assert(e[0] == 1);
		assert(e[1] == 2);
		assert(e[2] == 3);
		assert(e[3] == 4);
		assert(e[4] == 5);

		// Addition operator - concatenates a Static Array and a c-style array
		int f[] = { 1, 2, 3 };
		StaticArray<int, 3> g = { 4, 5, 6 };
		StaticArray<int, 6> h = g + f;
		assert(h.Size() == 6);
		assert(h[0] == 4);
		assert(h[1] == 5);
		assert(h[2] == 6);
		assert(h[3] == 1);
		assert(h[4] == 2);
		assert(h[5] == 3);

		// Addition operator - concatenates a c-style array and a Static Array
		h = f + g;
		assert(h.Size() == 6);
		assert(h[0] == 1);
		assert(h[1] == 2);
		assert(h[2] == 3);
		assert(h[3] == 4);
		assert(h[4] == 5);
		assert(h[5] == 6);

		// Index operator
		StaticArray<int, 3> i = { 1, 2, 3 };
		assert(i[0] == 1);
		bool success = false;
		try
		{
			int j = i[3]; // Array index out of bounds
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		// Index operator (const version)
		const StaticArray<int, 3> j = { 1, 2, 3 };
		assert(j[0] == 1);
		success = false;
		try
		{
			const int k = j[3]; // Array index out of bounds
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		// Equality operator
		StaticArray<int, 3> l = { 1, 2, 3 };
		StaticArray<int, 3> m = { 1, 2, 3 };
		assert(l == m);
		DynamicArray<int> n = { 1, 2, 3 };
		assert(m == n);

		// Equality operator with c-style array
		StaticArray<int, 3> o = { 1, 2, 3 };
		int p[] = { 1, 2, 3 };
		assert(o == p);
		assert(p == o);

		// Inequality operator
		StaticArray<int, 3> q = { 1, 2, 3 };
		StaticArray<int, 3> r = { 4, 5, 6 };
		assert(q != r);
		DynamicArray<int> s = { 7, 8, 9 };
		assert(r != s);

		// Inequality operator with c-style array
		StaticArray<int, 3> t = { 1, 2, 3 };
		int u[] = { 4, 5, 6 };
		assert(t != u);
		assert(u != t);
	}

	void UnitTestStaticArrayMethods()
	{
		// Data method
		StaticArray<int, 3> a = { 1, 2, 3 };
		int* b = a.Data();
		assert(b[0] == 1);
		assert(b[1] == 2);
		assert(b[2] == 3);

		// Data method (const version)
		const StaticArray<int, 3> c = { 1, 2, 3 };
		const int* d = c.Data();
		assert(d[0] == 1);
		assert(d[1] == 2);
		assert(d[2] == 3);

		// Remove all method
		StaticArray<int, 3> e = { 1, 2, 3 };
		e.RemoveAll(); // Resets all elements to default values
		assert(e[0] == 0);
		assert(e[1] == 0);
		assert(e[2] == 0);

		// Size method
		StaticArray<int, 3> f = { 1, 2, 3 };
		assert(f.Size() == 3);

		// Static size method (constexpr)
		StaticArray<int, f.StaticSize()> g;
		assert(g.Size() == 3);

		// Ranged-based for loop support
		StaticArray<int, 3> h;
		for (int& element : h)
		{
			element = 1;
		}
		assert(h[0] == 1);
		assert(h[1] == 1);
		assert(h[2] == 1);

		const StaticArray<int, 3> i = { 1, 1, 1 };
		for (const int& element : i)
		{
			assert(element == 1);
		}

		// Contains method
		StaticArray<int, 3> j = { 1, 2, 3 };
		assert(j.Contains(2));
		assert(!j.Contains(4));

		// Copy method
		std::array<int, 3> k = { 1, 2, 3 }; // Using std::array as an example, but can be used to convert any array structure

		bool success = false;
		try
		{
			StaticArray<int, 1> l;
			l.Copy(k.data(), k.size()); // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 3> l;
		l.Copy(k.data(), k.size());
		assert(l[0] == 1);
		assert(l[1] == 2);
		assert(l[2] == 3);

		// Count method
		StaticArray<int, 5> m = { 1, 2, 2, 2, 3 };
		assert(m.Count(2) == 3);

		StaticArray<int*, 3> n{};
		assert(n.Count(nullptr) == 3);

		StaticArray<int, 5> o = { 1, 2, 3, 4, 5 };
		assert(o.Count([](const int& element) { return element % 2 == 1; }) == 3);

		// Delete all method
		int* p = new int();
		int* q = new int();
		int* r = new int();
		StaticArray<int*, 3> s = { p, q, r };
		s.DeleteAll(); // If element type is not a pointer then automatically calls remove all method instead
		assert(s[0] == nullptr);
		assert(s[1] == nullptr);
		assert(s[2] == nullptr);

		// Equals method
		StaticArray<int, 3> t = { 1, 2, 3 };
		std::array<int, 3> u = { 1, 2, 3 }; // Using std::array as an example, but can be used to compare with any array structure
		assert(t.Equals(u.data(), u.size()));

		// Fill method
		StaticArray<int, 3> v;
		v.Fill(1);
		assert(v[0] == 1);
		assert(v[1] == 1);
		assert(v[2] == 1);

		// Find method
		StaticArray<int, 3> w = { 1, 2, 3 };
		assert(w.Find([](const int& element) { return element < 3; }));
		assert(!w.Find([](const int& element) { return element > 3; }));

		// Indexof method
		StaticArray<int, 3> x = { 1, 2, 3 };
		assert(x.IndexOf(2) == 1);
		assert(x.IndexOf(4) == x.Size());
		assert(x.IndexOf([](const int& element) { return element > 2; }) == 2);

		StaticArray<int*, 3> y{};
		assert(y.IndexOf(nullptr) == 0);

		// Move method
		std::array<int, 3> z = { 1, 2, 3 }; // Using std::array as an example, but can be used to convert any array structure

		success = false;
		try
		{
			StaticArray<int, 1> aa;
			aa.Move(z.data(), z.size()); // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		StaticArray<int, 3> aa;
		aa.Move(z.data(), z.size());
		assert(aa[0] == 1);
		assert(aa[1] == 2);
		assert(aa[2] == 3);

		// Replace method
		StaticArray<int, 3> ab = { 1, 2, 3 };
		ab.Replace(2, 4);
		assert(ab[0] == 1);
		assert(ab[1] == 4);
		assert(ab[2] == 3);

		StaticArray<int*, 3> ac{};
		int* ad = new int();
		ac.Replace(nullptr, ad);
		assert(ac[0] == ad);
		assert(ac[1] == ad);
		assert(ac[2] == ad);
		delete ad;

		StaticArray<int, 3> ae = { 1, 2, 3 };
		ae.Replace([](const int& element) { return element % 2 == 1; }, 4);
		assert(ae[0] == 4);
		assert(ae[1] == 2);
		assert(ae[2] == 4);

		// Reverse method
		StaticArray<int, 3> af = { 1, 2, 3 };
		af.Reverse();
		assert(af[0] == 3);
		assert(af[1] == 2);
		assert(af[2] == 1);

		// Reverse find method
		StaticArray<int, 3> ag = { 1, 2, 3 };
		assert(ag.ReverseFind([](const int& element) { return element < 3; }));
		assert(!ag.ReverseFind([](const int& element) { return element > 3; }));

		// Reverse indexof method
		StaticArray<int, 4> ah = { 1, 2, 2, 3 };
		assert(ah.ReverseIndexOf(2) == 2);
		assert(ah.ReverseIndexOf(4) == ah.Size());
		assert(ah.ReverseIndexOf([](const int& element) { return element < 3; }) == 2);

		// Shuffle method
		StaticArray<int, 10> ai = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		srand(static_cast<unsigned int>(time(nullptr))); // Seed random number generator
		ai.Shuffle();
		StaticArray<int, 10> aj = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		assert(ai != aj); // This may still assert due to the nature of randomness but would be extremely unlikely

		// Sort method
		StaticArray<int, 3> ak = { 3, 1, 2 };
		ak.Sort(); // Insertion sort < 10 elements
		assert(ak[0] == 1);
		assert(ak[1] == 2);
		assert(ak[2] == 3);

		StaticArray<int, 10> al = { 3, 1, 2, 7, 10, 9, 6, 8, 5, 4 };
		al.Sort(); // Quick sort >= 10 elements
		assert(al[0] == 1);
		assert(al[1] == 2);
		assert(al[2] == 3);
		assert(al[3] == 4);
		assert(al[4] == 5);
		assert(al[5] == 6);
		assert(al[6] == 7);
		assert(al[7] == 8);
		assert(al[8] == 9);
		assert(al[9] == 10);

		StaticArray<int, 3> am = { 1, 2, 3 };
		am.Sort([](const int& left, const int& right) { return left % 2 == 1 && right % 2 == 0; });
		assert(am[0] == 1);
		assert(am[1] == 3);
		assert(am[2] == 2);

		// Swap method
		StaticArray<int, 3> an = { 1, 2, 3 };
		an.Swap(0, 2);
		assert(an[0] == 3);
		assert(an[1] == 2);
		assert(an[2] == 1);
	}

	void UnitTestStaticArrayZero()
	{
		// Default constructor
		StaticArray<int, 0> a{};

		// Addition operator - concatenates two Static Arrays
		StaticArray<int, 3> b = { 1, 2, 3 };
		StaticArray<int, 3> c = a + b;
		assert(c[0] == 1);
		assert(c[1] == 2);
		assert(c[2] == 3);
		c = b + a;
		assert(c[0] == 1);
		assert(c[1] == 2);
		assert(c[2] == 3);

		// Addition operator - concatenates a Static Array and a c-style array
		int d[] = { 1, 2, 3 };
		c = a + d;
		assert(c[0] == 1);
		assert(c[1] == 2);
		assert(c[2] == 3);

		// Addition operator - concatenates a c-style array and a Static Array
		c = d + a;
		assert(c[0] == 1);
		assert(c[1] == 2);
		assert(c[2] == 3);

		// Equality operator
		StaticArray<int, 0> e;
		assert(a == e);
		DynamicArray<int> f;
		assert(a == f);

		// Inequality operator
		StaticArray<int, 3> g = { 1, 2, 3 };
		assert(a != g);
		DynamicArray<int> h = { 1, 2, 3 };
		assert(a != h);

		// Inequality operator with c-style array
		int i[] = { 1, 2, 3 };
		assert(a != i);

		// Data method
		assert(a.Data() == nullptr);

		// Data method (const version)
		const StaticArray<int, 0> j;
		assert(j.Data() == nullptr);

		// Size method
		assert(a.Size() == 0);

		// Static size method (constexpr)
		StaticArray<int, a.StaticSize()> k;
		assert(k.Size() == 0);

		// Copy method
		std::array<int, 3> l = { 1, 2, 3 }; // Using std::array as an example, but can be used to convert any array structure

		bool success = false;
		try
		{
			a.Copy(l.data(), l.size()); // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		// Equals method
		std::array<int, 3> m = { 1, 2, 3 }; // Using std::array as an example, but can be used to compare with any array structure
		assert(!a.Equals(m.data(), m.size()));

		// Move method
		std::array<int, 3> n = { 1, 2, 3 }; // Using std::array as an example, but can be used to convert any array structure

		success = false;
		try
		{
			a.Move(n.data(), n.size()); // Invalid - destination array cannot be smaller than source array
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		// Other compatibility tests
		StaticArray<int, 3> o = a;
		assert(o[0] == 0);
		assert(o[1] == 0);
		assert(o[2] == 0);
		StaticArray<int, 3> p = std::move(a);
		assert(p[0] == 0);
		assert(p[1] == 0);
		assert(p[2] == 0);
		StaticArray<int, 0> q;
		p = q;
		assert(p[0] == 0);
		assert(p[1] == 0);
		assert(p[2] == 0);
		p = std::move(q);
		assert(p[0] == 0);
		assert(p[1] == 0);
		assert(p[2] == 0);
		StaticArray<int, 0> r;
		StaticArray<int, 3> s(r.Data(), r.Size());
		assert(s[0] == 0);
		assert(s[1] == 0);
		assert(s[2] == 0);
		StaticArray<int, 3> t(r.Data(), r.Size(), true);
		assert(t[0] == 0);
		assert(t[1] == 0);
		assert(t[2] == 0);
		StaticArray<int, 0> u;
		t.Copy(u.Data(), u.Size());
		assert(t[0] == 0);
		assert(t[1] == 0);
		assert(t[2] == 0);
		assert(!t.Equals(u.Data(), u.Size()));
		t.Move(u.Data(), u.Size());
		assert(t[0] == 0);
		assert(t[1] == 0);
		assert(t[2] == 0);
	}
}