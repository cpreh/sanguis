#include "file_size.hpp"

std::ifstream::pos_type file_size(std::ifstream &fn)
{
	fn.seekg(0,std::ios_base::end);
	std::ifstream::pos_type s = fn.tellg();
	fn.seekg(0,std::ios_base::beg);
	return s;
}
