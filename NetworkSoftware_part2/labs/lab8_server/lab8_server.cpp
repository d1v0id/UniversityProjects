/*
 * lab8_server.cpp
 *
 *      Author: dmitry
 */
#include <iostream>
#include <vector>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#define PORT_NUM 1984

using boost::asio::ip::tcp;

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create(boost::asio::io_service& io_service) {
		return pointer(new tcp_connection(io_service));
	}

	tcp::socket& socket() {
		return socket_;
	}

	void start() {
		size_t len = socket_.read_some(boost::asio::buffer(buf));

		if (len > 0) {
			boost::asio::async_write(
				socket_,
				boost::asio::buffer(revert_message_text()),
				boost::bind(&tcp_connection::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
			);
		}
	}

private:
	tcp_connection(boost::asio::io_service& io_service) : socket_(io_service) {
	}

	void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/) {
	}

	std::string revert_message_text() {
		std::string result = "";
		std::vector<std::string> strVec;
		boost::algorithm::split(strVec, buf, boost::is_any_of(" "));

		for (std::vector<std::string>::iterator i = strVec.begin(); i != strVec.end(); i++) {
			std::cout << *i << std::endl;
			std::string tmp = "";

			int len = strlen((*i).c_str());
			for (int j = 0; j < len; j++) {
				tmp += (*i).at(len - j - 1);
			}

			result += tmp + " ";
		}

		result.at(result.length() - 1) = '\n';

		return result;
	}

	tcp::socket socket_;
	boost::array<char, 128> buf;
};

class tcp_server
{
public:
	tcp_server(boost::asio::io_service& io_service) : acceptor_(io_service, tcp::endpoint(tcp::v4(), PORT_NUM)) {
		start_accept();
	}

private:
	void start_accept() {
		tcp_connection::pointer new_connection = tcp_connection::create(acceptor_.get_io_service());

		acceptor_.async_accept(
				new_connection->socket(),
				boost::bind(&tcp_server::handle_accept, this, new_connection, boost::asio::placeholders::error)
		);
	}

	void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error) {
		if (!error) {
			new_connection->start();
		}

		start_accept();
	}

	tcp::acceptor acceptor_;
};

int main()
{
	printf("Port number: %d\n", PORT_NUM);
	try {
		boost::asio::io_service io_service;
		tcp_server server(io_service);
		io_service.run();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
