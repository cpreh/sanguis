#include "file_to_string.hpp"
#include "file_size.hpp"
#include <stdexcept>
#include <vector>
#include <fstream>

std::string const file_to_string(const std::string &fn)
{
	std::ifstream file(fn.c_str());
	if (!file.is_open())
		throw std::runtime_error("couldn't open file \""+fn+"\"");
	
	std::ifstream::pos_type const s = file_size(file);
	std::vector<char> str(s);
	file.read(&str[0],s);
	return std::string(str.begin(),str.end());
}
