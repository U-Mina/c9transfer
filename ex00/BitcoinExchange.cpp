/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:50:31 by ewu               #+#    #+#             */
/*   Updated: 2025/08/15 13:32:11 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream> //convert str to str-stream

/*------------constructor---------*/

BitcoinExchange::BitcoinExchange()
{
	//std::cout << "default cons called!\n";
	readDB();
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	this->_DB = other._DB;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		this->_DB = other._DB;
	return *this;
}
BitcoinExchange::~BitcoinExchange()
{
	//std::cout << "default des called!\n";
}

/*------------methods------------------*/

static bool _checkdigit(std::string& s)
{
	for (int i = 0; s[i]; ++i)
	{
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}

static bool _checkFeb(int yy, int dd) {
	if ((yy % 4 == 0 && yy % 100 != 0) || yy % 400 == 0) {
		if (dd > 29) {
			std::cerr << "Error: over 29th on Feb\n";
			return false;
		}
	}
	if (dd > 28) {
		std::cerr << "Error: no 29th Feb this year => " << yy << '\n';
		return false;
	}
	return true;
}

static bool _range(std::string& yy, std::string& mm, std::string& dd) {
	int year = std::stoi(yy);
	
	if (year < 2009) {
		return false;	
	}
	
	int month = std::stoi(mm);
	if (month < 1 || month > 12) {
		std::cerr << "Error: invalid month => " << month << '\n';
		return false;
	}
	
	int day = std::stoi(dd);
	if (day > 31) {
		std::cerr << "Error: over 31 days => " << day << '\n';	
		return false;
	}
	
	if (!_checkFeb(year, day)) {
		return (false);
	}
	//30 days month
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30)
		{
			std::cerr << "Error: no 31st days in month => " << month << '\n';
			return false;
		}
	}
	return true;
}

//YYYY-MM-DD
bool BitcoinExchange::validDate(const std::string& _date) const
{
	if (_date.size() > 10 || _date[4] != '-' || _date[7] != '-')
		return false;
	std::string yy = _date.substr(0, 4);
	std::string mm = _date.substr(5, 2);
	std::string dd = _date.substr(8, 2);
	if (!_checkdigit(yy) || !_checkdigit(mm) || !_checkdigit(dd)) //any non-num in date
		return false;
	if (!_range(yy, mm, dd))
		return false;
	return true;
}

bool BitcoinExchange::validValue(const std::string& _val) const
{
	try
	{
		size_t pos;
		float _rate = std::stof(_val, &pos); //&pos the index of 1st non-numeric char
		if (_val.size() != pos)
		{
			std::cerr << "Error: Invalid value: " << _val << "\n";
			return false;
		}
		if (_rate < 0.00f)
		{
			std::cerr << "Error: not a positive number.\n";
			return false;
		}
		if (_rate > 1000.00f)
		{
			std::cerr << "Error: too large a number.\n";
			return false;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error:\nInvalid value: " << _val << "\n";
		return false;
	}
	return true;
}

void BitcoinExchange::readDB()
{
	std::ifstream csv("data.csv");
	if (!csv.is_open()) //cant open data.csv
	{
		throw std::runtime_error("Error:\nCannot open data.csv\n");
	}
	std::string line;
	std::getline(csv, line); //read the 1st line, skip it in loop
	while (std::getline(csv, line))
	{
		std::stringstream tmpCsv(line); //convert str to str-stream, use getline() to read (date part and value part)
		std::string csvDate;
		std::string csvRate;
		if (std::getline(tmpCsv, csvDate, ',') && std::getline(tmpCsv, csvRate)) // data,val
		{
			try {
				float _rate = std::strtof(csvRate.c_str(), NULL);
				_DB[csvDate] = _rate;
				//store date-val pair in map _DB
			} catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}
	}
	csv.close();
}

/**
 * floor lookup: find the pair value for the 'key'
 * lower.bound() => to find the first element in the data map whose 'date' is not
 * less than the input date. namely, it finds the first date
 * in the map that is either equal to or greater than the input date
 * return an iterator
 * if 'date' exist, lower_bound() return an it to that 'date'
 * if doesn't exist, return next greater 'date'
 * if 'date' greater then all, return _DB.end()
 */
float BitcoinExchange::floorDate(const std::string& date) const
{
	typename std::map<std::string, float>::const_iterator c_it \
				= _DB.lower_bound(date);
	if (c_it == _DB.begin()) {//the date is equal or earlier than begin
		return c_it->second; //access the exchange_rate
	} else {
		typename std::map<std::string, float>::const_iterator pre \
				= std::prev(c_it);
		return pre->second; //find the exact match, return 'rate'
	}
}

static void _trimSpace(std::string& s)
{
	std::string tmp;
	for (size_t i = 0; i < s.length(); ++i)
	{
		if (s[i] != ' ')
			tmp = tmp + s[i];
	}
	s = tmp;
}

void BitcoinExchange::readInput(const std::string& inFile) const
{
	std::ifstream input(inFile);
	if (!input.is_open())
		throw std::runtime_error("Error: could not open file\n");
	std::string line;
	std::getline(input, line); //skip 1st line
	while (std::getline(input, line))
	{
		std::stringstream tmpIn(line);
		std::string inDate;
		std::string inVal;
		if (std::getline(tmpIn, inDate, '|') && std::getline(tmpIn, inVal)) {
			// date | rate
			_trimSpace(inDate);
			_trimSpace(inVal);
			// inDate.erase(std::remove_if(inDate.begin(), inDate.end(), ::isspace), inDate.end());
			// inVal.erase(std::remove_if(inVal.begin(), inVal.end(), ::isspace), inVal.end());
			if (!validDate(inDate)) {
				// std::cerr << "Error: invalid date => " << inDate << '\n';
				continue; //the read will continue to next line (behaviour of test case)
			}
			if (!validValue(inVal))
				continue; //err msg print already
			try {
				float exchangeRate = floorDate(inDate);
				float inputVal = std::stof(inVal, NULL);
				float res = exchangeRate * inputVal;
				std:: cout << inDate << " => " << inVal << " = " << res << '\n';
			} catch (const std::exception& e) {
				std::cerr << "Error: " << e.what() << '\n';
			}
		} else {
			std::cerr << "Error: bad input => " << inDate << '\n';
		}
	}
	input.close();
}

/**
 * std::getline(std::istream& is, std::string& str)
 * std::getline(std::istream& is, std::string& str, char delim)
 * Reads from input-stream (usually std::cin/file stream) into str until it '\n'
 * or delimiter, delim is NOT INCLUED in 'str'
 */