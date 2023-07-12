#include "UnitTestDynamicArray.h"

#include <cassert>
#include <ctime>
#include <vector>

#include "DynamicArray.h"
#include "StaticArray.h"

namespace UnitTests
{
	void UnitTestDynamicArrayConstructors();
	void UnitTestDynamicArrayAssignment();
	void UnitTestDynamicArrayOperators();
	void UnitTestDynamicArrayMethods();

	void UnitTestDynamicArray()
	{
		UnitTestDynamicArrayConstructors();
		UnitTestDynamicArrayAssignment();
		UnitTestDynamicArrayOperators();
		UnitTestDynamicArrayMethods();
	}

	void UnitTestDynamicArrayConstructors()
	{
		// Default constructor
		DynamicArray<int> a;
		assert(a.Size() == 0);
		assert(a.Capacity() == 0);

		// Constructor with capacity argument
		DynamicArray<int> b(3);
		assert(b.Size() == 0);
		assert(b.Capacity() == 3);

		// Copy constructor
		DynamicArray<int> c = { 1, 2, 3 };
		DynamicArray<int> d = c;
		assert(d.Size() == 3);
		assert(d.Capacity() == 3);
		assert(d[0] == 1);
		assert(d[1] == 2);
		assert(d[2] == 3);

		// Move constructor
		DynamicArray<int> e = { 1, 2, 3 };
		DynamicArray<int> f = std::move(e);
		assert(e.Size() == 0);
		assert(e.Capacity() == 0);
		assert(f.Size() == 3);
		assert(f.Capacity() == 3);
		assert(f[0] == 1);
		assert(f[1] == 2);
		assert(f[2] == 3);

		// Conversion copy constructor from other Array (Static Array)
		StaticArray<int, 3> g = { 1, 2, 3 };
		DynamicArray<int> h = g;
		assert(h.Size() == 3);
		assert(h.Capacity() == 3);
		assert(h[0] == 1);
		assert(h[1] == 2);
		assert(h[2] == 3);

		// Conversion move constructor from other Array (Static Array)
		StaticArray<int, 3> i = { 1, 2, 3 };
		DynamicArray<int> j = std::move(i);
		assert(j.Size() == 3);
		assert(j.Capacity() == 3);
		assert(j[0] == 1);
		assert(j[1] == 2);
		assert(j[2] == 3);

		// Conversion copy constructor from initializer list
		DynamicArray<int> k = { 1, 2, 3 };
		assert(k.Size() == 3);
		assert(k.Capacity() == 3);
		assert(k[0] == 1);
		assert(k[1] == 2);
		assert(k[2] == 3);

		// Conversion copy constructor from c-style array
		int l[] = { 1, 2, 3 };
		DynamicArray<int> m = l;
		assert(m.Size() == 3);
		assert(m.Capacity() == 3);
		assert(m[0] == 1);
		assert(m[1] == 2);
		assert(m[2] == 3);

		// Conversion copy constructor from raw array
		std::vector<int> n = { 1, 2, 3 }; // Using std::vector as an example, but can be used to convert any array structure
		DynamicArray<int> o(n.data(), n.size());
		assert(o.Size() == 3);
		assert(o.Capacity() == 3);
		assert(o[0] == 1);
		assert(o[1] == 2);
		assert(o[2] == 3);

		// Conversion move constructor from raw array
		std::vector<int> p = { 1, 2, 3 }; // Using std::vector as an example, but can be used to convert any array structure
		DynamicArray<int> q(p.data(), p.size(), true);
		assert(q.Size() == 3);
		assert(q.Capacity() == 3);
		assert(q[0] == 1);
		assert(q[1] == 2);
		assert(q[2] == 3);
	}

