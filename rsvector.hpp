#if !defined(RSVECTOR_H)

#include <iostream>
#include <memory>
#include <time.h>

#define DEFAULT_VECTOR_CAP 32

template<typename T>
class Vector
{
	std::unique_ptr<T[]> v;
	int size;
	int cap;

public:
	Vector()
	{
		size = 0;
		cap = DEFAULT_VECTOR_CAP;
		v = std::make_unique<T[]>(cap);
	}

	Vector(Vector &rhs)
	{
		size = rhs.size;
		cap = rhs.cap;
		v = std::make_unique<T[]>(cap);

		for (int i = 0; i < size; ++i)
			v[i] = rhs.v[i];
	}

	Vector(Vector &&rhs)
	{
		size = rhs.size;
		cap = rhs.cap;
		std::swap(v, rhs.v);
	}

	Vector &
	operator=(Vector &rhs)
	{
		if (rhs.size > cap)
			resize (rhs.size * 2 + 1);

		size = rhs.size;
		v = std::make_unique<T[]>(cap);

		for (int i = 0; i < size; ++i)
			v[i] = rhs.v[i];

		return *this;
	}

	Vector &
	operator=(Vector &&rhs)
	{
		Vector r = std::move(rhs);
		std::swap(*this, r);

		return *this;
	}

	void
	resize(int _newCap)
	{
		if (_newCap < cap)
			return;

		cap = _newCap;
		std::unique_ptr<T[]> pres = std::move(v);
		v = std::make_unique<T[]>(cap);

		for (int i = 0; i < size; ++i)
			v[i] = pres[i];
	}

	void
	push_back(T val)
	{
		if (size >= cap)
			resize (cap * 2 + 1);
		
		v[size++] = val;
	}

	T &operator[](int i)
	{
		return v[i];
	}

	T &operator[](int i) const
	{
		return v[i];
	}
	
	template<typename _T>
	friend std::ostream &operator<<(std::ostream &, const Vector<_T> &);

	~Vector()
	{
		v.reset();
	}

};

template<typename T>
std::ostream &
operator<<(std::ostream &out, const Vector<T> &v)
{
	out << "Vector { size: " << v.size
	    << ", cap: " << v.cap 
	    << "}\n";

	if (v.size)
	{
		out << "{" << v[0];
		
		for (int i = 1; i < v.size; ++i)
			out << ", " << v[i];

		out << "}\n";
	}
	return out;
}

namespace test
{
	int rsvector();

} // test

#endif

