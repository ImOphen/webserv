#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "Request.hpp"
#include "fstream"

class Response
{
	private:
		std::string		_response;
		int				_status_code;
		std::map<int, std::string>	_response_message;
	public:
		void init_response_code_message()
		{
			_response_message[200] = "OK";
			_response_message[403] = "Forbidden";
			_response_message[404] = "Not Found";
			_response_message[405] = "Method Not Allowed";
			_response_message[500] = "Internal Server Error";
			_response_message[502] = "Bad Gateway";		
		}
		Response(Request &request)
		{
			init_response_code_message();
			_status_code = 200;
			std::string content = "";
			std::string path = request.get_path();
			if (path == "/")
			{
				std::ifstream file("index.html");
				if (file.is_open())
				{
					std::string line = "";
					while (getline(file, line))
						content += line;
					file.close();
				}
			}
			else
			{
				_status_code = 404;
				content = "404 Not Found";
			}
			_response = "HTTP/1.1 " + std::to_string(_status_code) + " " + _response_message[_status_code] + "\r\n";
			_response += "Content-Type: text/html\r\n";
			_response += "Content-Length: " + std::to_string(content.size()) + "\r\n";
			_response += "\r\n\r\n";
			_response += content;
		}
		std::string		operator*()
		{
			return this->_response;
		}
};

#endif