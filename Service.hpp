#pragma once

#include<iostream>
#include<string>
#include <boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>

//declaration of Service class to handle request from client
class Service
{
	// structure for user details
	struct user
	{
		std::string username;
		std::string password;
		std::string type_user;
	};

	//map for holds user details
	std::map<std::string, user> userMap;

	//map for holds car details
	std::map<std::string, std::map<std::string, std::string>> carMap;

	//methods for handling client requests
public:
	std::string addUser(std::string, std::string, std::string);
	std::string validateUser(std::string, std::string);
	std::string addCar(std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string);
	std::string showMyCars(std::string);
	std::string selectCar(std::string);
	std::string returnCar(std::string);
	std::string showAvailableCars();
	std::string showAllCars();
	std::string deleteCar(std::string);
	std::string showCarInfo(std::string);
};

