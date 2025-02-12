#include "../inc/PmergeMe.hpp"

std::vector<int>::iterator binary_search(std::vector<int> &vec, std::vector<int>::iterator last, int value, size_t &comp_count, size_t &range)
{
	last -= range;
	std::vector<int>::iterator first = vec.begin() + range - 1;
	size_t count = (last - first) / range + 1;
	size_t step;
	std::vector<int>::iterator it;

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

int main(int argc, char **argv)
{
   try {
        std::vector<int> vec;
        // std::deque<int> deq;
        std::regex pattern("^[\\s]*[0-9]+[\\s]*$");
        std::smatch match;

        if (argc < 2)
            throw std::string("Need arguments!");
        if (argc > std::numeric_limits<int>::max())
			throw std::string("Argument size capped to max int value");
        for (int i = 1; i < argc; i++)
        {
            std::string tmp(argv[i]);
            if (!std::regex_match(tmp, match, pattern))
                throw std::string("Oh thats not a valid input only one value per argument!");
			int value = std::stoi(tmp);
			if (std::find(vec.begin(), vec.end(), value) != vec.end())
				throw std::string("Oh no duplicates allowed!");
            vec.push_back(value);
        }
        
        
        std::cout<<"Before: ";
        for_each (vec.begin(), vec.end(), [](int i){std::cout<<i<<" ";});
        std::cout<<std::endl;
        const auto vec_start = std::chrono::high_resolution_clock::now();
	    size_t vec_counter = 0;
        pmerge(vec, 0, vec_counter);
        const auto vec_end = std::chrono::high_resolution_clock::now(); 
        const auto deq_start = std::chrono::high_resolution_clock::now(); 
        size_t deq_counter = 0;
        // pmerge(deq);
        const auto deq_end = std::chrono::high_resolution_clock::now(); 
        std::cout<<"After: ";
        for_each (vec.begin(), vec.end(), [](int i){std::cout<<i<<" ";});
        std::cout<<std::endl;
        auto duration_vec = std::chrono::duration_cast<std::chrono::microseconds>(vec_end - vec_start);
        auto duration_deq = std::chrono::duration_cast<std::chrono::microseconds>(deq_end - deq_start);
        std::cout   <<"Time to process a range of " <<argc -1 <<" elements with std::vector: " 
                    << duration_vec.count() <<std::endl;
		std::cout<<"Comparisons: "<<vec_counter<<std::endl;
    }
    catch (std::exception &e){std::cout<<"Error: "<<e.what()<<std::endl;return 1;}
    catch (int &e){std::cout<<"ERRORCODE: "<<e<<std::endl;return 1;}
    catch (std::string &e) {std::cout<<"ERROR: "<<e<<std::endl;return 1;}
    catch (...) {std::cout <<"LOL!"<<std::endl;return 1;}
    return 0;

}   
// 20  1  4  2 17 11  9  3  8  5 10 12 14 18 13  6 21  7 15 19 16 
// 18 20 13  2 10  6 17  8  3 21  4  7  5  9 15 16  1 12 11 14 19
// 15 10 11  9 13  8 14  3 16  2 18 12  1  7 21 17 19  6  5 20  4