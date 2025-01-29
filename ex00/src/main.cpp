/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:18:00 by pstrohal          #+#    #+#             */
/*   Updated: 2025/01/29 14:02:24 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bitcoinExchange.hpp"

unsigned int validate_smatch(std::smatch &match, int &errorcode)
{
	try{
		if (match.size() != 4)
			throw (errorcode = 1);
		time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		auto current = std::localtime(&now);
		int year	= std::stoi(match.str(0));
		int month	= std::stoi(match.str(1));
		int	day		= std::stoi(match.str(2));
		int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if (year < 0 || year > current->tm_year + 1900)
			throw std::string("Invalid Year!");
		if ((year % 4 == 0  && year % 100 != 0) || year % 400 == 0)
			months[1] = 29;
		if ((month  < 1 || month > 12) || month > current->tm_mon + 1)
			throw std::string("Invalid month!");
		if ((day < 1 || day > months[month]) || (year == current->tm_year && month == current->tm_mon && day > current->tm_mday))
			throw std::string("Invalid day!");
		long value =  std::stoul(match.str(0) + match.str(1) + match.str(2));
		if (value < 0);
			
	}
	catch (std::exception &e){
		std::cout<<DR<<"ERROR! "<<e.what()<<X<<std::endl;
	}
	catch(int &errorcode){
		
	}
	return -1;
}

bool	fill_database(std::map<unsigned int, float> &database, std::ifstream &file)
{
	std::string tmp;
	std::smatch match;
	unsigned int date;
	std::regex pattern("(^\\d{4})-(\\d{2})-(\\d{2})),(\\d+(\\.\\d+)?$)");
	while (std::getline(file, tmp))
	{
		if (tmp == "date,exchange_rate\n")
			continue;
		if (!std::regex_search(tmp, match, pattern))
			return false;
		date = validate_smatch(match);
		if (date < 0)
			return false;
		auto check = database.insert_or_assign(date, stof(match.str(3)));
		if (!check.second){
			std::cout<<DR<<"ERROR! Ambiguous entry in database!"<<X<<std::endl;
			return false;}
	}
	return true;
}
void print(int errorcode, std::string date, float value)
{

}



int main (int argc, char **argv)
{

	if (!argc == 2)
		{std::cout<<DR<<"ERROR! Usage: ./btc <filename>"<<X<<std::endl; return 1;}


	std::ifstream					database_file("../cpp_09/data.csv", std::fstream::in);
	std::ifstream					input_file(argv[1], std::fstream::in);
	std::map<unsigned int, float>	database;


	if (!database_file.is_open() || !database_file.good())
		{std::cout<<DR<<"ERROR! Database not correctly provided!"<<X<<std::endl; return 1;}
	if (!input_file.is_open() || !input_file.good())
		{std::cout<<DR<<"ERROR! Input file not correctly provided!"<<X<<std::endl; return 1;}
	if (!fill_database(database, database_file))
		return 1;
	

	std::regex pattern("(^\\d{4})-(\\d{2})-(\\d{2})) | (\\d+(\\.\\d+)?$)"); 
	std::smatch						match;
	std::string						current_line;
	unsigned int 					input_date;
	float							input_value;
	bool							header = false;
	int								errorcode;
	while (std::getline(input_file, current_line))
	{
		if (!header)
			{header = true; continue;}
		std::regex_search(current_line, match, pattern);
		if (match.size() == 4)
			input_date = validate_smatch(match, errorcode);
		else if (match.size() == 3)
			
	}

	return 0;
}