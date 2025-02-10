#include "../inc/PmergeMe.hpp"

// bool compare(int &b, int &a, int &counter)
// {
//     counter++;
//     int tmp;
//     if (a < b)
//     {
//         tmp = a;
//         a = b;
//         b = tmp;
//     }
//     return;
// }

int main(int argc, char **argv)
{
   try {
        std::vector<int> vec;
        // std::deque<int> deq;
        std::regex pattern("^[0-9]+$");
        std::smatch match;

        if (argc < 2)
            {std::cout <<"need args!" <<std::endl;return 1;}
        
        for (int i = 1; i < argc; i++)
        {
            std::string tmp(argv[i]);
            if (!std::regex_match(tmp, match, pattern))
                throw std::string("Oh thats not a valid input!");
			int value = std::stoi(tmp);
			if (std::find(vec.begin(), vec.end(), value) != vec.end())
				throw std::string("Oh no duplicates allowed!");
            vec.push_back(value);
        }
        
        
        std::cout<<"Before: ";
        for_each (vec.begin(), vec.end(), [](int i){std::cout<<i<<" ";});
        std::cout<<std::endl;
        // const auto vec_start = std::chrono::high_resolution_clock::now();
	    size_t vec_counter = 0;
        pmerge(vec, 0, vec_counter);
        // const auto vec_end = std::chrono::high_resolution_clock::now(); 
        // const auto deq_start = std::chrono::high_resolution_clock::now(); 
        // size_t deq_counter = 0;
        // // pmerge(deq);
        // const auto deq_end = std::chrono::high_resolution_clock::now(); 
        std::cout<<"After: ";
        for_each (vec.begin(), vec.end(), [](int i){std::cout<<i<<" ";});
        // // std::cout<<std::endl;
        // auto duration_vec = std::chrono::duration_cast<std::chrono::microseconds>(vec_end - vec_start);
        // auto duration_deq = std::chrono::duration_cast<std::chrono::microseconds>(deq_end - deq_start);
        // std::cout   <<"Time to process a range of " <<argc -1 <<" elements with std::vector: " 
        //             << duration_vec.count();

    }
    catch (std::exception &e){std::cout<<"Error: "<<e.what()<<std::endl;return 1;}
    catch (int &e){std::cout<<"ERRORCODE: "<<e<<std::endl;return 1;}
    catch (std::string &e) {std::cout<<"ERROR: "<<e<<std::endl;return 1;}
    catch (...) {std::cout <<"LOL!"<<std::endl;return 1;}
    return 0;

}   