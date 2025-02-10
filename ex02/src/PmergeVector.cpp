#include "../inc/PmergeMe.hpp"

void pmerge(std::vector<int> &vec, int lvl, size_t &count)
{
	size_t range = pow(2, lvl);
	auto b = vec.begin() + range - 1;
	auto a = b + range;
	std::cout<<"range: "<<range<<std::endl;
	while (a < vec.end() && b < vec.end())
	{
		// std::cout<<"a = "<<*a<<" range:";
		// for_each(a - (range-1), a + 1, [](int i){std::cout<<i<<" ";});
		// std::cout<<std::endl;
		// std::cout<<"b = "<<*b<<" range: ";
		// for_each(b - (range -1), b + 1, [](int i){std::cout<<i<<" ";});
		// std::cout<<std::endl;

		if (*a < *b)
		{
			if (range == 1)
				std::iter_swap(b, a);
			else
				std::swap_ranges(a - (range -1), a + 1, b - (range - 1));
			// std::cout<<"swapped"<<std::endl;
		}
		count++;
		a += range * 2;
		b += range * 2;
		for_each (vec.begin(), vec.end(), [](int i){std::cout<<i<<" ";});
		std::cout<<std::endl;
	}
	std::cout<<"\n\n========== "<<lvl<<" ===========\n"<<std::endl;
	if (vec.size() >= 2 * pow(2, lvl + 1))
		pmerge(vec, lvl + 1, count);

	if ((vec.size() / range )%2 != 0)
		
}

