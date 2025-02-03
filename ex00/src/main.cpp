/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:18:00 by pstrohal          #+#    #+#             */
/*   Updated: 2025/01/31 17:35:07 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

			// return false;
			// for(auto matches : match)
			// {
			// 	std::cout<<matches.str()<<"  |  ";
			// }
#include "../inc/bitcoinExchange.hpp"

unsigned int validate_smatch(std::smatch &match, int &errorcode, float &value, bool databasemode)
{
	try{
		if (match.size() != 6)
			{errorcode = 1; throw errorcode;}
		time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		auto current = std::localtime(&now);
		int year	= std::stoi(match.str(1));
		int month	= std::stoi(match.str(2));
		int	day		= std::stoi(match.str(3));
		int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

		if (year < 0 || year > current->tm_year + 1900)
			{errorcode = 1; throw errorcode;}
		if ((year % 4 == 0  && year % 100 != 0) || year % 400 == 0)
			months[1] = 29;
		if ((month  < 1 || month > 12) || (month > current->tm_mon + 1 && year == current->tm_year))
			{errorcode = 1; throw errorcode;}
		if ((day < 1 || day > months[month - 1]) || (year == current->tm_year && month == current->tm_mon && day > current->tm_mday))
			{errorcode = 1; throw errorcode;}
		long date =  std::stoul(match.str(1) + match.str(2) + match.str(3));
		value = std::stof(match.str(4)) ;
		if (value < 0 && !databasemode)
			throw (errorcode = 2);
		if (value > 1000.0 && !databasemode)
			throw (errorcode = 3);
		return (date);
	}
	catch (std::exception &e){
		std::cout<<DR<<"ERROR: "<<e.what()<<X<<std::endl;
		return (errorcode = 4);
	}
	catch(int &errorcode){return -errorcode;}
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
		if (!std::regex_match(tmp, match, pattern))
			return false;
		date = validate_smatch(match, errorcode, value, 1);
		if (errorcode)
			return false;
		auto check = database.insert_or_assign(date, value);
		if (!check.second){
			std::cout<<DR<<"ERROR! Ambiguous entry in database!"<<X<<std::endl;
			return false;}
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
	std::ifstream					input_file(argv[1], std::fstream::in);
	std::map<unsigned int, float>	database;


	if (!database_file.is_open() || !database_file.good())
		{std::cout<<DR<<"ERROR! Database not correctly provided!"<<X<<std::endl; return 2;}
	if (!input_file.is_open() || !input_file.good())
		{std::cout<<DR<<"ERROR! Input file not correctly provided!"<<X<<std::endl; database_file.close(); return 1;}
	if (!fill_database(database, database_file))
		{input_file.close(); database_file.close(); return 3;}
	database_file.close();

	
	std::regex pattern("(^\\d{4})-(\\d{2})-(\\d{2}) \\| (-?\\d+(\\.\\d+)?$)");
	std::smatch						match;
	std::string						current_line;
	unsigned int 					input_date;
	float							input_value;
	bool							header = false;
	int								errorcode = 0;
	int								range = 0;
	while (std::getline(input_file, current_line))
	{
		if (!header)
			{header = true; continue;}
		std::regex_match(current_line, match, pattern);
		input_date = validate_smatch(match, errorcode, input_value, 0);
		switch (errorcode){
			case 1:
				std::cout<<"Error: bad input => "<<current_line<<std::endl;
				break;
			case 2:
				std::cout<<"Error: not a positive number."<<std::endl;
				break;
			case 3:
				std::cout<<"Error: too large a number."<<std::endl;
				break;
			case 4:
				std::exit(4);
				break;
			default:
				auto it = database.lower_bound(input_date);
				if (it == database.end())
					{it--; range = 1;}
				else if (input_date < database.begin()->first)
					range = -1;
				std::cout	<<current_line.substr(0, 10)
							<<" => "<<input_value
							<< " = "
							<<input_value * it->second;
				if (range > 0){
					std::cout	<< " (Careful! Input date far away from last database entry: "
								<< it->first / 10000<<"-"
								<< std::setfill('0')<<std::setw(2)<<(it->first % 10000) / 100<<"-"
								<< std::setfill('0')<<std::setw(2)<<(it->first % 100) << " converison might not be accurate!)";}
				else if(range < 0){
					std::cout	<< " (Careful! Input date far away from first database entry: "
								<< it->first / 10000<<"-"
								<< std::setfill('0')<<std::setw(2)<<(it->first % 10000) / 100<<"-"
								<< std::setfill('0')<<std::setw(2)<< (it->first % 100) << " converison might not be accurate!)";}
				std::cout<<std::endl;
		}
		errorcode = 0;
	}
	input_file.close();
	return 0;
}