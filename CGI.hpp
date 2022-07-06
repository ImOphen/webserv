#ifndef CGI_HPP
# define CGI_HPP

#include "Request.hpp"
#include <iostream>
#include <string>
#include <map>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef std::map<std::string, std::string>::iterator  map_iterator;

class CGI
{
    private:
        std::map<std::string, std::string>  _env;
        Request     const                   &_request;
        std::string const                   &_cgi_path;
        std::string const                   &_file;
        std::string                         _content;
    public:
        CGI(Request const &_req, std::string const &_file_path, std::string const &_fast_cgi_path);
        ~CGI();
        std::string _get_content();
    
    private:
        void        _set_content();
        void        _set_env_variables();
        char        **_get_env_array();
};

#endif