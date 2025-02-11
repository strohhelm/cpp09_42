#include "../inc/PmergeMe.hpp"


void pmerge(std::vector<int> &vec, int lvl, size_t &counter)
{
	size_t range = pow(2, lvl);
	auto b = vec.begin() + range - 1;
	auto a = b + range;
	std::cout<<"\n\n========== "<<"lvl:"<<lvl<<" ===========\n"<<std::endl;
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
		counter++;
		a += range * 2;
		b += range * 2;
		// std::cout<<std::endl;
	}
	if (vec.size() >= 2 * pow(2, lvl + 1))
		pmerge(vec, lvl + 1, counter);
	std::cout<<"\n\n========== "<<"lvl:"<<lvl<<" ===========\n"<<std::endl;

	// std::cout<<"After recursion:"<<std::endl;
	for_each (vec.begin(), vec.end(), [](int i){std::cout<<i<<" ";});
	std::cout <<std::endl;

	//half of recursion is done, now comes the second part

	b = vec.begin() + range - 1;
	a = b + range;
	
	std::cout<<"a = "<<*a<<std::endl;
	std::cout<<"b = "<<*b<<std::endl;

	//making a vactor for index tracking that holds the values of the coresponding indexes in the vec {b1, a1, b2, a2, ....,bn,an}
	//after every insert, all indeces biger or equal than found index are increased by one
	std::vector<int> bline;
	std::vector<int> index_tracker( vec.size() / range, -1);
	index_tracker[0] = 0;
	size_t index = 1;


	//filling index_tracker with initial indeces for b1 and all a's.
	//all b's from b1 and higher are set to -1 to indicate they are not sorted yet.
	for(size_t i = 1; i <index_tracker.size(); i += 2)
		index_tracker[i] = index++;


	//dividing the main vector vec into vec and bline
	for (std::vector<int>::iterator it = a + range; it < vec.end(); it += range)
	{
		std::cout<<"it: "<<*it<<std::endl;
		bline.insert(bline.end(), it - (range - 1), it + 1);
		vec.erase(it - (range - 1), it + 1);
	}

	std::cout << "Contents of vec:"<<std::endl;
	for_each (vec.begin(), vec.end(), [](int i){std::cout<<i<<" | ";});
	std::cout <<std::endl;
	std::cout << "Contents of bline:"<<std::endl;
	for_each (bline.begin(), bline.end(), [](int i){std::cout<<i<<" | ";});
	std::cout <<std::endl;
	std::cout << "Contents of index_tracker:"<<std::endl;
	for_each (index_tracker.begin(), index_tracker.end(), [](int i){std::cout<<i<<" | ";});
	std::cout <<std::endl;

	

	// now i have 3 extra vectors:
	// - vec, where everything is sorted correctly
	// - bline where all b's are to be sorted into vec,
	// - index_tracker to know which an is at which index to sort the coresponding bn in a binary serach only until index of an.

	// i have to sort b's according to the jacobbsthal numbers for minimum maximum comparisons for bn.
	// so i start with b3 then b2. then next jacobsthal number is 5 so i sort b5, then b4.
	// Next JN in 11 so i sort b10, b9, b8, b7, b6. and so on.

	size_t	jacobsthal;
	std::vector<int>::iterator	iter_to_insert_before;
	size_t	bn_index;
	std::vector<int>::iterator bn_line_iter;
	std::vector<int>::iterator last;
	while (bline.size() != 0)
	{
		jacobsthal = next_jacobsthal(0);
		if (bline.size() < jacobsthal)
			jacobsthal = bline.size() - 1;
		bn_line_iter = bline.begin() + ((jacobsthal - 1) * range  - 1); // bc index 0 (b1) and 1 (a1) are already pushed to vec. index
		while (jacobsthal > 1)
		{
			bn_index = (jacobsthal - 1) * 2;
			if (bn_index + 1 < index_tracker.size())
				last = vec.begin() + index_tracker[bn_index + 1];
			else
				last = vec.end() - 1;
			iter_to_insert_before = binary_search(vec, last, *bn_line_iter, counter, range);
			int new_index_of_bn_in_vec = iter_to_insert_before - vec.begin();
			vec.insert(iter_to_insert_before, bline.begin() + bn_index - range, bline.begin() + bn_index);
			bline.erase(bline.begin() + bn_index - range, bline.begin() + bn_index);
			for (auto it = index_tracker.begin(); it < index_tracker.end(); it++)
			{
				if (*it >= 0 && *it >= new_index_of_bn_in_vec)
					(*it)++;
				if (it == index_tracker.begin() + bn_index)
					*it = new_index_of_bn_in_vec;
			}
			bn_line_iter -= range;
			jacobsthal--;

			// std::cout << "Contents of vec:"<<std::endl;
			// for_each (vec.begin(), vec.end(), [](int i){std::cout<<i<<" | ";});
			// std::cout <<std::endl;
			// std::cout << "Contents of bline:"<<std::endl;
			// for_each (bline.begin(), bline.end(), [](int i){std::cout<<i<<" | ";});
			// std::cout <<std::endl;
			// std::cout << "Contents of index_tracker:"<<std::endl;
			// for_each (index_tracker.begin(), index_tracker.end(), [](int i){std::cout<<i<<" | ";});
			// std::cout <<std::endl;
		}
	}
	(void)next_jacobsthal(1);
}

