#include <rsvector.hpp>

namespace test
{
	int
	rsvector()
	{
		Vector<int> v;
		
		for (int i = 0; i < 100; ++i)
			v.push_back(i);

		std::cout << v << '\n';
		
		return 0;
	}
}
