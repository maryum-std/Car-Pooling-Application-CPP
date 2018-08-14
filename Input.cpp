#include<iostream>
#include<map>
#include<string>
#include<sstream>
#include "Input.hpp"
#include "Connection.hpp"
#include<time.h>
#include<boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>


// method for accepting input as well as displaying output
void input()
{
	try
	{
		std::map<std::string, std::string> userData;
		std::map<std::string, std::string> carData;
		Connect con;
		int choice;

		std::string username;
		std::string password;
		std::string type_user;

		int carId;
		std::string manufacturer;
		std::string model;
		std::string color;
		std::string seats;
		std::string trunk_volume;
		std::string fuel_type;
		std::string typeof_gearbox;
		std::string location;
		std::string rentPerDay;
		std::string returnType;
		std::string status;

		do
		{
			std::cout << "------ Welcome to Car Sharing Application ------" << std::endl;
			std::cout << "1.Register as a new User " << std::endl;
			std::cout << "2.Login , If your an existing User!" << std::endl;
			std::cout << "3.Quit" << std::endl;
			std::cin >> choice;

			switch (choice)
			{
			case 1: // Register as a new user
			{
				std::cout << "Enter Username :" << std::endl;
				std::cin >> username;
				std::cout << "Enter Password :" << std::endl;
				std::cin >> password;
				std::cout << "What type of User are you?:" << std::endl;
				std::cout << "1. Car Owner" << std::endl;
				std::cout << "2. Car Renter" << std::endl;
				int userTypeChoice;
				std::cin >> userTypeChoice;
				type_user = ((userTypeChoice == 1) ? "Car Owner" : "Car Renter");

				userData["type"] = "user_register";
				userData["username"] = username;
				userData["password"] = password;
				userData["type_user"] = type_user;

				std::string returnStr = con.connection(userData);
				if (returnStr == "saved")
				{
					std::cout << "User data saved successfully." << std::endl;
				}
				else
				{
					std::cout << "Sorry, Error Occurred! "+ returnStr << std::endl;
				}
				break;
			}
			case 2: // Login
			{
				std::cout << "Enter Username :" << std::endl;
				std::cin >> username;
				std::cout << "Enter Password :" << std::endl;
				std::cin >> password;

				userData["type"] = "user_login";
				userData["username"] = username;
				userData["password"] = password;

				//-----------------start of car if--------------------------//

				if (con.connection(userData) == "true")
				{
					//call car options

					int userChoice;

					do
					{
						std::cout << "1.Add a new car to the pool" << std::endl;
						std::cout << "2.Show all my cars " << std::endl;
						std::cout << "3.Select a car for rent" << std::endl;
						std::cout << "4.Return a car back" << std::endl;
						std::cout << "5.Show all Available cars" << std::endl;
						std::cout << "6.Show all cars" << std::endl;
						std::cout << "7.Delete a car" << std::endl;
						std::cout << "8.Show car details" << std::endl;
						std::cout << "9.Logout" << std::endl;
                        std::cin >> userChoice;

						switch (userChoice)
						{
						case 1: // Add a new car
						{
							carData["type"] = "add_car";

							srand(time(NULL));
							carId = rand() % 9000 + 1000;
							carData["carId"] = std::to_string(carId);

							carData["username"] = username;

							std::cout << "Enter Manufacturer" << std::endl;
							std::cin >> manufacturer;
							carData["manufacturer"] = manufacturer;

							std::cout << "Enter Model" << std::endl;
							std::cin >> model;
							carData["model"] = model;

							std::cout << "Enter Color" << std::endl;
							std::cin >> color;
							carData["color"] = color;

							std::cout << "Enter Number of Seats " << std::endl;
							std::cin >> seats;
							carData["seats"] = seats;

							std::cout << "Enter Trunk Volume" << std::endl;
							std::cin >> trunk_volume;
							carData["trunk_volume"] = trunk_volume;

							std::cout << "Enter the type of fuel" << std::endl;
							std::cin >> fuel_type;
							carData["fuel_type"] = fuel_type;

							std::cout << "Enter the type of gearbox" << std::endl;
							std::cin >> typeof_gearbox;
							carData["typeof_gearbox"] = typeof_gearbox;

							std::cout << "Enter Location" << std::endl;
							std::cin >> location;
							carData["location"] = location;

							std::cout << "Enter Rent per Day" << std::endl;
							std::cin >> rentPerDay;
							carData["rentPerDay"] = rentPerDay;

							std::cout << "Enter type of return - fixed-time or until-return" << std::endl;
							std::cin >> returnType;
							carData["returnType"] = returnType;

							status = "Available";
							carData["status"] = status;

							if (con.connection(carData) == "car_added")
							{
								std::cout << "Car added successfully. Your car id is : " << carId << std::endl;
							}

							else
							{
								std::cout << "Some error occurred!" << std::endl;
							}

							break;
						}
						case 2: // Show my cars

						{
							carData["type"] = "show_my_cars";
							carData["username"] = username;

							std::string myCarsString = con.connection(carData);

							std::map<std::string, std::map<std::string, std::string>> myCars;
							std::stringstream ss(myCarsString);
							boost::archive::text_iarchive ia(ss);
							ia >> myCars;

							if (myCars.size() > 0)
							{
								for (std::map<std::string, std::map<std::string, std::string>>::iterator it = myCars.begin(); it != myCars.end(); ++it)
								{
									std::cout  << " Car ID : " << it->second["carId"] << " Manufacturer :\t" << it->second["manufacturer"] << '\n';
								}
							}

							else
							{
								std::cout << "You dont have any cars. Please add a car" << std::endl;
							}
							

							break;
						}

						case 3:  // selecting a car for rent
						{
							carData["type"] = "select_a_car";


							std::cout << "Enter carId :" << std::endl;
							std::cin >> carId;
							carData["carId"] = std::to_string(carId);

							std::string myCarsString = con.connection(carData);

							if (myCarsString == "car_selected")
							{
								std::cout << myCarsString << std::endl;
							}

							else
							{
								std::cout << myCarsString << std::endl;
							}

							break;

						}

						case 4: // Returing a car
						{
							carData["type"] = "return_car";

							std::cout << "Enter carId :" << std::endl;
							std::cin >> carId;
							carData["carId"] = std::to_string(carId);

							std::string myCarsString = con.connection(carData);

							if (myCarsString == "car_returned")
							{
								std::cout << myCarsString << std::endl;
							}
							else
							{
								std::cout << myCarsString << std::endl;
							}
							break;

						}

						case 5:  // Showing available cars
						{
							carData["type"] = "show_available_cars";
							
                            std::string myCarsString = con.connection(carData);

							std::map<std::string, std::map<std::string, std::string>> myCars;
							std::stringstream ss(myCarsString);
							boost::archive::text_iarchive ia(ss);
							ia >> myCars;

							if (myCars.size() > 0)
							{
								for (std::map<std::string, std::map<std::string, std::string>>::iterator it = myCars.begin(); it != myCars.end(); ++it)
								{
									std::cout << it->first << " Car ID : " << it->second["carId"] <<  "Manufacturer :"<< it->second["manufacturer"] << '\n';
								}
							}

							else
							{
								std::cout << "No car is available currently!! " << std::endl;
							}
							
							break;

						}

						case 6:  // Showing all cars
						{
							carData["type"] = "show_all_cars";
							carData["status"] = status;


							std::string myCarsString = con.connection(carData);

							std::map<std::string, std::map<std::string, std::string>> myCars;
							std::stringstream ss(myCarsString);
							boost::archive::text_iarchive ia(ss);
							ia >> myCars;

							if (myCars.size() > 0)
							{
								for (std::map<std::string, std::map<std::string, std::string>>::iterator it = myCars.begin(); it != myCars.end(); ++it)
								{
									std::cout  << " Car ID : " << it->second["carId"] << "  Manufacturer : "<< it->second["manufacturer"] <<"  Status : "<< it->second["status"] << '\n';
								}
							}

							else
							{
								std::cout << "No car is present in the cart" << std::endl;
							}

							
							break;

						}
						case 7:   // Deleting a car
						{
							carData["type"] = "delete_car";
							std::cout << "Enter carId :" << std::endl;
							std::cin >> carId;
							carData["carId"] = std::to_string(carId);
							std::string myCarsString = con.connection(carData);

							if (myCarsString == "car_deleted")
							{
								std::cout << myCarsString << std::endl;
							}

							else
							{
								std::cout << myCarsString << std::endl;
							}

							break;
						}

						case 8:  // Showing car details
						{
							carData["type"] = "show_car_info";
							std::cout << "Enter carId :" << std::endl;
							std::cin >> carId;
							carData["carId"] = std::to_string(carId);
							std::string myCarsString = con.connection(carData);

							std::map<std::string, std::map<std::string, std::string>> myCars;
							std::stringstream ss(myCarsString);
							boost::archive::text_iarchive ia(ss);
							ia >> myCars;

							if (myCars.size() > 0)
							{
								for (std::map<std::string, std::map<std::string, std::string>>::iterator it = myCars.begin(); it != myCars.end(); ++it)
								{
									std::cout << "Car ID :"<<it->second["carId"] << '\n';
									std::cout << "Manufacturer :" <<it->second["manufacturer"] << '\n';
									std::cout << "Model :"<< it->second["model"] << '\n';
									std::cout << "Color :" <<it->second["color"] << '\n';
									std::cout << "No of Seats :"<<it->second["seats"] << '\n';
									std::cout << "Trunk Volume :"<< it->second["trunk_volume"] << '\n';
									std::cout << "Type of Fuel :"<< it->second["fuel_type"] << '\n';
									std::cout << "Type of gearbox :"<< it->second["typeof_gearbox"] << '\n';
									std::cout << "Location :"<<it->second["location"] << '\n';
									std::cout << "Rent per day :" <<it->second["rentPerDay"] << '\n';
									std::cout << "Return type :" << it->second["returnType"] << '\n';
									std::cout << "Status :" << it->second["status"] << '\n';
									std::cout << "----------------------------" << std::endl;
								}
							}

							else
							{
								std::cout << "You dont have any cars. " << std::endl;
							}
						

							break;
						}

						case 9:
						{
							input();
						}
						default:
							exit(0);
							break;
						}

					} while (userChoice == 1 || userChoice == 2 || userChoice == 3 || userChoice == 4 || userChoice == 5 || userChoice == 6 || userChoice == 7 || userChoice == 8 || userChoice == 9);

				}

				//------------------end of car if------------------------------//
				else
				{
					std::cout << "Username or Password is incorrect" << std::endl;
					input();
				}
				break;
			}

			default:
				exit(0);
				break;
			}
		} while (choice == 1 || choice == 2);

	}

	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
