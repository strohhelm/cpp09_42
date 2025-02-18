#ifndef PMERGEME_HPP
#define PMERGEME_HPP


#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <regex>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <limits>


void	pmerge(std::vector<int> &vec, int lvl, size_t &count);
void	pmerge(std::deque<int> &deq, int lvl, size_t &count);
size_t	jacobsthal(int mode);

template <typename T>
typename T::iterator binary_search(T &vec, typename T::iterator last, int value, size_t &comp_count, size_t &range)
{
	last -= range;
	typename T::iterator first = vec.begin() + range - 1;
	size_t count = (last - first) / range + 1;
	size_t step;
	typename T::iterator it;

	while (count > 0)
	{
		it = first; 
		step = count / 2;
		std::advance(it, step * range);
		comp_count++;
		if (value > *it)
		{
			it += range;
			first = it;
			count -= step + 1;
		}
		else
			count = step;
	}
	//returns vec.end() for the case of being the biggest number in the array
	if (first == last + range)
		return vec.end();
	return first;
}
#endif