	void UnitTestDynamicArrayAssignment()
	{
		// Copy assignment operator
		DynamicArray<int> a = { 1, 2, 3 };
		DynamicArray<int> b;
		b = a;
		assert(b.Size() == 3);
		assert(b.Capacity() == 3);
		assert(b[0] == 1);
		assert(b[1] == 2);
		assert(b[2] == 3);

		// Move assignment operator
		DynamicArray<int> c = { 1, 2, 3 };
		DynamicArray<int> d;
		d = std::move(c);
		assert(c.Size() == 0);
		assert(c.Capacity() == 0);
		assert(d.Size() == 3);
		assert(d.Capacity() == 3);
		assert(d[0] == 1);
		assert(d[1] == 2);
		assert(d[2] == 3);

		// Conversion copy assignment operator from other Array (Static Array)
		StaticArray<int, 3> e = { 1, 2, 3 };
		DynamicArray<int> f;
		f = e;
		assert(f.Size() == 3);
		assert(f.Capacity() == 3);
		assert(f[0] == 1);
		assert(f[1] == 2);
		assert(f[2] == 3);

		// Conversion move assignment operator from other Array (Static Array)
		StaticArray<int, 3> g = { 1, 2, 3 };
		DynamicArray<int> h;
		h = std::move(g);
		assert(h.Size() == 3);
		assert(h.Capacity() == 3);
		assert(h[0] == 1);
		assert(h[1] == 2);
		assert(h[2] == 3);

		// Conversion copy assignment operator from initializer list
		DynamicArray<int> i;
		i = { 1, 2, 3 };
		assert(i.Size() == 3);
		assert(i.Capacity() == 3);
		assert(i[0] == 1);
		assert(i[1] == 2);
		assert(i[2] == 3);

		// Conversion copy assignment operator from c-style array
		int j[] = { 1, 2, 3 };
		DynamicArray<int> k;
		k = j;
		assert(k.Size() == 3);
		assert(k.Capacity() == 3);
		assert(k[0] == 1);
		assert(k[1] == 2);
		assert(k[2] == 3);

		// Addition assignment operator - concatenates the Dynamic Array and another Array (Dynamic Array)
		DynamicArray<int> l = { 1, 2, 3 };
		DynamicArray<int> m = { 4, 5, 6 };
		l += m;
		assert(l.Size() == 6);
		assert(l.Capacity() == 6);
		assert(l[0] == 1);
		assert(l[1] == 2);
		assert(l[2] == 3);
		assert(l[3] == 4);
		assert(l[4] == 5);
		assert(l[5] == 6);

		// Addition assignment operator - concatenates the Dynamic Array and another Array (Static Array)
		DynamicArray<int> n = { 1, 2, 3 };
		StaticArray<int, 3> o = { 4, 5, 6 };
		n += o;
		assert(n.Size() == 6);
		assert(n.Capacity() == 6);
		assert(n[0] == 1);
		assert(n[1] == 2);
		assert(n[2] == 3);
		assert(n[3] == 4);
		assert(n[4] == 5);
		assert(n[5] == 6);

		// Addition assignment operator - concatenates the Dynamic Array and an initializer list
		DynamicArray<int> p = { 1, 2, 3 };
		p += { 4, 5, 6 };
		assert(p.Size() == 6);
		assert(p.Capacity() == 6);
		assert(p[0] == 1);
		assert(p[1] == 2);
		assert(p[2] == 3);
		assert(p[3] == 4);
		assert(p[4] == 5);
		assert(p[5] == 6);

		// Addition assignment operator - concatenates the Dynamic Array and a c-style array
		DynamicArray<int> q = { 1, 2, 3 };
		int r[] = { 4, 5, 6 };
		q += r;
		assert(q.Size() == 6);
		assert(q.Capacity() == 6);
		assert(q[0] == 1);
		assert(q[1] == 2);
		assert(q[2] == 3);
		assert(q[3] == 4);
		assert(q[4] == 5);
		assert(q[5] == 6);
	}

