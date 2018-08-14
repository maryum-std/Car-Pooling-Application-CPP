#pragma once

#include<iostream>
#include<string>
#include<map>

//class holding method for connecting to the server
class Connect
{
public:
	//method declaration for establishing network connection with the server
	std::string connection(std::map<std::string, std::string> dataMap);
};

