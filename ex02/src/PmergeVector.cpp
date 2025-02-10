#include "../inc/PmergeMe.hpp"

std::vector<int>::iterator binary_search(std::vector<int> &vec, std::vector<int>::iterator last, int value, size_t &counter)
{
	std::vector<int>::iterator it;
	size_t count, step;
	std::vector<int>::iterator first = vec.begin();
	count = last - first;

	while (count > 0)
	{
		it = first;
		step = count / 2;
		std::advance(it, step);
		if (value < *it)
		{
			first = ++it;
			count -= step + 1;
		}
		else
			count = step;
		counter++;
	}
 
	return first;
}
size_t next_jacobsthal(int reset)
{
	static size_t n = 3;
	static size_t jacobsthal = 3;

	jacobsthal = pow(2, n) - jacobsthal;
	n++;
	return jacobsthal;
	if (reset)
	{
		n = 3;
		jacobsthal = 3;
	}
}
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

	b = vec.begin() + range - 1;
	a = b + range;
	size_t num = 0;
	std::vector<int> pend;
	std::vector<int> mainline;
	for (std::vector<int>::iterator it = a + range; it < vec.end(); it += 2 * range)
	{
		pend.insert(pend.end(), it - range, it);
		vec.erase(it - range, it);
	}


	size_t	jacobsthal;
	while (pend.size() != 0)
	{
		jacobsthal = next_jacobsthal(0);
		if (pend.size() < jacobsthal)
			jacobsthal = pend.size() - 1;
		while (jacobsthal >= 0)
		{
			
		}

	
	}
	(void)next_jacobsthal(1);
}

