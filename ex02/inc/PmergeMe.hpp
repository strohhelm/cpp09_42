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


void pmerge(std::vector<int> &vec, int lvl, size_t &count);
// void pmerge(std::deque<int> &deq, int lvl, size_t &count);

size_t next_jacobsthal(void);

#endif