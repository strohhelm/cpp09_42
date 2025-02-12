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


void pmerge(std::vector<int> &vec, int lvl, size_t &count);
// void pmerge(std::deque<int> &deq, int lvl, size_t &count);

size_t jacobsthal(int mode);
std::vector<int>::iterator binary_search(std::vector<int> &vec, std::vector<int>::iterator last, int value, size_t &counterer, size_t &range);

#endif