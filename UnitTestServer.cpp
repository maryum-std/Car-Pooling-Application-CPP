#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include "Service.hpp"

//test case for adding new user
BOOST_AUTO_TEST_CASE(addUserTest)
{
	BOOST_CHECK(addUser(“username”, ”password”, ”type_user”) == “1”);
}

//test case for login
BOOST_AUTO_TEST_CASE(validateUserTest)
{
	BOOST_CHECK(validateUser(“username”, ”password”) == “1”);
}

//test case for wrong username in login
BOOST_AUTO_TEST_CASE(validateUserFailUsernameTest)
{
	BOOST_CHECK(validateUser(“invalidusername”, ”password”) == “0”);
}

//test case for wrong password while login
BOOST_AUTO_TEST_CASE(validateUserFailPasswordTest)
{
	BOOST_CHECK(validateUser(“username”, ”invalidpassword”) == “0”);
}

//test case for adding new car
BOOST_AUTO_TEST_CASE(addCarTest)
{
	carMap[“carId”] = “carId”;
	carMap[“username”] = “username”;
	carMap[“manufacturer”] = “manufacturer”;
	carMap[“model”] = “model”;
	carMap[“color”] = “color”;
	carMap[“seats”] = “seats”;
	carMap[“trunk_volume”] = “trunk_volume”;
	carMap[“fuel_type”] = “fuel_type”;
	carMap[“typeof_gearbox”] = “ typeof_gearbox”;
	carMap[“location”] = “location”;
	carMap[“rentPerDay”] = “rentPerDay”;
	carMap[“returnType”] = “returnType”;
	carMap[“status”] = “status”;
	BOOST_CHECK(addCar() == "1");
}

//test case for showing particular user's cars
BOOST_AUTO_TEST_CASE(showMyCarsTest)
{
	BOOST_CHECK(showMyCars(“username”) == “1”);
}

//test case for selecting a car
BOOST_AUTO_TEST_CASE(selectCarTest)
{
	carMap[“carId”] = “carId”;
	BOOST_CHECK(selectCar() == "1”);
}

//test case for selecting a car with wrong car id
BOOST_AUTO_TEST_CASE(selectCarFailTest)
{
	carMap[“carId”] = “invalidcarId”;
	BOOST_CHECK(selectCar() == “0”);
}

//test case for returning a car
BOOST_AUTO_TEST_CASE(returnCarTest)
{
	carMap[“carId”] = “carId”;
	BOOST_CHECK(returnCar() == "1”);
}

//test case for returning a car with wrong car id
BOOST_AUTO_TEST_CASE(returnCarFailTest)
{
	carMap[“carId”] = “invalidcarId”;
	BOOST_CHECK(returnCar() == “0”);
}

//test case for deleting a car
BOOST_AUTO_TEST_CASE(deleteCarTest)
{
	server.carMap[“carId”] = “carId”;
	BOOST_CHECK(deleteCar() == "1");
}




