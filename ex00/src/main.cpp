/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:18:00 by pstrohal          #+#    #+#             */
/*   Updated: 2025/01/30 20:47:01 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bitcoinExchange.hpp"

unsigned int validate_smatch(std::smatch &match, int &errorcode, float &value)
{
	try{
		if (match.size() < 5|| match.size() > 6)
			{std::cout<<DR<<"ERROR: "<<match.size()<<X<<std::endl;
			for(auto matches : match)
			{
				std::cout<<matches.str()<<std::endl;
			}
			throw (errorcode = 1);
			}
		time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		auto current = std::localtime(&now);
		int year	= std::stoi(match.str(1));
		int month	= std::stoi(match.str(2));
		int	day		= std::stoi(match.str(3));
		int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

		if (year < 0 || year > current->tm_year + 1900)
			throw (errorcode = 1);
		if ((year % 4 == 0  && year % 100 != 0) || year % 400 == 0)
			months[1] = 29;
		if ((month  < 1 || month > 12) || month > current->tm_mon + 1)
			throw (errorcode = 1);
		if ((day < 1 || day > months[month]) || (year == current->tm_year && month == current->tm_mon && day > current->tm_mday))
			throw (errorcode = 1);
		long date =  std::stoul(match.str(1) + match.str(2) + match.str(3));
		long value = std::stof(match.str(4)) ;
		if (value < 0)
			throw (errorcode = 2);
		if (value > 1000.0)
			throw (errorcode = 3);
		return (date);
	}
	catch (std::exception &e){
		std::cout<<DR<<"ERROR: "<<e.what()<<X<<std::endl;
		return (errorcode = 4);
	}
	catch(int &errorcode){return errorcode;}
}

bool	fill_database(std::map<unsigned int, float> &database, std::ifstream &file)
{
	std::string		tmp;
	std::smatch		match;
	unsigned int	date;
	float			value;
	int				errorcode = 0;
	bool			start = false;
	std::regex pattern("(^\\d{4})-(\\d{2})-(\\d{2}),(\\d+(\\.\\d+)?$)");
	while (std::getline(file, tmp))
	{
		if (!start){start = true; continue;}
		if (!std::regex_search(tmp, match, pattern))
			return false;
		if (match.str(0) != tmp)
			return false;
		date = validate_smatch(match, errorcode, value);
		if (errorcode)
			return false;
		auto check = database.insert_or_assign(date, value);
		if (!check.second){
			std::cout<<DR<<"ERROR! Ambiguous entry in database!"<<X<<std::endl;
			return false;}
		std::cout<<database.at(date)<<std::endl;
	}
	return true;
}
// void print(int errorcode, std::smatch &match, float &value, std::map<unsigned int, float> &database)
// {

// }



int main (int argc, char **argv)
{

	if (argc != 2)
		{std::cout<<DR<<"ERROR! Usage: ./btc <filename>"<<X<<std::endl; return 1;}


	std::ifstream					database_file("./data.csv", std::fstream::in);
	// std::ifstream					input_file(argv[1], std::fstream::in);
	std::map<unsigned int, float>	database;


	if (!database_file.is_open() || !database_file.good())
		{std::cout<<DR<<"ERROR! Database not correctly provided!"<<X<<std::endl; return 1;}
	// if (!input_file.is_open() || !input_file.good())
		// {std::cout<<DR<<"ERROR! Input file not correctly provided!"<<X<<std::endl; database_file.close(); return 1;}
	if (!fill_database(database, database_file))
		// {input_file.close(); database_file.close(); return 1;}
	// database_file.close();

	// std::regex pattern("(^\\d{4})-(\\d{2})-(\\d{2})) | (\\d+(\\.\\d+)?$)"); 
	// std::smatch						match;
	// std::string						current_line;
	// unsigned int 					input_date;
	// float							input_value;
	// bool							header = false;
	// int								errorcode = 0;
	// while (std::getline(input_file, current_line))
	// {
	// 	if (!header)
	// 		{header = true; continue;}
	// 	std::regex_search(current_line, match, pattern);
	// 	input_date = validate_smatch(match, errorcode, input_value);
	// 	switch (errorcode){
	// 		case 1:
	// 			std::cout<<"Error: bad input => "<<current_line.substr(0, 9)<<std::endl;
	// 		case 2:
	// 			std::cout<<"Error: not a positive number."<<std::endl;
	// 		case 3:
	// 			std::cout<<"Error: too large a number."<<std::endl;
	// 		case 4:
	// 			std::exit(1);
	// 		default:
	// 			std::cout<<current_line.substr(0, 9)<<" => "<<input_value<< " = " << input_value * database.at(input_date)<<std::endl;
	// 	}
	// 	errorcode = 0;
	// }
	// input_file.close();
	

	return 0;
}