#include "Network.hpp"
#include "Service.hpp"

//method for receiving data from client and directing it to the corresponding methods for serving the request
void Network::serverManage(void)
{
	try
	{
		//boost asio udp object
		typedef boost::asio::ip::udp asioudp;

		//boost asio io service object
		boost::asio::io_service io_service;

		//defining the endpoint and port number
		asioudp::socket socket(io_service, asioudp::endpoint(asioudp::v4(), 13));

		//creating object for Service class
		Service s;

		//map for holding received data
		std::map<std::string, std::string> inputData;

		while (true)
		{
			std::array<char, 4096> recv_buf;
			asioudp::endpoint remote_endpoint;
			boost::system::error_code error;
			std::size_t const received_bytes = socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint, 0, error);

			if (error && error != boost::asio::error::message_size)
				throw boost::system::system_error(error);

			std::string const inputmessage(recv_buf.data(), received_bytes);

			//de-serializing received data
			std::stringstream ss(inputmessage);
			boost::archive::text_iarchive ia(ss);
			ia >> inputData;

			//message for responding back to the client
			std::string message = "";

			//calling addUser method
			if (inputData["type"] == "user_register")
				message = s.addUser(inputData["username"], inputData["password"], inputData["type_user"]);

			//calling user validation method
			else if ((inputData["type"] == "user_login"))
				message = s.validateUser(inputData["username"], inputData["password"]);

			//calling method to add car to the pool
			else if (inputData["type"] == "add_car")
			{

				message = s.addCar(inputData["carId"], inputData["username"], inputData["manufacturer"], inputData["model"], inputData["color"], inputData["seats"], inputData["trunk_volume"], inputData["fuel_type"], inputData["typeof_gearbox"], inputData["location"], inputData["rentPerDay"], inputData["returnType"], inputData["status"]);
			}

			//calling method to show cars of a particular user
			else if (inputData["type"] == "show_my_cars")
			{
				message = s.showMyCars(inputData["username"]);
			}

			//calling method for selecting a particular car
			else if (inputData["type"] == "select_a_car")
			{
				message = s.selectCar(inputData["carId"]);
			}

			//calling method for returning a particular car
			else if (inputData["type"] == "return_car")
			{
				message = s.returnCar(inputData["carId"]);
			}

			//calling method for showing all available cars in the pool
			else if (inputData["type"] == "show_available_cars")
			{
				message = s.showAvailableCars();
			}

			//calling method for showing all cars in the pool
			else if (inputData["type"] == "show_all_cars")
			{
				message = s.showAllCars();
			}

			//calling method for deleting a car from the pool
			else if (inputData["type"] == "delete_car")
			{
				message = s.deleteCar(inputData["carId"]);
			}

			//calling method for showing details of a particular car
			else if (inputData["type"] == "show_car_info")
			{
				message = s.showCarInfo(inputData["carId"]);
			}

			boost::system::error_code ignored_error;

			//method for sending data back to the client
			socket.send_to(boost::asio::buffer(message), remote_endpoint, 0, ignored_error);
		}


	}

	//catch exception and display exception message
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
}