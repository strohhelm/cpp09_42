#include "../inc/PmergeMe.hpp"


size_t jacobsthal(int mode)
{
	static size_t n = 1;
	static size_t previous = 1;
	static size_t jacobsthal = 1;

	if (mode == 0)
	{
		previous = jacobsthal;
		jacobsthal = pow(2, n) - jacobsthal;
		n++;
		return jacobsthal;
	}
	else if (mode == 1)
	{
		n = 2;
		jacobsthal = 1;
		previous = 1;
		return jacobsthal;
	}
	else
		return previous;
}

size_t calc_max_comp(size_t n)
{
	size_t sum = 0;
	for (size_t k = 1; k <= n; k++)
	{
		sum += static_cast<size_t>(std::ceil(std::log2(3.0 * k / 4.0)));
	}
	return (sum);
}

int main(int argc, char **argv)
{
	try {
		std::vector<int> vec;
		std::deque<int> deq;
		std::regex pattern("^[\\s]*[0-9]+[\\s]*$");
		std::smatch match;
		size_t vec_counter = 0;
		size_t deq_counter = 0;


		//input handling
		if (argc < 2)
			throw std::string("Need arguments!");
		if (argc > std::numeric_limits<int>::max())
			throw std::string("Argument size capped to max int value");
		for (int i = 1; i < argc; i++)
		{
			std::string tmp(argv[i]);
			if (!std::regex_match(tmp, match, pattern))
				throw std::string("Oh thats not a valid input only one positive integer value per argument!");
			int value = std::stoi(tmp);
			// if (std::find(vec.begin(), vec.end(), value) != vec.end())
			// 	throw std::string("Oh no duplicates allowed!");
			vec.push_back(value);
			deq.push_back(value);
		}


		std::cout<<"VEC Before: ";
		for_each (vec.begin(), vec.end(), [](int i){std::cout<<i<<" ";});
		std::cout<<"\nDEQ Before: ";
		for_each (deq.begin(), deq.end(), [](int i){std::cout<<i<<" ";});
		std::cout<<std::endl;
		
		//main part and stopping times
		const auto vec_start = std::chrono::high_resolution_clock::now();
		pmerge(vec, 0, vec_counter);
		const auto vec_end = std::chrono::high_resolution_clock::now(); 
		
		const auto deq_start = std::chrono::high_resolution_clock::now(); 
		pmerge(deq, 0, deq_counter);
		const auto deq_end = std::chrono::high_resolution_clock::now(); 
		
		std::cout<<std::endl;
		std::cout<<"VEC After: ";
		for_each (vec.begin(), vec.end(), [](int i){std::cout<<i<<" ";});
		std::cout<<std::endl;
		std::cout<<"DEQ After: ";
		for_each (deq.begin(), deq.end(), [](int i){std::cout<<i<<" ";});
		std::cout<<std::endl;
		
		for(size_t i = 0; i < vec.size(); i++)
		{
			if (vec[i] != deq[i])
				throw std::string("LOL vec and deq not equal, you fucked up!");
		}
		if (deq_counter != vec_counter)
			throw std::string("LOL counter not equal, you fucked up!");
		if (!std::is_sorted(vec.begin(), vec.end()))
			throw std::string("LOL not sorted, you fucked up!");
		std::cout<<"Maximum comparisons for "<<argc - 1<<" numbers: "<<calc_max_comp(static_cast<size_t>((argc - 1)))<<std::endl;


		//print statements
		auto duration_vec = std::chrono::duration_cast<std::chrono::microseconds>(vec_end - vec_start);
		auto duration_deq = std::chrono::duration_cast<std::chrono::microseconds>(deq_end - deq_start);
		//vector
		std::cout	<<"Time to process a range of " <<argc -1 <<" elements with std::vector<int>: " 
					<< duration_vec.count() <<" microseconds"<<std::endl;
		std::cout	<<"Comparisons for vector: "<<vec_counter<<std::endl;
		//deque
		std::cout	<<"Time to process a range of " <<argc -1 <<" elements with std::deque<int>: " 
					<< duration_deq.count() <<" microseconds"<<std::endl;
		std::cout<<"Comparisons: "<<deq_counter<<std::endl;
	}
	catch (std::exception &e){std::cout<<"Error: "<<e.what()<<std::endl;return 1;}
	catch (int &e){std::cout<<"ERRORCODE: "<<e<<std::endl;return 1;}
	catch (std::string &e) {std::cout<<"ERROR: "<<e<<std::endl;return 1;}
	catch (...) {std::cout <<"LOL!"<<std::endl;return 1;}
	return 0;

}
// 20  1  4  2 17 11  9  3  8  5 10 12 14 18 13  6 21  7 15 19 16 
// 18 20 13  2 10  6 17  8  3 21  4  7  5  9 15 16  1 12 11 14 19
// 15 10 11  9 13  8 14  3 16  2 18 12  1  7 21 17 19  6  5 20 4
// "15", "10", "11", " 9", "13", " 8", "14", " 3", "16", " 2", "18", "12", " 1", " 7", "21", "17", "19", " 6", " 5", "20", "4"
// 7  8 16 21 18 13  6 14 11  9  1 12  5 10  3 20  4 19 15 17

//6 3 7 2 7 5 9 5 8 3 9 2 4 6 3 2 8 10 7 8 9
// "6", "3", "7", "2", "7", "5", "9", "5", "8", "3", "9", "2", "4", "6", "3", "2", "8", "10", "7", "8", "9"

//14 9 9 13 7 1 9 15 15 7 12 12 15 7 10 12 18 8 1 17 19
// 5 9 16 11 13 15 8 14 8 3 19 2 16 11 5 20 14 11 18 21 18 


// 17 3  20  19  18  2  21  6 18  16  12  5  3  2  10  11  6  18  11  1 8 10  12  15  19  10  1 12  14  12  16