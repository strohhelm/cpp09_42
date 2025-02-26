#include "../inc/PmergeMe.hpp"

void pmerge(std::deque<int> &deq, int lvl, size_t &counter)
{
	size_t range = pow(2, lvl);
	auto b = deq.begin() + range - 1;
	auto a = b + range;
	while (a < deq.end() && b < deq.end())
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
	if (deq.size() >= 2 * pow(2, lvl + 1))
		pmerge(deq, lvl + 1, counter);
	//half of recursion is done, now comes the second part

	//making a deque for index tracking that holds the values of the coresponding indexes in the deq {b1, a1, b2, a2, ....,bn,an}
	//after every insert, all indeces biger or equal than found index are increased by one
	std::deque<int> bline;
	std::deque<int> index_tracker( deq.size() / range, -1);
	index_tracker[0] = 0;
	size_t index = 1;
	//filling index_tracker with initial indeces for b1 and all a's.
	//all b's from b1 and higher are set to -1 to indicate they are not sorted yet.
	for(size_t i = 1; i <index_tracker.size(); i += 2)
		index_tracker[i] = index++;
	b = deq.begin() + range - 1;
	a = b + range;
	std::deque<int>::iterator it = deq.begin() + range - 1 + range + range;
	//dividing the main deque deq into deq and bline
	for (size_t i = 1; deq.begin() + range - 1 + range + i * range < deq.end(); i++)
	{
		it = deq.begin() + range - 1 + range + i * range;
		bline.insert(bline.end(), it - (range - 1), it + 1);
		deq.erase(it - (range - 1), it + 1);
	}
	// now i have 3 extra deques:
	// - deq, where everything is sorted correctly
	// - bline where all b's are to be sorted into deq,
	// - index_tracker to know which an is at which index to sort the coresponding bn in a binary serach only until index of an.

	// i have to sort b's according to the jacobbsthal numbers for minimum maximum comparisons for bn.
	// so i start with b3 then b2. then next jacobsthal number is 5 so i sort b5, then b4.
	// Next JN in 11 so i sort b10, b9, b8, b7, b6. and so on.
	size_t	current_jacobsthal;
	size_t	previous_jacobsthal;
	std::deque<int>::iterator	iter_to_insert_before;
	size_t	bn_index;
	std::deque<int>::iterator bn_line_iter;
	std::deque<int>::iterator last;
	int new_index_of_bn_in_deq;
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
			// std::cout<<"current Jacobsthal: "<<current_jacobsthal<<"	previous: "<<previous_jacobsthal<<std::endl;
			// std::cout << "Contents of deq:"<<std::endl;
			// for (size_t it = 0; it < deq.size(); it ++){if (it % (size_t)pow(2, lvl) == 0){std ::cout <<"| ";}std::cout << deq[it]<<" ";}
			// std::cout <<std::endl;
			// std::cout << "Contents of bline:"<<std::endl;
			// for (size_t it = 0; it < bline.size(); it ++){if (it % (size_t)pow(2, lvl) == 0){std ::cout <<"| ";}std::cout << bline[it]<<" ";}
			// std::cout <<std::endl;
			bn_index = (current_jacobsthal - 1) * 2;
			//in case the rest of the sequence is enough to build its own element blast
			if (bn_index + 1 < index_tracker.size())
				last = deq.begin() + (range - 1) + index_tracker[bn_index + 1] * range - range;
			else
				last = deq.begin() -1 + (deq.size() / range) * range;
			// std::cout << "last range:"<<std::endl;
			// for (size_t it = 0; it < range; it ++){std::cout << *(last - (range - 1) + it)<<" ";}
			// std::cout <<std::endl;
			//returns the iter where iter - range is the actual index where in deq range of (bn - range, bn) should be inserted
			iter_to_insert_before = binary_search( deq, last, *bn_line_iter, counter, range);
			// case for inserting after last index but last is not the last range index of deq.
			if (iter_to_insert_before != deq.end())
				iter_to_insert_before -= (range - 1);
			else if (iter_to_insert_before == deq.end())
				iter_to_insert_before = last + 1;
			new_index_of_bn_in_deq = (iter_to_insert_before - deq.begin()) / range;
			// in case the element gets added to the end of deq, its index needs to be increased 
			if (iter_to_insert_before == deq.end() || new_index_of_bn_in_deq < 0)
				new_index_of_bn_in_deq++;
			
			//			actual index in deq to insert |	range index current bn
			deq.insert(iter_to_insert_before, bn_line_iter - (range - 1), bn_line_iter + 1);
			//removing the just inserted bn from bline
			bline.erase(bn_line_iter - (range - 1), bn_line_iter + 1);
			//updating the tracker indeces of all a's and b's with a index equal or higher than nwe index of bn
			//also giving bn a valid value
			for (auto it = index_tracker.begin(); it < index_tracker.end(); it++)
			{
				if ((*it >= 0 )&& (*it >= new_index_of_bn_in_deq))
					(*it)++;
				if (it == index_tracker.begin() + bn_index)
					*it = new_index_of_bn_in_deq;
			}
			current_jacobsthal--;
			bn_line_iter = (bline.begin() -1 ) + ((current_jacobsthal - previous_jacobsthal) * range); //deque iterator change for working program
		// std::cout <<std::endl;
		}
	}

	(void)jacobsthal(1);
	// 	std::cout << "Contents of deq:"<<std::endl;
	// 	for (size_t it = 0; it < deq.size(); it ++){if (it % (size_t)pow(2, lvl) == 0){std ::cout <<"| ";}std::cout << deq[it]<<" ";}
	// 	std::cout <<std::endl;
	// std::cout << "======= recursion lvl: "<<lvl<<" done\n"<<std::endl;
}

// 26 1 37 39 25 30 1 16 17 14 27 18 27 15 23 40 11 12 40 2 26 22 2 35 2 19 2 17 36 31 33 32 23 7 2 18 12 6 1 34