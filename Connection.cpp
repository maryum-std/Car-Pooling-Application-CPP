#include<iostream>
#include<boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <string>
#include <sstream>
#include"Connection.hpp"


using namespace boost::archive;


//method for connecting to the server using boosts asio udp
std::string Connect::connection(std::map<std::string, std::string> dataMap)
{
	// serializing the data sent to the server
	std::stringstream ss;
	text_oarchive oa{ ss };
	oa << dataMap;

	//creating object for boost asio udp
	typedef boost::asio::ip::udp asioudp;

	//creating object for io service
	boost::asio::io_service io_service;
	
	//defining endpoint and the port number of the server
	asioudp::endpoint receiver_endpoint = asioudp::endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), 13);
	
	//call socket constructor
	asioudp::socket socket(io_service);

	//open socket connection
	socket.open(asioudp::v4());

	//data for sending to the server
	std::string const send_buf = ss.str();

	//sending data to server
	socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

	//variable holding received data
	std::array<char, 4096> recv_buf;
	asioudp::endpoint sender_endpoint;

	//receive data from server
	size_t const len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
	std::string const recv_msg(recv_buf.data(), len);

	return recv_msg;
}

