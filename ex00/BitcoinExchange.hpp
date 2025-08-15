/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:43:33 by ewu               #+#    #+#             */
/*   Updated: 2025/08/15 13:21:51 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map> //a container with 'key:value' pair, accessible by 'key' (NOT INDEX)
#include <string>
#include <stdexcept>

/**
 * Exception:
 * invalid date: year 2009/month 13/day 28/29/30/31;
 * invalid value: -/>1000/non-numeric
 * Error:
 * no input.txt (check ac num); no data.csv; read/open err
 */
class BitcoinExchange
{
private:
	std::map<std::string, float> _DB; 
	//map stores date | exchange_rate; map<keyType, valueType> mapName
	bool validDate(const std::string& _date) const;
	bool validValue(const std::string& _val) const;
	void readDB();
	//void readDB(const std::string& _csvFile); //take REF of .CSV file and read
	
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();
	void readInput(const std::string& inFile) const;
	//read user input.txt
	float floorDate(const std::string& date) const;
	//to floor the data in .csv to find closest match
};

#endif

// class InvalidDateException : public std::exception
// {
// public:
// 	const char* what() const throw()
// 	{
// 		return ("Date is invalid!\n"); //maybe more cases specified, do later
// 	}
// };
// class InvalidValException : public std::exception
// {
// public:
// 	const char* what() const throw()
// 	{
// 		return ("\033[33mInvalid value!\n Should within 0-1000!\n\033[0m");
// 	}
// };
/**
 * 1. read and parse CSV into map
 * 2. read input
 * 3. split input into format: data | value
 * 4. check validity of 'data' & 'value'
 * 5. find the closest data in CSV
 * 6. calculate and print
 * template:
 * 2018-02-02 (yyyy-mm-dd)
	void Account::_displayTimestamp() {
		//get cur time
		std::time_t now = std::time(nullptr);
		std::tm *curTime = std::localtime(&now);
		std::cout << std::put_time(curTime, "%Y-%m-%d"); }
*/