	void UnitTestDynamicArrayOperators()
	{
		// Addition operator - concatenates two Arrays (Dynamic Array + Dynamic Array)
		DynamicArray<int> a = { 1, 2, 3 };
		DynamicArray<int> b = { 4, 5, 6 };
		DynamicArray<int> c = a + b;
		assert(c.Size() == 6);
		assert(c.Capacity() == 6);
		assert(c[0] == 1);
		assert(c[1] == 2);
		assert(c[2] == 3);
		assert(c[3] == 4);
		assert(c[4] == 5);
		assert(c[5] == 6);

		// Addition operator - concatenates two Arrays (Dynamic Array + Static Array)
		StaticArray<int, 3> d = { 1, 2, 3 };
		DynamicArray<int> e = { 4, 5, 6 };
		DynamicArray<int> f = d + e;
		assert(f.Size() == 6);
		assert(f.Capacity() == 6);
		assert(f[0] == 1);
		assert(f[1] == 2);
		assert(f[2] == 3);
		assert(f[3] == 4);
		assert(f[4] == 5);
		assert(f[5] == 6);

		f = e + d;
		assert(f.Size() == 6);
		assert(f.Capacity() == 6);
		assert(f[0] == 4);
		assert(f[1] == 5);
		assert(f[2] == 6);
		assert(f[3] == 1);
		assert(f[4] == 2);
		assert(f[5] == 3);

		// Addition operator - concatenates two Arrays (Static Array + Static Array)
		StaticArray<int, 3> g = { 1, 2, 3 };
		StaticArray<int, 3> h = { 4, 5, 6 };
		DynamicArray<int> i = g + h;
		assert(i.Size() == 6);
		assert(i.Capacity() == 6);
		assert(i[0] == 1);
		assert(i[1] == 2);
		assert(i[2] == 3);
		assert(i[3] == 4);
		assert(i[4] == 5);
		assert(i[5] == 6);

		// Addition operator - concatenates a Dynamic Array and a c-style array
		int j[] = { 1, 2, 3 };
		DynamicArray<int> k = { 4, 5, 6 };
		DynamicArray<int> l = j + k;
		assert(l.Size() == 6);
		assert(l.Capacity() == 6);
		assert(l[0] == 1);
		assert(l[1] == 2);
		assert(l[2] == 3);
		assert(l[3] == 4);
		assert(l[4] == 5);
		assert(l[5] == 6);

		l = k + j;
		assert(l.Size() == 6);
		assert(l.Capacity() == 6);
		assert(l[0] == 4);
		assert(l[1] == 5);
		assert(l[2] == 6);
		assert(l[3] == 1);
		assert(l[4] == 2);
		assert(l[5] == 3);

		// Index operator
		DynamicArray<int> m = { 1, 2, 3 };
		assert(m[0] == 1);
		bool success = false;
		try
		{
			int n = m[3]; // Array index out of bounds
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		// Index operator (const version)
		const DynamicArray<int> n = { 1, 2, 3 };
		assert(n[0] == 1);
		success = false;
		try
		{
			int o = n[3]; // Array index out of bounds
		}
		catch (const std::exception&)
		{
			success = true;
		}
		assert(success);

		// Equality operator
		DynamicArray<int> o = { 1, 2, 3 };
		DynamicArray<int> p = { 1, 2, 3 };
		assert(o == p);
		StaticArray<int, 3> q = { 1, 2, 3 };
		assert(p == q);

		// Equality operator with c-style array
		DynamicArray<int> r = { 1, 2, 3 };
		int s[] = { 1, 2, 3 };
		assert(r == s);
		assert(s == r);

		// Inequality operator
		DynamicArray<int> t = { 1, 2, 3 };
		DynamicArray<int> u = { 4, 5, 6 };
		assert(t != u);
		StaticArray<int, 3> v = { 7, 8, 9 };
		assert(u != v);

		// Inequality operator with c-style array
		DynamicArray<int> w = { 1, 2, 3 };
		int x[] = { 4, 5, 6 };
		assert(w != x);
		assert(x != w);
	}

	void UnitTestDynamicArrayMethods()
	{
		// Add method (element)
		DynamicArray<int> a;
		assert(a.Size() == 0);
		a.Add(1);
		assert(a.Size() == 1);
		assert(a[0] == 1);

		// Add method (other Array - Dynamic Array)
		DynamicArray<int> b;
		DynamicArray<int> c = { 1, 2, 3 };
		b.Add(c);
		assert(b.Size() == 3);
		assert(b[0] == 1);
		assert(b[1] == 2);
		assert(b[2] == 3);

		// Add method (other Array - Static Array)
		StaticArray<int, 3> d = { 4, 5, 6 };
		b.Add(d);
		assert(b.Size() == 6);
		assert(b[3] == 4);
		assert(b[4] == 5);
		assert(b[5] == 6);

		// Add method (c-style array)
		DynamicArray<int> e;
		int f[] = { 1, 2, 3 };
		e.Add(f);
		assert(e.Size() == 3);
		assert(e[0] == 1);
		assert(e[1] == 2);
		assert(e[2] == 3);

		// Add method (raw array)
		DynamicArray<int> g;
		std::vector<int> h = { 1, 2, 3 }; // Using std::vector as an example, but can be used with any array structure
		g.Add(h.data(), h.size());
		assert(g.Size() == 3);
		assert(g[0] == 1);
		assert(g[1] == 2);
		assert(g[2] == 3);

		// Add unique method
		DynamicArray<int> i = { 1, 2, 3 };
		i.AddUnique(4);
		assert(i.Size() == 4);
		assert(i[0] == 1);
		assert(i[1] == 2);
		assert(i[2] == 3);
		assert(i[3] == 4);
		i.AddUnique(3); // Array already contains element
		assert(i.Size() == 4);
		assert(i[0] == 1);
		assert(i[1] == 2);
		assert(i[2] == 3);
		assert(i[3] == 4);

		// Capacity method
		DynamicArray<int> j = { 1, 2, 3 };
		assert(j.Capacity() == 3);

		// Data method
		DynamicArray<int> k = { 1, 2, 3 };
		int* l = k.Data();
		l[0] = 4;
		assert(k[0] == 4);
		assert(k[1] == 2);
		assert(k[2] == 3);

		// Data method (const version)
		const DynamicArray<int> m = { 1, 2, 3 };
		const int* n = m.Data();
		assert(n[0] == 1);

		// Test struct for emplace methods
		struct Test
		{
			Test() = default;
			Test(int first, int second) : m_first(first), m_second(second) {}

			bool operator==(const Test&) const = default;
			bool operator!=(const Test&) const = default;

			int m_first;
			int m_second;
		};

		// Emplace method
		DynamicArray<Test> o;
		o.Emplace(1, 2);
		assert(o.Size() == 1);
		assert(o[0].m_first == 1);
		assert(o[0].m_second == 2);

		// Emplace at method
		o.EmplaceAt(0, 3, 4);
		assert(o.Size() == 2);
		assert(o[0].m_first == 3);
		assert(o[0].m_second == 4);
		assert(o[1].m_first == 1);
		assert(o[1].m_second == 2);

		// Insert method (element)
		DynamicArray<int> p = { 1, 2, 3 };
		p.Insert(1, 4);
		assert(p.Size() == 4);
		assert(p[0] == 1);
		assert(p[1] == 4);
		assert(p[2] == 2);
		assert(p[3] == 3);

		// Insert method (other Array - Dynamic Array)
		DynamicArray<int> q = { 1, 2, 3 };
		DynamicArray<int> r = { 4, 5, 6 };
		q.Insert(1, r);
		assert(q.Size() == 6);
		assert(q[0] == 1);
		assert(q[1] == 4);
		assert(q[2] == 5);
		assert(q[3] == 6);
		assert(q[4] == 2);
		assert(q[5] == 3);

		// Insert method (other Array - Static Array)
		StaticArray<int, 3> s = { 7, 8, 9 };
		q.Insert(4, s);
		assert(q.Size() == 9);
		assert(q[0] == 1);
		assert(q[1] == 4);
		assert(q[2] == 5);
		assert(q[3] == 6);
		assert(q[4] == 7);
		assert(q[5] == 8);
		assert(q[6] == 9);
		assert(q[7] == 2);
		assert(q[8] == 3);

		// Insert method (c-style array)
		DynamicArray<int> t = { 1, 2, 3 };
		int u[] = { 4, 5, 6 };
		t.Insert(1, u);
		assert(t.Size() == 6);
		assert(t[0] == 1);
		assert(t[1] == 4);
		assert(t[2] == 5);
		assert(t[3] == 6);
		assert(t[4] == 2);
		assert(t[5] == 3);

		// Insert method (raw array)
		DynamicArray<int> v = { 1, 2, 3 };
		std::vector<int> w = { 4, 5, 6 }; // Using std::vector as an example, but can be used with any array structure
		v.Insert(1, w.data(), w.size());
		assert(v.Size() == 6);
		assert(v[0] == 1);
		assert(v[1] == 4);
		assert(v[2] == 5);
		assert(v[3] == 6);
		assert(v[4] == 2);
		assert(v[5] == 3);

		// Insert unique method
		DynamicArray<int> x = { 1, 2, 3 };
		x.InsertUnique(1, 4);
		assert(x.Size() == 4);
		assert(x[0] == 1);
		assert(x[1] == 4);
		assert(x[2] == 2);
		assert(x[3] == 3);
		x.InsertUnique(1, 3); // Array already contains element
		assert(x.Size() == 4);
		assert(x[0] == 1);
		assert(x[1] == 4);
		assert(x[2] == 2);
		assert(x[3] == 3);

		// Remove method
		DynamicArray<int> y = { 1, 2, 3 };
		y.Remove(2);
		assert(y.Size() == 2);
		assert(y[0] == 1);
		assert(y[1] == 3);

		DynamicArray<int*> z = { nullptr };
		z.Remove(nullptr);
		assert(z.Size() == 0);

		DynamicArray<int> aa = { 1, 2, 3 };
		aa.Remove([](const int& element) { return element > 1; });
		assert(aa.Size() == 1);
		assert(aa[0] == 1);

		// Remove all method
		DynamicArray<int> ab = { 1, 2, 3 };
		ab.RemoveAll();
		assert(ab.Size() == 0);

		// Remove at method
		DynamicArray<int> ac = { 1, 2, 3 };
		ac.RemoveAt(1);
		assert(ac.Size() == 2);
		assert(ac[0] == 1);
		assert(ac[1] == 3);

		// Remove duplicates method
		DynamicArray<int> ad = { 1, 2, 2, 2, 3, 3 };
		ad.RemoveDuplicates();
		assert(ad.Size() == 3);
		assert(ad[0] == 1);
		assert(ad[1] == 2);
		assert(ad[2] == 3);

		// Remove range method
		DynamicArray<int> ae = { 1, 2, 3, 4, 5, 6 };
		ae.RemoveRange(2, 4);
		assert(ae.Size() == 3);
		assert(ae[0] == 1);
		assert(ae[1] == 2);
		assert(ae[2] == 6);

		// Resize method
		DynamicArray<int> af;
		assert(af.Capacity() == 0);
		af.Resize(3);
		assert(af.Capacity() == 3);

		// Size method
		assert(af.Size() == 0);

		// Trim method
		DynamicArray<int> ag(6);
		ag.Add(1);
		ag.Add(2);
		ag.Add(3);
		assert(ag.Capacity() == 6);
		ag.Trim();
		assert(ag.Capacity() == 3);

		// Range-based for loop support
		DynamicArray<int> ah(3);
		for (int& element : ah)
		{
			element = 1;
		}

		for (const int& element : ah)
		{
			assert(element == 1);
		}

		// Contains method
		DynamicArray<int> ai = { 1, 2, 3 };
		assert(ai.Contains(2));
		assert(!ai.Contains(4));

		// Copy method
		DynamicArray<int> aj(3);
		std::vector<int> ak = { 1, 2, 3 }; // Using std::vector as an example, but can be used to convert any array structure
		aj.Copy(ak.data(), ak.size());
		assert(aj.Size() == 3);
		assert(aj[0] == 1);
		assert(aj[1] == 2);
		assert(aj[2] == 3);

		// Count method
		DynamicArray<int> al = { 1, 2, 2, 2, 3 };
		assert(al.Count(2) == 3);

		DynamicArray<int*> am(3);
		am.Fill(nullptr);
		assert(am.Count(nullptr) == 3);

		DynamicArray<int> an = { 1, 2, 3, 4, 5 };
		assert(an.Count([](const int& element) { return element % 2 == 1; }) == 3);

		// Delete all method
		int* ao = new int();
		int* ap = new int();
		int* aq = new int();
		DynamicArray<int*> ar = { ao, ap, aq };
		ar.DeleteAll(); // If element type is not a pointer then automatically calls remove all method instead
		assert(ar.Size() == 0);

		// Equals method
		DynamicArray<int> as = { 1, 2, 3 };
		std::vector<int> at = { 1, 2, 3 }; // Using std::vector as an example, but can be used to compare with any array structure
		assert(as.Equals(at.data(), at.size()));

		// Fill method
		DynamicArray<int> au(3);
		au.Fill(1);
		assert(au[0] == 1);
		assert(au[1] == 1);
		assert(au[2] == 1);

		// Find method
		DynamicArray<int> av = { 1, 2, 3 };
		assert(av.Find([](const int& element) { return element < 3; }));
		assert(!av.Find([](const int& element) { return element > 3; }));

		// Indexof method
		DynamicArray<int> aw = { 1, 2, 3 };
		assert(aw.IndexOf(2) == 1);
		assert(aw.IndexOf(4) == aw.Size());
		assert(aw.IndexOf([](const int& element) { return element > 2; }) == 2);

		DynamicArray<int*> ax = { nullptr };
		assert(ax.IndexOf(nullptr) == 0);

		// Move method
		std::vector<int> ay = { 1, 2, 3 }; // Using std::vector as an example, but can be used to convert any array structure
		DynamicArray<int> az(3);
		az.Move(ay.data(), ay.size());
		assert(az[0] == 1);
		assert(az[1] == 2);
		assert(az[2] == 3);

		// Replace method
		DynamicArray<int> ba = { 1, 2, 3 };
		ba.Replace(2, 4);
		assert(ba[0] == 1);
		assert(ba[1] == 4);
		assert(ba[2] == 3);

		DynamicArray<int*> bc(3);
		bc.Fill(nullptr);
		int* bd = new int();
		bc.Replace(nullptr, bd);
		assert(bc[0] == bd);
		assert(bc[1] == bd);
		assert(bc[2] == bd);
		delete bd;

		DynamicArray<int> be = { 1, 2, 3 };
		be.Replace([](const int& element) { return element % 2 == 1; }, 4);
		assert(be[0] == 4);
		assert(be[1] == 2);
		assert(be[2] == 4);

		// Reverse method
		DynamicArray<int> bf = { 1, 2, 3 };
		bf.Reverse();
		assert(bf[0] == 3);
		assert(bf[1] == 2);
		assert(bf[2] == 1);

		// Reverse find method
		DynamicArray<int> bg = { 1, 2, 3 };
		assert(bg.ReverseFind([](const int& element) { return element < 3; }));
		assert(!bg.ReverseFind([](const int& element) { return element > 3; }));

		// Reverse indexof method
		DynamicArray<int> bh = { 1, 2, 2, 3 };
		assert(bh.ReverseIndexOf(2) == 2);
		assert(bh.ReverseIndexOf(4) == bh.Size());
		assert(bh.ReverseIndexOf([](const int& element) { return element < 3; }) == 2);

		// Shuffle method
		DynamicArray<int> bi = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		srand(static_cast<unsigned int>(time(nullptr))); // Seed random number generator
		bi.Shuffle();
		DynamicArray<int> bj = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		assert(bi != bj); // This may still assert due to the nature of randomness but would be extremely unlikely

		// Sort method
		DynamicArray<int> bk = { 3, 1, 2 };
		bk.Sort(); // Insertion sort < 10 elements
		assert(bk[0] == 1);
		assert(bk[1] == 2);
		assert(bk[2] == 3);

		DynamicArray<int> bl = { 3, 1, 2, 7, 10, 9, 6, 8, 5, 4 };
		bl.Sort(); // Quick sort >= 10 elements
		assert(bl[0] == 1);
		assert(bl[1] == 2);
		assert(bl[2] == 3);
		assert(bl[3] == 4);
		assert(bl[4] == 5);
		assert(bl[5] == 6);
		assert(bl[6] == 7);
		assert(bl[7] == 8);
		assert(bl[8] == 9);
		assert(bl[9] == 10);

		DynamicArray<int> bm = { 1, 2, 3 };
		bm.Sort([](const int& left, const int& right) { return left % 2 == 1 && right % 2 == 0; });
		assert(bm[0] == 1);
		assert(bm[1] == 3);
		assert(bm[2] == 2);

		// Swap method
		DynamicArray<int> bn = { 1, 2, 3 };
		bn.Swap(0, 2);
		assert(bn[0] == 3);
		assert(bn[1] == 2);
		assert(bn[2] == 1);
	}
}