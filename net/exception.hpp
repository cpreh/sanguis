#ifndef NET_EXCEPTION_HPP_INCLUDED
#define NET_EXCEPTION_HPP_INCLUDED

#include "types.hpp"
#include <stdexcept>

namespace net
{
struct exception : public std::runtime_error
{
	explicit exception(const string_type &s) : std::runtime_error(s) {}
};
}

#endif
