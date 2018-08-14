#include<iostream>
#include<map>
#include<string>
#include <sstream>
#include "Service.hpp"

//namespace for using boost archive for serialization and de-serialization
using namespace boost::archive;

// registering a new user
std::string Service::addUser(std::string username, std::string password, std::string type_user)
{
	if (userMap.count(username))
	{
		return "username_already_exists";
	}
	else
	{
		userMap[username] = user{ username, password, type_user };
	}
	
	return "saved";
}


// login
std::string Service::validateUser(std::string username, std::string password)
{
	for (int i = 0; i < userMap.size(); i++)
	{
		if (username == userMap[username].username && password == userMap[username].password)
		{
			return "true";
		}
		else
		{
			return "false";
		}
	}
}


//  adding a car to pool
std::string Service::addCar(std::string carId, std::string username, std::string manufacturer, std::string model, std::string color, std::string seats, std::string trunk_volume, std::string fuel_type, std::string typeof_gearbox, std::string location, std::string rentPerDay, std::string returnType, std::string status)
{

	carMap[carId] = {

	{ "carId" , carId },
	{ "username", username },
	{ "manufacturer", manufacturer },
	{ "model", model },
	{ "color", color },
	{ "seats", seats },
	{ "trunk_volume", trunk_volume },
	{ "fuel_type", fuel_type },
	{ "typeof_gearbox", typeof_gearbox },
	{ "location", location },
	{ "rentPerDay", rentPerDay },
	{ "returnType", returnType },
	{ "status", status }

	};

	return "car_added";
}


// show user's cars
std::string Service::showMyCars(std::string username)
{
	std::map<std::string, std::map<std::string, std::string>> tempMap;
	for (std::map<std::string, std::map<std::string, std::string>>::iterator it = carMap.begin(); it != carMap.end(); ++it)
	{
		if (it->second["username"] == username) 
		{
			tempMap[it->first] = it->second; 
		}
	}
	std::stringstream ss;
	boost::archive::text_oarchive oarch(ss);
	oarch << tempMap;
	return ss.str();
}


// show all available cars
std::string Service::showAvailableCars()
{
	std::map<std::string, std::map<std::string, std::string>> tempMap;
	for (std::map<std::string, std::map<std::string, std::string>>::iterator it = carMap.begin(); it != carMap.end(); ++it)
	{
		if (it->second["status"] == "Available") 
		{
			tempMap[it->first] = it->second; 
		}
	}
	std::stringstream ss;
	boost::archive::text_oarchive oarch(ss);
	oarch << tempMap;
	return ss.str();
}

std::string Service::showAllCars()
{
	std::map<std::string, std::map<std::string, std::string>> tempMap;
	for (std::map<std::string, std::map<std::string, std::string>>::iterator it = carMap.begin(); it != carMap.end(); ++it)
	{
		if (it->second["status"] == "Available" || it->second["status"] == "Not Available") 
		{
			tempMap[it->first] = it->second; 
		}
	}
	std::stringstream ss;
	boost::archive::text_oarchive oarch(ss);
	oarch << tempMap;
	return ss.str();
}


// selecting a car for rent
std::string Service::selectCar(std::string carId)
{
	if (carMap.count(carId))
	{
		for (std::map<std::string, std::map<std::string, std::string>>::iterator it = carMap.begin(); it != carMap.end(); ++it)
		{
			if (it->second["carId"] == carId)
			{
				it->second["status"] = "Not Available";
			}
		}
	}
	else
	{
		return "carId_not_found";
	}


	return "car_selected";
}


// returning a car
std::string Service::returnCar(std::string carId)
{
	if (carMap.count(carId))
	{
		for (std::map<std::string, std::map<std::string, std::string>>::iterator it = carMap.begin(); it != carMap.end(); ++it)
		{
			if (it->second["carId"] == carId)
			{
				it->second["status"] = "Available";
			}
		}
	}
	else
	{
		return "carId_not_found";
	}

	return "car_returned";
}


// deleting a car
std::string Service::deleteCar(std::string carId)
{
	if (carMap.count(carId))
	{
		for (std::map<std::string, std::map<std::string, std::string>>::iterator it = carMap.begin(); it != carMap.end(); ++it)
		{
			if (it->second["carId"] == carId)
			{
				carMap.erase(it);
				break;
			}
		}
	}
	else
	{
		return "carId_not_found";
	}


	return "car_deleted";
}


// show all car details
std::string Service::showCarInfo(std::string carId)
{
	std::map<std::string, std::map<std::string, std::string>> tempMap;

	if (carMap.count(carId))
	{
		for (std::map<std::string, std::map<std::string, std::string>>::iterator it = carMap.begin(); it != carMap.end(); ++it)
		{
			if (it->second["carId"] == carId)
			{
				tempMap[it->first] = it->second;
			}
		}
	}
	
	std::stringstream ss;
	boost::archive::text_oarchive oarch(ss);
	oarch << tempMap;
	return ss.str();
}


