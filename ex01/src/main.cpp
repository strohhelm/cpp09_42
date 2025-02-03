/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@42.heilbronn.de>        #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 09:08:09 by pstrohal          #+#    #+#             */
/*   Updated: 2025-02-02 09:08:09 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RPN.hpp"

int main(int argc, char **argv)
{
	try{
	if (argc != 2 || !*argv[1])
		throw "Error usage: ./RPN \".....\"";
	std::string input = argv[1];
	std::regex first_filter("^[\\d\\+\\-\\*\\/ ]+?$");
	std::regex second_filter(R"([0-9+\-*/]+?)");
	std::stack<float>	storage;
	std::smatch match;
	if(!std::regex_match(input, match, first_filter))
		throw "Error";
	std::sregex_iterator it(input.begin(), input.end(), second_filter);
	std::sregex_iterator end;
	for(; it != end; it++)
	{
		if (storage.size() < 2 && !std::isdigit(it->str()[0]))
			throw "Error: needs al least two operands first!";
		else if (std::isdigit(it->str()[0]))
			storage.push(std::stof(it->str()));
		else if (!std::isdigit(it->str()[0]))
			{
				float a = storage.top();
				storage.pop();
				float b = storage.top();
				storage.pop();
				switch (static_cast<char>(it->str()[0])){
					case '-':
						storage.push(b - a);
						break;
					case '+':
						storage.push(b + a);
						break;
					case '*':
						storage.push(b * a);
						break;
					case '/':
						storage.push(b / a);
						break;
					default:
						throw "Error lol";
				}
			}
	}
	if (storage.size() != 1)
		throw "Error missing input";
	else
		std::cout<<storage.top()<<std::endl;
	return 0;
	}
	catch (std::exception &e)
		{std::cout<<"Error: "<<e.what()<<std::endl; return 1;}
	catch (char const *s)
		{std::cout<<s<<std::endl; return 1;}
}