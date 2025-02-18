#include "../inc/PmergeMe.hpp"

void pmerge(std::vector<int> &vec, int lvl, size_t &counter)
{
	size_t range = pow(2, lvl);
	auto b = vec.begin() + range - 1;
	auto a = b + range;
	while (a < vec.end() && b < vec.end())
	{
		counter++;
		if (*a < *b)
		{
			if (range == 1)
				std::iter_swap(b, a);
			else
				std::swap_ranges(a - (range -1), a + 1, b - (range - 1));
		}
		a += range * 2;
		b += range * 2;
	}
	if (vec.size() >= 2 * pow(2, lvl + 1))
		pmerge(vec, lvl + 1, counter);
	//half of recursion is done, now comes the second part

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
	b = vec.begin() + range - 1;
	a = b + range;
	//dividing the main vector vec into vec and bline
	for (std::vector<int>::iterator it = a + range; it < vec.end(); it += range)
	{
		// std::cout<<"it: "<<*it<<std::endl;
		bline.insert(bline.end(), it - (range - 1), it + 1);
		vec.erase(it - (range - 1), it + 1);
	}
	// now i have 3 extra vectors:
	// - vec, where everything is sorted correctly
	// - bline where all b's are to be sorted into vec,
	// - index_tracker to know which an is at which index to sort the coresponding bn in a binary serach only until index of an.

	// i have to sort b's according to the jacobbsthal numbers for minimum maximum comparisons for bn.
	// so i start with b3 then b2. then next jacobsthal number is 5 so i sort b5, then b4.
	// Next JN in 11 so i sort b10, b9, b8, b7, b6. and so on.
	size_t	current_jacobsthal;
	size_t	previous_jacobsthal;
	std::vector<int>::iterator	iter_to_insert_before;
	size_t	bn_index;
	std::vector<int>::iterator bn_line_iter;
	std::vector<int>::iterator last;
	int new_index_of_bn_in_vec;
	while (bline.size() != 0)
	{
		current_jacobsthal = jacobsthal(0);
		previous_jacobsthal = jacobsthal(2);
		// if there are less b ranges left in bline than the next insertion would start from
		if ((bline.size() / range) < current_jacobsthal - previous_jacobsthal)
		{
			current_jacobsthal = bline.size() / range + previous_jacobsthal;
			bn_line_iter = bline.end() - 1;
		}
		else
			bn_line_iter = (bline.begin() -1 ) + ((current_jacobsthal - previous_jacobsthal) * range);
			//the index of the current range of bn = (bn-range, bn)
			//b1 is already on mainline so bn line starts with bn_index 2 at range index 0 (begin + (range - 1)) -> jacobsthal - 2
		while (current_jacobsthal > previous_jacobsthal)
		{
			bn_index = (current_jacobsthal - 1) * 2;
			//in case the rest of the sequence is enough to build its own element blast
			if (bn_index + 1 < index_tracker.size())
				last = vec.begin() + (range - 1) + index_tracker[bn_index + 1] * range;
			else
				last = vec.end() - 1;
			//returns the iter where iter - range is the actual index where in vec range of (bn - range, bn) should be inserted
			iter_to_insert_before = binary_search(vec, last, *bn_line_iter, counter, range);
			// case for inserting after last index but last is not the last range index of vec.
			if (iter_to_insert_before != vec.end())
				iter_to_insert_before -= (range - 1);
			else if (iter_to_insert_before == vec.end() && last != vec.end() - 1)
				iter_to_insert_before = last + 1;
			new_index_of_bn_in_vec = (iter_to_insert_before - vec.begin()) / range;
			// in case the element gets added to the end of vec, its index needs to be increased 
			if (iter_to_insert_before == vec.end() || new_index_of_bn_in_vec < 0)
				new_index_of_bn_in_vec++;

			//			actual index in vec to insert |	range index current bn
			vec.insert(iter_to_insert_before, bn_line_iter - (range - 1), bn_line_iter + 1);
			//removing the just inserted bn from bline
			bline.erase(bn_line_iter - (range - 1), bn_line_iter + 1);
			//updating the tracker indeces of all a's and b's with a index equal or higher than nwe index of bn
			//also giving bn a valid value
			for (auto it = index_tracker.begin(); it < index_tracker.end(); it++)
			{
				if ((*it >= 0 )&& (*it >= new_index_of_bn_in_vec))
					(*it)++;
				if (it == index_tracker.begin() + bn_index)
					*it = new_index_of_bn_in_vec;
			}
			bn_line_iter -= range;
			current_jacobsthal--;
		}
	}
	(void)jacobsthal(1);
}

//  "7", " 8", "16", "21", "18", "13", " 6", "14", "11", " 9", " 1", "12", " 5", "10", " 3", "20", " 4", "19", "15", "17", " 2"