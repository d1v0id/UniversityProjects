/*
 * lab8_client.cpp
 *
 *      Author: dmitry
 */
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	try {
		if (argc != 4) {
			std::cerr << "Usage: client <host> <port> <message>" << std::endl;
			return 1;
		}

		// All programs that use asio need to have io_service
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(argv[1], argv[2]);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		std::string message = argv[3];
		size_t writeLen = socket.write_some(boost::asio::buffer(message));

		for (;;) {
			boost::array<char, 128> buf;
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof) {
				break; // Connection closed cleanly by peer.
			}
			else if (error) {
				throw boost::system::system_error(error); // Some other error.
			}

			std::cout.write(buf.data(), len);
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
